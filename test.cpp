/********************************************************
This program is  Manjimaru's simple value iteration 
C++ version. There is an original C version in 
~/dynamic_programming/.
*********************************************************/
// C Headers
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
// C++ Headers
//#include <iostream>
#include <vector>
using namespace std;

// FUNCTIONS FOR SETUP
int numberCells(double, vector<double> &);
void setVector(int, double, vector<double> &, vector<double> &);
void setObst(vector<double> &);
void setGoal(vector<double> &, vector<double> &, vector<double> &);
void setInitialValue(vector<double> &, vector<double> &, vector<double> &);
void conditionValue(vector<double> &, vector<double> &, vector<double> &, int, int, int);
void setInitialPolicy(vector<double> &, vector<double> &, vector<char> &);
void conditionPolicy (vector<double> &, vector<double> &, vector<char> &, int, int, int);

// FUNCTIONS FOR VALUE ITERATION
void valueIteration(vector<double> &, vector<double> &, vector<double> &, vector<char> &, vector<double> &);
void conditionR(int, int, int, vector<double> &, vector<double> &);
void conditionTheta(int, int, int, vector<double> &, vector<double> &);
void conditionPhi(int, int, int, vector<double> &, vector<double> &);
void computeTotalCost(vector<double> &, vector<double> &);
double computeNewValue(vector<double> &);
char computeNewPolicy(vector<double> &);

// FUNCTIONS FOR ANALYSIS
double cpuSecond(void);

// DEFINE GLOBAL PARAMETERS
int nr, ntheta, nphi;
double perr;
double gamma1;
double vGoal, vObst, vMove;
double vInitial;
int numActions = 7;

int main(int argc, char **argv){
	double iStart=cpuSecond();

	// DEFINE PARAMETERS
	double dr, dtheta, dphi;
	vector<double> rdim(2), thetadim(2), phidim(2);
	vector<double> rVec, thetaVec, phiVec;
	// - minimum grid resolution for r, theta, phi
	dr = 5.0, dtheta = 180.0, dphi = 180;
	// - dimensions of the state space
	rdim[0] = 0.0, rdim[1] = 10.0;
	thetadim[0] = 0.0, thetadim[1] = 360.0;
	phidim[0] = 0.0, phidim[1] = 360.0;
	// - number of grid cells
	nr = numberCells(dr, rdim);
	ntheta = numberCells(dtheta, thetadim);
	nphi = numberCells(dphi, phidim);
	printf("nr=%d ntheta=%d nphi=%d\n", nr, ntheta, nphi);
	// - vectors for r, theta, phi
	setVector(nr, dr, rdim, rVec);
	setVector(ntheta, dtheta, thetadim, thetaVec);
	setVector(nphi, dphi, phidim, phiVec);

	// - probability of going the wrong way
	perr = 0.0;
	// attenuation rate
	gamma1 = 1.0;
	// - value of goal, collision, movement
	vGoal = 100.0;
	vObst = -100.0;
	vMove = -1.0;
	// initial guess at all values
	vInitial = 0.0;

	// DEFINE OBSTACLE AND GOAL LOCATIONS
	vector<double> isobst(nr*ntheta*nphi,0), isgoal(nr*ntheta*nphi,0);
	setObst(isobst);
	setGoal(thetaVec, phiVec, isgoal);

	// DEFINE INITIAL GUESS AT VALUE AND POLICY
	vector<double> J(nr*ntheta*nphi,0);
	vector<char> U(nr*ntheta*nphi,0);
	setInitialValue(isobst, isgoal, J);
	setInitialPolicy(isobst, isgoal, U);

	// DO VALUE ITERATION
	int T = 100;
	vector<double> Jprev(nr*ntheta*nphi,0);
	vector<char> Uprev(nr*ntheta*nphi,0);

	for(int t=0; t<T; t++){
		printf("Iteration %d\n", t+1);

		// Iterate over all states.
		Jprev = J;
		Uprev = U;
		valueIteration(isobst, isgoal, J, U, Jprev);

		for(int x=0; x<nr*ntheta*nphi; x++){
			printf("%2d J=%3.1f U=%2d\n", x, J[x], U[x]);
		}
		printf("\n");
	}
	
	double iElaps=cpuSecond()-iStart;
	printf("Time elapsed = %f ms\n", iElaps*1000.0f);
	return(0);
}

/*--------------- SETUP FUNCTIONS ----------------*/

int numberCells(double d, vector<double> &dim){
	int n = 0;
	double diff;
	diff = dim[1]-dim[0];

	if(d<1 || d>diff){
		printf("value of resolution or dimension is invalid.\n");
	}
	else{
		n = floorf(diff/d+1.0);
	}

	return n;
}

void setVector(int n, double d, vector<double> &dim, vector<double> &Vec){
	double value;
	value = dim[0];

	for(int i=0; i<n; i++){
		Vec.push_back(value);
		value += d;
	}
}

void setObst(vector<double> &isobst){
	for(int j=0; j<ntheta; j++){
		for(int k=0;k<nphi; k++){
			isobst[nr*ntheta*k+(nr-1)*ntheta+j] = 1;
		}
	}
}

void setGoal(vector<double> &thetaVec, vector<double> &phiVec, vector<double> &isgoal){
	for(int j=0; j<ntheta; j++){
		for(int k=0; k<nphi; k++){
			if(thetaVec[j]==phiVec[k])
				isgoal[nr*ntheta*k+j] = 1;
		}
	}
}

