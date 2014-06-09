/**
  ******************************************************************************
  * @file    Drivers.h
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   Peripherals Drivers header
  ******************************************************************************
  * @attention
  *
  * DESCRIPTION....
  *
  * <h2><center>&copy; COPYRIGHT 2012 Dynapack</center></h2>
  ******************************************************************************
  */

//==============================================================================
// Includes
//==============================================================================
#include "stm8l15x.h"
#include "Config_Info\System_Config_Info.h"

//==============================================================================
// Private define
//==============================================================================
#define Disable     0
#define Enable      1


#define Func_Fail           1
#define Func_Complete       0

#define true        1
#define false       0
//==============================================================================
// Private Enum
//==============================================================================
enum Device_Enable
{
  DeviceOff,
  DeviceOn
};
enum forButtonStatusCode
{
    ButtonRelease,
    ButtonPress
};

//==============================================================================
// System Clock Define
//==============================================================================
//
//#define System_Clock_Freq_2MHz
//#define System_Clock_Freq_4MHz
#define System_Clock_Freq_8MHz

//////////////////////////////////////////
#if defined(System_Clock_Freq_2MHz) && defined(System_Clock_Freq_4MHz)
    #error "Please Select One of Clock Freq Setting"
#elif defined(System_Clock_Freq_2MHz) && defined(System_Clock_Freq_8MHz)
    #error "Please Select One of Clock Freq Setting"
#elif defined(System_Clock_Freq_4MHz) && defined(System_Clock_Freq_8MHz)
    #error "Please Select One of Clock Freq Setting"
#endif
//////////////////////////////////////////

//==============================================================================
// Clock Config
//==============================================================================
#if defined(System_Clock_Freq_2MHz)
#define dSourceFreqDivided			CLK_SYSCLKDiv_8 //HEI freq 16MHz / 8 = 2MHz, for peripheral device and MCU core
#elif  defined(System_Clock_Freq_4MHz)
#define dSourceFreqDivided			CLK_SYSCLKDiv_4 //HEI freq 16MHz / 4 = 4MHz, for peripheral device and MCU core
#elif  defined(System_Clock_Freq_8MHz)
#define dSourceFreqDivided			CLK_SYSCLKDiv_2 //HEI freq 16MHz / 2 = 8MHz, for peripheral device and MCU core
#endif

#define RTC_WakeUp_Second_Times     1   //seconds

void _Device_Normal_Config_For_Exit_Halt();
void _Device_Active_Halt_Config_With_RTC_WakeUp();

//void _Device_CLK_Config(void);

void _Device_CLK_Config_Switch_To_HSI_Clock_Source();
void _Device_CLK_Config_Switch_To_LSI_Clock_Source();
//==============================================================================
// Watch Dog (IWDG) Config
//==============================================================================
void _Device_IWDG_Config(void);
unsigned char _Device_IsResumedByIWDG();
void _Device_Reload_IWDG_Counter();
//==============================================================================
// Watch Dog (WWDG) Config
//==============================================================================
void _Device_WWDG_Config(void);
void _Device_Reset_WWDG_Counter();

//==============================================================================
// Timer 4  Config
//==============================================================================
#if defined(System_Clock_Freq_2MHz)
/////////////////////////////////////////////////////////////////////////////////////////////
//for example, TIM4 (8 bits) configuration: (SYSCLK = 2MHz)
//   - TIM4CLK is set to 16 MHz, the TIM4 Prescaler is equal to 128 so the TIM1 counter
//   clock used is 16 MHz / 128 = 125 000 Hz
//  - With 125 000 Hz we can generate time base:
//      max time base is 2.048 ms if TIM4_PERIOD = 255 --> (255 + 1) / 125000 = 2.048 ms
//      min time base is 0.016 ms if TIM4_PERIOD = 1   --> (  1 + 1) / 125000 = 0.016 ms
//
//  - In this example , TIM4CLK is set to 4 MHz,
//        the TIM4 Prescaler is equal to 64,
//        so the TIM1 counter clock used is 4 MHz / 64 = 62,500 Hz.
//        we need to generate a time base equal to 1 ms
//        so TIM4_PERIOD = (0.001 * 62500 - 1) = 61
/////////////////////////////////////////////////////////////////////////////////////////////
#define Define_Constant_Timer4IntervalTimeBase_mS	1   //User could not modify the values
//#define dTimer4Divided				TIM4_Prescaler_64   // 4 MHz / 64 = 62,500 Hz
//#define dTIM4_PERIOD                  61                  //(0.001 * 62500 - 1) = 61 for 0.001S = 1 ms, max = 255
//#define dTimer4Divided				    TIM4_Prescaler_128  // 16 MHz / 128 = 125,000 Hz
//#define dTIM4_PERIOD                    124                  //(0.001 * 125000 - 1) = 124 for 0.001S = 1 ms, max = 255
#define dTimer4Divided				    TIM4_Prescaler_16  // 2 MHz / 16 = 125,000 Hz
#define dTIM4_PERIOD                    124                  //(0.001 * 125000 - 1) = 124 for 0.001S = 1 ms, max = 255

