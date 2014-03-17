/*
* 		pwn2107 HW1. 
 */

#include "common_header.h"
#include "GLScreenCapturer.h"
#include "trackball.h"
#include "display.h"
#include "importer.hpp"
#include "tree.hpp"
#include "IKsolver.hpp"

//#elif defined(__linux)
#if defined(__APPLE__) || defined(MACOSX)
#   include <GLUT/glut.h>
#else
#   include <GL/glut.h>
#endif


#define BUFFER_LENGTH 256

using namespace std;
GLfloat spin = 0.0;
float sphereX = 0.0;
float sphereY = 0.0;
float sphereZ = 0.0;

GLuint theRoom;
GLuint theRubiks;

GLuint red;
GLuint green;
GLuint blue;
GLuint orange;
GLuint yellow;
GLuint white;

GLuint roomFloor;
GLuint wall;
GLuint ceiling;
GLuint painting1;
GLuint painting2; 
GLuint concrete;
GLuint carpet;
GLuint woodDark;
GLuint window;

GLint viewport[4];
GLdouble modelview[16];
GLdouble projection[16];

static GLuint textures[6];
static GLuint roomTextures[10];
bool captureScreen = false;
static GLfloat PosX =0.0;
static GLfloat PosY = -01.0 ;
static GLfloat PosZ = -ROOMWIDTH*0.99;
static GLScreenCapturer screenshot("screenshot-%d.ppm");
char titleString[150];
Tree * person;
Tree * pscm;      //Planar serial chain manipulator

IKsolver * solverChain;
IKsolver * solverPerson;

#define MAX_JOINT_MODELS 5

int selectedModel = 0;
struct modelSel{
    bool sel;
    Tree * tree;
    IKsolver * solv;
    VectorXd * targets;
};

struct modelSel selectedJointSystem[MAX_JOINT_MODELS];
VectorXd tPerson;
VectorXd tPSCM;

bool IKmode = false;
int  numModels = 0;


void drawSelectableObjects( void )
{
    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR, currentColor);
    
    GLfloat selectedColor[] = {0, 1, 0, 1};
    GLfloat unselectedColor[] = {0, 0,1, 1};

    // Initialize the name stack
    glInitNames();
    glPushName(0);
    
    /* save the current transformation state */
    glPushMatrix();
    {
    
        if( selectedJointSystem[0].sel )
            glMaterialfv(GL_FRONT, GL_DIFFUSE, selectedColor);
        else
            glMaterialfv(GL_FRONT, GL_DIFFUSE, unselectedColor);
        glLoadName(0);
        pscm->draw();

        if( selectedJointSystem[1].sel  )
            glMaterialfv(GL_FRONT, GL_DIFFUSE, selectedColor);
        else
            glMaterialfv(GL_FRONT, GL_DIFFUSE, unselectedColor);
        glLoadName(1);
        person->draw();
    }
    /* restore the previous transformation state*/
    glPopMatrix();
    
    GLfloat blankMaterial[] = {1.0, 1.0, 1.0, 0.0};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blankMaterial);
		
    glColor4fv(currentColor);

}

