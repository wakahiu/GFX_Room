#include "common_header.h"

//-----------------------------------------------------------------
// Print for OpenGL errors
//
// Returns 1 if an OpenGL error occurred, 0 otherwise.
//

/*  Create checkerboard texture  */
#define checkImageWidth 64
#define checkImageHeight 64


static bool sphereBouncing = false;

extern GLfloat spin;
extern GLuint theRoom;
extern GLuint theRubiks;
extern float sphereX, sphereY, sphereZ;

extern float dx, dy, dz;

static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

void displayIcosahedron(void);
void displayPlanets(void);
void displayCube(void);
void spinDisplay(void);
void bouncingSphere(void);
void rotatingSphere(void);
void displaySquare(void);
void torus(int numc, int numt);
void makeCheckImage(void);
void displayTile(void);
void displayRoom( GLuint * texture);
void displayBrick(float x, float y, float z , GLuint text);
void displayPanel(float x, float y, GLuint text);
void displayRoof(float b, float h, float w, GLuint text);
int  LoadBMP(const char* location, GLuint &texture);
void displayCabin(float w, float h, float l, GLuint * texture);
void displayRubik(float l, GLuint * texture);
void displayBookShelf(float d, float w, float h, GLuint *textures);
