#include "common_header.h"
/*
* Defines a vector in R3. Assumes an orthogonal basis for the vectors
*/
#ifndef VECTOR_R3
#define VECTOR_R3
class VectorR3{

private:
	float x;
	float y;
	float z;
	
public:
	VectorR3(float x, float y, float z)
	: x(x), y(y),z(z){}
	
	//Static member function to calculate the cross product of two vectors
	static VectorR3 crossProd(VectorR3 u , VectorR3 v);
	
}

#endif
