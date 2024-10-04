#ifdef __cplusplus
extern "C" {
#endif

#ifndef __SERVO_H__
#define __SERVO_H__

#include "Standard_Library.h"
#include "System_Library.h"

uint8_t servo_init(uint8_t i2c_dev, uint8_t hwAddress, uint8_t freq);
uint8_t servo_end(uint8_t hwAddress);

void init_angle_to_pulse_length_lookup_table();	
int pulse_length_to_tick_converter(int frequency, int pulseLength);
void set_servo(uint8_t hwAddress, uint8_t pwmChannel, int frequency, int angleDegree);
void set_servo_pwm(uint8_t hwAddress, uint8_t pwmChannel, int frequency, int pulseLength);

#endif
