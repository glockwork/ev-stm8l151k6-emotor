
/**
  ******************************************************************************
  * @file    Driver_User_Interface.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   for user to calling and control Devices
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
#include "Protection_Polling_Func.h"
//#include "Config_Info\User_Define_Parser.h"
#include "Config_Info\System_Config_Info.h"
#include "SOC\Calculate_NTC_ADC_TO_TEMPERATURE.h"

//==============================================================================
// Global/Extern variables
//==============================================================================
//==============================================================================
// Extern functions
//==============================================================================
//extern unsigned int usMBCRC16( unsigned char * pucFrame, unsigned int usLen );
//extern unsigned int usCheckSum16( unsigned char * pucFrame, unsigned int usLen );
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
//unsigned char G_All_LED_Bits_Mask;
unsigned char Button_Interrupt_Counter;
//unsigned int USB_OCP_Signal_Protection_Cycle_Counter;
//unsigned int USB_OCP_Signal_Release_Cycle_Counter;

//unsigned char Communication_Receive_Calling_Index;
//
//unsigned char G_Communication_Array[CommunicationArray_Total_Bytes_Size];
//
//unsigned char G_Receiving_Buffer[ Receiving_Buffer_Total_Bytes_Size ];
//unsigned char Receiving_Data[Receiving_Buffer_Size ];
//unsigned int Communication_Receive_Temp_count;
//unsigned char Communication_Receive_Temp;
extern const unsigned char Sys_Flash_Control_Bit;

//==============================================================================
// Private function prototypes
//==============================================================================

//==============================================================================
// Private functions
//==============================================================================


////////////////////////////////////////////////////////////////////////
// System Clock Setup  : (section start)
void _DUI_System_Init_And_Clk_Setup(){
    //_Device_CLK_Config();
    _Device_CLK_Config_Switch_To_HSI_Clock_Source();
}
void _DUI_System_Clk_Switch_To_HSI(){
    _Device_CLK_Config_Switch_To_HSI_Clock_Source();
}
void _DUI_System_Clk_Switch_To_LSI(){
    _Device_CLK_Config_Switch_To_LSI_Clock_Source();
}
void _DUI_Enable_RTC_WakeUp(){
    _Device_RTC_Config();

    /* RTC will wake-up from (active) halt every 5 second */
    RTC_SetWakeUpCounter(RTC_WakeUp_Second_Times);
    RTC_WakeUpCmd(ENABLE);
}
void _DUI_Disable_RTC_WakeUp(){
    RTC_WakeUpCmd(DISABLE);
    _Device_Disable_RTC();
}
// System Clock Setup  : (section stop)
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Utility Functions  : (section start)
void _DUI_delay_cycles(unsigned long cycleCount){
    _Device_delay_cycles(cycleCount);
}
void _DUI_GPIO_LowPower_Config(){
    _Device_GPIO_LowPower_Config();
}

void _DUI_BootloaderCheck_To_Disable(){
    unsigned char b1,b2;
    b1 = *((unsigned char *)0x480b); //Bootloader1 check address
    b2 = *((unsigned char *)0x480c); //Bootloader2 check address
    if((b1 != 0) || (b2 != 0)){
        //////////////////////////////////////////////////
        // disable Bootloader1 and 2 Check
        _DUI_SetBootloaderCheck(Disable);
    }
}
void _DUI_SetBootloaderCheck(unsigned char enable){
    FLASH_Unlock(FLASH_MemType_Data);
    if(enable){
        //////////////////////////////////////////////////
        // enable Bootloader1 and 2
        FLASH_ProgramOptionByte(0x480b, 0x55);   //Bootloader1 Enable
        FLASH_ProgramOptionByte(0x480c, 0xaa);   //Bootloader2 Enable
        //FLASH_ProgramOptionByte(0x4800, 0x00);   //Read output protection
    }else{
        //////////////////////////////////////////////////
        // disable Bootloader1 and 2
        FLASH_ProgramOptionByte(0x480b, 0x00);   //Bootloader1 disable
        FLASH_ProgramOptionByte(0x480c, 0x00);   //Bootloader2 disable
        //FLASH_ProgramOptionByte(0x4800, 0x00);   //Read output protection
    }
    FLASH_Lock(FLASH_MemType_Data);
}
void _DUI_ReadOutProtection_Check_To_Enable(){
    unsigned char b1;
    b1 = *((unsigned char *)0x4800); //Read-out protection address
    if(b1 != 0){
        //////////////////////////////////////////////////
        // enable Read Out Protection
        _DUI_SetReadOutProtection(Enable);
        WWDG_SWReset();
    }
}

void _DUI_SetReadOutProtection(unsigned char enable){
    FLASH_Unlock(FLASH_MemType_Data);
    if(enable){
        //////////////////////////////////////////////////
        // enable Read-out protection
        FLASH_ProgramOptionByte(0x4800, 0x00);   //Read-out protection on
    }else{
        //////////////////////////////////////////////////
        // disable Read-out protection
        FLASH_ProgramOptionByte(0x4800, 0xAA);   //Read-out protection off
    }
    FLASH_Lock(FLASH_MemType_Data);
}
void _DUI_Set_System_Control_Bit_To_EEPROM(unsigned char setBits, unsigned char enable){
    unsigned char val;
    val = System_Control_Bit_EEPROM;
    if(enable){
        //set
        val |= setBits;
    }else{
        //reset
        val &= ~setBits;
        //val = val & System_Control_Bit_EEPROM;
    }
    FLASH_Unlock(FLASH_MemType_Data);

    /* Program byte at the address */
    FLASH_ProgramByte( CONFIG_SEGMENT + System_Control_Bit_EEPROM_Offset, val);

    FLASH_Lock(FLASH_MemType_Data);
}

//void _DUI_Set_Mask_Control_Bit_To_Code_Flash(unsigned char setMaskBits, unsigned char enable){
//    unsigned long address_val;
//    unsigned char val;
//    //unsigned long address_val;
//    FLASH_Lock(FLASH_MemType_Data);
//    _DUI_delay_cycles(1000);     //1000 = 5.3ms at CCLK=8MHz.
//    val = Sys_Flash_Control_Bit;
//    if(enable){
//        //clear bit
//        val &= ~setMaskBits;
//    }
//    address_val = (uint32_t)&Sys_Flash_Control_Bit;
//    FLASH_SetProgrammingTime(FLASH_ProgramTime_Standard);
//    FLASH_Unlock(FLASH_MemType_Program);
//    _DUI_delay_cycles(1000);     //1000 = 5.3ms at CCLK=8MHz.
//
//    FLASH_EraseByte(0x91e6);
//    /* Program byte at the address */
//    FLASH_ProgramByte( 0x91e6, 0x12);
//    FLASH_WaitForLastOperation(FLASH_MemType_Program);
//
//    FLASH_Lock(FLASH_MemType_Program);
//}
// Utility Functions  : (section stop)
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// LED function  : (section start)
void _DUI_InitLEDDisplay(){
    //_Device_Set_Led_PWM_Enable(DeviceOff);
    _Device_Set_Led_PWM_Channel_Bits_Enable(0);
    _Device_Init_Led_Function();
}
#if (_USE_TOUCH_KEY_WITH_LED_ == 1)
void _DUI_Initial_Touch_Key_Led(){
    _Device_Init_TOUCH_KEY_Led_Function();
}
void _DUI_Set_Touch_Key_Led(unsigned char Device_Enable){
    _Device_Set_TOUCH_KEY_Led_OnOff(Device_Enable);
}
void _DUI_Set_Touch_Key_Led_Blinking(unsigned char Device_Enable){
    _Device_Set_TOUCH_KEY_LED_Blinking(Device_Enable);
}
#endif

void _DUI_LED_Flashing_Directly(){
    unsigned char i;
    _Device_Init_Led_Function();
    for( i = 0; i < 10; i++){
#if SYSTEM_NUM_OF_LED == 3
        _Device_Set_Led_OnOff_By_BITs(LED1_BIT | LED2_BIT | LED3_BIT );
#elif   SYSTEM_NUM_OF_LED == 4
        _Device_Set_Led_OnOff_By_BITs(LED1_BIT | LED2_BIT | LED3_BIT | LED4_BIT );
#else
        _Device_Set_Led_OnOff_By_BITs(LED1_BIT | LED2_BIT | LED3_BIT | LED4_BIT | LED5_BIT);
#endif
        _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
        _DUI_delay_cycles(10000);    //100 = 1ms at CCLK=4MHz. 10000 = 100ms
        _Device_Set_Led_OnOff_By_BITs(0);
        _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
        _DUI_delay_cycles(10000);    //100 = 1ms at CCLK=4MHz. 10000 = 100ms
    }
    _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
}
void _DUI_LED_TurnOff_serially(){
    unsigned char j;
    unsigned char LED_Bits;

    LED_Bits = 0;
#if SYSTEM_NUM_OF_LED == 3
        LED_Bits = (LED1_BIT | LED2_BIT | LED3_BIT );
#elif   SYSTEM_NUM_OF_LED == 4
        LED_Bits = (LED1_BIT | LED2_BIT | LED3_BIT | LED4_BIT );
#else
        LED_Bits = (LED1_BIT | LED2_BIT | LED3_BIT | LED4_BIT | LED5_BIT);
#endif

    _Device_Init_Led_Function();
    do{
        _Device_Set_Led_OnOff_By_BITs( LED_Bits );
        LED_Bits = LED_Bits >> 1;
        for(j = 0; j < 3; j++){
            _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
            _DUI_delay_cycles(10000);    //100 = 1ms at CCLK=4MHz. 10000 = 100ms
        }
        for(j = 0; j < 3; j++){
            _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
            _DUI_delay_cycles(10000);    //100 = 1ms at CCLK=4MHz. 10000 = 100ms
        }
    }while(LED_Bits != 0);
    _Device_Set_Led_OnOff_By_BITs( LED_Bits );
    _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
}

// LED function  : (section end)
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
// MosFet control  : (section start)
void _DUI_InitMosControl(){
    G_Device_Interface_Status &= ~CHG_MOSFET_STATUS;
    G_Device_Interface_Status &= ~DSG_MOSFET_STATUS;
    _Device_Mos_Control_Init();
#if (_DSG_Mos_Control_Reversed_Lo_Turn_ON_ == 1)
    _DUI_Set_DSG_MosFET(DeviceOff);
#endif
#if (_CHG_Mos_Control_Reversed_Lo_Turn_ON_ == 1)
    _DUI_Set_CHG_MosFET(DeviceOff);
#endif
}
#if (_DSG_Mos_Control_Reversed_Lo_Turn_ON_ == 1)
void _DUI_Set_DSG_MosFET(unsigned char enable){
    if(enable == DeviceOn){
        _Device_DSG_MosFET_Pin_Low();
        G_Device_Interface_Status |= (DSG_MOSFET_STATUS);
    }else{
        _Device_DSG_MosFET_Pin_High();
        G_Device_Interface_Status &= ~(DSG_MOSFET_STATUS);
    }
}
#else
void _DUI_Set_DSG_MosFET(unsigned char enable){
    if(enable == DeviceOn){
        _Device_DSG_MosFET_Pin_High();
        G_Device_Interface_Status |= (DSG_MOSFET_STATUS);
    }else{
        _Device_DSG_MosFET_Pin_Low();
        G_Device_Interface_Status &= ~(DSG_MOSFET_STATUS);
    }
}
#endif
#if (_CHG_Mos_Control_Reversed_Lo_Turn_ON_ == 1)
void _DUI_Set_CHG_MosFET(unsigned char enable){
    if(enable == DeviceOn){
        _Device_CHG_MosFET_Pin_Low();
        G_Device_Interface_Status |= (CHG_MOSFET_STATUS);
    }else{
        _Device_CHG_MosFET_Pin_High();
        G_Device_Interface_Status &= ~(CHG_MOSFET_STATUS);
    }
}
#else
void _DUI_Set_CHG_MosFET(unsigned char enable){
    if(enable == DeviceOn){
        _Device_CHG_MosFET_Pin_High();
        G_Device_Interface_Status |= (CHG_MOSFET_STATUS);
    }else{
        _Device_CHG_MosFET_Pin_Low();
        G_Device_Interface_Status &= ~(CHG_MOSFET_STATUS);
    }
}
#endif

