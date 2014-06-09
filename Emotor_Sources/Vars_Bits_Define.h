






enum For_G_SysModeStatusCode  //unsigned char
{
    UnKnowStatus,
    StartUp,
    POSTMode, //Power-on self-test
    NormalMode,
    FailureMode,
    ShutdownMode,
    CalibrationMode,
    ShippingMode,
    SuspendMode,
    SleepingMode,
    Sleeping_AutoWakeupMode
};

enum For_CurrentStatusCode  //unsigned char
{
  CurrentInRelax,   // == 0, because initial values is '0'
  CurrentInDSG,
  CurrentInCHG
};
/********************************************************************************
* Extern Function																*
********************************************************************************/


/********************************************************************************
* Golbal Variable Control Bits	Define											*
********************************************************************************/
/////////////////////////////////////////////////////////////////////////////////
/* Module Status Control Bits */
/* For G_Module_Status ; unsigned int */
//Low byte
#define Current_Dir_CHG          	(0x0001)    //Charging
#define Current_Dir_Static          (0x0002)    //relaxation mode or Quiescent current, usually equal to discharging
#define Current_Dir_DSG        		(0x0004)    //Discharging,
#define CHG_MOS_FAIL                (0x0008)    //No Use,
#define DSG_MOS_FAIL                (0x0010)    //No Use,
#define Dynamic_UVP                 (0x0020)    //No Use,
#define Module_UT                   (0x0040)    // Under Temperature Alarm
#define Current_Dir_CHG_No_Delay    (0x0080)    //
//Hight byte
#define Module_D_OC                 (0x0100)    //=D_OC, DisCharge over current flag
#define Module_C_OC                 (0x0200)    //=C_OC, Charge over current flag
#define Module_BAT_OV               (0x0400)    // Over Voltage Alarm, Whole Battery voltage
#define Module_BAT_UV               (0x0800)    // Under Voltage Alarm, Whole Battery voltage
//#define Module_PIC_OV               (0x1000)    // Cell Voltage Over Voltage Alarm
//#define Module_PIC_UV               (0x2000)    // Cell Voltage Under Voltage Alarm
#define Module_CHG_OT               (0x4000)    // CHG Over Temperature Alarm
#define Module_DSG_OT               (0x8000)    // DSG Over Temperature Alarm

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/* G_Module_Function_Status Control Bits */
/* For G_Module_Function_Status ; unsigned int */
//Low byte
#define ENABLE_DOC_COUNTER              (0x0001)    //Start DSG Over current counting for releasing OC. if finish, will set DOC_COUNTING_FINISH flag
#define DOC_COUNTING_FINISH             (0x0002)    //DOC Over current counting Finish.
#define ENABLE_COC_COUNTER              (0x0004)    //Start CHG Over current counting for releasing OC. if finish, will set COC_COUNTING_FINISH flag
#define COC_COUNTING_FINISH             (0x0008)    //COC Over current counting Finish.
#define COC_RELEASE_FOR_REPEATED_CHECK  (0x0010)    //After COC release, this flag will set until holding time out.
#define Module_C_OC_LOCK                (0x0020)    //Repeat COC for setting times, CHG Mos will be lock, until dsg current
#define LOW_TEMP_SOC_SET                (0x0040)    //At Low temperature setting range for setting SOC signal High for charging
#define Auto_Sleeping_Entry             (0x0080)    //
//Hight byte
#define DSG_LOW_OTA                     (0x0100)    // if temperature reach low level OT setting
#define DSG_HIGH_OTA                    (0x0200)    // if temperature reach High level OT setting
#define DSG_HIGH_CURRENT_FOR_OT         (0x0400)    // if current over High currentsetting or not
#define USE_DSG_HIGH_OT_SETTING         (0x0800)    // 1 = Use DSG HIGH OT Protection setting, 0 = Use (Normal) OT Protection setting.
#define INITIAL_CHARGING_TEMP_RANGE     (0x1000)    //
#define SW_PRESS_FOR_TURN_OFF_DSG       (0x2000)    // set = Turn off Dsg Mos by SW, reset = Turn on Dsg Mos by SW
#define After_UVP_Delay_Counting_Done   (0x4000)    //after UVP, starting count for delay to setting times, and than set the Flag to start detection released voltage
#define SYS_1_SEC_FLAG                  (0x8000)    //

