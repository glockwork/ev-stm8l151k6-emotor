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
* Define																        *
********************************************************************************/

#define MOS_Fail_CycleTimes                 3  //unit:cycles ,  MOS_Fail_CycleTimes * TimerIntervalTimeBase_MS

#define CHG_Status_Delay_CycleTimes         10  //unit:cycles ,  CHG_Status_Delay_CycleTimes * TimerIntervalTimeBase_MS

///////////////////////////////////////////////////////////////////////////////////
/* sg_Protection_1_Status Control Bits */
/* For sg_Protection_1_Status ; unsigned int */
//Low byte
#define fCHG_UT_COUNT                   (0x0001)    //
#define fCHG_OTP_COUNT                  (0x0002)    //
#define fDSG_HIGH_CURRENT_OTP_COUNT     (0x0004)    //
#define fDSG_LOW_CURRENT_OTP_COUNT      (0x0008)    //
//#define fCHARGING_IN_HIGH_TEMP          (0x0010)
//#define fCHARGING_IN_LOW_TEMP           (0x0020)    //
//#define fSTORE_IN_LOW_TEMP1             (0x0040)    //
//#define fSTORE_IN_LOW_TEMP2             (0x0080)    //
////Hight byte
#define fCHG_Status_Start_Count          (0x0100)    //
#define fIn_CHG_Status                   (0x0200)    //
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
* Current File Define Function													*
********************************************************************************/
void GetAllADCValuesAndSetDirection();

/********************************************************************************
* Extern Variable																*
********************************************************************************/

/********************************************************************************
* Golbal Variable																*
********************************************************************************/


/********************************************************************************
* Local file Variable										                    *
********************************************************************************/
static unsigned char DSG_OC_Counter;
static unsigned char CHG_OC_Counter;
static unsigned char COC_Repeat_Counter;
static unsigned char Battery_OV_Counter;
static unsigned char Battery_UV_Counter;
static unsigned char DSG_Low_OT_Counter;
static unsigned char DSG_High_OT_Counter;
static unsigned char CHG_OT_Counter;
static unsigned char UT_Counter;

////////////////////////////////////////////////////////////////////////////////
static unsigned char AVG_ADC_CURRENT_ARRAY_Index;
static unsigned char STORE_AVG_ADC_CURRENT_Counter;
static unsigned int AVG_ADC_CURRENT_ARRAY[AVG_ADC_CURRENT_ARRAY_NUMS];
////////////////////////////////////////////////////////////////////////////////
static unsigned char AVG_ADC_VOLTAGE_ARRAY_Index;
static unsigned char STORE_AVG_ADC_VOLTAGE_Counter;
static unsigned int AVG_ADC_VOLTAGE_ARRAY[AVG_ADC_VOLTAGE_ARRAY_NUMS];

////////////////////////////////////////////////////////////////////////////////
static unsigned int NTC_ADC_MAX_Lower_Temp;
static unsigned int NTC_ADC_MIN_Higher_Temp;
////////////////////////////////////////////////////////////////////////////////
static unsigned int After_Battery_UV_Start_Counter;

static unsigned int System_1_Min_Flag_Counter;
static unsigned int AutoSleeping_Minutes_Counter;

void Record_And_Count_NTC_CHG_UTP_TIMES();
void Record_And_Count_NTC_CHG_OTP_TIMES();
void Record_And_Count_NTC_DSG_LOW_CURRENT_OTP_TIMES();
void Record_And_Count_NTC_DSG_HIGH_CURRENT_OTP_TIMES();
////////////////////////////////////////////////////////////////////////////////
unsigned int USB_OCP_Signal_Protection_Cycle_Counter;
unsigned int USB_OCP_Signal_Release_Cycle_Counter;
////////////////////////////////////////////////////////////////////////////////
static unsigned char BackLight_Blinking_Counter;
////////////////////////////////////////////////////////////////////////////////
unsigned int sg_Protection_1_Status;
////////////////////////////////////////////////////////////////////////////////
static unsigned char CHG_MOS_FAIL_Counter;
static unsigned char DSG_MOS_FAIL_Counter;
////////////////////////////////////////////////////////////////////////////////
static unsigned int Recording_1_Min_Counter;
unsigned char g_Recording_SystemActivatedMinutes;
////////////////////////////////////////////////////////////////////////////////
static unsigned char CHG_Status_Delay_Counter;
//G_System_Activated_TotalHours
/********************************************************************************
* 															                    *
********************************************************************************/
void InitProtectionPollingFuncVariables(void){
    G_Module_Status = 0;
    G_Module_Function_Status = 0;
    G_Add_Module_Function_Status = 0;
    //G_Auxiliary_Module_Status = 0;


    DSG_OC_Counter = 0;
    CHG_OC_Counter = 0;
    COC_Repeat_Counter = 0;
    Battery_OV_Counter = 0;
    Battery_UV_Counter = 0;
    DSG_Low_OT_Counter = 0;
    DSG_High_OT_Counter = 0;
    CHG_OT_Counter = 0;
    UT_Counter = 0;

    NTC_ADC_MAX_Lower_Temp = 0;
    NTC_ADC_MIN_Higher_Temp = 0;

    After_Battery_UV_Start_Counter = 0;
    System_1_Min_Flag_Counter = 0;
    AutoSleeping_Minutes_Counter = 0;

    for(AVG_ADC_CURRENT_ARRAY_Index = 0; AVG_ADC_CURRENT_ARRAY_Index < AVG_ADC_CURRENT_ARRAY_NUMS; AVG_ADC_CURRENT_ARRAY_Index++){
        AVG_ADC_CURRENT_ARRAY[AVG_ADC_CURRENT_ARRAY_Index] = 0;
    }
    AVG_ADC_CURRENT_ARRAY_Index = 0;
    STORE_AVG_ADC_CURRENT_Counter = 0;
    for(AVG_ADC_VOLTAGE_ARRAY_Index = 0; AVG_ADC_VOLTAGE_ARRAY_Index < AVG_ADC_VOLTAGE_ARRAY_NUMS; AVG_ADC_VOLTAGE_ARRAY_Index++){
        AVG_ADC_VOLTAGE_ARRAY[AVG_ADC_VOLTAGE_ARRAY_Index] = 0;
    }
    AVG_ADC_VOLTAGE_ARRAY_Index = 0;
    STORE_AVG_ADC_VOLTAGE_Counter = 0;



    USB_OCP_Signal_Protection_Cycle_Counter = 0;
    USB_OCP_Signal_Release_Cycle_Counter = 0;

    BackLight_Blinking_Counter = 0;

    ////////////////////////////////////////////////////////
    sg_Protection_1_Status = 0;
    ////////////////////////////////////////////////////////
    CHG_MOS_FAIL_Counter = 0;
    DSG_MOS_FAIL_Counter = 0;
    ////////////////////////////////////////////////////////
    Recording_1_Min_Counter = 0;
    CHG_Status_Delay_Counter =0;
}
/********************************************************************************
* 															                    *
********************************************************************************/
unsigned int GetAndSet_AVG_ADC_CURRENT(unsigned int dsg_adc){
    unsigned int i, sum;
    AVG_ADC_CURRENT_ARRAY[AVG_ADC_CURRENT_ARRAY_Index] = dsg_adc;
    AVG_ADC_CURRENT_ARRAY_Index++;
    if(AVG_ADC_CURRENT_ARRAY_Index >= AVG_ADC_CURRENT_ARRAY_NUMS){
        AVG_ADC_CURRENT_ARRAY_Index = 0;
    }
    sum = 0;
    for(i=0; i < AVG_ADC_CURRENT_ARRAY_NUMS; i++){
        sum += AVG_ADC_CURRENT_ARRAY[i];
    }
    return (sum >> 3);  // (= sum / 8)
}

unsigned int GetAndSet_AVG_ADC_VOLTAGE(unsigned int vol_adc){
    unsigned int i, sum;
    AVG_ADC_VOLTAGE_ARRAY[AVG_ADC_VOLTAGE_ARRAY_Index] = vol_adc;
    AVG_ADC_VOLTAGE_ARRAY_Index++;
    if(AVG_ADC_VOLTAGE_ARRAY_Index >= AVG_ADC_VOLTAGE_ARRAY_NUMS){
        AVG_ADC_VOLTAGE_ARRAY_Index = 0;
    }
    sum = 0;
    for(i=0; i < AVG_ADC_VOLTAGE_ARRAY_NUMS; i++){
        sum += AVG_ADC_VOLTAGE_ARRAY[i];
    }
    return (sum >> 2);  // (= sum / 4)
}

