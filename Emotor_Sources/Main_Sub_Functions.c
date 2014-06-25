/**
  ******************************************************************************
  * @file    main_Sub_Functions.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   Sub functions for Main program calling
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
#include "Config_Info\FW_Version_Define.h"

#include "Capacity_Display_Polling_Func.h"
//==============================================================================
// Global/Extern variables
//==============================================================================
#pragma data_alignment = 4
unsigned int G_Var_Array[VarArray_Int_Size];
unsigned char G_BAR_CODE_ID_Array[BAR_CODE_ID_Array_Whole_Size];

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

void Sleeping_In_Halt_AutoWakeup();

//==============================================================================
// Private typedef
//==============================================================================
//==============================================================================
// Private define
//==============================================================================
//STM8L/AL-medium density: STM8L15xK6
#define Bootloader_After_BL_Option_Check_Address    0x601a  //V 1.1
#define Bootloader_After_ROP_Check_Address          0x6028  //V 1.1
//#define Bootloader_After_BL_Option_Check_Address    0x601f  //V 1.2
//#define Bootloader_After_ROP_Check_Address          0x602d  //V 1.2
#define OneWireTransmitByCmd_2ndTX_DeleyCycle         20 // 30ms*3 = 150 ms (+/-50ms)

#define Sending_One_Wire_Array_Step_Base_On_1_Sec_Length    2
//const unsigned char Sending_One_Wire_Array_Step_Base_On_1_Sec[Sending_One_Wire_Array_Step_Base_On_1_Sec_Length] =
const unsigned char Sending_One_Wire_Array_Step_Base_On_1_Sec[] =
{
    Sending_SysInfor,
    Sending_EEPROMInfor,
    //Sending_PNInfor,
};
#define Sending_One_Wire_Array_Step_Base_On_Timer_Length    6
//const unsigned char Sending_One_Wire_Array_Step_Base_Timer[Sending_One_Wire_Array_Step_Base_On_Timer_Length] =
const unsigned char Sending_One_Wire_Array_Step_Base_Timer[] =
{
    Sending_SysInfor,
    Sending_Empty_Delay,
    Sending_Empty_Delay,
    Sending_Empty_Delay,
    Sending_Empty_Delay,
    Sending_EEPROMInfor,
    //Sending_Empty_Delay,
    //Sending_Empty_Delay,
    //Sending_Empty_Delay,
    //Sending_Empty_Delay,
    //Sending_PNInfor,
};
//==============================================================================
// Private macro
//==============================================================================
//==============================================================================
// Private Enum
//==============================================================================
//==============================================================================
// Private variables
//==============================================================================
unsigned char gPerviousCapacity;
unsigned char gEEPROM_Storing_Step;
unsigned char gOneWireTransmitByCmdCount;
unsigned char gOneWireTransmitByButtonCount;
unsigned char gOneWireTransmitAlwaysCount;

extern unsigned int sg_Protection_1_Status; //from Protection_Polling_Func.c

//==============================================================================
// Private function prototypes
//==============================================================================
// only for indecating Parsing File Name
// Do not modify
const unsigned char ParsingProjectNameStr[] = ParsingProjectName;
const unsigned char ParsingFileNameStr[] = ParsingFileName;
const unsigned char ParsingFwMajorVerStr = FW_MAJOR_VERSION;
const unsigned char ParsingFwMinorVerStr = FW_MINOR_VERSION;
const unsigned char ParsingFwReservedVerStr = FW_RESERVED_VERSION;
//.....................................................................
//const unsigned char Sys_Flash_Control_Bit = 0xff;
//__root __no_init volatile unsigned char Sys_Flash_Control_Bit @0x91e6;
//__root __no_init volatile unsigned char Sys_Flash_Control_Bit;
//volatile unsigned char Sys_Flash_Control_Bit = 0xff;
//==============================================================================
// Private functions
//==============================================================================
unsigned int FirstInitial_Func(void){

    //G_BAR_CODE_ID_Array[0] = ParsingFileName[0];
    _DUI_System_Init_And_Clk_Setup();

    //_DUI_BootloaderCheck_To_Disable();
    //_DUI_ReadOutProtection_Check_To_Enable();

//  GPIO_Init(GPIOA, GPIO_Pin_All ,GPIO_Mode_In_FL_No_IT);
//  GPIO_Init(GPIOB, GPIO_Pin_All, GPIO_Mode_In_FL_No_IT);
//  GPIO_Init(GPIOC, GPIO_Pin_All, GPIO_Mode_In_FL_No_IT);
//  GPIO_Init(GPIOD, GPIO_Pin_All, GPIO_Mode_In_FL_No_IT);
//  GPIO_Init(GPIOE, GPIO_Pin_All, GPIO_Mode_In_FL_No_IT);
//  GPIO_Init(GPIOF, GPIO_Pin_All,GPIO_Mode_In_FL_No_IT);
//

//    _DUI_delay_cycles(5000);    //5000 = 52ms at CCLK=4MHz.
//    _DUI_delay_cycles(500);     //500 = 5ms at CCLK=4MHz.
//    _DUI_delay_cycles(200);     //200 = 2ms at CCLK=4MHz.
//    _DUI_delay_cycles(100);     //100 = 1ms at CCLK=2MHz.
//
//    _DUI_delay_cycles(10000);   //10000 = 53ms at CCLK=8MHz.
//    _DUI_delay_cycles(1000);    //1000 = 5.38ms at CCLK=8MHz.
//    _DUI_delay_cycles(500);     //500 = 2.6ms at CCLK=8MHz.
//    _DUI_delay_cycles(100);     //100 = 550us at CCLK=8MHz.


#if(_LED_Control_Reverse_With_Lo_LEVEL_Turn_ON_ == 1)
    if(System_Control_Bit_EEPROM & SYS_UPDATED_FW){
        GPIO_Init(LED1_PORT, LED1_PIN, GPIO_Mode_Out_PP_Low_Slow);  // set as output and PP Low level
        GPIO_Init(LED3_PORT, LED3_PIN, GPIO_Mode_Out_PP_Low_Slow);  // set as output and PP Low level
        GPIO_LOW(LED1_PORT, LED1_PIN);
        GPIO_LOW(LED3_PORT, LED3_PIN);
        ((void(*)())Bootloader_After_ROP_Check_Address)();  //jump to the address directly
    }

//    if((Sys_Flash_Control_Bit & SYS_Ready_UPDATED_FW_Mask_Bit) == 0){
//        GPIO_Init(LED1_PORT, LED1_PIN, GPIO_Mode_Out_PP_Low_Slow);  // set as output and PP Low level
//        GPIO_Init(LED3_PORT, LED3_PIN, GPIO_Mode_Out_PP_Low_Slow);  // set as output and PP Low level
//        GPIO_LOW(LED1_PORT, LED1_PIN);
//        GPIO_LOW(LED3_PORT, LED3_PIN);
//        ((void(*)())Bootloader_After_ROP_Check_Address)();  //jump to the address directly
//    }
#else
    if(System_Control_Bit_EEPROM & SYS_UPDATED_FW){
        GPIO_Init(LED1_PORT, LED1_PIN, GPIO_Mode_Out_PP_Low_Slow);  // set as output and PP Low level
        GPIO_Init(LED3_PORT, LED3_PIN, GPIO_Mode_Out_PP_Low_Slow);  // set as output and PP Low level
        GPIO_HIGH(LED1_PORT, LED1_PIN);
        GPIO_HIGH(LED3_PORT, LED3_PIN);
        ((void(*)())Bootloader_After_ROP_Check_Address)();  //jump to the address directly
    }
//    if((Sys_Flash_Control_Bit & SYS_Ready_UPDATED_FW_Mask_Bit) == 0){
//        GPIO_Init(LED1_PORT, LED1_PIN, GPIO_Mode_Out_PP_Low_Slow);  // set as output and PP Low level
//        GPIO_Init(LED3_PORT, LED3_PIN, GPIO_Mode_Out_PP_Low_Slow);  // set as output and PP Low level
//        GPIO_HIGH(LED1_PORT, LED1_PIN);
//        GPIO_HIGH(LED3_PORT, LED3_PIN);
//        ((void(*)())Bootloader_After_ROP_Check_Address)();  //jump to the address directly
//    }
#endif
    _DUI_GPIO_LowPower_Config();
//    while(1){
//        wfi();
//    }
    _DUI_InitLEDDisplay();

    return StartUp;
}

unsigned int Startup_Func()
{
    _DUI_System_Init_And_Clk_Setup();

    //EEPROM information has not been re-initial
    while(1){
        if((System_Control_Bit_EEPROM & SYS_INIT_DATA_SET1) && (System_Control_Bit_EEPROM & SYS_INIT_DATA_SET2)){
            break;
        }else{
            _DUI_LED_Flashing_Directly();
        }
    }

    _DUI_EEPROM_Access_Enable();

    ////////////////////////////////////////////////////////////////////////////
    // check and modify System setting Information to EEPROM
    if((SystemSetting_Info_Byte1_Calculation != SystemSetting_Info_Byte1) ||
       (SystemSetting_Info_Byte2_Calculation != SystemSetting_Info_Byte2) ||
       (SystemSetting_Info_Byte3_Calculation != SystemSetting_Info_Byte3)){
        _DUI_EEPROM_WriteByte(SystemSetting_Info_Byte1_Offset , SystemSetting_Info_Byte1_Calculation);
        _DUI_delay_cycles(100);     //100 = 550us at CCLK=8MHz.
        _DUI_EEPROM_WriteByte(SystemSetting_Info_Byte2_Offset , SystemSetting_Info_Byte2_Calculation);
        _DUI_delay_cycles(100);     //100 = 550us at CCLK=8MHz.
        _DUI_EEPROM_WriteByte(SystemSetting_Info_Byte3_Offset , SystemSetting_Info_Byte3_Calculation);
        _DUI_delay_cycles(100);     //100 = 550us at CCLK=8MHz.
    }
    ////////////////////////////////////////////////////////////////////////////
    // check and modify FW Version to EEPROM
    if((VERSION != FW_MAJOR_VERSION) || (MINOR_VERSION != FW_MINOR_VERSION) || (RESERVED_VERSION != FW_RESERVED_VERSION)){
        _DUI_EEPROM_WriteByte(VERSION_Offset , FW_MAJOR_VERSION);
        _DUI_delay_cycles(100);     //100 = 550us at CCLK=8MHz.
        _DUI_EEPROM_WriteByte(MINOR_VERSION_Offset , FW_MINOR_VERSION);
        _DUI_delay_cycles(100);     //100 = 550us at CCLK=8MHz.
        _DUI_EEPROM_WriteByte(RESERVED_VERSION_Offset , FW_RESERVED_VERSION);
        _DUI_delay_cycles(100);     //100 = 550us at CCLK=8MHz.
    }
    ////////////////////////////////////////////////////////////////////////////
    // check and store MCU UID to EEPROM
    unsigned int i;
    unsigned char c1, c2;
    //unsigned char flag;
    //flag = false;
    for(i = 0; i < Unique_ID_Registers_Length; i++){
        c1 = (*((unsigned char *)(Unique_ID_Registers_Address + i)));
        c2 = (*((unsigned char *)(CONFIG_SEGMENT + MCU_UID_Offset + i )));
        if( c1 != c2){
            _DUI_EEPROM_WriteByte(MCU_UID_Offset + i, c1);
            _DUI_delay_cycles(500);     //500 = 2.6ms at CCLK=8MHz.
            //flag = true;
            //break;
        }
    }
//    if(flag){
//        for(i = 0; i < Unique_ID_Registers_Length; i++){
//            c1 = (*((unsigned char *)(Unique_ID_Registers_Address + i)));
//            _DUI_EEPROM_WriteByte(MCU_UID_Offset + i, c1);
//            //_DUI_delay_cycles(500);     //500 = 2.6ms at CCLK=8MHz.
//        }
//    }
//    ////////////////////////////////////////////////////////////////////////////
//    // check and store MCU UID to EEPROM
//    unsigned int i;
//    unsigned char c1, c2, flag;
//    flag = false;
//    for(i = 0; i < Unique_ID_Registers_Length; i++){
//        c1 = (*((unsigned char *)(Unique_ID_Registers_Address + i)));
//        c2 = (*((unsigned char *)(CONFIG_SEGMENT + MCU_UID_Offset + i )));
//        if( c1 != c2){
//            flag = true;
//            break;
//        }
//    }
//    if(flag){
//        for(i = 0; i < Unique_ID_Registers_Length; i++){
//            c1 = (*((unsigned char *)(Unique_ID_Registers_Address + i)));
//            _DUI_EEPROM_WriteByte(MCU_UID_Offset + i, c1);
//            //_DUI_delay_cycles(500);     //500 = 2.6ms at CCLK=8MHz.
//        }
//    }
    ////////////////////////////////////////////////////////////////////////////
    _DUI_EEPROM_Access_Disable();

	//Initialization
	disableInterrupts();  /* disable interrupts */

    _DUI_GPIO_LowPower_Config();
    _DUI_InitLEDDisplay();