#elif defined(System_Clock_Freq_4MHz)

/////////////////////////////////////////////////////////////////////////////////////////////
//for example, TIM4 (8 bits) configuration:  (SYSCLK = 4MHz)
//   - TIM4CLK is set to 16 MHz, the TIM4 Prescaler is equal to 128 so the TIM1 counter
//   clock used is 16 MHz / 128 = 125 000 Hz
//  - With 125 000 Hz we can generate time base:
//      max time base is 2.048 ms if TIM4_PERIOD = 255 --> (255 + 1) / 125000 = 2.048 ms
//      min time base is 0.016 ms if TIM4_PERIOD = 1   --> (  1 + 1) / 125000 = 0.016 ms
//
//  - In this example , TIM4CLK is set to 4 MHz,
//        the TIM4 Prescaler is equal to 64,
//        so the TIM1 counter clock used is 4 MHz / 64 = 62,500 Hz.
//        we need to generate a time base equal to 1 ms
//        so TIM4_PERIOD = (0.001 * 62500 - 1) = 61
/////////////////////////////////////////////////////////////////////////////////////////////
// for 1 ms
//#define Define_Constant_Timer4IntervalTimeBase_mS	1   //User could not modify the values
//#define dTimer4Divided				TIM4_Prescaler_64   // 4 MHz / 64 = 62,500 Hz
//#define dTIM4_PERIOD                  61                  //(0.001 * 62500 - 1) = 61 for 0.001S = 1 ms, max = 255
// for 10 ms
#define Define_Constant_Timer4IntervalTimeBase_mS	10   //User could not modify the values
#define dTimer4Divided                  TIM4_Prescaler_256   // 4 MHz / 256 = 15625 Hz
#define dTIM4_PERIOD                    155                  //(0.01 * 15625 - 1) = 155 for 0.01S = 10 ms, max = 255

#elif defined(System_Clock_Freq_8MHz)

/////////////////////////////////////////////////////////////////////////////////////////////
//for example, TIM4 (8 bits) configuration:  (SYSCLK = 4MHz)
//   - TIM4CLK is set to 16 MHz, the TIM4 Prescaler is equal to 128 so the TIM1 counter
//   clock used is 16 MHz / 128 = 125 000 Hz
//  - With 125 000 Hz we can generate time base:
//      max time base is 2.048 ms if TIM4_PERIOD = 255 --> (255 + 1) / 125000 = 2.048 ms
//      min time base is 0.016 ms if TIM4_PERIOD = 1   --> (  1 + 1) / 125000 = 0.016 ms
//
//  - In this example , TIM4CLK is set to 4 MHz,
//        the TIM4 Prescaler is equal to 64,
//        so the TIM1 counter clock used is 4 MHz / 64 = 62,500 Hz.
//        we need to generate a time base equal to 1 ms
//        so TIM4_PERIOD = (0.001 * 62500 - 1) = 61
/////////////////////////////////////////////////////////////////////////////////////////////
// for 1 ms
//#define Define_Constant_Timer4IntervalTimeBase_mS	1   //User could not modify the values
//#define dTimer4Divided				TIM4_Prescaler_64   // 4 MHz / 64 = 62,500 Hz
//#define dTIM4_PERIOD                  61                  //(0.001 * 62500 - 1) = 61 for 0.001S = 1 ms, max = 255
// for 10 ms
#define Define_Constant_Timer4IntervalTimeBase_mS	10   //User could not modify the values
#define dTimer4Divided                  TIM4_Prescaler_512   // 8 MHz / 512 = 15625 Hz
#define dTIM4_PERIOD                    155                  //(0.01 * 15625 - 1) = 155 for 0.01S = 10 ms, max = 255

#else
    #error "Please Select One of Clock Freq Setting"
#endif

#define Max_Timer4_INTERRUPT_Function_Calling  5

