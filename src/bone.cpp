#include "bone.hpp"
//Create a new bone and if parent exists, attach it as one of it's children.
Bone::Bone(Bone &prnt,string name, float x, float y, float z, float alpha, float beta, float gamma, float length )
	:parent(&prnt),name(name), x(x), y(y), z(z), alpha(alpha), beta(beta), gamma(gamma), length(length),childList(NULL){
	
	struct boneNode * newNode = (struct boneNode*)malloc(sizeof(struct boneNode));
	newNode->bone = this;
	newNode->next = prnt.childList;
	parent->childList = newNode;
	
}

Bone::Bone() :parent(NULL),name("root"), x(0.0f), y(0.0f), z(0.0f), alpha(0.0f), beta(0.0f), gamma(0.0f), length(0.0f),childList(NULL){
}

void Bone::addChild(const Bone child){
	children.push_back(child);
};

Bone::Bone(const Bone &other)
	:parent(other.parent),name(other.name), x(other.x), y(other.y), z(other.z), alpha(other.alpha), beta(other.beta), gamma(other.gamma), length(other.length){
	cout << "copy constructor called " << other.name << " parent "  << other.parent->name << endl;
	/*if( other.parent->parent ){
		for(list<Bone>::iterator it = this->parent->parent->children.begin(); it != this->parent->parent->children.end() ; ++it){
			cout << it->name << "==" << other.parent->name << it->children.size() <<"\t" ;
			if(!it->name.compare(other.parent->name) ){ 
				cout << "found one " << other.parent->name << endl;
				this->parent = &(*it);
				Bone * grandParent = this->parent->parent;
				this->parent->parent = NULL;			//Prevents copy constructor infinite loop;
				it->children.push_back(*this);
				this->parent->parent = grandParent;
				cout << "\nPush bone " << this->name << " " << it->children.size() << " to parent " << this->parent->name << endl;
			}
		}
	}
	*/
}

int Bone::size(void){
	return children.size();
}


void Bone::printHeirarchy(int rank){
	
	for(int i=0; i < rank; i++)
			cout << "\t" ;
	cout << this->name << endl;
	
	struct boneNode * curr = this->childList;
	while( curr ){
		curr->bone->printHeirarchy(rank+1);
		curr = curr->next;
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
	struct boneNode * curr = this->childList;
	while( curr ){
		curr->bone->draw();
		curr = curr->next;
	}
	glPopMatrix();
}

