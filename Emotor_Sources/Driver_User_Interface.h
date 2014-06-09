
/**
  ******************************************************************************
  * @file    Driver_User_Interface.h
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   Deiver_User_Interface Header
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
#include "Drivers\Drivers.h"
#include "Config_Info\System_Config_Info.h"
#include "Global_Variable_Define.h"
//#include "Vars_Bits_Define.h"
//#include "Config_Info\User_Define_Parser.h"
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
//LED display numbers could be 3, 4, 5 LEDs, other numbers are invalid.
//#define SYSTEM_NUM_OF_LED     5
#define SYSTEM_NUM_OF_LED     _LED_SETTING_NUMBERS_

//communication define
#define MAX_CommunicationArray_Bytes_Size       (VarArray_Int_Size + VarArray_Int_Size)
#define CommunicationCRCCodeBytes               (2)
#define One_Wire_PrecedingCodeBytes             (4)
#define One_Wire_EndingCodeBytes                (4)

#define Back_Up_Bytes                           (4) //0ne for respond-command , another one for data length byte, other for reserved byte.

#define CommunicationArray_Data_Bytes_Size           (MAX_CommunicationArray_Bytes_Size)

#define CommunicationArray_Total_Bytes_Size           (CommunicationArray_Data_Bytes_Size + CommunicationCRCCodeBytes + One_Wire_PrecedingCodeBytes + One_Wire_EndingCodeBytes + Back_Up_Bytes)

#define Receiving_Buffer_Size               (30)
#define Receiving_Buffer_Total_Bytes_Size           (Receiving_Buffer_Size + CommunicationCRCCodeBytes + One_Wire_PrecedingCodeBytes + One_Wire_EndingCodeBytes + Back_Up_Bytes)

#define Unique_ID_Registers_Address         0x4926
#define Unique_ID_Registers_Length          (12)

extern unsigned char G_Communication_Array[];


#define LeadingCode                 (0x3A)
#define SlaveAddressCode            (0x16)
#define EndCode1                    (0x0D)
#define EndCode2                    (0x0A)
#define Respond_Error_Check_Code    (0xF3)
#define Respond_Accept_Check_Code   (0xF0)

#define MIN_Receive_Packet_Num      (9)
#define MIN_Receive_Packet_Index    (MIN_Receive_Packet_Num - 1)

#define ONE_WIRE_PrecedingCheckCode         (0x80f8)

#define ONE_WIRE_Data_PrecedingCode         (0x80A0)
#define ONE_WIRE_EEPROM_Seg_PrecedingCode   (0x80D0)
#define ONE_WIRE_PN_INFO_Seg_PrecedingCode  (0x80E0)


#define ONE_WIRE_EndCheckCode               (0x70f7)
//==============================================================================
// Private macro
//==============================================================================
//==============================================================================
// Private Enum
//==============================================================================
//==============================================================================
// Global variables define
//==============================================================================
/* Driver G_Device_Interface_Status Control Bits */
/* For G_Device_Interface_Status ; unsigned int */
//Low byte
#define CHG_MOSFET_STATUS               (0x0001)    //CHG MOSFET Status, set = turn on
#define DSG_MOSFET_STATUS               (0x0002)    //DSG MOSFET Status, set = turn on
#define ADC_CONVERSION                  (0x0004)    //
#define ADP_SOC_STATUS                  (0x0008)    //Adapter Soc Pin status
#define ONE_WIRE_ENABLE_STATUS          (0x0010)    //One Wire control pin enable for one-wire communication
#define UART_ISOLATE_ENABLE_STATUS      (0x0020)    //UART Isolation Enable for communication
#define NTC_ENABLE_STATUS               (0x0040)    //NTC Detection Enable control pin
#define POLLING_TIMER_ENABLE_STATUS     (0x0080)    //
////Hight byte
#define SYS_INFO_RECORD_TO_EEPROM       (0x0100)    //
#define BackLight_BUTTON_PRESS          (0x0200)    //
#define BackLight_BUTTON_CLICK          (0x0400)    //
#define BackLight_LED_OnOff_Status      (0x0800)    //
#define BackLight_Constant_ON           (0x1000)    ///
#define BackLight_Blinking              (0x2000)    //
#define HW_CHG_Status                   (0x4000)    //
#define HW_DSG_Status                   (0x8000)    //
/////////////////////////////////////////////////////////////////////////////////

