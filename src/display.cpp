#include "display.h"

float dx = 0.3;
float dy = 0.3;
float dz = 0.3;
float R = 3.0;

void spinDisplay(void){

	spin += 1.0;
	spin = spin > 360.0 ? 0 : spin;
	glutPostRedisplay();				//Nudge display function
}

void bouncingSphere(void){
	sphereX += dx;
	dx = ((sphereX < (-ROOMWIDTH+0.9*R)) || (sphereX > (ROOMWIDTH-0.9*R))) ? -dx : dx;
	sphereY += dy;
	dy = ((sphereY < (-ROOMHEIGHT/2+0.9*R)) || (sphereY > (ROOMHEIGHT/2-0.9*R))) ? -dy : dy;
	sphereZ += dz;
	dz = ((sphereZ < (-ROOMLENGTH+0.9*R)) || (sphereZ > (ROOMLENGTH-0.9*R))) ? -dx : dx;
	glutPostRedisplay();				//Nudge display function
}

void rotatingSphere(void){
	spinDisplay();
	float r = 0.9;
	
	sphereX = r*ROOMWIDTH*cos( 2*spin* M_PI/180.0 );
	sphereY = r*r*ROOMHEIGHT*0.5*sin( spin* M_PI/180.0 )*sin( spin* M_PI/180.0 );
	sphereZ = r*ROOMLENGTH*sin( spin* M_PI/180.0 );
}

//Source 

 
struct BITMAPINFOHEADER {
	short Reserved1;
	short hSize;
	short Reserved2;
	short biWidth;
	short Reserved3;
	short biHeight;
	short Reserved4;
	short colorPlanes;
	short bitsPerPixel;
	short compresionMethod;
	/*short Reserved5;
	short Reserved6;
	short Reserved7;
	short Reserved8;
	short Reserved9;
	short Reserved10;
	int Reserved11;
	int Reserved12;
	short Reserved13; */
	short biSize;
	
};

struct BITMAPFILEHEADER {
  short bfType;
  int bfSize;
  short Reserved1;
  short bfOffBits;
};

