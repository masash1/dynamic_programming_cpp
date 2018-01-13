// An implementation file (1/4)

/*--------------- SETUP FUNCTIONS ----------------*/

// C Headers
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
//#include <string.h>
//#include <sys/time.h>

// C++ Headers
#include <vector>
using namespace std;

// Own Headers
#include "params.h"

int numberCells(float d, vector<float> &dim)
{
	int n = 0;
	float diff;
	diff = dim[1]-dim[0];

	if(d<1 || d>diff){
		printf("value of resolution or dimension is invalid.\n");
	}
	else{
		n = floorf(diff/d+1.0);
	}

	return n;
}

void setVector(int n, float d, vector<float> &dim, vector<float> &Vec)
{
	float value;
	value = dim[0];

	for(int i=0; i<n; i++){
		Vec.push_back(value);
		value += d;
	}
}

void setObst(vector<float> &isobst)
{
	for(int j=0; j<ntheta; j++){
		for(int k=0;k<nphi; k++){
			isobst[nr*ntheta*k+(nr-1)*ntheta+j] = 1;
		}
	}
}

void setGoal(vector<float> &thetaVec, vector<float> &phiVec, vector<float> &isgoal)
{
	for(int j=0; j<ntheta; j++){
		for(int k=0; k<nphi; k++){
			if(thetaVec[j]==phiVec[k])
				isgoal[nr*ntheta*k+j] = 1;
		}
	}
}

void conditionValue(vector<float> &isobst, vector<float> &isgoal, vector<float> &J, int i, int j, int k)
{
	if(isobst[nr*ntheta*k+ntheta*i+j]){
		J[nr*ntheta*k+ntheta*i+j] = vObst;
	}
	else if(isgoal[nr*ntheta*k+ntheta*i+j]){
		J[nr*ntheta*k+ntheta*i+j] = vGoal;
	}
	else{
		J[nr*ntheta*k+ntheta*i+j] = vInitial;
	}
}

void setInitialValue(vector<float> &isobst, vector<float> &isgoal, vector<float> &J)
{
	for(int i=0; i<nr; i++){
		for(int j=0; j<ntheta; j++){
			for(int k=0; k<nphi; k++){
				conditionValue(isobst, isgoal, J, i, j, k);
			}
		}
	}
}

void conditionPolicy (vector<float> &isobst, vector<float> &isgoal, vector<char> &U, int i, int j, int k)
{
	if(isobst[nr*ntheta*k+ntheta*i+j]){
		U[nr*ntheta*k+ntheta*i+j] = -1;
	}
	else if(isgoal[nr*ntheta*k+ntheta*i+j]){
		U[nr*ntheta*k+ntheta*i+j] = -1;
	}
	else{
		char r = rand() % numActions;
		U[nr*ntheta*k+ntheta*i+j] = r;
	}
}

void setInitialPolicy(vector<float> &isobst, vector<float> &isgoal, vector<char> &U)
{
	srand((unsigned)time(NULL));

	for(int i=0; i<nr; i++){
		for(int j=0; j<ntheta; j++){
			for(int k=0; k<nphi; k++){
				conditionPolicy(isobst, isgoal, U, i, j, k);
			}
		}
	}
}

