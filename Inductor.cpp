// 12-Sept-23 Fahad A. Khan Created
// // Functions defintion for the inductor class

#include "Inductor.h"

Inductor::Inductor(double inductance, double red, double green, double blue, std::string name) {
    this->inductance = inductance;
    this->Red = red;
    this->Green = green;
    this->Blue = blue;
    this->name = name;
}

double Inductor::GetVoltage(double current, double timestep) {
    return current * inductance;
}

std::string Inductor::GetName() const {
    return name;
}

void Inductor::Display() {
    std::cout << "Inductor: " << name << std::endl;
	std::cout << "Inductance: " << inductance << std::endl;
	std::cout << "Red: " << Red << std::endl;
	std::cout << "Green: " << Green << std::endl;
	std::cout << "Blue: " << Blue << std::endl;
}

void Inductor::Update()
{
}

double Inductor::GetInductance()
{
    return 0.0;
}

void Inductor::SetInductance(double l)
{
}




