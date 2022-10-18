#include "Standard_Library.h"
#include "System_Library.h"
extern "C" {
#include "BCM2835.h"
#include "PCA9685.h"
#include "Adafruit_ServoHAT.h"
}

#include "robot.h"

#define FREQUENCY 70
#define SERVOHATADDR 0x40
#define SERVOMIN 500
#define SENSOR_MAX 8192

Robot::Robot()
{    
    //int servo_min = 500;  // Min pulse length out of 4096

    //const int minPin = 0;
    //const int maxPin = 11;

    //float irValue = 1000.0f;
    //float sonarValue = 1000.0f;

    //cd = new CalibrationData();

    //RobotState initState = new RobotState();

//    leftHorizontalEye = f_leftHorizontalEye = initState.leftHorizontalEye;
//    leftVerticalEye = f_leftVerticalEye = initState.leftVerticalEye;
//    rightHorizontalEye = f_rightHorizontalEye = initState.rightHorizontalEye;
//    rightVerticalEye = f_rightVerticalEye = initState.rightVerticalEye;
//    leftEyebrow = f_leftEyebrow = initState.leftEyebrow;
//    rightEyebrow = f_rightEyebrow = initState.rightEyebrow;
//    rightEyelid = f_rightEyelid = initState.rightEyelid;
//    leftEyelid = f_leftEyelid = initState.leftEyelid;
//    leftLip = f_leftLip = initState.leftLip;
//    rightLip = f_rightLip = initState.rightLip;
//    jaw = f_jaw = initState.jaw;
//    neckTilt = f_neckTilt = initState.neckTilt;
//    neckTwist = f_neckTwist = initState.neckTwist;

    // Twist 0  	35 - 165
    // Neck 1  		80 - 100
    // Chin 2  		60 - 80
    // RLip 3  		30 - 120
    // LLip 4  		30 - 120
    // VLEye 5 		30 - 100
    // VREye 6 		30 - 100
    // HLEye 7 		30 - 100
    // HREye 8 		30 - 100
    // LEyelid 9 	40 - 90
    // REyelid 10  	40 - 90
    // LEyebrow 11 	30 - 100
    // REyebrow 12  30 - 100

    rightEyebrowMin = 30;
    rightEyebrowMax = 100;
    rightEyebrowMid = ((rightEyebrowMax - rightEyebrowMin)/2) + rightEyebrowMin;
    rightEyebrowPin = 12;

    leftEyebrowMin = 30;
    leftEyebrowMax = 100;
    leftEyebrowMid = ((leftEyebrowMax - leftEyebrowMin)/2) + leftEyebrowMin;
    leftEyebrowPin = 11;
    

    rightEyelidMin = 40;
    rightEyelidMax = 90;
    rightEyelidMid = ((rightEyelidMax - rightEyelidMin)/2) + rightEyelidMin;
    rightEyelidPin = 10;


    leftEyelidMin = 40;
    leftEyelidMax = 90;
    leftEyelidMid = ((leftEyelidMax - leftEyelidMin)/2) + leftEyelidMin;
    leftEyelidPin = 9;

    rightHorizontalEyeMin = 30;
    rightHorizontalEyeMax = 100;
    rightHorizontalEyeMid = ((rightHorizontalEyeMax - rightHorizontalEyeMin)/2) + rightHorizontalEyeMin;
    rightHorizontalEyePin = 8;

    leftHorizontalEyeMin = 30;
    leftHorizontalEyeMax = 100;
    leftHorizontalEyeMid = ((leftHorizontalEyeMax - leftHorizontalEyeMin)/2) + leftHorizontalEyeMin;
    leftHorizontalEyePin = 7;
    
    
    // RLip 3  		30 - 120
    // LLip 4  		30 - 120
    // VLEye 5 		30 - 100
    // VREye 6 		30 - 100

    leftVerticalEyeMin = 30;
    leftVerticalEyeMax = 100;
    leftVerticalEyeMid = ((leftVerticalEyeMax - leftVerticalEyeMin)/2) + leftVerticalEyeMin;
    leftVerticalEyePin = 6;

    rightVerticalEyeMin = 30;
    rightVerticalEyeMax = 100;
    rightVerticalEyeMid = ((rightVerticalEyeMax - rightVerticalEyeMin)/2) + rightVerticalEyeMin;
    rightVerticalEyePin = 5;

    rightLipMin = 30;
    rightLipMax = 120;
    rightLipMid = ((rightLipMax - rightLipMin)/2) + rightLipMin;
    rightLipPin = 4;

    leftLipMin = 30;
    leftLipMax = 120;
    leftLipMid = ((leftLipMax - leftLipMin)/2) + leftLipMin;
    leftLipPin = 3;

	// Twist 0  	35 - 165
    // Neck 1  		80 - 100
    // Chin 2  		60 - 80
    jawMin = 60;
    jawMax = 110;
    jawMid = ((jawMax - jawMin)/2) + jawMin;
    jawPin = 2;

    neckTiltMin = 80;
    neckTiltMax = 100;
    neckTiltMid = ((neckTiltMax - neckTiltMin)/2) + neckTiltMin;
    neckTiltPin = 1;

    neckTwistMin = 35;
    neckTwistMax = 165;
    neckTwistMid = 80;
    neckTwistPin = 0;

    map_peripheral_BCM2835(&gpio);
    map_peripheral_BCM2835(&bsc0);

    init_I2C_protocol();
    init_PCA9685(SERVOHATADDR);
    set_PWM_frequency_PCA9685(SERVOHATADDR, FREQUENCY);
    init_angle_to_pulse_length_lookup_table();

    set_servo(SERVOHATADDR, neckTwistPin, FREQUENCY, neckTwistMid);
    set_servo(SERVOHATADDR, neckTiltPin, FREQUENCY, neckTiltMid);
    set_servo(SERVOHATADDR, jawPin, FREQUENCY, jawMid);
    set_servo(SERVOHATADDR, leftLipPin, FREQUENCY, leftLipMid);
    set_servo(SERVOHATADDR, rightLipPin, FREQUENCY, rightLipMid);
    set_servo(SERVOHATADDR, leftVerticalEyePin, FREQUENCY, leftVerticalEyeMid);
    set_servo(SERVOHATADDR, rightVerticalEyePin, FREQUENCY, rightVerticalEyeMid);
    set_servo(SERVOHATADDR, leftHorizontalEyePin, FREQUENCY, leftHorizontalEyeMid);
    set_servo(SERVOHATADDR, rightHorizontalEyePin, FREQUENCY, rightHorizontalEyeMid);
    set_servo(SERVOHATADDR, leftEyelidPin, FREQUENCY, leftEyelidMid);
    set_servo(SERVOHATADDR, rightEyelidPin, FREQUENCY, rightEyelidMid);
    set_servo(SERVOHATADDR, leftEyebrowPin, FREQUENCY, leftEyebrowMid);
    set_servo(SERVOHATADDR, rightEyebrowPin, FREQUENCY, rightEyebrowMid);

    // Prime the distance sensor
    //ranger = new vl53l0x();
    VL53L0X_Error        Status = VL53L0X_ERROR_NONE;
    //VL53L0X_Dev_t        MyDevice;
    //VL53L0X_Dev_t        *pMyDevice = &MyDevice;
    //VL53L0X_Version_t    Version;
    //VL53L0X_Version_t    *pVersion   = &Version;
    //VL53L0X_DeviceInfo_t DeviceInfo;

    VL53L0X_Dev_t *pFrontSensor = &frontSensor;
    Status = vl53l0x_init(pFrontSensor,"/dev/i2c-1" );
    usleep(100000);

    VL53L0X_StartMeasurement(pFrontSensor);
    frontLastMeasurement = 0;

    int distance = GetDistance();
    qDebug() << "Distance: " << distance << " Status: " << Status;

}