void _Device_Timer4_Init(void);
void _Device_Setting_Timer4_Enable(uint8_t enable);
//void _Device_Set_Timer4_Interrupt_Timer_Calling_Delay(uint16_t ms_Dealy);
//void _Device_Set_Timer4_Interrupt_Timer_Calling_Function(uint8_t fun_index, void (*calling_fun)());
//void _Device_Remove_Timer4_Interrupt_Timer_Calling_Function(uint8_t fun_index);
void _Device_Set_Timer4_Interrupt_Timer_Calling_Function_With_Delay_And_Exec(uint8_t fun_index, void (*calling_fun)(), __IO uint16_t ms_Dealy );
void _Device_Remove_Timer4_Interrupt_Timer_Calling_Function(uint8_t fun_index);

//==============================================================================
// Timer 3  PWM Config
//==============================================================================
#define Define_Constant_Timer3IntervalTimeBase_mS	100              //  User could not modify the values

#if defined(System_Clock_Freq_2MHz)

//#define TIM3_CLOCK_DEVIATION        (50)                            //
//#define TIM3_PRESCALER              TIM3_Prescaler_32               //  for TIM3CLK = 16 MHz; 16 MHz / 32 = 500 000 Hz = TIM3 output frequency
//#define TIM3_PERIOD                 (50000 - TIM3_CLOCK_DEVIATION)  //  1/ TIM3 output frequency * TIM3_PERIOD = 100 ms = Interval Time

#define TIM3_CLOCK_DEVIATION        (50)                            //
#define TIM3_PRESCALER              TIM3_Prescaler_4               //  for TIM3CLK = 2 MHz; 2 MHz / 4 = 500 000 Hz = TIM3 output frequency
#define TIM3_PERIOD                 (50000 - TIM3_CLOCK_DEVIATION)  //  1/ TIM3 output frequency * TIM3_PERIOD = 100 ms = Interval Time

#elif defined(System_Clock_Freq_4MHz)

#define TIM3_CLOCK_DEVIATION        (50)                            //
#define TIM3_PRESCALER              TIM3_Prescaler_8               //  for TIM3CLK = 2 MHz; 4 MHz / 8 = 500 000 Hz = TIM3 output frequency
#define TIM3_PERIOD                 (50000 - TIM3_CLOCK_DEVIATION)  //  1/ TIM3 output frequency * TIM3_PERIOD = 100 ms = Interval Time

#elif defined(System_Clock_Freq_8MHz)

#define TIM3_CLOCK_DEVIATION        (50)                            //
#define TIM3_PRESCALER              TIM3_Prescaler_16               //  for TIM3CLK = 2 MHz; 8 MHz / 16 = 500 000 Hz = TIM3 output frequency
//#define TIM3_PERIOD                 (50000 - TIM3_CLOCK_DEVIATION)  //  1/ TIM3 output frequency * TIM3_PERIOD = 100 ms = Interval Time
#define TIM3_PERIOD                 (25000 - TIM3_CLOCK_DEVIATION)  //  1/ TIM3 output frequency * TIM3_PERIOD = 50 ms = Interval Time
#define TIM3_Count_For_50MS_Interval   2   //  for TIM3CLK = 8 MHz; 550 ms = Interval Time
#define Max_Timer3_Fast_INTERRUPT_Function_Calling  2

void _Device_Set_Timer3_Fast_Interrupt_Timer_Calling_Function(uint8_t fun_index, void (*calling_fun)());
void _Device_Remove_Timer3_Fast_Interrupt_Timer_Calling_Function(uint8_t fun_index);

#else
    #error "Please Select One of Clock Freq Setting"
#endif

#define Max_Timer3_INTERRUPT_Function_Calling  7

void _Device_Timer3_Init(void);
void _Device_Setting_Timer3_Enable(uint8_t enable);
void _Device_Set_Timer3_Interrupt_Timer_Calling_Interval_Times(uint16_t ms_Dealy);
void _Device_Set_Timer3_Interrupt_Timer_Calling_Function(uint8_t fun_index, void (*calling_fun)());
void _Device_Remove_Timer3_Interrupt_Timer_Calling_Function(uint8_t fun_index);

//==============================================================================
// Timer 1  PWM Config
//==============================================================================
#define Define_Constant_Timer1_OutputFrequency	250 //Hz, User could not modify the values

