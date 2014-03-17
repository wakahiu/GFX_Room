#include "IKsolver.hpp"

IKsolver::IKsolver(Tree * T): T(T){
	J.resize(3*(T->numEff), T->numJoints);
	J.setZero();
	//cout << endl << J  << endl; 
	
	Jpinv.resize(T->numJoints, 3*(T->numEff) );
	Jpinv.setZero();
	e.resize( 3*(T->numEff) );
	e.setZero();
	s.resize( 3*(T->numEff) );
	__updateS( );
	prevTarget.resize(3*(T->numEff));
	prevTarget.setZero();
}

void IKsolver::solve( VectorXd target){
	
	//if( (target - prevTarget).norm() > 0.0001  ){
	//cout << "Moved " <<  endl;
	updateJacobian();
	updateJacobianPinvDLS();
	__updateS( );
	e = target - s;
	
	VectorXd deltaTheta = Jpinv * e;
	
	/*
	//Clamp the delta thetas
	float MAX_DTH = M_PI*0.001;
	for(int i = 0; i < deltaTheta.size(); i++){
		deltaTheta(i) = deltaTheta(i) > MAX_DTH ? MAX_DTH : deltaTheta(i);
	}*/
	
	updateJoints(deltaTheta);
	
	__updateS( );
	VectorXd eNew = target - s;
	
	cout << eNew << endl;

	if( e.norm() / eNew.norm() < 1.0 ){
		cout << "Went Further\n" ;
		updateJoints(-deltaTheta);
		lbd *= 2;
		this->solve( target - e/2.0);
		lbd /= 2;
		//this->solve( target + e/2.0);
	}
		
		
	//}
	prevTarget = target;
	 
}

void IKsolver::__updateS( void ){
	
	//DFS traversal of the tree to get current position of end effectors.
	stack<Node *> seqTree;
	seqTree.push( T->getRoot() );

	while(!seqTree.empty()){
		Node * node = seqTree.top();
		seqTree.pop(); 
		
		if(node->getType() == EFFECTOR || node->getType() == BOTH){
				RowVector3d * Si = node->posAbs;
				//cout << endl << *Si << endl;
				int idx = 3*(node->effId);
				s(idx) = 	Si->x();
				s(idx+1)= 	Si->y();
				s(idx+2)=	Si->z();
			}

		for( struct nodeLink * curr = node->children; curr; curr = curr->next){
			seqTree.push( curr->node );
		}
	}
}



void IKsolver::updateJoints( VectorXd dTh ){
	//DFS traversal of the tree to get update the joint angles.
	stack<Node *> seqTree;
	seqTree.push( T->getRoot() );

	//Update the angles th += dth
	while(!seqTree.empty()){
		Node * node = seqTree.top();
		seqTree.pop(); 
		
		for( struct nodeLink * curr = node->children; curr; curr = curr->next){
			seqTree.push( curr->node );
		}
		
		if( node->parent && (node->getType() == JOINT  || node->getType() == BOTH) ){
			
				int idx = (node->jointId);
				//cout << idx;
				double phi = DEG( dTh( idx ) );
				node->theta += phi;
		}
	}

	//Angles updated.
	//Now we follow the tree structure from the root updating the absolute positions
	seqTree.push( T->getRoot() );
	while(!seqTree.empty()){
	
		Node * node = seqTree.top();
		seqTree.pop();
		
		for( struct nodeLink * curr = node->children; curr; curr = curr->next){
			seqTree.push( curr->node );
		}
		
		if( node->parent == NULL){
			continue;
		}
		
		Node * pr = node->parent;
		//Update the positions of joints
		double s = sin(RAD( node->parent->theta/2.0 ) );
		double c = cos(RAD( node->parent->theta/2.0 ) );
		double px = node->parent->axisRot->x();
		double py = node->parent->axisRot->y();
		double pz = node->parent->axisRot->z();
		
		Quaterniond * pg = node->parent->quat;
		Quaterniond q( c , s*px , s*py, s* pz );
		Quaterniond p( 0, 0, node->parent->length, 0 );
		
		//Quaternion rotations are p*q*pinv
		Quaterniond rot_p( q * (*pg) * p * pg->inverse() * q.inverse()  );
		
		//cout << "Position " << rot_p.x() << endl;
		node->posAbs->x() = rot_p.x() + pr->posAbs->x();
		node->posAbs->y() = rot_p.y() + pr->posAbs->y();;
		node->posAbs->z() = rot_p.z() + pr->posAbs->z();;
		
		node->quat = new Quaterniond( q * (*pg) ) ;
	
	}	
}

void IKsolver::updateJacobianPinvDLS(void){
	//cout << "----- J -----" << endl;
	//cout << J << endl;
	cout << "----- Jtr -----" << endl;
	MatrixXd Jtr = J.transpose();
	cout << Jtr << endl;
	cout << "----- J_x_Jtr -----" << endl;
	MatrixXd J_x_Jtr = J*Jtr + MatrixXd::Identity(3*(T->numEff) , 3*(T->numEff) ) * lbd* lbd;
	cout << J_x_Jtr << endl << endl;
	cout << "----- Jpinv -----" << endl;
	Jpinv = Jtr*J_x_Jtr.inverse();
	cout << Jpinv <<endl;
}

void IKsolver::updateJacobian(void){
	
	//DFS traversal of all nodes to create a Jacobian Matrix
	stack<Node *> seqTree;
	seqTree.push( T->getRoot() );
	int row, col;

	/*
	* create a jacobian matrix of size 3k*n. Where k is the number of effectors 
	* and n is the number of joints
	*/
	while(!seqTree.empty()){
		Node * node = seqTree.top();
		seqTree.pop();
		
		RowVector3d * Si = node->posAbs; 
		
		if(node->getType() == EFFECTOR || node->getType() == BOTH){
			
			row = 3*(node->effId);
			
			//Get all ancesotors - joints that affect joint node n.
			for( Node * ancestor = node->parent; ancestor && ancestor->parent ; ancestor = ancestor->parent){
				/*
				* If the i'th end effector is affected by joint j, then the
				* Jacobian matrix entry is given by:
				*ds/d@ = Vj x (Si-Pj)
				*/
				//cout << ancestor->name << endl;
				RowVector3d * Pj = ancestor->posAbs;
				RowVector3d * Vj = ancestor->axisRot;
				RowVector3d Uij = Vj->cross(*Si-*Pj);
				
				col = ancestor->jointId;
				
				J(row,col) = Uij.x();
				J(row+1, col) = Uij.y();
				J(row+2, col) = Uij.z();
				
			}
			
		}
		
		for( struct nodeLink * curr = node->children; curr; curr = curr->next){
			seqTree.push( curr->node );
		}
	}
	cout << "Done updating Jacobian\n" << J << endl;
}
