/**
  ******************************************************************************
  * @file    Capacity_Display_Polling_Func.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   releated capacity functions for Timer to calling
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
#include "Protection_Polling_Func.h"
#include "SOC\SOC_With_Temperature_Calculation.h"

#include "Coulomb_Counter\coulomb_counter.h"
//==============================================================================
// Global/Extern variables
//==============================================================================


//==============================================================================
// Extern functions
//==============================================================================
//==============================================================================
// Private typedef
//==============================================================================
//==============================================================================
// Private define
//==============================================================================
#define Capacity_Polling_Interval_Time_Base_MS          TimerIntervalTimeBase_MS   // 100 ms

#define Capacity_1_Sec_Flag_CycleTimes                  10  //unit:cycles , 1 sec = System_1_Sec_Flag_CycleTimes * TimerIntervalTimeBase_MS
#define Capacity_Showing_Period_CycleTimes              30  //unit:cycles , 2 sec = Capacity_Showing_Period_CycleTimes * TimerIntervalTimeBase_MS
#define Capacity_FCC_CycleTimes                         100  //unit:cycles , 10 sec = Capacity_FCC_CycleTimes * TimerIntervalTimeBase_MS
#define FCC_Release_When_Relax_Delay_Hours              24  //unit:Hours

#define Capacity_To_Static_Waiting_CycleTimes           600  //unit:cycles , 60 sec = Capacity_To_Static_Waiting_CycleTimes * TimerIntervalTimeBase_MS

//#define Cap_Defference_Values                            10
#define Cap_Defference_Delay_Update_CycleTimes           300  //unit:cycles , 30 sec = Cap_Defference_Delay_Update_CycleTimes * TimerIntervalTimeBase_MS

/////////////////////////////////////////////////////////////////////////////////
/* G_Capacity_Var_Bits_Status Bits */
/* For G_Capacity_Var_Bits_Status ; unsigned int */
//Low byte
#define Timer_Polling_XOR_Flag              (0x0001)    //XOR Bit
#define CAP_1_SEC_FLAG                      (0x0002)    //
#define Polling_Set_CHG_Capacity_Displaying        (0x0004)    //
#define CAP_FUN_Interrupt_Exec_ON           (0x0008)    //capacity func at least exec. onec
#define START_COUNT_FCC                     (0x0010)    //
#define CHG_FCC_SET                         (0x0020)    //
#define FCC_1_SEC_FLAG                      (0x0040)    //
#define CAP_UPDATED_ONEC                    (0x0080)    //
//High byte
#define Capacity_Showing_Hold                       (0x0100)    //
#define Capacity_Hold_In_CHG                        (0x0200)    //
#define User_Set_DSG_Capacity_Displaying            (0x0400)    //start count
#define User_Set_DSG_Capacity_Displaying_FINISH     (0x0800)    //
#define Cap_Hold_DSG_To_Static              (0x1000)    //start count
#define Cap_Hold_CHG_To_Static              (0x2000)    //start count
#define Cap_Defference_Delay_Count_Flag     (0x4000)    //
#define Cap_Defference_Delay_Finish_Flag    (0x8000)    //



//==============================================================================
// Private macro
//==============================================================================
//==============================================================================
// Private Enum
//==============================================================================
//==============================================================================
// Private variables
//==============================================================================
//unsigned int g_Capacity_Polling_Interval_Time_mS;       //ms
//unsigned int G_Capacity_Var_Bits_Status;


static unsigned char g_Capacity_1_Sec_Flag_Counter;
static unsigned char g_Capacity_Showing_Period_Counter;
static unsigned char g_Capacity_FCC_Counter;
static unsigned int g_FCC_Release_Second_Timer_Counter;
static unsigned int g_FCC_Release_Hour_Timer_Counter;

static unsigned char g_Current_CHG_LED_Codes;

static unsigned char g_Current_Status;

static unsigned int g_Capacity_DSG_To_Static_Hold_Counter;
static unsigned int g_Capacity_CHG_To_Static_Hold_Counter;

static unsigned int g_Cap_Defference_Delay_Update_Counter;

#if (_Enable_Coulomb_Counter_FCC_RM_ == 1)
//static unsigned int g_temp_FCC;
#endif
void InitCoulombCounterCap();

enum For_LEDDisplayStatusCode  //unsigned char
{
  ALL_LEDs_OFF,   // == 0, because initial values is '0'
  Breathing_LED1,
  Breathing_LED2_LightLEDs,
  Breathing_LED3_LightLEDs,
  Breathing_LED4_LightLEDs,
  Breathing_LED5_LightLEDs,
  Light_1_LED,
  Light_2_LED,
  Light_3_LED,
  Light_4_LED,
  Light_5_LED,
  Blinking_1_LED
};


//static unsigned char g_Capacity_Light_LED_Numbers;
//static unsigned char g_Cap_Light_LED_BITS;
//static unsigned char g_Cap_PWM_LED_BITS;
static float gf_cap_remaning_capacity;
unsigned int g_Capacity_Remaining_Capacity;
//==============================================================================
// Private function prototypes
//==============================================================================

