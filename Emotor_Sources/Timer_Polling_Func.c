

/********************************************************************************
* Include																		*
********************************************************************************/
#include "Driver_User_Interface.h"
#include "Global_Variable_Define.h"
#include "Vars_Bits_Define.h"
#include "Config_Info\System_Config_Info.h"
#include "Protection_Polling_Func.h"


//#include "Global_config.h"
//#include "Module_Driver_Define.h"
//#include "SystemInformation\User_Define_Parser.h"
//#include "Module_Variable_Define.h"
//#include "Module_Var_Bit_Define.h"
//#include "DefinePollingFunctions.h"


/********************************************************************************
* Define	                                                                    *
********************************************************************************/

/********************************************************************************
* Extern Function																*
********************************************************************************/
/********************************************************************************
* Current File Define Function													*
********************************************************************************/
//void GetCurrentValuesAndDirection();

/********************************************************************************
* Extern Variable																*
********************************************************************************/

/********************************************************************************
* Golbal Variable																*
********************************************************************************/


/********************************************************************************
* Local file Variable										                    *
********************************************************************************/
//static unsigned char LED_Blink_inverse_Flag;
//static unsigned char LED_PWM_One_step_Cycle_Counter;
//static unsigned char LED_PWM_Steps;
static unsigned char ButtonPressCounter;
static unsigned char DOC_ReleaseCounter;
static unsigned char COC_ReleaseCounter;
static unsigned char COC_ReleaseHoldingCounter;
static unsigned char System_1_Sec_Flag_Counter;
static unsigned char ButtonMultiPressCounter;
static unsigned char ONE_WIRE_Enable_Temporary_Counter;
//////////////////////////////////
//static unsigned char AUX1_Settting_CycleTimes;
//static unsigned char AUX1_Counter;
//////////////////////////////////

/********************************************************************************
* 															                    *
********************************************************************************/
void InitTimerPollingVariables(){

//    LED_PWM_One_step_Cycle_Counter = 0;
//    LED_PWM_Steps = 0;
//    LED_Blink_inverse_Flag = 0;
//
    ButtonPressCounter = 0;
    DOC_ReleaseCounter = 0;
    COC_ReleaseCounter = 0;
    COC_ReleaseHoldingCounter = 0;
    System_1_Sec_Flag_Counter = 0;
    ButtonMultiPressCounter = 0;

    ONE_WIRE_Enable_Temporary_Counter = 0;


//
//
//    //////////////////////////
//    AUX1_Settting_CycleTimes = 0;
//    AUX1_Counter = 0;
//    InitTimerFunction();
//    Set_Interrupt_Timer_Calling_Function(1, TimerCounterForPolling);

}
/********************************************************************************
* 															                    *
********************************************************************************/
//void Set_IntoHaltModeDelay_Counter_Cycles(unsigned char cycles){
//    AUX1_Settting_CycleTimes = cycles;
//    G_Add_Device_Interface_Status &= ~ENABLE_AUX1_COUNTER;
//    G_Add_Device_Interface_Status &= ~AUX1_COUNTING_FINISH;
//}
//void Recount_IntoHaltModeDelay_Counter(){
//    AUX1_Counter = 0;
//    G_Add_Device_Interface_Status &= ~AUX1_COUNTING_FINISH;
//}
/********************************************************************************
* 															                    *
********************************************************************************/