#if (_USE_USB_POWER_OUTPUT_MODULE_ == 1)
    _DUI_Init_USB_Output_Power_Signal_Control();
#endif

    _DUI_LED_Flashing_Directly();

    for(i = 0; i < VarArray_Int_Size; i++){
        G_Var_Array[i] = 0;
    }
    for(i = 0; i < BAR_CODE_ID_Array_Whole_Size; i++){
        G_BAR_CODE_ID_Array[i] = 0;
    }

    _Device_WWDG_Config();
    _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset

    G_SysModeStatusCode = 0;
    G_Module_Status = 0;
    G_Module_Function_Status = 0;
    G_Add_Module_Function_Status = 0;
    G_Device_Interface_Status = 0;
    G_Extend_Device_Interface_Status = 0;

    G_DSG_Current_ADC = 0;
    G_CHG_Current_ADC = 0;
    G_VBAT_ADC = 0;
    G_NTC1_ADC = 0;
    G_NTC2_ADC = 0;
    G_Vref_mVoltage = 0;
    G_Current_Capacity = 0;
    G_Hold_Capacity = 0;
    G_Capacity_Var_Bits_Status = 0;

    gEEPROM_Storing_Step = 0;
	
//    InitLEDDisplay();
    _DUI_InitMosControl();
    _DUI_InitButtonEvent();
    _DUI_InitOutputSignals();
    _DUI_InitInputSignals();

    _DUI_InitADCFunction();
    _DUI_InitTimerFunction();
    _DUI_EEPROM_Access_Enable();

    _DUI_Communication_Enable();

    _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset

