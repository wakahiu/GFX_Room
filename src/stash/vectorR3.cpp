#include "vectorR3.hpp"

VectorR3 Vector::crossProd(VectorR3 u, VectorR3 v){

	float xNew =  (u.y * v.z - u.z*v.y);
	float yNew = -(u.x * v.z - u.z*v.x);
	float zNew =  (u.x * v.y - u.x*v.y);
	
	return VectorR3(xNew,yNew,zNew);
}