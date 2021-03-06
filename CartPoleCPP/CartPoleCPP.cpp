// CartPoleCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

const double MASSPOLE = .209;						//kg
const double LENGTH = .326;							//meters
const double FOURTHIRDS = 4 / 3;					//generic
const double GRAVITY = 9.8;							//meters / second
const int FORCE_MAG = 10;							//Newtons
const double TOTAL_MASS = MASSPOLE + .711;			//kg
const double POLEMASS_LENGTH = MASSPOLE * LENGTH;	//kg * meters
const double TAU = .002;							//seconds

void cartPole(int action, float *x, float *x_dot, float *theta, float *theta_dot){ //
	int action;
	double *x, *x_dot, *theta, *theta_dot;
	double xacc, thetaacc, force, costheta, sintheta, temp;

	force = (action > 0) ? FORCE_MAG : -FORCE_MAG;
	costheta = cos(*theta);
	sintheta = sin(*theta);

	temp = (force + POLEMASS_LENGTH * *theta_dot * *theta_dot * sintheta)
		/ TOTAL_MASS;

	thetaacc = (GRAVITY * sintheta - costheta * temp)
		/ (LENGTH * (FOURTHIRDS - MASSPOLE * costheta * costheta
			/ TOTAL_MASS));

	xacc = temp - POLEMASS_LENGTH * thetaacc* costheta / TOTAL_MASS;

	/*** Update the four state variables, using Euler's method. ***/

	*x += TAU * *x_dot;
	*x_dot += TAU * xacc;
	*theta += TAU * *theta_dot;
	*theta_dot += TAU * thetaacc;
}

int main()
{
	cartPole(0, *x, *x_dot, *theta, *theta_dot);
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