#if (_USE_TOUCH_KEY_WITH_LED_ == 1)
            _DUI_Initial_Touch_Key_Led();
            _DUI_Set_Touch_Key_Led_Blinking(DeviceOn);
#endif


#if (_LED_BackLight_Control_ == 1)
    _DUI_Init_BackLight_Control();
#endif

//
//
//    delay_cycles(5);
//    InitUARTFunction();
//
//    SysInfo_init();
//
//    /////////////////////////////////
//    InitSubPollingProtectionVariables();
//    InitADCFunction();
//    Set_Interrupt_ADC_Conversion_Finish_Function(ProtectionForPolling); //wait for startAdcConversion()
//
//    /////////////////////////////////
//    InitTimerPollingVariables();
//    //InitTimerFunction();
//    InitAWUTimerFunction();
//    Set_AWU_Shorter_Timer_Interval_Time_Base();
//
//
    enableInterrupts();  /* enable interrupts */
//
//    if(!(System_Control_Bit_EEPROM & Calibration_Done)){
//        return ShutdownMode;
//    }


    /////////////////////////////////////////////////////////////////////////////////////////////
    // ADC Scan
    //GPIO_HIGH(LED1_PORT, LED1_PIN);
    _DUI_ADC_Channels_Scan();
    //GPIO_LOW(LED1_PORT, LED1_PIN);


    //_Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
    //_DUI_delay_cycles(500);     //500 = 2.6ms at CCLK=8MHz.


    _DUI_delay_cycles(10000);    //100 = 1ms at CCLK=4MHz. 10000 = 100ms
    _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset


    return NormalMode;
}