///////////////////////////////////////////////////////////////////////////////////////
//  - TIM1CLK = 4 MHz
//  - TIM1_PRESCALER = 1
//  - TIM1 counter clock(freq) = TIM1CLK / (TIM1_PRESCALER+1) = 2 MHz
//  - TIM1_Period = 7999
//  - TIM1 Channel output frequency = TIM1 counter clock / (TIM1 Period+1) = 250Hz
//
//  ==> example for TIM1 configuration:
//    - TIM1CLK is set to 4 MHz,
//    - the TIM2 Prescaler is equal to 2,
//    - so the TIM1 counter clock used is 4 MHz / (1 + 1) = 2 MHz
//    - then set the TIM1_PERIOD is equal to 7999,
//    - TIM1 Channel 1 output frequency   = TIM1 counter clock / (TIM1_PERIOD + 1)
//                                        = 2 000 000 / (7999 + 1) = 250 Hz
///////////////////////////////////////////////////////////////////////////////////////
#define TIM1_PERIOD                 7999    //not modify, have to fix

#if defined(System_Clock_Freq_2MHz)
//#define TIM1_PRESCALER              7   //for TIM1CLK = 16 MHz
#define TIM1_PRESCALER              0   //for TIM1CLK = 2 MHz
#elif defined(System_Clock_Freq_4MHz)
#define TIM1_PRESCALER              1   //for TIM1CLK = 4 MHz
#elif defined(System_Clock_Freq_8MHz)
#define TIM1_PRESCALER              3   //for TIM1CLK = 8 MHz
#else
    #error "Please Select One of Clock Freq Setting"
#endif

#define TIM1_REPTETION_COUNTER      0

#define _Init_TIM1_Duty_Values_     0    // Duty = _Init_Duty_Values_ / (TIM1_PERIOD+1) =(0%)

//void _Device_TIM1_Config(void);
void _Device_Set_Timer1_PWM_Config_Enable(uint8_t enable);
void _Device_Set_Timer1_Channel_1_PWM(uint8_t enable);
void _Device_Set_Timer1_Channel_2_PWM(uint8_t enable);
void _Device_Set_Timer1_Channel_3_PWM(uint8_t enable);
void _Device_Set_Timer1_Channel_1_PWM_Duty(uint16_t duty_value);
void _Device_Set_Timer1_Channel_2_PWM_Duty(uint16_t duty_value);
void _Device_Set_Timer1_Channel_3_PWM_Duty(uint16_t duty_value);

//==============================================================================
// Timer 2  PWM Config
//==============================================================================
#define Define_Constant_Timer2_OutputFrequency	250 //Hz, User could not modify the values
////////////////////////////////////////////////////////////////////////////////////////
//  - TIM2CLK = 4 MHz
//  - TIM2_PRESCALER = TIM2_Prescaler_2
//  - TIM2 counter clock(freq) = TIM1CLK / TIM2_PRESCALER = 2 MHz
//  - TIM2_Period = 7999
//  - TIM2 Channel output frequency = TIM2 counter clock / (TIM2 Period+1) = 250Hz
//
//  ==> example for TIM2 configuration:
//    - TIM2CLK is set to 4 MHz,
//    - the TIM2 Prescaler is equal to 2,
//    - so the TIM2 counter clock used is 4 MHz / 2 =  2 MHz
//    - then set the TIM2_PERIOD is equal to 7999,
//    - TIM1 Channel 1 output frequency   = TIM2 counter clock / (TIM2_PERIOD + 1)
//                                        = 2 000 000 / (7999 + 1) = 250 Hz
////////////////////////////////////////////////////////////////////////////////////////
#define TIM2_PERIOD                 7999

#if defined(System_Clock_Freq_2MHz)
//#define TIM2_PRESCALER              TIM2_Prescaler_8 //for TIM1CLK = 16 MHz
#define TIM2_PRESCALER              TIM2_Prescaler_1 //for TIM1CLK = 2 MHz (No effect)
#elif defined(System_Clock_Freq_4MHz)
#define TIM2_PRESCALER              TIM2_Prescaler_2 //for TIM1CLK = 4 MHz
#elif defined(System_Clock_Freq_8MHz)
#define TIM2_PRESCALER              TIM2_Prescaler_4 //for TIM1CLK = 8 MHz
#else
    #error "Please Select One of Clock Freq Setting"
#endif

#define TIM2_REPTETION_COUNTER      0
#define _Init_TIM2_Duty_Values_     0    // Duty = _Init_Duty_Values_ / (TIM2_PERIOD+1) =(0%)