void setInitialValue(vector<double> &isobst, vector<double> &isgoal, vector<double> &J){
	for(int i=0; i<nr; i++){
		for(int j=0; j<ntheta; j++){
			for(int k=0; k<nphi; k++){
				conditionValue(isobst, isgoal, J, i, j, k);
			}
		}
	}
}

void conditionValue(vector<double> &isobst, vector<double> &isgoal, vector<double> &J, int i, int j, int k){
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

void setInitialPolicy(vector<double> &isobst, vector<double> &isgoal, vector<char> &U){
	srand((unsigned)time(NULL));

	for(int i=0; i<nr; i++){
		for(int j=0; j<ntheta; j++){
			for(int k=0; k<nphi; k++){
				conditionPolicy(isobst, isgoal, U, i, j, k);
			}
		}
	}
}

void conditionPolicy (vector<double> &isobst, vector<double> &isgoal, vector<char> &U, int i, int j, int k){
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

/*--------------- VALUE ITERATION FUNCTIONS ----------------*/

void valueIteration(vector<double> &isobst, vector<double> &isgoal, vector<double> &J, vector<char> &U, vector<double> &Jprev){
	vector<double> tempCost(numActions,0), totalCost(numActions,0);

	for(int i=0; i<nr; i++){
		for(int j=0; j<ntheta; j++){
			for(int k=0; k<nphi; k++){
				if(!isobst[nr*ntheta*k+ntheta*i+j] && !isgoal[nr*ntheta*k+ntheta*i+j]){
					tempCost[0]=Jprev[nr*ntheta*k+ntheta*i+j];
					// condition of r
					conditionR(i, j, k, tempCost, Jprev);

					// Compute the total expected cost for each of the possible actions.
					computeTotalCost(tempCost, totalCost);

					// Compute the new exptected cost-to-go, by taking the maximum over
					// possible actions.
					J[nr*ntheta*k+ntheta*i+j] = computeNewValue(totalCost);
					U[nr*ntheta*k+ntheta*i+j] = computeNewPolicy(totalCost);

				}
			}
		}
	}
}

void conditionR(int i, int j, int k, vector<double> &tempCost, vector<double> &Jprev){
	if(i==0){
		tempCost[1] = Jprev[nr*ntheta*k+ntheta*(i+1)+j];
		tempCost[2] = Jprev[nr*ntheta*k+ntheta*i+j];
	}
	else{
		tempCost[1] = Jprev[nr*ntheta*k+ntheta*(i+1)+j];
		tempCost[2] = Jprev[nr*ntheta*k+ntheta*(i-1)+j];
	}
	conditionTheta(i, j, k, tempCost, Jprev);
}

void conditionTheta(int i, int j, int k, vector<double> &tempCost, vector<double> &Jprev){
	if(j==0){
		tempCost[3] = Jprev[nr*ntheta*k+ntheta*i+(j+1)];
		tempCost[4] = Jprev[nr*ntheta*k+ntheta*i+(ntheta-1)];
	}
	else if(j==ntheta-1){
		tempCost[3] = Jprev[nr*ntheta*k+ntheta*i];
		tempCost[4] = Jprev[nr*ntheta*k+ntheta*i+(j-1)];
	}
	else{
		tempCost[3] = Jprev[nr*ntheta*k+ntheta*i+(j+1)];
		tempCost[4] = Jprev[nr*ntheta*k+ntheta*i+(j-1)];
	}
	conditionPhi(i, j, k, tempCost, Jprev);
}

void conditionPhi(int i, int j, int k, vector<double> &tempCost, vector<double> &Jprev){
	if(k==0){
		tempCost[5] = Jprev[nr*ntheta*(k+1)+ntheta*i+j];
		tempCost[6] = Jprev[nr*ntheta*(nphi-1)+ntheta*i+j];
	}
	else if(k==nphi-1){
		tempCost[5] = Jprev[ntheta*i+j];
		tempCost[6] = Jprev[nr*ntheta*(k-1)+ntheta*i+j];
	}
	else{
		tempCost[5] = Jprev[nr*ntheta*(k+1)+ntheta*i+j];
		tempCost[6] = Jprev[nr*ntheta*(k-1)+ntheta*i+j];
	}
}

void computeTotalCost(vector<double> &tempCost, vector<double> &totalCost){
	double tempCostTotal=0;
	
	for(int n=0; n<numActions; n++){
		tempCostTotal+=tempCost[n];
	}
	for(int n=0; n<numActions; n++){
		totalCost[n]=vMove+gamma1*((1-perr)*tempCost[n]+(perr/6)*(tempCostTotal-tempCost[n]));
	}
}

double computeNewValue(vector<double> &totalCost){
	double max;
	max = totalCost[0];
	
	for(int n=0; n<numActions; n++){
		if(totalCost[n]>max)
			max=totalCost[n];
	}

	return max;
}

char computeNewPolicy(vector<double> &totalCost){
	double max;
	char idx;
	max = totalCost[0];

	for(int n=0; n<numActions; n++){
		if(totalCost[n]>max){
			max=totalCost[n];
			idx=n;
		}
	}

	return idx;
}

/*----------- FUNCTIONS FOR ANALYSIS ----------*/
double cpuSecond(void){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return ((double)tp.tv_sec+(double)tp.tv_usec*1.e-6);
}
