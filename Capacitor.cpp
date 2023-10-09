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
	return 0.0;
}

std::string Capacitor::GetName() const
{
	return std::string();
}

void Capacitor::Display()
{
	//set color to the color of the component
	glColor3f(Red, Green, Blue);

}

void Capacitor::Update()
{
}

double Capacitor::GetInductance()
{
	return 0.0;
}