// http://www.cplusplus.com/articles/GwvU7k9E/
int LoadBMP(const char* location, GLuint &texture){
	
	char* datBuff[2] = {NULL, NULL}; // Header buffers
	char* pixels = NULL; // Pixels

	struct BITMAPFILEHEADER* bmpHeader = NULL; // Header
	struct BITMAPINFOHEADER* bmpInfo   = NULL; // Info 
	
	// The file... We open it with it's constructor
	std::ifstream file(location, std::ios::binary);
	if(!file)
	{
		std::cout << "Failure to open bitmap file.\n";

		return 1;
	}
	
	// Allocate byte memory that will hold the two headers
	datBuff[0] = new char[sizeof(BITMAPFILEHEADER)];
	datBuff[1] = new char[sizeof(BITMAPINFOHEADER)];

	file.read((char*)datBuff[0], sizeof(BITMAPFILEHEADER));
	file.read((char*)datBuff[1], sizeof(BITMAPINFOHEADER));
	
	//cout << "sizeof Short " << sizeof(int) << endl;
	// Construct the values from the buffers
	bmpHeader = (BITMAPFILEHEADER*) datBuff[0];
	bmpInfo   = (BITMAPINFOHEADER*) datBuff[1];
	//cout << "File size " << bmpHeader->bfSize << " offSet " << bmpHeader->bfOffBits << endl;
	
	// Check if the file is an actual BMP file
	if(bmpHeader->bfType != 0x4D42)
	{
		std::cout << "File \"" << location << "\" isn't a bitmap file\n";
		return 2;
	}
	
	// Set width and height to the values loaded from the file
	GLuint w = bmpInfo->biWidth;
	GLuint h = bmpInfo->biHeight;
	
	// First allocate pixel memory
	unsigned long sz = w*h*3;
	pixels = new char[sz];
	cout << "Image Dim WxH " << w << " x " << h << " Size " << sz << endl;
	
	/*
	cout << "Reserve1 " << bmpInfo->Reserved1  << endl;
	cout << "Info Header Size " << bmpInfo->hSize  << endl;
	cout << "Reserve2 " << bmpInfo->Reserved2  << endl;
	cout << "Reserve3 " << bmpInfo->Reserved3  << endl;
	cout << "Reserve4 " << bmpInfo->Reserved4  << endl;
	cout << "Color Planes " << bmpInfo->colorPlanes << endl;
	cout << "bitsPerPixel " << bmpInfo->bitsPerPixel  << endl;
	cout << "compresionMethod " <bmpInfo->compresionMethod  << endl;
	cout << "Reserve5 " << bmpInfo->Reserved5  << endl;
	cout << "Reserve6 " << bmpInfo->Reserved6  << endl;
	cout << "Reserve7 " << bmpInfo->Reserved7  << endl;
	cout << "Reserve8 " << bmpInfo->Reserved8  << endl;
	cout << "Reserve9 " << bmpInfo->Reserved9  << endl;
	cout << "Reserve10 " << bmpInfo->Reserved10  << endl;
	cout << "Reserve11 " << bmpInfo->Reserved11  << endl;
	cout << "Reserve12 " << bmpInfo->Reserved12  << endl;
	cout << "Reserve13 " << bmpInfo->Reserved13  << endl;
	cout << "Size " << bmpInfo->biSize << endl;*/


	// Go to where image data starts, then read in image data
	file.seekg(bmpHeader->bfOffBits);
	file.read((char*)pixels, sz);
	
	// We're almost done. We have our image loaded, however it's not in the right format.
	// .bmp files store image data in the BGR format, and we have to convert it to RGB.
	// Since we have the value in bytes, this shouldn't be to hard to accomplish
	char tmpRGB = 0; // Swap buffer

	for (unsigned long i = 0; i < sz; i += 3)
	{
		tmpRGB        = pixels[i];
		pixels[i]     = pixels[i + 2];
		pixels[i + 2] = tmpRGB;
		
	}

	
	/*******************GENERATING TEXTURES*******************/

	glGenTextures(1, &texture);             // Generate a texture
	glBindTexture(GL_TEXTURE_2D, texture); // Bind that texture temporarily

	GLint mode = GL_RGB;                   // Set the mode

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	//Boarder behaviour
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
   
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	 
	// Create the texture. We get the offsets from the image, then we use it with the image's
	// pixel data to create it.
	glTexImage2D(GL_TEXTURE_2D, 0, mode, w, h, 0, mode, GL_UNSIGNED_BYTE, pixels);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// Output a successful message
	std::cout << "Texture \"" << location << "\" successfully loaded.\n";

	// Delete the two buffers.
	delete[] datBuff[0];
	delete[] datBuff[1];
	delete[] pixels;

	return 0; // Return success code
}
	
static GLfloat vdata[12][3] = {    
   {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},    
   {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},    
   {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} };
