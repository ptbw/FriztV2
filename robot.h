#ifndef ROBOT_H
#define ROBOT_H

//#include "vl53l0x.h"

#include "VL53L0X_Rasp/vl53l0x_api.h"
#include "VL53L0X_Rasp/vl53l0x_platform.h"

#include "configwindow.h"
#include "speak.h"
#include "i.h"

class Robot
{
private:
    // send packets

    static const int minPin = 2;
    static const int maxPin = 19;

    static const int ARDUINO_GET_ID = 0; // returns ARDU
    static const int ARDUINO_RESET = 1; //
    static const int ARDUINO_SET_OBJECT = 2; //
    static const int ARDUINO_SET_SERVO = 3; //
    static const int ARDUINO_HEARTBEAT = 4;
    static const int ARDUINO_RELEASE_SERVO = 5;
    static const int ARDUINO_GET_IR = 6;
    static const int ARDUINO_GET_SONAR = 7;

    static const int ARDUINO_LOAD_CONFIG = 32;
    static const int ARDUINO_SAVE_CONFIG = 33;
    static const int ARDUINO_SAVE_SEQUENCE = 34;


    float f_leftHorizontalEye;
    float f_leftVerticalEye;
    float f_rightHorizontalEye;
    float f_rightVerticalEye;
    float f_leftEyebrow;
    float f_rightEyebrow;
    float f_rightEyelid;
    float f_leftEyelid;
    float f_leftLip;
    float f_rightLip;
    float f_jaw;
    float f_neckTilt;
    float f_neckTwist;
    
    //int sonarOutPin;
    //int sonarInPin;

    //int irValue;
    //double sonarValue;

    //CalibrationData * cd;

    //Serial * serial;

    //vl53l0x * ranger;


public:
    int leftHorizontalEyeMin;
    int leftHorizontalEyeMax;
    int leftHorizontalEyeMid;
    int leftHorizontalEyePin;
    int leftVerticalEyeMin;
    int leftVerticalEyeMax;
    int leftVerticalEyeMid;
    int leftVerticalEyePin;
    int rightHorizontalEyeMin;
    int rightHorizontalEyeMax;
    int rightHorizontalEyeMid;
    int rightHorizontalEyePin;
    int rightVerticalEyeMin;
    int rightVerticalEyeMax;
    int rightVerticalEyeMid;
    int rightVerticalEyePin;
    int leftLipMin;
    int leftLipMax;
    int leftLipMid;
    int leftLipPin;
    int rightLipMin;
    int rightLipMax;
    int rightLipMid;
    int rightLipPin;
    int jawMin;
    int jawMax;
    int jawMid;
    int jawPin;
    int neckTiltMin;
    int neckTiltMax;
    int neckTiltMid;
    int neckTiltPin;
    int neckTwistMin;
    int neckTwistMax;
    int neckTwistMid;
    int neckTwistPin;
    int leftEyebrowMin;
    int leftEyebrowMax;
    int leftEyebrowMid;
    int leftEyebrowPin;
    int rightEyebrowMin;
    int rightEyebrowMax;
    int rightEyebrowMid;
    int rightEyebrowPin;
    int leftEyelidMin;
    int leftEyelidMax;
    int leftEyelidMid;
    int leftEyelidPin;
    int rightEyelidMin;
    int rightEyelidMax;
    int rightEyelidMid;
    int rightEyelidPin;

    int frontLastMeasurement;


    //Robot(Serial * serial);
    Robot();
    ~Robot();

    void Reset();

    int GetDistance();
    int GetDistance(VL53L0X_Dev_t pMyDevice, int* lastMeasurement);
    VL53L0X_Error printDistance(VL53L0X_Dev_t *pMyDevice);
    VL53L0X_Error vl53l0x_init(VL53L0X_Dev_t *pMyDevice, const char *);
    VL53L0X_Dev_t frontSensor;

    void SetServo(int pin, int val);
    void ResetServo(int pin, int val);
    void ResetServo(int pin);
    void ResetServo();
    void SetServo(Qt::CheckState state, int min, int max, int pin, int val);

    void SetState(int n_leftHorizontalEye, int n_leftVerticalEye, int n_rightHorizontalEye, int n_rightVerticalEye, int n_leftEyebrow, int n_rightEyebrow, int n_rightEyelid, int n_leftEyelid, int n_leftLip, int n_rightLip, int n_jaw, int n_neckTilt, int n_neckTwist);
    void SetExpression(QString name);
    void SetExpression(int e);
    void SetExpression();
    void SetMouth(QString shape);

    void SetLeft();
    void SetCentre();
    void SetRight();
    void SetNeck(int angle);

    void SpeakMessage(QString msg);
    void SpeakPhoneme(QString phoneme, QString msg);
    void SpeakWord(QString word);

};

#endif // ROBOT_H
