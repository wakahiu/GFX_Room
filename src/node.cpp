#include "node.hpp"
//Create a new node and if parent exists, attach it as one of it's children.
Node::Node(	Node &parent,string name, 
			RowVector3d posAbs, RowVector3d posOffset, RowVector3d axisRot,
			double theta, float length,
			nodeType type, bool isAbs, bool frozen):
			
	parent(&parent),
	name(name),
	
	posAbs( new RowVector3d(posAbs) ),
	posOffset( new RowVector3d(posOffset) ),
	axisRot( new RowVector3d(axisRot) ),
	
	theta(theta),
	length(length),
	quat( new Quaterniond( 1.0,0.0,0.0,0.0 ) ),
	children(NULL),
	effId(-1),
	jointId(-1),
	type(type),
	isAbs(isAbs),
	frozen(frozen),
	isActiveJoint(false){
	
}

Node::Node( const RowVector3d v ):
	parent(NULL),
	name("root"),
	theta(0.0),
	length(0.0),
	
	posAbs( new RowVector3d(v)),
	posOffset( new RowVector3d(0.0,0.0,0.0) ),
	axisRot( (new RowVector3d(0.0,0.0,1.0)) ),
	
	quat( new Quaterniond( 1.0,0.0,0.0,0.0 )),
	children(NULL),
	effId(-1),
	jointId(-1),
	type(JOINT),
	isAbs(true),
	frozen(false),
	isActiveJoint(true){
}

Node::Node(const Node &other)
		:parent(parent),
	name(other.name),
	theta(other.theta),
	length(other.length),
	
	posAbs(new RowVector3d( *other.posAbs) ),
	posOffset(new RowVector3d( *other.posOffset) ),
	axisRot(new RowVector3d( *other.axisRot) ),

	quat(other.quat),
	effId(other.effId),
	jointId(other.jointId),
	type(other.type),
	isAbs(other.isAbs),
	frozen(other.frozen),
	children(NULL),
	isActiveJoint(other.isActiveJoint){
}

void Node::addChild(Node * child){
	struct nodeLink * temp = new nodeLink();
	temp->next = children;
	temp->node = child;
	child->parent = this;
	children = temp;
};