static GLuint tindices[20][3] = { 
   {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
   {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
   {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
   {6,1,10}, {9,0,11}, {9
   ,11,2}, {9,2,5}, {7,2,11} };
   
void displayIcosahedron(){
	glPushMatrix();
	
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glBegin( GL_TRIANGLES );
		for( int i = 0; i < 20 ; i++){
			glVertex3fv(&vdata[tindices[i][0]][0]);
			glVertex3fv(&vdata[tindices[i][1]][0]);
			glVertex3fv(&vdata[tindices[i][2]][0]);
		}
	glEnd();
	
	glPopMatrix();
}


// Gotten from
//http://www.glprogramming.com/red/chapter07.html
//Display List tutorial
/* Draw a torus */
void torus(int numc, int numt){
   int i, j, k;
   float m = 3.0;
   double s, t, x, y, z, twopi;

   twopi = 2 * (double)M_PI;
   for (i = 0; i < numc; i++) {
      glBegin(GL_QUAD_STRIP);
      for (j = 0; j <= numt; j++) {
         for (k = 1; k >= 0; k--) {
            s = (i + k) % numc + 0.5;
            t = j % numt;

            x = (1+.1*cos(s*twopi/numc))*cos(t*twopi/numt)*m;
            y = (1+.1*cos(s*twopi/numc))*sin(t*twopi/numt)*m;
            z = .1 * sin(s * twopi / numc)*m;
            glNormal3f(1.0,0.0,0.0);
            glVertex3f(x, y, z);
         }
      }
      glEnd();
   }
}

void displayPlanets(void){
	glPushMatrix();
	glRotatef(spin*2,0.0,1.0,0.0);
   drawOneLineSmoothShading( 0.0,-2.0,0.0,
   							 1.0,1.0,0.0,
   							 0.0,2.0,0.0,
   							 1.0,0.0,1.0);
   
   glColor3f(1.0,1.0,1.0);
   
   
   glColor3f(0.0,1.0,1.0);
   glRotatef(spin*2,0.0,1.0,0.0);
   glutSolidSphere(1.0,30,24);						//Draw Sun
   
   glPushMatrix();
   
   glColor3f(0.7,0.3,0.0);
   //glRotatef(year,0.0,1.0,0.0);						
   glTranslatef(2.1,0.0,0.0);
   //glRotatef(day,0.0,1.0,0.0);						//Spin Earth 
   glutSolidSphere(0.4,15,12);

   glColor3f(0.2,0.5,1.0);
   glTranslatef(0.0, 0.0,0.5); 						//Moon
   glutSolidSphere(0.1,10,8);
   
   glPopMatrix();
   glColor3f(0.9,0.0,0.6);
   //glRotatef(year*2,0.0,1.0,0.0);						
   glTranslatef(3.0,0.0,0.0);
   //glRotatef(day,0.0,1.0,0.0);						//Spin Mars 
   glutSolidSphere(0.3,12,10);
   
   glColor3f(0.0,0.5,0.0);
   glTranslatef(0.0, 0.0,0.5); 						//Martian Moon
   glutSolidSphere(0.1,10,8);
	glPopMatrix();
}

void displaySquare(void){

	glPushMatrix();
	
	unsigned int vaoID[1]; // Our Vertex Array Object
	unsigned int vboID[1]; // Our Vertex Buffer Object

	glColor3f(0.7,0.3,1.0);
	float* vertices = new float[18];	// Vertices for our square

	vertices[0] = -10.5; vertices[1] = -10.5; vertices[2] = 0.0; // Bottom left corner
	vertices[3] = -10.5; vertices[4] = 10.5; vertices[5] = 0.0; // Top left corner
	vertices[6] = 10.5; vertices[7] = 10.5; vertices[8] = 0.0; // Top Right corner

	vertices[9] = 10.5; vertices[10] = -10.5; vertices[11] = 0.0; // Bottom right corner
	vertices[12] = -10.5; vertices[13] = -10.5; vertices[14] = 0.0; // Bottom left corner
	vertices[15] = 10.5; vertices[16] = 10.5; vertices[17] = 0.0; // Top Right corner

	glGenVertexArrays(1, &vaoID[0]); // Create our Vertex Array Object

	glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object so we can use it
	
	glGenBuffers(1, vboID); // Generate our Vertex Buffer Object
	
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); // Bind our Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
	
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	glEnableVertexAttribArray(0); // Enable our Vertex Array Object index 0
	glBindVertexArray(0); // Disable our Vertex Buffer Object
	
	glBindVertexArray(vaoID[0]);
	glColor3f(0.7,0.3,1.0);
	glDrawArrays(GL_TRIANGLES, 0, 2332218);
	glBindVertexArray(0); // Disable our Vertex Buffer Object
	delete [] vertices; // Delete our vertices from memory
	
	glFlush();
	glPopMatrix();
}
void makeCheckImage(void)
{
   int i, j, c;
    
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         //c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         if((i>(checkImageHeight/2)) || (j>(checkImageWidth/2)) )
         	c = 100; 
         checkImage[i][j][0] = (GLubyte) 100;
         checkImage[i][j][1] = (GLubyte) c;
         checkImage[i][j][2] = (GLubyte) c;
         checkImage[i][j][3] = (GLubyte) 100;
      }
   }
}
void displayPanel(float x, float y, GLuint text){
	x/=2; y/=2;
	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_QUADS);
	   glTexCoord2f(0.0, 0.0); glVertex3f(-x, -y, 0.0);
	   glTexCoord2f(0.0, y); glVertex3f(-x, y, 0.0);
	   glTexCoord2f(x, y); glVertex3f(x, y, 0.0);
	   glTexCoord2f(x, 0.0); glVertex3f(x, -y, 0.0);
   glEnd();
}