//==============================================================================
// Private functions
//==============================================================================
unsigned char get_DSG_Capacity_LEDDisplayStatusCode(unsigned char capacity){
    unsigned char displayCode;
#if _LED_SETTING_NUMBERS_ == 3
        if(capacity <= DSG_CAPACITY_DISPLAY_TH_1){
            displayCode = Blinking_1_LED;
        }else if(capacity <= DSG_CAPACITY_DISPLAY_TH_2){
            displayCode = Light_1_LED;
        }else if(capacity <= DSG_CAPACITY_DISPLAY_TH_3){
            displayCode = Light_2_LED;
        }else{
            displayCode = Light_3_LED;
        }
#elif _LED_SETTING_NUMBERS_ == 4
        if(capacity <= DSG_CAPACITY_DISPLAY_TH_1){
            displayCode = Blinking_1_LED;
        }else if(capacity <= DSG_CAPACITY_DISPLAY_TH_2){
            displayCode = Light_1_LED;
        }else if(capacity <= DSG_CAPACITY_DISPLAY_TH_3){
            displayCode = Light_2_LED;
        }else if(capacity <= DSG_CAPACITY_DISPLAY_TH_4){
            displayCode = Light_3_LED;
        }else{
            displayCode = Light_4_LED;
        }
#elif _LED_SETTING_NUMBERS_ == 5
        if(capacity <= DSG_CAPACITY_DISPLAY_TH_1){
            displayCode = Blinking_1_LED;
        }else if(capacity <= DSG_CAPACITY_DISPLAY_TH_2){
            displayCode = Light_1_LED;
        }else if(capacity <= DSG_CAPACITY_DISPLAY_TH_3){
            displayCode = Light_2_LED;
        }else if(capacity <= DSG_CAPACITY_DISPLAY_TH_4){
            displayCode = Light_3_LED;
        }else if(capacity <= DSG_CAPACITY_DISPLAY_TH_5){
            displayCode = Light_4_LED;
        }else{
            displayCode = Light_5_LED;
        }
#elif _LED_SETTING_NUMBERS_ == 0

        displayCode = ALL_LEDs_OFF;
#else
    #error "Please select Number of LED for display using"
#endif
        return displayCode;
}
unsigned char get_CHG_Capacity_LEDDisplayStatusCode(unsigned char capacity){
    unsigned char displayCode;

#if _LED_SETTING_NUMBERS_ == 3
        if(capacity <= CHG_CAPACITY_DISPLAY_TH_1){
            displayCode = Breathing_LED1;
        }else if(capacity <= CHG_CAPACITY_DISPLAY_TH_2){
            displayCode = Breathing_LED2_LightLEDs;
        }else{
            if(G_Capacity_Var_Bits_Status & CHG_FCC_SET){
                displayCode = Light_3_LED;
            }else{
                displayCode = Breathing_LED3_LightLEDs;
            }
        }
#elif _LED_SETTING_NUMBERS_ == 4
        if(capacity <= CHG_CAPACITY_DISPLAY_TH_1){
            displayCode = Breathing_LED1;
        }else if(capacity <= CHG_CAPACITY_DISPLAY_TH_2){
            displayCode = Breathing_LED2_LightLEDs;
        }else if(capacity <= CHG_CAPACITY_DISPLAY_TH_3){
            displayCode = Breathing_LED3_LightLEDs;
        }else{
            if(G_Capacity_Var_Bits_Status & CHG_FCC_SET){
                displayCode = Light_4_LED;
            }else{
                displayCode = Breathing_LED4_LightLEDs;
            }
        }
#elif _LED_SETTING_NUMBERS_ == 5
        if(capacity <= CHG_CAPACITY_DISPLAY_TH_1){
            displayCode = Breathing_LED1;
        }else if(capacity <= CHG_CAPACITY_DISPLAY_TH_2){
            displayCode = Breathing_LED2_LightLEDs;
        }else if(capacity <= CHG_CAPACITY_DISPLAY_TH_3){
            displayCode = Breathing_LED3_LightLEDs;
        }else if(capacity <= CHG_CAPACITY_DISPLAY_TH_4){
            displayCode = Breathing_LED4_LightLEDs;
        }else{
            if(G_Capacity_Var_Bits_Status & CHG_FCC_SET){
                displayCode = Light_5_LED;
            }else{
                displayCode = Breathing_LED5_LightLEDs;
            }
        }
#elif _LED_SETTING_NUMBERS_ == 0
        displayCode = ALL_LEDs_OFF;
#else
    #error "Please select Number of LED for display using"
#endif
        return displayCode;
}