// MosFet control  : (section stop)
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Button control  : (section start)
void Interrupt_Calling_ButtonEvent_Press_Trigger(){
    //test_high();

    G_Add_Module_Function_Status |= BUTTON_PRESS;
    if(G_Add_Module_Function_Status & ENABLE_MULTI_CLICK_COUNTER){
        Button_Interrupt_Counter++;
        if(Button_Interrupt_Counter >= COMPLETE_MULTI_CLICK_PRESS_TIMES){
            G_Add_Module_Function_Status |= BUTTON_COMPLETE_MULTI_CLICK;
            G_Add_Module_Function_Status &= ~ENABLE_MULTI_CLICK_COUNTER;
            Button_Interrupt_Counter = 0;
        }
    }else{
        G_Add_Module_Function_Status |= ENABLE_MULTI_CLICK_COUNTER;
        Button_Interrupt_Counter = 1;
    }

    //test_low();
}
void _DUI_InitButtonEvent(){
    G_Add_Module_Function_Status &= ~BUTTON_PRESS;
    _Device_Button_Config();
    Button_Interrupt_Counter = 0;
    _Device_Set_Interrupt_ButtonEvent_Press_Trigger_Function(Interrupt_Calling_ButtonEvent_Press_Trigger);
}
unsigned char _DUI_GetButtonStatus(){
    if(_Device_Get_Button_Status() == ButtonRelease){
        return ButtonRelease;
    }else{
        return ButtonPress;
    }
}
// Button control  : (section stop)
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// Optput Signal Control GPIO peripheral : (section start)
// OneWireControl/UartIsolationControl/NTC_Control/Adapter SOC
void _DUI_InitOutputSignals(){
    _Device_AdapterSOCControl_Pin_Low();
    G_Device_Interface_Status &= ~ADP_SOC_STATUS;

    _Device_OneWireControl_Pin_Low();
    G_Device_Interface_Status &= ~ONE_WIRE_ENABLE_STATUS;

    _Device_UartIsolationControl_Pin_Low();
    G_Device_Interface_Status &= ~UART_ISOLATE_ENABLE_STATUS;

    _Device_NTC_Control_Pin_Low();
    G_Device_Interface_Status &= ~NTC_ENABLE_STATUS;
}
void _DUI_Set_Adapter_SOC(unsigned char enable){
    if(enable == DeviceOn){
        _Device_AdapterSOCControl_Pin_High();
        G_Device_Interface_Status |= ADP_SOC_STATUS;
    }else{
        _Device_AdapterSOCControl_Pin_Low();
        G_Device_Interface_Status &= ~ADP_SOC_STATUS;
    }
}
void _DUI_Set_OneWire_Communication_Enable(unsigned char enable){
    if(enable == DeviceOn){
        _Device_OneWireControl_Pin_High();
        G_Device_Interface_Status |= ONE_WIRE_ENABLE_STATUS;
    }else{
        _Device_OneWireControl_Pin_Low();
        G_Device_Interface_Status &= ~ONE_WIRE_ENABLE_STATUS;
    }
}
void _DUI_Set_Uart_Isolation_Enable(unsigned char enable){
#if defined(_USE_UART_PORT_MAPPING_)
    if(enable == DeviceOn){
        _Device_UartIsolationControl_Pin_High();
        G_Device_Interface_Status |= UART_ISOLATE_ENABLE_STATUS;
    }else{
        _Device_UartIsolationControl_Pin_Low();
        G_Device_Interface_Status &= ~UART_ISOLATE_ENABLE_STATUS;
    }
#elif defined(_USE_UART_PORT_WITHOUT_MAPPING_)
    if(enable == DeviceOn){
        _Device_UartIsolationControl_Pin_Low();
        G_Device_Interface_Status |= UART_ISOLATE_ENABLE_STATUS;
    }else{
        _Device_UartIsolationControl_Pin_High();
        G_Device_Interface_Status &= ~UART_ISOLATE_ENABLE_STATUS;
    }
#else
    #error "Please select Use Usart_Port_Mapping 0(disable)/1(enable)"
#endif
}
void _DUI_Set_NTC_Detect_Control_Enable(unsigned char enable){
    if(enable == DeviceOn){
        _Device_NTC_Control_Pin_High();
        G_Device_Interface_Status |= NTC_ENABLE_STATUS;
    }else{
        _Device_NTC_Control_Pin_Low();
        G_Device_Interface_Status &= ~NTC_ENABLE_STATUS;
    }
}
// Optput Signal Control GPIO peripheral : (section stop)
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// Input Signal Control GPIO peripheral : (section start)
//
void _DUI_InitInputSignals(){
#if (_ENABLE_FOR_Monitoring_HW_PIC_STATUS_ == 1)
    _Device_InputSignalControl_Init();
    G_Device_Interface_Status &= ~HW_CHG_Status;
    G_Device_Interface_Status &= ~HW_DSG_Status;
#endif
}
#if (_ENABLE_FOR_Monitoring_HW_PIC_STATUS_ == 1)
unsigned char _DUI_Get_HW_CHG_Signal_Status(){
    return _Device_Get_HW_CHG_Status();
}
unsigned char _DUI_Get_HW_DSG_Signal_Status(){
    return _Device_Get_HW_DSG_Status();
}
void _DUI_Updated_HW_CHG_DSG_Signal_Status(){
    if(_Device_Get_HW_CHG_Status() == DeviceOn){
        G_Device_Interface_Status |= HW_CHG_Status;
    }else{
        G_Device_Interface_Status &= ~HW_CHG_Status;
    }
    if(_Device_Get_HW_DSG_Status() == DeviceOn){
        G_Device_Interface_Status |= HW_DSG_Status;
    }else{
        G_Device_Interface_Status &= ~HW_DSG_Status;
    }
}
#endif
// Input Signal Control GPIO peripheral : (section stop)
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// Timer (100ms)  : (section start)
void _DUI_InitTimerFunction(){
    _Device_Timer3_Init();
    _Device_Timer4_Init();
    G_Device_Interface_Status &= ~POLLING_TIMER_ENABLE_STATUS;
}
void _DUI_Set_TimerFunction_Cmd(unsigned char enable){
    if(enable == DeviceOn){
        _Device_Setting_Timer3_Enable(DeviceOn);
        G_Device_Interface_Status |= POLLING_TIMER_ENABLE_STATUS;
    }else{
        _Device_Setting_Timer3_Enable(DeviceOff);
        G_Device_Interface_Status &= ~POLLING_TIMER_ENABLE_STATUS;
    }
}
void _DUI_Set_Interrupt_Timer_Calling_Function(unsigned char fun_index, void (*calling_fun)()){
    _Device_Set_Timer3_Interrupt_Timer_Calling_Function(fun_index, calling_fun);
}
void _DUI_Remove_Interrupt_Timer_Calling_Function(unsigned char fun_index, void (*calling_fun)()){
    _Device_Remove_Timer3_Interrupt_Timer_Calling_Function(fun_index);
}

#if defined(System_Clock_Freq_8MHz)
void _DUI_Set_Fast_Interrupt_Timer_Calling_Function(unsigned char fun_index, void (*calling_fun)()){
    _Device_Set_Timer3_Fast_Interrupt_Timer_Calling_Function(fun_index, calling_fun);
}
void _DUI_Remove_Fast_Interrupt_Timer_Calling_Function(unsigned char fun_index, void (*calling_fun)()){
    _Device_Remove_Timer3_Fast_Interrupt_Timer_Calling_Function(fun_index);
}

#endif
// Timer (100ms)  : (section stop)
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// ADC Function Data Getting  : (section start)
void _DUI_InitADCFunction(){
    G_Device_Interface_Status &= ~ADC_CONVERSION;
    _Device_ADC_Config_Init();

    _DUI_Set_NTC_Detect_Control_Enable(DeviceOn);

}
void _DUI_Disable_ADCFunction(){
    G_Device_Interface_Status &= ~ADC_CONVERSION;
    _DUI_Set_NTC_Detect_Control_Enable(DeviceOff);
    _Device_ADC_Config_Init();
}

void _DUI_ADC_Channels_Scan(){
    G_Device_Interface_Status |= ADC_CONVERSION;
    _Device_ADC_Config_All_Channel_Scan();
    G_Device_Interface_Status &= ~ADC_CONVERSION;
}
unsigned int _DUI_Get_ADC_Channel_Values(unsigned int ChannelNum){
    return _Device_Get_ADC_Channel_Buffer(ChannelNum);
}
unsigned int _DUI_Get_Vref_mVoltage(){
    return _Device_Get_VRef_mVoltage();
}
// ADC Function Data Getting  : (section stop)
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// EEPROM  : (section start)	
void _DUI_EEPROM_Access_Enable(){
    _Device_EEPROM_Access_Enable();
}
void _DUI_EEPROM_Access_Disable(){
    _Device_EEPROM_Access_Disable();
}
unsigned char _DUI_EEPROM_WriteByte(unsigned int Address_Offset, unsigned char Data){
    return _Device_EEPROM_WriteByte(CONFIG_SEGMENT + Address_Offset, Data);
}
unsigned char _DUI_EEPROM_WriteDoubleWord(unsigned int Address_Offset, unsigned long Data){
    return _Device_EEPROM_WriteDoubleWord(CONFIG_SEGMENT + Address_Offset, Data);
}

// EEPROM  : (section stop)	
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// USB Output Power Signal Control setting  : (section start)
void _DUI_Init_USB_Output_Power_Signal_Control(){
    G_Add_Module_Function_Status &= ~ENABLE_USB_POWER_OUTPUT;
    G_Add_Module_Function_Status &= ~OCP_FOR_USB_POWER_OUTPUT;
    _Device_UsbOutputPowerSignalControl_Init();
    _DUI_Set_USB_Power_Output(DeviceOff);
    //USB_OCP_Signal_Release_Cycle_Counter = 0;
    //USB_OCP_Signal_Protection_Cycle_Counter = 0;
}
unsigned char _DUI_Get_USB_OCP_Signal_Status(){
    if(_Device_Get_USB_OCP_Signal_Status() == USB_Output_Power_Normal){
        return USB_Output_Power_Normal;
    }else{
        return USB_Output_Power_OCP;
    }
}
void _DUI_Set_USB_Power_Output(unsigned char enable){
    if(enable == DeviceOn){
        _Device_USB_OutputPower_ONOFF_Signal_Pin_High();
        G_Add_Module_Function_Status |= ENABLE_USB_POWER_OUTPUT;
    }else{
        _Device_USB_OutputPower_ONOFF_Signal_Pin_Low();
        G_Add_Module_Function_Status &= ~ENABLE_USB_POWER_OUTPUT;
    }
}