Robot::~Robot()
{
    ResetServo();
    //delete ranger;
    VL53L0X_i2c_close();
}

void Robot::Reset()
{

}

VL53L0X_Error Robot::printDistance(VL53L0X_Dev_t *pMyDevice)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    VL53L0X_RangingMeasurementData_t    RangingMeasurementData;
    Status = VL53L0X_PerformSingleRangingMeasurement(pMyDevice,
                    &RangingMeasurementData);

    if (Status != VL53L0X_ERROR_NONE) return Status;

    qDebug() << "Measured distance: " << RangingMeasurementData.RangeMilliMeter;

    return Status;
}

VL53L0X_Error Robot::vl53l0x_init(VL53L0X_Dev_t *pMyDevice, const char * device)
{

    VL53L0X_Error Status = VL53L0X_ERROR_NONE;

    uint32_t refSpadCount;
    uint8_t isApertureSpads;
    uint8_t VhvSettings;
    uint8_t PhaseCal;

    pMyDevice->I2cDevAddr = 0x29;

    pMyDevice->fd = VL53L0X_i2c_init((char*) device, pMyDevice->I2cDevAddr);
    if (pMyDevice->fd<0) {
        Status = VL53L0X_ERROR_CONTROL_INTERFACE;
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
        Status = VL53L0X_DataInit(pMyDevice); // Data initialization
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
        Status = VL53L0X_StaticInit(pMyDevice); // Device Initialization
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
        Status = VL53L0X_PerformRefCalibration(pMyDevice,
                &VhvSettings, &PhaseCal); // Device Initialization
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
        Status = VL53L0X_PerformRefSpadManagement(pMyDevice,
                &refSpadCount, &isApertureSpads); // Device Initialization
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
        //Status = VL53L0X_SetDeviceMode(pMyDevice, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING); // Setup in continuous ranging mode
        Status = VL53L0X_SetDeviceMode(pMyDevice, VL53L0X_DEVICEMODE_SINGLE_RANGING);
    }

    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetLimitCheckEnable(pMyDevice,
                VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1);
    }
    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetLimitCheckEnable(pMyDevice,
                VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1);
    }

    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetLimitCheckEnable(pMyDevice,
                VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, 1);
    }

    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetLimitCheckValue(pMyDevice,
                VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE,
                (FixPoint1616_t)(0.1*65536));
    }
    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetLimitCheckValue(pMyDevice,
                VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE,
                (FixPoint1616_t)(60*65536));
    }
    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(pMyDevice,
                20000);
    }