void UpdatedDetectingValues(){

    signed int temp;

    /////////////////////////////////////////////////////////////////////////////////////////////
    // ADC Scan
    //GPIO_HIGH(LED1_PORT, LED1_PIN);
    _DUI_ADC_Channels_Scan();
    //GPIO_LOW(LED1_PORT, LED1_PIN);

    /////////////////////////////////////////////////////////////////////////////////////////////
    // ADC Values Getting and calibration
    temp = _DUI_Get_ADC_Channel_Values(VBAT_CHANNEL_INDEX);
    temp = temp - VBAT_ADC_OFFSET;
    if(temp < 0){
        temp = 0;
    }
    G_VBAT_ADC = temp;

    temp = _DUI_Get_ADC_Channel_Values(ICHG_CHANNEL_INDEX);
    temp = temp - CHG_OP_ADC_OFFSET;
    if(temp < 0){
        temp = 0;
    }
    G_CHG_Current_ADC = temp;

    temp = _DUI_Get_ADC_Channel_Values(IDSG_CHANNEL_INDEX);
    temp = temp - DSG_OP_ADC_OFFSET;
    if(temp < 0){
        temp = 0;
    }
    G_DSG_Current_ADC = temp;

    temp = _DUI_Get_ADC_Channel_Values(NTC1_CHANNEL_INDEX);
    temp = temp - NTC1_ADC_OFFSET;
    if(temp < 0){
        temp = 0;
    }
    G_NTC1_ADC = temp;

#if (_ENABLE_NTC_2_DETECTION_ == 1)
    temp = _DUI_Get_ADC_Channel_Values(NTC2_CHANNEL_INDEX);
    temp = temp - NTC2_ADC_OFFSET;
    if(temp < 0){
        temp = 0;
    }
    G_NTC2_ADC = temp;
    NTC_ADC_MAX_Lower_Temp = (G_NTC1_ADC > G_NTC2_ADC)? G_NTC1_ADC : G_NTC2_ADC;
    NTC_ADC_MIN_Higher_Temp = (G_NTC1_ADC < G_NTC2_ADC)? G_NTC1_ADC : G_NTC2_ADC;
#else
    G_NTC2_ADC = 0;
    NTC_ADC_MAX_Lower_Temp = G_NTC1_ADC;
    NTC_ADC_MIN_Higher_Temp = G_NTC1_ADC;
#endif



    G_Vref_mVoltage = _DUI_Get_Vref_mVoltage();

}//void UpdatedDetectingValues(){

void UpdatedCurrentDirectionStatus(){

    /////////////////////////////////////////////////////////////////////////////////////////////
    // checking Current Direction status
    if((G_CHG_Current_ADC >= ADC_CURRENT_DETECT_FOR_CHG_STATUS) && (G_DSG_Current_ADC >= ADC_CURRENT_DETECT_FOR_DSG_STATUS)){
        if(G_DSG_Current_ADC >=  G_CHG_Current_ADC){
            ///////////////////////////////////////////////////
            //  in discharging status
            G_Module_Status |= Current_Dir_DSG;
            G_Module_Status &= ~Current_Dir_Static;
            //G_Module_Status &= ~Current_Dir_CHG;
            //sg_Protection_1_Status &= ~fIn_CHG_Status;
            G_Module_Status &= ~Current_Dir_CHG_No_Delay;
        }else{
            ////////////////////////////////////////////////////
            // in charging status
            ////////////////////////////////////////////////////
            G_Module_Status |= Current_Dir_CHG_No_Delay;
            //sg_Protection_1_Status |= fIn_CHG_Status;
            //G_Module_Status |= Current_Dir_CHG;
            G_Module_Status &= ~Current_Dir_Static;
            G_Module_Status &= ~Current_Dir_DSG;
        }
    }else{
        if(G_CHG_Current_ADC >= ADC_CURRENT_DETECT_FOR_CHG_STATUS){
            ////////////////////////////////////////////////////
            // in charging status
            ////////////////////////////////////////////////////
            G_Module_Status |= Current_Dir_CHG_No_Delay;
            //sg_Protection_1_Status |= fIn_CHG_Status;
            //G_Module_Status |= Current_Dir_CHG;
            G_Module_Status &= ~Current_Dir_Static;
            G_Module_Status &= ~Current_Dir_DSG;
        }else{
            ///////////////////////////////////////////////////
            //  in discharging status
            //(current direction include discharging and relaxation )
            if(G_DSG_Current_ADC >= ADC_CURRENT_DETECT_FOR_DSG_STATUS){
                // discharging
                G_Module_Status |= Current_Dir_DSG;
                G_Module_Status &= ~Current_Dir_Static;
                //G_Module_Status &= ~Current_Dir_CHG;
                //sg_Protection_1_Status &= ~fIn_CHG_Status;
                G_Module_Status &= ~Current_Dir_CHG_No_Delay;
            }else{
                // relaxation
                G_Module_Status |= Current_Dir_Static;
                G_Module_Status &= ~Current_Dir_DSG;
                //G_Module_Status &= ~Current_Dir_CHG;
                //sg_Protection_1_Status &= ~fIn_CHG_Status;
                G_Module_Status &= ~Current_Dir_CHG_No_Delay;
            }
        }//if(G_CHG_Current_ADC > ADC_CURRENT_DETECT_FOR_CHG_STATUS){ -else-
    }//else - if((G_CHG_Current_ADC >= ADC_CURRENT_DETECT_FOR_CHG_STATUS) && (G_DSG_Current_ADC >= ADC_CURRENT_DETECT_FOR_DSG_STATUS)){

    /////////////////////////////////////////////////////////////////////////////////////////////
    // CHG Status Delay
    /////////////////////////////////////////////////////////////////////////////////////////////
        //if(sg_Protection_1_Status & fIn_CHG_Status){
        if(G_Module_Status & Current_Dir_CHG_No_Delay){
            CHG_Status_Delay_Counter++;
            if(CHG_Status_Delay_Counter >= CHG_Status_Delay_CycleTimes){
                CHG_Status_Delay_Counter = 0;
                G_Module_Status |= Current_Dir_CHG;
            }
        }else {
            CHG_Status_Delay_Counter = 0;
            G_Module_Status &= ~Current_Dir_CHG;
        }
}//void UpdatedCurrentDirectionStatus(){

void Count_DSG_CHG_Times_ByMinutes(){
    if(G_Module_Status & Current_Dir_CHG){
        G_Current_ChargingTimes_Minutes++;
    }else{
        if(G_Current_ChargingTimes_Minutes != 0){
            G_Last_ChargingTimes_Minutes = G_Current_ChargingTimes_Minutes;
            if(G_Last_ChargingTimes_Minutes > G_Max_ChargingTimes_Minutes){
                G_Max_ChargingTimes_Minutes = G_Last_ChargingTimes_Minutes;
            }
            G_Current_ChargingTimes_Minutes = 0;
        }
    }
    ////////////////////////////
    if(G_Module_Status & Current_Dir_CHG){
        if(G_ul_NowTotalTimes_Without_Charging_Minutes != 0){
            G_ul_LastTotalTimes_Without_Charging_Minutes = G_ul_NowTotalTimes_Without_Charging_Minutes;
            if( G_ul_LastTotalTimes_Without_Charging_Minutes > G_ul_MaxTotalTimes_Without_Charging_Minutes){
                G_ul_MaxTotalTimes_Without_Charging_Minutes = G_ul_LastTotalTimes_Without_Charging_Minutes;
            }
        }
        G_ul_NowTotalTimes_Without_Charging_Minutes = 0;
    }else{
        G_ul_NowTotalTimes_Without_Charging_Minutes++;
    }
    //////////////////////
    if(G_Module_Status & Current_Dir_DSG){
        if(G_ul_NowTotalTimes_Without_DisCharging_Minutes != 0){
            G_ul_LastTotalTimes_Without_DisCharging_Minutes = G_ul_NowTotalTimes_Without_DisCharging_Minutes;
            if( G_ul_LastTotalTimes_Without_DisCharging_Minutes > G_ul_MaxTotalTimes_Without_DisCharging_Minutes){
                G_ul_MaxTotalTimes_Without_DisCharging_Minutes = G_ul_LastTotalTimes_Without_DisCharging_Minutes;
            }
        }
        G_ul_NowTotalTimes_Without_DisCharging_Minutes = 0;
    }else{
        G_ul_NowTotalTimes_Without_DisCharging_Minutes++;
    }
}//void Count_DSG_CHG_Times_ByMinutes(){

