#ifndef _BATTERY_H_
#define _BATTERY_H_ 
#include "config.h"

class Battery {
public:
	Battery(float _threshold, float _volt_min, float _volt_max);
	void init();
	float get_volt();
	float get_battery_notifier();
	bool get_battery_low();

private:
	float threshold;
	float volt_min;
	float volt_max;
	__IO u16 ADC_ConvertedValue[1];
};

#endif // _BATTERY_H_
