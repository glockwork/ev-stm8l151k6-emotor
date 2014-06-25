


//==============================================================================
// TEST GPIO Control_init
//==============================================================================
#define TEST_PORT	GPIOC
#define TEST_PIN	GPIO_Pin_2
void test_pin_init();
void test_high();
void test_low();
void test_toggle();

/********************************************************************************
*   Define for TimerPollingFunction                                             *
* Define	(could not be modified, because it's base on function define)       *
********************************************************************************/
// Timer
#define TimerIntervalTimeBase_MS                100  // unit: ms
//// PWM Function has 10 setp different frequency and light on and ligh off, so total PWM turn on is LED_PWM_One_Step_CycleTimes * LED_PWM_Whole_Steps
//#define LED_PWM_Whole_Steps                     20  //could not be modified, because it's base on function define
/********************************************************************************
* Define	                                                                    *
********************************************************************************/
//#define LED_PWM_One_Step_CycleTimes             3   //unit:cycles , 150ms = LED_PWM_One_Step_CycleTimes * TimerIntervalTimeBase_MS
//#define LED_Blink_OnOffInterval_CycleTimes      8  //unit:cycles , 500 ms = LED_Blink_OnOffInterval_CycleTimes * TimerIntervalTimeBase_MS
#define Button_Click_CycleTimes                 6  //unit:cycles ,  600 ms = Button_Click_CycleTimes * TimerIntervalTimeBase_MS
#define Button_Long_Press_CycleTimes            50 //unit:cycles , 5 sec = Button_Long_Press_CycleTimes * TimerIntervalTimeBase_MS
//
#define COMPLETE_MULTI_CLICK_PRESS_TIMES                3  //unit: Times , click COMPLETE_MULTI_CLICK_PRESS_TIMES times, MULTI CLICK function will be enable
#define Button_MultiClick_DetectionCycleTimes   15  //unit:cycles ,  1.5 sec = Button_MultiClick_DetectionCycleTimes * TimerIntervalTimeBase_MS

#define OC_PROTECTION_CycleTimes                50//unit:cycles , 5 sec = OC_PROTECTION_CycleTimes * TimerIntervalTimeBase_MS

/*
    COC_RELEASE_HOLDING_CycleTimes
    must biger than CHG_OC_Protection_Delay_Cycle
    for COC_RELEASE_FOR_REPEATED_CHECK
*/
//#define COC_RELEASE_HOLDING_CycleTimes        (CHG_OC_Protection_Delay_Cycle+3)  //unit:cycles , 1 sec = COC_RELEASE_HOLDING_CycleTimes * TimerIntervalTimeBase_MS
//#define COC_RELEASE_HOLDING_CycleTimes          18  //unit:cycles , 1.15 sec = COC_RELEASE_HOLDING_CycleTimes * TimerIntervalTimeBase_MS
#define AVG_ADC_CURRENT_ARRAY_NUMS          8   //do not modify
#define STORE_AVG_ADC_CURRENT_CycleTimes    75      //unit:cycles , 7.5 sec = STORE_AVG_CURRENT_CycleTimes * TimerIntervalTimeBase_MS
#define AVG_ADC_VOLTAGE_ARRAY_NUMS          4   //do not modify
#define STORE_AVG_ADC_VOLTAGE_CycleTimes    100      //unit:cycles , 10 sec = STORE_AVG_CURRENT_CycleTimes * TimerIntervalTimeBase_MS


#define System_1_Sec_Flag_CycleTimes            10  //unit:cycles , 1 sec = System_1_Sec_Flag_CycleTimes * TimerIntervalTimeBase_MS

#define ONE_WIRE_Enable_Temporary_CycleTimes    90  //unit:cycles , 8 sec = ONE_WIRE_Enable_Temporary_CycleTimes * TimerIntervalTimeBase_MS