void set_LED_Display_Code(unsigned char display_code){
    switch(display_code){
        case ALL_LEDs_OFF:  //set LED Control by order
            _Device_Set_Blinking_Light_LED_BIT(0);
            _Device_Set_Led_OnOff_By_BITs(0);
            _Device_Set_Breathing_Light_LED_BIT(0);
            break;
        case Breathing_LED1:  //set LED Control by order
            _Device_Set_Blinking_Light_LED_BIT(0);
            _Device_Set_Breathing_Light_LED_BIT(LED1_BIT);
            _Device_Set_Led_OnOff_By_BITs(0);
            break;
        case Breathing_LED2_LightLEDs:  //set LED Control by order
            _Device_Set_Blinking_Light_LED_BIT(0);
            _Device_Set_Breathing_Light_LED_BIT(LED2_BIT);
            _Device_Set_Led_OnOff_By_BITs(LED1_BIT);
            break;
        case Breathing_LED3_LightLEDs:  //set LED Control by order
            _Device_Set_Blinking_Light_LED_BIT(0);
            _Device_Set_Breathing_Light_LED_BIT(LED3_BIT);
            _Device_Set_Led_OnOff_By_BITs(LED1_BIT | LED2_BIT);
            break;
        case Breathing_LED4_LightLEDs:  //set LED Control by order
            _Device_Set_Blinking_Light_LED_BIT(0);
            _Device_Set_Breathing_Light_LED_BIT(LED4_BIT);
            _Device_Set_Led_OnOff_By_BITs(LED1_BIT | LED2_BIT | LED3_BIT);
            break;
        case Breathing_LED5_LightLEDs:  //set LED Control by order
            _Device_Set_Blinking_Light_LED_BIT(0);
            _Device_Set_Breathing_Light_LED_BIT(LED5_BIT);
            _Device_Set_Led_OnOff_By_BITs(LED1_BIT | LED2_BIT | LED3_BIT | LED4_BIT);
            break;
        case Light_1_LED:  //set LED Control by order
            _Device_Set_Blinking_Light_LED_BIT(0);
            _Device_Set_Breathing_Light_LED_BIT(0);
            _Device_Set_Led_OnOff_By_BITs(LED1_BIT);
            break;
        case Light_2_LED:  //set LED Control by order
            _Device_Set_Blinking_Light_LED_BIT(0);
            _Device_Set_Breathing_Light_LED_BIT(0);
            _Device_Set_Led_OnOff_By_BITs(LED1_BIT | LED2_BIT);
            break;
        case Light_3_LED:  //set LED Control by order
            _Device_Set_Blinking_Light_LED_BIT(0);
            _Device_Set_Breathing_Light_LED_BIT(0);
            _Device_Set_Led_OnOff_By_BITs(LED1_BIT | LED2_BIT | LED3_BIT);
            break;
        case Light_4_LED:  //set LED Control by order
            _Device_Set_Blinking_Light_LED_BIT(0);
            _Device_Set_Breathing_Light_LED_BIT(0);
            _Device_Set_Led_OnOff_By_BITs(LED1_BIT | LED2_BIT | LED3_BIT | LED4_BIT);
            break;
        case Light_5_LED:  //set LED Control by order
            _Device_Set_Blinking_Light_LED_BIT(0);
            _Device_Set_Breathing_Light_LED_BIT(0);
            _Device_Set_Led_OnOff_By_BITs(LED1_BIT | LED2_BIT | LED3_BIT | LED4_BIT | LED5_BIT);
            break;
        case Blinking_1_LED:  //set LED Control by order
            _Device_Set_Breathing_Light_LED_BIT(0);
            _Device_Set_Led_OnOff_By_BITs(0);
            _Device_Set_Blinking_Light_LED_BIT(LED1_BIT);
            break;
        default:  //set LED Control by order
            _Device_Set_Blinking_Light_LED_BIT(0);
            _Device_Set_Led_OnOff_By_BITs(0);
            _Device_Set_Breathing_Light_LED_BIT(0);
            break;
    }
}

//unsigned char get_Capacity_LED_Light_Number(unsigned char capacity){
//    unsigned char NumOfLeds;
//
//#if _LED_SETTING_NUMBERS_ == 3
//        if(capacity <= CAPACITY_DISPLAY_TH_1){
//          NumOfLeds = 1;
//        }else if(capacity <= CAPACITY_DISPLAY_TH_2){
//          NumOfLeds = 2;
//        }else{
//          NumOfLeds = 3;
//        }
//#elif _LED_SETTING_NUMBERS_ == 4
//        if(capacity <= CAPACITY_DISPLAY_TH_1){
//            NumOfLeds = 1;
//        }else if(capacity <= CAPACITY_DISPLAY_TH_2){
//            NumOfLeds = 2;
//        }else if(capacity <= CAPACITY_DISPLAY_TH_3){
//            NumOfLeds = 3;
//        }else{
//            NumOfLeds = 4;
//        }
//#else
//        if(capacity <= CAPACITY_DISPLAY_TH_1){
//            NumOfLeds = 1;
//        }else if(capacity <= CAPACITY_DISPLAY_TH_2){
//            NumOfLeds = 2;
//        }else if(capacity <= CAPACITY_DISPLAY_TH_3){
//            NumOfLeds = 3;
//        }else if(capacity <= CAPACITY_DISPLAY_TH_4){
//            NumOfLeds = 4;
//        }else{
//            NumOfLeds = 5;
//        }
//#endif
//        return NumOfLeds;
//}

//==============================================================================
// Public functions
//==============================================================================
void coulombCounterFccUpdated(unsigned int FccVal, unsigned char re_Changed){
    G_Last_FCC_Updated_Values = G_Real_FCC_In_CoulombCounter;
    G_Real_FCC_In_CoulombCounter = FccVal;
    //G_Real_FCC_In_CoulombCounter = get_FCC();
    if(re_Changed){
        G_REAL_FCC_UPDATE_TIMES++;
        if(G_REAL_FCC_UPDATE_TIMES > 0xfff8){
            G_REAL_FCC_UPDATE_TIMES = 0xfff8;
        }
    }
}
//==============================================================================
// Public functions
//==============================================================================
void InitCapacityDisplayFuncVariables(void){
    //g_Capacity_Polling_Interval_Time_mS = 0;
    G_Capacity_Var_Bits_Status = 0;
    g_Capacity_1_Sec_Flag_Counter = 0;
    g_Capacity_Showing_Period_Counter = 0;
    g_Capacity_FCC_Counter = 0;
    g_FCC_Release_Second_Timer_Counter = 0;
    g_FCC_Release_Hour_Timer_Counter = 0;

    g_Current_CHG_LED_Codes = 0;

    g_Current_Status = CurrentInRelax;

    g_Capacity_DSG_To_Static_Hold_Counter = 0;
    g_Capacity_CHG_To_Static_Hold_Counter = 0;

    g_Cap_Defference_Delay_Update_Counter = 0;
    //g_Capacity_Light_LED_Numbers = 0;

    InitCoulombCounterCap();


}

