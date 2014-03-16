#include "common_header.h"
#include "tree.hpp"

#ifndef IK_SOLVER
#define IK_SOLVER

using Eigen::MatrixXd;

class IKsolver{

public:
	IKsolver(Tree * T);
	//Matrix calcJacobian(void);
	//void PseudoInvert(void);
	//void Invert(void);
	
	void solve(void);
private:
	 
	Tree * T;
	MatrixXd J;
	MatrixXd Jinv;
	MatrixXd JpseudoInv;
	
	int rows;
	int cols;
	
	
};
#endif