void Protection_Polling_Function(void){
    //GPIO_HIGH(LED2_PORT, LED2_PIN);


    //signed int temp;

#if (_ENABLE_FOR_Monitoring_HW_PIC_STATUS_ == 1)
    _DUI_Updated_HW_CHG_DSG_Signal_Status();
#endif
    /////////////////////////////////////////////////////////////////////////////////////////////
    // System Avtivated Time count
    Recording_1_Min_Counter++;
    // 1 minute
    if(Recording_1_Min_Counter >= System_1_Min_Flag_CycleTimes){
        Recording_1_Min_Counter = 0;
        g_Recording_SystemActivatedMinutes++;
        Count_DSG_CHG_Times_ByMinutes();
    }
    // 1 hour
    if(g_Recording_SystemActivatedMinutes >= 60){
        g_Recording_SystemActivatedMinutes = 0;
        G_System_Activated_TotalHours++;
        if(G_System_Activated_TotalHours >= UINT_MAX_VALUES_TH){
            G_System_Activated_TotalHours = UINT_MAX_VALUES_TH;
        }
    }
//    /////////////////////////////////////////////////////////////////////////////////////////////
//    // ADC Scan
//    //GPIO_HIGH(LED1_PORT, LED1_PIN);
//    _DUI_ADC_Channels_Scan();
//    //GPIO_LOW(LED1_PORT, LED1_PIN);
//
//    /////////////////////////////////////////////////////////////////////////////////////////////
//    // ADC Values Getting and calibration
//    temp = _DUI_Get_ADC_Channel_Values(VBAT_CHANNEL_INDEX);
//    temp = temp - VBAT_ADC_OFFSET;
//    if(temp < 0){
//        temp = 0;
//    }
//    G_VBAT_ADC = temp;
//
//    temp = _DUI_Get_ADC_Channel_Values(ICHG_CHANNEL_INDEX);
//    temp = temp - CHG_OP_ADC_OFFSET;
//    if(temp < 0){
//        temp = 0;
//    }
//    G_CHG_Current_ADC = temp;
//
//    temp = _DUI_Get_ADC_Channel_Values(IDSG_CHANNEL_INDEX);
//    temp = temp - DSG_OP_ADC_OFFSET;
//    if(temp < 0){
//        temp = 0;
//    }
//    G_DSG_Current_ADC = temp;
//
//    temp = _DUI_Get_ADC_Channel_Values(NTC1_CHANNEL_INDEX);
//    temp = temp - NTC1_ADC_OFFSET;
//    if(temp < 0){
//        temp = 0;
//    }
//    G_NTC1_ADC = temp;
//
//#if (_ENABLE_NTC_2_DETECTION_ == 1)
//    temp = _DUI_Get_ADC_Channel_Values(NTC2_CHANNEL_INDEX);
//    temp = temp - NTC2_ADC_OFFSET;
//    if(temp < 0){
//        temp = 0;
//    }
//    G_NTC2_ADC = temp;
//    NTC_ADC_MAX_Lower_Temp = (G_NTC1_ADC > G_NTC2_ADC)? G_NTC1_ADC : G_NTC2_ADC;
//    NTC_ADC_MIN_Higher_Temp = (G_NTC1_ADC < G_NTC2_ADC)? G_NTC1_ADC : G_NTC2_ADC;
//#else
//    G_NTC2_ADC = 0;
//    NTC_ADC_MAX_Lower_Temp = G_NTC1_ADC;
//    NTC_ADC_MIN_Higher_Temp = G_NTC1_ADC;
//#endif
//
//
//
//    G_Vref_mVoltage = _DUI_Get_Vref_mVoltage();

    UpdatedDetectingValues();

//    /////////////////////////////////////////////////////////////////////////////////////////////
//    // checking Current Direction status
//    if((G_CHG_Current_ADC >= ADC_CURRENT_DETECT_FOR_CHG_STATUS) && (G_DSG_Current_ADC >= ADC_CURRENT_DETECT_FOR_DSG_STATUS)){
//        if(G_DSG_Current_ADC >=  G_CHG_Current_ADC){
//            ///////////////////////////////////////////////////
//            //  in discharging status
//            G_Module_Status |= Current_Dir_DSG;
//            G_Module_Status &= ~Current_Dir_Static;
//            //G_Module_Status &= ~Current_Dir_CHG;
//            sg_Protection_1_Status &= ~fIn_CHG_Status;
//        }else{
//            ////////////////////////////////////////////////////
//            // in charging status
//            ////////////////////////////////////////////////////
//            sg_Protection_1_Status |= fIn_CHG_Status;
//            //G_Module_Status |= Current_Dir_CHG;
//            G_Module_Status &= ~Current_Dir_Static;
//            G_Module_Status &= ~Current_Dir_DSG;
//        }
//    }else{
//        if(G_CHG_Current_ADC >= ADC_CURRENT_DETECT_FOR_CHG_STATUS){
//            ////////////////////////////////////////////////////
//            // in charging status
//            ////////////////////////////////////////////////////
//            sg_Protection_1_Status |= fIn_CHG_Status;
//            //G_Module_Status |= Current_Dir_CHG;
//            G_Module_Status &= ~Current_Dir_Static;
//            G_Module_Status &= ~Current_Dir_DSG;
//        }else{
//            ///////////////////////////////////////////////////
//            //  in discharging status
//            //(current direction include discharging and relaxation )
//            if(G_DSG_Current_ADC >= ADC_CURRENT_DETECT_FOR_DSG_STATUS){
//                // discharging
//                G_Module_Status |= Current_Dir_DSG;
//                G_Module_Status &= ~Current_Dir_Static;
//                //G_Module_Status &= ~Current_Dir_CHG;
//                sg_Protection_1_Status &= ~fIn_CHG_Status;
//            }else{
//                // relaxation
//                G_Module_Status |= Current_Dir_Static;
//                G_Module_Status &= ~Current_Dir_DSG;
//                //G_Module_Status &= ~Current_Dir_CHG;
//                sg_Protection_1_Status &= ~fIn_CHG_Status;
//            }
//        }//if(G_CHG_Current_ADC > ADC_CURRENT_DETECT_FOR_CHG_STATUS){ -else-
//    }//else - if((G_CHG_Current_ADC >= ADC_CURRENT_DETECT_FOR_CHG_STATUS) && (G_DSG_Current_ADC >= ADC_CURRENT_DETECT_FOR_DSG_STATUS)){
//
//    /////////////////////////////////////////////////////////////////////////////////////////////
//    // CHG Status Delay
//    /////////////////////////////////////////////////////////////////////////////////////////////
//        if(sg_Protection_1_Status & fIn_CHG_Status){
//            CHG_Status_Delay_Counter++;
//            if(CHG_Status_Delay_Counter >= CHG_Status_Delay_CycleTimes){
//                CHG_Status_Delay_Counter = 0;
//                G_Module_Status |= Current_Dir_CHG;
//            }
//        }else {
//            CHG_Status_Delay_Counter = 0;
//            G_Module_Status &= ~Current_Dir_CHG;
//        }

    UpdatedCurrentDirectionStatus();

    /////////////////////////////////////////////////////////////////////////////////////////////
    // Protection Flag Checking
    /////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    // checking if it's D_OC
    // compare if Discharging Current greater than ADC_DOC_PROTECTION,
    // it will be into DSG OC protection.
    // Delay 略小於設定值 (+- TimerIntervalTimeBase_MS)
    if(((G_Module_Status & Module_D_OC)==0) && G_DSG_Current_ADC >= ADC_DOC_PROTECTION){
        DSG_OC_Counter++;
        if(DSG_OC_Counter >= DSG_OC_Protection_Delay_Cycle){
            G_Module_Status |= Module_D_OC;
            DSG_OC_Counter = 0;
            G_DOCP_TIMES++;
            if(G_DOCP_TIMES >= UINT_MAX_VALUES_TH){
                G_DOCP_TIMES = UINT_MAX_VALUES_TH;
            }
            ///////////////////////////////////////////////////////////////////
            //Enable DOC counting for DOC release
            G_Module_Function_Status |= ENABLE_DOC_COUNTER;
        }//if(((G_Module_Status & Module_D_OC)==0) && G_DSG_Current_ADC >= ADC_DOC_PROTECTION){
    }else{
        DSG_OC_Counter = 0;
    }
    //////////////////////////////////////////////////////////////////
    // checking if it's C_OC
    // compare if Charging Current greater than ADC_COC_PROTECTION,
    // it will be into CHG OC protection.
    // Delay 略小於設定值 (+- TimerIntervalTimeBase_MS)
    if(((G_Module_Status & Module_C_OC)==0) && G_CHG_Current_ADC >= ADC_COC_PROTECTION){
        CHG_OC_Counter++;
        if(CHG_OC_Counter >= CHG_OC_Protection_Delay_Cycle){
            G_Module_Status |= Module_C_OC;
            CHG_OC_Counter = 0;
            G_COCP_TIMES++;
            if(G_COCP_TIMES >= UINT_MAX_VALUES_TH){
                G_COCP_TIMES = UINT_MAX_VALUES_TH;
            }
            ///////////////////////////////////////////////////////////////////
            //Enable COC counting for COC release
            G_Module_Function_Status |= ENABLE_COC_COUNTER;
            ///////////////////////////////////////////////////////////////////
            //Check COC Repeat times COC release
            if(G_Module_Function_Status & COC_RELEASE_FOR_REPEATED_CHECK){
                COC_Repeat_Counter++;
                G_Module_Function_Status &= ~COC_RELEASE_FOR_REPEATED_CHECK;
                if(COC_Repeat_Counter >= COC_Repeat_For_LOCK_Times){
                    G_Module_Function_Status |= Module_C_OC_LOCK;
                    COC_Repeat_Counter = 0;
                }
            }else{
                COC_Repeat_Counter = 0;
            }
        }//if(((G_Module_Status & Module_C_OC)==0) && G_CHG_Current_ADC >= ADC_COC_PROTECTION){
    }else{
        CHG_OC_Counter = 0;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////
    //DOC Release and clear Flag
    if((G_Module_Status & Module_D_OC) && (G_Module_Function_Status & DOC_COUNTING_FINISH)){
        G_Module_Function_Status &= ~DOC_COUNTING_FINISH;
        G_Module_Status &= ~Module_D_OC;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////
    //COC Release and clear Flag
    if((G_Module_Status & Module_C_OC) && (G_Module_Function_Status & COC_COUNTING_FINISH)){
        G_Module_Function_Status &= ~COC_COUNTING_FINISH;
        G_Module_Status &= ~Module_C_OC;
        G_Module_Function_Status |= COC_RELEASE_FOR_REPEATED_CHECK;
    }


    //COC Lock Release while dsg or button click
    if(G_Module_Function_Status & Module_C_OC_LOCK){
        if((G_Module_Status & Current_Dir_DSG) || (G_Add_Module_Function_Status & BUTTON_CLICK_For_COC_LOCK)){
            G_Module_Function_Status &= ~Module_C_OC_LOCK;
            if(G_Add_Module_Function_Status & BUTTON_CLICK_For_COC_LOCK){
                G_Add_Module_Function_Status &= ~BUTTON_CLICK_For_COC_LOCK;
            }
        }
    }else{
        if(G_Add_Module_Function_Status & BUTTON_CLICK_For_COC_LOCK){
            G_Add_Module_Function_Status &= ~BUTTON_CLICK_For_COC_LOCK;
        }
    }


//      /////////////////////////////////////////////////////////////////////////////////////////////
//      // Check whether DSG MOSFET Failure, when DSG mosfet turn off
//      if((G_SystemFailureStatus == 0) && (G_Device_Action_Controls & DSG_MOS_TURNOFF_STABLE)){
//        if(((G_Device_Action_Controls & DSG_MOSFET_TurnON)==0) && (G_Module_Active_Status & Current_Dir_DSG) && (G_DSG_Current_ADC > 100)){
//          if(DSGMosFet_Fail_Counter >= MosFET_Protection_Delay_Cycle){
//            G_Indication_FailureMode_Status |= DSGMOSFETFail;
//          }else{
//            DSGMosFet_Fail_Counter++;
//          }
//        }else{
//          DSGMosFet_Fail_Counter = 0;
//        }
//      }else{
//        DSGMosFet_Fail_Counter = 0;
//      }
//      /////////////////////////////////////////////////////////////////////////////////////////////
//      // Check whether CHG MOSFET Failure, when CHG mosfet turn off
//      if((G_SystemFailureStatus == 0) && (G_Device_Action_Controls & CHG_MOS_TURNOFF_STABLE)){
//        if(((G_Device_Action_Controls & CHG_MOSFET_TurnON)==0) && (G_Module_Active_Status & Current_Dir_CHG) && (G_CHG_Current_ADC > 100)){
//          if(CHGMosFet_Fail_Counter >= MosFET_Protection_Delay_Cycle){
//            G_Indication_FailureMode_Status |= CHGMOSFETFail;
//          }else{
//            CHGMosFet_Fail_Counter++;
//          }
//        }else{
//          CHGMosFet_Fail_Counter = 0;
//        }
//      }else{
//        CHGMosFet_Fail_Counter = 0;
//      }

 //ADC_BATTERY_OV_RELEASE
    /////////////////////////////////////////////////////////////////////////////////////////////
    // checking if it's Battery OV
    // Delay 略小於設定值 (+- TimerIntervalTimeBase_MS)
    if(((G_Module_Status & Module_BAT_OV)==0) && G_VBAT_ADC >= ADC_BATTERY_OV_PROTECTION){
        Battery_OV_Counter++;
        if(Battery_OV_Counter >= Battery_OV_Protection_Delay_Cycle){
            G_Module_Status |= Module_BAT_OV;
            Battery_OV_Counter = 0;
            G_OVP_TIMES++;
            if(G_OVP_TIMES >= UINT_MAX_VALUES_TH){
                G_OVP_TIMES = UINT_MAX_VALUES_TH;
            }
        }//if(((G_Module_Status & Module_BAT_OV)==0) && G_VBAT_ADC >= ADC_BATTERY_OV_PROTECTION){
    }else{
        Battery_OV_Counter = 0;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////
    // release Battery OV if it's Battery OV
    if((G_Module_Status & Module_BAT_OV) && G_VBAT_ADC < ADC_BATTERY_OV_RELEASE){
        G_Module_Status &= ~Module_BAT_OV;
        Battery_OV_Counter = 0;
    }
//    /////////////////////////////////////////////////////////////////////////////////////////////
//    //Cell OV/UV protection and release
//    if(get_PIC_UVP_Status()){
//      G_Module_Status |= Module_PIC_UV;
//    }else{
//      G_Module_Status &= ~Module_PIC_UV;
//    }
//    if(get_PIC_OVP_Status()){
//      G_Module_Status |= Module_PIC_OV;
//    }else{
//      G_Module_Status &= ~Module_PIC_OV;
//    }

#if (_Dynamic_UVP_With_Temperature_ == 1)
    /////////////////////////////////////////////////////////////////////////////////////////////
    // checking Dynamic UVP by Temperature
    // Delay 略小於設定值 (+- TimerIntervalTimeBase_MS)
        if(NTC_ADC_MAX_Lower_Temp > Dynamic_UVP_ADC_TEMP_TH1){
            // ntc > th1 :(real temp < setting th1)
            if(G_VBAT_ADC <= Dynamic_UVP_ADC_BATTERY_Vol_TH1){
                G_Module_Status |= Dynamic_UVP;
            }else{
                G_Module_Status &= ~Dynamic_UVP;
            }
        }else if(NTC_ADC_MAX_Lower_Temp > Dynamic_UVP_ADC_TEMP_TH2){
            // th1 >= ntc > th2 :( setting th1 <= real temp < setting th2)
            if(G_VBAT_ADC <= Dynamic_UVP_ADC_BATTERY_Vol_TH2){
                G_Module_Status |= Dynamic_UVP;
            }else{
                G_Module_Status &= ~Dynamic_UVP;
            }
        }else if(NTC_ADC_MAX_Lower_Temp > Dynamic_UVP_ADC_TEMP_TH3){
            // th2 >= ntc > th3 :( setting th2 <= real temp < setting th3)
            if(G_VBAT_ADC <= Dynamic_UVP_ADC_BATTERY_Vol_TH3){
                G_Module_Status |= Dynamic_UVP;
            }else{
                G_Module_Status &= ~Dynamic_UVP;
            }
        }else{
            // th3 >= ntc :( real temp <= setting th3)
            if(G_VBAT_ADC <= Dynamic_UVP_ADC_BATTERY_Vol_TH4){
                G_Module_Status |= Dynamic_UVP;
            }else{
                G_Module_Status &= ~Dynamic_UVP;
            }
        }

    if(((G_Module_Status & Module_BAT_UV)==0) && (G_Module_Status & Dynamic_UVP)){
        Battery_UV_Counter++;
        if(Battery_UV_Counter >= Battery_UV_Protection_Delay_Cycle){
            G_Module_Status |= Module_BAT_UV;
            Battery_UV_Counter = 0;
            G_UVP_TIMES++;
            if(G_UVP_TIMES >= UINT_MAX_VALUES_TH){
                G_UVP_TIMES = UINT_MAX_VALUES_TH;
            }
        }//if(((G_Module_Status & Module_BAT_UV)==0) && G_VBAT_ADC <= ADC_BATTERY_UV_PROTECTION){
    }else{
        Battery_UV_Counter = 0;
    }
#else
    /////////////////////////////////////////////////////////////////////////////////////////////
    // checking if it's Battery UV
    // Delay 略小於設定值 (+- TimerIntervalTimeBase_MS)
    if(((G_Module_Status & Module_BAT_UV)==0) && G_VBAT_ADC <= ADC_BATTERY_UV_PROTECTION){
        Battery_UV_Counter++;
        if(Battery_UV_Counter >= Battery_UV_Protection_Delay_Cycle){
            G_Module_Status |= Module_BAT_UV;
            Battery_UV_Counter = 0;
            G_UVP_TIMES++;
            if(G_UVP_TIMES >= UINT_MAX_VALUES_TH){
                G_UVP_TIMES = UINT_MAX_VALUES_TH;
            }
        }//if(((G_Module_Status & Module_BAT_UV)==0) && G_VBAT_ADC <= ADC_BATTERY_UV_PROTECTION){
    }else{
        Battery_UV_Counter = 0;
    }
#endif
    /////////////////////////////////////////////////////////////////////////////////////////////
    // when Battery UV , Start counting delay
    if(G_Module_Status & Module_BAT_UV){
        if((G_Module_Function_Status & After_UVP_Delay_Counting_Done) == 0){
            After_Battery_UV_Start_Counter++;
            if(After_Battery_UV_Start_Counter >= AFTER_UVP_Delay_Count_CycleTimes){
                G_Module_Function_Status |= After_UVP_Delay_Counting_Done;
                After_Battery_UV_Start_Counter = 0;
            }
        }
    }
//    if((G_Module_Status & Module_BAT_UV) && ((G_Module_Function_Status & After_UVP_Delay_Counting_Done) == 0)){
//        After_Battery_UV_Start_Counter++;
//        if(After_Battery_UV_Start_Counter >= AFTER_UVP_Delay_Count_CycleTimes){
//            G_Module_Function_Status |= After_UVP_Delay_Counting_Done;
//            After_Battery_UV_Start_Counter = 0;
//        }
//    }else{
//        G_Module_Function_Status &= ~After_UVP_Delay_Counting_Done;
//        After_Battery_UV_Start_Counter = 0;
//    }

//    /////////////////////////////////////////////////////////////////////////////////////////////
//    // release Battery UV if it's Battery UV
//    if((G_Module_Status & Module_BAT_UV) && G_VBAT_ADC > ADC_BATTERY_UV_RELEASE){
//        G_Module_Status &= ~Module_BAT_UV;
//        Battery_UV_Counter = 0;
//    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    // release Battery UV and PIC UV , only at charging
    if((G_Module_Status & Module_BAT_UV)){
        //relese UV By Charger staus
        if(G_Module_Status & Current_Dir_CHG){
            G_Module_Status &= ~Module_BAT_UV;
            Battery_UV_Counter = 0;
            G_Module_Function_Status &= ~After_UVP_Delay_Counting_Done;
        }
        if(G_Module_Function_Status & After_UVP_Delay_Counting_Done){
            if(G_VBAT_ADC > ADC_BATTERY_UV_RELEASE){
                G_Module_Status &= ~Module_BAT_UV;
                G_Module_Function_Status &= ~After_UVP_Delay_Counting_Done;
                Battery_UV_Counter = 0;
                After_Battery_UV_Start_Counter = 0;
            }
        }
    }



    /////////////////////////////////////////////////////////////////////////////////////////////
    // checking if it's NTC OT without current direction
    /////////////////////////////////////////////////////////////////////////////////////////////
    // set DSG Low OT without current direction
    if((G_Module_Function_Status & DSG_LOW_OTA)==0){
        if(NTC_ADC_MIN_Higher_Temp <= ADC_DSG_OT_LOW_PROTECTION){
            DSG_Low_OT_Counter++;
            if(DSG_Low_OT_Counter >= DSG_Low_OT_Protection_Delay_Cycle){
                G_Module_Function_Status |= DSG_LOW_OTA;
                DSG_Low_OT_Counter = 0;
            }
        }else{
            DSG_Low_OT_Counter = 0;
        }
    }else{
        DSG_Low_OT_Counter = 0;
    }
    // set DSG High OT without current direction
    if((G_Module_Function_Status & DSG_HIGH_OTA)==0){
        if(NTC_ADC_MIN_Higher_Temp <= ADC_DSG_OT_HIGH_PROTECTION){
            DSG_High_OT_Counter++;
            if(DSG_High_OT_Counter >= DSG_High_OT_Protection_Delay_Cycle){
                G_Module_Function_Status |= DSG_HIGH_OTA;
                DSG_High_OT_Counter = 0;
            }
        }else{
            DSG_High_OT_Counter = 0;
        }
    }else{
        DSG_High_OT_Counter = 0;
    }
    // release DSG High OT without current direction
    if(G_Module_Function_Status & DSG_HIGH_OTA){
        if(NTC_ADC_MIN_Higher_Temp > ADC_DSG_OT_HIGH_RELEASE){
            G_Module_Function_Status &= ~DSG_HIGH_OTA;
        }
    }
    // release DSG Low OT without current direction
    if(G_Module_Function_Status & DSG_LOW_OTA){
        if(NTC_ADC_MIN_Higher_Temp > ADC_DSG_OT_LOW_RELEASE){
            G_Module_Function_Status &= ~DSG_LOW_OTA;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    //Check High current for DSG OT_PROTECTION
    if( G_DSG_Current_ADC >=  ADC_DSG_HIGH_CURRENT_DETECT){
      G_Module_Function_Status |= DSG_HIGH_CURRENT_FOR_OT;
    }else{
      G_Module_Function_Status &= ~DSG_HIGH_CURRENT_FOR_OT;
    }

    ///////////////////////////////////////////////////////////////////////////
    // set DSG OT Protection Level
    // when current reach high, use high OT setting for protection
    if(((G_Module_Function_Status & USE_DSG_HIGH_OT_SETTING)==0) && (G_Module_Function_Status & DSG_HIGH_CURRENT_FOR_OT)){
      G_Module_Function_Status |= USE_DSG_HIGH_OT_SETTING;
    }
    if((G_Module_Function_Status & USE_DSG_HIGH_OT_SETTING) &&((G_Module_Function_Status & DSG_HIGH_CURRENT_FOR_OT)==0)){
        if((G_Module_Function_Status & (DSG_LOW_OTA + DSG_HIGH_OTA)) == 0){
            G_Module_Function_Status &= ~USE_DSG_HIGH_OT_SETTING;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    // set System DSG OT Protection without current
    if((G_Module_Function_Status & DSG_HIGH_OTA) && (G_Module_Function_Status & USE_DSG_HIGH_OT_SETTING)){
        if((G_Module_Status & Module_DSG_OT) == 0){
            //Record_And_Count_NTC_DSG_HIGH_CURRENT_OTP_TIMES();
            sg_Protection_1_Status |= fDSG_HIGH_CURRENT_OTP_COUNT;
        }
        G_Module_Status |= Module_DSG_OT;
    }else if((G_Module_Function_Status & DSG_LOW_OTA) && ((G_Module_Function_Status & USE_DSG_HIGH_OT_SETTING)==0)){
        if((G_Module_Status & Module_DSG_OT) == 0){
            //Record_And_Count_NTC_DSG_LOW_CURRENT_OTP_TIMES();
            sg_Protection_1_Status |= fDSG_LOW_CURRENT_OTP_COUNT;
        }
        G_Module_Status |= Module_DSG_OT;
    }else if((G_Module_Function_Status & (DSG_LOW_OTA + DSG_HIGH_OTA)) == 0){
        G_Module_Status &= ~Module_DSG_OT;
    }


    if(G_Module_Status & Module_DSG_OT){
        if((sg_Protection_1_Status & fDSG_HIGH_CURRENT_OTP_COUNT)&&(G_Module_Status & Current_Dir_DSG)){
            sg_Protection_1_Status &= ~fDSG_HIGH_CURRENT_OTP_COUNT;
            Record_And_Count_NTC_DSG_HIGH_CURRENT_OTP_TIMES();
        }
        if((sg_Protection_1_Status & fDSG_LOW_CURRENT_OTP_COUNT)&&(G_Module_Status & Current_Dir_DSG)){
            sg_Protection_1_Status &= ~fDSG_LOW_CURRENT_OTP_COUNT;
            Record_And_Count_NTC_DSG_LOW_CURRENT_OTP_TIMES();
        }
    }else{
        sg_Protection_1_Status &= ~fDSG_HIGH_CURRENT_OTP_COUNT;
        sg_Protection_1_Status &= ~fDSG_LOW_CURRENT_OTP_COUNT;
    }


    ///////////////////////////////////////////////////////////////////////////
    //checking if it's CHG_OT without current direction
    ///////////////////////////////////////////////////////////////////////////
    if((G_Module_Status & Module_CHG_OT)==0){
        if(NTC_ADC_MIN_Higher_Temp <= ADC_CHG_OT_PROTECTION){
            CHG_OT_Counter++;
            if(CHG_OT_Counter >= CHG_OT_Protection_Delay_Cycle){
                G_Module_Status |= Module_CHG_OT;
                CHG_OT_Counter = 0;
                //Record_And_Count_NTC_CHG_OTP_TIMES();
            }
        }else{
            CHG_OT_Counter = 0;
        }
    }else{
        CHG_OT_Counter = 0;
    }

    if(G_Module_Status & Module_CHG_OT){
        if(((sg_Protection_1_Status & fCHG_OTP_COUNT)==0)&&(G_Module_Status & Current_Dir_CHG)){
            sg_Protection_1_Status |= fCHG_OTP_COUNT;
            Record_And_Count_NTC_CHG_OTP_TIMES();
        }
    }else{
        sg_Protection_1_Status &= ~fCHG_OTP_COUNT;
    }

    ///////////////////////////////////////////////////////////////////////////
    // release CHG OT without current direction
    if(G_Module_Status & Module_CHG_OT){
        if(NTC_ADC_MIN_Higher_Temp > ADC_CHG_OT_RELEASE){
            G_Module_Status &= ~Module_CHG_OT;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    //checking if it's UT without current direction
    if((G_Module_Status & Module_UT)==0){
        if(NTC_ADC_MAX_Lower_Temp >= ADC_UT_PROTECTION){
            UT_Counter++;
            if(UT_Counter >= UT_Protection_Delay_Cycle){
                G_Module_Status |= Module_UT;
                UT_Counter = 0;
            }
        }else{
            UT_Counter = 0;
        }
    }else{
        UT_Counter = 0;
    }

    if(G_Module_Status & Module_UT){
        if(((sg_Protection_1_Status & fCHG_UT_COUNT)==0)&&(G_Module_Status & Current_Dir_CHG)){
            sg_Protection_1_Status |= fCHG_UT_COUNT;
            Record_And_Count_NTC_CHG_UTP_TIMES();
        }
    }else{
        sg_Protection_1_Status &= ~fCHG_UT_COUNT;
    }
    ///////////////////////////////////////////////////////////////////////////
    // release UT without current direction
    if(G_Module_Status & Module_UT){
        if(NTC_ADC_MAX_Lower_Temp < ADC_UT_RELEASE){
            G_Module_Status &= ~Module_UT;
        }
    }


    ///////////////////////////////////////////////////////////////////////////
    // Check initial Charging temperature range and set flag
    ///////////////////////////////////////////////////////////////////////////
    if((NTC_ADC_MIN_Higher_Temp >= ADC_INITIAL_CHARGING_TEMP_RANGE_HI) && (NTC_ADC_MAX_Lower_Temp <= ADC_INITIAL_CHARGING_TEMP_RANGE_LO)){
        G_Module_Function_Status |= INITIAL_CHARGING_TEMP_RANGE;
    }else{
        G_Module_Function_Status &= ~INITIAL_CHARGING_TEMP_RANGE;
    }
    ///////////////////////////////////////////////////////////////////////////
    // Check Set SOC signal temperature range and set flag
    ///////////////////////////////////////////////////////////////////////////
    if((NTC_ADC_MIN_Higher_Temp >= ADC_LOW_TEMP_SOC_CHARGING_RANGE_HI) && (NTC_ADC_MAX_Lower_Temp <= ADC_LOW_TEMP_SOC_CHARGING_RANGE_LO)){
        G_Module_Function_Status |= LOW_TEMP_SOC_SET;
    }else{
        G_Module_Function_Status &= ~LOW_TEMP_SOC_SET;
    }


    ///////////////////////////////////////////////////////////////////////////
#if (_AUTO_ENTER_SLEEPING_MODE_PREASS_TO_WAKE_UP_ == 1)
    if((G_Module_Function_Status & Auto_Sleeping_Entry)== 0){
        if(G_Extend_Device_Interface_Status & Force_CHG_MOS_OFF){
            _DUI_Set_CHG_MosFET(DeviceOff);
        }else{
            //////////////////////////////////////////////////////////////////////////////
            // MosFet control and Protection release
            //////////////////////////////////////////////////////////////////////////////
            // CHG MosFet control and Protection release
            if(G_Module_Status & (Module_C_OC + Module_BAT_OV + Module_CHG_OT + Module_UT) || (G_Module_Function_Status & Module_C_OC_LOCK)){
                _DUI_Set_CHG_MosFET(DeviceOff);
            }// if CHG protection
            else{
                // normal set CHG on without any alarm
                // when first time charge, check valid charging temperature
                if((G_Module_Status & Current_Dir_DSG) || (G_Module_Status & Current_Dir_Static)){
                    if(G_Module_Function_Status & INITIAL_CHARGING_TEMP_RANGE){
                        _DUI_Set_CHG_MosFET(DeviceOn);
                    }else{
                        _DUI_Set_CHG_MosFET(DeviceOff);
                    }
                }else{
                    _DUI_Set_CHG_MosFET(DeviceOn);
                }
            }
        }
        if(G_Extend_Device_Interface_Status & Force_DSG_MOS_OFF){
            _DUI_Set_DSG_MosFET(DeviceOff);
        }else{
            //////////////////////////////////////////////////////////////////////////////
            // DSG MosFet control and Protection release
            if(G_Module_Function_Status & SW_PRESS_FOR_TURN_OFF_DSG){
                _DUI_Set_DSG_MosFET(DeviceOff);
            }else{
                if((G_Module_Status & (Module_D_OC + Module_BAT_UV + Module_DSG_OT))){
                    _DUI_Set_DSG_MosFET(DeviceOff);
                }else{
                    _DUI_Set_DSG_MosFET(DeviceOn);
                }
            }
        }
    }else{
#if (_AUTO_RTC_PERIOD_WAKE_UP_FOR_AUTO_SLEEPING_ == 0)
        _DUI_Set_DSG_MosFET(DeviceOff);
        _DUI_Set_CHG_MosFET(DeviceOff);
#endif
    }
#else
    if(G_Extend_Device_Interface_Status & Force_CHG_MOS_OFF){
        _DUI_Set_CHG_MosFET(DeviceOff);
    }else{
        //////////////////////////////////////////////////////////////////////////////
        // MosFet control and Protection release
        //////////////////////////////////////////////////////////////////////////////
        // CHG MosFet control and Protection release
        if(G_Module_Status & (Module_C_OC + Module_BAT_OV + Module_CHG_OT + Module_UT) || (G_Module_Function_Status & Module_C_OC_LOCK)){
            _DUI_Set_CHG_MosFET(DeviceOff);
        }// if CHG protection
        else{
            // normal set CHG on without any alarm
            // when first time charge, check valid charging temperature
            if((G_Module_Status & Current_Dir_DSG) || (G_Module_Status & Current_Dir_Static)){
                if(G_Module_Function_Status & INITIAL_CHARGING_TEMP_RANGE){
                    _DUI_Set_CHG_MosFET(DeviceOn);
                }else{
                    _DUI_Set_CHG_MosFET(DeviceOff);
                }
            }else{
                _DUI_Set_CHG_MosFET(DeviceOn);
            }
        }
    }
    if(G_Extend_Device_Interface_Status & Force_DSG_MOS_OFF){
        _DUI_Set_DSG_MosFET(DeviceOff);
    }else{
        //////////////////////////////////////////////////////////////////////////////
        // DSG MosFet control and Protection release
        if(G_Module_Function_Status & SW_PRESS_FOR_TURN_OFF_DSG){
            _DUI_Set_DSG_MosFET(DeviceOff);
        }else{
            if((G_Module_Status & (Module_D_OC + Module_BAT_UV + Module_DSG_OT))){
                _DUI_Set_DSG_MosFET(DeviceOff);
            }else{
                _DUI_Set_DSG_MosFET(DeviceOn);
            }
        }
    }
#endif

#if (_System_Life_Ending_Enable_ == 1)

#endif

    //////////////////////////////////////////////////////////////////////////////
    // detection mos fail and counter
    //////////////////////////////////////////////////////////////////////////////
    if(((G_Module_Status & CHG_MOS_FAIL) == 0) && ((G_Device_Interface_Status & CHG_MOSFET_TurnON)==0)){
        if(CHG_MOS_FAIL_Counter > MOS_Fail_CycleTimes){
            if(G_Module_Status & Current_Dir_CHG){
                G_Module_Status |= CHG_MOS_FAIL;
            }
        }else{
            CHG_MOS_FAIL_Counter++;
        }
    }else{
        CHG_MOS_FAIL_Counter = 0;
    }
    if(((G_Module_Status & DSG_MOS_FAIL) == 0) && ((G_Device_Interface_Status & DSG_MOSFET_TurnON)==0)){
        if(DSG_MOS_FAIL_Counter > MOS_Fail_CycleTimes){
            if(G_Module_Status & Current_Dir_DSG){
                G_Module_Status |= DSG_MOS_FAIL;
            }
        }else{
            DSG_MOS_FAIL_Counter++;
        }
    }else{
        DSG_MOS_FAIL_Counter = 0;
    }

    //////////////////////////////////////////////////////////////////////////////
    // Count for Store Average current to calculate and set
    //////////////////////////////////////////////////////////////////////////////
    if(STORE_AVG_ADC_CURRENT_Counter >= STORE_AVG_ADC_CURRENT_CycleTimes){
        STORE_AVG_ADC_CURRENT_Counter = 0;
        G_AVG_DSG_Current_ADC = GetAndSet_AVG_ADC_CURRENT(G_DSG_Current_ADC);
    }else{
        STORE_AVG_ADC_CURRENT_Counter++;
    }
    //////////////////////////////////////////////////////////////////////////////
    // Count for Store Average Voltage to calculate and set
    //////////////////////////////////////////////////////////////////////////////
    if(STORE_AVG_ADC_VOLTAGE_Counter >= STORE_AVG_ADC_VOLTAGE_CycleTimes){
        STORE_AVG_ADC_VOLTAGE_Counter = 0;
        G_AVG_Battery_Voltage_ADC = GetAndSet_AVG_ADC_VOLTAGE(G_VBAT_ADC);
    }else{
        STORE_AVG_ADC_VOLTAGE_Counter++;
    }

    //GPIO_LOW(LED2_PORT, LED2_PIN);


#if (_AUTO_ENTER_SLEEPING_MODE_PREASS_TO_WAKE_UP_ == 1)
    //////////////////////////////////////////////////////////////////////////
    //System 1 min Counter For Auto Sleeping: (section start)
    if((G_Module_Status & Current_Dir_Static)){
        if(((G_Module_Function_Status & Auto_Sleeping_Entry)==0) && (G_VBAT_ADC < Enter_Auto_Sleeping_ADC_Vol_Condition)){
            System_1_Min_Flag_Counter++;
            if(System_1_Min_Flag_Counter >= System_1_Min_Flag_CycleTimes){
                AutoSleeping_Minutes_Counter++;
                System_1_Min_Flag_Counter = 0;
            }
        }
    }
    //System 1 min Counter For Auto Sleeping: (section stop)
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    //Auto Sleeping Counter : (section start)
    if((G_Module_Status & Current_Dir_Static)){
        if(((G_Module_Function_Status & Auto_Sleeping_Entry)==0) && (G_VBAT_ADC < Enter_Auto_Sleeping_ADC_Vol_Condition)){
            if(AutoSleeping_Minutes_Counter >= AUTO_ENTRY_SLEEPING_DELAY_MINUTES){
                G_Module_Function_Status |= Auto_Sleeping_Entry;
                System_1_Min_Flag_Counter = 0;
                AutoSleeping_Minutes_Counter = 0;
            }
        }else{
            System_1_Min_Flag_Counter = 0;
            AutoSleeping_Minutes_Counter = 0;
        }
    }else{
        System_1_Min_Flag_Counter = 0;
        AutoSleeping_Minutes_Counter = 0;
    }
    //Auto Sleeping Counter : (section stop)
    //////////////////////////////////////////////////////////////////////////
#else
    System_1_Min_Flag_Counter = System_1_Min_Flag_Counter;
    AutoSleeping_Minutes_Counter = AutoSleeping_Minutes_Counter;
#endif

#if (_USE_USB_POWER_OUTPUT_MODULE_ == 1)
    //////////////////////////////////////////////////////////////////////////
    //USB Output OCP Process : (section start)
    // USB OCP
    if((( G_Add_Module_Function_Status & OCP_FOR_USB_POWER_OUTPUT)==0) && (_DUI_Get_USB_OCP_Signal_Status() == USB_Output_Power_OCP)){
        USB_OCP_Signal_Protection_Cycle_Counter++;
        if(USB_OCP_Signal_Protection_Cycle_Counter >= USB_OCP_Signal_Protection_Cycle_Debounce){
            G_Add_Module_Function_Status |= OCP_FOR_USB_POWER_OUTPUT;
            //_DUI_Set_USB_Power_Output(DeviceOff);
            USB_OCP_Signal_Release_Cycle_Counter = 0;
            USB_OCP_Signal_Protection_Cycle_Counter = 0;
        }
    }else{
        USB_OCP_Signal_Protection_Cycle_Counter = 0;
    }
    //USB Release
    if( G_Add_Module_Function_Status & OCP_FOR_USB_POWER_OUTPUT){
        USB_OCP_Signal_Release_Cycle_Counter++;
        if(USB_OCP_Signal_Release_Cycle_Counter > USB_OCP_Signal_Release_Cycle){
            //_DUI_Set_USB_Power_Output(DeviceOn);
            G_Add_Module_Function_Status &= ~OCP_FOR_USB_POWER_OUTPUT;
            USB_OCP_Signal_Release_Cycle_Counter = 0;
        }
    }
    if((G_Device_Interface_Status &(DSG_MOSFET_TurnON)) == 0){
        _DUI_Set_USB_Power_Output(DeviceOff);
    }else if( G_Add_Module_Function_Status & OCP_FOR_USB_POWER_OUTPUT){
        _DUI_Set_USB_Power_Output(DeviceOff);
    }else{
        _DUI_Set_USB_Power_Output(DeviceOn);
    }
    //USB Output OCP Processr : (section stop)
    //////////////////////////////////////////////////////////////////////////
#endif

#if (_LED_BackLight_Control_ == 1)
//    //////////////////////////////////////////////////////////////////////////
//    //Back Light Start Counter : (section start)
//    if((G_Device_Interface_Status &(DSG_MOSFET_TurnON)) == 0){
//        _DUI_Set_BackLight_Output(DeviceOff);
//        BackLight_Blinking_Counter = 0;
//    }else{
//        if(G_Device_Interface_Status & BackLight_Constant_ON ){
//            BackLight_Blinking_Counter = 0;
//            _DUI_Set_BackLight_Output(DeviceOn);
//        }else if(G_Device_Interface_Status & BackLight_Blinking){
//            BackLight_Blinking_Counter++;
//            if(BackLight_Blinking_Counter >= BackLight_Blinking_Delay_Cycle){
//                BackLight_Blinking_Counter = 0;
//                if(G_Device_Interface_Status & BackLight_LED_OnOff_Status){
//                    _DUI_Set_BackLight_Output(DeviceOff);
//                }else{
//                    _DUI_Set_BackLight_Output(DeviceOn);
//                }
//            }
//        }else{
//            BackLight_Blinking_Counter = 0;
//            _DUI_Set_BackLight_Output(DeviceOff);
//        }
//    }
//    //Back Light Start Counter : (section stop)
//    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //Back Light Start Counter : (section start)
#if (_AUTO_ENTER_SLEEPING_MODE_PREASS_TO_WAKE_UP_ == 1)
    if(( G_VBAT_ADC < Dynamic_UVP_ADC_BATTERY_Vol_TH1)||(G_Module_Function_Status & Auto_Sleeping_Entry)){
#else
    if(( G_VBAT_ADC < Dynamic_UVP_ADC_BATTERY_Vol_TH1)){
#endif
        _DUI_Set_BackLight_Output(DeviceOff);
        BackLight_Blinking_Counter = 0;
        G_Device_Interface_Status &= ~BackLight_Constant_ON;
        G_Device_Interface_Status &= ~BackLight_Blinking;
    }else if(G_VBAT_ADC >= Dynamic_UVP_ADC_BATTERY_Vol_TH1){
        if(G_Device_Interface_Status & BackLight_Constant_ON ){
            BackLight_Blinking_Counter = 0;
            _DUI_Set_BackLight_Output(DeviceOn);
        }else if(G_Device_Interface_Status & BackLight_Blinking){
            BackLight_Blinking_Counter++;
            if(BackLight_Blinking_Counter >= BackLight_Blinking_Delay_Cycle){
                BackLight_Blinking_Counter = 0;
                if(G_Device_Interface_Status & BackLight_LED_OnOff_Status){
                    _DUI_Set_BackLight_Output(DeviceOff);
                }else{
                    _DUI_Set_BackLight_Output(DeviceOn);
                }
            }
        }else{
            BackLight_Blinking_Counter = 0;
            _DUI_Set_BackLight_Output(DeviceOff);
        }
    }
    //Back Light Start Counter : (section stop)
    //////////////////////////////////////////////////////////////////////////
#else
    BackLight_Blinking_Counter = BackLight_Blinking_Counter+1;
    BackLight_Blinking_Counter = 0;
#endif

}//void Protection_Polling_Function(){

void Record_And_Count_NTC_CHG_UTP_TIMES(){
    // for UTP conditions and in CHG
    //NTC_ADC_MAX_Lower_Temp = (G_NTC1_ADC > G_NTC2_ADC)? G_NTC1_ADC : G_NTC2_ADC;
#if (_ENABLE_NTC_2_DETECTION_ == 1)
    if(G_NTC1_ADC > G_NTC2_ADC){
        G_TH1_CHG_UTP_TIMES++;
        if(G_TH1_CHG_UTP_TIMES >= UINT_MAX_VALUES_TH){
            G_TH1_CHG_UTP_TIMES = UINT_MAX_VALUES_TH;
        }
    }else{
        G_TH2_CHG_UTP_TIMES++;
        if(G_TH2_CHG_UTP_TIMES >= UINT_MAX_VALUES_TH){
            G_TH2_CHG_UTP_TIMES = UINT_MAX_VALUES_TH;
        }
    }
#else
    G_TH1_CHG_UTP_TIMES++;
    if(G_TH1_CHG_UTP_TIMES >= UINT_MAX_VALUES_TH){
        G_TH1_CHG_UTP_TIMES = UINT_MAX_VALUES_TH;
    }
#endif
}
void Record_And_Count_NTC_CHG_OTP_TIMES(){
    // for CHG UTP conditions
    //NTC_ADC_MIN_Higher_Temp = (G_NTC1_ADC < G_NTC2_ADC)? G_NTC1_ADC : G_NTC2_ADC;
#if (_ENABLE_NTC_2_DETECTION_ == 1)
    if(G_NTC1_ADC < G_NTC2_ADC){
        G_CHG_TH1_OTP_TIMES++;
        if(G_CHG_TH1_OTP_TIMES >= UINT_MAX_VALUES_TH){
            G_CHG_TH1_OTP_TIMES = UINT_MAX_VALUES_TH;
        }
    }else{
        G_CHG_TH2_OTP_TIMES++;
        if(G_CHG_TH2_OTP_TIMES >= UINT_MAX_VALUES_TH){
            G_CHG_TH2_OTP_TIMES = UINT_MAX_VALUES_TH;
        }
    }
#else
    G_CHG_TH1_OTP_TIMES++;
    if(G_CHG_TH1_OTP_TIMES >= UINT_MAX_VALUES_TH){
        G_CHG_TH1_OTP_TIMES = UINT_MAX_VALUES_TH;
    }
#endif
}

void Record_And_Count_NTC_DSG_LOW_CURRENT_OTP_TIMES(){
    // for OTP conditions
    //NTC_ADC_MIN_Higher_Temp = (G_NTC1_ADC < G_NTC2_ADC)? G_NTC1_ADC : G_NTC2_ADC;
#if (_ENABLE_NTC_2_DETECTION_ == 1)
    if(G_NTC1_ADC < G_NTC2_ADC){
        G_DSG_TH1_LOW_CURRENT_OTP_TIMES++;
        if(G_DSG_TH1_LOW_CURRENT_OTP_TIMES >= UINT_MAX_VALUES_TH){
            G_DSG_TH1_LOW_CURRENT_OTP_TIMES = UINT_MAX_VALUES_TH;
        }
    }else{
        G_DSG_TH2_LOW_CURRENT_OTP_TIMES++;
        if(G_DSG_TH2_LOW_CURRENT_OTP_TIMES >= UINT_MAX_VALUES_TH){
            G_DSG_TH2_LOW_CURRENT_OTP_TIMES = UINT_MAX_VALUES_TH;
        }
    }
#else
    G_DSG_TH1_LOW_CURRENT_OTP_TIMES++;
    if(G_DSG_TH1_LOW_CURRENT_OTP_TIMES >= UINT_MAX_VALUES_TH){
        G_DSG_TH1_LOW_CURRENT_OTP_TIMES = UINT_MAX_VALUES_TH;
    }
#endif
}
void Record_And_Count_NTC_DSG_HIGH_CURRENT_OTP_TIMES(){
    // for OTP conditions
    //NTC_ADC_MIN_Higher_Temp = (G_NTC1_ADC < G_NTC2_ADC)? G_NTC1_ADC : G_NTC2_ADC;
#if (_ENABLE_NTC_2_DETECTION_ == 1)
    if(G_NTC1_ADC < G_NTC2_ADC){
        G_DSG_TH1_HIGH_CURRENT_OTP_TIMES++;
        if(G_DSG_TH1_HIGH_CURRENT_OTP_TIMES >= UINT_MAX_VALUES_TH){
            G_DSG_TH1_HIGH_CURRENT_OTP_TIMES = UINT_MAX_VALUES_TH;
        }
    }else{
        G_DSG_TH2_HIGH_CURRENT_OTP_TIMES++;
        if(G_DSG_TH2_HIGH_CURRENT_OTP_TIMES >= UINT_MAX_VALUES_TH){
            G_DSG_TH2_HIGH_CURRENT_OTP_TIMES = UINT_MAX_VALUES_TH;
        }
    }
#else
    G_DSG_TH1_HIGH_CURRENT_OTP_TIMES++;
    if(G_DSG_TH1_HIGH_CURRENT_OTP_TIMES >= UINT_MAX_VALUES_TH){
        G_DSG_TH1_HIGH_CURRENT_OTP_TIMES = UINT_MAX_VALUES_TH;
    }
#endif
}

//==============================================================================
// Private functions
//==============================================================================
void test_pin_init(){
    GPIO_Init(TEST_PORT, TEST_PIN, GPIO_Mode_Out_PP_Low_Slow);  // set as output and PP Low level
}
void test_high(){
    TEST_PORT->ODR|=TEST_PIN;
}
void test_low(){
    TEST_PORT->ODR&=~TEST_PIN;
}
void test_toggle(){
    TEST_PORT->ODR^=TEST_PIN;
}
