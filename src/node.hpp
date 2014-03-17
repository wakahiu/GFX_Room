#include "common_header.h"

#ifndef NODE
#define NODE
/*
* Node structure. Each node contains a position, length and angle
*/

class Node{

	friend class Tree;
	friend class IKsolver;
private:
	
	string name;					//Unique string id.
	RowVector3d * posAbs;			//Absolute position
	RowVector3d * posOffset;		//Offset relative to parent
	RowVector3d * axisRot;			//Axis of Rotation
	int effId;						//Effector id
	int jointId;					//Joint id
	enum nodeType type;  			//Effector/joint/both
	bool	 isAbs;					//Absolute position or relative position
	double theta;					//Angle or rotation in radians
	float length;					//Length
	struct nodeLink * children;		//Children linked list
	Node * parent;					//Parent		
	bool frozen;					//Frozen or active
	Quaterniond * quat;				//All the rotations that have happened to ancesotors
	
public:
	//Create a new node and attach it to parent.
	Node(	Node &parent,string name, 
			RowVector3d posAbs, RowVector3d posOffset, RowVector3d axisRot,
			double theta, float length,
			nodeType type, bool isAbs, bool frozen);
			
	Node(const RowVector3d v);
	Node(const Node &other);
	//Takes a node and adds a child. If it doesn't exist, it creates a childless 
	//node;
	//Takes a node and prints to std out the heirarchy

	int	size(void);
	void addChild(Node * child);
	nodeType getType(void){return type;}
			
};

struct nodeLink{
	Node* node;
	nodeLink* next;
};

#endif