#if 0   //move to protecting polling
void _DUI_USB_Power_Output_Control_Polling(){

    if((( G_Add_Module_Function_Status & OCP_FOR_USB_POWER_OUTPUT)==0) && (_DUI_Get_USB_OCP_Signal_Status() == USB_Output_Power_OCP)){
        USB_OCP_Signal_Protection_Cycle_Counter++;
        if(USB_OCP_Signal_Protection_Cycle_Counter >= USB_OCP_Signal_Protection_Cycle_Debounce){
            G_Add_Module_Function_Status |= OCP_FOR_USB_POWER_OUTPUT;
            _DUI_Set_USB_Power_Output(DeviceOff);
            USB_OCP_Signal_Release_Cycle_Counter = 0;
            USB_OCP_Signal_Protection_Cycle_Counter = 0;
        }
    }else{
        USB_OCP_Signal_Protection_Cycle_Counter = 0;
    }
    if( G_Add_Module_Function_Status & OCP_FOR_USB_POWER_OUTPUT){
        USB_OCP_Signal_Release_Cycle_Counter++;
        if(USB_OCP_Signal_Release_Cycle_Counter >= USB_OCP_Signal_Release_Cycle){
            _DUI_Set_USB_Power_Output(DeviceOn);
            G_Add_Module_Function_Status &= ~OCP_FOR_USB_POWER_OUTPUT;
            USB_OCP_Signal_Release_Cycle_Counter = 0;
        }
    }
}
#endif
// USB Output Power Signal Control setting  : (section stop)
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Back Light Control setting  : (section start)
void Interrupt_Calling_BackLight_ButtonEvent_Press_Trigger(){
    //G_Device_Interface_Status |= BackLight_BUTTON_PRESS;

    // 1st press: BackLight_Constant_ON, 2nd press: BackLight_Blinking, 3th press: turn off Back light
//    if(((G_Device_Interface_Status & BackLight_Constant_ON) == 0) && ((G_Device_Interface_Status & BackLight_Blinking) == 0)){
//        G_Device_Interface_Status |= BackLight_Constant_ON;
//        G_Device_Interface_Status &= ~BackLight_Blinking;
//    }else if(((G_Device_Interface_Status & BackLight_Blinking) == 0) && (G_Device_Interface_Status & BackLight_Constant_ON)){
//        G_Device_Interface_Status |= BackLight_Blinking;
//        G_Device_Interface_Status &= ~BackLight_Constant_ON;
//    }else{
//        G_Device_Interface_Status &= ~BackLight_Constant_ON;
//        G_Device_Interface_Status &= ~BackLight_Blinking;
//    }

    // 1st press: BackLight_Blinking, 2nd press: BackLight_Constant_ON, 3th press: turn off Back light
    if(((G_Device_Interface_Status & BackLight_Constant_ON) == 0) && ((G_Device_Interface_Status & BackLight_Blinking) == 0)){
        G_Device_Interface_Status |= BackLight_Blinking;
        G_Device_Interface_Status &= ~BackLight_Constant_ON;
    }else if(((G_Device_Interface_Status & BackLight_Constant_ON) == 0) && (G_Device_Interface_Status & BackLight_Blinking)){
        G_Device_Interface_Status |= BackLight_Constant_ON;
        G_Device_Interface_Status &= ~BackLight_Blinking;
    }else{
        G_Device_Interface_Status &= ~BackLight_Constant_ON;
        G_Device_Interface_Status &= ~BackLight_Blinking;
    }
}
void _DUI_Init_BackLight_Control(){
    G_Device_Interface_Status &= ~BackLight_BUTTON_PRESS;
    G_Device_Interface_Status &= ~BackLight_BUTTON_CLICK;
    G_Device_Interface_Status &= ~BackLight_Constant_ON;
    G_Device_Interface_Status &= ~BackLight_Blinking;
    G_Device_Interface_Status &= ~BackLight_LED_OnOff_Status;
    _Device_BackLightControl_Init();
    _Device_Set_Interrupt_BackLight_ButtonEvent_Press_Trigger_Function(Interrupt_Calling_BackLight_ButtonEvent_Press_Trigger);
}

unsigned char _DUI_Get_BackLight_ButtonStatus(){
    if(_Device_Get_BackLight_Button_Status() == ButtonRelease){
        return ButtonRelease;
    }else{
        return ButtonPress;
    }
}

void _DUI_Set_BackLight_Output(unsigned char enable){
    if(enable == DeviceOn){
        _Device_BackLight_SignalOutput_Pin_High();
        G_Device_Interface_Status |= BackLight_LED_OnOff_Status;
    }else{
        _Device_BackLight_SignalOutput_Pin_Low();
        G_Device_Interface_Status &= ~BackLight_LED_OnOff_Status;
    }
}
void _DUI_Set_BackLight_Button_Interrupt_Enable(unsigned char enable){
    _Device_Set_BackLight_Button_Interrupt_Enable(enable);
}