//void _Device_TIM2_Config(void);
void _Device_Set_Timer2_PWM_Config_Enable(uint8_t enable);
void _Device_Set_Timer2_Channel_1_PWM(uint8_t enable);
void _Device_Set_Timer2_Channel_2_PWM(uint8_t enable);
void _Device_Set_Timer2_Channel_1_PWM_Duty(uint16_t duty_value);
void _Device_Set_Timer2_Channel_2_PWM_Duty(uint16_t duty_value);


//==============================================================================
// Utility Functions
//==============================================================================
void _Device_delay_cycles(unsigned long cycleCount);
void _Device_GPIO_LowPower_Config(void);

//==============================================================================
// Button Control_init
//==============================================================================
void _Device_Button_Config(void);
unsigned char _Device_Get_Button_Status();
void _Device_Set_Interrupt_ButtonEvent_Press_Trigger_Function(void (*calling_fun)());
void _Device_Remove_Interrupt_ButtonEvent_Press_Trigger_Function();

//==============================================================================
// LED PWM Control_init
//==============================================================================
// PWM Output
#define LED1_PORT	GPIOD
#define LED1_PIN	GPIO_Pin_2
#define LED2_PORT	GPIOD
#define LED2_PIN	GPIO_Pin_4
#define LED3_PORT	GPIOD
#define LED3_PIN	GPIO_Pin_5
#define LED4_PORT	GPIOB
#define LED4_PIN	GPIO_Pin_0
#define LED5_PORT	GPIOB
#define LED5_PIN	GPIO_Pin_2

#define LED1_BIT                (0x01)
#define LED2_BIT                (0x02)
#define LED3_BIT                (0x04)
#define LED4_BIT                (0x08)
#define LED5_BIT                (0x10)
enum LED_NUM_CODEs
{
    LED1_Num,
    LED2_Num,
    LED3_Num,
    LED4_Num,
    LED5_Num
};

#define GPIO_HIGH(IO_Port,IO_Pin) 		IO_Port->ODR|=IO_Pin
#define GPIO_LOW(IO_Port,IO_Pin)		IO_Port->ODR&=~IO_Pin
#define GPIO_TOGGLE(IO_Port,IO_Pin) 	IO_Port->ODR^=IO_Pin

#define MAX_LED_NUM         5

//#define BREATHING_LIGHT_EACH_STEP_INTERVAL_MS    70 //unit: 1ms, 70ms for one of 20 steps
#define BREATHING_LIGHT_EACH_STEP_INTERVAL_MS    7 //unit: 10ms, 70ms for one of 20 steps
//#define BLINKING_LIGHT_INTERVAL_MS               300 //unit: 1ms, 200ms
#define BLINKING_LIGHT_INTERVAL_MS               20//unit: 10ms, 200ms



void _Device_Init_Led_Function(void);
void _Device_Set_Led_OnOff_By_BITs(unsigned char LEDNumBits);
void _Device_Set_Led_Pin_OnOff(unsigned char LEDNum, unsigned char Device_Enable);
//void _Device_Set_Led_PWM_Enable(unsigned char enable);
void _Device_Set_Led_PWM_Channel_Bits_Enable(unsigned char LEDNumBits);
void _Device_Set_Led_PWM_Change_Duty(unsigned char LEDNumBits, unsigned int duty);
unsigned char _Device_Get_Last_PWM_LED_Bit_By_LED_NUMs(unsigned char ShowingNumOfLeds);
unsigned char _Device_Get_LED_Bit_Without_PWM_Bit_By_LED_NUMs(unsigned char ShowingNumOfLeds);
unsigned char _Device_Get_LED_Bit_By_LED_NUMs(unsigned char ShowingNumOfLeds);
void _Device_Set_Breathing_Light_LED_BIT( unsigned char PWM_Led_Bit );
void _Device_Set_Blinking_Light_LED_BIT( unsigned char Blink_Led_Bit );

#if (_USE_TOUCH_KEY_WITH_LED_ == 1)
#define TOUCH_KEY_LED_BLINKING_LIGHT_Turn_On_INTERVAL_MS              20 //unit: 10ms, 200ms
#define TOUCH_KEY_LED_BLINKING_LIGHT_Turn_Off_INTERVAL_MS             180 //unit: 10ms, 200ms
#define TOUCH_KEY_LED_PORT	        GPIOB
#define TOUCH_KEY_LED_PIN	        GPIO_Pin_2
void _Device_Init_TOUCH_KEY_Led_Function(void);
void _Device_Set_TOUCH_KEY_Led_OnOff(unsigned char Device_Enable);
void _Device_Set_TOUCH_KEY_LED_Blinking( unsigned char Device_Enable );
#endif