#define System_1_Min_Flag_CycleTimes            600  //unit:cycles , 60 sec = System_1_Min_Flag_CycleTimes * TimerIntervalTimeBase_MS
/********************************************************************************
* Define	(for SUB Polling Protection)                                        *
********************************************************************************/
/////////////////////////////////////////////////
// Current Sub Functions Vairable Define
//1 time = 50ms, based on timer interval time
#define DSG_OC_Protection_Delay_Cycle       100   //times,100*100 ms = 10sec = DSG_OC_Protection_Delay_Cycle * TimerIntervalTimeBase_MS
//#define DSG_OC_Protection_Delay_Cycle       10   //times,10*100 ms = 1sec = DSG_OC_Protection_Delay_Cycle * TimerIntervalTimeBase_MS
#define CHG_OC_Protection_Delay_Cycle       10   //times,10*100 ms = 1sec = CHG_OC_Protection_Delay_Cycle * TimerIntervalTimeBase_MS

/*
    COC_RELEASE_HOLDING_CycleTimes
    must biger than CHG_OC_Protection_Delay_Cycle about 3 cycle timies
    for COC_RELEASE_FOR_REPEATED_CHECK
*/
#define COC_RELEASE_HOLDING_CycleTimes        (CHG_OC_Protection_Delay_Cycle+3)  //unit:cycles , 1 sec = COC_RELEASE_HOLDING_CycleTimes * TimerIntervalTimeBase_MS
//#define COC_RELEASE_HOLDING_CycleTimes          18  //unit:cycles , 1.15 sec = COC_RELEASE_HOLDING_CycleTimes * TimerIntervalTimeBase_MS



#define Battery_OV_Protection_Delay_Cycle   30   //times, 3000 ms = 3sec = Battery_OV_Protection_Delay_Cycle * TimerIntervalTimeBase_MS
#define Battery_UV_Protection_Delay_Cycle   30   //times, 3000 ms = 3sec = Battery_UV_Protection_Delay_Cycle * TimerIntervalTimeBase_MS
//#define DSG_Low_OT_Protection_Delay_Cycle   10   //times, 1000 ms = 1sec = DSG_Low_OT_Protection_Delay_Cycle * TimerIntervalTimeBase_MS
//#define DSG_High_OT_Protection_Delay_Cycle  10   //times, 1000 ms = 1sec = DSG_High_OT_Protection_Delay_Cycle * TimerIntervalTimeBase_MS
#define DSG_Low_OT_Protection_Delay_Cycle   1200   //times, 120000 ms = 2min = DSG_Low_OT_Protection_Delay_Cycle * TimerIntervalTimeBase_MS
#define DSG_High_OT_Protection_Delay_Cycle  1200   //times, 120000 ms = 2min = DSG_High_OT_Protection_Delay_Cycle * TimerIntervalTimeBase_MS
#define CHG_OT_Protection_Delay_Cycle       10   //times, 1000 ms = 1sec = CHG_OT_Protection_Delay_Cycle * TimerIntervalTimeBase_MS
#define UT_Protection_Delay_Cycle           10   //times, 1000 ms = 1sec = UT_Protection_Delay_Cycle * TimerIntervalTimeBase_MS
//////////////////////////////////////////////////////////////////////////////////////////////
// the unit is cycles
#define COC_Repeat_For_LOCK_Times           3   //times, COC Repeat 3 times then LOCK

#define AFTER_UVP_Delay_Count_CycleTimes    50//unit:cycles , 5 sec = AFTER_UVP_Delay_Count_CycleTimes * TimerIntervalTimeBase_MS

#define DISPLAY_1_LED   1
#define DISPLAY_2_LED   2
#define DISPLAY_3_LED   3
#define DISPLAY_4_LED   4
#define DISPLAY_5_LED   5
#define BREATHING_LIGHT_STEP_INTERVAL_MS    75 //100ms for one of 20 steps
#define BREATHING_LIGHT_REPEAT_TIMES        2   // repeat 2 times
//////////////////////////////////////////////////////////////////////////////////////////////
#define WWAK_UP_HOLDING_Delay_SECONDS       10   //sec. : 20 sec, have to be set bigger than button long press times

#define TOUCH_KEY_LED_LIGHT_IN_SHUTDOWN_SECONDS       2   //sec. : 2 sec, have to be set bigger than button long press times
//////////////////////////////////////////////////////////////////////////////////////////////

