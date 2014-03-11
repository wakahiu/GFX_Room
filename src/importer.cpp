#include "importer.hpp"

Bone createPerson(void){
	//Create a root bone.
	//This is a "null" bone that represents a single point and is the 
	//Animation center of the structure

Bone root;
	Bone neck(	root , "neck", 
				0.0,0.0,0.0,
				0.0,0.0,0.0,
				1.5);
		
		Bone head(	neck , "head", 
					0.0,0.0,0.0,
					0.0,0.0,0.0,
					1.5);
					
	Bone back(	root , "back", 
				0.0,0.0,0.0,
				0.0,0.0,180.0,
				2.5);
		Bone rPelvis(	back , "rPelvis", 
					0.0,0.0,0.0,
					0.0,0.0,150.0,
					0.5f);
				
		Bone lPelvis(	back , "lPelvis", 
					0.0,0.0,0.0,
					0.0,0.0,-150.0,
					0.5);

	Bone rHumerus(	root , "rHumerus", 
				0.0,0.0,0.0,
				0.0,0.0,120.0,
				2.0);
				
		Bone rUlna(	rHumerus  , "rUlna", 
					0.0,0.0,0.0,
					0.0,0.0,60.0,
					2.0);
				
	Bone lHumerus(	root , "lHumerus", 
				0.0,0.0,0.0,
				0.0,0.0,-120.0,
				2.0);
		
		Bone lUlna(	lHumerus , "lUlna", 
					0.0,0.0,0.0,
					0.0,0.0,-60.0,
					-2.0);
	root.printHeirarchy();			
	cout << "root size " << root.size() << endl;
	cout << "back size " << back.size() << endl;
	return root;
}

//bool loadMesh(const string fileName);