//void _Device_Set_Led_PWM_20_Steps(unsigned char LEDNumBits, unsigned char steps);


//void _Device_Set_Led_PWM_BITs(unsigned char LEDNumBits);
//void _Device_Set_Led_PWM_20_Steps(unsigned char LEDNumBits, unsigned char steps);
//void _Device_Set_Led_OnOff_BITs(unsigned char LEDNumBits);
//void _Device_Set_Led_Pin_OnOff(unsigned char LEDNumPin);




//==============================================================================
// ADC 1 Config
//==============================================================================


void _Device_ADC_Config_Init(void);
void _Device_ADC_Config_All_Channel_Scan(void);
unsigned int _Device_Get_ADC_Channel_Buffer(unsigned int channelNum);
unsigned int _Device_Get_VRef_mVoltage();

//==============================================================================
// USART1 Config
//==============================================================================
void _Device_Uart_Enable(void);
void _Device_Uart_Disable(void);
void _Device_Set_Uart_RX_Interrupt(unsigned char enable);
void _Device_Set_Uart_Interrupt_Receive_Calling_Function(void (*calling_fun)(__IO unsigned char receivedByte));
unsigned char _Device_Uart_Send_Bytes(unsigned char *sendByte, unsigned int length);
unsigned char _Device_Get_Uart_Pin_Interrupt_Received();

//==============================================================================
// Configure RTC peripheral
//==============================================================================
void _Device_RTC_Config(void);
void _Device_RTC_Wake_Up_Event_Enable( unsigned char enable);
void _Device_Disable_RTC(void);
//==============================================================================
// Configure Optput Signal Control GPIO peripheral
//==============================================================================
void _Device_OptputSignalControl_Init(void);
void _Device_AdapterSOCControl_Pin_High();
void _Device_AdapterSOCControl_Pin_Low();
void _Device_OneWireControl_Pin_High();
void _Device_OneWireControl_Pin_Low();
void _Device_UartIsolationControl_Pin_High();
void _Device_UartIsolationControl_Pin_Low();
void _Device_NTC_Control_Pin_High();
void _Device_NTC_Control_Pin_Low();
//==============================================================================
// Configure Input Signal Control GPIO peripheral
//==============================================================================
void _Device_InputSignalControl_Init(void);
unsigned char _Device_Get_HW_CHG_Status();
unsigned char _Device_Get_HW_DSG_Status();

//==============================================================================
// Configure Mos FET  Control GPIO peripheral
//==============================================================================
void _Device_Mos_Control_Init(void);
void _Device_DSG_MosFET_Pin_High();
void _Device_DSG_MosFET_Pin_Low();
void _Device_CHG_MosFET_Pin_High();
void _Device_CHG_MosFET_Pin_Low();

//==============================================================================
// Configure EEPROM Write/Read setting
//==============================================================================
#define Eeprom_Start_Add    0x1000
#define Eeprom_End_Add      0x13ff
void _Device_EEPROM_Access_Enable();
void _Device_EEPROM_Access_Disable();
unsigned char _Device_EEPROM_WriteByte(unsigned int Write_Address, unsigned char Data);
unsigned char _Device_EEPROM_WriteDoubleWord(unsigned int Write_Address, unsigned long Data);

//==============================================================================
// USB Output Power Signal Control setting
//==============================================================================
enum forUsbOcpStatusCode
{
    USB_Output_Power_Normal,
    USB_Output_Power_OCP
};
void _Device_UsbOutputPowerSignalControl_Init(void);
void _Device_USB_OutputPower_ONOFF_Signal_Pin_High();
void _Device_USB_OutputPower_ONOFF_Signal_Pin_Low();
unsigned char _Device_Get_USB_OCP_Signal_Status();

//==============================================================================
// Back Light Signal Control setting
//==============================================================================
void _Device_BackLightControl_Init(void);
unsigned char _Device_Get_BackLight_Button_Status();
void _Device_Set_BackLight_Button_Interrupt_Enable(unsigned char enable);
void _Device_Set_Interrupt_BackLight_ButtonEvent_Press_Trigger_Function(void (*calling_fun)());
void _Device_Remove_Interrupt_BackLight_ButtonEvent_Press_Trigger_Function();
void _Device_BackLight_SignalOutput_Pin_High();
void _Device_BackLight_SignalOutput_Pin_Low();


/******************* (C) COPYRIGHT 2012 Dynapack *****END OF FILE****/