//    if (Status == VL53L0X_ERROR_NONE) {
//        Status = VL53L0X_SetVcselPulsePeriod(pMyDevice,
//		        VL53L0X_VCSEL_PERIOD_PRE_RANGE, 18);
//    }
//    if (Status == VL53L0X_ERROR_NONE) {
//        Status = VL53L0X_SetVcselPulsePeriod(pMyDevice,
//		        VL53L0X_VCSEL_PERIOD_FINAL_RANGE, 14);
//   }
    return Status;
}

int Robot::GetDistance(VL53L0X_Dev_t sensor, int* last){

    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    VL53L0X_RangingMeasurementData_t    RangingMeasurementData;

    //Status = VL53L0X_GetRangingMeasurementData(&sensor, &RangingMeasurementData);

    Status = VL53L0X_PerformSingleRangingMeasurement(&sensor, &RangingMeasurementData);

    if (Status != VL53L0X_ERROR_NONE) return -1;

    int val = SENSOR_MAX;
    if(RangingMeasurementData.RangeMilliMeter >= 0 && RangingMeasurementData.RangeMilliMeter <= SENSOR_MAX)
    {
        val =  RangingMeasurementData.RangeMilliMeter;
    }

    *last = val;

    //if(*last != 0 && ((val - *last) > 300 || (val - *last) < -300)){
    //    return *last;
    //}

    return val;
}

int Robot::GetDistance()
{      
   return GetDistance(frontSensor, &frontLastMeasurement);
   //return ranger->GetDistance();
}

void Robot::SetServo(int pin, int angle)
{
    // qDebug() << "Pin: " << pin << "Angle: " << angle;
    set_servo(SERVOHATADDR, pin, FREQUENCY, angle);
}

void Robot::ResetServo(int pin, int angle)
{
    set_servo(SERVOHATADDR, pin, 0, angle);
}

void Robot::ResetServo(int pin)
{
    set_servo(SERVOHATADDR, pin, 0, 10);
}

void Robot::ResetServo()
{
    for(int pin = 0 ;pin < 16; pin++)
       ResetServo(pin);
}

void Robot::SetServo( Qt::CheckState state, int min, int max, int pin, int val)
{
    if(val < min || val > max || state != Qt::Checked)
    {
       ResetServo(pin, val < min ? min : max);
       return;
    }

    if(state == Qt::Checked)
    {
        //printf("Servo: %d, Value: %d", pin, val);
        SetServo(pin, val);
    }    
}


