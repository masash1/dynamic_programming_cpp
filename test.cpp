/********************************************************
This program is  Manjimaru's simple value iteration 
C++ version. There is an original C version in 
~/dynamic_programming/.
*********************************************************/

// Client Code (means this file contains main function)

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

// Own Headers
#include "setup.h"
#include "value.h"
#include "timer.h"
#include "params.h"

int main(int argc, char **argv)
{
double  iStart=cpuSecond();

	// DEFINE PARAMETERS
	float dr, dtheta, dphi;
	vector<float> rdim(2), thetadim(2), phidim(2);
	vector<float> rVec, thetaVec, phiVec;
	// - minimum grid resolution for r, theta, phi
	dr = 1.0, dtheta = 1.0, dphi = 1.0;
	// - dimensions of the state space
	rdim[0] = 0.0, rdim[1] = 10.0;
	thetadim[0] = 0.0, thetadim[1] = 360.0;
	phidim[0] = 0.0, phidim[1] = 360.0;
	// - number of grid cells
	nr = numberCells(dr, rdim);
	ntheta = numberCells(dtheta, thetadim);
	nphi = numberCells(dphi, phidim);
	printf("nr=%d ntheta=%d nphi=%d\n", nr,ntheta,nphi);
	printf("Number of states is %d\n", nr*ntheta*nphi);
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
	vector<float> isobst(nr*ntheta*nphi,0), isgoal(nr*ntheta*nphi,0);
	setObst(isobst);
	setGoal(thetaVec, phiVec, isgoal);

	// DEFINE INITIAL GUESS AT VALUE AND POLICY
	vector<float> J(nr*ntheta*nphi,0);
	vector<char> U(nr*ntheta*nphi,0);
	setInitialValue(isobst, isgoal, J);
	setInitialPolicy(isobst, isgoal, U);

	// DO VALUE ITERATION
	vector<float> Jprev(nr*ntheta*nphi,0);
	vector<char> Uprev(nr*ntheta*nphi,0);
	
	int t=1;
	float error=1;
	while(error!=0){
		printf("Iteration %d\n", t);

		// Iterate over all states.
		Jprev = J;
		Uprev = U;
		valueIteration(isobst, isgoal, J, U, Jprev);

		error=0;
                for(int x=0; x<nr*ntheta*nphi; x++){
                       // printf("%2d J=%3.1f Jprev= %3.1f U=%2d\n", x, J[x], Jprev[x],U[x]);
                        error+=(J[x]-Jprev[x]);
                }
                t+=1;
		printf("\n");

	}
	
double iElaps=cpuSecond()-iStart;
	printf("Time elapsed = %f ms\n", iElaps*1000.0f);
	return(0);
}
