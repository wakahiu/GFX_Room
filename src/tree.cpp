#include "tree.hpp"

Tree::Tree(RowVector3d v){
	root = new Node( v );
	
	numEff = 0;
	numJoints = 0;
}

void Tree::incrementAngle(float dTh){
	root->theta+=dTh;
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
			cout << child->effId << endl;
			break;
		case JOINT:
			
			child->jointId = numJoints++;
			
			break;
		case BOTH:
			child->effId = numEff++;
			child->jointId = numJoints++;
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
 	if(n->isAbs)
		glTranslatef(n->posAbs->x(),n->posAbs->y(),n->posAbs->z());
	else
		glTranslatef(n->posOffset->x(),n->posOffset->y(),n->posOffset->z());
	
	if( n->type == JOINT ) {
		glutSolidSphere(0.4,20,20);
	}
	
	glRotatef(n->theta,n->axisRot->x(),n->axisRot->y(),n->axisRot->z());
	
	
	glTranslatef(0.0,n->length*0.5,0.0);
	
	if( (n->type == EFFECTOR) || (n->type == BOTH) ){
		GLfloat effColor[] = {1.0, 0.0, 1.0, 0.0};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, effColor);
		glColor3f(0.0,0.0,1.0);
		glutSolidSphere(0.4,16,16);
	}
	
	
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