void displayRoom( GLuint * texture){
	
	GLuint roomFloor = texture[0];
	GLuint wall = texture[1];
	GLuint ceiling = texture[2];
	GLuint painting1 = texture[3];
	GLuint painting2 = texture[4];
	GLuint concrete = texture[5];
	GLuint carpet = texture[6];
	GLuint woodDark = texture[7];
	GLuint book = texture[8];
	
	float x, y, z;
	x =  ROOMWIDTH;
	z =  ROOMLENGTH;
	y = -ROOMHEIGHT/2.0;
	float s=2.0;	
	//The roomFloor
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, roomFloor);
	glBegin(GL_QUADS);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(0.0, 0.0);		glVertex3f(-x, y, -z);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(0.0, y/8); 	glVertex3f(-x, y, z+ROOMWIDTH);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(x/8, y/8); 	glVertex3f(x, y, z+ROOMWIDTH);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(x/8, 0.0); 	glVertex3f(x, y, -z);
   	glEnd();
   	//Walls
   	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	   glNormal3f(-1.0,0.0,0.0);	glTexCoord2f(0.0, 0.0);	glVertex3f(x, -y, -z);
	   glNormal3f(-1.0,0.0,0.0);	glTexCoord2f(x/8, 0); 	glVertex3f(x, -y, z+ROOMWIDTH);
	   glNormal3f(-1.0,0.0,0.0);	glTexCoord2f(x/8, y/8); 	glVertex3f(x, y, z+ROOMWIDTH);
	   glNormal3f(-1.0,0.0,0.0);	glTexCoord2f(0, y/8); 	glVertex3f(x, y, -z);
   	glEnd();
   	
   	
   	glBegin(GL_QUADS);
	   glNormal3f(1.0,0.0,0.0);	glTexCoord2f(0.0, 0.0);	glVertex3f(-x, -y, -z);
	   glNormal3f(1.0,0.0,0.0);	glTexCoord2f(x/8, 0.0); 	glVertex3f(-x, -y, z);
	   glNormal3f(1.0,0.0,0.0);	glTexCoord2f(x/8, y/8); 	glVertex3f(-x, y, z);
	   glNormal3f(1.0,0.0,0.0);	glTexCoord2f(0.0, y/8); 	glVertex3f(-x, y, -z);
   	glEnd();
   	
   	glBegin(GL_QUADS);
	   glNormal3f(0.0,0.0,1.0);	glTexCoord2f(0.0, 0.0);	glVertex3f(-x, -y, -z);
	   glNormal3f(0.0,0.0,1.0);	glTexCoord2f(0.0, y/8); 	glVertex3f(-x, y, -z);
	   glNormal3f(0.0,0.0,1.0);	glTexCoord2f(x/8, y/8); 	glVertex3f(x, y, -z);
	   glNormal3f(0.0,0.0,1.0);	glTexCoord2f(x/8, 0.0); 	glVertex3f(x, -y, -z);
   	glEnd();
   	
   	//--------------------------------------------------------------------------
   	/*
   	*	Special Wall
   	*/
   	
   	s=0.35;
   	float xs, ys, zs;
   	xs=  x*s;
   	ys=  y;
   	zs=  z;
   	
   	glPushMatrix();
   	glTranslatef(ROOMWIDTH/1.5,0.0,0.0);
   	glBegin(GL_QUADS);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(0.0, 0.0);	glVertex3f(-xs, -ys, zs);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(0.0, ys/8); 	glVertex3f(-xs, ys, zs);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(xs/8, ys/8); 	glVertex3f(xs, ys, zs);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(xs/8, 0.0); 	glVertex3f(xs, -ys, zs);
   	glEnd();
   	glPopMatrix();
   	
   	glPushMatrix();
   	glTranslatef(-ROOMWIDTH/1.5,0.0,0.0);
   	glBegin(GL_QUADS);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(0.0, 0.0);	glVertex3f(-xs, -ys, zs);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(0.0, ys/8); 	glVertex3f(-xs, ys, zs);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(xs/8, ys/8); 	glVertex3f(xs, ys, zs);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(xs/8, 0.0); 	glVertex3f(xs, -ys, zs);
   	glEnd();
   	
   glPopMatrix();
   	s=0.35;
   	xs=  x;
   	ys=  y*s;
   	glPushMatrix();
   	glTranslatef(0.0,ROOMHEIGHT/2.0,0.0);
   	glBegin(GL_QUADS);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(0.0, 0.0);	glVertex3f(-xs, -ys, zs);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(0.0, ys/8); 	glVertex3f(-xs, ys, zs);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(xs/8, ys/8); 	glVertex3f(xs, ys, zs);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(xs/8, 0.0); 	glVertex3f(xs, -ys, zs);
   	glEnd();
   	glPopMatrix();
   	
   	

   	zs = z + ROOMWIDTH;
   	glBegin(GL_QUADS);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(0.0, 0.0);	glVertex3f(-x, -y, zs);
	   glNormal3f(0.0,0.0, 1.0);	glTexCoord2f(0.0, y/8); 	glVertex3f(-x, y, zs);
	   glNormal3f(0.0,0.0, 1.0);	glTexCoord2f(x/8, y/8); 	glVertex3f(x, y, zs);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(x/8, 0.0); 	glVertex3f(x, -y, zs);
   	glEnd();
   	
   	s=24;
   	//Door Frame
   	glPushMatrix();
   	glTranslatef(ROOMWIDTH/3,-ROOMHEIGHT/8,ROOMLENGTH);
   	displayBrick(ROOMLENGTH/s,ROOMHEIGHT/2.5,ROOMWIDTH/s,woodDark);
   	glPopMatrix();
   	
   	glPushMatrix();
   	glTranslatef(-ROOMWIDTH/3,-ROOMHEIGHT/8,ROOMLENGTH);
   	displayBrick(ROOMLENGTH/s,ROOMHEIGHT/2.5,ROOMWIDTH/s,woodDark);
   	glPopMatrix();
   	
   	glPushMatrix();
   	glTranslatef(0,ROOMHEIGHT/3,ROOMLENGTH);
   	glRotatef(90,0.0,0.0,1.0);
   	displayBrick(ROOMLENGTH/s,ROOMHEIGHT/2.7,ROOMWIDTH/s,woodDark);
   	glPopMatrix();
   	
   	
   	
   	//--------------------------------------------------------------------------
   	y = ROOMHEIGHT/2.0;
   	//The Ceiling
   	s=1.5;
	glBindTexture(GL_TEXTURE_2D, ceiling);
	glBegin(GL_QUADS);
	   glNormal3f(0.0,-1.0,0.0);	glTexCoord2f(0.0, 0.0);		glVertex3f(-x, y, -z);
	   glNormal3f(0.0,-1.0,0.0);	glTexCoord2f(0.0, y/s); 	glVertex3f(-x, y, z+ROOMWIDTH);
	   glNormal3f(0.0,-1.0,0.0);	glTexCoord2f(x/s, y/s); 	glVertex3f(x, y, z+ROOMWIDTH);
	   glNormal3f(0.0,-1.0,0.0);	glTexCoord2f(x/s, 0.0); 	glVertex3f(x, y, -z);
   	glEnd();
   	s=2.25;
   	
   	//Painting
   	glBindTexture(GL_TEXTURE_2D, painting2);
   	
	glBegin(GL_QUADS);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(0.0, 0.0);		glVertex3f(-x/s, -y/s, -z+0.01);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(0.0, 1.0); 	glVertex3f(-x/s, y/s, -z+0.01);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(1.0, 1.0); 	glVertex3f(x/s, y/s, -z+0.01);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(1.0, 0.0); 	glVertex3f(x/s, -y/s, -z+0.01);
   	glEnd();
   	
   	glBindTexture(GL_TEXTURE_2D, woodDark);
   	s=2.15;
	glBegin(GL_QUADS);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(0.0, 0.0);		glVertex3f(-x/s, -y/s, -z+0.005);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(0.0, 1.0); 	glVertex3f(-x/s, y/s, -z+0.005);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(1.0, 1.0); 	glVertex3f(x/s, y/s, -z+0.005);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(1.0, 0.0); 	glVertex3f(x/s, -y/s, -z+0.005);
   	glEnd();
   	
   	int ROOMHEIGHT_2 = ROOMHEIGHT/2;
   	//Collumns
   	glPushMatrix();
   	glTranslatef(-ROOMWIDTH,0.0,-ROOMLENGTH);
   	displayBrick(ROOMLENGTH/8,ROOMHEIGHT/2,ROOMWIDTH/8,concrete);
   	glPopMatrix();
   	
   	glPushMatrix();
   	glTranslatef(-ROOMWIDTH,0.0,ROOMLENGTH);
   	displayBrick(ROOMLENGTH/8,ROOMHEIGHT/2,ROOMWIDTH/8,concrete);
   	glPopMatrix();
   	
   	glPushMatrix();
   	glTranslatef(ROOMWIDTH,0.0,-ROOMLENGTH);
   	displayBrick(ROOMLENGTH/8,ROOMHEIGHT/2,ROOMWIDTH/8,concrete);
   	glPopMatrix();
   	
   	glPushMatrix();
   	glTranslatef(ROOMWIDTH,0.0,ROOMLENGTH);
   	displayBrick(ROOMLENGTH/8,ROOMHEIGHT/2,ROOMWIDTH/8,concrete);
   	glPopMatrix();
   

   	y = -ROOMHEIGHT/2.0;
   	float cR = 0.8;
   	x*=cR;
   	z*=cR;
   	
   	s = 2.5;
   	//Carpet
   	glBindTexture(GL_TEXTURE_2D, carpet);
	glBegin(GL_QUADS);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(0.0, 0.0);		glVertex3f(-x, y+0.01, -z);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(0.0, y/s); 	glVertex3f(-x, y+0.01, z);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(x/s, y/s); 	glVertex3f(x, y+0.01, z);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(x/s, 0.0); 	glVertex3f(x, y+0.01, -z);
   	glEnd();
   
   	//displayBookShelf(5.0, ROOMHEIGHT*3/2, 3.0, &texture[7]);
   	
   	glBindTexture(GL_TEXTURE_2D, wall);
   	glPopMatrix();
}