void init(void) 
{

	//Set up lightin Some Lighting.
	float lightY = 10.0;
	const float amb = 1.4;
	const float diff = 0.7;
    const float LightAmbient[][4]  = {  { amb, amb, amb, 1.0f },
    									{ amb, amb, amb, 1.0f } };
    									
    const float LightDiffuse[][4]  = {  { diff, diff, diff, 1.0f },
                                        { diff, diff, diff, 1.0f } };
                                        
 	const float LightPosition[][4] = {  { 10.0f,  lightY, 10.0f, 0.0f },
                                        { 0.0f, 10.0f, 1.0f, 1.0f } };
	GLfloat mat_spec[] = {1.0,1.0,1.0,1.0};
	GLfloat mat_shin[] = {100.0};
	GLfloat light_pos[] = {10.0,lightY,00.0,1.0};
	
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);					//Shading technique GL_FLAT,GL_SMOOTH
   
   
   glMaterialfv(GL_FRONT, GL_SPECULAR,mat_spec);
   glMaterialfv(GL_FRONT, GL_SHININESS,mat_shin);
   glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
   glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient[0]);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse[0]);
   glLightfv(GL_LIGHT0, GL_POSITION, LightPosition[0]);
   glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
   
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHTING);
	//glEnable(GL_BLEND); //Enable blending.	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.

   	//Import Textures.
   	LoadBMP("textures/red.bmp",red);
   	LoadBMP("textures/green.bmp",green);
   	LoadBMP("textures/blue.bmp",blue);
   	LoadBMP("textures/orange.bmp",orange);
   	LoadBMP("textures/yellow.bmp",yellow);
   	LoadBMP("textures/white.bmp",white);

   	textures[0] = red;
	textures[1] = green;
	textures[2] = blue;
	textures[3] = orange;
	textures[4] = yellow;
	textures[5] = white;
	
	LoadBMP("textures/woodFloor.bmp",roomFloor);
	LoadBMP("textures/interiorWall.bmp",wall);
	LoadBMP("textures/ceiling.bmp",ceiling);
	LoadBMP("textures/painting1.bmp",painting1);
	LoadBMP("textures/painting2.bmp",painting2);
	LoadBMP("textures/concrete.bmp",concrete);
	LoadBMP("textures/carpet.bmp",carpet);
	LoadBMP("textures/woodDark.bmp",woodDark);
	LoadBMP("textures/window.bmp",window);
	roomTextures[0] = roomFloor;
	roomTextures[1] = wall;
	roomTextures[2] = ceiling;
	roomTextures[3] = painting1;
	roomTextures[4] = painting2;
	roomTextures[5] = concrete;
	roomTextures[6] = carpet;
	roomTextures[7] = woodDark;
	roomTextures[8] = window;
	
	//Generate the Roomdisplay list
	theRoom = glGenLists(2);
	glNewList(theRoom, GL_COMPILE);
	displayRoom(roomTextures);
	
	glEndList();
   
   	 tbInit(GLUT_RIGHT_BUTTON);
   	 tbAnimate(GL_TRUE);
   
   if(IKmode){
		sprintf (titleString, "INVERSE KINEMATICS MODE *\n");
	}else{
		sprintf (titleString, "FORWARD KINEMATICS MODE *\n");
	}
    glutSetWindowTitle(titleString);
   glutSetWindowTitle(titleString);
   	/*
   	* Kinematic models
   	*/
   	person = createPerson(-4.0,0.0,0.0);
   	pscm = createPSCM(4.0,-5.0,0.0);
   	
    selectedJointSystem[0].tree = person;
    numModels++;
    selectedJointSystem[1].tree = pscm;
    numModels++;
    
    for(int i = 0; i < numModels &&  i < MAX_JOINT_MODELS ;i++ ){
    	
    	selectedJointSystem[i].sel = (i==0)? true : false;
    }
    
   
   	pscm->printHeirarchy();
   	person->printHeirarchy();
   	/*
   	tPSCM(0) = 0.0;
   	tPSCM(1) = 0.0;
   	tPSCM(2) = 0.0;
   	for(int i = 0; i < 15 ; i++ ){
   		tPerson(i) = 0.1;
   	}*/
   	solverChain =  new IKsolver(pscm);
 	solverPerson =  new IKsolver(person);
 	
 	//Initialize target vectors to the current effector positions
 	tPSCM = solverChain->initTargs();
 	tPerson = solverPerson->initTargs();
 	
 	selectedJointSystem[0].solv = solverPerson;
 	selectedJointSystem[1].solv = solverChain;
 	selectedJointSystem[0].targets = &tPerson;
 	selectedJointSystem[1].targets = &tPSCM;
}