void Robot::SetMouth(QString shape)
{
   if(shape == "aaah")
    {
        SetServo(Qt::Checked, leftEyelidMin, leftEyelidMax, leftEyelidPin, 70 );
        SetServo(Qt::Checked, rightEyelidMin, rightEyelidMax, rightEyelidPin, 70 );
        SetServo(Qt::Checked, leftLipMin, leftLipMax, leftLipPin, 66 );
        SetServo(Qt::Checked, rightLipMin, rightLipMax, rightLipPin, 68 );
        SetServo(Qt::Checked, jawMin, jawMax, jawPin, 70);
    }
    else if(shape == "aa")
    {
        SetServo(Qt::Checked, leftEyelidMin, leftEyelidMax, leftEyelidPin, 70 );
        SetServo(Qt::Checked, rightEyelidMin, rightEyelidMax, rightEyelidPin, 70 );
        SetServo(Qt::Checked, leftLipMin, leftLipMax, leftLipPin, 50 );
        SetServo(Qt::Checked, rightLipMin, rightLipMax, rightLipPin, 80 );
        SetServo(Qt::Checked, jawMin, jawMax, jawPin, 30);
    }
    else if(shape == "i")
    {
        SetServo(Qt::Checked, leftEyelidMin, leftEyelidMax, leftEyelidPin, 70 );
        SetServo(Qt::Checked, rightEyelidMin, rightEyelidMax, rightEyelidPin, 70 );
        SetServo(Qt::Checked, leftLipMin, leftLipMax, leftLipPin, 88 );
        SetServo(Qt::Checked, rightLipMin, rightLipMax, rightLipPin, 44 );
        SetServo(Qt::Checked, jawMin, jawMax, jawPin, 64);
    }
    else if(shape == "laa")
    {
        SetServo(Qt::Checked, leftEyelidMin, leftEyelidMax, leftEyelidPin, 90 );
        SetServo(Qt::Checked, rightEyelidMin, rightEyelidMax, rightEyelidPin, 90 );
        SetServo(Qt::Checked, leftLipMin, leftLipMax, leftLipPin, 70 );
        SetServo(Qt::Checked, rightLipMin, rightLipMax, rightLipPin, 68 );
        SetServo(Qt::Checked, jawMin, jawMax, jawPin, 60);
    }
    else if(shape == "sss")
    {
        SetServo(Qt::Checked, leftEyelidMin, leftEyelidMax, leftEyelidPin, 70 );
        SetServo(Qt::Checked, rightEyelidMin, rightEyelidMax, rightEyelidPin, 70 );
        SetServo(Qt::Checked, leftLipMin, leftLipMax, leftLipPin, 46 );
        SetServo(Qt::Checked, rightLipMin, rightLipMax, rightLipPin, 92 );
        SetServo(Qt::Checked, jawMin, jawMax, jawPin, 90);
    }
    else if(shape == "eee")
    {
        SetServo(Qt::Checked, leftEyelidMin, leftEyelidMax, leftEyelidPin, 70 );
        SetServo(Qt::Checked, rightEyelidMin, rightEyelidMax, rightEyelidPin, 70 );
        SetServo(Qt::Checked, leftLipMin, leftLipMax, leftLipPin, 88 );
        SetServo(Qt::Checked, rightLipMin, rightLipMax, rightLipPin, 46 );
        SetServo(Qt::Checked, jawMin, jawMax, jawPin, 74);
    }
    else if(shape == "oh")
    {
        SetServo(Qt::Checked, leftEyelidMin, leftEyelidMax, leftEyelidPin, 90 );
        SetServo(Qt::Checked, rightEyelidMin, rightEyelidMax, rightEyelidPin, 90 );
        SetServo(Qt::Checked, leftLipMin, leftLipMax, leftLipPin,100 );
        SetServo(Qt::Checked, rightLipMin, rightLipMax, rightLipPin, 30 );
        SetServo(Qt::Checked, jawMin, jawMax, jawPin, 60);
    }
    else if(shape == "oooh")
    {
        SetServo(Qt::Checked, leftEyelidMin, leftEyelidMax, leftEyelidPin, 90 );
        SetServo(Qt::Checked, rightEyelidMin, rightEyelidMax, rightEyelidPin, 90 );
        SetServo(Qt::Checked, leftLipMin, leftLipMax, leftLipPin, 20 );
        SetServo(Qt::Checked, rightLipMin, rightLipMax, rightLipPin, 30 );
        SetServo(Qt::Checked, jawMin, jawMax, jawPin, 60);
    }
    else if(shape == "fuh")
    {
        SetServo(Qt::Checked, leftEyelidMin, leftEyelidMax, leftEyelidPin, 90 );
        SetServo(Qt::Checked, rightEyelidMin, rightEyelidMax, rightEyelidPin, 90 );
        SetServo(Qt::Checked, leftLipMin, leftLipMax, leftLipPin, 84 );
        SetServo(Qt::Checked, rightLipMin, rightLipMax, rightLipPin, 50 );
        SetServo(Qt::Checked, jawMin, jawMax, jawPin, 90);
    }
    else if(shape == "mmm")
    {
        SetServo(Qt::Checked, leftEyelidMin, leftEyelidMax, leftEyelidPin, 70 );
        SetServo(Qt::Checked, rightEyelidMin, rightEyelidMax, rightEyelidPin, 70 );
        SetServo(Qt::Checked, leftLipMin, leftLipMax, leftLipPin, 62);
        SetServo(Qt::Checked, rightLipMin, rightLipMax, rightLipPin, 80 );
        SetServo(Qt::Checked, jawMin, jawMax, jawPin, 100);
    }
    else
    {
        SetServo(Qt::Checked, leftEyelidMin, leftEyelidMax, leftEyelidPin, 70 );
        SetServo(Qt::Checked, rightEyelidMin, rightEyelidMax, rightEyelidPin, 70 );
        SetServo(Qt::Checked, leftLipMin, leftLipMax, leftLipPin, 62 );
        SetServo(Qt::Checked, rightLipMin, rightLipMax, rightLipPin, 92 );
        SetServo(Qt::Checked, jawMin, jawMax, jawPin, 100);
    }
}

