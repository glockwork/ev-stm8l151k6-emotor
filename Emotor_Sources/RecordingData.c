/**
  ******************************************************************************
  * @file    RecordingData.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   Calculation and recording All ADC values
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
//#include "SOC\New_SOC_Calculation.h"
#include "SOC\Calculate_NTC_ADC_TO_TEMPERATURE.h"

//==============================================================================
// Global/Extern variables
//==============================================================================


//==============================================================================
// Extern functions
//==============================================================================
extern unsigned char g_Recording_SystemActivatedMinutes;
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


//
///********************************************************************************
//* Define																		*
//********************************************************************************/
//#define EEPROMWriteRetry    3
//
//#define Recording_1_Sec_CycleTimes                  15  //unit:cycles , 1 sec = System_1_Sec_Flag_CycleTimes * TimerIntervalTimeBase_MS
////#define WriteRecordingData_Hours                    24  //unit:hours
//#define WriteRecordingData_Hours                    1  //unit:hours
//#define RecordingPolling_Start_Delay_CycleTimes            15  //unit:cycles , 1 sec = RecordingPolling_Start_Delay_CycleTimes * TimerIntervalTimeBase_MS
///////////////////////////////////////////////////////////////////////////////////
/* sg_Recording_3rd_Status Control Bits */
/* For sg_Recording_3rd_Status ; unsigned int */
//Low byte
#define fSTATIC_OVER_VOLTAGE            (0x0001)    //
#define fOVER_LOADING                   (0x0002)    //
#define fCHG_OVER_VOLTAGE               (0x0004)    //
#define fCHG_FASTER_CHARGING            (0x0008)    //
#define fCHARGING_IN_HIGH_TEMP          (0x0010)
#define fCHARGING_IN_LOW_TEMP           (0x0020)    //
#define fSTORE_IN_LOW_TEMP1             (0x0040)    //
#define fSTORE_IN_LOW_TEMP2             (0x0080)    //
////Hight byte
#define fSTORE_IN_LOW_TEMP3             (0x0100)    //
#define fSTORE_IN_LOW_TEMP4             (0x0200)    //
#define fSTORE_IN_HIGH_TEMP1            (0x0400)    //
#define fSTORE_IN_HIGH_TEMP2            (0x0800)    //
#define fSTORE_IN_HIGH_TEMP3            (0x1000)    //
#define fSTORE_IN_HIGH_TEMP4            (0x2000)    //
#define fSTORE_IN_HIGH_TEMP5            (0x4000)    //
#define fNoUsed                         (0x8000)    //
///////////////////////////////////////////////////////////////////////////////////
/* sg_Recording_4th_Status Control Bits */
/* For sg_Recording_4th_Status ; unsigned int */
//Low byte
#define fLOW_TEMP1_IN_DSG_ACT           (0x0001)    //
#define fLOW_TEMP2_IN_DSG_ACT           (0x0002)    //
#define fLOW_TEMP3_IN_DSG_ACT           (0x0004)    //
//#define fCHG_FASTER_CHARGING            (0x0008)    //
//#define fCHARGING_IN_HIGH_TEMP          (0x0010)
//#define fCHARGING_IN_LOW_TEMP           (0x0020)    //
//#define fSTORE_IN_LOW_TEMP1             (0x0040)    //
//#define fSTORE_IN_LOW_TEMP2             (0x0080)    //
////Hight byte
//#define fSTORE_IN_LOW_TEMP3             (0x0100)    //
//#define fSTORE_IN_LOW_TEMP4             (0x0200)    //
//#define fSTORE_IN_HIGH_TEMP1            (0x0400)    //
//#define fSTORE_IN_HIGH_TEMP2            (0x0800)    //
//#define fSTORE_IN_HIGH_TEMP3            (0x1000)    //
//#define fSTORE_IN_HIGH_TEMP4            (0x2000)    //
//#define fSTORE_IN_HIGH_TEMP5            (0x4000)    //
//#define fNoUsed                         (0x8000)    //
/********************************************************************************
* Extern Function																*
********************************************************************************/
/********************************************************************************
* Extern Variable																*
********************************************************************************/
void CoulombCounterForOneSecond(void);
void Updated3rdTrackingRecordInfoForPolling();
void CountAndUpdated3rdTrackingRecordInfo_in_1_min();

/********************************************************************************
* Golbal Variable																*
********************************************************************************/


/********************************************************************************
* Local file Variable										                    *
********************************************************************************/
static unsigned int     _500mS_Counter;
static unsigned int     _1_Min_Counter;
static unsigned int     WriteRecordingData_Minutes_Counter;
static unsigned int     RecordingPolling_Start_Delay_Counter;

static unsigned long    sg_CHG_ADC_AccumulatingQ_RECORD;
static unsigned long    sg_DSG_ADC_AccumulatingQ_RECORD;

//static unsigned char     EEPROM_Storing_Step;
//static unsigned long    sg_Current_DSG_Test_ADC_AccumulatingQ;
//static unsigned long    sg_Current_CHG_Test_ADC_AccumulatingQ;
//================================
static unsigned int     sg_Recording_3rd_Status;
static unsigned int     sg_Recording_3rd_1_Min_Counter;
static unsigned int     sg_Recording_4th_Status;

////////////////////////////////////////////////////////////////////////////////
static unsigned int NTC_ADC_MAX_Lower_Temp;
static unsigned int NTC_ADC_MIN_Higher_Temp;
////////////////////////////////////////////////////////////////////////////////
static unsigned char sg_STATIC_OVER_VOLTAGE_HOURS_TIMES_COUNT;
static unsigned char sg_CHG_OVER_VOLTAGE_MINUTES_TIMES_COUNT;
//static unsigned char sg_OVER_LOADING_MINUTES_TIMES_COUNT;
//static unsigned char sg_FASTER_CHARGING_MINUTES_TIMES_COUNT;
static unsigned char sg_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_COUNT;
static unsigned char sg_CHARGING_IN_LOW_TEMP_MINUTES_TIMES_COUNT;
static unsigned char sg_STORE_IN_LOW_TEMP1_HOURS_TIMES_COUNT;
static unsigned char sg_STORE_IN_LOW_TEMP2_HOURS_TIMES_COUNT;
static unsigned char sg_STORE_IN_LOW_TEMP3_HOURS_TIMES_COUNT;
static unsigned char sg_STORE_IN_LOW_TEMP4_HOURS_TIMES_COUNT;
//static unsigned char sg_STORE_IN_HIGH_TEMP1_MINUTES_TIMES_COUNT;
//static unsigned char sg_STORE_IN_HIGH_TEMP2_MINUTES_TIMES_COUNT;
//static unsigned char sg_STORE_IN_HIGH_TEMP3_MINUTES_TIMES_COUNT;
//static unsigned char sg_STORE_IN_HIGH_TEMP4_MINUTES_TIMES_COUNT;
//static unsigned char sg_STORE_IN_HIGH_TEMP5_MINUTES_TIMES_COUNT;

////////////////////////////////////////////////////////////////////////////////
static unsigned int sg_LOW_TEMP1_IN_DSG_ACT_RECORD_MINUTES_Times;
static unsigned int sg_LOW_TEMP2_IN_DSG_ACT_RECORD_MINUTES_Times;
static unsigned int sg_LOW_TEMP3_IN_DSG_ACT_RECORD_MINUTES_Times;

