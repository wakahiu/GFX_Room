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
VectorXd IKsolver::initTargs(void){
	
	VectorXd Targs(3*T->numEff);
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
		
		if( (node->getType() == INACTIVE || node->getType() == EFFECTOR  || node->getType() == BOTH) ){
			
			RowVector3d * Si = node->posAbs;
				Targs( 3*node->effId + 0 ) = Si->x();
				Targs( 3*node->effId + 1 ) = Si->y();
				Targs( 3*node->effId + 2 ) = Si->z();
		}
	}
	return Targs;
}

void IKsolver::solve( VectorXd target){
	
	updateJacobian();
	updateJacobianPinvDLS();
	
	__updateS( );
	e = target - s;
	
	int k = this->getActiveEffId();
	
	//Display the position of the target
	GLfloat effColor[] = {.5, 0.9, 1, 0.4};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, effColor);
	glPushMatrix();
	glTranslatef( target(k*3+0), target(k*3+1), target(k*3+2) );
	glutSolidSphere(0.2,16,16);
	glPopMatrix();
	GLfloat otherColor[] = {0.3, 0.3, 0.3, 0.0};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, otherColor);
	
	VectorXd deltaTheta = Jpinv * e;
	
	T->updateJoints(deltaTheta);
	return;
	 
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

int IKsolver::getActiveEffId(void){
	return T->activeEff->effId;
}

void IKsolver::updateJacobianPinvDLS(void){
	//cout << "----- J -----" << endl;
	//cout << J << endl;
	//cout << "----- Jtr -----" << endl;
	MatrixXd Jtr = J.transpose();
	//cout << Jtr << endl;
	//cout << "----- J_x_Jtr -----" << endl;
	MatrixXd J_x_Jtr = J*Jtr + MatrixXd::Identity(3*(T->numEff) , 3*(T->numEff) ) * lbd* lbd;
	//cout << J_x_Jtr << endl << endl;
	//cout << "----- Jpinv -----" << endl;
	Jpinv = Jtr*J_x_Jtr.inverse();
	//cout << Jpinv <<endl;
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
}