#define NumOBJ 1
void displayBookShelf(float d, float h, float w, GLuint *textures){
	GLuint wood = textures[0];
	GLuint books = textures[1];
	float d2 = d/2;
	float h2 = h/2;
	float w2 = w/2;
	
	//glBindTexture(GL_TEXTURE_2D, wood);
	float vdata[12][3] = {	
	{-w2, -h2,-d2}, {-w2, -h2, d2}, {-w2, h2,-d2}, {-w2, h2,d2},
	{w2, -h2,-d2}, {w2, -h2, d2}, {w2, h2,-d2}, {w2, h2,d2} };
	
	int vindices[5][4] = { 	
	{0,1,3,2}, {4,5,7,6}, {0,1,5,4}, {2,3,7,6},{0,4,6,2}  };
	
	/*
	int normals[][] ={
	*/
	float s = 1.0;
	

	glBegin(GL_QUADS);{  
		for (int i = 0; i < NumOBJ; i++) {    
		   /* color information here */ 
		   glVertex3fv(&vdata[vindices[i][0]][0]); 
		   glVertex3fv(&vdata[vindices[i][1]][0]); 
		   glVertex3fv(&vdata[vindices[i][2]][0]); 
		   glVertex3fv(&vdata[vindices[i][3]][0]);
		}
	}glEnd();


}

