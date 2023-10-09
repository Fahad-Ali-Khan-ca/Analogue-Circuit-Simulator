// 09-Sept-23 Fahad A. Khan Created
// Compare this snippet from Capacitor.h:

#ifndef _INDUCTOR_H
#define _INDUCTOR_H
#include "component.h"
class Inductor : public Component {
	double inductance;
	public:
		Inductor(double inductance, double red, double green, double blue, std::string name);
		double GetVoltage(double current, double timestep) override;
		std::string GetName() const override;
		//display
		void Display() override;
		//update	
		void Update() override;
		//getters
		double GetInductance();
		//setters
		void SetInductance(double l);

};
#endif // !_INDUCTOR_H_
