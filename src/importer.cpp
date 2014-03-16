#include "importer.hpp"

Tree * createPSCM( float x, float y, float z ){

	RowVector3d rootPos( (double)x, (double)y , (double)z );
	
	//Create a rooted tree. The root position is assumed to be absolute
	Tree * T = new Tree( rootPos );

	T->addChild( "root", "child1", 
			RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
			RowVector3d(0.0,0.0,0.0),						//Axis of rotation
			0.0, 3.0,
			JOINT, false, false );
			
	T->addChild( "child1", "child2", 
			RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
			RowVector3d(0.0,0.0,1.0),						//Axis of rotation
			90.0, 3.0,
			JOINT, false, false );	
		
	T->addChild( "child2", "child3", 
			RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
			RowVector3d(0.0,0.0,1.0),						//Axis of rotation
			-90.0, 3.0,
			JOINT, false, false );
			
	T->addChild( "child3", "child4", 
			RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
			RowVector3d(0.0,0.0,1.0),						//Axis of rotation
			-90.0, 3.0,
			JOINT, false, false );
			
	T->addChild( "child4", "eff1", 
			RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
			RowVector3d(0.0,0.0,1.0),						//Axis of rotation
			00.0, 0.0,
			EFFECTOR, false, false );
				
	return T;
}

Tree * createPerson( float x, float y, float z ){
	RowVector3d rootPos( (double)x, (double)y , (double)z );
	
	//Create a rooted tree
	Tree * T = new Tree( rootPos );
	
	//Create a root Node.
	//This is a "null" Node that represents a single point and is the 
	//Animation center of the structure
	/*
	Node neck(	root , "neck", 
				0.0,0.0,0.0,
				0.0,0.0,0.0,
				1.0);
		
		Node head(	neck , "head", 
					0.0,0.0,0.0,
					0.0,0.0,00.0,
					0.5);
							
	Node back(	root , "back", 
				0.0,0.0,0.0,
				0.0,0.0,180.0,
				2.5);
				
		Node rPelvis(	back , "rPelvis", 
					0.0,0.0,0.0,
					0.0,0.0,45.0,
					0.8f);
		
			Node rFemur(	rPelvis , "rFemur", 
						0.0,0.0,0.0,
						0.0,0.0,-45.0,
						2.5f);
			
				Node rTibia(	rFemur , "rTibia", 
							0.0,0.0,0.0,
							0.0,0.0,00.0,
							2.5f);
						
		Node lPelvis(	back , "lPelvis", 
					0.0,0.0,0.0,
					0.0,0.0,-45.0,
					0.8);
			
			Node lFemur(	lPelvis , "lFemur", 
						0.0,0.0,0.0,
						0.0,0.0,45.0,
						2.5f);
						
				Node lTibia( lFemur , "lTibia", 
						0.0,0.0,0.0,
						0.0,0.0,00.0,
						2.5f);

	Node rHumerus(	root , "rHumerus", 
				0.0,0.0,0.0,
				0.0,0.0,120.0,
				1.5);
				
		Node rUlna(	rHumerus  , "rUlna", 
					0.0,0.0,0.0,
					0.0,0.0,-60.0,
					1.5);
				
	Node lHumerus(	root , "lHumerus", 
				0.0,0.0,0.0,
				0.0,0.0,-120.0,
				1.5);
		
		Node lUlna(	lHumerus , "lUlna", 
					0.0,0.0,0.0,
					0.0,0.0,60.0,
					1.5);
					*/
	return T;
}

