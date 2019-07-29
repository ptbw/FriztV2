#include "vl53l0x.h"

VL53L0X_Error WaitMeasurementDataReady(VL53L0X_DEV Dev) {
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    uint8_t NewDatReady=0;
    uint32_t LoopNb;

    // Wait until it finished
    // use timeout to avoid deadlock
    if (Status == VL53L0X_ERROR_NONE) {
        LoopNb = 0;
        do {
            Status = VL53L0X_GetMeasurementDataReady(Dev, &NewDatReady);
            if ((NewDatReady == 0x01) || Status != VL53L0X_ERROR_NONE) {
                break;
            }
            LoopNb = LoopNb + 1;
            VL53L0X_PollingDelay(Dev);
        } while (LoopNb < VL53L0X_DEFAULT_MAX_LOOP);

        if (LoopNb >= VL53L0X_DEFAULT_MAX_LOOP) {
            Status = VL53L0X_ERROR_TIME_OUT;
        }
    }

    return Status;
}


VL53L0X_Error WaitStopCompleted(VL53L0X_DEV Dev) {
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    uint32_t StopCompleted=0;
    uint32_t LoopNb;

    // Wait until it finished
    // use timeout to avoid deadlock
    if (Status == VL53L0X_ERROR_NONE) {
        LoopNb = 0;
        do {
            Status = VL53L0X_GetStopCompletedStatus(Dev, &StopCompleted);
            if ((StopCompleted == 0x00) || Status != VL53L0X_ERROR_NONE) {
                break;
            }
            LoopNb = LoopNb + 1;
            VL53L0X_PollingDelay(Dev);
        } while (LoopNb < VL53L0X_DEFAULT_MAX_LOOP);

        if (LoopNb >= VL53L0X_DEFAULT_MAX_LOOP) {
            Status = VL53L0X_ERROR_TIME_OUT;
        }

    }

    return Status;
}

int vl53l0x::GetDistance()
{
    VL53L0X_RangingMeasurementData_t    RangingMeasurementData;
    VL53L0X_RangingMeasurementData_t   *pRangingMeasurementData    = &RangingMeasurementData;
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;

    int result = 9999;
    if(Status == VL53L0X_ERROR_NONE)
    {
        Status = WaitMeasurementDataReady(pMyDevice);

        if(Status == VL53L0X_ERROR_NONE)
        {
            Status = VL53L0X_GetRangingMeasurementData(pMyDevice, pRangingMeasurementData);

            result = pRangingMeasurementData->RangeMilliMeter;


            // Clear the interrupt
            VL53L0X_ClearInterruptMask(pMyDevice, VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);
        }
    }
    printf("Measurement %d\n", result);
    return result;
}

void vl53l0x::PrintPalError(VL53L0X_Error Status)
{
    char buf[VL53L0X_MAX_STRING_LENGTH];
    VL53L0X_GetPalErrorString(Status, buf);
    printf("API Status: %i : %s\n", Status, buf);
}