/********************************************************************************
* System_Information_init	                            						*
********************************************************************************/
//void SysInfo_init_test(){
//
//    //updated Data
//    G_RECORD_DATA_COUNT    =  11;
//    G_MAX_DSG_C_ADC_RECORD =  12;
//    G_MAX_CHG_C_ADC_RECORD =  13;
//    G_MAX_VBAT_ADC_RECORD  =  14;
//    G_MIN_VBAT_ADC_RECORD  =  15;
//    G_MAX_VBAT_SocLo_ADC_RECORD  =  16;
//    G_MAX_VBAT_SocHi_ADC_RECORD  =  17;
//
//    G_DSG_MAX_TH1_ADC_RECORD   =  18;
//    G_DSG_MIN_TH1_ADC_RECORD   =  19;
//    G_DSG_MAX_TH2_ADC_RECORD   =  20;
//    G_DSG_MIN_TH2_ADC_RECORD   =  21;
//
//    G_CHG_Cycle_Count_RECORD = 22;
//    sg_CHG_ADC_AccumulatingQ_RECORD = 23;
//
//
//    ////////////////////////////////////////////////////////////////////////////
//    sg_DSG_ADC_AccumulatingQ_RECORD = 24;
//    G_DSG_Cycle_Count_RECORD = 25;
//
//    G_CHG_MAX_TH1_ADC_RECORD = 26;
//    G_CHG_MIN_TH1_ADC_RECORD = 27;
//    G_CHG_MAX_TH2_ADC_RECORD = 28;
//    G_CHG_MIN_TH2_ADC_RECORD = 29;
//
//    G_OVP_TIMES		 = 30 ;
//    G_UVP_TIMES		 = 31 ;
//    G_COCP_TIMES	 = 32;
//    G_DOCP_TIMES	 = 33;
//
//    G_TH1_CHG_UTP_TIMES = 34;
//    G_TH2_CHG_UTP_TIMES = 35;
//
//    G_CHG_TH1_OTP_TIMES  = 36;
//    G_CHG_TH2_OTP_TIMES  = 37;
//
//    G_DSG_TH1_LOW_CURRENT_OTP_TIMES   = 38;
//    G_DSG_TH1_HIGH_CURRENT_OTP_TIMES  = 39;
//    G_DSG_TH2_LOW_CURRENT_OTP_TIMES   = 40;
//    G_DSG_TH2_HIGH_CURRENT_OTP_TIMES  = 41;
//
//    G_RECORD_2nd_DATA_COUNT = 42;
//    ////////////////////////////////////////////////////////////////////////////
//
//    G_REAL_FCC_UPDATE_TIMES                  = 80;
//    G_Real_FCC_In_CoulombCounter             = 81;
//
//    G_STATIC_OVER_VOLTAGE_HOURS_TIMES        = 44;
//    G_CHG_OVER_VOLTAGE_MINUTES_TIMES           = 45;
//    G_OVER_LOADING_MINUTES_TIMES             = 46;
//    G_FASTER_CHARGING_MINUTES_TIMES          = 47;
//    G_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES      = 48;
//    G_CHARGING_IN_LOW_TEMP_MINUTES_TIMES       = 49;
//
//    G_STORE_IN_LOW_TEMP1_HOURS_TIMES         = 50;
//    G_STORE_IN_LOW_TEMP2_HOURS_TIMES         = 51;
//    G_STORE_IN_LOW_TEMP3_HOURS_TIMES         = 52;
//    G_STORE_IN_LOW_TEMP4_HOURS_TIMES         = 53;
//
//    G_STORE_IN_HIGH_TEMP1_MINUTES_TIMES      = 54;
//    G_STORE_IN_HIGH_TEMP2_MINUTES_TIMES      = 55;
//    G_STORE_IN_HIGH_TEMP3_MINUTES_TIMES      = 56;
//    G_STORE_IN_HIGH_TEMP4_MINUTES_TIMES      = 57;
//    G_STORE_IN_HIGH_TEMP5_MINUTES_TIMES      = 58;
//    G_RECORD_3rd_TRACKING_DATA_COUNT         = 59;
//    ////////////////////////////////////////////////////////////////////////////
//    _500mS_Counter = 0;
//    _1_Min_Counter = 0;
//    WriteRecordingData_Minutes_Counter = 0;
//    RecordingPolling_Start_Delay_Counter = 0;
//
//    sg_Recording_3rd_Status = 0;
//    sg_Recording_3rd_1_Min_Counter = 0;
//    sg_Recording_4th_Status = 0;
//
//
//    sg_STATIC_OVER_VOLTAGE_HOURS_TIMES_COUNT = 0;
//    sg_CHG_OVER_VOLTAGE_MINUTES_TIMES_COUNT = 0;
//    //sg_OVER_LOADING_MINUTES_TIMES_COUNT = 0;
//    //sg_FASTER_CHARGING_MINUTES_TIMES_COUNT = 0;
//    sg_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_COUNT = 0;
//    sg_CHARGING_IN_LOW_TEMP_MINUTES_TIMES_COUNT = 0;
//    sg_STORE_IN_LOW_TEMP1_HOURS_TIMES_COUNT = 0;
//    sg_STORE_IN_LOW_TEMP2_HOURS_TIMES_COUNT = 0;
//    sg_STORE_IN_LOW_TEMP3_HOURS_TIMES_COUNT = 0;
//    sg_STORE_IN_LOW_TEMP4_HOURS_TIMES_COUNT = 0;
////    sg_STORE_IN_HIGH_TEMP1_MINUTES_TIMES_COUNT = 0;
////    sg_STORE_IN_HIGH_TEMP2_MINUTES_TIMES_COUNT = 0;
////    sg_STORE_IN_HIGH_TEMP3_MINUTES_TIMES_COUNT = 0;
////    sg_STORE_IN_HIGH_TEMP4_MINUTES_TIMES_COUNT = 0;
////    sg_STORE_IN_HIGH_TEMP5_MINUTES_TIMES_COUNT = 0;
//
//    NTC_ADC_MAX_Lower_Temp = 0;
//    NTC_ADC_MIN_Higher_Temp = 0;
//
//    ///////////////////////////////////////////////////////////////////////////
//
//    sg_LOW_TEMP1_IN_DSG_ACT_RECORD_MINUTES_Times = 0;
//    sg_LOW_TEMP2_IN_DSG_ACT_RECORD_MINUTES_Times = 0;
//    sg_LOW_TEMP3_IN_DSG_ACT_RECORD_MINUTES_Times = 0;
//
//    //EEPROM_Storing_Step = 0;
//}
void SysInfo_init(){

    //updated Data
    G_RECORD_DATA_COUNT    =  RECORD_DATA_COUNT_EEPROM;
    G_MAX_DSG_C_ADC_RECORD =  MAX_DSG_C_ADC_RECORD_EEPROM;
    G_MAX_CHG_C_ADC_RECORD =  MAX_CHG_C_ADC_RECORD_EEPROM;
    G_MAX_VBAT_ADC_RECORD  =  MAX_VBAT_ADC_RECORD_EEPROM;
    G_MIN_VBAT_ADC_RECORD  =  MIN_VBAT_ADC_RECORD_EEPROM;
    G_MAX_VBAT_SocLo_ADC_RECORD  =  MAX_VBAT_SocLo_ADC_RECORD_EEPROM;
    G_MAX_VBAT_SocHi_ADC_RECORD  =  MAX_VBAT_SocHi_ADC_RECORD_EEPROM;

    G_DSG_MAX_TH1_ADC_RECORD   =  DSG_MAX_TH1_ADC_RECORD_EEPROM;
    G_DSG_MIN_TH1_ADC_RECORD   =  DSG_MIN_TH1_ADC_RECORD_EEPROM;
    G_DSG_MAX_TH2_ADC_RECORD   =  DSG_MAX_TH2_ADC_RECORD_EEPROM;
    G_DSG_MIN_TH2_ADC_RECORD   =  DSG_MIN_TH2_ADC_RECORD_EEPROM;

    G_CHG_Cycle_Count_RECORD = CHG_Cycle_Count_RECORD_EEPROM;
    sg_CHG_ADC_AccumulatingQ_RECORD = CHG_ADC_AccumulatingQ_RECORD_EEPROM;


    ////////////////////////////////////////////////////////////////////////////
    sg_DSG_ADC_AccumulatingQ_RECORD = DSG_ADC_AccumulatingQ_RECORD_EEPROM;
    G_DSG_Cycle_Count_RECORD = DSG_Cycle_Count_RECORD_EEPROM;

    G_CHG_MAX_TH1_ADC_RECORD = CHG_MAX_TH1_ADC_RECORD_EEPROM;
    G_CHG_MIN_TH1_ADC_RECORD = CHG_MIN_TH1_ADC_RECORD_EEPROM;
    G_CHG_MAX_TH2_ADC_RECORD = CHG_MAX_TH2_ADC_RECORD_EEPROM;
    G_CHG_MIN_TH2_ADC_RECORD = CHG_MIN_TH2_ADC_RECORD_EEPROM;

    G_OVP_TIMES		 = G_OVP_TIMES_RECORD_EEPROM ;
    G_UVP_TIMES		 = G_UVP_TIMES_RECORD_EEPROM ;
    G_COCP_TIMES	 = G_COCP_TIMES_RECORD_EEPROM;
    G_DOCP_TIMES	 = G_DOCP_TIMES_RECORD_EEPROM;

    G_TH1_CHG_UTP_TIMES = G_TH1_CHG_UTP_TIMES_RECORD_EEPROM;
    G_TH2_CHG_UTP_TIMES = G_TH2_CHG_UTP_TIMES_RECORD_EEPROM;

    G_CHG_TH1_OTP_TIMES  = G_CHG_TH1_OTP_TIMES_RECORD_EEPROM;
    G_CHG_TH2_OTP_TIMES  = G_CHG_TH2_OTP_TIMES_RECORD_EEPROM;

    G_DSG_TH1_LOW_CURRENT_OTP_TIMES   = G_DSG_TH1_LOW_CURRENT_OTP_TIMES_RECORD_EEPROM;
    G_DSG_TH1_HIGH_CURRENT_OTP_TIMES  = G_DSG_TH1_HIGH_CURRENT_OTP_TIMES_RECORD_EEPROM;
    G_DSG_TH2_LOW_CURRENT_OTP_TIMES   = G_DSG_TH2_LOW_CURRENT_OTP_TIMES_RECORD_EEPROM;
    G_DSG_TH2_HIGH_CURRENT_OTP_TIMES  = G_DSG_TH2_HIGH_CURRENT_OTP_TIMES_RECORD_EEPROM;

    G_RECORD_2nd_DATA_COUNT = RECORD_2nd_DATA_COUNT_EEPROM;
    ////////////////////////////////////////////////////////////////////////////
    G_REAL_FCC_UPDATE_TIMES                  = REAL_FCC_UPDATE_TIMES_RECORD_EEPROM;
    G_Real_FCC_In_CoulombCounter             = REAL_FCC_mAH_RECORD_EEPROM;

    G_STATIC_OVER_VOLTAGE_HOURS_TIMES        = STATIC_OVER_VOLTAGE_HOURS_TIMES_RECORD_EEPROM;
    G_CHG_OVER_VOLTAGE_MINUTES_TIMES           = CHG_OVER_VOLTAGE_MINUTES_TIMES_RECORD_EEPROM;
    G_OVER_LOADING_MINUTES_TIMES             = OVER_LOADING_MINUTES_TIMES_RECORD_EEPROM;
    G_FASTER_CHARGING_MINUTES_TIMES          = FASTER_CHARGING_MINUTES_TIMES_RECORD_EEPROM;
    G_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES      = CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_RECORD_EEPROM;
    G_CHARGING_IN_LOW_TEMP_MINUTES_TIMES       = CHARGING_IN_LOW_TEMP_MINUTES_TIMES_RECORD_EEPROM;

    G_STORE_IN_LOW_TEMP1_HOURS_TIMES         = STORE_IN_LOW_TEMP1_HOURS_TIMES_RECORD_EEPROM;
    G_STORE_IN_LOW_TEMP2_HOURS_TIMES         = STORE_IN_LOW_TEMP2_HOURS_TIMES_RECORD_EEPROM;
    G_STORE_IN_LOW_TEMP3_HOURS_TIMES         = STORE_IN_LOW_TEMP3_HOURS_TIMES_RECORD_EEPROM;
    G_STORE_IN_LOW_TEMP4_HOURS_TIMES         = STORE_IN_LOW_TEMP4_HOURS_TIMES_RECORD_EEPROM;

    G_STORE_IN_HIGH_TEMP1_MINUTES_TIMES      = STORE_IN_HIGH_TEMP1_MINUTES_TIMES_RECORD_EEPROM;
    G_STORE_IN_HIGH_TEMP2_MINUTES_TIMES      = STORE_IN_HIGH_TEMP2_MINUTES_TIMES_RECORD_EEPROM;
    G_STORE_IN_HIGH_TEMP3_MINUTES_TIMES      = STORE_IN_HIGH_TEMP3_MINUTES_TIMES_RECORD_EEPROM;
    G_STORE_IN_HIGH_TEMP4_MINUTES_TIMES      = STORE_IN_HIGH_TEMP4_MINUTES_TIMES_RECORD_EEPROM;
    G_STORE_IN_HIGH_TEMP5_MINUTES_TIMES      = STORE_IN_HIGH_TEMP5_MINUTES_TIMES_RECORD_EEPROM;
    G_RECORD_3rd_TRACKING_DATA_COUNT         = RECORD_3rd_TRACKING_DATA_COUNT_EEPROM;
    ////////////////////////////////////////////////////////////////////////////
    G_Last_FCC_Updated_Values                = Last_Record_FCC_mAh_RECORD_EEPROM;
    ////////////////////////////////////////////////////////////////////////////
    _500mS_Counter = 0;
    _1_Min_Counter = 0;
    WriteRecordingData_Minutes_Counter = 0;
    RecordingPolling_Start_Delay_Counter = 0;

    sg_Recording_3rd_Status = 0;
    sg_Recording_3rd_1_Min_Counter = 0;
    sg_Recording_4th_Status = 0;


    sg_STATIC_OVER_VOLTAGE_HOURS_TIMES_COUNT = 0;
    sg_CHG_OVER_VOLTAGE_MINUTES_TIMES_COUNT = 0;
    sg_CHG_OVER_VOLTAGE_MINUTES_TIMES_COUNT = sg_CHG_OVER_VOLTAGE_MINUTES_TIMES_COUNT;
    //sg_OVER_LOADING_MINUTES_TIMES_COUNT = 0;
    //sg_FASTER_CHARGING_MINUTES_TIMES_COUNT = 0;
    sg_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_COUNT = 0;
    sg_CHARGING_IN_LOW_TEMP_MINUTES_TIMES_COUNT = 0;
    sg_STORE_IN_LOW_TEMP1_HOURS_TIMES_COUNT = 0;
    sg_STORE_IN_LOW_TEMP2_HOURS_TIMES_COUNT = 0;
    sg_STORE_IN_LOW_TEMP3_HOURS_TIMES_COUNT = 0;
    sg_STORE_IN_LOW_TEMP4_HOURS_TIMES_COUNT = 0;
//    sg_STORE_IN_HIGH_TEMP1_MINUTES_TIMES_COUNT = 0;
//    sg_STORE_IN_HIGH_TEMP2_MINUTES_TIMES_COUNT = 0;
//    sg_STORE_IN_HIGH_TEMP3_MINUTES_TIMES_COUNT = 0;
//    sg_STORE_IN_HIGH_TEMP4_MINUTES_TIMES_COUNT = 0;
//    sg_STORE_IN_HIGH_TEMP5_MINUTES_TIMES_COUNT = 0;

    NTC_ADC_MAX_Lower_Temp = 0;
    NTC_ADC_MIN_Higher_Temp = 0;

    /////////////////////////////////////////////////////////////////////////////

    sg_LOW_TEMP1_IN_DSG_ACT_RECORD_MINUTES_Times = LOW_TEMP1_IN_DSG_ACT_RECORD_MINUTES_EEPROM;
    sg_LOW_TEMP2_IN_DSG_ACT_RECORD_MINUTES_Times = LOW_TEMP2_IN_DSG_ACT_RECORD_MINUTES_EEPROM;
    sg_LOW_TEMP3_IN_DSG_ACT_RECORD_MINUTES_Times = LOW_TEMP3_IN_DSG_ACT_RECORD_MINUTES_EEPROM;
    //EEPROM_Storing_Step = 0;

    g_Recording_SystemActivatedMinutes = RECORDING_System_Activated_Times_Minutes_For_1_Hours;
    G_System_Activated_TotalHours = RECORDING_System_Activated_Times_For_TotalHours;
    /////////////////////////////////////////////////////////////////////////////
//#define G_ul_Current_InSleepingMode_Times                   (*((unsigned long *)(&G_Current_InSleepingMode_Times_Hi)))
//#define G_ul_NowTotalTimes_Without_Charging_Minutes         (*((unsigned long *)(&G_NowTotalTimes_Without_Charging_Minutes_Hi)))
//#define G_ul_NowTotalTimes_Without_DisCharging_Minutes      (*((unsigned long *)(&G_NowTotalTimes_Without_DisCharging_Minutes_Hi)))
//
    G_ul_LastTotalTimes_Without_Charging_Minutes = LastTotalTimes_Without_Charging_Minutes_RECORD_EEPROM;
    G_ul_MaxTotalTimes_Without_Charging_Minutes = MaxTotalTimes_Without_Charging_Minutes_RECORD_EEPROM;
    G_ul_LastTotalTimes_Without_DisCharging_Minutes = LastTotalTimes_Without_DisCharging_Minutes_RECORD_EEPROM;
    G_ul_MaxTotalTimes_Without_DisCharging_Minutes = MaxTotalTimes_Without_DisCharging_Minutes_RECORD_EEPROM;

    G_Last_ChargingTimes_Minutes = Last_ChargingTimes_Minutes_RECORD_EEPROM;
    G_Max_ChargingTimes_Minutes = Max_ChargingTimes_Minutes_RECORD_EEPROM;
}
void UpdatedSystemRecordingInfoForPolling(){

    if(RecordingPolling_Start_Delay_Counter >= RecordingPolling_Start_Delay_CycleTimes){

        //Compare MAX/MIN data and updated
        if(G_DSG_Current_ADC > G_MAX_DSG_C_ADC_RECORD){
            G_MAX_DSG_C_ADC_RECORD = G_DSG_Current_ADC;
        }
        if(G_CHG_Current_ADC > G_MAX_CHG_C_ADC_RECORD){
            G_MAX_CHG_C_ADC_RECORD = G_CHG_Current_ADC;
        }


        //VBAT 最大值改為平均
//        if(G_VBAT_ADC > G_MAX_VBAT_ADC_RECORD){
//            G_MAX_VBAT_ADC_RECORD = G_VBAT_ADC;
//        }
        if(G_AVG_Battery_Voltage_ADC > G_MAX_VBAT_ADC_RECORD){
            G_MAX_VBAT_ADC_RECORD = G_AVG_Battery_Voltage_ADC;
        }
        if(G_VBAT_ADC < G_MIN_VBAT_ADC_RECORD){
            G_MIN_VBAT_ADC_RECORD = G_VBAT_ADC;
        }

        if( G_Module_Status & Current_Dir_CHG){
            if(G_Device_Interface_Status & ADP_SOC_STATUS){
                if(G_VBAT_ADC > G_MAX_VBAT_SocHi_ADC_RECORD){
                    G_MAX_VBAT_SocHi_ADC_RECORD = G_VBAT_ADC;
                }
            }else{
                if(G_VBAT_ADC > G_MAX_VBAT_SocLo_ADC_RECORD){
                    G_MAX_VBAT_SocLo_ADC_RECORD = G_VBAT_ADC;
                }
            }
        }

        if( G_Module_Status & Current_Dir_CHG){
            //chg
            if(G_NTC1_ADC > G_CHG_MAX_TH1_ADC_RECORD){
                G_CHG_MAX_TH1_ADC_RECORD = G_NTC1_ADC;
            }
            if(G_NTC1_ADC < G_CHG_MIN_TH1_ADC_RECORD){
                G_CHG_MIN_TH1_ADC_RECORD = G_NTC1_ADC;
            }
#if (_ENABLE_NTC_2_DETECTION_ == 1)
            if(G_NTC2_ADC > G_CHG_MAX_TH2_ADC_RECORD){
                G_CHG_MAX_TH2_ADC_RECORD = G_NTC2_ADC;
            }
            if(G_NTC2_ADC < G_CHG_MIN_TH2_ADC_RECORD){
                G_CHG_MIN_TH2_ADC_RECORD = G_NTC2_ADC;
            }
#endif
        //}else if( G_Module_Status & Current_Dir_DSG) {
        }else {
            //dsg, static
            if(G_NTC1_ADC > G_DSG_MAX_TH1_ADC_RECORD){
                G_DSG_MAX_TH1_ADC_RECORD = G_NTC1_ADC;
            }
            if(G_NTC1_ADC < G_DSG_MIN_TH1_ADC_RECORD){
                G_DSG_MIN_TH1_ADC_RECORD = G_NTC1_ADC;
            }
#if (_ENABLE_NTC_2_DETECTION_ == 1)
            if(G_NTC2_ADC > G_DSG_MAX_TH2_ADC_RECORD){
                G_DSG_MAX_TH2_ADC_RECORD = G_NTC2_ADC;
            }
            if(G_NTC2_ADC < G_DSG_MIN_TH2_ADC_RECORD){
                G_DSG_MIN_TH2_ADC_RECORD = G_NTC2_ADC;
            }
#endif
        }//if( G_Module_Status & Current_Dir_CHG){ - else

        Updated3rdTrackingRecordInfoForPolling();

    }else{
        RecordingPolling_Start_Delay_Counter++;
    }

    // updated AccumulatingQ_RECORD
    G_CHG_ADC_AccumulatingQ_RECORD_Lo = (unsigned int)sg_CHG_ADC_AccumulatingQ_RECORD;
    G_CHG_ADC_AccumulatingQ_RECORD_Hi = (unsigned int)(sg_CHG_ADC_AccumulatingQ_RECORD >> 16);

    G_DSG_ADC_AccumulatingQ_RECORD_Lo = (unsigned int)sg_DSG_ADC_AccumulatingQ_RECORD;
    G_DSG_ADC_AccumulatingQ_RECORD_Hi = (unsigned int)(sg_DSG_ADC_AccumulatingQ_RECORD >> 16);

//    ////////////////////////////////////////////////////////////////////////////////////////////////////
//    // updated DSG AccumulatingQ
//    G_Current_DSG_ADC_AccumulatingQ_Lo = (unsigned int)sg_Current_DSG_Test_ADC_AccumulatingQ;
//    G_Current_DSG_ADC_AccumulatingQ_Hi = (unsigned int)(sg_Current_DSG_Test_ADC_AccumulatingQ >> 16);
//    if(G_Current_DSG_ADC_AccumulatingQ_Hi >= UINT_MAX_VALUES_TH){
//        sg_Current_DSG_Test_ADC_AccumulatingQ = 0;
//    }
//    // updated CHG AccumulatingQ
//    G_Current_CHG_ADC_AccumulatingQ_Lo = (unsigned int)sg_Current_CHG_Test_ADC_AccumulatingQ;
//    G_Current_CHG_ADC_AccumulatingQ_Hi = (unsigned int)(sg_Current_CHG_Test_ADC_AccumulatingQ >> 16);
//    if(G_Current_CHG_ADC_AccumulatingQ_Hi >= UINT_MAX_VALUES_TH){
//        sg_Current_CHG_Test_ADC_AccumulatingQ = 0;
//    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //Calculation Recording data time for writing to EEPROM
    _1_Min_Counter++;
    if(_1_Min_Counter >= _1_Min_CycleTimes_For_RecordingData){
        _1_Min_Counter = 0;
        WriteRecordingData_Minutes_Counter++;
        //CoulombCounterForOneSecond();
    }else{
        //_1_Min_Counter++;
    }

    if(WriteRecordingData_Minutes_Counter >= WriteRecordingData_Minutes){
        WriteRecordingData_Minutes_Counter = 0;
        G_Device_Interface_Status |= SYS_INFO_RECORD_TO_EEPROM;
        //EEPROM_Storing_Step = 0;
        //WriteSystemRecordingInfoToEEPROM();
    }

    ////////////////////////////////////////////////////////////////////////////
    // For Coulomb Counter
    _500mS_Counter++;
    if(_500mS_Counter >= _500mS_CycleTimes_For_CoulombCounter){
        _500mS_Counter = 0;
        CoulombCounterForHalfSecond();
        G_NTC1_Real_0p1_KelvinDegree = Get_KelvinDegree_By_NTC_ADC(G_NTC1_ADC);
#if (_ENABLE_NTC_2_DETECTION_ == 1)
        G_NTC2_Real_0p1_KelvinDegree = Get_KelvinDegree_By_NTC_ADC(G_NTC2_ADC);
#endif

    }else{
        //_500mS_Counter++;
    }
    ////////////////////////////////////////
    //  _DUI_Set_Adapter_SOC
    if((G_CHG_Cycle_Count_RECORD >= Cycle_Count_FOR_CHG_1st_TH) && (G_CHG_Cycle_Count_RECORD < Cycle_Count_FOR_CHG_2nd_TH)){
        _DUI_Set_Adapter_SOC(DeviceOn);
    }else{
        if(G_Module_Function_Status & LOW_TEMP_SOC_SET){
            _DUI_Set_Adapter_SOC(DeviceOn);
        }else{
            _DUI_Set_Adapter_SOC(DeviceOff);
        }
    }
//
//    ///////////////////////////////////////////////////////////////////////////
//    //Storing Infor. To EEPROM
//    if(G_Device_Interface_Status & SYS_INFO_RECORD_TO_EEPROM){
//        switch(EEPROM_Storing_Step){
//            case Storing_AccumulatingQ:
//                WriteAccumulatingQToEEPROM();
//                break;
//            case Storing_MaxMinVbatCurr:
//                WriteMaxMinVbatCurrToEEPROM();
//                break;
//            case Storing_MaxMin_NTC:
//                WriteMaxMin_NTC_ToEEPROM();
//                break;
//            case Storing_OVUV_OC_UT:
//                Write_OVUV_OC_UT_ToEEPROM();
//                break;
//            case Storing_DSG_CHG_OTP:
//                Write_DSG_CHG_OTP_ToEEPROM();
//                break;
//            case Storing_Last_Step:
//            default:
//                G_Device_Interface_Status &= ~SYS_INFO_RECORD_TO_EEPROM;
//                EEPROM_Storing_Step = 0;
//                break;
//        }
//        EEPROM_Storing_Step++;
//    }else{
//        EEPROM_Storing_Step = 0;
//    }//if(G_Device_Interface_Status & SYS_INFO_RECORD_TO_EEPROM){
}