void display(void)
{

	//Update goes here.
		
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt( PosX, PosY, PosZ,
				0, 0,  0,
				0.0f, 1.0f,  0.0f);
	
	glPushMatrix();
	{
	
	   //Turn on Texturing
	   glEnable(GL_TEXTURE_2D);
	   //Specify deCals
	   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	   
	   //The Room using display lists
	   glCallList(theRoom);
	   
	   //Draw A transparent/Invisible plane to help in selectin objects.
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0,0.0,1.0,5.0);
		glBegin(GL_QUADS);
			glVertex3f(-25, 25, 0);
			glVertex3f(-25, -25, 0);
			glVertex3f(25, -25, 0);
			glVertex3f(25, 25, 0);
		glEnd();
		
		//----------------------------------------------------------------------
		
		glDisable(GL_BLEND);
		
		drawSelectableObjects();
	
		if(IKmode){
			selectedJointSystem[selectedModel].solv->solve( *selectedJointSystem[selectedModel].targets);
		}
		
	   // Retrieve current matrice before they get popped.
		glGetDoublev( GL_MODELVIEW_MATRIX, modelview );        // Retrieve The Modelview Matrix
		glGetDoublev( GL_PROJECTION_MATRIX, projection );    // Retrieve The Projection Matrix
		glGetIntegerv( GL_VIEWPORT, viewport );                // Retrieves The Viewport Values (X, Y, Width, Height)
	   
	   /*
	   
	   //Draw a Rubiks Cube
	   glPushMatrix();
	   glTranslatef(sphereX,-sphereY,-sphereZ);
	   glRotatef(spin,sphereX,-sphereY,-sphereZ);
	   displayRubik(3.0,textures);
	   glPopMatrix();
	   
	   
	   	glColor3f(1.0,1.0,0.0);
	   	glPushMatrix();
		glTranslatef(-sphereX,-sphereY,-sphereZ);
		glutSolidSphere(3.0,40,20);
		glPopMatrix(); 
	
		glPushMatrix();
		glTranslatef(sphereX,sphereY,-sphereZ);
		glutSolidSphere(3.0,40,20);
		glPopMatrix();
	   
	   */
	   if( captureScreen)
	   	screenshot.capture();
	   
   
   }glPopMatrix();
	
    glutSwapBuffers();
}

void reshape (int w, int h)
{
	
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);					//Current Matrix specifies projection transform
   	
   glLoadIdentity ();								//Init current projection matrix
   													//Only the matrix specified in the following has effect
   	
   	//gluOrtho2D(-50,50,-50,50);							
   gluPerspective(60.0, (GLfloat)w/GLfloat(h),10.0,100.0);	//Perspective projection
   
   glMatrixMode (GL_MODELVIEW);						//Succeeding transforms now affect the model view matrix 
   						glFlush ();							//Instead of the projection matrix.
   	
   	glLoadIdentity ();
   
}


void processSelection(int xPos, int yPos)
{
    GLfloat fAspect;
    
    // Space for selection buffer
    static GLuint selectBuff[BUFFER_LENGTH];
    
    // Hit counter and viewport storage
    GLint hits, viewport[4];
    
    // Setup selection buffer
    glSelectBuffer(BUFFER_LENGTH, selectBuff);
    
    // Get the viewport
    //x and y coordinates followed by h and w
    glGetIntegerv(GL_VIEWPORT, viewport);
    
    // Switch to projection and save the matrix
    glMatrixMode(GL_PROJECTION);
    
    glPushMatrix();
    {
        // Change render mode
        glRenderMode(GL_SELECT);
        
        // Establish new clipping volume to be unit cube around
        // mouse cursor point (xPos, yPos) and extending two pixels
        // in the vertical and horizontal direction
        glLoadIdentity();
        gluPickMatrix(xPos, viewport[3] - yPos + viewport[1], 0.1,0.1, viewport);
        
        // Apply perspective matrix 
        fAspect = (float)viewport[2] / (float)viewport[3];
        gluPerspective(45.0f, fAspect, 1.0, 425.0);
        
        //Enter selection mode and redraw objects on screen
        // Render only those needed for selection
        glPushMatrix();    
        {
            tbMatrixForSelection();
            drawSelectableObjects();
        }
        glPopMatrix();
        
         for(int i = 0; i < numModels &&  i < MAX_JOINT_MODELS ;i++ ){
			selectedJointSystem[i].sel = (i==0);
		}
    
        // Collect the hits
        hits = glRenderMode(GL_RENDER);
        
        // If hit(s) occurred, display the info.
        if(hits != 0)
        {
        	
        	
            // Save current picked object.
            // Take only the nearest selection
            int pickedObj = selectBuff[3];
            
            //sprintf (titleString, "You clicked on %d", pickedObj);
            //glutSetWindowTitle(titleString);
            
            if (pickedObj == 0) {
              selectedJointSystem[0].sel = true;
              glutSetWindowTitle("Selected obj0!");
            }
            
            if ( pickedObj == 1) {
              selectedJointSystem[1].sel = true;
              glutSetWindowTitle("Selected obj1!");
            }
           
        }
        else{
            glutSetWindowTitle("Nothing was clicked on!");
        }
        
        // Restore the projection matrix
        glMatrixMode(GL_PROJECTION);
    }
    glPopMatrix();
    
    // Go back to modelview for normal rendering
    glMatrixMode(GL_MODELVIEW);
    
    glutPostRedisplay();
}


