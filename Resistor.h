#ifndef _RESISTOR_H_
#define _RESISTOR_H_
#include "component.h"
class Resistor : public Component {
    double resistance;
public:
    Resistor(double r) : resistance(r) {}
    double getVoltage(double current)  {
        return current * resistance;
    }
};
#endif //_RESISTOR_H