void Storing_Infor_To_EEPROM_By_Step(unsigned char step){
        switch(step){
            case Storing_AccumulatingQ:
                WriteAccumulatingQToEEPROM();
                break;
            case Storing_MaxMinVbatCurr:
                WriteMaxMinVbatCurrToEEPROM();
                break;
            case Storing_MaxMin_NTC:
                WriteMaxMin_NTC_ToEEPROM();
                break;
            case Storing_OVUV_OC_UT:
                Write_OVUV_OC_UT_ToEEPROM();
                break;
            case Storing_DSG_CHG_OTP:
                Write_DSG_CHG_OTP_ToEEPROM();
                break;
            case Storing_FCC_Update:
                Write_FCC_Update_ToEEPROM();
                break;
            case Storing_3rd_Chg_Dsg:
                Write_3rd_Chg_Dsg_ToEEPROM();
                break;
            case Storing_3rd_Low_Temp:
                Write_3rd_Low_Temp_ToEEPROM();
                break;
            case Storing_3rd_High_Temp:
                Write_3rd_High_Temp_ToEEPROM();
                break;
            case Storing_4rd_Low_Temp_in_Act:
                Write_4rd_Low_Temp_in_Act_ToEEPROM();
                break;
            case Storing_Count_DSG_CHG_Time_1:
                Write_Count_DSG_CHG_TIME_1_ToEEPROM();
                break;
            case Storing_Count_DSG_CHG_Time_2:
                Write_Count_DSG_CHG_TIME_2_ToEEPROM();
                break;
            case Storing_Last_Step:
            default:
                break;
        }
}
void CoulombCounterForHalfSecond(void){
    if( G_Module_Status & Current_Dir_CHG){
        sg_CHG_ADC_AccumulatingQ_RECORD += G_CHG_Current_ADC;
        if(sg_CHG_ADC_AccumulatingQ_RECORD >= ADC_AccQ_FOR_CHG_TH){
            sg_CHG_ADC_AccumulatingQ_RECORD = 0;
            G_CHG_Cycle_Count_RECORD++;
        }
    }else{
        if( G_Module_Status & Current_Dir_DSG){
            sg_DSG_ADC_AccumulatingQ_RECORD += G_DSG_Current_ADC;
            if(sg_DSG_ADC_AccumulatingQ_RECORD >= ADC_AccQ_FOR_DSG_TH){
                sg_DSG_ADC_AccumulatingQ_RECORD = 0;
                G_DSG_Cycle_Count_RECORD++;
            }
        }
    }
    if(G_CHG_Cycle_Count_RECORD >= UINT_MAX_VALUES_TH){
        G_CHG_Cycle_Count_RECORD = UINT_MAX_VALUES_TH;
    }
    if(G_DSG_Cycle_Count_RECORD >= UINT_MAX_VALUES_TH){
        G_DSG_Cycle_Count_RECORD = UINT_MAX_VALUES_TH;
    }
}