//unsigned char inverse_led1_flag = 0;
//unsigned char inverse_led2_flag = 0;
//unsigned char oneSec_flag = 0;
//unsigned char testarray[10];
//unsigned int testWord[5];
void test1(){
    GPIO_TOGGLE(LED1_PORT, LED1_PIN);
}
void test2(){
    GPIO_TOGGLE(LED2_PORT, LED2_PIN);

}
unsigned int Normal_Func(){

    gOneWireTransmitByCmdCount = 0;
    gOneWireTransmitByButtonCount = 0;
    gOneWireTransmitAlwaysCount = 0;

    _DUI_Set_Interrupt_Timer_Calling_Function(0, Timer_Counter_For_Polling);
    InitTimerPollingVariables();
    _DUI_Set_Interrupt_Timer_Calling_Function(1, Protection_Polling_Function);
    InitProtectionPollingFuncVariables();
    _DUI_Set_Interrupt_Timer_Calling_Function(2, UpdatedSystemRecordingInfoForPolling);
    SysInfo_init();

    _DUI_Set_Interrupt_Timer_Calling_Function(3, Capacity_Timer_Polling_Func_In_Interrupt);
    InitCapacityDisplayFuncVariables();
#if defined(System_Clock_Freq_8MHz)
    _DUI_Set_Fast_Interrupt_Timer_Calling_Function(0, _Device_Reset_WWDG_Counter);
#else
    _DUI_Set_Interrupt_Timer_Calling_Function(4, _Device_Reset_WWDG_Counter);
#endif

#if (_USE_USB_POWER_OUTPUT_MODULE_ == 1)
		// remove the polling into protection polling function
    //_DUI_Set_Interrupt_Timer_Calling_Function(5, _DUI_USB_Power_Output_Control_Polling);
#endif

    _Device_Reset_WWDG_Counter();    //Refresh WWDG counter to Stop MCU reset
    _DUI_Set_TimerFunction_Cmd(DeviceOn);



#if _ONE_WIRE_UART_BUTTON_TEMPORARY_SET_ENABLE_
    G_Add_Module_Function_Status |= ONE_WIRE_UART_SET_ENABLE;
#endif
#if _ONE_WIRE_UART_ALWAYS_TRANSMIT_SET_ENABLE_
    G_Add_Module_Function_Status |= ONE_WIRE_TRANSMIT_ALWAYS;
#endif
    //    oneSec_flag = 0;
    while((G_Module_Function_Status & SYS_1_SEC_FLAG)==0);

    while(1){


        //_Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
        //_DUI_ReceiveDataParsingBy_RX_FRAME_DONE_For_Polling();


        Capacity_Main_System_Polling_Func_Not_In_Interrupt();

        if(G_Add_Module_Function_Status & BUTTON_LONG_PRESS){
            //GPIO_TOGGLE(LED2_PORT, LED2_PIN);
            G_Add_Module_Function_Status &= ~BUTTON_LONG_PRESS;

#if (_LED_BackLight_Control_ == 1)
         _DUI_Set_BackLight_Output(DeviceOff);
         _DUI_Set_BackLight_Button_Interrupt_Enable(Disable);
#endif


#if (_AUTO_ENTER_SLEEPING_MODE_PREASS_TO_WAKE_UP_ == 1)
            G_Module_Function_Status |= Auto_Sleeping_Entry;
            //_DUI_LED_TurnOff_serially();
            //_Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
#else

            ///////////////////////////////////////////////////////
            // turn off all devices
            _DUI_Set_TimerFunction_Cmd(DeviceOff);
            _DUI_InitMosControl();
            _DUI_InitOutputSignals();
            _DUI_Disable_ADCFunction();
            _DUI_InitTimerFunction();

#if (_USE_TOUCH_KEY_WITH_LED_ == 1)
            _DUI_Initial_Touch_Key_Led();
            _DUI_Set_Touch_Key_Led_Blinking(DeviceOff);
#endif  //#if (_USE_TOUCH_KEY_WITH_LED_ == 1)
            _DUI_InitLEDDisplay();

#if (_USE_USB_POWER_OUTPUT_MODULE_ == 1)
            _DUI_Init_USB_Output_Power_Signal_Control();
#endif

            ////////////////////////////////////////////////////////////////////////////////////
            // Record System information to EEPROM : (section start)
            /////////////////////////////////////////////////
            // Storing Information To EEPROM
            _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
            if(G_Device_Interface_Status & SYS_INFO_RECORD_TO_EEPROM){
                G_Device_Interface_Status &= ~SYS_INFO_RECORD_TO_EEPROM;
                _DUI_delay_cycles(2000);     //500 = 2.6ms at CCLK=8MHz.
                _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
            }
            for(gEEPROM_Storing_Step = 0; gEEPROM_Storing_Step < Storing_Last_Step; gEEPROM_Storing_Step++){
                Storing_Infor_To_EEPROM_By_Step(gEEPROM_Storing_Step);
                _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
            }

            gEEPROM_Storing_Step = 0;
            // Record System information to EEPROM : (section stop)
            ////////////////////////////////////////////////////////////////////////////////////

            _DUI_EEPROM_Access_Disable();

            _DUI_Communication_Disable();
            _DUI_delay_cycles(500);     //500 = 2.6ms at CCLK=8MHz.
            _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset

            return ShutdownMode;
            //return Sleeping_AutoWakeupMode;
#endif  //#if else(_AUTO_ENTER_SLEEPING_MODE_PREASS_TO_WAKE_UP_ == 1)
        }

        ///////////////////////////////////////////////////////////////
        // showing capacity by button click
        if(G_Add_Module_Function_Status & BUTTON_CLICK){
            G_Add_Module_Function_Status &= ~BUTTON_CLICK;
//            //GPIO_TOGGLE(LED1_PORT, LED1_PIN);
//            if(inverse_led1_flag == 0){
//                _Device_Set_Breathing_Light_LED_BIT(_Device_Get_Last_PWM_LED_Bit_By_LED_NUMs(4));
//                _Device_Set_Led_OnOff_By_BITs(LED2_BIT | LED1_BIT );
//                _Device_Set_Blinking_Light_LED_BIT( 0 );
//
//            }else{
//                _Device_Set_Blinking_Light_LED_BIT( 0 );
//                //_Device_Set_Breathing_Light_LED_BIT(_Device_Get_Last_PWM_LED_Bit_By_LED_NUMs(0));
//                //_Device_Set_Led_OnOff_By_BITs(_Device_Get_LED_Bit_By_LED_NUMs(5));
//            }
//            inverse_led1_flag ^= 0x01;


#if (_Enable_SW_Button_Only_For_Turn_ON_OFF_System_ == 1)
            if(G_Module_Function_Status & SW_PRESS_FOR_TURN_OFF_DSG){
                G_Module_Function_Status &= ~SW_PRESS_FOR_TURN_OFF_DSG;
            }else{
                G_Module_Function_Status |= SW_PRESS_FOR_TURN_OFF_DSG;
            }
#else
#if (_LED_SETTING_NUMBERS_ != 0)
            Capacity_Display_By_User();
#endif
#endif
//            if((G_Module_Status & Current_Dir_CHG) == 0){
//                G_Add_Module_Function_Status &= ~ONE_WIRE_DISABLE_BY_CHG;
//            }else{
//                G_Add_Module_Function_Status |= ONE_WIRE_DISABLE_BY_CHG;
//            }
//            G_Add_Module_Function_Status |= ONE_WIRE_TEMPORARY_START_COUNT;

#if (_Enable_MagneticReedSW_AsButton_Only_For_RxTx_ == 1)
            G_Add_Module_Function_Status |= ONE_WIRE_TEMPORARY_START_COUNT;
#endif


        }//if(G_Add_Module_Function_Status & BUTTON_CLICK){

        if((G_Module_Status & Current_Dir_CHG) == 0){
            G_Add_Module_Function_Status &= ~ONE_WIRE_DISABLE_BY_CHG;
        }else{
            G_Add_Module_Function_Status |= ONE_WIRE_DISABLE_BY_CHG;
        }

//        if(G_Add_Module_Function_Status & BUTTON_CLICK){
//            //GPIO_TOGGLE(LED1_PORT, LED1_PIN);
//            if((G_Add_Module_Function_Status & Breathing_Light_START) == 0){
//                //Display_Breathing_Light(2);
//            }
//
////            if(oneSec_flag == 0){
////               _Device_Set_Timer4_Interrupt_Timer_Calling_Function_With_Delay_And_Exec(1, test2, 3);
////            }else if(oneSec_flag == 2){
////                _Device_Remove_Timer4_Interrupt_Timer_Calling_Function(0);
////            }else if(oneSec_flag == 4){
////                _Device_Remove_Timer4_Interrupt_Timer_Calling_Function(1);
////            }else if(oneSec_flag == 6){
////                _Device_Set_Timer4_Interrupt_Timer_Calling_Function_With_Delay_And_Exec(1, test2, 3);
////            }else if(oneSec_flag == 8){
////                _Device_Remove_Timer4_Interrupt_Timer_Calling_Function(1);
////            }
////            oneSec_flag++;
//            G_Add_Module_Function_Status &= ~BUTTON_CLICK;
//        }
        if(G_Add_Module_Function_Status & BUTTON_COMPLETE_MULTI_CLICK){
            G_Add_Module_Function_Status &= ~BUTTON_COMPLETE_MULTI_CLICK;
            //GPIO_TOGGLE(LED4_PORT, LED4_PIN);

            G_Add_Module_Function_Status |= ONE_WIRE_TEMPORARY_START_COUNT;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        // Each one second calling : (section start)
        if(G_Module_Function_Status & SYS_1_SEC_FLAG){
            ////////////////////////////////////////////////////////////////////////////////////
            G_Module_Function_Status &= ~SYS_1_SEC_FLAG;
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            //One Wire TEMPORARY communication enable : (section start)
            if((G_Add_Module_Function_Status & ONE_WIRE_UART_SET_ENABLE) &&((G_Add_Module_Function_Status & ONE_WIRE_TRANSMIT_ALWAYS)==0)){
                if(G_Add_Module_Function_Status & ONE_WIRE_TEMPORARY_START_COUNT){
                    if((G_Add_Module_Function_Status & ONE_WIRE_DISABLE_BY_CHG) == 0){
                       _DUI_Set_OneWire_Communication_Enable(DeviceOn);
                    }else{
                       _DUI_Set_OneWire_Communication_Enable(DeviceOff);
                    }
//                    if(G_Add_Module_Function_Status & ONE_WIRE_Send_EEPROM_Data){
//                        _DUI_One_Wire_Send_EEPROM_DATA_CRC16();
//                        G_Add_Module_Function_Status &= ~ONE_WIRE_Send_EEPROM_Data;
//
//                    }else{
//                        _DUI_One_Wire_Send_Word_CRC16(G_Var_Array, VarArray_Int_Size);
//                        G_Add_Module_Function_Status |= ONE_WIRE_Send_EEPROM_Data;
//                    }

                    _DUI_Send_One_Wire_Information_Data_By_Step(Sending_One_Wire_Array_Step_Base_On_1_Sec[gOneWireTransmitByButtonCount]);
                    gOneWireTransmitByButtonCount++;
                    if(gOneWireTransmitByButtonCount >= Sending_One_Wire_Array_Step_Base_On_1_Sec_Length){
                        gOneWireTransmitByButtonCount = 0;
                    }
                }else{
                    _DUI_Set_OneWire_Communication_Enable(DeviceOff);
                    gOneWireTransmitByButtonCount = 0;
                }
            }else if(G_Add_Module_Function_Status & ONE_WIRE_TRANSMIT_ALWAYS){

                _DUI_Set_OneWire_Communication_Enable(DeviceOff);

//                if(G_Add_Module_Function_Status & ONE_WIRE_Send_EEPROM_Data){
//                    _DUI_One_Wire_Send_EEPROM_DATA_CRC16();
//                    G_Add_Module_Function_Status &= ~ONE_WIRE_Send_EEPROM_Data;
//
//                }else{
//                    _DUI_One_Wire_Send_Word_CRC16(G_Var_Array, VarArray_Int_Size);
//                    G_Add_Module_Function_Status |= ONE_WIRE_Send_EEPROM_Data;
//                }

                _DUI_Send_One_Wire_Information_Data_By_Step(Sending_One_Wire_Array_Step_Base_On_1_Sec[gOneWireTransmitAlwaysCount]);
                gOneWireTransmitAlwaysCount++;
                if(gOneWireTransmitAlwaysCount >= Sending_One_Wire_Array_Step_Base_On_1_Sec_Length){
                    gOneWireTransmitAlwaysCount = 0;
                }
            }else{
                _DUI_Set_OneWire_Communication_Enable(DeviceOff);
                gOneWireTransmitAlwaysCount = 0;
            }//if(ONE_WIRE_TEMPORARY_ENABLE){ - else
            //One Wire TEMPORARY communication enable : (section stop)
            ////////////////////////////////////////////////////////////////////////////////////

        }//if(G_Module_Function_Status & SYS_1_SEC_FLAG){
        // Each one second calling : (section stop)
        ////////////////////////////////////////////////////////////////////////////////////

//        ////////////////////////////////////////////////////////////////////////////////////
//        // Each calling about 10ms to 150ms : (section start)
//        if(G_Add_Module_Function_Status & ONE_WIRE_TRANSMIT_ONCE_BY_CMD){
//            if((G_Add_Module_Function_Status & ONE_WIRE_Send_EEPROM_Data)==0){
//                _DUI_One_Wire_Send_Word_CRC16(G_Var_Array, VarArray_Int_Size);
//                G_Add_Module_Function_Status |= ONE_WIRE_Send_EEPROM_Data;
//                gOneWireTransmitByCmdCount = 0;
//            }else{
//                if(gOneWireTransmitByCmdCount >= OneWireTransmitByCmd_2ndTX_DeleyCycle){
//                    gOneWireTransmitByCmdCount = 0;
//                    _DUI_One_Wire_Send_EEPROM_DATA_CRC16();
//                    G_Add_Module_Function_Status &= ~ONE_WIRE_TRANSMIT_ONCE_BY_CMD;
//                    G_Add_Module_Function_Status &= ~ONE_WIRE_Send_EEPROM_Data;
//                }else{
//                    gOneWireTransmitByCmdCount++;
//                }
//            }
//        }//if(G_Add_Module_Function_Status & ONE_WIRE_TRANSMIT_ONCE_BY_CMD){
//        // Each calling about 10ms to 150ms : (section stop)
//        ////////////////////////////////////////////////////////////////////////////////////


        ////////////////////////////////////////////////////////////////////////////////////
        // Sending System information through UART : (section start)
        if(G_Add_Module_Function_Status & ONE_WIRE_TRANSMIT_ONCE_BY_CMD){
            //each step internal time is about 62 ms
            _DUI_Send_One_Wire_Information_Data_By_Step(Sending_One_Wire_Array_Step_Base_Timer[gOneWireTransmitByCmdCount]);
            gOneWireTransmitByCmdCount++;
            if(gOneWireTransmitByCmdCount >= Sending_One_Wire_Array_Step_Base_On_Timer_Length){
                gOneWireTransmitByCmdCount = 0;
                G_Add_Module_Function_Status &= ~ONE_WIRE_TRANSMIT_ONCE_BY_CMD;
            }
        }
        // Sending System information through UART : (section stop)
        ////////////////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////////////////
        // Record System information to EEPROM : (section start)
        if(G_Device_Interface_Status & SYS_INFO_RECORD_TO_EEPROM){
            Storing_Infor_To_EEPROM_By_Step(gEEPROM_Storing_Step);
            gEEPROM_Storing_Step++;
            if(gEEPROM_Storing_Step > Storing_Last_Step){
                gEEPROM_Storing_Step = 0;
                G_Device_Interface_Status &= ~SYS_INFO_RECORD_TO_EEPROM;
            }
        }else{
            gEEPROM_Storing_Step = 0;
        }
        // Record System information to EEPROM : (section stop)
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        // Record BAR CODE information to EEPROM : (section start)
        if(G_BAR_CODE_ID_Array[0] == 0x01){
            Write_BAR_CODE_ID_To_EEPROM();
        }
        // Record BAR CODE information to EEPROM : (section stop)
        ////////////////////////////////////////////////////////////////////////////////////

        if((G_Module_Status & CHG_MOS_FAIL) && ((System_Control_Bit_EEPROM & SYS_CHG_MOS_FAIL_SET) == 0)){
            _DUI_Set_System_Control_Bit_To_EEPROM(SYS_CHG_MOS_FAIL_SET , Enable);
        }
        if((G_Module_Status & DSG_MOS_FAIL) && ((System_Control_Bit_EEPROM & SYS_DSG_MOS_FAIL_SET) == 0)){
            _DUI_Set_System_Control_Bit_To_EEPROM(SYS_DSG_MOS_FAIL_SET , Enable);
        }
//        if(G_Device_Interface_Status & Breathing_Light_FINISH){
//            _DUI_Finish_Display_Breathing_Light();
//            G_Device_Interface_Status &= ~Breathing_Light_FINISH;
//        }

#if (_AUTO_ENTER_SLEEPING_MODE_PREASS_TO_WAKE_UP_ == 1)
        //unsigned char icount;

        //AUTO_ENTER_SLEEPING_MODE
        if(G_Module_Function_Status & Auto_Sleeping_Entry){

#if (_LED_BackLight_Control_ == 1)
         _DUI_Set_BackLight_Output(DeviceOff);
         _DUI_Set_BackLight_Button_Interrupt_Enable(Disable);
#endif
            _DUI_LED_TurnOff_serially();
            _DUI_Set_TimerFunction_Cmd(DeviceOff);

            _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset

            _DUI_Communication_Disable();

            gEEPROM_Storing_Step = 0;
            G_Device_Interface_Status &= ~SYS_INFO_RECORD_TO_EEPROM;
            for(gEEPROM_Storing_Step = 0; gEEPROM_Storing_Step < Storing_Last_Step; gEEPROM_Storing_Step++){
                Storing_Infor_To_EEPROM_By_Step(gEEPROM_Storing_Step);
                _DUI_delay_cycles(500);     //500 = 2.6ms at CCLK=8MHz.
                _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
            }

#if (_USE_TOUCH_KEY_WITH_LED_ == 1)
            _DUI_Set_Touch_Key_Led(DeviceOff);
#endif
            G_Module_Function_Status &= ~Auto_Sleeping_Entry;

#if (_USE_USB_POWER_OUTPUT_MODULE_ == 1)
            _DUI_Init_USB_Output_Power_Signal_Control();
#endif

#if (_AUTO_RTC_PERIOD_WAKE_UP_FOR_AUTO_SLEEPING_ == 1)

            //_DUI_Set_TimerFunction_Cmd(DeviceOff);
            _DUI_Set_NTC_Detect_Control_Enable(DeviceOff);
            _DUI_Set_CHG_MosFET(DeviceOn);
            //_DUI_Set_DSG_MosFET(DeviceOn);
#if (_AUTO_RTC_PERIOD_WAKE_UP_With_DSG_MOS_OFF_ == 1)
            _DUI_Set_DSG_MosFET(DeviceOff);
#endif
#if (_AUTO_RTC_PERIOD_WAKE_UP_With_CHG_MOS_OFF_ == 1)
            _DUI_Set_CHG_MosFET(DeviceOff);
#endif

            _DUI_delay_cycles(100);    //100 = 519us at CCLK=8MHz. recheck at 2013/12/20
//            _DUI_delay_cycles(500);    //500 = 2.56ms at CCLK=8MHz. recheck at 2013/12/20
//            _DUI_delay_cycles(1000);    //1000 = 5.123ms at CCLK=8MHz. recheck at 2013/12/20
//            _DUI_delay_cycles(1500);    //1500 = 7.68ms at CCLK=8MHz. recheck at 2013/12/20
//            _DUI_delay_cycles(2000);    //2000 = 10.236ms at CCLK=8MHz. recheck at 2013/12/20

            //icount = 0;
            //halt();
            _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
            Sleeping_In_Halt_AutoWakeup();

            _DUI_delay_cycles(100);    //100 = 519us at CCLK=8MHz. recheck at 2013/12/20
            _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset

#else
            unsigned char icount;
            _DUI_Set_CHG_MosFET(DeviceOff);
            _DUI_Set_DSG_MosFET(DeviceOff);

            //_DUI_Set_TimerFunction_Cmd(DeviceOff);
        into_halt_mode:
            _DUI_Set_NTC_Detect_Control_Enable(DeviceOff);
            icount = 0;
            halt();

            for(icount = 0; icount < 10; icount++){
                _DUI_delay_cycles(10000);    //100 = 1ms at CCLK=4MHz. 10000 = 100ms
                _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
            }
            if(_DUI_GetButtonStatus() != ButtonPress){
                goto into_halt_mode;
            }

#endif

#if (_Enable_Coulomb_Counter_FCC_RM_ == 1)
            // by hsinmo 2014/06/05
            // for lev assembling process failure, and causing Voltage error and FCC derating.
            // so reset CoulombCounter at first wakeup
            if((G_Extend_Device_Interface_Status & HasSleptOnce) == 0){
                G_Extend_Device_Interface_Status |= HasSleptOnce;
                InitCoulombCounterCap();
            }
#endif

            _DUI_Set_NTC_Detect_Control_Enable(DeviceOn);
            _DUI_LED_Flashing_Directly();

            _DUI_Communication_Enable();

            _DUI_Set_TimerFunction_Cmd(DeviceOn);

#if (_LED_BackLight_Control_ == 1)
         _DUI_Set_BackLight_Button_Interrupt_Enable(Enable);
#endif
        }else{
            wfi();  /* Wait For Interrupt */
        }
#else
        wfi();  /* Wait For Interrupt */
#endif
     }//while(1);
}

#if (_AUTO_RTC_PERIOD_WAKE_UP_FOR_AUTO_SLEEPING_ == 1)
void Sleeping_In_Halt_AutoWakeup(){

    unsigned char icount;
    float countTemp;
    //unsigned char ionce;
    //signed int temp;

    //icount = 0;
    G_ul_Current_InSleepingMode_Times = 0;
    //_DUI_InitButtonEvent();
    //*pSleepingTotalTimes = 0xfffe;
    //G_Sleeping_Mode_State = 0;
    _Device_Active_Halt_Config_With_RTC_WakeUp();
    while(1){
        //GPIO_TOGGLE(LED4_PORT, LED4_PIN);
        //GPIO_LOW(LED5_PORT, LED5_PIN);
        halt();
        //GPIO_HIGH(LED5_PORT, LED5_PIN);
        _DUI_System_Clk_Switch_To_HSI();

        G_ul_Current_InSleepingMode_Times++;

        _DUI_delay_cycles(100);    //100 = 519us at CCLK=8MHz. recheck at 2013/12/20
        _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
        //_DUI_delay_cycles(2000);    //2000 = 10.236ms at CCLK=8MHz. recheck at 2013/12/20
        //*pSleepingTotalTimes += 1;
        ///////////////////////////////////////////////////////////////////////////////

//        _DUI_delay_cycles(100);    //100 = 519us at CCLK=8MHz. recheck at 2013/12/20
//        _DUI_delay_cycles(500);    //500 = 2.56ms at CCLK=8MHz. recheck at 2013/12/20
//        _DUI_delay_cycles(1000);    //1000 = 5.123ms at CCLK=8MHz. recheck at 2013/12/20
//        _DUI_delay_cycles(1500);    //1500 = 7.68ms at CCLK=8MHz. recheck at 2013/12/20
//        _DUI_delay_cycles(2000);    //2000 = 10.236ms at CCLK=8MHz. recheck at 2013/12/20

        //_Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset

        //_DUI_delay_cycles(500);    //500 = 2.56ms at CCLK=8MHz. recheck at 2013/12/20
        //_DUI_delay_cycles(100);     //100 = 111.4ms at CCLK = RTC CLK = 38kHz. recheck at 2013/12/20
        //_DUI_delay_cycles(10);     //10 = 12.8ms at CCLK = RTC CLK = 38kHz. recheck at 2013/12/20
        //_DUI_delay_cycles(5);      //5 = 7.2ms at CCLK = RTC CLK = 38kHz. recheck at 2013/12/20

        if(_DUI_Get_Communication_Pin_Interrupt_Received()){
            icount = 0;
            //_Device_Normal_Config_For_Exit_Halt();
            //G_Sleeping_Mode_State |= EXIT_FROM_UART;
            _DUI_Disable_RTC_WakeUp();
            break;
        }

        //////////////////////////////////////////////////////////////////////////
        // Button Press over 800ms
        icount = 0;
        for(icount = 0; icount < 80; icount++){
            if(_DUI_GetButtonStatus() == ButtonPress){
                _DUI_delay_cycles(2000);    //2000 = 10.236ms at CCLK=8MHz. recheck at 2013/12/20
                _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
            }else{
                break;
            }
        }
        if(icount > 75){
            //G_Sleeping_Mode_State |= EXIT_FROM_SW_BUTTON;
            _DUI_Disable_RTC_WakeUp();
            break;
        }
//        if((_DUI_GetButtonStatus() == ButtonPress)&&(icount > 0)){
//            icount = 0;
//            //_Device_Normal_Config_For_Exit_Halt();
//            _DUI_Disable_RTC_WakeUp();
//            break;
//        }
        ///////////////////////////////////////////////////////////////////////////////
        // check current
        UpdatedDetectingValues();
        UpdatedCurrentDirectionStatus();
        _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
        //if((G_Module_Status & Current_Dir_CHG)||(G_Module_Status & Current_Dir_DSG)){
        //if((G_Module_Status & Current_Dir_CHG_No_Delay)||(G_Module_Status & Current_Dir_DSG)){
        if(G_Module_Status & Current_Dir_CHG_No_Delay){
            //_Device_Normal_Config_For_Exit_Halt();
            //G_Sleeping_Mode_State |= EXIT_FROM_CHG_CURRENT;
            _DUI_Disable_RTC_WakeUp();
            break;
        }else if(G_Module_Status & Current_Dir_DSG){
            //_Device_Normal_Config_For_Exit_Halt();
            //G_Sleeping_Mode_State |= EXIT_FROM_DSG_CURRENT;
            _DUI_Disable_RTC_WakeUp();
            break;
        }
        _DUI_System_Clk_Switch_To_LSI();
        _DUI_delay_cycles(5);     //10 = 7.2ms at CCLK = RTC CLK = 38kHz.
    }//while(1)

    countTemp = G_ul_Current_InSleepingMode_Times;
    countTemp = SleepMode_Autowakeup_Intervaltimes_min * countTemp;
    G_ul_NowTotalTimes_Without_Charging_Minutes += (unsigned long)countTemp;
    G_ul_NowTotalTimes_Without_DisCharging_Minutes += (unsigned long)countTemp;

}//Sleeping_In_Halt_AutoWakeup(){
void Sleeping_In_Halt_AutoWakeup_org(){

    unsigned char icount;
    //unsigned char ionce;
    //signed int temp;

    //icount = 0;

    //_DUI_InitButtonEvent();

   // halt();
    /////////////////////////////////////////////////
    // Switch Clock From HSI (8MHz) to LSI (38KHz)
    // WWDG counter : Non-Allowed Refresh time 323.368ms
    // WWDG counter : Allowed Refresh time 20.695 sec
    // RTC Wake-up From Halt Mode is each 5 sec (real 5.33 sec)
    //
    _Device_Active_Halt_Config_With_RTC_WakeUp();
    //_DUI_delay_cycles(1000);     //100 = 111.4ms at CCLK = RTC CLK = 38kHz.
    //_Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
    while(1){
        /////////////////////////////////////////////////////////////////////////////////////////////
        //GPIO_HIGH(LED3_PORT, LED3_PIN);
        //GPIO_TOGGLE(LED2_PORT, LED2_PIN);
        /////////////////////////////////////////////////////////////////////////////////////////////
        // ADC Scan and ADC Values Getting and calibration
        // about delay 132ms
        //GPIO_HIGH(LED3_PORT, LED3_PIN);
        UpdatedDetectingValues();
        _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
        UpdatedCurrentDirectionStatus();
        //GPIO_LOW(LED3_PORT, LED3_PIN);
        //if((G_Module_Status & Current_Dir_CHG)||(G_Module_Status & Current_Dir_DSG)){
        if((G_Module_Status & Current_Dir_CHG_No_Delay)||(G_Module_Status & Current_Dir_DSG)){
            _Device_Normal_Config_For_Exit_Halt();
            break;
        }else{
            halt();
        }
        icount = 0;
        if(_DUI_GetButtonStatus() == ButtonPress){
            icount++;
        }
        _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
        //_DUI_delay_cycles(100);     //100 = 111.4ms at CCLK = RTC CLK = 38kHz.
        //_DUI_delay_cycles(10);     //10 = 12.8ms at CCLK = RTC CLK = 38kHz.
        _DUI_delay_cycles(20);     //10 = 12.8ms at CCLK = RTC CLK = 38kHz.
        if((_DUI_GetButtonStatus() == ButtonPress)&&(icount > 0)){
            icount = 0;
            _Device_Normal_Config_For_Exit_Halt();
            break;
        }
        if(_DUI_Get_Communication_Pin_Interrupt_Received()){
            icount = 0;
            _Device_Normal_Config_For_Exit_Halt();
            break;
        }
    }

}//Sleeping_In_Halt_AutoWakeup(){
#endif

unsigned int Shutdown_Func(){

    unsigned char icount;
#if (_USE_TOUCH_KEY_WITH_LED_ == 1)
    unsigned char TouchKeyLEDcount;
    unsigned char TouchKeyButtonStatus;
    TouchKeyButtonStatus = 0;
    TouchKeyLEDcount = 0;
#endif

    icount = 0;

    _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset

    _DUI_LED_TurnOff_serially();
    _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
    _DUI_GPIO_LowPower_Config();
    _DUI_Communication_Disable();
     _DUI_delay_cycles(10000);    //100 = 1ms at CCLK=4MHz. 10000 = 100ms
    _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
     _DUI_delay_cycles(10000);    //100 = 1ms at CCLK=4MHz. 10000 = 100ms
    _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset

    _DUI_InitButtonEvent();

    while(1){

        halt();

#if (_USE_TOUCH_KEY_WITH_LED_ == 1)
        TouchKeyButtonStatus = 1;
        _DUI_Set_Touch_Key_Led(DeviceOn);
#endif

        _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
        _DUI_Set_Interrupt_Timer_Calling_Function(0, Timer_Counter_For_Polling);
        InitTimerPollingVariables();
        _DUI_Set_TimerFunction_Cmd(DeviceOn);
        while(1){
            _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
            if(G_Add_Module_Function_Status & BUTTON_CLICK){
                G_Add_Module_Function_Status &= ~BUTTON_CLICK;
            }
            if(G_Add_Module_Function_Status & BUTTON_LONG_PRESS){
                //GPIO_TOGGLE(LED2_PORT, LED2_PIN);
                G_Add_Module_Function_Status &= ~BUTTON_LONG_PRESS;
                return StartUp;
            }
#if (_USE_TOUCH_KEY_WITH_LED_ == 1)

            if(_DUI_GetButtonStatus() != ButtonRelease){
                TouchKeyButtonStatus = 1;
            }
#endif

            if(G_Module_Function_Status & SYS_1_SEC_FLAG){
                G_Module_Function_Status &= ~SYS_1_SEC_FLAG;
#if (_USE_TOUCH_KEY_WITH_LED_ == 1)
                if(TouchKeyButtonStatus){
                    _DUI_Set_Touch_Key_Led(DeviceOn);
                    if(TouchKeyLEDcount >= TOUCH_KEY_LED_LIGHT_IN_SHUTDOWN_SECONDS){
                        TouchKeyLEDcount = 0;
                        _DUI_Set_Touch_Key_Led(DeviceOff);
                        TouchKeyButtonStatus = 0;
                    }else{
                        TouchKeyLEDcount++;
                    }
                }else{
                    TouchKeyLEDcount = 0;
                    _DUI_Set_Touch_Key_Led(DeviceOff);
                }
#endif
                if(_DUI_GetButtonStatus() == ButtonRelease){
                    if(icount >= WWAK_UP_HOLDING_Delay_SECONDS){
                        icount = 0;
                        _DUI_Set_TimerFunction_Cmd(DeviceOff);
                        break; //enter to halt mode
                    }else{
                        icount++;
                    }
                }else{
                    icount = 0;
                }//else - if(_DUI_GetButtonStatus() == ButtonRelease){
            }
            wfi();
        }
    }
}//unsigned int Shutdown_Func(){


unsigned int Sleeping_AutoWakeup_Func(){

    unsigned char icount;
#if (_USE_TOUCH_KEY_WITH_LED_ == 1)
    //unsigned char TouchKeyLEDcount;
    //unsigned char TouchKeyButtonStatus;
    //TouchKeyButtonStatus = 0;
    //TouchKeyLEDcount = 0;
#endif

    icount = 0;


    _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset

    _DUI_LED_TurnOff_serially();
    _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
    _DUI_GPIO_LowPower_Config();
    _DUI_Communication_Disable();
     _DUI_delay_cycles(10000);    //100 = 1ms at CCLK=4MHz. 10000 = 100ms
    _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
     _DUI_delay_cycles(10000);    //100 = 1ms at CCLK=4MHz. 10000 = 100ms
    _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset

    _DUI_InitButtonEvent();


    halt();
    /////////////////////////////////////////////////
    // Switch Clock From HSI (8MHz) to LSI (38KHz)
    // WWDG counter : Non-Allowed Refresh time 323.368ms
    // WWDG counter : Allowed Refresh time 20.695 sec
    // RTC Wake-up From Halt Mode is each 5 sec (real 5.33 sec)
    //
    _Device_Active_Halt_Config_With_RTC_WakeUp();

    while(1){
        if(icount == DeviceOn){
            icount = DeviceOff;
        }else{
            icount = DeviceOn;
        }

        halt();
        _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
        //_DUI_Set_Touch_Key_Led(icount);
//        if(TouchKeyLEDcount == 0){
//            _Device_Normal_Config_For_Exit_Halt();
//            TouchKeyLEDcount = 1;
//        }

//
//        for(icount=0; icount<100;icount++){
//            _Device_delay_cycles(15);
//        }

    }

}//unsigned int Sleeping_AutoWakeup_Func(){
