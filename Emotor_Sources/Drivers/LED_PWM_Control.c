/**
  ******************************************************************************
  * @file    LED_PWM_Control.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   LED display, I/O and PWM Control
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
#include "Drivers.h"
#include "Config_Info\System_Config_Info.h"
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
#define _One_Step_Count_Values_For_10_Steps_      800   //  (7999+1)/10
#define _One_Step_Count_Values_For_20_Steps_      400   //  (7999+1)/10
///////////////////////////////////////////////////////////////////////////////
//  MAX PERIOD = TIM1_PERIOD  and  TIM2_PERIOD  =   (7999 + 1) = 8000
//#define PWM_FREQ_STEP_POINTS         21
//const unsigned int PWM_Freq_Scaler_Duty[PWM_FREQ_STEP_POINTS]=
//{
//        0    , 	//index = 00
//        800  ,  //index = 01
//        1600 ,  //index = 02
//        2400 ,  //index = 03
//        3200 ,  //index = 04
//        4000 ,  //index = 05
//        4800 ,  //index = 06
//        5600 ,  //index = 07
//        6400 ,  //index = 08
//        7200 ,  //index = 09
//        8000 ,  //index = 10, Max PERIOD
//        7200 ,  //index = 11
//        6400 ,  //index = 12
//        5600 ,  //index = 13
//        4800 ,  //index = 14
//        4000 ,  //index = 15
//        3200 ,  //index = 16
//        2400 ,  //index = 17
//        1600 ,  //index = 18
//        800  ,  //index = 19
//        0       //index = 20
//};


//#define PWM_FREQ_STEP_POINTS         41
//const unsigned int PWM_Freq_Scaler_Duty[PWM_FREQ_STEP_POINTS]=
//{
//    0,	400,	800,	1200,	1600,	2000,	2400,	2800,	3200,	3600,	4000,
//    4400,	4800,	5200,	5600,	6000,	6400,	6800,	7200,	7600,	8000,	
//    7600,	7200,	6800,	6400,	6000,	5600,	5200,	4800,	4400,	4000,	
//    3600,	3200,	2800,	2400,	2000,	1600,	1200,	800,	400,	0	
//};

#define PWM_FREQ_STEP_POINTS         45

#if(_LED_Control_Reverse_With_Lo_LEVEL_Turn_ON_ == 1)
const unsigned int PWM_Freq_Scaler_Duty[PWM_FREQ_STEP_POINTS]=
{
    8000, 7000, 6200,	5600,	5200,	4800,	4400,	4000,	3600,	3200,	2800,	2400,
    2000,	1800,	1600,	1400,	1200,	1000,	800,	600,	400,	200,
    0,	200,	400,	600,	800,	1000,	1200,	1400,	1600,	1800,	2000,
    2400,	2800,	3200,	3600,	4000,	4400,	4800,	5200,	5600,	6200,	7000,
    8000
};
#else
const unsigned int PWM_Freq_Scaler_Duty[PWM_FREQ_STEP_POINTS]=
{
    0,	200,	400,	600,	800,	1000,	1200,	1400,	1600,	1800,	2000,
    2400,	2800,	3200,	3600,	4000,	4400,	4800,	5200,	5600,	6200,	7000,
    8000,
    7000,	6200,	5600,	5200,	4800,	4400,	4000,	3600,	3200,	2800,	2400,
    2000,	1800,	1600,	1400,	1200,	1000,	800,	600,	400,	200,	0
};
#endif
//==============================================================================
// Private macro
//==============================================================================
//==============================================================================
// Private variables
//==============================================================================
//==============================================================================
// Private function prototypes
//==============================================================================
static unsigned char set_PWM_LED_BITS;
static unsigned char set_Light_LED_BITS;
static unsigned char set_Blink_LED_BITS;
static unsigned char blink_XOR_Flag;
static unsigned char set_PWM_Duty_Steps;
//==============================================================================
// Private functions
//==============================================================================
/**
  * @brief  LED I/O Control_init	
  * @param  None
  * @retval None
  */
