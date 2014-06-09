/**
  ******************************************************************************
  * @file    Current_Count_SOC_Function.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   Current count for Timer to calling
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
//#include "Driver_User_Interface.h"
//#include "Global_Variable_Define.h"
//#include "Vars_Bits_Define.h"
//#include "Config_Info\System_Config_Info.h"
//#include "Protection_Polling_Func.h"
//#include "SOC\SOC_With_Temperature_Calculation.h"

#include "Current_Count_SOC_Function.h"

//==============================================================================
// Global/Extern variables
//==============================================================================

#if 0
//==============================================================================
// Extern functions
//==============================================================================
//==============================================================================
// Private typedef
//==============================================================================
//==============================================================================
// Private define
//==============================================================================
#define Current_Count_Polling_Interval_Time_Base_MS          TimerIntervalTimeBase_MS   // 100 ms

///////////////////////////////////////////////////////////////////////////////////
///* G_Currnet_Count_Bits_Status Bits */
///* For G_Currnet_Count_Bits_Status ; unsigned int */
//Low byte
//#define no_used              (0x0001)    //
//#define no_used                      (0x0002)    //
//#define no_used        (0x0004)    //
//#define no_used     (0x0008)    //
//#define no_used                     (0x0010)    //
//#define no_used                         (0x0020)    //
//#define no_used                      (0x0040)    //
//#define no_used       (0x0080)    //
//High byte
//#define no_used                       (0x0100)    //
//#define no_used                        (0x0200)    //
//#define no_used            (0x0400)    //
//#define no_used     (0x0800)    //
//#define no_used       (0x1000)    //
//#define no_used       (0x2000)    //
//#define no_used       (0x4000)    //
//#define no_used       (0x8000)    //

////////////////////////////////////////////////////////////////////////////////
// For_CoulombCounter
#define _500mS_CycleTimes_For_CurrentCount         5  //unit:cycles , 500 ms = _500mS_CycleTimes_For_CurrentCount * TimerIntervalTimeBase_MS
#define _1000mS_CycleTimes_For_CurrentCount        10  //unit:cycles , 1000 ms = _1000mS_CycleTimes_For_CurrentCount * TimerIntervalTimeBase_MS

//==============================================================================
// Private macro
//==============================================================================
//==============================================================================
// Private Enum
//==============================================================================
//==============================================================================
// Private variables
//==============================================================================
unsigned int G_Currnet_Count_Bits_Status;

static unsigned char _500mS_Counter;
static unsigned char _1000mS_Counter;
unsigned long ADC_DSG_AccumulatingQ_500ms;
unsigned long ADC_CHG_AccumulatingQ_500ms;
unsigned long ADC_DSG_AccumulatingQ_1000ms;
unsigned long ADC_CHG_AccumulatingQ_1000ms;
//==============================================================================
// Private function prototypes
//==============================================================================
void CoulombCounterFor500MS(void);
void CoulombCounterFor1000MS(void);
//==============================================================================
// Private functions
//==============================================================================


//==============================================================================
// Public functions
//==============================================================================
void InitCurrentCountFuncVariables(void){
    _500mS_Counter = 0;
    _1000mS_Counter = 0;
    
    ADC_DSG_AccumulatingQ_500ms = 0;
    ADC_CHG_AccumulatingQ_500ms = 0;
    ADC_DSG_AccumulatingQ_1000ms = 0;
    ADC_CHG_AccumulatingQ_1000ms = 0;
}//void InitCurrentCountFuncVariables(void){


void Current_Count_Timer_Polling_Func_In_Interrupt(){
    
    ////////////////////////////////////////////////////////////////////////////
    // For Coulomb Counter
    if(_500mS_Counter >= _500mS_CycleTimes_For_CurrentCount){
        _500mS_Counter = 0;
        CoulombCounterFor500MS();
    }else{
        _500mS_Counter++;
    }
    ////////////////////////////////////////////////////////////////////////////
    // For Coulomb Counter
    if(_1000mS_Counter >= _1000mS_CycleTimes_For_CurrentCount){
        _1000mS_Counter = 0;
        CoulombCounterFor1000MS();
    }else{
        _1000mS_Counter++;
    }
}//void Current_Count_Timer_Polling_Func_In_Interrupt(){
    



void CoulombCounterFor500MS(void){
    if( G_Module_Status & Current_Dir_CHG){
        ADC_CHG_AccumulatingQ_500ms += G_CHG_Current_ADC;
    }else{
        if( G_Module_Status & Current_Dir_DSG){
            ADC_DSG_AccumulatingQ_500ms += G_DSG_Current_ADC;
        }
    }
}


void CoulombCounterFor1000MS(void){
    if( G_Module_Status & Current_Dir_CHG){
        ADC_CHG_AccumulatingQ_1000ms += G_CHG_Current_ADC;
    }else{
        if( G_Module_Status & Current_Dir_DSG){
            ADC_DSG_AccumulatingQ_1000ms += G_DSG_Current_ADC;
        }
    }
}


#endif