void Robot::SetState(int n_leftHorizontalEye, int n_leftVerticalEye, int n_rightHorizontalEye, int n_rightVerticalEye, int n_leftEyebrow, int n_rightEyebrow, int n_rightEyelid, int n_leftEyelid, int n_leftLip, int n_rightLip, int n_jaw, int n_neckTilt, int n_neckTwist)
{
    if (n_leftEyebrow != -1) SetServo(Qt::Checked, leftEyebrowMin, leftEyebrowMax,leftEyebrowPin, n_leftEyebrow );
    if (n_rightEyebrow != -1) SetServo(Qt::Checked, rightEyebrowMin, rightEyebrowMax, rightEyebrowPin, n_rightEyebrow );
    if (n_leftEyelid != -1) SetServo(Qt::Checked, leftEyelidMin, leftEyelidMax, leftEyelidPin, n_leftEyelid );
    if (n_rightEyelid != -1) SetServo(Qt::Checked, rightEyelidMin, rightEyelidMax, rightEyelidPin, n_rightEyelid );
    if (n_leftHorizontalEye != -1) SetServo(Qt::Checked, leftHorizontalEyeMin, leftHorizontalEyeMax, leftHorizontalEyePin, n_leftHorizontalEye );
    if (n_rightHorizontalEye != -1) SetServo(Qt::Checked, rightHorizontalEyeMin, rightHorizontalEyeMax, rightHorizontalEyePin, n_rightHorizontalEye );
    if (n_leftVerticalEye != -1) SetServo(Qt::Checked, leftVerticalEyeMin, leftVerticalEyeMax, leftVerticalEyePin, n_leftVerticalEye );
    if (n_rightVerticalEye != -1) SetServo(Qt::Checked, rightVerticalEyeMin, rightVerticalEyeMax, rightVerticalEyePin, n_rightVerticalEye );
    if (n_leftLip != -1) SetServo(Qt::Checked, leftLipMin, leftLipMax, leftLipPin, n_leftLip );
    if (n_rightLip != -1) SetServo(Qt::Checked, rightLipMin, rightLipMax, rightLipPin, n_rightLip );
    if (n_neckTwist != -1) SetServo(Qt::Checked, neckTwistMin, neckTwistMax, neckTwistPin, n_neckTwist );
    if (n_neckTilt != -1) SetServo(Qt::Checked, neckTiltMin, neckTiltMax, neckTiltPin, n_neckTilt );
    if (n_jaw != -1) SetServo(Qt::Checked, jawMin, jawMax, jawPin, n_jaw );
    I::msleep(500);
    ResetServo();
}