void displayRubik(float l, GLuint * texture){
	GLuint red = texture[0];
	GLuint green = texture[1];
	GLuint blue = texture[2];
	GLuint orange = texture[3];
	GLuint yellow = texture[4];
	GLuint white = texture[5];

	glPushMatrix();
	float x, y, z;
	x = y = z = l;
	glRotatef(spin,0.0,1.0,0.0);
	glBindTexture(GL_TEXTURE_2D, red);
	glBegin(GL_QUADS);
	   glNormal3f(0.0,0.0,1.0);	glTexCoord2f(0.0, 0.0);	glVertex3f(-x, -y, z);
	   glNormal3f(0.0,0.0,1.0);	glTexCoord2f(0.0, y); glVertex3f(-x, y, z);
	   glNormal3f(0.0,0.0,1.0);	glTexCoord2f(x, y); glVertex3f(x, y, z);
	   glNormal3f(0.0,0.0,1.0);	glTexCoord2f(x, 0.0); glVertex3f(x, -y, z);
   glEnd();
   glBindTexture(GL_TEXTURE_2D, orange);
	glBegin(GL_QUADS);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(0.0, 0.0); glVertex3f(-x, -y, -z);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(0.0, y); glVertex3f(-x, y, -z);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(x, y); glVertex3f(x, y, -z);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(x, 0.0); glVertex3f(x, -y, -z);
   glEnd();
   
   glBindTexture(GL_TEXTURE_2D, blue);
	glBegin(GL_QUADS);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(0.0, 0.0); glVertex3f(-x, y, -z);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(0.0, y); glVertex3f(-x, y, z);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(x, y); glVertex3f(x, y, z);
	   glNormal3f(0.0,1.0,0.0);	glTexCoord2f(x, 0.0); glVertex3f(x, y, -z);
   glEnd();
   
   glBindTexture(GL_TEXTURE_2D, green);
	glBegin(GL_QUADS);
	   glNormal3f(0.0,-1.0,0.0);	glTexCoord2f(0.0, 0.0); glVertex3f(-x, -y, -z);
	   glNormal3f(0.0,-1.0,0.0);	glTexCoord2f(0.0, y); glVertex3f(-x, -y, z);
	   glNormal3f(0.0,-1.0,0.0);	glTexCoord2f(x, y); glVertex3f(x, -y, z);
	   glNormal3f(0.0,-1.0,0.0);	glTexCoord2f(x, 0.0); glVertex3f(x, -y, -z);
   glEnd();	
   
   glBindTexture(GL_TEXTURE_2D, white);
	glBegin(GL_QUADS);
	   glNormal3f(1.0,0.0,0.0);	glTexCoord2f(0.0, 0.0); glVertex3f(x, -y, -z);
	   glNormal3f(1.0,0.0,0.0);	glTexCoord2f(0.0, y); glVertex3f(x, -y, z);
	   glNormal3f(1.0,0.0,0.0);	glTexCoord2f(x, y); glVertex3f(x, y, z);
	   glNormal3f(1.0,0.0,0.0);	glTexCoord2f(x, 0.0); glVertex3f(x, y, -z);
   glEnd();
   
   glBindTexture(GL_TEXTURE_2D, yellow);
	glBegin(GL_QUADS);
	   glNormal3f(-1.0,0.0,0.0);	glTexCoord2f(0.0, 0.0); glVertex3f(-x, -y, -z);
	   glNormal3f(-1.0,0.0,0.0);	glTexCoord2f(0.0, y); glVertex3f(-x, -y, z);
	   glNormal3f(-1.0,0.0,0.0);	glTexCoord2f(x, y); glVertex3f(-x, y, z);
	   glNormal3f(-1.0,0.0,0.0);	glTexCoord2f(x, 0.0); glVertex3f(-x, y, -z);
   glEnd();	
   
   glPopMatrix();
}


