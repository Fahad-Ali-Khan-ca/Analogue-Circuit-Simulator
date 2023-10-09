// 12-Sept-23 Fahad A. Khan Created
// Functions defintion for the resistor class

#include "Resistor.h"
#include <iostream>

Resistor::Resistor(double resistance, double red, double green, double blue, std::string name) {
    this->resistance = resistance;
    this->Red = red;
    this->Green = green;
    this->Blue = blue;
    this->name = name;
}

std::string Resistor::GetName() const
{
    return std::string();
}

void Resistor::Update()
{
}

double Resistor::GetVoltage(double current, double timestep) {
    return current * resistance;
}

void Resistor::Display()
{
}