void Updated3rdTrackingRecordInfoForPolling(){

#if (_ENABLE_NTC_2_DETECTION_ == 1)

    NTC_ADC_MAX_Lower_Temp = (G_NTC1_ADC > G_NTC2_ADC)? G_NTC1_ADC : G_NTC2_ADC;
    NTC_ADC_MIN_Higher_Temp = (G_NTC1_ADC < G_NTC2_ADC)? G_NTC1_ADC : G_NTC2_ADC;
#else
    G_NTC2_ADC = 0;
    NTC_ADC_MAX_Lower_Temp = G_NTC1_ADC;
    NTC_ADC_MIN_Higher_Temp = G_NTC1_ADC;
#endif

    if(G_Module_Status & Current_Dir_Static){
        /////////////////////////////////////////////////////////////
        // in Current_Dir_Static
        if(G_VBAT_ADC > RECORDING_ADC_OVER_VOLTAGE_TH){
            sg_Recording_3rd_Status |= fSTATIC_OVER_VOLTAGE;
        }else if(G_VBAT_ADC < RECORDING_ADC_OVER_VOLTAGE_TH){
            sg_Recording_3rd_Status &= ~fSTATIC_OVER_VOLTAGE;
            sg_STATIC_OVER_VOLTAGE_HOURS_TIMES_COUNT = 0;
        }
    }else{
        sg_Recording_3rd_Status &= ~fSTATIC_OVER_VOLTAGE;
        sg_STATIC_OVER_VOLTAGE_HOURS_TIMES_COUNT = 0;
    }
    if(G_Module_Status & Current_Dir_DSG){
        /////////////////////////////////////////////////////////////
        // in Current_Dir_DSG
        if(G_DSG_Current_ADC > RECORDING_ADC_DSG_OVER_CURRENT_TH){
            sg_Recording_3rd_Status |= fOVER_LOADING;
        }else if(G_DSG_Current_ADC < RECORDING_ADC_DSG_OVER_CURRENT_TH){
            sg_Recording_3rd_Status &= ~fOVER_LOADING;
            //sg_OVER_LOADING_MINUTES_TIMES_COUNT = 0;
        }
    }else{
        sg_Recording_3rd_Status &= ~fOVER_LOADING;
        //sg_OVER_LOADING_MINUTES_TIMES_COUNT = 0;
    }

    if(G_Module_Status & Current_Dir_CHG){
        /////////////////////////////////////////////////////////////
        // in Current_Dir_CHG
        //=========================================================//
        // sg_CHG_OVER_VOLTAGE_MINUTES_TIMES_COUNT
        if(G_VBAT_ADC > RECORDING_ADC_OVER_VOLTAGE_TH){
            sg_Recording_3rd_Status |= fCHG_OVER_VOLTAGE;
        }else if(G_VBAT_ADC < RECORDING_ADC_OVER_VOLTAGE_TH){
            sg_Recording_3rd_Status &= ~fCHG_OVER_VOLTAGE;
            sg_CHG_OVER_VOLTAGE_MINUTES_TIMES_COUNT = 0;
        }
        //=========================================================//
        // sg_FASTER_CHARGING_MINUTES_TIMES_COUNT
        if(G_CHG_Current_ADC > RECORDING_ADC_CHG_FASTER_CHARGING_CURRENT_TH){
            sg_Recording_3rd_Status |= fCHG_FASTER_CHARGING;
        }else if(G_CHG_Current_ADC < RECORDING_ADC_CHG_FASTER_CHARGING_CURRENT_TH){
            sg_Recording_3rd_Status &= ~fCHG_FASTER_CHARGING;
            //sg_FASTER_CHARGING_MINUTES_TIMES_COUNT = 0;
        }
        //=========================================================//
        // sg_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_COUNT
        if(NTC_ADC_MIN_Higher_Temp < RECORDING_ADC_HIGH_TEMP_TH_FOR_CHARGING){
            sg_Recording_3rd_Status |= fCHARGING_IN_HIGH_TEMP;
        }else if(NTC_ADC_MIN_Higher_Temp > RECORDING_ADC_HIGH_TEMP_TH_FOR_CHARGING){
            sg_Recording_3rd_Status &= ~fCHARGING_IN_HIGH_TEMP;
            sg_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_COUNT = 0;
        }
        //=========================================================//
        // sg_CHARGING_IN_LOW_TEMP_MINUTES_TIMES_COUNT
        if(NTC_ADC_MAX_Lower_Temp > RECORDING_ADC_LOW_TEMP_TH_FOR_CHARGING){
            sg_Recording_3rd_Status |= fCHARGING_IN_LOW_TEMP;
        }else if(NTC_ADC_MAX_Lower_Temp < RECORDING_ADC_LOW_TEMP_TH_FOR_CHARGING){
            sg_Recording_3rd_Status &= ~fCHARGING_IN_LOW_TEMP;
            sg_CHARGING_IN_LOW_TEMP_MINUTES_TIMES_COUNT = 0;
        }
    }else{
        //=========================================================//
        // release sg_CHG_OVER_VOLTAGE_MINUTES_TIMES_COUNT
        sg_Recording_3rd_Status &= ~fCHG_OVER_VOLTAGE;
        sg_CHG_OVER_VOLTAGE_MINUTES_TIMES_COUNT = 0;
        //=========================================================//
        // release sg_FASTER_CHARGING_MINUTES_TIMES_COUNT
        sg_Recording_3rd_Status &= ~fCHG_FASTER_CHARGING;
        //sg_FASTER_CHARGING_MINUTES_TIMES_COUNT = 0;
        //=========================================================//
        // release sg_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_COUNT
        sg_Recording_3rd_Status &= ~fCHARGING_IN_HIGH_TEMP;
        sg_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_COUNT = 0;
        //=========================================================//
        // release sg_CHARGING_IN_LOW_TEMP_MINUTES_TIMES_COUNT
        sg_Recording_3rd_Status &= ~fCHARGING_IN_LOW_TEMP;
        sg_CHARGING_IN_LOW_TEMP_MINUTES_TIMES_COUNT = 0;
    }
    ////////////////////////////////////////////////////////////////////////
    if(NTC_ADC_MAX_Lower_Temp > RECORDING_ADC_LOW_TEMP_GRADE_TH1){
        sg_Recording_3rd_Status |= fSTORE_IN_LOW_TEMP1;
    }else{
        sg_Recording_3rd_Status &= ~fSTORE_IN_LOW_TEMP1;
        sg_STORE_IN_LOW_TEMP1_HOURS_TIMES_COUNT = 0;
    }
    if(NTC_ADC_MAX_Lower_Temp > RECORDING_ADC_LOW_TEMP_GRADE_TH2){
        sg_Recording_3rd_Status |= fSTORE_IN_LOW_TEMP2;
    }else{
        sg_Recording_3rd_Status &= ~fSTORE_IN_LOW_TEMP2;
        sg_STORE_IN_LOW_TEMP2_HOURS_TIMES_COUNT = 0;
    }
    if(NTC_ADC_MAX_Lower_Temp > RECORDING_ADC_LOW_TEMP_GRADE_TH3){
        sg_Recording_3rd_Status |= fSTORE_IN_LOW_TEMP3;
    }else{
        sg_Recording_3rd_Status &= ~fSTORE_IN_LOW_TEMP3;
        sg_STORE_IN_LOW_TEMP3_HOURS_TIMES_COUNT = 0;
    }
    if(NTC_ADC_MAX_Lower_Temp > RECORDING_ADC_LOW_TEMP_GRADE_TH4){
        sg_Recording_3rd_Status |= fSTORE_IN_LOW_TEMP4;
    }else{
        sg_Recording_3rd_Status &= ~fSTORE_IN_LOW_TEMP4;
        sg_STORE_IN_LOW_TEMP4_HOURS_TIMES_COUNT = 0;
    }
    //////////////////////////////////////////////////////////////////////

    if(NTC_ADC_MIN_Higher_Temp < RECORDING_ADC_HIGH_TEMP_GRADE_TH1){
        sg_Recording_3rd_Status |= fSTORE_IN_HIGH_TEMP1;
    }else{
        sg_Recording_3rd_Status &= ~fSTORE_IN_HIGH_TEMP1;
        //sg_STORE_IN_HIGH_TEMP1_MINUTES_TIMES_COUNT = 0;
    }
    if(NTC_ADC_MIN_Higher_Temp < RECORDING_ADC_HIGH_TEMP_GRADE_TH2){
        sg_Recording_3rd_Status |= fSTORE_IN_HIGH_TEMP2;
    }else{
        sg_Recording_3rd_Status &= ~fSTORE_IN_HIGH_TEMP2;
        //sg_STORE_IN_HIGH_TEMP2_MINUTES_TIMES_COUNT = 0;
    }
    if(NTC_ADC_MIN_Higher_Temp < RECORDING_ADC_HIGH_TEMP_GRADE_TH3){
        sg_Recording_3rd_Status |= fSTORE_IN_HIGH_TEMP3;
    }else{
        sg_Recording_3rd_Status &= ~fSTORE_IN_HIGH_TEMP3;
        //sg_STORE_IN_HIGH_TEMP3_MINUTES_TIMES_COUNT = 0;
    }
    if(NTC_ADC_MIN_Higher_Temp < RECORDING_ADC_HIGH_TEMP_GRADE_TH4){
        sg_Recording_3rd_Status |= fSTORE_IN_HIGH_TEMP4;
    }else{
        sg_Recording_3rd_Status &= ~fSTORE_IN_HIGH_TEMP4;
        //sg_STORE_IN_HIGH_TEMP4_MINUTES_TIMES_COUNT = 0;
    }
    if(NTC_ADC_MIN_Higher_Temp < RECORDING_ADC_HIGH_TEMP_GRADE_TH5){
        sg_Recording_3rd_Status |= fSTORE_IN_HIGH_TEMP5;
    }else{
        sg_Recording_3rd_Status &= ~fSTORE_IN_HIGH_TEMP5;
        //sg_STORE_IN_HIGH_TEMP5_MINUTES_TIMES_COUNT = 0;
    }



    if(G_Module_Status & Current_Dir_DSG){

        ////////////////////////////////////////////////////////////////////////
        if(NTC_ADC_MAX_Lower_Temp > RECORDING_ADC_LOW_TEMP_IN_DSG_ACT_TH1){
            sg_Recording_4th_Status |= fLOW_TEMP1_IN_DSG_ACT;
        }else{
            sg_Recording_4th_Status &= ~fLOW_TEMP1_IN_DSG_ACT;
        }
        if(NTC_ADC_MAX_Lower_Temp > RECORDING_ADC_LOW_TEMP_IN_DSG_ACT_TH2){
            sg_Recording_4th_Status |= fLOW_TEMP2_IN_DSG_ACT;
        }else{
            sg_Recording_4th_Status &= ~fLOW_TEMP2_IN_DSG_ACT;
        }
        if(NTC_ADC_MAX_Lower_Temp > RECORDING_ADC_LOW_TEMP_IN_DSG_ACT_TH3){
            sg_Recording_4th_Status |= fLOW_TEMP3_IN_DSG_ACT;
        }else{
            sg_Recording_4th_Status &= ~fLOW_TEMP3_IN_DSG_ACT;
        }
    }else{
        sg_Recording_4th_Status &= ~fLOW_TEMP1_IN_DSG_ACT;
        sg_Recording_4th_Status &= ~fLOW_TEMP2_IN_DSG_ACT;
        sg_Recording_4th_Status &= ~fLOW_TEMP3_IN_DSG_ACT;
    }
    //////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //1 miuntes Recording data time : (section start)
    sg_Recording_3rd_1_Min_Counter++;
    if(sg_Recording_3rd_1_Min_Counter >= _1_Min_CycleTimes_For_RecordingData){
        sg_Recording_3rd_1_Min_Counter = 0;
        CountAndUpdated3rdTrackingRecordInfo_in_1_min();
    }else{
        //sg_Recording_3rd_1_Min_Counter++;
    }
    //1 miuntes Recording data time : (section stop)
    ////////////////////////////////////////////////////////////////////////////////////////////////////
}