void displayCabin(float w, float h, float l, GLuint * texture){
	GLuint Side = texture[0];
	GLuint Roof = texture[1];
	float bodyToRoofRatio=0.6;
	float hr = h*(1.0-bodyToRoofRatio);
	float hb = h*bodyToRoofRatio;
	
  	displayBrick(w, hb , l , Side);
   	glTranslatef(0.0,hb/2,0.0);
   	displayRoof(l,hr,w, Roof);
}

void displayRoof(float b, float h, float w,GLuint text){
	
	b/=2; w/=2;
	glBindTexture(GL_TEXTURE_2D, text);
   	
	glBegin(GL_QUADS);
		
	   glTexCoord2f(0.0, 0.0); glVertex3f(-w, 0.0, b);
	   glTexCoord2f(0.0, w); glVertex3f(w, 0.0, b);
	   glTexCoord2f(h, w); glVertex3f(w, h, 0.0);
	   glTexCoord2f(h, 0.0); glVertex3f(-w, h, 0.0);
   	glEnd();
   	
	glBegin(GL_QUADS);	
	   glTexCoord2f(0.0, 0.0); glVertex3f(-w, 0.0, -b);
	   glTexCoord2f(0.0, w); glVertex3f(w, 0.0, -b);
	   glTexCoord2f(h, w); glVertex3f(w, h, 0.0);
	   glTexCoord2f(h, 0.0); glVertex3f(-w, h, 0.0);
	glEnd();
   
}