void keyboard( unsigned char key, int x, int y )
{
    switch(key)
    {
    case 27: // Escape key
        exit(0);
        break;
  	case 'l':
    	if( sphereBouncing )
       		glutIdleFunc(spinDisplay);
       	else
       		glutIdleFunc(NULL);
      	sphereBouncing = !sphereBouncing; 
        break;
        
   	case 'k':
    	if( sphereBouncing )
       		glutIdleFunc(rotatingSphere);
       	else
       		glutIdleFunc(NULL);
      	sphereBouncing = !sphereBouncing; 
        break;
   	
   	 case 'b':
    	if( sphereBouncing )
       		glutIdleFunc(bouncingSphere);
       	else
       		glutIdleFunc(NULL);
      	sphereBouncing = !sphereBouncing; 
        break;
   	
   	case ' ':
   		IKmode = IKmode ? false : true;
   		if(IKmode){
   			sprintf (titleString, "INVERSE KINEMATICS MODE *\n");
   		}else{
   			sprintf (titleString, "FORWARD KINEMATICS MODE *\n");
   			glutIdleFunc(NULL);
   		}
        glutSetWindowTitle(titleString);
   		break;
   		
   	case 'r':
        captureScreen = !captureScreen; 
        break; 
     
	//Selects the model
    case '1':
    case '2':
	    selectedJointSystem[selectedModel].sel = false;
	    selectedModel = key-'1';
	    selectedJointSystem[selectedModel].sel = true;
	    glutPostRedisplay();
        break;
        
    case '+':
    case '=':
    	if( !IKmode ){
        	selectedJointSystem[selectedModel].tree->incrementAngle(3.0);
        	glutPostRedisplay();
        }
        break;
    case '-':
    case '_':
    	if( !IKmode ){
        	selectedJointSystem[selectedModel].tree->incrementAngle(-3.0);
        	glutPostRedisplay();
        }
        break;
       
   	//Motion Goes here.
   	//Forward
   	case 'w':
       	PosZ = ((PosZ- .40) < -ROOMWIDTH) ? PosZ : (PosZ- .40);
       	glutPostRedisplay();
        break;
   	//Down
   	case 's':
   		PosZ = ((PosZ+ .40) > ROOMWIDTH) ? PosZ : (PosZ+ .40);
   		glutPostRedisplay();
   		break;
	
   	//Right
  	case 'd':
   		PosX = ((PosX- .40) < -ROOMLENGTH) ? PosX : (PosX- .40);
   		glutPostRedisplay();
   		break;
   	//Left
   	case 'a':
   		PosX = ((PosX + .40) > ROOMLENGTH) ? PosX : (PosX+ .40);
   		glutPostRedisplay();
   		break;
    }
}

//Called whenever the mouse is clicked.
void mouse( int button, int state, int x, int y)
{
    tbMouse(button, state, x, y);
    
    //Start updating target positions in Inv Kinematics mode
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        if( !IKmode )
        	processSelection(x, y);
    
    //Stop updating target positions in Inv  Kinematics mode
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        glutPostRedisplay();
    }
}

//Called whenever the mouse moves.
void motion(int x, int y)
{
    tbMotion(x, y);
    
    
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
    
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
    
    if(IKmode ){
    	int k;
    	switch(selectedModel){
    		case 0:
    			k = solverPerson->getActiveEffId();
    			break;
    		case 1:
    			k = solverChain->getActiveEffId();
    			break;
    	}  	
    	//cout << "Selected Model " << selectedModel << "x,y" << posX << " " << posY<< endl;
    	(*selectedJointSystem[selectedModel].targets)(3*k+0) = posX;
    	(*selectedJointSystem[selectedModel].targets)(3*k+1) = posY;
    	(*selectedJointSystem[selectedModel].targets)(3*k+2) = 0;
    	
    	cout  << endl << " pos x " << posX << " y " << posY << " z "<< posZ << endl;
    }
    
    glutPostRedisplay();

}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   
   //Initialize the graphics
   glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowSize (900, 700); 
   glutInitWindowPosition (200, 100);
   glutCreateWindow (argv[0]);
   
   assert(!glewInit());
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutMouseFunc( mouse );
   glutKeyboardFunc( keyboard );
   glutMotionFunc( motion );
   glutMainLoop();
   return 0;
}