void InitCoulombCounterCap(){

#if (_Enable_Coulomb_Counter_FCC_RM_ == 1)
    init_Coulomb_counter(coulombCounterFccUpdated, DESIGN_CAPACITY_mAH);
    //g_temp_FCC = 0;
    G_Real_FCC_In_CoulombCounter  = get_FCC();
#endif

    gf_cap_remaning_capacity = 0.0f;
    g_Capacity_Remaining_Capacity = 0;
}

//void Set_Capacity_Polling_Interval_Time_mS(unsigned int Polling_Interval_Time_ms){
//    if(Polling_Interval_Time_ms > 0){
//        g_Capacity_Polling_Interval_Time_mS = Polling_Interval_Time_ms;
//        G_Capacity_Var_Bits_Status |= Polling_Interval_Time_Set;
//    }else{
//        g_Capacity_Polling_Interval_Time_mS = 0;
//        G_Capacity_Var_Bits_Status &= ~Polling_Interval_Time_Set;
//    }
//}

void Capacity_Timer_Polling_Func_In_Interrupt(){
//    if((G_Capacity_Var_Bits_Status & Polling_Interval_Time_Set)== 0){
//        return;
//    }
    //////////////////////////////////////////////////////////////////////////
    //Flag Blink by timer (XOR) : (section start)
    G_Capacity_Var_Bits_Status ^= Timer_Polling_XOR_Flag;
    //Flag Blink by timer (XOR) : (section stop)
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //Current Direction Codes Set : (section start)
    if(G_Module_Status & Current_Dir_CHG){
        g_Current_Status = CurrentInCHG;
        //G_Capacity_Var_Bits_Status |= Polling_Set_CHG_Capacity_Displaying;
    }else if(G_Module_Status & Current_Dir_DSG){
        g_Current_Status = CurrentInDSG;
        //G_Capacity_Var_Bits_Status &= ~Polling_Set_CHG_Capacity_Displaying;
    }else{
        g_Current_Status = CurrentInRelax;
        //G_Capacity_Var_Bits_Status &= ~Polling_Set_CHG_Capacity_Displaying;
    }
    //Current Direction Codes Set : (section stop)
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //Capacity 1 sec Counter : (section start)
    g_Capacity_1_Sec_Flag_Counter++;
    if(g_Capacity_1_Sec_Flag_Counter >= Capacity_1_Sec_Flag_CycleTimes){
        G_Capacity_Var_Bits_Status |= CAP_1_SEC_FLAG;
        G_Capacity_Var_Bits_Status |= FCC_1_SEC_FLAG;
        g_Capacity_1_Sec_Flag_Counter = 0;
    }
    //Capacity 1 sec Counter : (section stop)
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    //Showing DSG Capacity LED and Capacity LED Period_Counter: (section start)
    if(((G_Capacity_Var_Bits_Status & User_Set_DSG_Capacity_Displaying_FINISH) == 0) &&
        (G_Capacity_Var_Bits_Status & User_Set_DSG_Capacity_Displaying)){
            g_Capacity_Showing_Period_Counter++;
            if(g_Capacity_Showing_Period_Counter >= Capacity_Showing_Period_CycleTimes){
                g_Capacity_Showing_Period_Counter = 0;
                G_Capacity_Var_Bits_Status &= ~User_Set_DSG_Capacity_Displaying;
                G_Capacity_Var_Bits_Status |= User_Set_DSG_Capacity_Displaying_FINISH;
            }
    }else{
        g_Capacity_Showing_Period_Counter = 0;
    }
    //Showing DSG Capacity LED and Capacity LED Period_Counter: (section stop)
    //////////////////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////////////////
    //FCC Detection Counter: (section start)
    if(((G_Capacity_Var_Bits_Status & CHG_FCC_SET)==0) && (G_Capacity_Var_Bits_Status & START_COUNT_FCC)){
        g_Capacity_FCC_Counter++;
        if(g_Capacity_FCC_Counter >= Capacity_FCC_CycleTimes){
            g_Capacity_FCC_Counter = 0;
            G_Capacity_Var_Bits_Status &= ~START_COUNT_FCC;
            G_Capacity_Var_Bits_Status |= CHG_FCC_SET;
        }
    }else{
        g_Capacity_FCC_Counter = 0;
    }
    //FCC Detection Counter: (section stop)
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //FCC Timer Counter FOR Release: (section start)
    if(G_Capacity_Var_Bits_Status & FCC_1_SEC_FLAG){
        G_Capacity_Var_Bits_Status &= ~FCC_1_SEC_FLAG;
        if((G_Capacity_Var_Bits_Status & CHG_FCC_SET ) && (g_Current_Status == CurrentInRelax)){
            g_FCC_Release_Second_Timer_Counter++;
            if(g_FCC_Release_Second_Timer_Counter >= 3600){ // 1 hour
                g_FCC_Release_Hour_Timer_Counter++;
                g_FCC_Release_Second_Timer_Counter = 0;
            }
            if(g_FCC_Release_Hour_Timer_Counter >= FCC_Release_When_Relax_Delay_Hours){
                G_Capacity_Var_Bits_Status &= ~CHG_FCC_SET;
                G_Capacity_Var_Bits_Status &= ~START_COUNT_FCC;
                g_FCC_Release_Hour_Timer_Counter = 0;
                g_FCC_Release_Second_Timer_Counter = 0;
            }
        }else{
            g_FCC_Release_Hour_Timer_Counter = 0;
            g_FCC_Release_Second_Timer_Counter = 0;
        }
    }
    if((G_Capacity_Var_Bits_Status & CHG_FCC_SET ) && (g_Current_Status == CurrentInDSG)){
        G_Capacity_Var_Bits_Status &= ~CHG_FCC_SET;
        G_Capacity_Var_Bits_Status &= ~START_COUNT_FCC;
    }
    //FCC Timer Counter FOR Release: (section stop)
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //Capacity form current status to static waitting-holding Timer Counter: (section start)
    if(G_Capacity_Var_Bits_Status & Cap_Hold_DSG_To_Static){
        g_Capacity_DSG_To_Static_Hold_Counter++;
        if(g_Capacity_DSG_To_Static_Hold_Counter >= Capacity_To_Static_Waiting_CycleTimes){
            g_Capacity_DSG_To_Static_Hold_Counter = 0;
            G_Capacity_Var_Bits_Status &= ~Cap_Hold_DSG_To_Static;
        }
    }else{
        g_Capacity_DSG_To_Static_Hold_Counter = 0;
    }
    if(G_Capacity_Var_Bits_Status & Cap_Hold_CHG_To_Static){
        g_Capacity_CHG_To_Static_Hold_Counter++;
        if(g_Capacity_CHG_To_Static_Hold_Counter >= Capacity_To_Static_Waiting_CycleTimes){
            g_Capacity_CHG_To_Static_Hold_Counter = 0;
            G_Capacity_Var_Bits_Status &= ~Cap_Hold_CHG_To_Static;
        }
    }else{
        g_Capacity_CHG_To_Static_Hold_Counter = 0;
    }
    //Capacity form current status to static waitting-holding Timer Counter: (section stop)
    //////////////////////////////////////////////////////////////////////////
    if(G_Capacity_Var_Bits_Status & Cap_Defference_Delay_Count_Flag){
        g_Cap_Defference_Delay_Update_Counter++;
        if(g_Cap_Defference_Delay_Update_Counter >= Cap_Defference_Delay_Update_CycleTimes){
            g_Cap_Defference_Delay_Update_Counter = 0;
            G_Capacity_Var_Bits_Status &= ~Cap_Defference_Delay_Count_Flag;
            G_Capacity_Var_Bits_Status |= Cap_Defference_Delay_Finish_Flag;
        }
    }else{
        g_Cap_Defference_Delay_Update_Counter = 0;
    }

#if (_Enable_Coulomb_Counter_FCC_RM_ == 1)
    //////////////////////////////////////////////////////////////////////////
    //Coulomb Counter: (section start)
    SetADCValuesToCoulombCounterFunc( G_DSG_Current_ADC, G_CHG_Current_ADC, G_VBAT_ADC, G_NTC1_ADC);
    SetFactorValuesToCoulombCounterFunc(DSG_mA_To_ADC_Factor, CHG_mA_To_ADC_Factor, VBAT_mV_To_ADC_Factor);
    current_coulomb_counter(g_Current_Status);
    //Coulomb Counter: (section stop)
    //////////////////////////////////////////////////////////////////////////
#endif

    G_Capacity_Var_Bits_Status |= CAP_FUN_Interrupt_Exec_ON;
}//void Capacity_Timer_Polling_Func_In_Interrupt(){