void displayBrick(float x, float y, float z , GLuint text){
	
	x; y; z;
	float s = 5.0;
	glBindTexture(GL_TEXTURE_2D, text);
   
   	glBegin(GL_QUADS);
	   glNormal3f(0.0,0.0,1.0);	glTexCoord2f(0.0, 0.0);	glVertex3f(-x, -y, z);
	   glNormal3f(0.0,0.0,1.0);	glTexCoord2f(0.0, y/s); glVertex3f(-x, y, z);
	   glNormal3f(0.0,0.0,1.0);	glTexCoord2f(x/s, y/s); glVertex3f(x, y, z);
	   glNormal3f(0.0,0.0,1.0);	glTexCoord2f(x/s, 0.0); glVertex3f(x, -y, z);
   glEnd();

	glBegin(GL_QUADS);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(0.0, 0.0); glVertex3f(-x, -y, -z);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(0.0, y/s); glVertex3f(-x, y, -z);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(x/s, y/s); glVertex3f(x, y, -z);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(x/s, 0.0); glVertex3f(x, -y, -z);
   glEnd();
   
   	glPushMatrix();
   	glScalef(1.0,1.0,-1.0);
   	glRotatef(90.0,0.0,1.0,0.0);
   	float temp;
   	temp = x;
   	x = z;
   	z = temp;
   	glBegin(GL_QUADS);
	   glNormal3f(0.0,0.0,1.0);	glTexCoord2f(0.0, 0.0);	glVertex3f(-x, -y, z);
	   glNormal3f(0.0,0.0,1.0);	glTexCoord2f(0.0, y/s); glVertex3f(-x, y, z);
	   glNormal3f(0.0,0.0,1.0);	glTexCoord2f(x/s, y/s); glVertex3f(x, y, z);
	   glNormal3f(0.0,0.0,1.0);	glTexCoord2f(x/s, 0.0); glVertex3f(x, -y, z);
   glEnd();

	glBegin(GL_QUADS);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(0.0, 0.0); glVertex3f(-x, -y, -z);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(0.0, y/s); glVertex3f(-x, y, -z);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(x/s, y/s); glVertex3f(x, y, -z);
	   glNormal3f(0.0,0.0,-1.0);	glTexCoord2f(x/s, 0.0); glVertex3f(x, -y, -z);
   glEnd();
   glPopMatrix();
   
}

void displayTile(void){
	//glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );		//GL_FILL Or GL_LINE
	
	glPushMatrix();
   glBegin(GL_QUADS);
	   glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0.0);
	   glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 0.0);
	   glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
	   glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 0.0);

   glEnd();
   glPopMatrix();
}

void displayCube(void){
	glPushMatrix();
	glLoadIdentity();
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );		//GL_FILL Or GL_LINE
	//glRotatef(year,0.0,1.0,0.0);
	glBegin( GL_QUADS );
		//
		glVertex3f(-5.0, -5.00, -5.0);
		glVertex3f(-5.0, 5.00, -5.0);
		glVertex3f(5.0, 5.00, -5.0);
		glVertex3f(5.0, -5.00, -5.0);
	glEnd();
	
	glBegin( GL_QUADS );
		//
		glVertex3f(-5.0, -5.00, 5.0);
		glVertex3f(-5.0, 5.00, 5.0);
		glVertex3f(5.0, 5.00, 5.0);
		glVertex3f(5.0, -5.00, 5.0);
	glEnd();
	
	glBegin( GL_QUADS );
		//
		glVertex3f(-5.0, -5.00, -5.0);
		glVertex3f(-5.0, -5.00, 5.0);
		glVertex3f(5.0, -5.00, 5.0);
		glVertex3f(5.0, -5.00, -5.0);
	glEnd();
	
	glBegin( GL_QUADS );
		//
		glVertex3f(-5.0, 5.00, -5.0);
		glVertex3f(-5.0, 5.00, 5.0);
		glVertex3f(5.0, 5.00, 5.0);
		glVertex3f(5.0, 5.00, -5.0);
	glEnd();
	
	glBegin( GL_QUADS );
		//
		glVertex3f(-5.0, 5.00, -5.0);
		glVertex3f(-5.0, 5.00, 5.0);
		glVertex3f(-5.0, -5.00, 5.0);
		glVertex3f(-5.0, -5.00, -5.0);
	glEnd();
	
	glBegin( GL_QUADS );
		//
		glVertex3f(5.0, 5.00, -5.0);
		glVertex3f(5.0, 5.00, 5.0);
		glVertex3f(5.0, -5.00, 5.0);
		glVertex3f(5.0, -5.00, -5.0);
	glEnd();
	 
	glPopMatrix();
}