// Back Light Control setting  : (section stop)
////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//// Uart2  : (section start)	
////
////Baud rate : 9600
////=======Receiving Data Structure===============================
////typedef struct{
////    static char cStart = 0X3A;	//起始字元
////    unsigned char 0X16;		    //Slave Address
////    unsigned char Command;		//命令
////    unsigned char LenExpected;	//數據長度
////    unsigned char DataBuf[DATA_BUF_NUM];//數據內容
////    unsigned char LRCDataLow;	    //checkSum with slave Low byte
////    unsigned char LRCDataHigh;	//checkSum with slave High byte
////    static char cEND1= 0X0D;	//結束字元 1
////    static char cEND1= 0X0A;	//結束字元 2
////} LEV Protocol Packet;
////
////========Transmiting Data Structure===========================
////typedef struct{
////    static char cStart = 0X3A;	//起始字元
////    unsigned char 0X16;		//Slave Address
////    unsigned char Command;		//應回應的命令
////    unsigned char LenExpected;	//數據長度
////    unsigned char DataBuf[DATA_BUF_NUM];//數據內容
////    unsigned char LRCDataLow;	    //checkSum with slave Low byte
////    unsigned char LRCDataHigh;	//checkSum with slave High byte
////    static char cEND1= 0X0D;	//結束字元 1
////    static char cEND1= 0X0A;	//結束字元 2
////} LEV Protocol Packet;
////
//////=========Transmiting Accept Respond Structure ( No used )===================================================================
////typedef struct{
////    static char cStart = 0X3A;	//起始字元
////    unsigned char 0X16;		//Slave Address
////    unsigned char Respond_Accept_Check_Code = 0x80; //Accept 碼
////    unsigned char LenExpected = 1;	//數據長度
////    unsigned char Command;		//應回應的命令
////    unsigned char LRCDataLow;	    //checkSum with slave Low byte
////    unsigned char LRCDataHigh;	//checkSum with slave High byte
////    static char cEND1= 0X0D;	//結束字元 1
////    static char cEND1= 0X0A;	//結束字元 2
////} LEV Protocol Packet;
////
////=========Transmiting Error-Respond Structure ( No used )===================================================================
////typedef struct{
////    static char cStart = 0X3A;	//起始字元
////    unsigned char 0X16;		//Slave Address
////    unsigned char Respond_Error_Check_Code = 0x83; //錯誤碼
////    unsigned char LenExpected = 1;	//數據長度
////    unsigned char Command;		//應回應的命令
////    unsigned char LRCDataLow;	    //checkSum with slave Low byte
////    unsigned char LRCDataHigh;	//checkSum with slave High byte
////    static char cEND1= 0X0D;	//結束字元 1
////    static char cEND1= 0X0A;	//結束字元 2
////} LEV Protocol Packet;
////
////========One Wire Transmiting Data Structure=======================================================
////typedef struct{
////    static uint cStart1 = 0x80f8;	//起始字元 // send High byte first, then send Low byte second.
////    static uint cStart2 = 0x80A0;	//function字元 // send High byte first, then send Low byte second.
////                                    // 0x80A0 : data 資料,
////                                    // 0x80D0 ~ 0x80DF : EEPROM Seg 0 ~ 15 (a segment = 64 bytes),
////    unsigned int LenExpected;//數據長度 ; send High byte first, then send Low byte second.
////    unsigned char DataBuf[LenExpected];//數據內容
////    unsigned char LRCDataHigh;	//CRC or checkSum High byte, calculating only for DataBuf
////    unsigned char LRCDataLow;	//CRC or checkSum Low byte, calculating only for DataBuf
////    static uint cEND1= 0x70f7;	//結束字組 1 // send High byte first, then send Low byte second.
////    static uint cEND1= 0x70f7;	//結束字組 2 // send High byte first, then send Low byte second.
////} ModbusProtocolPacket;//RTU mode
////========One Wire Transmiting EEPROM Data Structure=======================================================
////typedef struct{
////    static uint cStart1 = 0x80f8;	//起始字元 // send High byte first, then send Low byte second.
////    static uint cStart2 = 0x80D0;	//function字元 // send High byte first, then send Low byte second.
////    unsigned char DataBuf[];//數據內容
////    unsigned char LRCDataHigh;	//CRC or checkSum High byte, calculating only for DataBuf
////    unsigned char LRCDataLow;	//CRC or checkSum Low byte, calculating only for DataBuf
////    static uint cEND1= 0x70f7;	//結束字組 1 // send High byte first, then send Low byte second.
////    static uint cEND1= 0x70f7;	//結束字組 2 // send High byte first, then send Low byte second.
////} ModbusProtocolPacket;//RTU mode
////
//#define LeadingCode                 (0x3A)
//#define SlaveAddressCode            (0x16)
//#define EndCode1                    (0x0D)
//#define EndCode2                    (0x0A)
//#define Respond_Error_Check_Code    (0xF3)
//#define Respond_Accept_Check_Code   (0xF0)
//
//#define ONE_WIRE_PrecedingCheckCode         (0x80f8)
//#define ONE_WIRE_Data_PrecedingCode         (0x80A0)
//#define ONE_WIRE_EEPROM_Seg_PrecedingCode   (0x80D0)
//#define ONE_WIRE_EndCheckCode               (0x70f7)
//
//
//#define UratRXFrameInternalGapTime	    20  // unit: ms
//#define _RX_IT_Reset_Polling_Cycles_    50  // cycle
//
//unsigned int Reset_RX_IT_Cycle_Count;
//unsigned int Receive_Internal_Gap_Time_Count;
//
//unsigned char Receive_First_Index;  //0x3A
//unsigned char Receive_End_Index;  //0x0A
//unsigned char Receive_Cmd;  //
//unsigned char Receive_DATA_Length;  //
//unsigned char Receiving_Data_Array[ Receiving_Buffer_Size ];
//
//
//
//unsigned char ReceiveDataParsingPacketAndCheck(){
//    unsigned char last_idx;
//    unsigned char i, length;
//    unsigned int chkSum;
//    unsigned char chkSum_hi, chkSum_lo;
//    unsigned char CheckFlag;
//
//    last_idx = Communication_Receive_Calling_Index - 1;
//
//    CheckFlag = false;
//
//    G_Extend_Device_Interface_Status &= ~UART_RX_PrecedingCode_Find;
//    G_Extend_Device_Interface_Status &= ~UART_RX_EndingCode_Find;
//    G_Extend_Device_Interface_Status &= ~UART_RX_FRAME_DONE;
//    G_Extend_Device_Interface_Status &= ~UART_RX_FRAME_ADDRESS_FAIL;
//
//    //check ending codes and Preceding Codes, if it's match.
//    Receive_End_Index = 0;
//    for(i = last_idx; i > 0; i--){
//        if((G_Receiving_Buffer[i] == EndCode2) && (G_Receiving_Buffer[i - 1] == EndCode1)){
//            G_Extend_Device_Interface_Status |= UART_RX_EndingCode_Find;
//            Receive_End_Index = i;
//            break;
//        }
//    }
//    Receive_First_Index =0;
//    for(i = 0; i < Receive_End_Index; i++){
//        if((G_Receiving_Buffer[i] == LeadingCode) && (G_Receiving_Buffer[i+1] == SlaveAddressCode)){
//            G_Extend_Device_Interface_Status |= UART_RX_PrecedingCode_Find;
//            Receive_First_Index = i;
//            break;
//        }
//    }
//
//    //if find receiving packet, calculate chech sum.
//    //and transfer data to Arrays
//    if( (G_Extend_Device_Interface_Status & UART_RX_EndingCode_Find) &&
//        (G_Extend_Device_Interface_Status & UART_RX_PrecedingCode_Find) &&
//        (Receive_End_Index > Receive_First_Index)){
//
//        length = Receive_End_Index - Receive_First_Index - 4; // length include slaveAdd, DataLength byte, Data bytes
//        if( length > 0){
//            chkSum = usCheckSum16( &(G_Receiving_Buffer[1]), length );
//            chkSum_hi = chkSum >> 8;
//            chkSum_lo = chkSum & 0x00ff;
//            if((chkSum_hi == G_Receiving_Buffer[Receive_End_Index - 2]) && (chkSum_lo == G_Receiving_Buffer[Receive_End_Index - 3])){
//                Receive_Cmd = G_Receiving_Buffer[Receive_First_Index + 2];
//                Receive_DATA_Length = G_Receiving_Buffer[Receive_First_Index + 3];
//                i = Receive_First_Index + 3; // data length index
//                last_idx = Receive_End_Index - 4;// last data index without checkSum
//                last_idx = last_idx - i; // Really Data Length
//                if((Receive_DATA_Length <= Receiving_Buffer_Size)&&(last_idx == Receive_DATA_Length)){
//                    for(i=0; i< Receive_DATA_Length; i++){
//                        Receiving_Data_Array[i] = G_Receiving_Buffer[Receive_First_Index + 4 + i];
//                    }
//                    CheckFlag = true;
//                }
//            }
//        }//if( length > 0){
//    }
//
//
////    //clear Receiving Buffer
////    for(i = 0; i < Communication_Receive_Calling_Index; i++){
////        G_Receiving_Buffer[i] = 0;
////    }
//    Communication_Receive_Calling_Index = 0;
//    if((G_Extend_Device_Interface_Status & UART_RX_PrecedingCode_Find) == 0){
//           G_Extend_Device_Interface_Status |= UART_RX_FRAME_ADDRESS_FAIL;
//       }
//
//    G_Extend_Device_Interface_Status &= ~UART_RX_PrecedingCode_Find;
//    G_Extend_Device_Interface_Status &= ~UART_RX_EndingCode_Find;
//
//    G_Extend_Device_Interface_Status |= UART_RX_FRAME_DONE;
//    if(CheckFlag){
//        G_Extend_Device_Interface_Status &= ~UART_RX_FRAME_PACKET_FAIL;
//        for(i = 0; i < Communication_Receive_Calling_Index; i++){
//            G_Receiving_Buffer[i] = 0;
//        }
//        return true;
//    }else{
//        G_Extend_Device_Interface_Status |= UART_RX_FRAME_PACKET_FAIL;
//        for(i = 0; i < Communication_Receive_Calling_Index; i++){
//            G_Receiving_Buffer[i] = 0;
//        }
//        return false;
//    }
//}
//
//void Communication_Receive_Frame_Timer_Calling_Counter(){
//    Receive_Internal_Gap_Time_Count++;
//    if(Receive_Internal_Gap_Time_Count > UratRXFrameInternalGapTime){
//        //GPIO_HIGH(LED4_PORT, LED4_PIN);
//        _Device_Remove_Timer4_Interrupt_Timer_Calling_Function(2);
//        _DUI_Communication_RX_Interrupt_Set(DeviceOff);
//        ReceiveDataParsingPacketAndCheck();
//        //_DUI_Communication_RX_Interrupt_Set(DeviceOn);
//        //GPIO_LOW(LED4_PORT, LED4_PIN);
//    }
//}
//void Communication_Interrupt_Receive_Calling_Function_With_Timer(unsigned char receivedByte){
//            //GPIO_HIGH(LED3_PORT, LED3_PIN);
//
//    if(Communication_Receive_Calling_Index == 0){
//        Receive_Internal_Gap_Time_Count = 0;
//        _Device_Set_Timer4_Interrupt_Timer_Calling_Function_With_Delay_And_Exec(2, Communication_Receive_Frame_Timer_Calling_Counter, 1);
//    }
//    G_Receiving_Buffer[Communication_Receive_Calling_Index++] = receivedByte;
//    Receive_Internal_Gap_Time_Count = 0;
//    if(Communication_Receive_Calling_Index >= Receiving_Buffer_Total_Bytes_Size){
//        _Device_Remove_Timer4_Interrupt_Timer_Calling_Function(2);
//        _DUI_Communication_RX_Interrupt_Set(DeviceOff);
//        Communication_Receive_Calling_Index = Receiving_Buffer_Total_Bytes_Size - 1;
//        Receive_Internal_Gap_Time_Count = 0;
//        _Device_Set_Timer4_Interrupt_Timer_Calling_Function_With_Delay_And_Exec(2, Communication_Receive_Frame_Timer_Calling_Counter, 1);
//    }
//            //GPIO_LOW(LED3_PORT, LED3_PIN);
//}
//
//typedef void (*Function_ptr)( void );
//unsigned int g_uiTemp1;//, uiTemp2;
//void Communication_ReceiveDataParsing(){
//    unsigned int uiTemp1;//, uiTemp2;
//    //unsigned long ulTemp1;
//    float fTemp1;//, uiTemp2;
//    unsigned char Failure_Flag;
//
//    Failure_Flag = false;
//    //////////////////////////////////////
//    // Communication
//    switch(Receive_Cmd){
//
////////////////////////////////////////
//// Communication for user
////////////////////////////////////////
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // Calculation Temperature to 0.1K
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0x08;   Received_Byte[3] = Receive_DATA_Length = 1;
//        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
//        case 0x08:
//            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
//                uiTemp1 = Get_KelvinDegree_By_NTC_ADC(G_NTC1_ADC);
//                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // Calculation Current Hi word
//        // Calculation Voltage Hi word
//        // Calculation Avg Current Hi word
//        // Calculation Remaining Capacity Hi word
//        // Calculation Full Charge Capacity Hi word
//        // Cell Voltages Block 1
//        // Cell Voltages Block 2
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0x06;   Received_Byte[3] = Receive_DATA_Length = 1;
//        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
//        case 0x04:
//        case 0x06:
//        case 0x07:
//        case 0x1e:
//        case 0x1f:
//        case 0x24:
//        case 0x25:
//            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
//                uiTemp1 = 0;
//                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // Calculation Voltage Lo word
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0x09;   Received_Byte[3] = Receive_DATA_Length = 1;
//        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
//        case 0x09:
//            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
//                fTemp1 = VBAT_mV_To_ADC_Factor;
//                fTemp1 = G_VBAT_ADC / fTemp1;
//                uiTemp1 = (unsigned int)fTemp1;
//                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // Calculation Current Lo word
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0x0A;   Received_Byte[3] = Receive_DATA_Length = 1;
//        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
//        case 0x0A:
//            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
//                fTemp1 = DSG_mA_To_ADC_Factor;
//                fTemp1 = G_DSG_Current_ADC / fTemp1;
//                uiTemp1 = (unsigned int)fTemp1;
//                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // Calculation Average Current Lo word
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0x0B;   Received_Byte[3] = Receive_DATA_Length = 1;
//        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
//        case 0x0B:
//            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
//                fTemp1 = DSG_mA_To_ADC_Factor;
//                fTemp1 = G_AVG_DSG_Current_ADC / fTemp1;
//                uiTemp1 = (unsigned int)fTemp1;
//                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        //  Relative State Of Charge
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0x0D;   Received_Byte[3] = Receive_DATA_Length = 1;
//        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
//        case 0x0D:
//            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
//                if(g_uiTemp1 > 100){
//                    g_uiTemp1 = 0;
//                }else{
//                    g_uiTemp1++;
//                }
//                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &g_uiTemp1, 1, true, true);
////                uiTemp1 = 96;
////                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        //  Absolute State Of Charge
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0x0E;   Received_Byte[3] = Receive_DATA_Length = 1;
//        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
//        case 0x0E:
//            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
//                uiTemp1 = 96;
//                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        //  Absolute State Of Charge
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0x0F;   Received_Byte[3] = Receive_DATA_Length = 1;
//        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
//        case 0x0F:
//            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
//                uiTemp1 = 90;
//                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // Calculation Cycle_Count_RECORD word
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0x17;   Received_Byte[3] = Receive_DATA_Length = 1;
//        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
//        case 0x17:
//            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
//                uiTemp1 = G_Cycle_Count_RECORD;
//                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//
////////////////////////////////////////
//// Communication manufacture
////////////////////////////////////////
//        case 0xA0:
//            _Device_Uart_Send_Bytes(Receiving_Data_Array, Receive_DATA_Length);
//            break;
//
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // get mcu uid data
//        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
//        // Send_Bytes[2] = RespondCmd;  Send_Bytes[3] = data length;
//        // Send_Bytes[4 ~ (4 + length - 1 )] = UID 12 bytes Data
//        // Send_Bytes[last - 3] = CRC Hi;  Send_Bytes[Last - 2] = CRC Lo;
//        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
//        case 0xA1:
//            _Device_Uart_Send_Bytes((unsigned char *)Unique_ID_Registers_Address, Unique_ID_Registers_Length);
//            //_DUI_Communication_Send_Bytes_CRC16(0xA1, (unsigned char *)Unique_ID_Registers_Address, Unique_ID_Registers_Length, 1, 1);
//            break;
//
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // get mcu uid data
//        case 0xA2:
//            _DUI_Communication_Send_Bytes_CheckSum(Receive_Cmd, (unsigned char *)Unique_ID_Registers_Address, Unique_ID_Registers_Length, true, true);
//            break;
//        case 0xA3:
//
//            break;
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // get ALL ADC data
//        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
//        // Send_Bytes[2] = Receive_Cmd;  Send_Bytes[3] = data length;
//        // Send_Bytes[] = DSG_Current_ADC; Send_Bytes[] = CHG_Current_ADC; Send_Bytes[] = VBAT_ADC
//        // Send_Bytes[] = NTC1_ADC; Send_Bytes[] = NTC2_ADC; Send_Bytes[] = Vref_mVoltage
//        // Send_Bytes[] = Current_Capacity
//        // Send_Bytes[last - 3] = CheckSum Lo;  Send_Bytes[Last - 2] = CheckSum Hi;
//        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
//        case 0xA4:
//            _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, (&G_DSG_Current_ADC), 8, true, true);
//            break;
//
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // set One_Wire Enable by button
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // DSG_OP_ADC_OFFSET
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0xB0;   Received_Byte[3] = Receive_DATA_Length = 1;
//        // Received_Byte[4] = Enable Data (1 byte); 0= disable, 1 or more = enable; (Receiving_Data_Array[0])
//        case 0xB0:
//            if(Receive_DATA_Length == 1){
//                if(Receiving_Data_Array[0]){
//                    G_Add_Module_Function_Status |= ONE_WIRE_UART_SET_ENABLE;
//                }else{
//                    G_Add_Module_Function_Status &= ~ONE_WIRE_UART_SET_ENABLE;
//                }
//                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // set user data capacity
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // D
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0xB0;   Received_Byte[3] = Receive_DATA_Length = 1;
//        // Received_Byte[4] = capacity; (Receiving_Data_Array[0])
//        case 0xB1:
//            if(Receive_DATA_Length == 1){
//                G_Current_Capacity = Receiving_Data_Array[0];
//                G_Hold_Capacity = G_Current_Capacity;
//                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // set Calbriation data bytes
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // DSG_OP_ADC_OFFSET
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0xD0;   Received_Byte[3] = Receive_DATA_Length = 1;
//        // Received_Byte[4] = Offset Data (1 byte); (Receiving_Data_Array[0])
//        case 0xD0:
//            if(Receive_DATA_Length == 1){
//                uiTemp1 = DSG_OP_ADC_OFFSET_Offset + CONFIG_SEGMENT;
//                _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 0 ]);
//                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // set Calbriation data bytes
//        // CHG_OP_ADC_OFFSET
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0xD1;   Received_Byte[3] = Receive_DATA_Length = 1;
//        // Received_Byte[4] = Offset Data (1 byte); (Receiving_Data_Array[0])
//        case 0xD1:
//            if(Receive_DATA_Length == 1){
//                uiTemp1 = CHG_OP_ADC_OFFSET_Offset + CONFIG_SEGMENT;
//                _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 0 ]);
//                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // set Calbriation data bytes
//        // VBAT_ADC_OFFSET
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0xD2;   Received_Byte[3] = Receive_DATA_Length = 1;
//        // Received_Byte[4] = Offset Data (1 byte); (Receiving_Data_Array[0])
//        case 0xD2:
//            if(Receive_DATA_Length == 1){
//                uiTemp1 = VBAT_ADC_OFFSET_Offset + CONFIG_SEGMENT;
//                _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 0 ]);
//                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // set Calbriation data bytes
//        // NTC1_ADC_OFFSET
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0xD3;   Received_Byte[3] = Receive_DATA_Length = 1;
//        // Received_Byte[4] = Offset Data (1 byte); (Receiving_Data_Array[0])
//        case 0xD3:
//            if(Receive_DATA_Length == 1){
//                uiTemp1 = NTC1_ADC_OFFSET_Offset + CONFIG_SEGMENT;
//                _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 0 ]);
//                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // set Calbriation data bytes
//        // NTC2_ADC_OFFSET
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0xD4;   Received_Byte[3] = Receive_DATA_Length = 1;
//        // Received_Byte[4] = Offset Data (1 byte); (Receiving_Data_Array[0])
//        case 0xD4:
//            if(Receive_DATA_Length == 1){
//                uiTemp1 = NTC2_ADC_OFFSET_Offset + CONFIG_SEGMENT;
//                _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 0 ]);
//                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // set Calbriation data bytes
//        // SOC_ADC_OFFSET
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0xD5;   Received_Byte[3] = Receive_DATA_Length = 1;
//        // Received_Byte[4] = Offset Data (1 byte); (Receiving_Data_Array[0])
//        case 0xD5:
//            if(Receive_DATA_Length == 1){
//                uiTemp1 = SOC_ADC_OFFSET_Offset + CONFIG_SEGMENT;
//                _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 0 ]);
//                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // get EEPROM data bytes
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0xE0;   Received_Byte[3] = Receive_DATA_Length = 3;
//        // Received_Byte[4] = EEPROM Address Offset (Lo byte); (Receiving_Data_Array[0])
//        // Received_Byte[5] = EEPROM Address Offset (Hi byte); (Receiving_Data_Array[1])
//        // Received_Byte[6] = Get Data Length (1 byte);    (Receiving_Data_Array[2])
//        case 0xE0:
//            if(Receive_DATA_Length == 3){
//                uiTemp1 = Receiving_Data_Array[1];
//                uiTemp1 = (uiTemp1 << 8) + Receiving_Data_Array[0] + CONFIG_SEGMENT;
//                _DUI_Communication_Send_EEPROM_DATA_CheckSum( Receive_Cmd, uiTemp1, Receiving_Data_Array[2]);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // write EEPROM data one byte
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0xE1;   Received_Byte[3] = Receive_DATA_Length = 3;
//        // Received_Byte[4] = EEPROM Address Offset (Lo byte); (Receiving_Data_Array[0])
//        // Received_Byte[5] = EEPROM Address Offset (Hi byte); (Receiving_Data_Array[1])
//        // Received_Byte[6] = write Data(1 byte);              (Receiving_Data_Array[2])
//        case 0xE1:
//            if( Receive_DATA_Length ==  3){
//                uiTemp1 = Receiving_Data_Array[1];
//                uiTemp1 = (uiTemp1 << 8) + Receiving_Data_Array[0] + CONFIG_SEGMENT;
//                _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 2 ]);
//                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // write EEPROM data word (two bytes)
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0xE2;   Received_Byte[3] = Receive_DATA_Length = 4;
//        // Received_Byte[4] = EEPROM Address Offset (Lo byte); (Receiving_Data_Array[0])
//        // Received_Byte[5] = EEPROM Address Offset (Hi byte); (Receiving_Data_Array[1])
//        // Received_Byte[6] = write Data(1 byte)(Lo);              (Receiving_Data_Array[2])
//        // Received_Byte[7] = write Data(1 byte)(Hi);              (Receiving_Data_Array[3])
//        case 0xE2:
//            if( Receive_DATA_Length ==  4){
//                uiTemp1 = Receiving_Data_Array[1];
//                uiTemp1 = (uiTemp1 << 8) + Receiving_Data_Array[0] + CONFIG_SEGMENT;
//                _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 2 ]);
//                _Device_EEPROM_WriteByte(uiTemp1 + 1, Receiving_Data_Array[ 3 ]);
//                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // write EEPROM data two words (four bytes)
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0xE3;   Received_Byte[3] = Receive_DATA_Length = 6;
//        // Received_Byte[4] = EEPROM Address Offset (Lo byte); (Receiving_Data_Array[0])
//        // Received_Byte[5] = EEPROM Address Offset (Hi byte); (Receiving_Data_Array[1])
//        // Received_Byte[6] = write Data(1 byte)(Lo);          (Receiving_Data_Array[2])
//        // Received_Byte[7] = write Data(1 byte);              (Receiving_Data_Array[3])
//        // Received_Byte[8] = write Data(1 byte);              (Receiving_Data_Array[4])
//        // Received_Byte[9] = write Data(1 byte)(Hi);          (Receiving_Data_Array[5])
//        case 0xE3:
//            if( Receive_DATA_Length ==  6){
//                uiTemp1 = Receiving_Data_Array[1];
//                uiTemp1 = (uiTemp1 << 8) + Receiving_Data_Array[0] + CONFIG_SEGMENT;
////                ulTemp1 = Receiving_Data_Array[2];
////                ulTemp1 = (ulTemp1 << 8) + Receiving_Data_Array[3];
////                ulTemp1 = (ulTemp1 << 8) + Receiving_Data_Array[4];
////                ulTemp1 = (ulTemp1 << 8) + Receiving_Data_Array[5];
////                _Device_EEPROM_WriteDoubleWord(uiTemp1, ulTemp1);
//                _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 2 ]);
//                _Device_EEPROM_WriteByte(uiTemp1 + 1, Receiving_Data_Array[ 3 ]);
//                _Device_EEPROM_WriteByte(uiTemp1 + 2, Receiving_Data_Array[ 4 ]);
//                _Device_EEPROM_WriteByte(uiTemp1 + 3, Receiving_Data_Array[ 5 ]);
//
//                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//
//
//        case 0xF0:
//            //reserved for accept Codes
//            break;
//        case 0xF3:
//            //reserved for Error Codes
//            break;
//        ////////////////////////////////////////////////////
//        // reset system by commnuication
//        case 0xFA:
//            if((Receive_DATA_Length == 1) &&(Receiving_Data_Array[0] == 0xff)){
//                for(uiTemp1 = 0; uiTemp1 < 19; uiTemp1++){
//                    _DUI_delay_cycles(10000);     //100 = 1ms at CCLK=4MHz. 10000 = 100ms
//                    GPIO_TOGGLE(LED1_PORT, LED1_PIN);
//                }
//                GPIO_TOGGLE(LED2_PORT, LED2_PIN);
//                GPIO_TOGGLE(LED3_PORT, LED3_PIN);
//                _DUI_delay_cycles(10000);     //100 = 1ms at CCLK=4MHz. 10000 = 100ms
//                _DUI_delay_cycles(10000);     //100 = 1ms at CCLK=4MHz. 10000 = 100ms
//                WWDG_SWReset();
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//        ////////////////////////////////////////////////////////////////////////
//        // for updated F/W by communication
//        case 0xFB:
//            if((Receive_DATA_Length == 1) &&(Receiving_Data_Array[0] == 0xff)){
//                for(uiTemp1 = 0; uiTemp1 < 19; uiTemp1++){
//                    _DUI_delay_cycles(10000);     //100 = 1ms at CCLK=4MHz. 10000 = 100ms
//                    GPIO_TOGGLE(LED1_PORT, LED1_PIN);
//                }
//                GPIO_TOGGLE(LED2_PORT, LED2_PIN);
//                GPIO_TOGGLE(LED3_PORT, LED3_PIN);
//                //////////////////////////////////////////////////
//                // enable for updated Firmware
//                _DUI_Set_System_Control_Bit_To_EEPROM(SYS_UPDATED_FW , Enable);
//                _DUI_delay_cycles(10000);     //100 = 1ms at CCLK=4MHz. 10000 = 100ms
//                _DUI_delay_cycles(10000);     //100 = 1ms at CCLK=4MHz. 10000 = 100ms
//                WWDG_SWReset();
//            }else{
//                Failure_Flag = true;
//            }
//            break;
//
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // get Respond_Error_Check_Code
//        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
//        // Send_Bytes[2] = RespondCmd;  Send_Bytes[3] = data length;
//        // Send_Bytes[] = DSG_Current_ADC; Send_Bytes[] = CHG_Current_ADC; Send_Bytes[] = VBAT_ADC
//        // Send_Bytes[] = NTC1_ADC; Send_Bytes[] = NTC2_ADC; Send_Bytes[] = Vref_mVoltage
//        // Send_Bytes[] = Current_Capacity
//        // Send_Bytes[last - 3] = CRC Hi;  Send_Bytes[Last - 2] = CRC Lo;
//        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
//        default:
//            //receiveData[0] = Respond_Error_Check_Code;
//            //_DUI_Communication_Send_Bytes_CRC16(Respond_Error_Check_Code, receiveData, 1, 1, 1);
//            break;
//    }
//
//    if(Failure_Flag){
//        _DUI_Communication_Send_Bytes_CheckSum(Respond_Error_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
//    }
//    Receive_Cmd = 0;
//    Receive_DATA_Length = 0;
//}
//unsigned char FirstFindingCodeIndex;
//unsigned char LastFindingCodeIndex;
//void _DUI_ReceiveDataParsingBy_RX_FRAME_DONE_For_Polling(){
////    // if communication fail, reset it
////    if((G_Extend_Device_Interface_Status & UART_STATUS) && ((G_Extend_Device_Interface_Status & UART_RX_IT_STATUS)==0)){
////        Reset_RX_IT_Cycle_Count++;
////        if(Reset_RX_IT_Cycle_Count >= _RX_IT_Reset_Polling_Cycles_){
////            _DUI_Communication_Disable();
////            _DUI_Communication_Enable();
////        }
////    }else{
////        Reset_RX_IT_Cycle_Count = 0;
////    }
//
//    if((G_Extend_Device_Interface_Status & UART_RX_FRAME_DONE) == 0){
//        return;
//    }
//    G_Extend_Device_Interface_Status &= ~UART_RX_FRAME_DONE;
//    G_Extend_Device_Interface_Status &= ~UART_RX_PrecedingCode_Find;
//    G_Extend_Device_Interface_Status &= ~UART_RX_EndingCode_Find;
//    Communication_Receive_Calling_Index = 0;
//    if(G_Extend_Device_Interface_Status & UART_RX_FRAME_PACKET_FAIL){
//        G_Extend_Device_Interface_Status &= ~UART_RX_FRAME_PACKET_FAIL;
//        Receive_Cmd = 0;
//        if((G_Extend_Device_Interface_Status & UART_RX_FRAME_ADDRESS_FAIL)==0){
//            _DUI_Communication_Send_Bytes_CheckSum(Respond_Error_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
//        }
//        G_Extend_Device_Interface_Status &= ~UART_RX_FRAME_ADDRESS_FAIL;
//    }else{
//        Communication_ReceiveDataParsing();
//    }
//    _DUI_Communication_RX_Interrupt_Set(DeviceOn);
//}
//
//
//
//void _DUI_Communication_Enable(){
//    Communication_Receive_Calling_Index = 0;
//    Communication_Receive_Temp_count = 0;
//    Communication_Receive_Temp = 0;
//
//    Receive_Internal_Gap_Time_Count = 0;
//    Reset_RX_IT_Cycle_Count = 0;
//
//    _DUI_Set_Uart_Isolation_Enable(DeviceOn);
//    _Device_Uart_Enable();
//    _Device_Set_Uart_Interrupt_Receive_Calling_Function(Communication_Interrupt_Receive_Calling_Function_With_Timer);
//    //_Device_Set_Uart_Interrupt_Receive_Calling_Function(Communication_Interrupt_Receive_Calling_Function_With_LeadingCode);
//    G_Extend_Device_Interface_Status |= UART_RX_IT_STATUS;
//    G_Extend_Device_Interface_Status |= UART_STATUS;
//}
//void _DUI_Communication_Disable(){
//    _Device_Uart_Disable();
//    _DUI_Set_Uart_Isolation_Enable(DeviceOff);
//    G_Extend_Device_Interface_Status &= ~UART_STATUS;
//}
//void _DUI_Communication_RX_Interrupt_Set(unsigned char enable){
//    if(enable){
//        _Device_Set_Uart_RX_Interrupt(DeviceOn);
//        G_Extend_Device_Interface_Status |= UART_RX_IT_STATUS;
//    }else{
//        _Device_Set_Uart_RX_Interrupt(DeviceOff);
//        G_Extend_Device_Interface_Status &= ~UART_RX_IT_STATUS;
//    }
//}
//void _DUI_Communication_Send_Bytes(unsigned char *sendData, unsigned int length){
//	//unsigned int commLength;
//    int i;
//
//    if(length > CommunicationArray_Data_Bytes_Size){
//        return;
//    }
//	for(i = 0; i < length; i++){
//        G_Communication_Array[i] = sendData[i];
//    }
//    _Device_Uart_Send_Bytes( G_Communication_Array, length); // send high byte first, send low byte second
//
//}
//void _DUI_One_Wire_Send_Word_CRC16(unsigned int *sendData, unsigned int length){
//	unsigned int sendingLength, usCRC16;
//	unsigned int DataLength;
//    int i;
//
//    DataLength = length << 1;    // mul 2
//    if(DataLength > CommunicationArray_Data_Bytes_Size){
//        return;
//    }
//	for(i = 0; i < DataLength; i++){
//        G_Communication_Array[i + 2] = (*(((unsigned char *)sendData) + i));
//    }
//    G_Communication_Array[0] = DataLength >> 8;
//    G_Communication_Array[1] = DataLength & 0x00ff;
//    DataLength = DataLength + 2;
//    /* Calculate CRC16 checksum for Modbus-Serial-Line-PDU. */
//    usCRC16 = usMBCRC16( G_Communication_Array, DataLength );
//
//    G_Communication_Array[DataLength] = usCRC16 >> 8;   //high-bytes first
//    G_Communication_Array[DataLength + 1] = usCRC16;    //low-bytes second
//
//    sendingLength = DataLength + 2;
//
//        //shift 4  position back
//        for(i = sendingLength; i > 0; i--){
//            G_Communication_Array[i + 3] = G_Communication_Array[i - 1];
//        }
//        G_Communication_Array[0] = ONE_WIRE_PrecedingCheckCode >> 8;
//        G_Communication_Array[1] = ONE_WIRE_PrecedingCheckCode & 0x00ff;
//        G_Communication_Array[2] = ONE_WIRE_Data_PrecedingCode >> 8;
//        G_Communication_Array[3] = ONE_WIRE_Data_PrecedingCode & 0x00ff;
//        sendingLength = sendingLength + 4;
//
//
//        G_Communication_Array[sendingLength] = ONE_WIRE_EndCheckCode >> 8;
//        G_Communication_Array[sendingLength + 1] = ONE_WIRE_EndCheckCode & 0x00ff;
//        G_Communication_Array[sendingLength + 2] = ONE_WIRE_EndCheckCode >> 8;
//        G_Communication_Array[sendingLength + 3] = ONE_WIRE_EndCheckCode & 0x00ff;
//        sendingLength = sendingLength + 4;
//    _Device_Uart_Send_Bytes( G_Communication_Array, sendingLength); // send high byte first, send low byte second
//}
//
//void _DUI_One_Wire_Send_Bytes_CRC16(unsigned char *sendData, unsigned int length){
//	unsigned int sendingLength, usCRC16;
//    int i;
//
//    if(length > CommunicationArray_Data_Bytes_Size){
//        return;
//    }
//	for(i = 0; i < length; i++){
//        G_Communication_Array[i + 2] = sendData[i];
//    }
//    G_Communication_Array[0] = length >> 8;
//    G_Communication_Array[1] = length & 0x00ff;
//    length = length + 2;
//
//    /* Calculate CRC16 checksum for Modbus-Serial-Line-PDU. */
//    usCRC16 = usMBCRC16( G_Communication_Array, length );
//
//    G_Communication_Array[length] = usCRC16 >> 8;   //high-bytes first
//    G_Communication_Array[length + 1] = usCRC16;    //low-bytes second
//
//    sendingLength = length + 2;
//
//        //shift 4 position back
//        for(i = sendingLength; i > 0; i--){
//            G_Communication_Array[i + 3] = G_Communication_Array[i - 1];
//        }
//        G_Communication_Array[0] = ONE_WIRE_PrecedingCheckCode >> 8;
//        G_Communication_Array[1] = ONE_WIRE_PrecedingCheckCode & 0x00ff;
//        G_Communication_Array[2] = ONE_WIRE_Data_PrecedingCode >> 8;
//        G_Communication_Array[3] = ONE_WIRE_Data_PrecedingCode & 0x00ff;
//        sendingLength = sendingLength + 4;
//
//        G_Communication_Array[sendingLength] = ONE_WIRE_EndCheckCode >> 8;
//        G_Communication_Array[sendingLength + 1] = ONE_WIRE_EndCheckCode & 0x00ff;
//        G_Communication_Array[sendingLength + 2] = ONE_WIRE_EndCheckCode >> 8;
//        G_Communication_Array[sendingLength + 3] = ONE_WIRE_EndCheckCode & 0x00ff;
//        sendingLength = sendingLength + 4;
//    _Device_Uart_Send_Bytes( G_Communication_Array, sendingLength); // send high byte first, send low byte second
//}
//
//void _DUI_One_Wire_Send_EEPROM_DATA_CRC16(){
//	unsigned int sendingLength, usCRC16;
//
//    /* Calculate CRC16 checksum for Modbus-Serial-Line-PDU. */
//    usCRC16 = usMBCRC16( (unsigned char *)CONFIG_SEGMENT, EEPROM_END_DATA_POSITION_Offset + 1);
//
//        G_Communication_Array[0] = ONE_WIRE_PrecedingCheckCode >> 8;
//        G_Communication_Array[1] = ONE_WIRE_PrecedingCheckCode & 0x00ff;
//        G_Communication_Array[2] = ONE_WIRE_EEPROM_Seg_PrecedingCode >> 8;
//        G_Communication_Array[3] = ONE_WIRE_EEPROM_Seg_PrecedingCode & 0x00ff;
//        sendingLength = 4;
//
//        G_Communication_Array[sendingLength] = usCRC16 >> 8;   //high-bytes first
//        G_Communication_Array[sendingLength + 1] = usCRC16;    //low-bytes second
//        G_Communication_Array[sendingLength + 2] = ONE_WIRE_EndCheckCode >> 8;
//        G_Communication_Array[sendingLength + 3] = ONE_WIRE_EndCheckCode & 0x00ff;
//        G_Communication_Array[sendingLength + 4] = ONE_WIRE_EndCheckCode >> 8;
//        G_Communication_Array[sendingLength + 5] = ONE_WIRE_EndCheckCode & 0x00ff;
//
//    _Device_Uart_Send_Bytes( G_Communication_Array, sendingLength); // send high byte first, send low byte second
//    _Device_Uart_Send_Bytes( (unsigned char *)CONFIG_SEGMENT, EEPROM_END_DATA_POSITION_Offset + 1); // send high byte first, send low byte second
//    _Device_Uart_Send_Bytes( &(G_Communication_Array[sendingLength]), sendingLength + 2); // send high byte first, send low byte second
//}
//
//void _DUI_Communication_Send_EEPROM_DATA_CheckSum(unsigned char RespondCmd, unsigned int sendStartAddress, unsigned int length){
//	unsigned int usCkSum16;
//	unsigned int i;
//
//    usCkSum16 = 0;
//            G_Communication_Array[0] = LeadingCode;
//            G_Communication_Array[1] = SlaveAddressCode;
//            G_Communication_Array[2] = RespondCmd;
//            G_Communication_Array[3] = length;
//
//        usCkSum16 = SlaveAddressCode + RespondCmd + length;
//        for(i=0; i < length; i++){
//            usCkSum16 += (*((unsigned char *)sendStartAddress));
//        }
//            G_Communication_Array[4] = usCkSum16;
//            G_Communication_Array[5] = usCkSum16 >> 8;
//            G_Communication_Array[6] = EndCode1;
//            G_Communication_Array[7] = EndCode2;
//
//    _Device_Uart_Send_Bytes( G_Communication_Array, 4); // send high byte first, send low byte second
//    _Device_Uart_Send_Bytes( (unsigned char *)sendStartAddress, length); // send high byte first, send low byte second
//    _Device_Uart_Send_Bytes( &(G_Communication_Array[4]), 4); // send high byte first, send low byte second
//}
//void _DUI_Communication_Send_Word_CheckSum(unsigned char RespondCmd, unsigned int *sendData, unsigned int length, unsigned char isAddPrecedingCode, unsigned char isAddEndCode){
//	unsigned int sendingLength, usCkSum16;
//	unsigned int DataLength;
//    int i;
//
//    DataLength = length << 1;    // mul 2
//    if(DataLength > CommunicationArray_Data_Bytes_Size){
//        return;
//    }
////	for(i = 0; i < DataLength; i++){
////        G_Communication_Array[i] = (*(((unsigned char *)sendData) + i));
////    }
//    DataLength = 0 ;
//	for(i = 0; i < length; i++){
//        G_Communication_Array[DataLength++] = (*(sendData + i)) ;       //low byte first
//        G_Communication_Array[DataLength++] = (*(sendData + i)) >> 8 ;  //high byte second
//    }
//
//    /* Calculate checksum*/
//    usCkSum16 = usCheckSum16( G_Communication_Array, DataLength );
//    //usCkSum16 += SlaveAddressCode;
//
//    G_Communication_Array[DataLength] = usCkSum16;    //low-bytes first
//    G_Communication_Array[DataLength + 1] = usCkSum16 >> 8;   //high-bytes second
//
//    sendingLength = DataLength + 2;
//
//
//        if(isAddPrecedingCode){
//            //shift 4 position back
//            for(i = sendingLength; i > 0; i--){
//                G_Communication_Array[i + 3] = G_Communication_Array[i - 1];
//            }
//            sendingLength = sendingLength + 4;
//
//            G_Communication_Array[0] = LeadingCode;
//            G_Communication_Array[1] = SlaveAddressCode;
//            G_Communication_Array[2] = RespondCmd;
//            G_Communication_Array[3] = DataLength;
//
//            usCkSum16 += SlaveAddressCode;
//            usCkSum16 += RespondCmd;
//            usCkSum16 += DataLength;
//        }//if(enable_with_PrecedingCode){
//        if(isAddEndCode){
//            G_Communication_Array[sendingLength] = EndCode1;
//            G_Communication_Array[sendingLength + 1] = EndCode2;
//            sendingLength = sendingLength + 2;
//        }
//
//        /* update checksum*/
//        G_Communication_Array[sendingLength - 4] = usCkSum16;    //low-bytes first
//        G_Communication_Array[sendingLength - 3] = usCkSum16 >> 8;   //high-bytes second
//
//    _Device_Uart_Send_Bytes( G_Communication_Array, sendingLength); // send high byte first, send low byte second
//}
//void _DUI_Communication_Send_Bytes_CheckSum(unsigned char RespondCmd, unsigned char *sendData, unsigned int length, unsigned char isAddPrecedingCode, unsigned char isAddEndCode){
//	unsigned int sendingLength, usCkSum16;
//    int i;
//
//    if(length > CommunicationArray_Data_Bytes_Size){
//        return;
//    }
//	for(i = 0; i < length; i++){
//        G_Communication_Array[i] = sendData[i];
//    }
//
//    /* Calculate checksum*/
//    usCkSum16 = usCheckSum16( G_Communication_Array, length );
//
//    //G_Communication_Array[length] = usCkSum16 >> 8;   //high-bytes first
//    //G_Communication_Array[length + 1] = usCkSum16;    //low-bytes second
//
//    sendingLength = length + 2;
//
//
//        if(isAddPrecedingCode){
//            //shift 4 position back
//            for(i = sendingLength; i > 0; i--){
//                G_Communication_Array[i + 3] = G_Communication_Array[i - 1];
//            }
//            sendingLength = sendingLength + 4;
//
//            G_Communication_Array[0] = LeadingCode;
//            G_Communication_Array[1] = SlaveAddressCode;
//            G_Communication_Array[2] = RespondCmd;
//            G_Communication_Array[3] = length;
//            usCkSum16 += SlaveAddressCode;
//            usCkSum16 += RespondCmd;
//            usCkSum16 += length;
//        }//if(enable_with_PrecedingCode){
//        if(isAddEndCode){
//            G_Communication_Array[sendingLength] = EndCode1;
//            G_Communication_Array[sendingLength + 1] = EndCode2;
//            sendingLength = sendingLength + 2;
//        }
//
//        /* update checksum*/
//        G_Communication_Array[sendingLength - 4] = usCkSum16;    //low-bytes first
//        G_Communication_Array[sendingLength - 3] = usCkSum16 >> 8;   //high-bytes second
//
//    _Device_Uart_Send_Bytes( G_Communication_Array, sendingLength); // send high byte first, send low byte second
//}
//
////void _DUI_Communication_Send_Word_CRC16(unsigned char RespondCmd, unsigned int *sendData, unsigned int length, unsigned char isAddPrecedingCode, unsigned char isAddEndCode){
////	unsigned int sendingLength, usCRC16;
////	unsigned int DataLength;
////    int i;
////
////    DataLength = length << 1;    // mul 2
////    if(DataLength > CommunicationArray_Data_Bytes_Size){
////        return;
////    }
////	for(i = 0; i < DataLength; i++){
////        G_Communication_Array[i] = (*(((unsigned char *)sendData) + i));
////    }
////
////    /* Calculate CRC16 checksum for Modbus-Serial-Line-PDU. */
////    usCRC16 = usMBCRC16( G_Communication_Array, DataLength );
////
////    G_Communication_Array[DataLength] = usCRC16 >> 8;   //high-bytes first
////    G_Communication_Array[DataLength + 1] = usCRC16;    //low-bytes second
////
////    sendingLength = DataLength + 2;
////
////
////        if(isAddPrecedingCode){
////            //shift 4 position back
////            for(i = sendingLength; i > 0; i--){
////                G_Communication_Array[i + 3] = G_Communication_Array[i - 1];
////            }
////            sendingLength = sendingLength + 4;
////
////            G_Communication_Array[0] = LeadingCode;
////            G_Communication_Array[1] = SlaveAddressCode;
////            G_Communication_Array[2] = RespondCmd;
////            G_Communication_Array[3] = DataLength;
////        }//if(enable_with_PrecedingCode){
////        if(isAddEndCode){
////            G_Communication_Array[sendingLength] = EndCode1;
////            G_Communication_Array[sendingLength + 1] = EndCode2;
////            sendingLength = sendingLength + 2;
////        }
////    _Device_Uart_Send_Bytes( G_Communication_Array, sendingLength); // send high byte first, send low byte second
////}
////void _DUI_Communication_Send_Bytes_CRC16(unsigned char RespondCmd, unsigned char *sendData, unsigned int length, unsigned char isAddPrecedingCode, unsigned char isAddEndCode){
////	unsigned int sendingLength, usCRC16;
////    int i;
////
////    if(length > CommunicationArray_Data_Bytes_Size){
////        return;
////    }
////	for(i = 0; i < length; i++){
////        G_Communication_Array[i] = sendData[i];
////    }
////
////    /* Calculate CRC16 checksum for Modbus-Serial-Line-PDU. */
////    usCRC16 = usMBCRC16( G_Communication_Array, length );
////
////    G_Communication_Array[length] = usCRC16 >> 8;   //high-bytes first
////    G_Communication_Array[length + 1] = usCRC16;    //low-bytes second
////
////    sendingLength = length + 2;
////
////
////        if(isAddPrecedingCode){
////            //shift 4 position back
////            for(i = sendingLength; i > 0; i--){
////                G_Communication_Array[i + 3] = G_Communication_Array[i - 1];
////            }
////            sendingLength = sendingLength + 4;
////
////            G_Communication_Array[0] = LeadingCode;
////            G_Communication_Array[1] = SlaveAddressCode;
////            G_Communication_Array[2] = RespondCmd;
////            G_Communication_Array[3] = length;
////        }//if(enable_with_PrecedingCode){
////        if(isAddEndCode){
////            G_Communication_Array[sendingLength] = EndCode1;
////            G_Communication_Array[sendingLength + 1] = EndCode2;
////            sendingLength = sendingLength + 2;
////        }
////    _Device_Uart_Send_Bytes( G_Communication_Array, sendingLength); // send high byte first, send low byte second
////}
//// Uart2  : (section stop)	
//////////////////////////////////////////////////////////////////////////