void Robot::SetExpression(QString name)
{    
    // qDebug() << "Set Expression: " << name;
    if (name == "Afraid")
        SetState(70 /*leftHorizontalEye*/, 65 /*leftVerticalEye*/, 70 /*rightHorizontalEye*/, 65 /*rightVerticalEye*/, 55 /*leftEyebrow*/, 95 /*rightEyebrow*/, 70 /*rightEyelid*/, 70 /*leftEyelid*/, 40 /*leftLip*/, 90 /*rightLip*/, 20 /*jaw*/, -1 /*neckTilt*/, -1 /*neckTwist*/);
    else if (name == "Awkward")
        SetState(70 /*leftHorizontalEye*/, 65 /*leftVerticalEye*/, 70 /*rightHorizontalEye*/, 48 /*rightVerticalEye*/, 40 /*leftEyebrow*/, 100 /*rightEyebrow*/, 90 /*rightEyelid*/, 90 /*leftEyelid*/, 80 /*leftLip*/, 60 /*rightLip*/, 50 /*jaw*/, 50 /*neckTilt*/, -1 /*neckTwist*/);
    else if (name == "Angry")
        SetState(70 /*leftHorizontalEye*/, 65 /*leftVerticalEye*/, 70 /*rightHorizontalEye*/, 48 /*rightVerticalEye*/, 90 /*leftEyebrow*/, 40 /*rightEyebrow*/, 65 /*rightEyelid*/, 70 /*leftEyelid*/, 20 /*leftLip*/, 40 /*rightLip*/, 120 /*jaw*/, 33 /*neckTilt*/, -1 /*neckTwist*/);
    else if (name == "Disappointed")
        SetState(90 /*leftHorizontalEye*/, 90 /*leftVerticalEye*/, 90 /*rightHorizontalEye*/, 40 /*rightVerticalEye*/, 40 /*leftEyebrow*/, 100 /*rightEyebrow*/, 90 /*rightEyelid*/, 90 /*leftEyelid*/, 40 /*leftLip*/, 100 /*rightLip*/, 90 /*jaw*/, 17 /*neckTilt*/, -1 /*neckTwist*/);
    else if (name == "Happy")
        SetState(80 /*leftHorizontalEye*/, 90 /*leftVerticalEye*/, 90 /*rightHorizontalEye*/, 40 /*rightVerticalEye*/, 60 /*leftEyebrow*/, 80 /*rightEyebrow*/,
                 70 /*rightEyelid*/,70 /*leftEyelid*/, 40 /*leftLip*/, 100 /*rightLip*/, 75 /*jaw*/, 50 /*neckTilt*/, -1 /*neckTwist*/);


    else if (name == "Neutral")
        SetState(80 /*leftHorizontalEye*/, 65 /*leftVerticalEye*/, 70 /* rightHorizontalEye*/, 65 /*rightVerticalEye*/, 70 /*leftEyebrow*/, 80 /*rightEyebrow*/, 70 /*rightEyelid*/, 70 /*leftEyelid*/, 75 /*leftLip*/, 65 /*rightLip*/, 130 /*jaw*/, -1 /*neckTilt*/, -1 /*neckTwist*/);

    else if (name == "Sad")    
        SetState(90 /*leftHorizontalEye*/, 90 /*leftVerticalEye*/, 90 /*rightHorizontalEye*/, 40 /*rightVerticalEye*/, 40 /*leftEyebrow*/, 100 /*rightEyebrow*/,
                 90 /*rightEyelid*/, 90 /*leftEyelid*/, 40 /*leftLip*/, 100 /*rightLip*/, 90 /*jaw*/, 17 /*neckTilt*/, -1 /*neckTwist*/);

    else if (name == "Sinister")
        SetState(90 /*leftHorizontalEye*/, 80 /*leftVerticalEye*/, 90 /*rightHorizontalEye*/, 60 /*rightVerticalEye*/, 50 /*leftEyebrow*/, 90 /*rightEyebrow*/,
                 60 /*rightEyelid*/, 70 /*leftEyelid*/, 90 /*leftLip*/, 60 /*rightLip*/, 120 /*jaw*/, 50 /*neckTilt*/, -1.0 /*neckTwist*/);

    else if (name == "Sleepy")
        SetState(90 /*leftHorizontalEye*/, 80 /*leftVerticalEye*/, 90 /*rightHorizontalEye*/, 60 /*rightVerticalEye*/, 40 /*leftEyebrow*/, 100 /*rightEyebrow*/,
                 55 /*rightEyelid*/, 60 /*leftEyelid*/, 50 /*leftLip*/, 80 /*rightLip*/, 120 /*jaw*/, 30 /*neckTilt*/, -1.0 /*neckTwist*/);

    else if (name == "Smile")
        SetState(80 /*leftHorizontalEye*/, 90 /*leftVerticalEye*/, 90 /*rightHorizontalEye*/, 40 /*rightVerticalEye*/, 60 /*leftEyebrow*/, 80 /*rightEyebrow*/,
                 70 /*rightEyelid*/,70 /*leftEyelid*/, 40 /*leftLip*/, 100 /*rightLip*/, 75 /*jaw*/, 50 /*neckTilt*/, -1 /*neckTwist*/);

    else if (name == "Sneaky")
        SetState(70 /*leftHorizontalEye*/, 30 /*leftVerticalEye*/, 70 /*rightHorizontalEye*/, 30 /*rightVerticalEye*/, 58 /*leftEyebrow*/, 51 /*rightEyebrow*/, 26 /*rightEyelid*/, 26 /*leftEyelid*/, 0 /*leftLip*/, 0 /*rightLip*/, 92/*jaw*/, 50 /*neckTilt*/, -1.0 /*neckTwist*/);

    else if (name == "Sulk")
        SetState(70 /*leftHorizontalEye*/, 60 /*leftVerticalEye*/, 70 /*rightHorizontalEye*/, 61 /*rightVerticalEye*/, 33 /*leftEyebrow*/, 32 /*rightEyebrow*/, 76 /*rightEyelid*/, 76 /*leftEyelid*/, 17 /*leftLip*/, 36 /*rightLip*/, 0 /*jaw*/, 50 /*neckTilt*/, -1.0 /*neckTwist*/);

    else if (name == "Surprised")
        SetState(80 /*leftHorizontalEye*/, 80 /*leftVerticalEye*/, 80 /*rightHorizontalEye*/, 60 /*rightVerticalEye*/,
                 96 /*leftEyebrow*/, 46 /*rightEyebrow*/, 90 /*rightEyelid*/, 90 /*leftEyelid*/, 100 /*leftLip*/, 40 /*rightLip*/,
                 60 /*jaw*/, 50 /*neckTilt*/, -1.0 /*neckTwist*/);

    else if (name == "Yelling")
        SetState(70 /*leftHorizontalEye*/, 50 /*leftVerticalEye*/, 70 /*rightHorizontalEye*/, 50 /*rightVerticalEye*/,
                 10 /*leftEyebrow*/, 9 /*rightEyebrow*/, 40 /*rightEyelid*/, 4 /*leftEyelid*/, 22 /*leftLip*/, 77 /*rightLip*/,
                 100 /*jaw*/, 33 /*neckTilt*/, -1.0 /*neckTwist*/);

    else if (name == "Worried")
        SetState(80 /*leftHorizontalEye*/, 100 /*leftVerticalEye*/, 80 /*rightHorizontalEye*/, 50 /*rightVerticalEye*/, 40 /*leftEyebrow*/, 100 /*rightEyebrow*/, 110 /*rightEyelid*/, 110 /*leftEyelid*/, 50 /*leftLip*/, 90 /*rightLip*/, 50 /*jaw*/, 67 /*neckTilt*/, -1.0 /*neckTwist*/);

    else /* Normal */
        SetState(70 /*leftHorizontalEye*/, 65 /*leftVerticalEye*/, 70 /* rightHorizontalEye*/, 65 /*rightVerticalEye*/, 70 /*leftEyebrow*/, 80 /*rightEyebrow*/, 70 /*rightEyelid*/, 70 /*leftEyelid*/, 75 /*leftLip*/, 65 /*rightLip*/, 130 /*jaw*/, -1 /*neckTilt*/, 85 /*neckTwist*/);

    //EditState(GetFinalState());
}

