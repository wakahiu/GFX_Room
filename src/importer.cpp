#include "importer.hpp"

void createPSCM(Bone &root){
	Bone bone1(	root , "bone1", 
				0.0,0.0,0.0,
				0.0,0.0,180.0,
				2.5);
				
		Bone bone2(	bone1 , "bone2", 
					0.0,0.0,0.0,
					0.0,0.0,45.0,
					1.5f);
		
			Bone bone3(	bone2 , "bone3", 
						0.0,0.0,0.0,
						0.0,0.0,-45.0,
						2.5f);
}

void createPerson(Bone &root){
	//Create a root bone.
	//This is a "null" bone that represents a single point and is the 
	//Animation center of the structure

	Bone neck(	root , "neck", 
				0.0,0.0,0.0,
				0.0,0.0,0.0,
				1.0);
		
		Bone head(	neck , "head", 
					0.0,0.0,0.0,
					0.0,0.0,00.0,
					0.5);
							
	Bone back(	root , "back", 
				0.0,0.0,0.0,
				0.0,0.0,180.0,
				2.5);
				
		Bone rPelvis(	back , "rPelvis", 
					0.0,0.0,0.0,
					0.0,0.0,45.0,
					0.8f);
		
			Bone rFemur(	rPelvis , "rFemur", 
						0.0,0.0,0.0,
						0.0,0.0,-45.0,
						2.5f);
			
				Bone rTibia(	rFemur , "rTibia", 
							0.0,0.0,0.0,
							0.0,0.0,00.0,
							2.5f);
						
		Bone lPelvis(	back , "lPelvis", 
					0.0,0.0,0.0,
					0.0,0.0,-45.0,
					0.8);
			
			Bone lFemur(	lPelvis , "lFemur", 
						0.0,0.0,0.0,
						0.0,0.0,45.0,
						2.5f);
						
				Bone lTibia( lFemur , "lTibia", 
						0.0,0.0,0.0,
						0.0,0.0,00.0,
						2.5f);

	Bone rHumerus(	root , "rHumerus", 
				0.0,0.0,0.0,
				0.0,0.0,120.0,
				1.5);
				
		Bone rUlna(	rHumerus  , "rUlna", 
					0.0,0.0,0.0,
					0.0,0.0,-60.0,
					1.5);
				
	Bone lHumerus(	root , "lHumerus", 
				0.0,0.0,0.0,
				0.0,0.0,-120.0,
				1.5);
		
		Bone lUlna(	lHumerus , "lUlna", 
					0.0,0.0,0.0,
					0.0,0.0,60.0,
					1.5);
}

//bool loadMesh(const string fileName);