#if 0
//////////////////////////////////////////////////
// LED function  : (section start)
void InitLEDDisplay(){
    unsigned char i = 0;
    unsigned char bit;

    G_All_LED_Bits_Mask = 0;
    for(i=0; i<LEDNumbers; i++){
        bit = 1;
        bit <<= i;
        G_All_LED_Bits_Mask |= bit;
    }

    G_LED_Interface_Status1 = 0;
    G_LED_Interface_Status2 = 0;
    _Device_Init_Led_Function();
}


void SetLed_DirectIO_BITs(unsigned char LEDNumBits){
    unsigned int temp = 0;
    temp = LEDNumBits & G_All_LED_Bits_Mask;
    //LEDNumBits = LEDNumBits & G_All_LED_Bits_Mask;
    //temp |= LEDNumBits;

    G_LED_Interface_Status1 = G_LED_Interface_Status1 & 0xff00;
    G_LED_Interface_Status1 |= temp;

    _Device_Set_Led_OnOff_BITs((unsigned char)G_LED_Interface_Status1);
}

void SetLed_DirectIO_Pin_OnOff(unsigned char LEDNumPin){
    unsigned int temp;
    temp = LEDNumPin & G_All_LED_Bits_Mask;
    //LEDNumPin = LEDNumPin & G_All_LED_Bits_Mask;
    //temp = LEDNumPin;

    _Device_Set_Led_Pin_OnOff((unsigned char)temp);
}

