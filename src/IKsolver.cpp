#include "IKsolver.hpp"

IKsolver::IKsolver(Tree * T): T(T){
	J.resize(3*T->numEff, T->numJoints);
	J.setZero();
}

void IKsolver::solve(void){
	
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
		
		if(node->getType() == EFFECTOR){
			
			row = 3*(node->effId);
			
			//Get all ancesotors - joints that affect joint node n.
			for( Node * ancestor = node->parent; ancestor ; ancestor = ancestor->parent){
				/*
				* If the i'th end effector is affected by joint j, then the
				* Jacobian matrix entry is given by:
				*ds/d@ = Vj x (Si-Pj)
				*/
				RowVector3d * Pj = node->posAbs;
				RowVector3d * Vj = node->axisRot;
				RowVector3d Uij = Vj->cross(*Si-*Pj);
				
				col = node->jointId;
				
				cout << Uij << endl;
				//J(row, col) = Uij.x();
				//J(row+1, col) = Uij.y();
				//J(row+1, col) = Uij.z();
				
			}
			
		}
		
		for( struct nodeLink * curr = node->children; curr; curr = curr->next){
			seqTree.push( curr->node );
		}
	}
	
	cout << "---------------\n" << J << endl ;
}