void CountAndUpdated3rdTrackingRecordInfo_in_1_min(){

    ///////////////////////////////////////////////////////////////////
    if(sg_Recording_3rd_Status & fSTATIC_OVER_VOLTAGE){
        sg_STATIC_OVER_VOLTAGE_HOURS_TIMES_COUNT++;
        if(sg_STATIC_OVER_VOLTAGE_HOURS_TIMES_COUNT >= 60){
            G_STATIC_OVER_VOLTAGE_HOURS_TIMES++;
            if(G_STATIC_OVER_VOLTAGE_HOURS_TIMES >= UINT_MAX_VALUES_TH){
                G_STATIC_OVER_VOLTAGE_HOURS_TIMES = UINT_MAX_VALUES_TH;
            }
            sg_STATIC_OVER_VOLTAGE_HOURS_TIMES_COUNT = 0;
        }
    }else{
        sg_STATIC_OVER_VOLTAGE_HOURS_TIMES_COUNT = 0;
    }
    ///////////////////////////////////////////////////////////////////
    if(sg_Recording_3rd_Status & fOVER_LOADING){
        G_OVER_LOADING_MINUTES_TIMES++;
        if(G_OVER_LOADING_MINUTES_TIMES >= UINT_MAX_VALUES_TH){
            G_OVER_LOADING_MINUTES_TIMES = UINT_MAX_VALUES_TH;
        }
    }
//    ///////////////////////////////////////////////////////////////////
//    //CHG_OVER_VOLTAGE count for 1 hour
//    if(sg_Recording_3rd_Status & fCHG_OVER_VOLTAGE){
//        sg_CHG_OVER_VOLTAGE_MINUTES_TIMES_COUNT++;
//        if(sg_CHG_OVER_VOLTAGE_MINUTES_TIMES_COUNT >= 60){
//            G_CHG_OVER_VOLTAGE_MINUTES_TIMES++;
//            if(G_CHG_OVER_VOLTAGE_MINUTES_TIMES >= UINT_MAX_VALUES_TH){
//                G_CHG_OVER_VOLTAGE_MINUTES_TIMES = UINT_MAX_VALUES_TH;
//            }
//            sg_CHG_OVER_VOLTAGE_MINUTES_TIMES_COUNT = 0;
//        }
//    }else{
//        sg_CHG_OVER_VOLTAGE_MINUTES_TIMES_COUNT = 0;
//    }
    ///////////////////////////////////////////////////////////////////
    //CHG_OVER_VOLTAGE count for 1 min
    if(sg_Recording_3rd_Status & fCHG_OVER_VOLTAGE){
        G_CHG_OVER_VOLTAGE_MINUTES_TIMES++;
        if(G_CHG_OVER_VOLTAGE_MINUTES_TIMES >= UINT_MAX_VALUES_TH){
            G_CHG_OVER_VOLTAGE_MINUTES_TIMES = UINT_MAX_VALUES_TH;
        }
    }

    ///////////////////////////////////////////////////////////////////
    if(sg_Recording_3rd_Status & fCHG_FASTER_CHARGING){
        G_FASTER_CHARGING_MINUTES_TIMES++;
        if(G_FASTER_CHARGING_MINUTES_TIMES >= UINT_MAX_VALUES_TH){
            G_FASTER_CHARGING_MINUTES_TIMES = UINT_MAX_VALUES_TH;
        }
    }
    ///////////////////////////////////////////////////////////////////
    //CHARGING_IN_HIGH_TEMP count for 10 mins
    if(sg_Recording_3rd_Status & fCHARGING_IN_HIGH_TEMP){
        sg_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_COUNT++;
        if(sg_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_COUNT >= 10){
            G_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES++;
            if(G_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES >= UINT_MAX_VALUES_TH){
                G_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES = UINT_MAX_VALUES_TH;
            }
            sg_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_COUNT = 0;
        }
    }else{
        sg_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_COUNT = 0;
    }
    ///////////////////////////////////////////////////////////////////
    //CHARGING_IN_LOW_TEMP count for 10 mins
    if(sg_Recording_3rd_Status & fCHARGING_IN_LOW_TEMP){
        sg_CHARGING_IN_LOW_TEMP_MINUTES_TIMES_COUNT++;
        if(sg_CHARGING_IN_LOW_TEMP_MINUTES_TIMES_COUNT >= 10){
            G_CHARGING_IN_LOW_TEMP_MINUTES_TIMES++;
            if(G_CHARGING_IN_LOW_TEMP_MINUTES_TIMES >= UINT_MAX_VALUES_TH){
                G_CHARGING_IN_LOW_TEMP_MINUTES_TIMES = UINT_MAX_VALUES_TH;
            }
            sg_CHARGING_IN_LOW_TEMP_MINUTES_TIMES_COUNT = 0;
        }
    }else{
        sg_CHARGING_IN_LOW_TEMP_MINUTES_TIMES_COUNT = 0;
    }
    ///////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////
    if(sg_Recording_3rd_Status & fSTORE_IN_LOW_TEMP1){
        sg_STORE_IN_LOW_TEMP1_HOURS_TIMES_COUNT++;
        if(sg_STORE_IN_LOW_TEMP1_HOURS_TIMES_COUNT >= 60){
            G_STORE_IN_LOW_TEMP1_HOURS_TIMES++;
            if(G_STORE_IN_LOW_TEMP1_HOURS_TIMES >= UINT_MAX_VALUES_TH){
                G_STORE_IN_LOW_TEMP1_HOURS_TIMES = UINT_MAX_VALUES_TH;
            }
            sg_STORE_IN_LOW_TEMP1_HOURS_TIMES_COUNT = 0;
        }
    }else{
        sg_STORE_IN_LOW_TEMP1_HOURS_TIMES_COUNT = 0;
    }
    ///////////////////////////////////////////////////////////////////
    if(sg_Recording_3rd_Status & fSTORE_IN_LOW_TEMP2){
        sg_STORE_IN_LOW_TEMP2_HOURS_TIMES_COUNT++;
        if(sg_STORE_IN_LOW_TEMP2_HOURS_TIMES_COUNT >= 60){
            G_STORE_IN_LOW_TEMP2_HOURS_TIMES++;
            if(G_STORE_IN_LOW_TEMP2_HOURS_TIMES >= UINT_MAX_VALUES_TH){
                G_STORE_IN_LOW_TEMP2_HOURS_TIMES = UINT_MAX_VALUES_TH;
            }
            sg_STORE_IN_LOW_TEMP2_HOURS_TIMES_COUNT = 0;
        }
    }else{
        sg_STORE_IN_LOW_TEMP2_HOURS_TIMES_COUNT = 0;
    }
    ///////////////////////////////////////////////////////////////////
    if(sg_Recording_3rd_Status & fSTORE_IN_LOW_TEMP3){
        sg_STORE_IN_LOW_TEMP3_HOURS_TIMES_COUNT++;
        if(sg_STORE_IN_LOW_TEMP3_HOURS_TIMES_COUNT >= 60){
            G_STORE_IN_LOW_TEMP3_HOURS_TIMES++;
            if(G_STORE_IN_LOW_TEMP3_HOURS_TIMES >= UINT_MAX_VALUES_TH){
                G_STORE_IN_LOW_TEMP3_HOURS_TIMES = UINT_MAX_VALUES_TH;
            }
            sg_STORE_IN_LOW_TEMP3_HOURS_TIMES_COUNT = 0;
        }
    }else{
        sg_STORE_IN_LOW_TEMP3_HOURS_TIMES_COUNT = 0;
    }
    ///////////////////////////////////////////////////////////////////
    if(sg_Recording_3rd_Status & fSTORE_IN_LOW_TEMP4){
        sg_STORE_IN_LOW_TEMP4_HOURS_TIMES_COUNT++;
        if(sg_STORE_IN_LOW_TEMP4_HOURS_TIMES_COUNT >= 60){
            G_STORE_IN_LOW_TEMP4_HOURS_TIMES++;
            if(G_STORE_IN_LOW_TEMP4_HOURS_TIMES >= UINT_MAX_VALUES_TH){
                G_STORE_IN_LOW_TEMP4_HOURS_TIMES = UINT_MAX_VALUES_TH;
            }
            sg_STORE_IN_LOW_TEMP4_HOURS_TIMES_COUNT = 0;
        }
    }else{
        sg_STORE_IN_LOW_TEMP4_HOURS_TIMES_COUNT = 0;
    }
    ///////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////
    if(sg_Recording_3rd_Status & fSTORE_IN_HIGH_TEMP1){
        G_STORE_IN_HIGH_TEMP1_MINUTES_TIMES++;
        if(G_STORE_IN_HIGH_TEMP1_MINUTES_TIMES >= UINT_MAX_VALUES_TH){
            G_STORE_IN_HIGH_TEMP1_MINUTES_TIMES = UINT_MAX_VALUES_TH;
        }
    }
    ///////////////////////////////////////////////////////////////////
    if(sg_Recording_3rd_Status & fSTORE_IN_HIGH_TEMP2){
        G_STORE_IN_HIGH_TEMP2_MINUTES_TIMES++;
        if(G_STORE_IN_HIGH_TEMP2_MINUTES_TIMES >= UINT_MAX_VALUES_TH){
            G_STORE_IN_HIGH_TEMP2_MINUTES_TIMES = UINT_MAX_VALUES_TH;
        }
    }
    ///////////////////////////////////////////////////////////////////
    if(sg_Recording_3rd_Status & fSTORE_IN_HIGH_TEMP3){
        G_STORE_IN_HIGH_TEMP3_MINUTES_TIMES++;
        if(G_STORE_IN_HIGH_TEMP3_MINUTES_TIMES >= UINT_MAX_VALUES_TH){
            G_STORE_IN_HIGH_TEMP3_MINUTES_TIMES = UINT_MAX_VALUES_TH;
        }
    }
    ///////////////////////////////////////////////////////////////////
    if(sg_Recording_3rd_Status & fSTORE_IN_HIGH_TEMP4){
        G_STORE_IN_HIGH_TEMP4_MINUTES_TIMES++;
        if(G_STORE_IN_HIGH_TEMP4_MINUTES_TIMES >= UINT_MAX_VALUES_TH){
            G_STORE_IN_HIGH_TEMP4_MINUTES_TIMES = UINT_MAX_VALUES_TH;
        }
    }
    ///////////////////////////////////////////////////////////////////
    if(sg_Recording_3rd_Status & fSTORE_IN_HIGH_TEMP5){
        G_STORE_IN_HIGH_TEMP5_MINUTES_TIMES++;
        if(G_STORE_IN_HIGH_TEMP5_MINUTES_TIMES >= UINT_MAX_VALUES_TH){
            G_STORE_IN_HIGH_TEMP5_MINUTES_TIMES = UINT_MAX_VALUES_TH;
        }
    }
    ///////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////
    if(sg_Recording_4th_Status & fLOW_TEMP1_IN_DSG_ACT){
        sg_LOW_TEMP1_IN_DSG_ACT_RECORD_MINUTES_Times++;
        if(sg_LOW_TEMP1_IN_DSG_ACT_RECORD_MINUTES_Times >= UINT_MAX_VALUES_TH){
            sg_LOW_TEMP1_IN_DSG_ACT_RECORD_MINUTES_Times = UINT_MAX_VALUES_TH;
        }
    }
    if(sg_Recording_4th_Status & fLOW_TEMP2_IN_DSG_ACT){
        sg_LOW_TEMP2_IN_DSG_ACT_RECORD_MINUTES_Times++;
        if(sg_LOW_TEMP2_IN_DSG_ACT_RECORD_MINUTES_Times >= UINT_MAX_VALUES_TH){
            sg_LOW_TEMP2_IN_DSG_ACT_RECORD_MINUTES_Times = UINT_MAX_VALUES_TH;
        }
    }
    if(sg_Recording_4th_Status & fLOW_TEMP3_IN_DSG_ACT){
        sg_LOW_TEMP3_IN_DSG_ACT_RECORD_MINUTES_Times++;
        if(sg_LOW_TEMP3_IN_DSG_ACT_RECORD_MINUTES_Times >= UINT_MAX_VALUES_TH){
            sg_LOW_TEMP3_IN_DSG_ACT_RECORD_MINUTES_Times = UINT_MAX_VALUES_TH;
        }
    }
    ///////////////////////////////////////////////////////////////////
    // For Test         ///////////////////////////////////////////////
    //G_RECORD_3rd_TRACKING_DATA_COUNT = G_STATIC_OVER_VOLTAGE_HOURS_TIMES + G_CHG_OVER_VOLTAGE_MINUTES_TIMES ;
    //G_RECORD_3rd_TRACKING_DATA_COUNT += G_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES + G_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES;
}
//#ifdef RAM_EXECUTION
//void WriteSystemRecordingInfoToEEPROM(){
//    //
//    //unsigned long data;
//    unsigned char count;
//    unsigned char flag;
//
//    //write record data count
//    G_RECORD_DATA_COUNT++;
//    //read data to internal
//    count = 0;
//    do{
//        flag = EEPROM_ReadWholeEEPROMToInternalMemory();
//        count++;
//        if(count > EEPROMWriteRetry){
//            break;
//        }
//    }while(flag == Data_Error);
//
//    //set data to internal
//    count = 0;
//    do{
//        flag = EEPROM_Set_Data_ToInternalMemory(RECORD_DATA_COUNT_EEPROM_Offset, (unsigned char *)(&G_RECORD_DATA_COUNT), RECORDING_DATA_NUMBER + RECORDING_DATA_NUMBER);
//        count++;
//        if(count > EEPROMWriteRetry){
//            break;
//        }
//    }while(flag == Data_Error);
//
//    //write data from internal to EEPROM
//    count = 0;
//    do{
//        flag = EEPROM_WriteWholeEEPROMFromInternalMemory();
//        count++;
//        if(count > EEPROMWriteRetry){
//            break;
//        }
//    }while(flag == Data_Error);
//
//}
//#else
void _DUI_Write_Int_Data_To_EEPROM(unsigned int Address_Offset, unsigned int Data){
    unsigned char chData1, chData2;
    unsigned char count;
    unsigned char flag;

    chData1 = (unsigned char)(Data >> 8);   //High byte at 1st index
    chData2 = (unsigned char)Data;   //Low byte at 2nd index
    count = 0;
    do{
        flag = _DUI_EEPROM_WriteByte(Address_Offset, chData1);
        count++;
        if(count > EEPROMWriteRetry){
            break;
        }
    }while(flag == Func_Fail);
    count = 0;
    do{
        flag = _DUI_EEPROM_WriteByte(Address_Offset + 1, chData2);
        count++;
        if(count > EEPROMWriteRetry){
            break;
        }
    }while(flag == Func_Fail);
}

