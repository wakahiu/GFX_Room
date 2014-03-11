/*
* 		pwn2107 HW1. 
 */

#include "common_header.h"
#include "GLScreenCapturer.h"
#include "trackball.h"
#include "display.h"
#include "importer.hpp"
#include "bone.hpp"

//#elif defined(__linux)
#if defined(__APPLE__) || defined(MACOSX)
#   include <GLUT/glut.h>
#else
#   include <GL/glut.h>
#endif


#define BUFFER_LENGTH 64

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
static GLfloat PosY =0.0;
static GLfloat PosZ =-ROOMWIDTH/2;
static GLScreenCapturer screenshot("screenshot-%d.ppm");

Bone arm;

void init(void) 
{

	//Set up lightin Some Lighting.
	float lightY = 10.0;
	const float amb = 1.4;
	const float diff = 1.7;
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
   
   	createPerson(arm);
   	//arm.printHeirarchy(1);
}


void display(void)
{
	
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt( PosX, PosY, PosZ,
				0, 0,  0,
				0.0f, 1.0f,  0.0f);
	
	glPushMatrix();
	arm.draw();
	/*
   //Turn on Texturing
   glEnable(GL_TEXTURE_2D);
   //Specify deCals
   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   
   
   
   //Draw a Rubiks Cube
   glPushMatrix();
   glTranslatef(sphereX,-sphereY,-sphereZ);
   glRotatef(spin,sphereX,-sphereY,-sphereZ);
   displayRubik(3.0,textures);
   glPopMatrix();
   
   //The Room using display lists
   glCallList(theRoom);
   
   	glColor3f(1.0,1.0,0.0);
   	glPushMatrix();
	glTranslatef(-sphereX,-sphereY,-sphereZ);
	glutSolidSphere(3.0,40,20);
	glPopMatrix(); 
	
	glPushMatrix();
	glTranslatef(sphereX,sphereY,-sphereZ);
	glutSolidSphere(3.0,40,20);
	glPopMatrix();
   
   if( captureScreen)
   	screenshot.capture();
   */
   
   glPopMatrix();
	
    glutSwapBuffers();
}

void reshape (int w, int h)
{
	
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);					//Current Matrix specifies projection transform
   	
   glLoadIdentity ();								//Init current projection matrix
   													//Only the matrix specified in the following has effect
   								
   gluPerspective(60.0, (GLfloat)w/GLfloat(h),1.0,120.0);	//Perspective projection
   
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
        
        
        // Render only those needed for selection
        glPushMatrix();    
        {
            //setCamera();
            tbMatrixForSelection();
            
            //drawSelectableTeapots();
        }
        glPopMatrix();
        
        
        // Collect the hits
        hits = glRenderMode(GL_RENDER);
        
        //isTeapot1_selected = false;
        //isTeapot2_selected = false;
        
        // If hit(s) occurred, display the info.
        if(hits != 0)
        {
        
            // Save current picked object.
            // Take only the nearest selection
            //pickedObj = selectBuff[3];
            
            //sprintf (titleString, "You clicked on %d", pickedObj);
            //glutSetWindowTitle(titleString);
            
            /*
            if (pickedObj == 0) {
                isTeapot1_selected = true;
            }
            
            if (pickedObj == 1) {
                isTeapot2_selected = true;
            }*/
            
        }
        else
            glutSetWindowTitle("Nothing was clicked on!");
        
        
        // Restore the projection matrix
        glMatrixMode(GL_PROJECTION);
        
    }
    glPopMatrix();
    
    // Go back to modelview for normal rendering
    glMatrixMode(GL_MODELVIEW);
    
    glutPostRedisplay();
}


void mouse( int button, int state, int x, int y)
{
    //tbMouse(button, state, x, y);
    
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        processSelection(x, y);
    
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        //pickedObj = -1;
        glutPostRedisplay();
    }
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
   		
   	case 'r':
        captureScreen = !captureScreen; 
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

void motion(int x, int y)
{
    tbMotion(x, y);
    
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
    
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
    glutPostRedisplay();

}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowSize (900, 700); 
   glutInitWindowPosition (100, 100);
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
