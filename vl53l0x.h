#ifndef VL53L0X_H
#define VL53L0X_H

#include "VL53L0X_Rasp/vl53l0x_api.h"
#include "VL53L0X_Rasp/vl53l0x_platform.h"

#define VERSION_REQUIRED_MAJOR 1
#define VERSION_REQUIRED_MINOR 0
#define VERSION_REQUIRED_BUILD 2

class vl53l0x
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;    
    VL53L0X_Dev_t MyDevice;
    VL53L0X_Dev_t *pMyDevice = &MyDevice;
    VL53L0X_Version_t                   Version;
    VL53L0X_Version_t                  *pVersion   = &Version;
    VL53L0X_DeviceInfo_t                DeviceInfo;


public:
    vl53l0x();
    ~vl53l0x();

    int GetStatus();
    int GetDistance();
    void PrintPalError(VL53L0X_Error Status);
};

#endif // VL53L0X_H
