/*
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
*/
#include "Standard_Library.h"
#include "System_Library.h"
#include "linux_i2c.h"
#include "PCA9685.h"
#include "servo.h"



uint8_t servo_init(uint8_t i2c_dev, uint8_t hwAddress, uint8_t freq)
{     
    init_angle_to_pulse_length_lookup_table();
    
    // setup the I2C bus device 
    int fd = PCA9685_openI2C(i2c_dev, hwAddress);
    if (fd < 0) {
        fprintf(stderr, "initHardware(): PCA9685_openI2C() returned ");
        fprintf(stderr, "%d for adpt %d at addr %x\n", fd, i2c_dev, hwAddress);
        return -1;
    } // if 

    int retval = PCA9685_initPWM(fd, hwAddress, freq);  
    return retval;
}

uint8_t servo_end(uint8_t hwAddress)
{
    int retval = PCA9685_closeI2C(hwAddress);
    return retval;
}

int angleToPulseLengthLookupTable[181];

void init_angle_to_pulse_length_lookup_table(){
	int i;
	for (i = 0; i < 181; i++){
		// 0 -> 500, 180 -> 2500, 90 -> 1500
		angleToPulseLengthLookupTable[i] = (int)(500 + i * 11.1111111+0.5);
	}	
	//printf("******Angle To Duty Cycle Lookup Table******\n");
	//printf("Index\tAngle\tPulse Length\t\n");
	//for (i = 0; i < 181; i++){
		//printf("%d\t%d\t%d\n", i, i, angleToPulseLengthLookupTable[i]);
	//}
	// 500 to 2500 	  
}

int pulse_length_to_tick_converter(int frequency, int pulseLength){
	double periodLength = (1.0 / frequency) * 1000000;
	double timePerTick = periodLength / 4096.0;
	double tick = pulseLength / timePerTick;
	//printf("hi %d %f %f %f\n", frequency, periodLength, timePerTick, tick);
	return ((int)tick);
}

void set_servo(uint8_t hwAddress, uint8_t pwmChannel, int frequency, int angleDegree){
    if(angleDegree <= 0 || angleDegree >= 180){
		printf("angle %d is out of servo range. Exit....\n", angleDegree);
		exit(1);
	}
	int pulseLength = angleToPulseLengthLookupTable[angleDegree];
	uint16_t offTime = (uint16_t)pulse_length_to_tick_converter(frequency, pulseLength);
    //printf("angle %d, pulseLength %d, offTime %d\n", angleDegree, pulseLength, offTime);
    set_PWM_PCA9685(hwAddress, pwmChannel, 0, offTime);
}

void set_servo_pwm(uint8_t hwAddress, uint8_t pwmChannel, int frequency, int pulseLength){
    if(pulseLength <= 500 || pulseLength >= 2500){
		printf("pulseLength %d is out of servo range. Exit....\n", pulseLength);
		exit(1);
	}
	// int pulseLength = angleToPulseLengthLookupTable[angleDegree];
	uint16_t offTime = (uint16_t)pulse_length_to_tick_converter(frequency, pulseLength);
    //printf("offTime %d\n", offTime);
	set_PWM_PCA9685(hwAddress, pwmChannel, 0, offTime);	
}