void WriteAccumulatingQToEEPROM(){
    unsigned char count;
    unsigned char flag;

    unsigned long data;
//    ////////////////////////////////////////////////////////////////////////////
//    //Test
//    G_RECORD_DATA_COUNT = 0x3330;
//    G_CHG_Cycle_Count_RECORD = 0x4440;
//
//    G_RECORD_DATA_COUNT++;
//    G_CHG_Cycle_Count_RECORD++;
//    data = G_RECORD_DATA_COUNT;
//    data = data << 16;
//    data |= G_CHG_Cycle_Count_RECORD;
//    count = 0;
//    do{
//    GPIO_HIGH(LED1_PORT, LED1_PIN);
//        flag = _DUI_EEPROM_WriteDoubleWord(RECORD_DATA_COUNT_EEPROM_Offset, data);
//    GPIO_LOW(LED1_PORT, LED1_PIN);
//    _DUI_delay_cycles(100);     //100 = 550us at CCLK=8MHz.
//        count++;
//        if(count > EEPROMWriteRetry){
//            break;
//        }
//    }while(flag == Func_Fail);
//
//    G_RECORD_DATA_COUNT++;
//    G_CHG_Cycle_Count_RECORD++;
//    data = G_RECORD_DATA_COUNT;
//    data = data << 16;
//    data |= G_CHG_Cycle_Count_RECORD;
//    count = 0;
//    do{
//    GPIO_HIGH(LED1_PORT, LED1_PIN);
//        flag = _DUI_EEPROM_WriteDoubleWord(RECORD_DATA_COUNT_EEPROM_Offset+4, data);
//    GPIO_LOW(LED1_PORT, LED1_PIN);
//    _DUI_delay_cycles(100);     //100 = 550us at CCLK=8MHz.
//        count++;
//        if(count > EEPROMWriteRetry){
//            break;
//        }
//    }while(flag == Func_Fail);
//
//    G_RECORD_DATA_COUNT++;
//    G_CHG_Cycle_Count_RECORD++;
//    data = G_RECORD_DATA_COUNT;
//    data = data << 16;
//    data |= G_CHG_Cycle_Count_RECORD;
//    count = 0;
//    do{
//    GPIO_HIGH(LED1_PORT, LED1_PIN);
//        flag = _DUI_EEPROM_WriteDoubleWord(RECORD_DATA_COUNT_EEPROM_Offset+8, data);
//    GPIO_LOW(LED1_PORT, LED1_PIN);
//    _DUI_delay_cycles(100);     //100 = 550us at CCLK=8MHz.
//        count++;
//        if(count > EEPROMWriteRetry){
//            break;
//        }
//    }while(flag == Func_Fail);
//
//    G_RECORD_DATA_COUNT++;
//    G_CHG_Cycle_Count_RECORD++;
//    data = G_RECORD_DATA_COUNT;
//    data = data << 16;
//    data |= G_CHG_Cycle_Count_RECORD;
//    count = 0;
//    do{
//    GPIO_HIGH(LED1_PORT, LED1_PIN);
//        flag = _DUI_EEPROM_WriteDoubleWord(RECORD_DATA_COUNT_EEPROM_Offset+12, data);
//    GPIO_LOW(LED1_PORT, LED1_PIN);
//    _DUI_delay_cycles(100);     //100 = 550us at CCLK=8MHz.
//        count++;
//        if(count > EEPROMWriteRetry){
//            break;
//        }
//    }while(flag == Func_Fail);
//
//    return;
//    //Test
//    ////////////////////////////////////////////////////////////////////////////

    if(G_CHG_Cycle_Count_RECORD != CHG_Cycle_Count_RECORD_EEPROM){
        ////////////////////////////////////////////////////////////////////////////
        // write word data to eeprom :G_RECORD_DATA_COUNT, G_CHG_Cycle_Count_RECORD
        G_RECORD_DATA_COUNT++;
        if(G_RECORD_DATA_COUNT >= UINT_MAX_VALUES_TH){
            G_RECORD_DATA_COUNT = UINT_MAX_VALUES_TH;
        }
        data = G_RECORD_DATA_COUNT;
        data = data << 16;
        data |= G_CHG_Cycle_Count_RECORD;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(RECORD_DATA_COUNT_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }

    ////////////////////////////////////////////////////////////////////////////
    //write word data (G_CHG_ADC_AccumulatingQ_RECORD_Hi and Lo ) to eeprom
    data = G_CHG_ADC_AccumulatingQ_RECORD_Hi;
    data = data << 16;
    data |= G_CHG_ADC_AccumulatingQ_RECORD_Lo;
    if(data != CHG_ADC_AccumulatingQ_RECORD_EEPROM){
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(CHG_ADC_AccumulatingQ_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }

    ////////////////////////////////////////////////////////////////////////////
    //write word data (G_DSG_ADC_AccumulatingQ_RECORD_Hi and Lo ) to eeprom
    data = G_DSG_ADC_AccumulatingQ_RECORD_Hi;
    data = data << 16;
    data |= G_DSG_ADC_AccumulatingQ_RECORD_Lo;
    if(data != DSG_ADC_AccumulatingQ_RECORD_EEPROM){
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(DSG_ADC_AccumulatingQ_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }

    if(G_DSG_Cycle_Count_RECORD != DSG_Cycle_Count_RECORD_EEPROM){
        ////////////////////////////////////////////////////////////////////////////
        // write word data to eeprom :G_DSG_Cycle_Count_RECORD, RESERVED_Recording
        data = G_DSG_Cycle_Count_RECORD;
        data = data << 16;
        data |= 0;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(DSG_Cycle_Count_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }

}
void WriteMaxMinVbatCurrToEEPROM(){
    unsigned char count;
    unsigned char flag;

    unsigned long data;
    if((G_MAX_DSG_C_ADC_RECORD != MAX_DSG_C_ADC_RECORD_EEPROM) || (G_MAX_CHG_C_ADC_RECORD != MAX_CHG_C_ADC_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data (max dsg and chg adc) to eeprom
        data = G_MAX_DSG_C_ADC_RECORD;
        data = data << 16;
        data |= G_MAX_CHG_C_ADC_RECORD;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(MAX_DSG_C_ADC_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }

    if((G_MAX_VBAT_ADC_RECORD != MAX_VBAT_ADC_RECORD_EEPROM) || (G_MIN_VBAT_ADC_RECORD != MIN_VBAT_ADC_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data (max/min vbat adc) to eeprom
        data = G_MAX_VBAT_ADC_RECORD;
        data = data << 16;
        data |= G_MIN_VBAT_ADC_RECORD;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(MAX_VBAT_ADC_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }

    if((G_MAX_VBAT_SocLo_ADC_RECORD != MAX_VBAT_SocLo_ADC_RECORD_EEPROM) || (G_MAX_VBAT_SocHi_ADC_RECORD != MAX_VBAT_SocHi_ADC_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data (max vbat chg adc) to eeprom
        data = G_MAX_VBAT_SocLo_ADC_RECORD;
        data = data << 16;
        data |= G_MAX_VBAT_SocHi_ADC_RECORD;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(MAX_VBAT_SocLo_ADC_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }
}
void WriteMaxMin_NTC_ToEEPROM(){
    unsigned char count;
    unsigned char flag;

    unsigned long data;
    if((G_DSG_MAX_TH1_ADC_RECORD != DSG_MAX_TH1_ADC_RECORD_EEPROM) || (G_DSG_MIN_TH1_ADC_RECORD != DSG_MIN_TH1_ADC_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data (max/min dsg NTC1 adc) to eeprom
        data = G_DSG_MAX_TH1_ADC_RECORD;
        data = data << 16;
        data |= G_DSG_MIN_TH1_ADC_RECORD;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(DSG_MAX_TH1_ADC_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }

#if (_ENABLE_NTC_2_DETECTION_ == 1)
    if((G_DSG_MAX_TH2_ADC_RECORD != DSG_MAX_TH2_ADC_RECORD_EEPROM) || (G_DSG_MIN_TH2_ADC_RECORD != DSG_MIN_TH2_ADC_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data (max/min dsg NTC2 adc) to eeprom
        data = G_DSG_MAX_TH2_ADC_RECORD;
        data = data << 16;
        data |= G_DSG_MIN_TH2_ADC_RECORD;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(DSG_MAX_TH2_ADC_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }
#endif
    if((G_CHG_MAX_TH1_ADC_RECORD != CHG_MAX_TH1_ADC_RECORD_EEPROM) || (G_CHG_MIN_TH1_ADC_RECORD != CHG_MIN_TH1_ADC_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data (max/min chg NTC1 adc) to eeprom
        data = G_CHG_MAX_TH1_ADC_RECORD;
        data = data << 16;
        data |= G_CHG_MIN_TH1_ADC_RECORD;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(CHG_MAX_TH1_ADC_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }
#if (_ENABLE_NTC_2_DETECTION_ == 1)
    if((G_CHG_MAX_TH2_ADC_RECORD != CHG_MAX_TH2_ADC_RECORD_EEPROM) || (G_CHG_MIN_TH2_ADC_RECORD != CHG_MIN_TH2_ADC_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data (max/min chg NTC2 adc) to eeprom
        data = G_CHG_MAX_TH2_ADC_RECORD;
        data = data << 16;
        data |= G_CHG_MIN_TH2_ADC_RECORD;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(CHG_MAX_TH2_ADC_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }
#endif
}


void Write_OVUV_OC_UT_ToEEPROM(){
    unsigned char count;
    unsigned char flag;

    unsigned long data;
    if((G_OVP_TIMES != G_OVP_TIMES_RECORD_EEPROM) || (G_UVP_TIMES != G_UVP_TIMES_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data (OVP UVP Times) to eeprom
        data = G_OVP_TIMES;
        data = data << 16;
        data |= G_UVP_TIMES;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(G_OVP_TIMES_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }

    if((G_COCP_TIMES != G_COCP_TIMES_RECORD_EEPROM) || (G_DOCP_TIMES != G_DOCP_TIMES_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data (COCP DOCP Times) to eeprom
        data = G_COCP_TIMES;
        data = data << 16;
        data |= G_DOCP_TIMES;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(G_COCP_TIMES_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }
    if((G_TH1_CHG_UTP_TIMES != G_TH1_CHG_UTP_TIMES_RECORD_EEPROM) || (G_TH2_CHG_UTP_TIMES != G_TH2_CHG_UTP_TIMES_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data (NTC1/NTC2 UTP Times) to eeprom
        data = G_TH1_CHG_UTP_TIMES;
        data = data << 16;
        data |= G_TH2_CHG_UTP_TIMES;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(G_TH1_CHG_UTP_TIMES_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }

}
void Write_DSG_CHG_OTP_ToEEPROM(){

    unsigned char count;
    unsigned char flag;
    unsigned char modified;

    unsigned long data;
    modified = 0;
    if((G_CHG_TH1_OTP_TIMES != G_CHG_TH1_OTP_TIMES_RECORD_EEPROM) || (G_CHG_TH2_OTP_TIMES != G_CHG_TH2_OTP_TIMES_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data (NTC1/NTC2 CHG OTP Times) to eeprom
        data = G_CHG_TH1_OTP_TIMES;
        data = data << 16;
        data |= G_CHG_TH2_OTP_TIMES;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(G_CHG_TH1_OTP_TIMES_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
        modified++;
    }

    if((G_DSG_TH1_LOW_CURRENT_OTP_TIMES != G_DSG_TH1_LOW_CURRENT_OTP_TIMES_RECORD_EEPROM) || (G_DSG_TH1_HIGH_CURRENT_OTP_TIMES != G_DSG_TH1_HIGH_CURRENT_OTP_TIMES_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data (NTC1 DSG OTP Low/High current Times) to eeprom
        data = G_DSG_TH1_LOW_CURRENT_OTP_TIMES;
        data = data << 16;
        data |= G_DSG_TH1_HIGH_CURRENT_OTP_TIMES;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(G_DSG_TH1_LOW_CURRENT_OTP_TIMES_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
        modified++;
    }
#if (_ENABLE_NTC_2_DETECTION_ == 1)
    if((G_DSG_TH2_LOW_CURRENT_OTP_TIMES != G_DSG_TH2_LOW_CURRENT_OTP_TIMES_RECORD_EEPROM) || (G_DSG_TH2_HIGH_CURRENT_OTP_TIMES != G_DSG_TH2_HIGH_CURRENT_OTP_TIMES_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data (NTC2 DSG OTP Low/High current Times) to eeprom
        data = G_DSG_TH2_LOW_CURRENT_OTP_TIMES;
        data = data << 16;
        data |= G_DSG_TH2_HIGH_CURRENT_OTP_TIMES;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(G_DSG_TH2_LOW_CURRENT_OTP_TIMES_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
        modified++;
    }
#endif
    if(modified > 0){
        ////////////////////////////////////////////////////////////////////////////
        //write word data (RECORD_2nd_DATA_COUNT) to eeprom
        G_RECORD_2nd_DATA_COUNT++;
        if(G_RECORD_2nd_DATA_COUNT >= UINT_MAX_VALUES_TH){
            G_RECORD_2nd_DATA_COUNT = UINT_MAX_VALUES_TH;
        }
        data = G_RECORD_2nd_DATA_COUNT;
        data = data << 16;
        data |= 0x00;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(RECORD_2nd_DATA_COUNT_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Write_FCC_Update_ToEEPROM(){

    unsigned char count;
    unsigned char flag;

    unsigned long data;
    unsigned char cdata1, cdata2;
    if((G_REAL_FCC_UPDATE_TIMES != REAL_FCC_UPDATE_TIMES_RECORD_EEPROM) || (G_Real_FCC_In_CoulombCounter != REAL_FCC_mAH_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data () to eeprom
        data = G_REAL_FCC_UPDATE_TIMES;
        data = data << 16;
        data |= G_Real_FCC_In_CoulombCounter;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(REAL_FCC_UPDATE_TIMES_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
        ////////////////////////////////////////////////////////////////////////////
        //write word G_Last_FCC_Updated_Values () to eeprom
        data = G_Last_FCC_Updated_Values;
        cdata2 = data;
        cdata1 = data >> 8;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteByte(Last_Record_FCC_mAh_RECORD_EEPROM_Offset, cdata1);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteByte(Last_Record_FCC_mAh_RECORD_EEPROM_Offset + 1, cdata2);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Write_3rd_Chg_Dsg_ToEEPROM(){

    unsigned char count;
    unsigned char flag;

    unsigned long data;
    if((G_STATIC_OVER_VOLTAGE_HOURS_TIMES != STATIC_OVER_VOLTAGE_HOURS_TIMES_RECORD_EEPROM) || (G_CHG_OVER_VOLTAGE_MINUTES_TIMES != CHG_OVER_VOLTAGE_MINUTES_TIMES_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data () to eeprom
        data = G_STATIC_OVER_VOLTAGE_HOURS_TIMES;
        data = data << 16;
        data |= G_CHG_OVER_VOLTAGE_MINUTES_TIMES;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(STATIC_OVER_VOLTAGE_HOURS_TIMES_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }
    if((G_OVER_LOADING_MINUTES_TIMES != OVER_LOADING_MINUTES_TIMES_RECORD_EEPROM) || (G_FASTER_CHARGING_MINUTES_TIMES != FASTER_CHARGING_MINUTES_TIMES_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data () to eeprom
        data = G_OVER_LOADING_MINUTES_TIMES;
        data = data << 16;
        data |= G_FASTER_CHARGING_MINUTES_TIMES;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(OVER_LOADING_MINUTES_TIMES_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }
    if((G_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES != CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_RECORD_EEPROM) || (G_CHARGING_IN_LOW_TEMP_MINUTES_TIMES != CHARGING_IN_LOW_TEMP_MINUTES_TIMES_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data () to eeprom
        data = G_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES;
        data = data << 16;
        data |= G_CHARGING_IN_LOW_TEMP_MINUTES_TIMES;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Write_3rd_Low_Temp_ToEEPROM(){

    unsigned char count;
    unsigned char flag;

    unsigned long data;
    if((G_STORE_IN_LOW_TEMP1_HOURS_TIMES != STORE_IN_LOW_TEMP1_HOURS_TIMES_RECORD_EEPROM) || (G_STORE_IN_LOW_TEMP2_HOURS_TIMES != STORE_IN_LOW_TEMP2_HOURS_TIMES_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data () to eeprom
        data = G_STORE_IN_LOW_TEMP1_HOURS_TIMES;
        data = data << 16;
        data |= G_STORE_IN_LOW_TEMP2_HOURS_TIMES;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(STORE_IN_LOW_TEMP1_HOURS_TIMES_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }
    if((G_STORE_IN_LOW_TEMP3_HOURS_TIMES != STORE_IN_LOW_TEMP3_HOURS_TIMES_RECORD_EEPROM) || (G_STORE_IN_LOW_TEMP4_HOURS_TIMES != STORE_IN_LOW_TEMP4_HOURS_TIMES_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data () to eeprom
        data = G_STORE_IN_LOW_TEMP3_HOURS_TIMES;
        data = data << 16;
        data |= G_STORE_IN_LOW_TEMP4_HOURS_TIMES;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(STORE_IN_LOW_TEMP3_HOURS_TIMES_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Write_3rd_High_Temp_ToEEPROM(){

    unsigned char count;
    unsigned char flag;

    unsigned long data;
    if((G_STORE_IN_HIGH_TEMP1_MINUTES_TIMES != STORE_IN_HIGH_TEMP1_MINUTES_TIMES_RECORD_EEPROM) || (G_STORE_IN_HIGH_TEMP2_MINUTES_TIMES != STORE_IN_HIGH_TEMP2_MINUTES_TIMES_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data () to eeprom
        data = G_STORE_IN_HIGH_TEMP1_MINUTES_TIMES;
        data = data << 16;
        data |= G_STORE_IN_HIGH_TEMP2_MINUTES_TIMES;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(STORE_IN_HIGH_TEMP1_MINUTES_TIMES_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }
    if((G_STORE_IN_HIGH_TEMP3_MINUTES_TIMES != STORE_IN_HIGH_TEMP3_MINUTES_TIMES_RECORD_EEPROM) || (G_STORE_IN_HIGH_TEMP4_MINUTES_TIMES != STORE_IN_HIGH_TEMP4_MINUTES_TIMES_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data () to eeprom
        data = G_STORE_IN_HIGH_TEMP3_MINUTES_TIMES;
        data = data << 16;
        data |= G_STORE_IN_HIGH_TEMP4_MINUTES_TIMES;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(STORE_IN_HIGH_TEMP3_MINUTES_TIMES_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }
    if((G_STORE_IN_HIGH_TEMP5_MINUTES_TIMES != STORE_IN_HIGH_TEMP5_MINUTES_TIMES_RECORD_EEPROM) || (G_RECORD_3rd_TRACKING_DATA_COUNT != RECORD_3rd_TRACKING_DATA_COUNT_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data () to eeprom
        data = G_STORE_IN_HIGH_TEMP5_MINUTES_TIMES;
        data = data << 16;
        data |= G_RECORD_3rd_TRACKING_DATA_COUNT;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(STORE_IN_HIGH_TEMP5_MINUTES_TIMES_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }
}
void Write_4rd_Low_Temp_in_Act_ToEEPROM(){
    unsigned char count;
    unsigned char flag;

    unsigned long data;
    if(sg_LOW_TEMP1_IN_DSG_ACT_RECORD_MINUTES_Times != LOW_TEMP1_IN_DSG_ACT_RECORD_MINUTES_EEPROM){
        ////////////////////////////////////////////////////////////////////////////
        //write word data () to eeprom
        data = sg_LOW_TEMP1_IN_DSG_ACT_RECORD_MINUTES_Times;
        data = data << 16;
        data |= sg_LOW_TEMP2_IN_DSG_ACT_RECORD_MINUTES_Times;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(LOW_TEMP1_IN_DSG_ACT_RECORD_MINUTES_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }
    if((sg_LOW_TEMP2_IN_DSG_ACT_RECORD_MINUTES_Times != LOW_TEMP2_IN_DSG_ACT_RECORD_MINUTES_EEPROM) || (sg_LOW_TEMP3_IN_DSG_ACT_RECORD_MINUTES_Times != LOW_TEMP3_IN_DSG_ACT_RECORD_MINUTES_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data () to eeprom
        data = sg_LOW_TEMP3_IN_DSG_ACT_RECORD_MINUTES_Times;
        data = data << 16;
        data |= G_System_Activated_TotalHours;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(LOW_TEMP3_IN_DSG_ACT_RECORD_MINUTES_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }

    ////////////////////////////////////////////////////////////////////////////
    //write word data () to eeprom
    data = RECORDING_Reserved_Data;
    data = data << 16;
    data |= g_Recording_SystemActivatedMinutes;
    count = 0;
    do{
        flag = _DUI_EEPROM_WriteDoubleWord(RECORDING_Reserved_Data_Offset, data);
        count++;
        if(count > EEPROMWriteRetry){
            break;
        }
    }while(flag == Func_Fail);


}

void Write_Count_DSG_CHG_TIME_1_ToEEPROM(){
    unsigned char count;
    unsigned char flag;

    unsigned long data;
    if(G_ul_LastTotalTimes_Without_Charging_Minutes != LastTotalTimes_Without_Charging_Minutes_RECORD_EEPROM){
        ////////////////////////////////////////////////////////////////////////////
        //write word data () to eeprom
        data = G_ul_LastTotalTimes_Without_Charging_Minutes;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(LastTotalTimes_Without_Charging_Minutes_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }
    if(G_ul_MaxTotalTimes_Without_Charging_Minutes != MaxTotalTimes_Without_Charging_Minutes_RECORD_EEPROM){
        ////////////////////////////////////////////////////////////////////////////
        //write word data () to eeprom
        data = G_ul_MaxTotalTimes_Without_Charging_Minutes;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(MaxTotalTimes_Without_Charging_Minutes_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }

    if(G_ul_LastTotalTimes_Without_DisCharging_Minutes != LastTotalTimes_Without_DisCharging_Minutes_RECORD_EEPROM){
        ////////////////////////////////////////////////////////////////////////////
        //write word data () to eeprom
        data = G_ul_LastTotalTimes_Without_DisCharging_Minutes;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(LastTotalTimes_Without_DisCharging_Minutes_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }
    if(G_ul_MaxTotalTimes_Without_DisCharging_Minutes != MaxTotalTimes_Without_DisCharging_Minutes_RECORD_EEPROM){
        ////////////////////////////////////////////////////////////////////////////
        //write word data () to eeprom
        data = G_ul_MaxTotalTimes_Without_DisCharging_Minutes;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(MaxTotalTimes_Without_DisCharging_Minutes_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }
}

void Write_Count_DSG_CHG_TIME_2_ToEEPROM(){
    unsigned char count;
    unsigned char flag;

    unsigned long data;
    if((G_Last_ChargingTimes_Minutes != Last_ChargingTimes_Minutes_RECORD_EEPROM) ||
       (G_Max_ChargingTimes_Minutes != Max_ChargingTimes_Minutes_RECORD_EEPROM)){
        ////////////////////////////////////////////////////////////////////////////
        //write word data () to eeprom
        data = G_Last_ChargingTimes_Minutes;
        data = data << 16;
        data |= G_Max_ChargingTimes_Minutes;
        count = 0;
        do{
            flag = _DUI_EEPROM_WriteDoubleWord(Last_ChargingTimes_Minutes_RECORD_EEPROM_Offset, data);
            count++;
            if(count > EEPROMWriteRetry){
                break;
            }
        }while(flag == Func_Fail);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Write_BAR_CODE_ID_To_EEPROM(){

    unsigned char count;
    unsigned char flag;
    unsigned char result;

    unsigned long data;
    unsigned char idx;
    idx = 2;
    result = Func_Complete;
    do{
        ////////////////////////////////////////////////////////////////////////////
        if((idx + 2) <= BAR_CODE_REAL_STORE_LENGTH){
            data = G_BAR_CODE_ID_Array[idx++];
            data = data << 8;
            data |= G_BAR_CODE_ID_Array[idx++];
            data = data << 8;
            data |= G_BAR_CODE_ID_Array[idx++];
            data = data << 8;
            data |= G_BAR_CODE_ID_Array[idx++];
            count = 0;
            do{
                flag = _DUI_EEPROM_WriteDoubleWord(BAR_CODE_Offset + idx - 6, data);
                count++;
                if(count > EEPROMWriteRetry){
                    break;
                }
            }while(flag == Func_Fail);
            if(flag == Func_Fail){
                result = Func_Fail;
            }
        }else{
            break;
        }
    }while(1);
    for(idx = 0; idx < BAR_CODE_ID_Array_Whole_Size; idx++){
        G_BAR_CODE_ID_Array[idx] = 0;
    }

    if(result == Func_Complete){
        _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, G_BAR_CODE_ID_Array + 1, 1, true, true);
    }else{
        _DUI_Communication_Send_Bytes_CheckSum(Respond_Error_Check_Code, G_BAR_CODE_ID_Array + 1, 1, true, true);
    }
}
//void WriteSystemRecordingInfoToEEPROM(){
//
//    unsigned char count;
//    unsigned char flag;
//
//    unsigned long data;
//    //unsigned int intData;
//    //unsigned char chData1, chData2;
//    //write word data (max dsg and chg adc) to eeprom
//    data = G_MAX_DSG_C_ADC_RECORD;
//    data = data << 16;
//    data |= G_MAX_CHG_C_ADC_RECORD;
//    count = 0;
//    do{
//        flag = _DUI_EEPROM_WriteDoubleWord(MAX_DSG_C_ADC_RECORD_EEPROM_Offset, data);
//        count++;
//        if(count > EEPROMWriteRetry){
//            break;
//        }
//    }while(flag == Func_Fail);
//    //write word data (max/min vbat adc) to eeprom
//    data = G_MAX_VBAT_ADC_RECORD;
//    data = data << 16;
//    data |= G_MIN_VBAT_ADC_RECORD;
//    count = 0;
//    do{
//        flag = _DUI_EEPROM_WriteDoubleWord(MAX_VBAT_ADC_RECORD_EEPROM_Offset, data);
//        count++;
//        if(count > EEPROMWriteRetry){
//            break;
//        }
//    }while(flag == Func_Fail);
//    //write word data (max vbat chg adc) to eeprom
//    data = G_MAX_VBAT_SocLo_ADC_RECORD;
//    data = data << 16;
//    data |= G_MAX_VBAT_SocHi_ADC_RECORD;
//    count = 0;
//    do{
//        flag = _DUI_EEPROM_WriteDoubleWord(MAX_VBAT_SocLo_ADC_RECORD_EEPROM_Offset, data);
//        count++;
//        if(count > EEPROMWriteRetry){
//            break;
//        }
//    }while(flag == Func_Fail);
//    //write word data (max/min th1 adc) to eeprom
//    data = G_DSG_MAX_TH1_ADC_RECORD;
//    data = data << 16;
//    data |= G_DSG_MIN_TH1_ADC_RECORD;
//    count = 0;
//    do{
//        flag = _DUI_EEPROM_WriteDoubleWord(DSG_MAX_TH1_ADC_RECORD_EEPROM_Offset, data);
//        count++;
//        if(count > EEPROMWriteRetry){
//            break;
//        }
//    }while(flag == Func_Fail);
//    //write word data (max/min th2 adc) to eeprom
//    data = G_DSG_MAX_TH2_ADC_RECORD;
//    data = data << 16;
//    data |= G_DSG_MIN_TH2_ADC_RECORD;
//    count = 0;
//    do{
//        flag = _DUI_EEPROM_WriteDoubleWord(DSG_MAX_TH2_ADC_RECORD_EEPROM_Offset, data);
//        count++;
//        if(count > EEPROMWriteRetry){
//            break;
//        }
//    }while(flag == Func_Fail);
//
//    //write bytes data ( G_RECORD_DATA_COUNT ) to eeprom
//    //write record data count
//    G_RECORD_DATA_COUNT++;
//
////    intData = G_RECORD_DATA_COUNT;
////    chData2 = (unsigned char)intData;   //Low byte
////    chData1 = (unsigned char)(intData >> 8);   //High byte
////    count = 0;
////    do{
////        flag = EEPROM_WriteByte(RECORD_DATA_COUNT_EEPROM_Offset, chData1);
////        count++;
////        if(count > EEPROMWriteRetry){
////            break;
////        }
////    }while(flag == Data_Error);
////    count = 0;
////    do{
////        flag = EEPROM_WriteByte(RECORD_DATA_COUNT_EEPROM_Offset + 1, chData2);
////        count++;
////        if(count > EEPROMWriteRetry){
////            break;
////        }
////    }while(flag == Data_Error);
//
//    //write word data (G_RECORD_DATA_COUNT and Cycle_Count_RECORD ) to eeprom
//    data = G_RECORD_DATA_COUNT;
//    data = data << 16;
//    data |= G_CHG_Cycle_Count_RECORD;
//    count = 0;
//    do{
//        flag = _DUI_EEPROM_WriteDoubleWord(RECORD_DATA_COUNT_EEPROM_Offset, data);
//        count++;
//        if(count > EEPROMWriteRetry){
//            break;
//        }
//    }while(flag == Func_Fail);
//
//    //write word data (G_CHG_ADC_AccumulatingQ_RECORD_Hi and Lo ) to eeprom
//    data = G_CHG_ADC_AccumulatingQ_RECORD_Hi;
//    data = data << 16;
//    data |= G_CHG_ADC_AccumulatingQ_RECORD_Lo;
//    count = 0;
//    do{
//        flag = _DUI_EEPROM_WriteDoubleWord(CHG_ADC_AccumulatingQ_RECORD_EEPROM_Offset, data);
//        count++;
//        if(count > EEPROMWriteRetry){
//            break;
//        }
//    }while(flag == Func_Fail);
//
//}
//#endif
//unsigned char SysInfo_init(){
//    unsigned char retry;
//    unsigned char flag;
//
//    flag = false;
//    retry = 0;
//    while(retry <= ReadMemory_RetryTimes){
//        //SetLed_DirectIO_BITs(0xff);
//        flag = EEPROM_ReadWholeMemory(uEEPROM_OBJ.eepromBytesArray, Eeprom_segment_Size);
//        //SetLed_DirectIO_BITs(0);
//        if(flag == Data_Success){
//            break;
//        }else{
//            retry++;
//        }
//    }
//    if(flag == Data_Error){
//        return Data_Error;
//    }
//    for(int i=0; i < Eeprom_segment_Size; i++){
//        uEEPROM_OBJ.eepromBytesArray[i] = 0;
//    }
//    return Data_Success;
//}