void Timer_Counter_For_Polling(){
//    GPIO_TOGGLE(LED1_PORT, LED1_PIN);
//    GPIO_HIGH(LED1_PORT, LED1_PIN);

//    if(temp == 0){
//        SetLed_DirectIO_OnOff(LED1, TurnOn);
//    }else{
//        SetLed_DirectIO_OnOff(LED1, TurnOff);
//    }
//    temp ^= 0x01;
    //return;


//    unsigned temp_char1, temp_char2;
//    //////////////////////////////////////////////////////////////////////////
//    //get LED PWM bit Flag  : (section start)
//    temp_char1 = (unsigned char)(G_LED_Interface_Status2 >> 8);
//    if(temp_char1 > 0){
//        if(LED_PWM_One_step_Cycle_Counter >=LED_PWM_One_Step_CycleTimes){
//            LED_PWM_One_step_Cycle_Counter = 0;
//            SetLedPWM20Steps(LED_PWM_Steps);
//            LED_PWM_Steps++;
//            if(LED_PWM_Steps > LED_PWM_Whole_Steps){
//                LED_PWM_Steps = 0;
//                SetLedPWMFunction(temp_char1, TurnOff);
//            }
//        }else{
//            LED_PWM_One_step_Cycle_Counter++;
//        }
//    }else{
//        LED_PWM_Steps = 0;
//        LED_PWM_One_step_Cycle_Counter = 0;
//    }
//    //get LED PWM bit Flag  : (section stop)
//    //////////////////////////////////////////////////////////////////////////

//    //////////////////////////////////////////////////////////////////////////
//    //get LED Blink Flag  : (section start)
//    temp_char2 = (unsigned char)G_LED_Interface_Status2;
//    temp_char2 = temp_char2 & (~temp_char1);   //and with mask PWM to get blink bits
//    //Blinking
//    if(temp_char2 > 0){
//        if(LED_Blink_inverse_Flag == 0){
//            SetLed_DirectIO_BITs(temp_char2);
//        }else{
//            SetLed_DirectIO_BITs(0);
//        }
//        LED_Blink_inverse_Flag ^= 0x01;
//    }
//    //get LED Blink Flag  : (section stop)
//    //////////////////////////////////////////////////////////////////////////
//
//    //////////////////////////////////////////////////////////////////////////
//    //get light on flag excluding PWM and Blink flag  : (section start)
//    temp_char1 = (unsigned char)(G_LED_Interface_Status2 >> 8); // get PWM bits
//    temp_char2 = (unsigned char)G_LED_Interface_Status2;        // get Blink bits
//    temp_char1 = ~(temp_char1 | temp_char2);    //OR with PWM and Blink to mask
//    temp_char2 = (unsigned char)(G_LED_Interface_Status1 >> 8); // get light on bits
//    temp_char2 = temp_char1 & temp_char2;
//    SetLed_DirectIO_BITs(temp_char2);
////    if(temp_char2 > 0){
////        SetLed_DirectIO_BITs(temp_char2);
////    }else{
////        SetLed_DirectIO_BITs(0);
////    }
//    //get light on flag excluding PWM and Blink flag  : (section stop)
//    //////////////////////////////////////////////////////////////////////////


//    //////////////////////////////////////////////////////////////////////////
//    //LED PWM Breathing_Light  : (section start)
//    if(G_Add_Module_Function_Status & Breathing_Light_FINISH){
//        Finish_Display_Breathing_Light_And_Timer();
//        G_Add_Module_Function_Status &= ~Breathing_Light_FINISH;
//    }
//
//    //LED PWM Breathing_Light  : (section stop)
//    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //Button  : (section start)
    if(G_Add_Module_Function_Status & BUTTON_PRESS){
        if(_DUI_GetButtonStatus() == ButtonPress){
            if(ButtonPressCounter >= Button_Long_Press_CycleTimes){
                G_Add_Module_Function_Status |= BUTTON_LONG_PRESS;
                G_Add_Module_Function_Status &= ~BUTTON_PRESS;
                ButtonPressCounter = 0;
            }else{
                ButtonPressCounter++;
            }
        }else{
            if(ButtonPressCounter <= Button_Click_CycleTimes){
                G_Add_Module_Function_Status |= BUTTON_CLICK;
                G_Add_Module_Function_Status |= BUTTON_CLICK_For_COC_LOCK;
            }
            G_Add_Module_Function_Status &= ~BUTTON_PRESS;
            ButtonPressCounter = 0;
        }
    }
    if(G_Add_Module_Function_Status & ENABLE_MULTI_CLICK_COUNTER){
        ButtonMultiPressCounter++;
        if(ButtonMultiPressCounter >= Button_MultiClick_DetectionCycleTimes){
            G_Add_Module_Function_Status &= ~ENABLE_MULTI_CLICK_COUNTER;
            ButtonMultiPressCounter = 0;
        }
    }else{
        ButtonMultiPressCounter = 0;
    }
    //Button  : (section stop)
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //DOC Counter : (section start)
    // 略小於設定值 (+- TimerIntervalTimeBase_MS)
    if(G_Module_Function_Status & ENABLE_DOC_COUNTER){
        DOC_ReleaseCounter++;
        if(DOC_ReleaseCounter >= OC_PROTECTION_CycleTimes){
            G_Module_Function_Status |= DOC_COUNTING_FINISH;
            G_Module_Function_Status &= ~ENABLE_DOC_COUNTER;
            DOC_ReleaseCounter = 0;
        }
    }else{
        DOC_ReleaseCounter = 0;
    }
    //DOC Counter : (section stop)
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    //COC Counter : (section start)
    // 略小於設定值 (+- TimerIntervalTimeBase_MS)
    if(G_Module_Function_Status & ENABLE_COC_COUNTER){
        COC_ReleaseCounter++;
        if(COC_ReleaseCounter >= OC_PROTECTION_CycleTimes){
            G_Module_Function_Status |= COC_COUNTING_FINISH;
            G_Module_Function_Status &= ~ENABLE_COC_COUNTER;
            COC_ReleaseCounter = 0;
        }
    }else{
        COC_ReleaseCounter = 0;
    }
    //COC Counter : (section stop)
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //COC Holding Counter After Release : (section start)
    if(G_Module_Function_Status & COC_RELEASE_FOR_REPEATED_CHECK){
        COC_ReleaseHoldingCounter++;
        if(COC_ReleaseHoldingCounter >= COC_RELEASE_HOLDING_CycleTimes){
            G_Module_Function_Status &= ~COC_RELEASE_FOR_REPEATED_CHECK;
            COC_ReleaseHoldingCounter = 0;
        }
    }else{
        COC_ReleaseHoldingCounter = 0;
    }
    //COC Holding Counter After Release : (section stop)
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //System 1 sec Counter : (section start)
    System_1_Sec_Flag_Counter++;
    if(System_1_Sec_Flag_Counter >= System_1_Sec_Flag_CycleTimes){
        G_Module_Function_Status |= SYS_1_SEC_FLAG;
        System_1_Sec_Flag_Counter = 0;
    }
    //System 1 sec Counter : (section stop)
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    //ONE_WIRE Start Counter : (section start)
    if(G_Add_Module_Function_Status & ONE_WIRE_TEMPORARY_START_COUNT){
        ONE_WIRE_Enable_Temporary_Counter++;
        if(ONE_WIRE_Enable_Temporary_Counter >= ONE_WIRE_Enable_Temporary_CycleTimes){
            G_Add_Module_Function_Status &= ~ONE_WIRE_TEMPORARY_START_COUNT;
            ONE_WIRE_Enable_Temporary_Counter = 0;
        }
    }
    //ONE_WIRE Start Counter : (section stop)
    //////////////////////////////////////////////////////////////////////////


//    //////////////////////////////////////////////////////////////////////////
//    //AUX1 Counter : (section start)
//    if(G_Add_Device_Interface_Status & ENABLE_AUX1_COUNTER){
//        AUX1_Counter++;
//        if(AUX1_Counter >= AUX1_Settting_CycleTimes){
//            G_Add_Device_Interface_Status |= AUX1_COUNTING_FINISH;
//            G_Add_Device_Interface_Status &= ~ENABLE_AUX1_COUNTER;
//            AUX1_Counter = 0;
//        }
//    }else{
//        AUX1_Counter = 0;
//    }
//    //AUX1 Counter : (section stop)
//    //////////////////////////////////////////////////////////////////////////
//    GPIO_LOW(LED1_PORT, LED1_PIN);

}
