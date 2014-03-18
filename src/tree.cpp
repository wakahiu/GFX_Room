#include "tree.hpp"

Tree::Tree(RowVector3d v){
	root = new Node( v );
	
	numEff = 0;
	numJoints = 0;
	activeEff = NULL;
	activeJoint = NULL;
}

void Tree::incrementAngle(float dTh){

	Node * jnt; 
	if( !activeJoint ){
		return;
		activeJoint = root;
		jnt = root;
	}else{
		jnt =  activeJoint;;
	}
	
	VectorXd Vdth(numJoints);
	Vdth.setZero();
	//cout << "JoinID " << jnt->jointId << endl;
	Vdth(jnt->jointId) += RAD(dTh);
	//cout << Vdth << endl << endl;
	updateJoints(Vdth);
	
}

bool Tree::selectEffector(float px, float py, float pz){
	stack<Node *> seqTree;
	seqTree.push( root );
	RowVector3d currPos(px,py,0);
	
	//cout << "Looking for " << currPos << endl;

	while(!seqTree.empty()){
		Node * node = seqTree.top();
		seqTree.pop(); 
		
		if(node->getType() == EFFECTOR || node->getType() == BOTH || node->getType() == INACTIVE){
				RowVector3d * Si = node->posAbs;
				RowVector3d * off = node->posOffset;
				//cout << *Si << endl;
				if( (currPos - (*Si + *off)).norm()  < 0.5 ){
					activeEff->type = INACTIVE;
					activeEff = node;
					activeEff->type = EFFECTOR;
					return true;
				}
			}

		for( struct nodeLink * curr = node->children; curr; curr = curr->next){
			seqTree.push( curr->node );
		}
	}
	return false;
}

bool Tree::selectJoint(float px, float py, float pz){
	stack<Node *> seqTree;
	seqTree.push( root );
	RowVector3d currPos(px,py,0);
	
	//cout << "Looking for " << currPos << endl;

	while(!seqTree.empty()){
		Node * node = seqTree.top();
		seqTree.pop(); 
		
		if(node->getType() == JOINT || node->getType() == BOTH){
				RowVector3d * Si = node->posAbs;
				RowVector3d * off = node->posOffset;
				//cout << *Si << endl;
				if( (currPos - (*Si + *off)).norm()  < 0.5 ){
					activeJoint = node;
					activeJoint->isActiveJoint = false;
					node->isActiveJoint = true;
					return true;
				}
			}

		for( struct nodeLink * curr = node->children; curr; curr = curr->next){
			seqTree.push( curr->node );
		}
	}
	return false;
}

void Tree::addChild(	string parentName,string childName, 
				RowVector3d posOffset, RowVector3d axisRot,
				double theta, float length,
				nodeType type, bool isAbs, bool frozen ){			
			
	Node * parent = __getNode(root, parentName);
	assert( parent );
	
	//RowVector3d * posAbs = new RowVector3d( *parent->posAbs + *parent->posOffset );

	double s = sin(RAD( parent->theta/2.0 ) );
	double c = cos(RAD( parent->theta/2.0 ) );
	double px = parent->axisRot->x();
	double py = parent->axisRot->y();
	double pz = parent->axisRot->z();
	
	Quaterniond * pg = parent->quat;
	Quaterniond q( c , s*px , s*py, s* pz );
	Quaterniond p( 0, 0, parent->length, 0 );
	
	//Quaternion rotations are p*q*pinv
	Quaterniond rot_p( q * (*pg) * p * pg->inverse() * q.inverse()  );
	
	RowVector3d posAbs( rot_p.x() , rot_p.y(), rot_p.z());
	
	posAbs += (*parent->posAbs + *parent->posOffset );

	
	Node * child = new Node(	*parent, childName,
								posAbs, posOffset, axisRot,
								theta, length,
								type, isAbs, frozen); 
	
	switch( type ){
		case EFFECTOR:
			child->effId = numEff++;
			if(activeEff){
				activeEff->type = INACTIVE;
				
			}
			activeEff = child;
			break;
		case JOINT:
			child->jointId = numJoints++;
			break;
		case BOTH:
			child->effId = numEff++;
			child->jointId = numJoints++;
			if(activeEff){
				activeEff->type = INACTIVE;
			}
			break;
	}
	child->quat = new Quaterniond( q * (*pg) ) ;
	parent->addChild( child );
}
//Finds a node by name in tree structure and return it's pointer if found. 
//Return null otherwise.
Node * Tree::__getNode(Node * n, string name){
	if( n->name.compare(name) == 0 ){
		//Fount it
		return n;
	}else{
	
		//DFS search
		struct nodeLink * curr = n->children;
		Node * rtnNode;
		
		while( curr ){
			rtnNode = __getNode( curr->node, name);
			
			//Found it?
			if( rtnNode)
				return rtnNode;
				
			curr = curr->next;
		}
		
	}
	return NULL;
}
		
		
void Tree::draw(void){
	__draw(root);
}

