#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>		//Rand
#include <time.h>
#include <assert.h>
#include <fstream>      // std::ifstream
#include <math.h>
#include <vector>

using namespace std;

#ifndef	COMMON_HEADER
#define COMMON_HEADER
#define printOpenGLError() __printOpenGLError(__FILE__, __LINE__)

static void __printOpenGLError(string file, int line){

  	GLenum glErr = glGetError();
    if (glErr != GL_NO_ERROR)
    {
        cout << "glError in file "<< file<<  " @ line " << line  << " "
        	 <<gluErrorString(glErr) << endl;
        exit(1);
    }
}

#define ROOMHEIGHT	30
#define ROOMWIDTH 	25
#define ROOMLENGTH	35

#define X .525731112119133606 * 5
#define Z .850650808352039932 * 5

#define drawOneLine(x1,y1,z1,x2,y2,z2) 	\
	glBegin( GL_LINES ); 			\
		glVertex3f((x1),(y1),(z1));		\
		glVertex3f((x2),(y2),(z2));		\
	glEnd();
	
#define drawOneLineSmoothShading(x1,y1,z1,R1,G1,B1,x2,y2,z2,R2,G2,B2) 	\
	glBegin( GL_LINES ); 				\
		glColor3f(R1,G1,B1);			\
		glVertex3f((x1),(y1),(z1));		\
		glColor3f(R2,G2,B2);			\
		glVertex3f((x2),(y2),(z2));		\
	glEnd();
	
#endif
