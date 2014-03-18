#include "importer.hpp"

Tree * createPSCM( float x, float y, float z ){

	RowVector3d rootPos( (double)x, (double)y , (double)z );
	
	//Create a rooted tree. The root position is assumed to be absolute
	Tree * T = new Tree( rootPos );

	T->addChild( "root", "child1", 
			RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
			RowVector3d(0.0,0.0,1.0),						//Axis of rotation
			-45.0, 3.0,
			JOINT, false, false );
	
	T->addChild( "child1", "child2", 
			RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
			RowVector3d(0.0,0.0,1.0),						//Axis of rotation
			45.0, 3.0,
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
	
	T->addChild( "root", "neck", 
			RowVector3d(0.0,0.7,0.0),						//Offset relative to parent
			RowVector3d(0.0,0.0,1.0),						//Axis of rotation
			0.0, 1.5,
			JOINT, false, false );
			
		T->addChild( "neck", "head", 
				RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
				RowVector3d(0.0,0.0,1.0),						//Axis of rotation
				0.0, 1.5,
				JOINT, false, false );
	
			T->addChild( "head", "headEff", 
					RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
					RowVector3d(0.0,0.0,1.0),						//Axis of rotation
					00.0, 0.0,
					EFFECTOR, false, false );
	
	T->addChild( "root", "back", 
			RowVector3d(0.0,-0.7,0.0),						//Offset relative to parent
			RowVector3d(0.0,0.0,1.0),						//Axis of rotation
			180.0, 3.0,
			JOINT, false, false ); 
			
		T->addChild( "back", "lPelvis", 
				RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
				RowVector3d(0.0,0.0,1.0),						//Axis of rotation
				45.0, 1.50,
				JOINT, false, false ); 
	
			T->addChild( "lPelvis", "lFemur", 
					RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
					RowVector3d(0.0,0.0,1.0),						//Axis of rotation
					-45.0, 4.00,
					JOINT, false, false );
					
				T->addChild( "lFemur", "lTibia", 
						RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
						RowVector3d(0.0,0.0,1.0),						//Axis of rotation
						0.0, 4.00,
						JOINT, false, false );
						
					T->addChild( "lTibia", "lancle", 
							RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
							RowVector3d(0.0,0.0,1.0),						//Axis of rotation
							0.0, 0.00,
							EFFECTOR, false, false );

		T->addChild( "back", "rPelvis", 
				RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
				RowVector3d(0.0,0.0,1.0),						//Axis of rotation
				-45.0, 1.500,
				JOINT, false, false ); 	
	
			T->addChild( "rPelvis", "rFemur", 
					RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
					RowVector3d(0.0,0.0,1.0),						//Axis of rotation
					45.0, 4.00,
					JOINT, false, false );
					
				T->addChild( "rFemur", "rTibia", 
						RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
						RowVector3d(0.0,0.0,1.0),						//Axis of rotation
						0.0, 4.00,
						JOINT, false, false );
						
					T->addChild( "rTibia", "rancle", 
							RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
							RowVector3d(0.0,0.0,1.0),						//Axis of rotation
							0.0, 0.00,
							EFFECTOR, false, false );
							
	T->addChild( "root", "lHumerus", 
				RowVector3d(1.0,0.0,0.0),						//Offset relative to parent
				RowVector3d(0.0,0.0,1.0),						//Axis of rotation
				-135.0, 2.50,
				JOINT, false, false ); 	
	
			T->addChild( "lHumerus", "lUlna", 
					RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
					RowVector3d(0.0,0.0,1.0),						//Axis of rotation
					45.0, 2.5,
					JOINT, false, false );
					
				T->addChild( "lUlna", "lWrist", 
						RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
						RowVector3d(0.0,0.0,1.0),						//Axis of rotation
						0.0, 0.75,
						JOINT, false, false );
						
					T->addChild( "lWrist", "lPalm", 
							RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
							RowVector3d(0.0,0.0,1.0),						//Axis of rotation
							0.0, 0.00,
							EFFECTOR, false, false );
	
	T->addChild( "root", "rHumerus", 
				RowVector3d(-1.0,0.0,0.0),						//Offset relative to parent
				RowVector3d(0.0,0.0,1.0),						//Axis of rotation
				135.0, 2.50,
				JOINT, false, false ); 	
	
			T->addChild( "rHumerus", "rUlna", 
					RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
					RowVector3d(0.0,0.0,1.0),						//Axis of rotation
					-45.0, 2.5,
					JOINT, false, false );
					
				T->addChild( "rUlna", "rWrist", 
						RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
						RowVector3d(0.0,0.0,1.0),						//Axis of rotation
						0.0, 0.75,
						JOINT, false, false );
						
					T->addChild( "rWrist", "rPalm", 
							RowVector3d(0.0,0.0,0.0),						//Offset relative to parent
							RowVector3d(0.0,0.0,1.0),						//Axis of rotation
							0.0, 0.00,
							EFFECTOR, false, false );
																								
	return T;
}