/* Driver G_Extend_Device_Interface_Status Control Bits */
/* For G_Extend_Device_Interface_Status ; unsigned int */
//Low byte
#define UART_STATUS                     (0x0001)    //
#define UART_TX_IT_STATUS               (0x0002)    //
#define UART_RX_IT_STATUS               (0x0004)    //
#define UART_RX_FRAME_DONE              (0x0008)    //
#define UART_RX_PrecedingCode_Find      (0x0010)    //
#define UART_RX_EndingCode_Find         (0x0020)    //
#define UART_RX_FRAME_ADDRESS_FAIL      (0x0040)    //
#define UART_RX_FRAME_PACKET_FAIL       (0x0080)    //
////Hight byte
#define Force_DSG_MOS_OFF               (0x0100)    //
#define Force_CHG_MOS_OFF               (0x0200)    //
//#define                   (0x0400)    //
//#define               (0x0800)    //
//#define         (0x1000)    ///
//#define         (0x2000)    //
//#define            (0x4000)    //
//#define            (0x8000)    //
/////////////////////////////////////////////////////////////////////////////////
//==============================================================================
// Private variables
//==============================================================================
//==============================================================================
// Private function prototypes
//==============================================================================
//////////////////////////////////////////////////
// System Clock Setup  : (section start)
void _DUI_System_Init_And_Clk_Setup(void);
void _DUI_System_Clk_Switch_To_HSI(void);
void _DUI_System_Clk_Switch_To_LSI(void);
void _DUI_Enable_RTC_WakeUp(void);
void _DUI_Disable_RTC_WakeUp(void);
// System Clock Setup  : (section stop)
//////////////////////////////////////////////////
//////////////////////////////////////////////////
// Utility Functions  : (section start)
void _DUI_delay_cycles(unsigned long cycleCount);
void _DUI_GPIO_LowPower_Config(void);
void _DUI_BootloaderCheck_To_Disable();
void _DUI_SetBootloaderCheck(unsigned char enable);
void _DUI_ReadOutProtection_Check_To_Enable();
void _DUI_SetReadOutProtection(unsigned char enable);
void _DUI_Set_System_Control_Bit_To_EEPROM(unsigned char setBits, unsigned char enable);
//void _DUI_Set_Mask_Control_Bit_To_Code_Flash(unsigned char setBits, unsigned char enable);

// Utility Functions  : (section stop)
//////////////////////////////////////////////////
//////////////////////////////////////////////////
// LED function  : (section start)
void _DUI_InitLEDDisplay();
void _DUI_LED_Flashing_Directly();
void _DUI_LED_TurnOff_serially();

#if (_USE_TOUCH_KEY_WITH_LED_ == 1)
void _DUI_Initial_Touch_Key_Led();
void _DUI_Set_Touch_Key_Led(unsigned char Device_Enable);
void _DUI_Set_Touch_Key_Led_Blinking(unsigned char Device_Enable);
#endif


//void _DUI_Display_Breathing_Light(unsigned char NumOfLeds);
//void _DUI_Finish_Display_Breathing_Light();

// LED function  : (section end)
//////////////////////////////////////////////////
////////////////////////////////////////////
// MosFet control  : (section start)
void _DUI_InitMosControl();
void _DUI_Set_DSG_MosFET(unsigned char enable);
void _DUI_Set_CHG_MosFET(unsigned char enable);
// MosFet control  : (section stop)
////////////////////////////////////////////
////////////////////////////////////////////
// Button control  : (section start)
void Interrupt_Calling_ButtonEvent_Press_Trigger();
void _DUI_InitButtonEvent();
unsigned char _DUI_GetButtonStatus();
// Button control  : (section stop)
////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// Optput Signal Control GPIO peripheral : (section start)
// OneWireControl/UartIsolationControl/NTC_Control/Adapter SOC
void _DUI_InitOutputSignals();
void _DUI_Set_Adapter_SOC(unsigned char enable);
void _DUI_Set_OneWire_Communication_Enable(unsigned char enable);
void _DUI_Set_Uart_Isolation_Enable(unsigned char enable);
void _DUI_Set_NTC_Detect_Control_Enable(unsigned char enable);
// Optput Signal Control GPIO peripheral : (section stop)
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// Input Signal Control GPIO peripheral : (section start)
void _DUI_InitInputSignals();
#if (_ENABLE_FOR_Monitoring_HW_PIC_STATUS_ == 1)
unsigned char _DUI_Get_HW_CHG_Signal_Status();
unsigned char _DUI_Get_HW_DSG_Signal_Status();
void _DUI_Updated_HW_CHG_DSG_Signal_Status();
#endif
// Input Signal Control GPIO peripheral : (section stop)
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////
// Timer (100ms)  : (section start)
void _DUI_InitTimerFunction();
void _DUI_Set_TimerFunction_Cmd(unsigned char enable);
void _DUI_Set_Interrupt_Timer_Calling_Function(unsigned char fun_index, void (*calling_fun)());
void _DUI_Remove_Interrupt_Timer_Calling_Function(unsigned char fun_index, void (*calling_fun)());
#if defined(System_Clock_Freq_8MHz)
void _DUI_Set_Fast_Interrupt_Timer_Calling_Function(unsigned char fun_index, void (*calling_fun)());
void _DUI_Remove_Fast_Interrupt_Timer_Calling_Function(unsigned char fun_index, void (*calling_fun)());
#endif
// Timer (100ms)  : (section stop)
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// ADC Function Data Getting  : (section start)
//
//below define Vars refer to Device ADC Config
#define IDSG_CHANNEL_INDEX      0
#define ICHG_CHANNEL_INDEX      1
#define VBAT_CHANNEL_INDEX      2
#define NTC1_CHANNEL_INDEX      3
#define NTC2_CHANNEL_INDEX      4
#define Vref_CHANNEL_INDEX      5
void _DUI_InitADCFunction();
void _DUI_Disable_ADCFunction();
void _DUI_ADC_Channels_Scan();
unsigned int _DUI_Get_ADC_Channel_Values(unsigned int ChannelNum);
unsigned int _DUI_Get_Vref_mVoltage();
// ADC Function Data Getting  : (section stop)
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// EEPROM  : (section start)	
void _DUI_EEPROM_Access_Enable();
void _DUI_EEPROM_Access_Disable();
unsigned char _DUI_EEPROM_WriteByte(unsigned int Address_Offset, unsigned char Data);
unsigned char _DUI_EEPROM_WriteDoubleWord(unsigned int Address_Offset, unsigned long Data);
// EEPROM  : (section stop)	
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// UART  : (section start)	
enum For_Send_One_Wire_Data_Step  //unsigned char
{
    Sending_SysInfor,
    Sending_EEPROMInfor,
    Sending_PNInfor,
    Sending_Empty_Delay,
    Sending_Last_Step
};
void _DUI_Communication_Enable();
void _DUI_Communication_Disable();
unsigned char _DUI_Get_Communication_Pin_Interrupt_Received();

