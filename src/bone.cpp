#include "bone.hpp"
//Create a new bone and if parent exists, attach it as one of it's children.
Bone::Bone(Bone &prnt,string name, float x, float y, float z, float alpha, float beta, float gamma, float length )
	:parent(&prnt),name(name), x(x), y(y), z(z), alpha(alpha), beta(beta), gamma(gamma), length(length){
	prnt.children.push_back(*this);
}

Bone::Bone() :parent(NULL),name("root"), x(0.0f), y(0.0f), z(0.0f), alpha(0.0f), beta(0.0f), gamma(0.0f), length(0.0f){
	root = this;
}

void Bone::addChild(const Bone child){
	children.push_back(child);
};

Bone::Bone(const Bone &other)
	:parent(other.parent),name(other.name), x(other.x), y(other.y), z(other.z), alpha(other.alpha), beta(other.beta), gamma(other.gamma), length(other.length){
	if( other.parent->parent ){
		for(vector<Bone>::iterator it = this->parent->parent->children.begin(); it != this->parent->parent->children.end() ; ++it){
			if(!it->name.compare(other.parent->name) ){
				this->parent = &(*it);
				Bone * grandParent = this->parent->parent;
				this->parent->parent = NULL;			//Prevents copy constructor infinite loop;
				it->children.push_back(*this);
				this->parent->parent = grandParent;
			}
		}
	}
		
}

int Bone::size(void){
	return children.size();
}
Bone * Bone::printHeirarchyUp(void){
	return NULL;
	/*
	cout << "\t" << name << " children size " << children.size() << " ptr " << this<< endl;
	if(!parent){
		return this;
	}else 
		return parent->printHeirarchyUp();
	*/
}

void Bone::printHeirarchy(void){
	
	cout << "\t" << name << " children size " << children.size() << endl;
	
	//Call function on all my children
	for(vector<Bone>::iterator it = children.begin(); it != children.end(); ++it){
		it->printHeirarchy();
	}
	
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
	glRotatef(beta,0.0,1.0,0.0);
	glRotatef(gamma,0.0,0.0,1.0);
	glBegin(GL_LINES);{
		glColor3f(1.0,0.0,1.0);
		glVertex3f(0.0,0.0,0.0);
		glColor3f(0.0,1.0,0.0);
		glVertex3f(0.0,length,0.0);
	}glEnd();
	//To reach to the new position
	glTranslatef(0.0,length,0.0);
	cout << "Drawing " << name << endl;
	//Call function on all my children
	for(vector<Bone>::iterator it = children.begin(); it != children.end(); ++it){
		it->draw();
	}
	glPopMatrix();
}