void _Device_Init_Led_Function(void)
{
    set_PWM_LED_BITS = 0;
    set_Light_LED_BITS = 0;
    set_Blink_LED_BITS = 0;
    blink_XOR_Flag = 0;

    set_PWM_Duty_Steps = 0;
    _Device_Set_Timer1_PWM_Config_Enable(DeviceOff);
    _Device_Set_Timer2_PWM_Config_Enable(DeviceOff);

#if(_LED_Control_Reverse_With_Lo_LEVEL_Turn_ON_ == 1)
    //for low power setting
	GPIO_Init(LED1_PORT, LED1_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
	GPIO_Init(LED2_PORT, LED2_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
	GPIO_Init(LED3_PORT, LED3_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
	GPIO_Init(LED4_PORT, LED4_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
	GPIO_Init(LED5_PORT, LED5_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
#else
    //for low power setting
	GPIO_Init(LED1_PORT, LED1_PIN, GPIO_Mode_Out_PP_Low_Slow);  // set as output and PP Low level
	GPIO_Init(LED2_PORT, LED2_PIN, GPIO_Mode_Out_PP_Low_Slow);  // set as output and PP Low level
	GPIO_Init(LED3_PORT, LED3_PIN, GPIO_Mode_Out_PP_Low_Slow);  // set as output and PP Low level
	GPIO_Init(LED4_PORT, LED4_PIN, GPIO_Mode_Out_PP_Low_Slow);  // set as output and PP Low level
	GPIO_Init(LED5_PORT, LED5_PIN, GPIO_Mode_Out_PP_Low_Slow);  // set as output and PP Low level
#endif
}


#if(_LED_Control_Reverse_With_Lo_LEVEL_Turn_ON_ == 1)
void _Device_Set_Led_OnOff_By_BITs(unsigned char LEDNumBits)
{
    set_Light_LED_BITS = LEDNumBits;
        // turn on , set lo
        // turn off , set hi
        if(LEDNumBits & LED1_BIT){
            GPIO_LOW(LED1_PORT, LED1_PIN);
        }else{
            GPIO_HIGH(LED1_PORT, LED1_PIN);
        }
        if(LEDNumBits & LED2_BIT){
            GPIO_LOW(LED2_PORT, LED2_PIN);
        }else{
            GPIO_HIGH(LED2_PORT, LED2_PIN);
        }
        if(LEDNumBits & LED3_BIT){
            GPIO_LOW(LED3_PORT, LED3_PIN);
        }else{
            GPIO_HIGH(LED3_PORT, LED3_PIN);
        }
        if(LEDNumBits & LED4_BIT){
            GPIO_LOW(LED4_PORT, LED4_PIN);
        }else{
            GPIO_HIGH(LED4_PORT, LED4_PIN);
        }
        if(LEDNumBits & LED5_BIT){
            GPIO_LOW(LED5_PORT, LED5_PIN);
        }else{
            GPIO_HIGH(LED5_PORT, LED5_PIN);
        }
}

void _Device_Set_Led_Pin_OnOff(unsigned char LEDNum, unsigned char Device_Enable)
{
    if(Device_Enable == DeviceOn){
        // turn on , set lo
        if(LEDNum == LED1_Num){
            GPIO_LOW(LED1_PORT, LED1_PIN);
        }else if (LEDNum == LED2_Num){
            GPIO_LOW(LED2_PORT, LED2_PIN);
        }else if (LEDNum == LED3_Num){
            GPIO_LOW(LED3_PORT, LED3_PIN);
        }else if (LEDNum == LED4_Num){
            GPIO_LOW(LED4_PORT, LED4_PIN);
        }else if (LEDNum == LED5_Num){
            GPIO_LOW(LED5_PORT, LED5_PIN);
        }
    }else{
        // turn off , set hi
        if(LEDNum == LED1_Num){
            GPIO_HIGH(LED1_PORT, LED1_PIN);
        }else if (LEDNum == LED2_Num){
            GPIO_HIGH(LED2_PORT, LED2_PIN);
        }else if (LEDNum == LED3_Num){
            GPIO_HIGH(LED3_PORT, LED3_PIN);
        }else if (LEDNum == LED4_Num){
            GPIO_HIGH(LED4_PORT, LED4_PIN);
        }else if (LEDNum == LED5_Num){
            GPIO_HIGH(LED5_PORT, LED5_PIN);
        }
    }
}
#else
void _Device_Set_Led_OnOff_By_BITs(unsigned char LEDNumBits)
{
    set_Light_LED_BITS = LEDNumBits;
        // turn on , set high
        // turn off , set low
        if(LEDNumBits & LED1_BIT){
            GPIO_HIGH(LED1_PORT, LED1_PIN);
        }else{
            GPIO_LOW(LED1_PORT, LED1_PIN);
        }
        if(LEDNumBits & LED2_BIT){
            GPIO_HIGH(LED2_PORT, LED2_PIN);
        }else{
            GPIO_LOW(LED2_PORT, LED2_PIN);
        }
        if(LEDNumBits & LED3_BIT){
            GPIO_HIGH(LED3_PORT, LED3_PIN);
        }else{
            GPIO_LOW(LED3_PORT, LED3_PIN);
        }
        if(LEDNumBits & LED4_BIT){
            GPIO_HIGH(LED4_PORT, LED4_PIN);
        }else{
            GPIO_LOW(LED4_PORT, LED4_PIN);
        }
        if(LEDNumBits & LED5_BIT){
            GPIO_HIGH(LED5_PORT, LED5_PIN);
        }else{
            GPIO_LOW(LED5_PORT, LED5_PIN);
        }
}

void _Device_Set_Led_Pin_OnOff(unsigned char LEDNum, unsigned char Device_Enable)
{
    if(Device_Enable == DeviceOn){
        // turn on , set high
        if(LEDNum == LED1_Num){
            GPIO_HIGH(LED1_PORT, LED1_PIN);
        }else if (LEDNum == LED2_Num){
            GPIO_HIGH(LED2_PORT, LED2_PIN);
        }else if (LEDNum == LED3_Num){
            GPIO_HIGH(LED3_PORT, LED3_PIN);
        }else if (LEDNum == LED4_Num){
            GPIO_HIGH(LED4_PORT, LED4_PIN);
        }else if (LEDNum == LED5_Num){
            GPIO_HIGH(LED5_PORT, LED5_PIN);
        }
    }else{
        // turn off , set low
        if(LEDNum == LED1_Num){
            GPIO_LOW(LED1_PORT, LED1_PIN);
        }else if (LEDNum == LED2_Num){
            GPIO_LOW(LED2_PORT, LED2_PIN);
        }else if (LEDNum == LED3_Num){
            GPIO_LOW(LED3_PORT, LED3_PIN);
        }else if (LEDNum == LED4_Num){
            GPIO_LOW(LED4_PORT, LED4_PIN);
        }else if (LEDNum == LED5_Num){
            GPIO_LOW(LED5_PORT, LED5_PIN);
        }
    }
}
#endif

//void _Device_Set_Led_PWM_Enable(unsigned char enable){
//    if(enable){
//        _Device_Set_Timer1_PWM_Config_Enable(DeviceOn);
//        _Device_Set_Timer2_PWM_Config_Enable(DeviceOn);
//    }else{
//        _Device_Set_Timer1_PWM_Config_Enable(DeviceOff);
//        _Device_Set_Timer2_PWM_Config_Enable(DeviceOff);
//        _Device_Init_Led_Function();
//    }
//    set_PWM_LED_BITS = 0;
//}
void _Device_Set_Led_PWM_Channel_Bits_Enable(unsigned char LEDNumBits){
    if(LEDNumBits == 0){
        _Device_Set_Timer1_PWM_Config_Enable(DeviceOff);
        _Device_Set_Timer2_PWM_Config_Enable(DeviceOff);
        _Device_Init_Led_Function();
        set_PWM_LED_BITS = 0;
        //set_PWM_Duty_Steps = 0;
    }else{
        _Device_Set_Timer1_PWM_Config_Enable(DeviceOn);
        _Device_Set_Timer2_PWM_Config_Enable(DeviceOn);
        set_PWM_LED_BITS = LEDNumBits;
    }
        if(LEDNumBits & LED1_BIT){
            _Device_Set_Timer1_Channel_1_PWM(DeviceOn);
        }else{
            _Device_Set_Timer1_Channel_1_PWM(DeviceOff);
        }
        if(LEDNumBits & LED2_BIT){
            _Device_Set_Timer1_Channel_2_PWM(DeviceOn);
        }else{
            _Device_Set_Timer1_Channel_2_PWM(DeviceOff);
        }
        if(LEDNumBits & LED3_BIT){
            _Device_Set_Timer1_Channel_3_PWM(DeviceOn);
        }else{
            _Device_Set_Timer1_Channel_3_PWM(DeviceOff);
        }
        if(LEDNumBits & LED4_BIT){
            _Device_Set_Timer2_Channel_1_PWM(DeviceOn);
        }else{
            _Device_Set_Timer2_Channel_1_PWM(DeviceOff);
        }
        if(LEDNumBits & LED5_BIT){
            _Device_Set_Timer2_Channel_2_PWM(DeviceOn);
        }else{
            _Device_Set_Timer2_Channel_2_PWM(DeviceOff);
        }
}
void _Device_Set_Led_PWM_Change_Duty(unsigned char LEDNumBits, unsigned int duty){
        if(LEDNumBits & LED1_BIT){
            _Device_Set_Timer1_Channel_1_PWM_Duty(duty);
        }
        if(LEDNumBits & LED2_BIT){
            _Device_Set_Timer1_Channel_2_PWM_Duty(duty);
        }
        if(LEDNumBits & LED3_BIT){
            _Device_Set_Timer1_Channel_3_PWM_Duty(duty);
        }
        if(LEDNumBits & LED4_BIT){
            _Device_Set_Timer2_Channel_1_PWM_Duty(duty);
        }
        if(LEDNumBits & LED5_BIT){
            _Device_Set_Timer2_Channel_2_PWM_Duty(duty);
        }
}

unsigned char _Device_Get_Last_PWM_LED_Bit_By_LED_NUMs(unsigned char ShowingNumOfLeds){
    unsigned int bit;
    if((ShowingNumOfLeds == 0)|| (ShowingNumOfLeds > MAX_LED_NUM)){
        return 0;
    }
    bit = 1;
    bit = bit << (ShowingNumOfLeds - 1);
    return bit;
}
unsigned char _Device_Get_LED_Bit_Without_PWM_Bit_By_LED_NUMs(unsigned char ShowingNumOfLeds){
    return (_Device_Get_Last_PWM_LED_Bit_By_LED_NUMs(ShowingNumOfLeds) - 1);
}

unsigned char _Device_Get_LED_Bit_By_LED_NUMs(unsigned char ShowingNumOfLeds){
    unsigned int bit_temp, bit;
    unsigned int i;
    if((ShowingNumOfLeds == 0)|| (ShowingNumOfLeds > MAX_LED_NUM)){
        return 0;
    }
    if(ShowingNumOfLeds == 1){
        return 0;
    }
    bit = 0;
    for(i = 0; i < (ShowingNumOfLeds); i++){
        bit_temp = 1;
        bit_temp = bit_temp << i;
        bit |= bit_temp;
    }
    return bit;
}
//unsigned char _Device_Get_LED_Bit_Without_PWM_Bit(unsigned char ShowingNumOfLeds){
//    unsigned int bit_temp, bit;
//    unsigned int i;
//    if((ShowingNumOfLeds == 0)|| (ShowingNumOfLeds > MAX_LED_NUM)){
//        return 0;
//    }
//    if(ShowingNumOfLeds == 1){
//        return 0;
//    }
//    bit = 0;
//    for(i = 0; i < (ShowingNumOfLeds - 1); i++){
//        bit_temp = 1;
//        bit_temp = bit_temp << i;
//        bit |= bit_temp;
//    }
//    return bit;
//}

void set_Breathing_Light_LED_For_Timer(){
    if(set_PWM_Duty_Steps >= PWM_FREQ_STEP_POINTS){
        set_PWM_Duty_Steps = 0;
    }
    _Device_Set_Led_PWM_Change_Duty(set_PWM_LED_BITS, PWM_Freq_Scaler_Duty[set_PWM_Duty_Steps]);
    set_PWM_Duty_Steps++;
}

void _Device_Set_Breathing_Light_LED_BIT( unsigned char PWM_Led_Bit ){
    _Device_Remove_Timer4_Interrupt_Timer_Calling_Function(0);
    _Device_Set_Led_PWM_Channel_Bits_Enable(0); //turn All PWM OFF
    if(PWM_Led_Bit == 0){
        return;
    }
    _Device_Set_Led_PWM_Channel_Bits_Enable(PWM_Led_Bit);
    _Device_Set_Timer4_Interrupt_Timer_Calling_Function_With_Delay_And_Exec(0,   set_Breathing_Light_LED_For_Timer , BREATHING_LIGHT_EACH_STEP_INTERVAL_MS);
}
void set_Blinking_LED_For_Timer(){
    unsigned char temp_bit;

    if(blink_XOR_Flag & 0x01){
        //turn off Blink_LED_BITS
        temp_bit = ~set_Blink_LED_BITS;
        temp_bit = set_Light_LED_BITS & temp_bit;   // clear Blink_LED_BITS from Light_LED_BITS and keep other status
    }else{
        //turn on Blink_LED_BITS
        temp_bit = set_Light_LED_BITS | set_Blink_LED_BITS;   // set Blink_LED_BITS to Light_LED_BITS and keep other status
    }
    _Device_Set_Led_OnOff_By_BITs(temp_bit);
    blink_XOR_Flag ^= 0x01;
}

void _Device_Set_Blinking_Light_LED_BIT( unsigned char Blink_Led_Bit ){
    unsigned char temp_bit;

    _Device_Remove_Timer4_Interrupt_Timer_Calling_Function(1);

    //turn off orginal Blink LED Bits
    temp_bit = ~set_Blink_LED_BITS;
    temp_bit = set_Light_LED_BITS & temp_bit;   // clear Blink_LED_BITS from Light_LED_BITS and keep other status
    _Device_Set_Led_OnOff_By_BITs(temp_bit); //keep all status and turn off Blink_LED_BITS

    if(Blink_Led_Bit == 0){
        return;
    }
    set_Blink_LED_BITS = Blink_Led_Bit;
    blink_XOR_Flag = 0;

    _Device_Set_Timer4_Interrupt_Timer_Calling_Function_With_Delay_And_Exec(1,   set_Blinking_LED_For_Timer , BLINKING_LIGHT_INTERVAL_MS);
}

#if (_USE_TOUCH_KEY_WITH_LED_ == 1)
static unsigned char TOUCH_KEY_Led_Light_Status;
static unsigned int TOUCH_KEY_Led_Light_Count;

void _Device_Init_TOUCH_KEY_Led_Function(void){
    TOUCH_KEY_Led_Light_Status = false;
    GPIO_Init(TOUCH_KEY_LED_PORT, TOUCH_KEY_LED_PIN, GPIO_Mode_Out_PP_Low_Slow);  // set as output and PP Low level
    TOUCH_KEY_Led_Light_Count = 0;
}
void _Device_Set_TOUCH_KEY_Led_OnOff(unsigned char Device_Enable){
    if(Device_Enable == DeviceOn){
        GPIO_HIGH(TOUCH_KEY_LED_PORT, TOUCH_KEY_LED_PIN);
    }else{
        GPIO_LOW(TOUCH_KEY_LED_PORT, TOUCH_KEY_LED_PIN);
    }
}

void set_TOUCH_KEY_LED_Blinking_For_Timer(){
    if(TOUCH_KEY_Led_Light_Status){
        //led turn off
        TOUCH_KEY_Led_Light_Count++;
        GPIO_LOW(TOUCH_KEY_LED_PORT, TOUCH_KEY_LED_PIN);
        if(TOUCH_KEY_Led_Light_Count >= TOUCH_KEY_LED_BLINKING_LIGHT_Turn_Off_INTERVAL_MS){
            TOUCH_KEY_Led_Light_Status = false;
            TOUCH_KEY_Led_Light_Count = 0;
        }
    }else{
        //led turn on
        TOUCH_KEY_Led_Light_Count++;
        GPIO_HIGH(TOUCH_KEY_LED_PORT, TOUCH_KEY_LED_PIN);
        if(TOUCH_KEY_Led_Light_Count >= TOUCH_KEY_LED_BLINKING_LIGHT_Turn_On_INTERVAL_MS){
            TOUCH_KEY_Led_Light_Status = true;
            TOUCH_KEY_Led_Light_Count = 0;
        }
    }
}
void _Device_Set_TOUCH_KEY_LED_Blinking( unsigned char Device_Enable ){
    if(Device_Enable == DeviceOn){
        _Device_Set_Timer4_Interrupt_Timer_Calling_Function_With_Delay_And_Exec(3,   set_TOUCH_KEY_LED_Blinking_For_Timer , 1);
    }else{
        _Device_Remove_Timer4_Interrupt_Timer_Calling_Function(3);
        _Device_Init_TOUCH_KEY_Led_Function();
    }
}

#endif
/******************* (C) COPYRIGHT 2012 Dynapack *****END OF FILE****/