void SetLedLightOnFlag(unsigned char LEDNumBits, unsigned char enable){
    unsigned int temp = 0;
    temp = LEDNumBits & G_All_LED_Bits_Mask;
    //LEDNumBits = LEDNumBits & G_All_LED_Bits_Mask;
    //temp = LEDNumBits;
    if(enable == 0){
        G_LED_Interface_Status1 &= ~(temp << 8);
    }else{
        G_LED_Interface_Status1 |= (temp << 8);
    }
}

void SetLedBlinkFlag(unsigned char LEDNumBits, unsigned char enable){
	unsigned int temp = 0;
    temp = LEDNumBits & G_All_LED_Bits_Mask;
    //LEDNumBits = LEDNumBits & G_All_LED_Bits_Mask;
    if(enable == 0){
        G_LED_Interface_Status2 &= ~temp;
    }else{
        G_LED_Interface_Status2 |= temp;
    }
}

void SetLedPWMFunction(unsigned char LEDNumBits, unsigned char enable){
    unsigned int temp = 0;
    temp = LEDNumBits & G_All_LED_Bits_Mask;
    //temp = LEDNumBits;

    if(enable){
        //turn on
        G_LED_Interface_Status2 |= (temp << 8);
        _Device_Set_Led_PWM_BITs((unsigned char)(G_LED_Interface_Status2 >> 8));
    }else{
        //turn off
        G_LED_Interface_Status2 &= ~(temp << 8);
        _Device_Set_Led_PWM_BITs(0);
    }
    //_Device_Set_Led_PWM_BITs((unsigned char)(G_LED_Interface_Status2 >> 8));

}
void SetLedPWM20Steps(unsigned char PWM_Steps){
    //LEDNumBits = LEDNumBits & G_All_LED_Bits_Mask;
    _Device_Set_Led_PWM_20_Steps((unsigned char)(G_LED_Interface_Status2 >> 8), PWM_Steps);
}


