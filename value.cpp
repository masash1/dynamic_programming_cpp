// An implementation file (2/4)

/*--------------- VALUE ITERATION FUNCTIONS ----------------*/

// C Headers
//#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>
//#include <time.h>
//#include <string.h>
//#include <sys/time.h>

// C++ Headers
//#include <iostream>
#include <vector>
using namespace std;

// Own Headers
#include "params.h"

void conditionPhi(int i, int j, int k, vector<float> &tempCost, vector<float> &Jprev)
{
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

void conditionTheta(int i, int j, int k, vector<float> &tempCost, vector<float> &Jprev)
{
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

void conditionR(int i, int j, int k, vector<float> &tempCost, vector<float> &Jprev)
{
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

void computeTotalCost(vector<float> &tempCost, vector<float> &totalCost)
{
	float tempCostTotal=0;
	
	for(int n=0; n<numActions; n++){
		tempCostTotal+=tempCost[n];
	}
	for(int n=0; n<numActions; n++){
		totalCost[n]=vMove+gamma1*((1-perr)*tempCost[n]+(perr/6)*(tempCostTotal-tempCost[n]));
	}
}

float computeNewValue(vector<float> &totalCost)
{
	float max;
	max = totalCost[0];
	
	for(int n=0; n<numActions; n++){
		if(totalCost[n]>max)
			max=totalCost[n];
	}

	return max;
}

char computeNewPolicy(vector<float> &totalCost)
{
	float max;
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
//#pragma acc kernels
void valueIteration(vector<float> &isobst, vector<float> &isgoal, vector<float> &J, vector<char> &U, vector<float> &Jprev)
{
	vector<float> tempCost(numActions,0), totalCost(numActions,0);

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

