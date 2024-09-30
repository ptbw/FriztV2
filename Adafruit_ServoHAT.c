#include "Standard_Library.h"
#include "System_Library.h"
#include "PCA9685.h"
#include "Adafruit_ServoHAT.h"


int angleToPulseLengthLookupTable[1810];

void init_angle_to_pulse_length_lookup_table(){
    // slope = (outputend - outputstart) / (inputend - inputstart)
    //       = (2500 - 500) / (1800 - 0)
    double slope = 1.0 * (2000.0/1800.0);

	int i;
    for (i = 0; i < 1810; i++){
		// 0 -> 500, 180 -> 2500, 90 -> 1500
        //angleToPulseLengthLookupTable[i] = (int)(500 + i * 11.11111111+0.5);
        // 0 -> 500, 1800 -> 2500, 900 -> 1500
        angleToPulseLengthLookupTable[i] = (int)(500 + (slope * i));
	}
    printf("******Angle To Duty Cycle Lookup Table******\n");
    printf("Index\tAngle\tPulse Length\t\n");
    for (i = 0; i < 1810; i+=900){
        double angle = (1.0 * i) / 10.0 ;
        printf("%d\t%f\t%d\n", i, angle, angleToPulseLengthLookupTable[i]);
    }
}



int pulse_length_to_tick_converter(int frequency, int pulseLength){
	double periodLength = (1.0 / frequency) * 1000000;
	double timePerTick = periodLength / 4096.0;
	double tick = pulseLength / timePerTick;
    //printf("hi %d %f %f %f\n", frequency, periodLength, timePerTick, tick);
	return ((int)tick);
}

void set_servo(uint8_t hwAddress, uint8_t pwmChannel, int frequency, double angleDegree){
    if(angleDegree < 5.0 || angleDegree > 175.0){
        printf("angle %.2f is out of servo range. Exit....\n", angleDegree);
        //exit(1);
        return;
	}

    int key = (int)(angleDegree * 10);
    //printf("Angle = %.2f Key = %d \n", angleDegree, key);
    int pulseLength = angleToPulseLengthLookupTable[key];
	uint16_t offTime = (uint16_t)pulse_length_to_tick_converter(frequency, pulseLength);
	set_PWM_PCA9685(hwAddress, pwmChannel, 0, offTime);	
}
