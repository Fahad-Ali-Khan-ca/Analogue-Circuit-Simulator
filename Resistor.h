// 09-Sept-23 Fahad A. Khan Created
#ifndef _RESISTOR_H_
#define _RESISTOR_H_
#include "component.h"

class Resistor : public Component {
    double resistance;
public:
    Resistor(double resistance, double red, double green, double blue, std::string name);
    std::string GetName() const override;
    void Update() override;
    double GetVoltage(double current, double timestep) override;
    void Display() override;
};
#endif //_RESISTOR_H