void Tree::__draw(Node * n){
	glPushMatrix();
	
	/* Draw this bone
 	 * 1. Translate to coords
 	 * 2. Rotate the matrix (Quaternions?)
 	 * 3. Draw the line
 	 * 4. Reach the end position (translate again)
 	 */
 	 GLfloat otherColor[] = {0.3, 0.3, 0.3, 0.0};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, otherColor);
		
 	if(n->isAbs)
		glTranslatef(n->posAbs->x(),n->posAbs->y(),n->posAbs->z());
	else{
		glTranslatef(n->posOffset->x(),n->posOffset->y(),n->posOffset->z());
	}
	
	if( n->type == JOINT ) {
		if( n->isActiveJoint ){
			GLfloat effColor[] = {0.9, 0.9, 0, 0.0};
			glMaterialfv(GL_FRONT, GL_DIFFUSE, effColor);
			glutSolidSphere(0.4,26,46);
		}else{
			glutSolidSphere(0.4,20,20);
		}
	}
	else if( (n->type == BOTH) || (n->type == INACTIVE)){
		GLfloat effColor[] = {0.0, 0.9, 1, 0.4};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, effColor);
		if( !n->name.compare( "headEff") ){
			glutSolidSphere(1.0,26,46);
		}else{
			glutSolidSphere(0.4,16,16);
		}
	}else if(  n->type == EFFECTOR ){
		GLfloat effColor[] = {0.0, 1.0, .2, 0.4};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, effColor);
		if( !n->name.compare( "headEff") ){
			glutSolidSphere(1.0,26,46);
		}else{
			glutSolidSphere(0.4,16,16);
		}
	}
	
	glMaterialfv(GL_FRONT, GL_DIFFUSE, otherColor);
	glRotatef(n->theta,n->axisRot->x(),n->axisRot->y(),n->axisRot->z());
	glTranslatef(0.0,n->length*0.5,0.0);
	glPushMatrix();
	glScalef(1.0,n->length*4.5,1.0);
	glutSolidCube(0.2);
	glPopMatrix();
	
	//To reach to the new position
	glTranslatef(0.0,n->length*0.5,0.0);
	//Call function on all my children
	struct nodeLink * curr = n->children;
	
	while( curr ){
		__draw( curr->node );
		curr = curr->next;
	}
	
	glPopMatrix();
	
}	

void Tree::updateJoints( VectorXd dTh ){
	//DFS traversal of the tree to get update the joint angles.
	stack<Node *> seqTree;
	seqTree.push( root );

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
	seqTree.push( root );
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
		node->posAbs->x() = rot_p.x() + pr->posAbs->x() + pr->posOffset->x();
		node->posAbs->y() = rot_p.y() + pr->posAbs->y() + pr->posOffset->y();
		node->posAbs->z() = rot_p.z() + pr->posAbs->z() + pr->posOffset->z();
		
		node->quat = new Quaterniond( q * (*pg) ) ;
	
	}	
}

void Tree::printHeirarchy(void){
	cout << "-- printing tree --" << endl;
	__printHeirarchy( root, 0);
}
//Print helper function
void Tree::__printHeirarchy(Node * n, int rank){
	
	for(int i=0; i < rank; i++)
			cout << "  " ;
	cout << n->name << " " << *n->posAbs << endl;
	
	struct nodeLink * curr = n->children;
	while( curr ){
		__printHeirarchy( curr->node, rank+1);
		curr = curr->next;
	}
}