void Robot::SetExpression(int e)
{   
    if (e == 0) SetExpression("Afraid");
    else if (e == 1) SetExpression("Awkward");
    else if (e == 2) SetExpression("Angry");
    else if (e == 3) SetExpression("Disappointed");
    else if (e == 4) SetExpression("Happy");
    else if (e == 5) SetExpression("Neutral");
    else if (e == 6) SetExpression("Sad");
    else if (e == 7) SetExpression("Sinister");
    else if (e == 8) SetExpression("Sleepy");
    else if (e == 9) SetExpression("Smile");
    else if (e == 10) SetExpression("Sneaky");
    else if (e == 11) SetExpression("Sulk");
    else if (e == 12) SetExpression("Surprised");
    else if (e == 13) SetExpression("Yelling");
    else if (e == 14) SetExpression("Worried");
    else
        SetExpression("Neutral");
}

void Robot::SetExpression()
{
    int value = (int)(qrand() % 15);
    SetExpression(value);    
}

//SetState(int n_leftHorizontalEye, int n_leftVerticalEye, int n_rightHorizontalEye, int n_rightVerticalEye, int n_leftEyebrow, int n_rightEyebrow, int n_rightEyelid, int n_leftEyelid, int n_leftLip, int n_rightLip, int n_jaw, int n_neckTilt, int n_neckTwist);
void Robot::SetLeft()
{
    SetState(90 /*leftHorizontalEye*/, 90 /*leftVerticalEye*/, 60 /* 50 rightHorizontalEye*/, 10 /* 50 rightVerticalEye*/, 100 /*leftEyebrow*/, 30 /*rightEyebrow*/, 90 /*rightEyelid*/, 90 /*leftEyelid*/, 80 /*leftLip*/, 80 /*rightLip*/, 100 /*jaw*/, -1 /*neckTilt*/, 30/*neckTwist*/);
}