unsigned int Cap_ABS(unsigned int a,unsigned int b){
    if(a==b){
        return 0 ;
    }else if(a > b){
        return (a - b);
    }else{
        return (b - a);
    }
}

void Capacity_Main_System_Polling_Func_Not_In_Interrupt(){

    unsigned char Led_Temp_codes;
    if((G_Capacity_Var_Bits_Status & CAP_FUN_Interrupt_Exec_ON)==0){
        return;
    }
    //////////////////////////////////////////////////////////////////////////
    //Disable DSG Showing Capacity LED Period_Counter: (section start)
    if(G_Capacity_Var_Bits_Status & User_Set_DSG_Capacity_Displaying_FINISH){
        G_Capacity_Var_Bits_Status &= ~User_Set_DSG_Capacity_Displaying_FINISH;
        set_LED_Display_Code(ALL_LEDs_OFF);
    }
    //Disable DSG Showing Capacity LED Period_Counter: (section stop)
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //set CHG_Capacity_Displaying: (section start)
    if((g_Current_Status == CurrentInCHG) && ((G_Capacity_Var_Bits_Status & Polling_Set_CHG_Capacity_Displaying)== 0)){
        //if dsg cap still dispalying , force to stop dsg cap display first
        if(G_Capacity_Var_Bits_Status & User_Set_DSG_Capacity_Displaying){
            G_Capacity_Var_Bits_Status &= ~User_Set_DSG_Capacity_Displaying;
            G_Capacity_Var_Bits_Status |= User_Set_DSG_Capacity_Displaying_FINISH;
        }else{
            G_Capacity_Var_Bits_Status |= Polling_Set_CHG_Capacity_Displaying;
            set_LED_Display_Code(0);
            g_Current_CHG_LED_Codes = get_CHG_Capacity_LEDDisplayStatusCode(G_Hold_Capacity);
            set_LED_Display_Code(g_Current_CHG_LED_Codes);
        }


    }
//    if((g_Current_Status == CurrentInCHG) && ((G_Capacity_Var_Bits_Status & Polling_Set_CHG_Capacity_Displaying)== 0)){
//        G_Capacity_Var_Bits_Status |= Polling_Set_CHG_Capacity_Displaying;
//        set_LED_Display_Code(0);
//        g_Current_CHG_LED_Codes = get_CHG_Capacity_LEDDisplayStatusCode(G_Hold_Capacity);
//        set_LED_Display_Code(g_Current_CHG_LED_Codes);
//    }
    if((g_Current_Status != CurrentInCHG) && (G_Capacity_Var_Bits_Status & Polling_Set_CHG_Capacity_Displaying)){
        G_Capacity_Var_Bits_Status &= ~Polling_Set_CHG_Capacity_Displaying;
        g_Current_CHG_LED_Codes = 0;
        set_LED_Display_Code(0);
    }
    //set CHG_Capacity_Displaying: (section stop)
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // Release Capacity Hold Showing Section : (section start)
        if(G_Capacity_Var_Bits_Status & Capacity_Showing_Hold){
            if(g_Current_Status == CurrentInRelax){
                if(G_Capacity_Var_Bits_Status & Capacity_Hold_In_CHG){
                    // previous cap hold was by chg
                    G_Capacity_Var_Bits_Status |= Cap_Hold_CHG_To_Static;
                }else{
                    // previous cap hold was by dsg
                    G_Capacity_Var_Bits_Status |= Cap_Hold_DSG_To_Static;
                }
                G_Capacity_Var_Bits_Status &= ~Capacity_Showing_Hold;
            }else{
                if(g_Current_Status == CurrentInCHG){
                    //CHG
                    if((G_Capacity_Var_Bits_Status & Capacity_Hold_In_CHG)==0){
                        G_Capacity_Var_Bits_Status &= ~Capacity_Showing_Hold;
                    }
                }else{
                    //DSG
                    if(G_Capacity_Var_Bits_Status & Capacity_Hold_In_CHG){
                        G_Capacity_Var_Bits_Status &= ~Capacity_Showing_Hold;
                    }
                }
            }// else - if(g_Current_Status == CurrentInRelax){
        }//if(G_Capacity_Var_Bits_Status & Capacity_Showing_Hold){
    // Release Capacity Hold Showing Section : (section stop)
    //////////////////////////////////////////////////////////////////////////

//    //////////////////////////////////////////////////////////////////////////
//    // Release Capacity Hold Showing Section : (section start)
//        if(G_Capacity_Var_Bits_Status & Capacity_Showing_Hold){
//            if(g_Current_Status == CurrentInCHG){
//                //CHG
//                if((G_Capacity_Var_Bits_Status & Capacity_Hold_In_CHG)==0){
//                    G_Capacity_Var_Bits_Status &= ~Capacity_Showing_Hold;
//                }
//            }else{
//                //DSG
//                if(G_Capacity_Var_Bits_Status & Capacity_Hold_In_CHG){
//                    G_Capacity_Var_Bits_Status &= ~Capacity_Showing_Hold;
//                }
//            }
//        }//if(G_Capacity_Var_Bits_Status & Capacity_Showing_Hold){
//    // Release Capacity Hold Showing Section : (section stop)
//    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // 1 sec Updated Section : (section start)
    if(G_Capacity_Var_Bits_Status & CAP_1_SEC_FLAG){
        G_Capacity_Var_Bits_Status &= ~CAP_1_SEC_FLAG;

#if (_Capacity_Showing_Use_Coulomb_Counter_  == 0)
        //////////////////////////////////////////////////////////////////////////
        //  calculate Capacity for each 1 sec : (section start)
        G_Current_Capacity = getBatteryCapacity(G_VBAT_ADC, G_DSG_Current_ADC, G_NTC1_ADC, g_Current_Status);
        //  calculate Capacity for each 1 sec : (section stop)
        //////////////////////////////////////////////////////////////////////////

        if(G_Capacity_Var_Bits_Status & CAP_UPDATED_ONEC){
            if(((G_Capacity_Var_Bits_Status & Cap_Defference_Delay_Count_Flag) == 0) &&
                ((G_Capacity_Var_Bits_Status & Cap_Defference_Delay_Finish_Flag) == 0) ){
                if(Cap_ABS(G_Hold_Capacity, G_Current_Capacity) > CAPACITY_DIFFERENCE_VALUES){
                    G_Capacity_Var_Bits_Status |= Cap_Defference_Delay_Count_Flag;
                }
            }
        }

        if((G_Capacity_Var_Bits_Status & Cap_Defference_Delay_Count_Flag) == 0){
            //////////////////////////////////////////////////////////////////////////
            //  Hold Capacity Showing Section by 1 sec: (section start)
            if(G_Capacity_Var_Bits_Status & Capacity_Showing_Hold){
                    //capacity calculation and hold
                    if(G_Capacity_Var_Bits_Status & Capacity_Hold_In_CHG){
                        //hold in chg
                        if(G_Current_Capacity > G_Hold_Capacity){
                            G_Hold_Capacity = G_Current_Capacity;
                        }
                    }else{
                        //hold in dsg
                        if(G_Current_Capacity < G_Hold_Capacity){
                            G_Hold_Capacity = G_Current_Capacity;
                        }
                    }
            }else{
                // setting capacity hold values
                if(g_Current_Status == CurrentInRelax){
                    //no update capacity, if current status change to Static, then wait 1 minutes
                    if((G_Capacity_Var_Bits_Status & Cap_Hold_DSG_To_Static) || (G_Capacity_Var_Bits_Status & Cap_Hold_CHG_To_Static)){
                    }else{
                        G_Hold_Capacity = G_Current_Capacity;
                    }
                }else{

                    //release current status to Static Flag
                    if((G_Capacity_Var_Bits_Status & Cap_Hold_DSG_To_Static) || (G_Capacity_Var_Bits_Status & Cap_Hold_CHG_To_Static)){
                        G_Capacity_Var_Bits_Status &= ~Cap_Hold_DSG_To_Static;
                        G_Capacity_Var_Bits_Status &= ~Cap_Hold_CHG_To_Static;
                    }

                    G_Capacity_Var_Bits_Status |= Capacity_Showing_Hold;
                    if(g_Current_Status == CurrentInCHG){
                        //CHG
                        G_Capacity_Var_Bits_Status |= Capacity_Hold_In_CHG;
                    }else{
                        //DSG
                        G_Capacity_Var_Bits_Status &= ~Capacity_Hold_In_CHG;
                    }
                    G_Hold_Capacity = G_Current_Capacity;
                }
            }
            //  Hold Capacity Showing Section by 1 sec: (section stop)
            //////////////////////////////////////////////////////////////////////////
            G_Capacity_Var_Bits_Status &= ~Cap_Defference_Delay_Finish_Flag;
            G_Capacity_Var_Bits_Status |= CAP_UPDATED_ONEC;
        }//if((G_Capacity_Var_Bits_Status & Cap_Defference_Delay_Count_Flag) == 0){

        gf_cap_remaning_capacity = G_Hold_Capacity;
        g_Capacity_Remaining_Capacity = DESIGN_CAPACITY_mAH;
        gf_cap_remaning_capacity = gf_cap_remaning_capacity / 100 * g_Capacity_Remaining_Capacity;
        g_Capacity_Remaining_Capacity = (unsigned int)gf_cap_remaning_capacity;

#else
        // _Capacity_Showing_Use_Coulomb_Counter_
        G_Current_Capacity = G_Capacity_In_CoulombCounter;
        G_Hold_Capacity = G_Capacity_In_CoulombCounter;
        g_Capacity_Remaining_Capacity = G_RM_In_CoulombCounter;
#endif

// remove this section on 2014/02/25 hsinmo
//        gf_cap_remaning_capacity = G_Hold_Capacity;
//        g_Capacity_Remaining_Capacity = DESIGN_CAPACITY_mAH;
//        gf_cap_remaning_capacity = gf_cap_remaning_capacity / 100 * g_Capacity_Remaining_Capacity;
//        g_Capacity_Remaining_Capacity = (unsigned int)gf_cap_remaning_capacity;


//        //////////////////////////////////////////////////////////////////////////
//        //  Hold Capacity Showing Section by 1 sec: (section start)
//        if(G_Capacity_Var_Bits_Status & Capacity_Showing_Hold){
//            //capacity calculation and hold
//            if(G_Capacity_Var_Bits_Status & Capacity_Hold_In_CHG){
//                //hold in chg
//                if(G_Current_Capacity > G_Hold_Capacity){
//                    G_Hold_Capacity = G_Current_Capacity;
//                }
//            }else{
//                //hold in dsg
//                if(G_Current_Capacity < G_Hold_Capacity){
//                    G_Hold_Capacity = G_Current_Capacity;
//                }
//            }
//        }else{
//            // setting capacity hold values
//            G_Capacity_Var_Bits_Status |= Capacity_Showing_Hold;
//            if(g_Current_Status == CurrentInCHG){
//                G_Capacity_Var_Bits_Status |= Capacity_Hold_In_CHG;
//            }else{
//                G_Capacity_Var_Bits_Status &= ~Capacity_Hold_In_CHG;
//            }
//            G_Hold_Capacity = G_Current_Capacity;
//
//        }
//        //  Hold Capacity Showing Section by 1 sec: (section stop)
//        //////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////
        //update CHG_Capacity_Displaying by one second: (section start)
        if(G_Capacity_Var_Bits_Status & Polling_Set_CHG_Capacity_Displaying){
            Led_Temp_codes = get_CHG_Capacity_LEDDisplayStatusCode(G_Hold_Capacity);
            if(Led_Temp_codes != g_Current_CHG_LED_Codes){
                set_LED_Display_Code(Led_Temp_codes);
                g_Current_CHG_LED_Codes = Led_Temp_codes;
            }
        }
        //update CHG_Capacity_Displaying by one second: (section stop)
        //////////////////////////////////////////////////////////////////////////


        //G_Current_Capacity = getRealCapacity(G_VBAT_ADC, G_DSG_Current_ADC, G_NTC1_ADC, g_Current_Status);

        //g_Capacity_Light_LED_Numbers = get_Capacity_LED_Light_Number(G_Hold_Capacity);
    }
    // 1 sec Updated Section : (section stop)
    //////////////////////////////////////////////////////////////////////////

#if (_Enable_Coulomb_Counter_FCC_RM_ == 1)
    //////////////////////////////////////////////////////////////////////////
    //Coulomb Counter: (section start)

    //Fcc Updated
//    g_temp_FCC = get_FCC();
//    if(G_Real_FCC_In_CoulombCounter != g_temp_FCC){
//        G_REAL_FCC_UPDATE_TIMES++;
//        G_Real_FCC_In_CoulombCounter = g_temp_FCC;
//    }
    G_RM_In_CoulombCounter   = get_RM();
    G_Capacity_In_CoulombCounter  = get_percentage();
    //Coulomb Counter: (section stop)
    //////////////////////////////////////////////////////////////////////////
#endif


    if((g_Current_Status == CurrentInCHG) && (G_CHG_Current_ADC < ADC_CHG_CHARGER_TAPE_CURRENT)){
        G_Capacity_Var_Bits_Status |= START_COUNT_FCC;
    }else{
        G_Capacity_Var_Bits_Status &= ~START_COUNT_FCC;
    }
}//void Capacity_Main_System_Polling_Func_Not_In_Interrupt(){

