
#include <stdio.h>
#include "hardwareserial.h"
#include "led.h"
#include "battery.h"
#include <ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <ros_arduino_msgs/RawImu.h>
#include <geometry_msgs/Vector3.h>

#define DEBUG_RATE 10

bool is_first = true;

Led led;
void led_cb(const std_msgs::Float64& cmd_msg){
	static bool stat_led = true;
	if(stat_led){
		led.on_off(ON);
		stat_led = false;
	}else{
		led.on_off(OFF);
		stat_led = true;
	}
}


int main(void) 
{
	SystemInit();
	initialise();

	uint32_t previous_debug_time = 0;

	char buffer[50];

	std_msgs::String str_msg;

	ros::NodeHandle  nh;
	nh.initNode();

	ros::Publisher battery("battery", &str_msg);
	ros::Subscriber<std_msgs::Float64> sub("led", led_cb);
	nh.advertise(battery);
	nh.subscribe(sub);

	Battery bat(25, 10.6, 12.6);
	bat.init();


	led.init();

	while(1){
		if ((millis() - previous_debug_time) >= (1000 / DEBUG_RATE)) {
			sprintf (buffer, "Current borad volt is : %f", bat.get_volt());
			str_msg.data = buffer;
			battery.publish( &str_msg );
			previous_debug_time = millis();    
		}
		nh.spinOnce();
	}
}