#define UINT_MAX_VALUES_TH           0xfff8
#define ULONG_MAX_VALUES_TH           0xfffffff8
//////////////////////////////////////////////////////////////////////////////////////////////
// Polling function
void InitProtectionPollingFuncVariables(void);
void Protection_Polling_Function(void);
void UpdatedDetectingValues(void);
void UpdatedCurrentDirectionStatus();

void InitTimerPollingVariables();
void Timer_Counter_For_Polling();

//////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************
* Define	(for Back Light control)                                            *
********************************************************************************/
#define BackLight_Blinking_Delay_Cycle      2   //times, 200 ms = BackLight_Blinking_Cycle * TimerIntervalTimeBase_MS
//////////////////////////////////////////////////////////////////////////////////////////////
//void Display_Capacity(unsigned char capacity);
//void Display_Breathing_Light(unsigned char NumOfLeds);
//void Finish_Display_Breathing_Light_And_Timer();


/********************************************************************************
* RECORDING DATA Define															*
********************************************************************************/
enum For_EEPROM_Store_Step  //unsigned char
{
    Storing_AccumulatingQ,
    Storing_MaxMinVbatCurr,
    Storing_MaxMin_NTC,
    Storing_OVUV_OC_UT,
    Storing_DSG_CHG_OTP,
    Storing_FCC_Update,
    Storing_3rd_Chg_Dsg,
    Storing_3rd_Low_Temp,
    Storing_3rd_High_Temp,
    Storing_4rd_Low_Temp_in_Act,
    Storing_Count_DSG_CHG_Time_1,
    Storing_Count_DSG_CHG_Time_2,
    storing_DSG_Current_Record,
    Storing_Last_Step
};


#define EEPROMWriteRetry    3

#define _500mS_CycleTimes_For_CoulombCounter         5  //unit:cycles , 500 ms = _500mS_CycleTimes_For_CoulombCounter * TimerIntervalTimeBase_MS
#define _1_Min_CycleTimes_For_RecordingData         600  //unit:cycles , 1 min = _1_Min_CycleTimes_For_RecordingData * TimerIntervalTimeBase_MS
#define _6_sec_CycleTimes_For_RecordingData         60  //unit:cycles , 6 sec = _6_sec_CycleTimes_For_RecordingData * TimerIntervalTimeBase_MS
#define WriteRecordingData_Minutes                   30  //unit: minutes
#define RecordingPolling_Start_Delay_CycleTimes            10  //unit:cycles + 1 , 1 sec = RecordingPolling_Start_Delay_CycleTimes * TimerIntervalTimeBase_MS
#define VBAT_Recording_Delay_CycleTimes_When_Soc_Set       5  //unit:cycles , 500 ms = VBAT_Recording_Delay_CycleTimes_When_Soc_Set * TimerIntervalTimeBase_MS

void SysInfo_init();
void UpdatedSystemRecordingInfoForPolling();
void CoulombCounterForHalfSecond(void);

void Storing_Infor_To_EEPROM_By_Step(unsigned char step);

void WriteAccumulatingQToEEPROM();
void WriteMaxMinVbatCurrToEEPROM();
void WriteMaxMin_NTC_ToEEPROM();
void Write_OVUV_OC_UT_ToEEPROM();
void Write_DSG_CHG_OTP_ToEEPROM();

void Write_FCC_Update_ToEEPROM();

void Write_3rd_Chg_Dsg_ToEEPROM();
void Write_3rd_Low_Temp_ToEEPROM();
void Write_3rd_High_Temp_ToEEPROM();
void Write_4rd_Low_Temp_in_Act_ToEEPROM();
void Write_Count_DSG_CHG_TIME_1_ToEEPROM();
void Write_Count_DSG_CHG_TIME_2_ToEEPROM();
void Write_DSG_Current_Record_ToEEPROM();

void Write_BAR_CODE_ID_To_EEPROM();
//void WriteSystemRecordingInfoToEEPROM();


//


