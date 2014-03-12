#include "common_header.h"

#ifndef BONE
#define BONE
/*
* Bone structure. Each bone contains a position, length and angle
*/

class Bone{

private:
		string name;
	//Bone positions
	 float x;
	 float y;
	 float z;
	 
	 //Bone angles aplha=x, beta=y, gamma=z
	 float alpha;
	 float beta;
	 float gamma;
	 
	 //Length
	 float length;
	 struct boneNode * childList;
	 
	 //Children
	 list<Bone> children;
	 //Only one parent
	 Bone * parent;
	 Bone * root;
	 Bone * sibling;
public:
	//Create a new bone and attached it to parent.
	Bone(Bone &prnt,string name, float x, float y, float z, float alpha, float beta, float gamma, float length );
	Bone();
	Bone(const Bone &other);
	//Takes a bone and adds a child. If it doesn't exist, it creates a childless 
	//bone;
	//Takes a bone and prints to std out the heirarchy
	void printHeirarchy(int rank);
	void draw(void);
	int	size(void);
	void incrementAngle(float a);
	void addChild(const Bone child);
			
};

struct boneNode{
	Bone* bone;
	boneNode* next;
};

#endif
