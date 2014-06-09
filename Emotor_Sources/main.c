/**
  ******************************************************************************
  * @file    main.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * DESCRIPTION....
  *
  * <h2><center>&copy; COPYRIGHT 2012 Dynapack</center></h2>
  */

//==============================================================================
// Includes
//==============================================================================
#include "Driver_User_Interface.h"
#include "Global_Variable_Define.h"
#include "Vars_Bits_Define.h"
#include "Config_Info\System_Config_Info.h"

//#include "SOC\SOC_With_Temperature_Calculation.h"

//==============================================================================
// Global/Extern variables
//==============================================================================

//==============================================================================
// Extern functions
//==============================================================================
extern unsigned int FirstInitial_Func(void);
extern unsigned int Startup_Func(void);
extern unsigned int Normal_Func(void);
//extern unsigned int Failure_Func(void);
extern unsigned int Shutdown_Func(void);
//extern unsigned int Shipping_Func(void);
extern unsigned int Calibration_Func(void);
extern unsigned int Sleeping_AutoWakeup_Func(void);
//==============================================================================
// Private typedef
//==============================================================================
//==============================================================================
// Private define
//==============================================================================
//==============================================================================
// Private macro
//==============================================================================
//==============================================================================
// Private Enum
//==============================================================================
//==============================================================================
// Private variables
//==============================================================================
//==============================================================================
// Private function prototypes
//==============================================================================

//==============================================================================
// Private functions
//==============================================================================
//unsigned char ucharV1;
//signed char charV1;
//unsigned int uintV1;
//unsigned long ulongV1;
//float floatV1;
void main(){

    G_SysModeStatusCode = FirstInitial_Func();


//    GPIO_HIGH(LED1_PORT, LED1_PIN);
//    GPIO_LOW(LED1_PORT, LED1_PIN);
//    GPIO_TOGGLE(LED1_PORT, LED1_PIN);

//    _Device_delay_cycles(5000);     //5000 = 52ms at CCLK=4MHz.
//    _Device_delay_cycles(500);     //500 = 5ms at CCLK=4MHz.
//    _Device_delay_cycles(200);     //200 = 2ms at CCLK=4MHz.
//    _Device_delay_cycles(100);     //100 = 1ms at CCLK=2MHz.

    _DUI_delay_cycles(5000);    //5000 = 52ms at CCLK=4MHz.
    _DUI_delay_cycles(500);     //500 = 5ms at CCLK=4MHz.
    _DUI_delay_cycles(200);     //200 = 2ms at CCLK=4MHz.
    _DUI_delay_cycles(100);     //100 = 1ms at CCLK=2MHz.

    _DUI_delay_cycles(10000);   //10000 = 53ms at CCLK=8MHz.
    _DUI_delay_cycles(1000);    //1000 = 5.38ms at CCLK=8MHz.
    _DUI_delay_cycles(500);     //500 = 2.6ms at CCLK=8MHz.
    _DUI_delay_cycles(100);     //100 = 550us at CCLK=8MHz.
	while (1){
		
		switch (G_SysModeStatusCode)
		{
			case StartUp:
				G_SysModeStatusCode = Startup_Func();
				break;
			
			case NormalMode:
				G_SysModeStatusCode = Normal_Func();
//                DisableTimerFunction();
//                stopAdcConversion();
//                DisableAWUTimerFunction();
				//Coulomb Counter Stop
				//G_Activate_Action_Status &= ~ACCUMULATING_Q_ENABLE;
				//WriteCoulombCounterDataToFlash();
				break;
			
			case FailureMode:
				//G_SysModeStatusCode = Failure_Func();
				//break;
			
			case ShutdownMode:
				G_SysModeStatusCode = Shutdown_Func();
				break;


            case Sleeping_AutoWakeupMode:
                G_SysModeStatusCode = Sleeping_AutoWakeup_Func();
                break;
			
			case CalibrationMode:
				//G_SysModeStatusCode = Calibration_Func();
				//break;
            case ShippingMode:
                //G_SysModeStatusCode = Shipping_Func();
                //break;
			default:
                G_SysModeStatusCode = StartUp;
                break;
		}//switch()
    }//while(1)


}


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
