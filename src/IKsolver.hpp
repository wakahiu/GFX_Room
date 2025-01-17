#include "common_header.h"
#include "tree.hpp"

#ifndef IK_SOLVER
#define IK_SOLVER

using Eigen::MatrixXd;

class IKsolver{

public:
	IKsolver(Tree * T);
	
	void updateJacobian(void);
	void solve( VectorXd target );
	void updateJacobianPinvDLS(void);
	void IKupdateTargets( VectorXd e );
	int  getActiveEffId(void);
	VectorXd initTargs(void);
	
private:

	void __updateS( void );
	
	Tree * T;
	MatrixXd J;
	MatrixXd Jpinv;
	MatrixXd JpseudoInv;

	VectorXd e;
	VectorXd s;
	VectorXd prevTarget;
	
	int rows;
	int cols;
	
	
};
#endif