void SetLedSerialTurnOnOff_ByIO(unsigned char enable){
    unsigned char bit;
    unsigned int i, j;
    SetLedPWMFunction(G_All_LED_Bits_Mask, TurnOff);
    SetLedBlinkFlag(G_All_LED_Bits_Mask, TurnOff);
    SetLedLightOnFlag(G_All_LED_Bits_Mask, TurnOff);

    if(enable){
        //turn on
        bit=0;
        for(i=0; i < LEDNumbers; i++){
            bit = (bit << 1) + 1;
            SetLed_DirectIO_Pin_OnOff(bit);
            for(j = 0; j < 1000;j++){
                delay_cycles(100); //about 960us at 4MHz
            }
        }
        SetLed_DirectIO_Pin_OnOff(0x00);
    }else{
        bit=G_All_LED_Bits_Mask;
        SetLed_DirectIO_Pin_OnOff(bit);
        for(i=0; i < LEDNumbers; i++){
            //SetLed_DirectIO_Pin_OnOff(~bit);
            for(j = 0; j < 1000;j++){
                delay_cycles(100); //about 960us at 4MHz
            }
            bit = (bit >> 1);
            SetLed_DirectIO_Pin_OnOff(bit);
        }
        SetLed_DirectIO_Pin_OnOff(0x00);
    }
}

void SetLedSerialTurnOnOff_ByTimer(unsigned char enable){
    unsigned char bit;
    unsigned int i, j;
    SetLedPWMFunction(G_All_LED_Bits_Mask, TurnOff);
    SetLedBlinkFlag(G_All_LED_Bits_Mask, TurnOff);
    SetLedLightOnFlag(G_All_LED_Bits_Mask, TurnOff);

    if(enable){
        //turn on
        bit=0;
        for(i=0; i < LEDNumbers; i++){
            bit = (bit << 1) + 1;
            SetLedLightOnFlag(bit, TurnOn);
            for(j = 0; j < 1000;j++){
                delay_cycles(100); //about 960us at 4MHz
            }
        }
        SetLedLightOnFlag(G_All_LED_Bits_Mask, TurnOff);
    }else{
        bit=G_All_LED_Bits_Mask;
        SetLedLightOnFlag(bit, TurnOn);
        for(i=0; i < LEDNumbers; i++){
            SetLedLightOnFlag(~bit, TurnOff);
            bit = (bit >> 1);
            for(j = 0; j < 1000;j++){
                delay_cycles(100); //about 960us at 4MHz
            }
        }
        SetLedLightOnFlag(G_All_LED_Bits_Mask, TurnOff);
    }
}


