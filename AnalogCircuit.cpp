//AnalogCircuit.cpp - function definitions for the analog circuit
//
// 20-May-22  M. Watler         Created.
// 27-May-22  M. Watler         Added graphical display.

#include <iomanip>//setw
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>//M_PI
#include <stdlib.h>//abs

#include "AnalogCircuit.h"
#include "Capacitor.h"
#include "Inductor.h"
#include "Resistor.h"

using namespace std;

int xpos, ypos;
int windowWidth, windowHeight;
double scalingFactor;

void start() {
	cout << "BEGIN" << endl;
	AnalogCircuit circuit("RLC.dat");
	circuit.run();
	cout << "Press any key + ENTER to end..." << endl;
	char key;
	cin >> key;
	glutLeaveMainLoop();
	cout << "DONE!" << endl;
}

void AnalogCircuit::display(float R, float G, float B) {//draw a point on the screen
	//	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(R, G, B);//RGB
	glBegin(GL_POINTS);
	glVertex2f(xpos, ypos);
	glEnd();
	glFlush();
}

AnalogCircuit::AnalogCircuit(std::string filename) {//dump data to filename, initialize variables
	fout.open(filename);
	fout << setw(12) << "Time";
	list<Component*>::iterator it;
	for (it = component.begin(); it != component.end(); ++it) {
		fout << setw(12) << (*it)->GetName();
	}
	fout << endl;

}


void AnalogCircuit::run() {
	component.push_back(new Resistor(10, 1.0, 0.0, 0.0, "R1"));//10ohm, Red
	component.push_back(new Capacitor(0.000100, 0.0, 1.0, 0.0, "C1"));//100uF, Green
	component.push_back(new Inductor(0.020, 0.0, 0.0, 1.0, "L1"));//20mH, Blue
	double 	xpos = windowWidth / 6;
	double ypos = (scalingFactor * windowHeight)/6;
	int numMarkers = 10;  // Number of markers
	float markerLength = 20.0;  // Length of each marker
	float intervalX = (scalingFactor * windowHeight) / numMarkers;  // Space between markers for horizontal line
	float intervalY = windowWidth / numMarkers;

	// Calculate center coordinates
	float centerX = windowWidth / 2.0;
	float centerY = (scalingFactor * windowHeight) / 2.0;

	//Horizontal line
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(0, ypos);  // Starting point of the line (center)
	glVertex2f(windowWidth, ypos);  // Ending point of the line (right edge)
	glEnd();

	//Vertical line
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(xpos, 0);  // Starting point of the line (center)
	glVertex2f(xpos, scalingFactor * windowHeight);  // Ending point of the line (top edge)
	glEnd();

	//Horizontal line markers
	for (int i = 0; i <= numMarkers; i++) {
		float markerY = i * intervalX;
		glBegin(GL_LINES);
		glVertex2f(xpos - markerLength / 2, markerY);  // Starting point of the marker
		glVertex2f(xpos + markerLength / 2, markerY);  // Ending point of the marker
		glEnd();
	}

	//Vertical line markers
	for (int i = 0; i <= numMarkers; i++) {
		float markerX = i * intervalY;
		glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 0.0);
		glVertex2f(markerX,ypos - markerLength / 2 );  // Starting point of the marker
		glVertex2f(markerX, ypos + markerLength / 2);  // Ending point of the marker
		glEnd();
	}
	//Display each component's name and colour
		
	list<Component*>::iterator it;
	for (it = component.begin(); it != component.end(); ++it) {
		std::string name = (*it)->GetName();


	}
	glFlush();




	//Run the simulation for the first 0.06 seconds (timeMax is 0.1 sec)
	//Dump data to a file as well as display on the screen

	for (double time = 0.0; time < 0.6 * timeMax; time += T) {
		double V = Vpeak * sin(2.0 * M_PI * freq * time);
		//...

		CostFunctionV(I, V);
	}

	//Run the simulation to the end (timeMax is 0.1 sec)
	//Dump data to a file as well as display on the screen
	for (double time = 0.6 * timeMax; time < timeMax; time += T) {
		double V = 0.0;
		//
		

		CostFunctionV(I, V);
	}
}

void AnalogCircuit::CostFunctionV(double& current, double voltage) {
	double I1 = current;
	double J1 = 0.0;
	double J0 = 0.0;
	double alpha = 1.0;

	do {
		double sumVoltage = 0.0;
		list<Component*>::iterator it;
		for (it = component.begin(); it != component.end(); ++it) {
			double Vcomponent = (*it)->GetVoltage(I1, T);
			sumVoltage += Vcomponent;
		}
		J1 = sumVoltage - voltage;
		//Reduce alpha if J1 and J0 are of opposite signs or are equal to each other
		if ((abs(J0 - J1) != (J0 - J1)) || J0 == J1)alpha /= 2.0;

		if (abs(J1) > tolerance) {
			if (J1 < 0) {//increase the current
				I1 += alpha;
			}
			else {
				I1 -= alpha;
			}
			J0 = J1;
		}
		if (alpha < tolerance / 1000000.0) {//reset alpha
			alpha = ((double)rand() / (RAND_MAX)) + 0.5;//between 0.5 and 1.5
		}
	} while (abs(J1) > tolerance);

	fout << setw(12) << I1;
	list<Component*>::iterator it;
	for (it = component.begin(); it != component.end(); ++it) {
		fout << setw(12) << (*it)->GetVoltage(I1, T);
		ypos = (windowHeight * (*it)->GetVoltage(I1, T) / Vpeak) / 2.0 + scalingFactor * windowHeight / 2.0;
		(*it)->Display();
		(*it)->Update();
	}
	fout << endl;

	current = I1;
}

AnalogCircuit::~AnalogCircuit() {//perform cleanup
}