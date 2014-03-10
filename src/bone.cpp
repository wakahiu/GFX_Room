#include "bone.hpp"
//Create a new bone and if parent exists, attach it as one of it's children.
Bone::Bone(Bone &parent,string name, float x, float y, float z, float alpha, float beta, float gamma, float length )
	:parent(&parent),name(name), x(x), y(y), z(z), alpha(alpha), beta(beta), gamma(gamma), length(length){
	if(&parent){
		parent.children.push_back(*this);
	}
}
//Takes a bone and adds a child. If it doesn't exist, it creates a childless 
//bone;
/*
Bone::Bone(Bone parent):parent(parent){
	if(parent){
		parent.children.push_back(this);
	}
}
*/


void Bone::printHeirarchy(void){
	return;
}

//Consider using quaternions
void Bone::draw(void){
	glPushMatrix();
	
	/* Draw this bone
 	 * 1. Translate to coords
 	 * 2. Rotate the matrix (Quaternions?)
 	 * 3. Draw the line
 	 * 4. Reach the end position (translate again)
 	 */
	glTranslatef(x,y,z);
	glRotatef(alpha,1.0,0.0,0.0);
	glBegin(GL_LINES);{
		glColor3f(1.0,0.0,1.0);
		glVertex3f(0.0,0.0,0.0);
		glColor3f(0.0,1.0,0.0);
		glVertex3f(length,0.0,0.0);
	}glEnd();
	//To reach to the new position
	glTranslatef(length,0,0);
	
	//Call function on all my children
	for(vector<Bone>::iterator it = children.begin(); it != children.end(); ++it){
		(*it).draw();
	}
	glPopMatrix();
}