void SetLedFlashing(){
    unsigned char bit;
    unsigned int i, j;
    SetLedPWMFunction(G_All_LED_Bits_Mask, TurnOff);
    SetLedBlinkFlag(G_All_LED_Bits_Mask, TurnOff);
    SetLedLightOnFlag(G_All_LED_Bits_Mask, TurnOff);

    bit = 0;
    for(i=0; i < 15; i++){
        bit ^= 0x01;
        if(bit){
            SetLed_DirectIO_Pin_OnOff(0xff);
        }else{
            SetLed_DirectIO_Pin_OnOff(0x00);
        }
        for(j = 0; j < 100;j++){
            delay_cycles(100); //about 960us at 4MHz
        }
    }
    SetLed_DirectIO_Pin_OnOff(0x00);

}

#if _USE_5_LED_DISPLAY_    ==  0
// 4LEDs
void DisplayCapacity(unsigned char capacity, char isOn)
{
    if(isOn)
    {
        if(capacity <= CAPACITY_1){
            SetLedPWMFunction(LED1, TurnOn);
        }else if(capacity <= CAPACITY_2){
            SetLedPWMFunction(LED1 + LED2, TurnOn);
        }else if(capacity <= CAPACITY_3){
            SetLedPWMFunction(LED1 + LED2 + LED3, TurnOn);
        }else {
            SetLedPWMFunction(LED1 + LED2 + LED3 + LED4, TurnOn);
        }
    }
    else
    {
        SetLedPWMFunction(LED1 + LED2 + LED3 + LED4, TurnOff);
    }
}
#else
// 5LEDs
void DisplayCapacity(unsigned char capacity, char isOn)
{
    if(isOn)
    {
        if(capacity <= CAPACITY_1){
            SetLedPWMFunction(LED1, TurnOn);
        }else if(capacity <= CAPACITY_2){
            SetLedPWMFunction(LED1 + LED2, TurnOn);
        }else if(capacity <= CAPACITY_3){
            SetLedPWMFunction(LED1 + LED2 + LED3, TurnOn);
        }else if (capacity <= CAPACITY_4){
            SetLedPWMFunction(LED1 + LED2 + LED3 + LED4, TurnOn);
        }else{
            SetLedPWMFunction(LED1 + LED2 + LED3 + LED4 + LED5, TurnOn);
        }
    }
    else
    {
        SetLedPWMFunction(LED1 + LED2 + LED3 + LED4 + LED5, TurnOff);
    }
}
#endif
// LED function  : (section stop)
//////////////////////////////////////////////////

////////////////////////////////////////////
// Input Signal Pin control  : (section start)
void InitInputSignalPin(){
    G_Device_Interface_Status &= ~PIC_UVP_STATUS;
    G_Device_Interface_Status &= ~PIC_OVP_STATUS;
    _Device_Init_Input_Signal_Pin_Function();
}

unsigned char get_PIC_UVP_Status(){
    if(_Device_Get_PIC_UVP_Status() == TurnOff){
        G_Device_Interface_Status &= ~PIC_UVP_STATUS;
        return TurnOff;
    }else{
        G_Device_Interface_Status |= PIC_UVP_STATUS;
        return TurnOn;
    }
}

unsigned char get_PIC_OVP_Status(){
    if(_Device_Get_PIC_OVP_Status() == TurnOff){
        G_Device_Interface_Status &= ~PIC_OVP_STATUS;
        return TurnOff;
    }else{
        G_Device_Interface_Status |= PIC_OVP_STATUS;
        return TurnOn;
    }
}
// Input Signal Pin control  : (section stop)
////////////////////////////////////////////





////////////////////////////////////////////
// AWU Timer (50ms)  : (section start)
void InitAWUTimerFunction(){
    _Device_AWU_HALT_Timer_Init();
}
void DisableAWUTimerFunction(){
    _Device_Disable_AWU_HALT_Timer();
}
void Set_AWU_Shorter_Timer_Interval_Time_Base(){
    _Device_Set_AWU_Shorter_Timer_Interval_Time_Base();
}
void Set_AWU_Longer_Timer_Interval_Time_Base(){
    _Device_Set_AWU_Longer_Timer_Interval_Time_Base();
}
void Set_Interrupt_AWU_Timer_Calling_Function(unsigned char fun_index, void (*calling_fun)()){
    _Device_Set_AWU_Interrupt_Timer_Calling_Function(fun_index, calling_fun);
}
void Remove_Interrupt_AWU_Timer_Calling_Function(unsigned char fun_index, void (*calling_fun)()){
    _Device_Remove_AWU_Interrupt_Timer_Calling_Function(fun_index);
}
// AWU Timer (50ms)  : (section stop)
////////////////////////////////////////////

////////////////////////////////////////////
// Uart2  : (section start)	

void InitUARTFunction(){
    _Device_Init_Uart();

    _Device_Set_Uart_Receive_Fram_Data_Calling_Function(ReceiveDataParsing);
    _Device_Set_Uart_RX_Interrupt(TurnOn);
}
void Set_Uart_RX_Interrupt(unsigned char enable){
    _Device_Set_Uart_RX_Interrupt(enable);
}
void UART_Send_Word_CRC(unsigned int *sendData, unsigned int length, unsigned char enable_with_PrecedingCode){
	unsigned int sendingLength, usCRC16;
    int i;

    if(length > GVarArraySize){
        length = GVarArraySize;
    }
	for(i = 0; i < length; i++){
        G_Communication_Array[i] = (*(sendData + i));
    }

    /* Calculate CRC16 checksum for Modbus-Serial-Line-PDU. */
    usCRC16 = usMBCRC16( ( unsigned char * ) G_Communication_Array, length * 2 );
    G_Communication_Array[length] = usCRC16;
    sendingLength = (length + 1) * 2;
    if(enable_with_PrecedingCode){
        //shift two arrays back
        for(i = length; i >= 0; i--){
            G_Communication_Array[i + 2] = G_Communication_Array[i];
        }

        G_Communication_Array[0] = PrecedingCheckCode;
        G_Communication_Array[1] = PrecedingCheckCode;
        G_Communication_Array[length + 2 + 1] = EndCheckCode;
        G_Communication_Array[length + 2 + 2] = EndCheckCode;
        sendingLength = (length + 1 + 2 + 2) * 2;
    }//if(enable_with_PrecedingCode){

//        /* Calculate CRC16 checksum for Modbus-Serial-Line-PDU. */
//        usCRC16 = usMBCRC16( ( UCHAR * ) pucSndBufferCur, usSndBufferCount );
//        ucRTUBuf[usSndBufferCount++] = ( UCHAR )( usCRC16 & 0xFF );
//        ucRTUBuf[usSndBufferCount++] = ( UCHAR )( usCRC16 >> 8 );
    _Device_Uart_Send_Byte(( unsigned char * ) G_Communication_Array, sendingLength); // send high byte first, send low byte second
}
void UART_Send_EEPROM_DATA_CRC_with_PrecedingCheckCode(){
	unsigned int sendingLength, usCRC16, val;
    int i;
    //unsigned char enable_with_PrecedingCode = true;
    unsigned int length = 64;
    //(*(PointerAttr uint8_t *) (uint16_t)Address)
    G_Communication_Array[0] = PrecedingCheckCode;
    G_Communication_Array[1] = PrecedingCheckCode;

    sendingLength = 0;
	for(i = 0; i < length; i++){
        val = (*((unsigned char *)(0x4000 + sendingLength)));
        sendingLength++;
        val = val << 8;
        val |= (*((unsigned char *)(0x4000 + sendingLength)));
        sendingLength++;
        G_Communication_Array[i + 2] = val;
    }

    /* Calculate CRC16 checksum for Modbus-Serial-Line-PDU. */
    usCRC16 = usMBCRC16( (( unsigned char * ) &(G_Communication_Array[2])), length * 2 );
    G_Communication_Array[length + 2] = usCRC16;
    G_Communication_Array[length + 2 + 1] = EndCheckCode;
    G_Communication_Array[length + 2 + 2] = EndCheckCode;
    sendingLength = (length + 1 + 2 + 2) * 2;
    _Device_Uart_Send_Byte(( unsigned char * ) G_Communication_Array, sendingLength); // send high byte first, send low byte second
}

void ReceiveDataParsing(unsigned char *receiveData, unsigned int length){
	unsigned int i, usCRC16;

    if(length > GVarArraySize + GVarArraySize){
        length = GVarArraySize + GVarArraySize;
    }
	for( i = 0; i < length; i++){
        ((unsigned char *)G_Communication_Array)[i] = (*(receiveData + i));
    }

    /* Calculate CRC16 checksum for Modbus-Serial-Line-PDU. */
    usCRC16 = usMBCRC16( ( unsigned char * ) G_Communication_Array, length - 2 );

    if(     (( unsigned char )( usCRC16 & 0xFF )) != ((unsigned char *)G_Communication_Array)[length - 1] || //llow byte
            (( unsigned char )( usCRC16 >> 8 ))  != ((unsigned char *)G_Communication_Array)[length - 2]){  // high byte
        // CRC16 checksum fail
        G_Communication_Array[0] = Uart_Send_Error_Code;
        UART_Send_Word_CRC(G_Communication_Array, 1, false);
        return;
    }else{
        // CRC16 checksum Pass
        i = ReceiveCmdParsing(G_Communication_Array, ((length - 2)>>1));
        //G_Communication_Array[0] = Read_funcition_code;
        if(i == 0){
           G_Communication_Array[0] = Uart_Send_Error_Code;
           i = 1;
        }
        UART_Send_Word_CRC(G_Communication_Array, i, false);

    }

}

// Uart2  : (section stop)	
////////////////////////////////////////////

////////////////////////////////////////////
// EEPROM  : (section start)	
void Init_EEPROM(){
    _Device_EEPROM_Init();
}
unsigned char EEPROM_WriteByte(unsigned int Address_Offset, unsigned char Data){
    if( _Device_EEPROM_WriteByte(Address_Offset, Data) == Data_Complete){
        return Data_Success;
    }else{
        return Data_Error;
    }
}
unsigned char EEPROM_WriteDoubleWord(unsigned int Address_Offset, unsigned long Data){
    if( _Device_EEPROM_WriteDoubleWord(Address_Offset, Data) == Data_Complete){
        return Data_Success;
    }else{
        return Data_Error;
    }
}
#ifdef RAM_EXECUTION
unsigned char EEPROM_WriteWholeMemory(unsigned char *array, unsigned char length){
    if( _Device_EEPROM_WriteWholeEEPROMMemory(array, length) == Data_Complete){
        return Data_Success;
    }else{
        return Data_Error;
    }
}
unsigned char EEPROM_ReadWholeMemory(unsigned char *array, unsigned char length){
    if( _Device_EEPROM_ReadWholeEEPROMMemory(array, length) == Data_Complete){
        return Data_Success;
    }else{
        return Data_Error;
    }
}

unsigned char EEPROM_ReadWholeEEPROMToInternalMemory( ){
    if( _Device_EEPROM_ReadWholeEEPROMToInternalMemory( ) == Data_Complete){
        return Data_Success;
    }else{
        return Data_Error;
    }
}
unsigned char EEPROM_Set_Data_ToInternalMemory(unsigned char offset, unsigned char *array, unsigned char length){
    if( _Device_EEPROM_Set_Data_ToInternalMemory(offset, array, length) == Data_Complete){
        return Data_Success;
    }else{
        return Data_Error;
    }
}
unsigned char EEPROM_WriteWholeEEPROMFromInternalMemory( ){
    if( _Device_EEPROM_WriteWholeEEPROMFromInternalMemory( ) == Data_Complete){
        return Data_Success;
    }else{
        return Data_Error;
    }
}
#endif
// EEPROM  : (section stop)	
////////////////////////////////////////////

////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////
void device_function_test(){
//    SetLed_DirectIO_OnOff(LED2, TurnOn);
//    SetLed_DirectIO_OnOff(LED2, TurnOff);
}
void device_function_test1(){
    _Device_uart_tim4_init();
    _Device_Set_Function_to_Timer_counter(10, device_function_test);
}
void device_function_test2(){
    _Device_Set_Function_to_Timer_counter(6, device_function_test);
}


#endif