vl53l0x::vl53l0x()
{
    int32_t status_int;

    uint32_t refSpadCount;
    uint8_t isApertureSpads;
    uint8_t VhvSettings;
    uint8_t PhaseCal;

    pMyDevice->I2cDevAddr      = 0x29;
    pMyDevice->fd = VL53L0X_i2c_init("/dev/i2c-1", pMyDevice->I2cDevAddr); //choose between i2c-0 and i2c-1; On the raspberry pi zero, i2c-1 are pins 2 and 3
    if (MyDevice.fd<0) {
           Status = VL53L0X_ERROR_CONTROL_INTERFACE;
           printf ("Failed to init\n");
    }
    if(Status == VL53L0X_ERROR_NONE)
    {
        status_int = VL53L0X_GetVersion(pVersion);
        if (status_int != 0)
            Status = VL53L0X_ERROR_CONTROL_INTERFACE;
    }

    /*
     *  Verify the version of the VL53L0X API running in the firmrware
     */
    if(Status == VL53L0X_ERROR_NONE)
    {
        if( pVersion->major != VERSION_REQUIRED_MAJOR ||
            pVersion->minor != VERSION_REQUIRED_MINOR ||
            pVersion->build != VERSION_REQUIRED_BUILD )
        {
            printf("VL53L0X API Version Error: Your firmware has %d.%d.%d (revision %d). This example requires %d.%d.%d.\n",
                pVersion->major, pVersion->minor, pVersion->build, pVersion->revision,
                VERSION_REQUIRED_MAJOR, VERSION_REQUIRED_MINOR, VERSION_REQUIRED_BUILD);
        }
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
        printf ("Call of VL53L0X_DataInit\n");
        Status = VL53L0X_DataInit(&MyDevice); // Data initialization
        PrintPalError(Status);
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
        Status = VL53L0X_GetDeviceInfo(&MyDevice, &DeviceInfo);
    }
    if(Status == VL53L0X_ERROR_NONE)
    {
        printf("VL53L0X_GetDeviceInfo:\n");
        printf("Device Name : %s\n", DeviceInfo.Name);
        printf("Device Type : %s\n", DeviceInfo.Type);
        printf("Device ID : %s\n", DeviceInfo.ProductId);
        printf("ProductRevisionMajor : %d\n", DeviceInfo.ProductRevisionMajor);
        printf("ProductRevisionMinor : %d\n", DeviceInfo.ProductRevisionMinor);

        if ((DeviceInfo.ProductRevisionMinor != 1) && (DeviceInfo.ProductRevisionMinor != 1)) {
            printf("Error expected cut 1.1 but found cut %d.%d\n",
                    DeviceInfo.ProductRevisionMajor, DeviceInfo.ProductRevisionMinor);
            Status = VL53L0X_ERROR_NOT_SUPPORTED;
        }
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
       printf ("Call of VL53L0X_StaticInit\n");
       Status = VL53L0X_StaticInit(pMyDevice); // Device Initialization
       // StaticInit will set interrupt by default
       PrintPalError(Status);
   }
   if(Status == VL53L0X_ERROR_NONE)
   {
       printf ("Call of VL53L0X_PerformRefCalibration\n");
       Status = VL53L0X_PerformRefCalibration(pMyDevice,
               &VhvSettings, &PhaseCal); // Device Initialization
       PrintPalError(Status);
   }

   if(Status == VL53L0X_ERROR_NONE)
   {
       printf ("Call of VL53L0X_PerformRefSpadManagement\n");
       Status = VL53L0X_PerformRefSpadManagement(pMyDevice,
               &refSpadCount, &isApertureSpads); // Device Initialization
       PrintPalError(Status);
   }

   if(Status == VL53L0X_ERROR_NONE)
   {

       printf ("Call of VL53L0X_SetDeviceMode\n");
       Status = VL53L0X_SetDeviceMode(pMyDevice, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING); // Setup in single ranging mode
       PrintPalError(Status);
   }

   if (Status == VL53L0X_ERROR_NONE)
   {
      Status = VL53L0X_SetLimitCheckValue(pMyDevice,
                  VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE,
                  (FixPoint1616_t)(0.1*65536));
   }

   if (Status == VL53L0X_ERROR_NONE)
   {
      Status = VL53L0X_SetLimitCheckValue(pMyDevice,
                  VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE,
                  (FixPoint1616_t)(60*65536));
    }

    if (Status == VL53L0X_ERROR_NONE)
    {
       Status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(pMyDevice, 33000);
    }

    if (Status == VL53L0X_ERROR_NONE)
    {
       Status = VL53L0X_SetVcselPulsePeriod(pMyDevice, VL53L0X_VCSEL_PERIOD_PRE_RANGE, 18);
    }

    if (Status == VL53L0X_ERROR_NONE)
    {
      Status = VL53L0X_SetVcselPulsePeriod(pMyDevice, VL53L0X_VCSEL_PERIOD_FINAL_RANGE, 14);
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
       printf ("Call of VL53L0X_StartMeasurement\n");
       Status = VL53L0X_StartMeasurement(pMyDevice);
       PrintPalError(Status);
    }
}

vl53l0x::~vl53l0x()
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;

    if(Status == VL53L0X_ERROR_NONE)
    {
        printf ("Call of VL53L0X_StopMeasurement\n");
        Status = VL53L0X_StopMeasurement(pMyDevice);
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
        printf ("Wait Stop to be competed\n");
        Status = WaitStopCompleted(pMyDevice);
    }

    if(Status == VL53L0X_ERROR_NONE)
        Status = VL53L0X_ClearInterruptMask(pMyDevice,
            VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);

    VL53L0X_i2c_close();
}
