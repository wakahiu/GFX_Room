#include "node.hpp"
#include "common_header.h"

#ifndef TREE
#define TREE

class Tree{

	friend class IKsolver;
private:
	Node * root;
	int numEff;
	int numJoints;
	
	void __draw(Node * n);
	void __printHeirarchy(Node  * n, int rank);
	Node * __getNode(Node * n, string name);
	
	
	
public:
	void incrementAngle(float dTh);
	Tree(RowVector3d v);
	void printHeirarchy(void);
	void draw(void);
	void addChild( 	string parentName,string childName, 
					RowVector3d posOffset, RowVector3d axisRot,
					double theta, float length,
					nodeType type, bool isAbs, bool frozen );
	
	//
	Node * getRoot(void){ return root; }
};
#endif	
