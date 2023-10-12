#include "Capacitor.h"


Capacitor::Capacitor(double capacitance, double red, double green, double blue, std::string name)
{
	this->capacitance = capacitance;
	this->Red = red;
	this->Green = green;
	this->Blue = blue;
	this->name = name;
}

double Capacitor::GetVoltage(double current, double timestep)
{
	double voltage = Vc + (current * timestep) / capacitance;
	return voltage;
}

std::string Capacitor::GetName() const
{
	return name;
}

void Capacitor::Display(double xpos, double ypos)
{
	//set color to the color of the component
	glColor3f(Red, Green, Blue);
	// Draw a point at the specified position
	glBegin(GL_POINTS);
	glVertex2f(xpos, ypos);
	glEnd();

	// Force execution of OpenGL commands in finite time
	glFlush();
}

void Capacitor::Update(double current, double voltage)
{
	double Vc = voltage;
}

double Capacitor::GetInductance()
{
	return 0.0;
}


void Capacitor::SetColor() const
{
	// set the color to the color of the component
	glColor3f(Red, Green, Blue);
}