void _DUI_Communication_RX_Interrupt_Set(unsigned char enable);
void _DUI_One_Wire_Send_Word_CRC16(unsigned int *sendData, unsigned int length);
void _DUI_One_Wire_Send_Bytes_CRC16(unsigned char *sendData, unsigned int length);

void _DUI_Communication_Send_Bytes(unsigned char *sendData, unsigned int length);

//void _DUI_Communication_Send_Word_CRC16(unsigned char RespondCmd,unsigned int *sendData, unsigned int length, unsigned char isAddPrecedingCode, unsigned char isAddEndCode);
//void _DUI_Communication_Send_Bytes_CRC16(unsigned char RespondCmd,unsigned char *sendData, unsigned int length,unsigned char isAddPrecedingCode, unsigned char isAddEndCode);
void _DUI_One_Wire_Send_EEPROM_DATA_CRC16();
void _DUI_One_Wire_Send_EEPROM_PN_INFO_DATA_CRC16();
void _DUI_Send_One_Wire_Information_Data_By_Step(unsigned char step);

//void _DUI_Communication_One_Wire_Send_EEPROM_64DATA_CRC(unsigned char SegmentNum);
void _DUI_ReceiveDataParsingBy_RX_FRAME_DONE_For_Polling();
void _DUI_Communication_Send_Word_CheckSum(unsigned char RespondCmd, unsigned int *sendData, unsigned int length, unsigned char isAddPrecedingCode, unsigned char isAddEndCode);
void _DUI_Communication_Send_Bytes_CheckSum(unsigned char RespondCmd, unsigned char *sendData, unsigned int length, unsigned char isAddPrecedingCode, unsigned char isAddEndCode);
void _DUI_Communication_Send_EEPROM_DATA_CheckSum(unsigned char RespondCmd, unsigned int sendStartAddress, unsigned int length);
// UART  : (section stop)	
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
// USB Output Power Signal Control setting  : (section start)
#define USB_OCP_Signal_Protection_Cycle_Debounce    (2)    //unit: 100ms, 2 = 200 ms
#define USB_OCP_Signal_Release_Cycle                (50)    //unit: 100ms, 100 = 1 sec
void _DUI_Init_USB_Output_Power_Signal_Control();
unsigned char _DUI_Get_USB_OCP_Signal_Status();
void _DUI_Set_USB_Power_Output(unsigned char enable);
void _DUI_USB_Power_Output_Control_Polling();
// USB Output Power Signal Control setting  : (section stop)
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Back Light Control setting  : (section start)
void Interrupt_Calling_BackLight_ButtonEvent_Press_Trigger();
void _DUI_Init_BackLight_Control();
unsigned char _DUI_Get_BackLight_ButtonStatus();
void _DUI_Set_BackLight_Output(unsigned char enable);
void _DUI_Set_BackLight_Button_Interrupt_Enable(unsigned char enable);
// Back Light Control setting  : (section stop)
////////////////////////////////////////////////////////////////////////
//==============================================================================
// Private functions
//==============================================================================