void Robot::SetCentre()
{
    SetState(90 /*leftHorizontalEye*/, 90 /*leftVerticalEye*/, 130 /* 50 rightHorizontalEye*/, 50 /* 50 rightVerticalEye*/, 100 /*leftEyebrow*/, 30 /*rightEyebrow*/, 90 /*rightEyelid*/, 90 /*leftEyelid*/, 80 /*leftLip*/, 80 /*rightLip*/, 100 /*jaw*/, -1 /*neckTilt*/, 90/*neckTwist*/);
}

void Robot::SetRight()
{
    SetState(90 /*leftHorizontalEye*/, 90 /*leftVerticalEye*/, 60 /* 50 rightHorizontalEye*/, 10 /* 50 rightVerticalEye*/, 100 /*leftEyebrow*/, 30 /*rightEyebrow*/, 50 /*rightEyelid*/, 90 /*leftEyelid*/, 80 /*leftLip*/, 80 /*rightLip*/, 100 /*jaw*/, -1 /*neckTilt*/, 150/*neckTwist*/);
}

void Robot::SetNeck(int angle)
{
    SetState( -1 /*leftHorizontalEye*/, -1 /*leftVerticalEye*/, -1 /* rightHorizontalEye*/, -1 /* rightVerticalEye*/, -1 /*leftEyebrow*/, -1 /*rightEyebrow*/, -1 /*rightEyelid*/, -1 /*leftEyelid*/, -1 /*leftLip*/, -1 /*rightLip*/, -1 /*jaw*/, -1 /*neckTilt*/, angle/*neckTwist*/);
}

void Robot::SpeakMessage(QString msg)
{
    //SpeakWord(msg);
    //return;

    QStringList words = msg.split(QRegExp("[,.]"),QString::SkipEmptyParts);
    QStringListIterator iterator(words);
    while (iterator.hasNext())
    {
       SpeakWord(iterator.next());
       I::msleep(100);
    }
    ResetServo();
}

void Robot::SpeakWord(QString msg)
{
    Speak speak;

    QStringList phons = speak.TextToPhon(msg);
    speak.TextToSpeech(msg);

    QStringListIterator iterator(phons);
    while (iterator.hasNext())
    {
        QString shape = speak.GetMouthShape(iterator.next());
        SetMouth(shape);
        I::msleep(60);
    }
}

void Robot::SpeakPhoneme(QString phoneme, QString msg)
{
    Speak speak;

    SetMouth(phoneme);
    speak.TextToSpeech(msg);
    I::msleep(120);
    ResetServo();
}