///////////////////////////////////////////////////////////////////////////////////
/* G_Add_Module_Function_Status Control Bits */
/* For G_Add_Module_Function_Status ; unsigned int */
//Low byte
#define BUTTON_PRESS                    (0x0001)    //
#define BUTTON_LONG_PRESS               (0x0002)    //
#define BUTTON_CLICK                    (0x0004)    //
#define BUTTON_CLICK_For_COC_LOCK       (0x0008)    //
#define ENABLE_MULTI_CLICK_COUNTER      (0x0010)
#define BUTTON_COMPLETE_MULTI_CLICK     (0x0020)    //
#define Breathing_Light_START           (0x0040)    //
#define Breathing_Light_FINISH          (0x0080)    //
////Hight byte
#define ONE_WIRE_UART_SET_ENABLE        (0x0100)    //
#define ONE_WIRE_DISABLE_BY_CHG         (0x0200)    //
#define ONE_WIRE_TEMPORARY_START_COUNT  (0x0400)    //
#define ONE_WIRE_Send_EEPROM_Data       (0x0800)    //
#define ONE_WIRE_TRANSMIT_ALWAYS        (0x1000)    //
#define ONE_WIRE_TRANSMIT_ONCE_BY_CMD   (0x2000)    //
#define ENABLE_USB_POWER_OUTPUT         (0x4000)    //
#define OCP_FOR_USB_POWER_OUTPUT        (0x8000)    //





///////////////////////////////////////////////////////////////////////////////////
/* System_Control_Bit_EEPROM Control Bits */
/* For System_Control_Bit_EEPROM ; unsigned char */
///////////////////////////////////////////////////////////////////////////////////
//#define _No_Used_       (0x01)    //
//#define _No_Used_       (0x02)    //
#define SYS_INIT_DATA_SET1      (0x04)    //for check EEPROM information has been re-initial or not(0:re-initialed)
#define SYS_INIT_DATA_SET2      (0x08)    //for check EEPROM information has been re-initial or not(0:re-initialed)
#define SYS_UPDATED_FW          (0x10)
//#define _No_Used_       (0x20)    //
#define SYS_CHG_MOS_FAIL_SET    (0x40)    //
#define SYS_DSG_MOS_FAIL_SET    (0x80)    //
///////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////
/* Sys_Flash_Control_Bit Control Bits */
/* For Sys_Flash_Control_Bit ; unsigned char */
///////////////////////////////////////////////////////////////////////////////////
//#define _No_Used_       (0x01)    //
//#define _No_Used_       (0x02)    //
//#define _No_Used_       (0x04)    //
//#define _No_Used_       (0x05)    //
#define SYS_Ready_UPDATED_FW_Mask_Bit   (0x10)  //for checking and ready for FW Update By Communication, (1: normal run, 0: ready for update)
//#define _No_Used_       (0x20)  //
//#define _No_Used_       (0x40)    //
//#define _No_Used_       (0x80)    //
///////////////////////////////////////////////////////////////////////////////////


















///* Module Status Control Bits */
///* For G_Activate_Action_Status ; unsigned int */
////Low byte
//#define BUTTON_PRESS_FLAG               (0x0001)    //if button has been pressed, will set BUTTON_PRESS_FLAG flag
//#define BUTTON_LONG_PRESS_FLAG          (0x0002)    //if button has been pressed longer than setting time, will set BUTTON_LONG_PRESS_Flag flag
//#define ENABLE_OC_COUNTER               (0x0004)    //Start Over current counting. if finish, will set OC_COUNTING_FINISH flag
//#define OC_COUNTING_FINISH              (0x0008)    //Over current counting Finish.
//#define CHG_CV_MODE_START               (0x0010)    //Start CV_MODE_RELEASE waiting time counting. if finish, will set CV_MODE_RELEASE_COUNTING_FINISH flag
//#define ENABLE_CV_MODE_COUNTER          (0x0020)    //Start CV_MODE_RELEASE waiting time counting. if finish, will set CV_MODE_RELEASE_COUNTING_FINISH flag
//#define CV_MODE_RELEASE_COUNTING_FINISH (0x0040)    //CV_MODE_RELEASE waiting time counting Finish.
//#define BUTTON_CLICK_FLAG               (0x0080)    //if button has been pressed and then release with out BUTTON_LONG_PRESS_FLAG is set
////Hight byte
//#define ENABLE_WAKE_UP_COUNTER          (0x0100)    //
//#define WAKE_UP_COUNTING_FINISH         (0x0200)    //
//#define ENABLE_SUSPEND_COUNTER          (0x0400)    //
//#define SUSPEND_COUNTING_FINISH         (0x0800)    //
//#define ENABLE_SUSPEND_WAKE_UP_COUNTER  (0x1000)    //
//#define SUSPEND_WAKE_UP_COUNTING_FINISH (0x2000)    //
//#define CAPACITY_DISLALY                (0x4000)    //
//#define ACCUMULATING_Q_ENABLE           (0x8000)    //