//static unsigned char gPWMLedBit;
//static unsigned char gLightLedBit;
//static  unsigned int Breathing_Light_Steps;

//void Breathing_Light_Step_For_Timer(){

//    if((G_Capacity_Var_Bits_Status & Breathing_Light_START) == 0){
//        _Device_Set_Led_PWM_Channel_Bits_Enable(gPWMLedBit);
//        _Device_Set_Led_PWM_Change_Duty(gPWMLedBit, 0);
//        _Device_Set_Led_OnOff_By_BITs(gLightLedBit);
//        G_Capacity_Var_Bits_Status |= Breathing_Light_START;
//        Breathing_Light_Steps = 0;
//    }
//    if(G_Capacity_Var_Bits_Status & Breathing_Light_START){
//        Breathing_Light_Steps++;
//        if(Breathing_Light_Steps >= PWM_FREQ_STEP_POINTS){
//            Breathing_Light_Steps = 0;
//            _Device_Set_Led_PWM_Change_Duty(gPWMLedBit, PWM_Freq_Scaler_Duty[Breathing_Light_Steps]);
//            G_Add_Module_Function_Status |= Breathing_Light_FINISH;
//        }else{
//            _Device_Set_Led_PWM_Change_Duty(gPWMLedBit, PWM_Freq_Scaler_Duty[Breathing_Light_Steps]);
//        }
//    }




//    if((G_Add_Module_Function_Status & Breathing_Light_START) == 0){
//        return;
//    }
//GPIO_HIGH(LED1_PORT, LED1_PIN);
//    if(Breathing_Light_Steps == 0){
//        _Device_Set_Led_PWM_Enable(DeviceOn);
//        _Device_Set_Led_PWM_20_Steps(Num_Of_Breathing_Light_Bits,   Breathing_Light_Steps);
//    }else if(Breathing_Light_Steps > 20){
//        Breathing_Light_Repeat_Count++;
//        if(Breathing_Light_Repeat_Count >= BREATHING_LIGHT_REPEAT_TIMES){
//            _Device_Set_Led_PWM_Enable(DeviceOff);
//            Num_Of_Breathing_Light_Bits = 0;
//            Breathing_Light_Repeat_Count = BREATHING_LIGHT_REPEAT_TIMES + 2;
//            Breathing_Light_Steps = 30;
//            G_Add_Module_Function_Status &= ~Breathing_Light_START;
//            G_Add_Module_Function_Status |= Breathing_Light_FINISH;
//        }else{
//            Breathing_Light_Steps = 0;
//        }
//    }else{
//        _Device_Set_Led_PWM_20_Steps(Num_Of_Breathing_Light_Bits,   Breathing_Light_Steps);
//    }
//    Breathing_Light_Steps++;
//GPIO_LOW(LED1_PORT, LED1_PIN);
//}
void Capacity_Display_By_User(){
    unsigned char LED_Codes;

    // Only Show DSG capacity
    if(g_Current_Status == CurrentInCHG){
        return;
    }

    set_LED_Display_Code(ALL_LEDs_OFF);

    LED_Codes = get_DSG_Capacity_LEDDisplayStatusCode(G_Hold_Capacity);
    set_LED_Display_Code(LED_Codes);

    G_Capacity_Var_Bits_Status |= User_Set_DSG_Capacity_Displaying;

}
void Display_All_LEDs_For_Test(){
    unsigned char LED_Codes;

    // Only Show DSG capacity
    if(g_Current_Status == CurrentInCHG){
        return;
    }

    set_LED_Display_Code(ALL_LEDs_OFF);

    LED_Codes = get_DSG_Capacity_LEDDisplayStatusCode(100);
    set_LED_Display_Code(LED_Codes);

    G_Capacity_Var_Bits_Status |= User_Set_DSG_Capacity_Displaying;

}

