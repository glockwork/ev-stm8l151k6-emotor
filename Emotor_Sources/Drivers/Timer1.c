/**
  ******************************************************************************
  * @file    Timer1.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   Timer1 setting
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

/**
  * @brief  Configure TIM1 peripheral
  * @param  None
  * @retval None
  */
void _Device_TIM1_Config(void)
{
    TIM1_DeInit();
#if(_LED_Control_Reverse_With_Lo_LEVEL_Turn_ON_ == 1)
    /* GPIO configuration: TIM1 channel 1 (PD2)(LED1), channel 2 (PD4)(LED2) and channel 3 (PD5)(LED3) */
	GPIO_Init(LED1_PORT, LED1_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
	GPIO_Init(LED2_PORT, LED2_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
	GPIO_Init(LED3_PORT, LED3_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
#else
    /* GPIO configuration: TIM1 channel 1 (PD2)(LED1), channel 2 (PD4)(LED2) and channel 3 (PD5)(LED3) */
	GPIO_Init(LED1_PORT, LED1_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
	GPIO_Init(LED2_PORT, LED2_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
	GPIO_Init(LED3_PORT, LED3_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
#endif
  /*
  - TIM1CLK = 4 MHz
  - TIM1_PRESCALER = 1
  - TIM1 counter clock(freq) = TIM1CLK / (TIM1_PRESCALER+1) = 2 MHz
  - TIM1_Period = 7999
  - TIM1 Channel output frequency = TIM1 counter clock / (TIM1 Period+1) = 250Hz

  ==> example for TIM1 configuration:
    - TIM1CLK is set to 4 MHz,
    - the TIM2 Prescaler is equal to 2,
    - so the TIM1 counter clock used is 4 MHz / (2 + 1) = 2 MHz
    - then set the TIM1_PERIOD is equal to 7999,
    - TIM1 Channel 1 output frequency   = TIM1 counter clock / (TIM1_PERIOD + 1)
                                        = 2 000 000 / (7999 + 1) = 250 Hz
  */

  /* Enable TIM1 clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM1, ENABLE);

  /* Time Base configuration */
  TIM1_TimeBaseInit(TIM1_PRESCALER, TIM1_CounterMode_Up, TIM1_PERIOD, TIM1_REPTETION_COUNTER);

//  /* TIM1 Channel 1 Configuration in PWM1 mode */
//  TIM1_OC1Init(TIM1_OCMode_PWM1, TIM1_OutputState_Enable, TIM1_OutputNState_Disable, _Init_TIM1_Duty_Values_,
//               TIM1_OCPolarity_High, TIM1_OCNPolarity_Low, TIM1_OCIdleState_Set, TIM1_OCNIdleState_Set);
//
//  /* TIM1 Channel 2 Configuration in PWM1 mode */
//  TIM1_OC2Init(TIM1_OCMode_PWM1, TIM1_OutputState_Enable, TIM1_OutputNState_Disable, _Init_TIM1_Duty_Values_,
//               TIM1_OCPolarity_High, TIM1_OCNPolarity_Low, TIM1_OCIdleState_Set, TIM1_OCNIdleState_Set);
//  /* TIM1 Channel 3 Configuration in PWM1 mode */
//  TIM1_OC3Init(TIM1_OCMode_PWM1, TIM1_OutputState_Enable, TIM1_OutputNState_Disable, _Init_TIM1_Duty_Values_,
//               TIM1_OCPolarity_High, TIM1_OCNPolarity_Low, TIM1_OCIdleState_Set, TIM1_OCNIdleState_Set);

  /* TIM1 Main Output Enable */
  TIM1_CtrlPWMOutputs(ENABLE);

  /* TIM1 counter enable */
  TIM1_Cmd(ENABLE);

}

void _Device_Set_Timer1_PWM_Config_Enable(uint8_t enable)
{
    if(enable){
        _Device_TIM1_Config();
//        /* TIM1 Main Output Enable */
//        TIM1_CtrlPWMOutputs(ENABLE);
//        /* Enable TIM1 */
//        TIM1_Cmd(ENABLE);
    }else{
        /* TIM1 Main Output Disable */
        TIM1_CtrlPWMOutputs(DISABLE);
        /* Disable TIM1 */
        TIM1_Cmd(DISABLE);
        /* Enable TIM1 clock */
        CLK_PeripheralClockConfig(CLK_Peripheral_TIM1, DISABLE);

        TIM1_DeInit();
#if(_LED_Control_Reverse_With_Lo_LEVEL_Turn_ON_ == 1)
        /* GPIO configuration: TIM1 channel 1 (PD2)(LED1), channel 2 (PD4)(LED2) and channel 3 (PD5)(LED3) */
        GPIO_Init(LED1_PORT, LED1_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
        GPIO_Init(LED2_PORT, LED2_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
        GPIO_Init(LED3_PORT, LED3_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
#else
        /* GPIO configuration: TIM1 channel 1 (PD2)(LED1), channel 2 (PD4)(LED2) and channel 3 (PD5)(LED3) */
        GPIO_Init(LED1_PORT, LED1_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
        GPIO_Init(LED2_PORT, LED2_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
        GPIO_Init(LED3_PORT, LED3_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
#endif
    }
}
void _Device_Set_Timer1_Channel_1_PWM(uint8_t enable)
{
    if(enable){
        /* TIM1 Channel 1 Configuration in PWM1 mode */
        TIM1_OC1Init(TIM1_OCMode_PWM1, TIM1_OutputState_Enable, TIM1_OutputNState_Disable, _Init_TIM1_Duty_Values_,
                   TIM1_OCPolarity_High, TIM1_OCNPolarity_Low, TIM1_OCIdleState_Set, TIM1_OCNIdleState_Set);
    }else{
        /* Disable the Channel 1: Reset the CCE Bit, Set the Output State ,
        the Output N State, the Output Polarity & the Output N Polarity*/
        TIM1->CCER1 &= (uint8_t)(~(TIM1_CCER1_CC1E | TIM1_CCER1_CC1NE  | TIM1_CCER1_CC1P | TIM1_CCER1_CC1NP));
        /* Reset the Output Compare Bits & Set the Output Compare Mode */
        TIM1->CCMR1 = (uint8_t)(TIM1->CCMR1 & (uint8_t)(~TIM1_CCMR_OCM));
#if(_LED_Control_Reverse_With_Lo_LEVEL_Turn_ON_ == 1)
        /* GPIO configuration: TIM1 channel 1 (PD2)(LED1), channel 2 (PD4)(LED2) and channel 3 (PD5)(LED3) */
        GPIO_Init(LED1_PORT, LED1_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
#else
        /* GPIO configuration: TIM1 channel 1 (PD2)(LED1), channel 2 (PD4)(LED2) and channel 3 (PD5)(LED3) */
        GPIO_Init(LED1_PORT, LED1_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
#endif
    }
}

void _Device_Set_Timer1_Channel_1_PWM_Duty(uint16_t duty_value)
{
    /* Set the Pulse value */
    TIM1->CCR1H = (uint8_t)(duty_value >> 8);
    TIM1->CCR1L = (uint8_t)(duty_value);
}
void _Device_Set_Timer1_Channel_2_PWM(uint8_t enable)
{
    if(enable){
        /* TIM1 Channel 2 Configuration in PWM1 mode */
        TIM1_OC2Init(TIM1_OCMode_PWM1, TIM1_OutputState_Enable, TIM1_OutputNState_Disable, _Init_TIM1_Duty_Values_,
                   TIM1_OCPolarity_High, TIM1_OCNPolarity_Low, TIM1_OCIdleState_Set, TIM1_OCNIdleState_Set);
    }else{
        /* Disable the Channel 2: Reset the CCE Bit, Set the Output State,
         the Output N State, the Output Polarity & the Output N Polarity*/
        TIM1->CCER1 &= (uint8_t)(~(TIM1_CCER1_CC2E | TIM1_CCER1_CC2NE | TIM1_CCER1_CC2P | TIM1_CCER1_CC2NP));
        /* Reset the Output Compare Bits & Set the Output Compare Mode */
        TIM1->CCMR2 = (uint8_t)(TIM1->CCMR2 & (uint8_t)(~TIM1_CCMR_OCM));
#if(_LED_Control_Reverse_With_Lo_LEVEL_Turn_ON_ == 1)
        /* GPIO configuration: TIM1 channel 1 (PD2)(LED1), channel 2 (PD4)(LED2) and channel 3 (PD5)(LED3) */
        GPIO_Init(LED2_PORT, LED2_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
#else
        /* GPIO configuration: TIM1 channel 1 (PD2)(LED1), channel 2 (PD4)(LED2) and channel 3 (PD5)(LED3) */
        GPIO_Init(LED2_PORT, LED2_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
#endif
    }
}
void _Device_Set_Timer1_Channel_2_PWM_Duty(uint16_t duty_value)
{
    /* Set the Pulse value */
    TIM1->CCR2H = (uint8_t)(duty_value >> 8);
    TIM1->CCR2L = (uint8_t)(duty_value);
}
void _Device_Set_Timer1_Channel_3_PWM(uint8_t enable)
{
    if(enable){
        /* TIM1 Channel 3 Configuration in PWM1 mode */
        TIM1_OC3Init(TIM1_OCMode_PWM1, TIM1_OutputState_Enable, TIM1_OutputNState_Disable, _Init_TIM1_Duty_Values_,
                   TIM1_OCPolarity_High, TIM1_OCNPolarity_Low, TIM1_OCIdleState_Set, TIM1_OCNIdleState_Set);
    }else{
        /* Disable the Channel 3: Reset the CCE Bit, Set the Output State,
         the Output N State, the Output Polarity & the Output N Polarity */
        TIM1->CCER2 &= (uint8_t)(~( TIM1_CCER2_CC3E | TIM1_CCER2_CC3NE | TIM1_CCER2_CC3P | TIM1_CCER2_CC3NP));
        /* Reset the Output Compare Bits & Set the Output Compare Mode */
        TIM1->CCMR3 = (uint8_t)(TIM1->CCMR3 & (uint8_t)(~TIM1_CCMR_OCM));
#if(_LED_Control_Reverse_With_Lo_LEVEL_Turn_ON_ == 1)
        /* GPIO configuration: TIM1 channel 1 (PD2)(LED1), channel 2 (PD4)(LED2) and channel 3 (PD5)(LED3) */
        GPIO_Init(LED3_PORT, LED3_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
#else
        /* GPIO configuration: TIM1 channel 1 (PD2)(LED1), channel 2 (PD4)(LED2) and channel 3 (PD5)(LED3) */
        GPIO_Init(LED3_PORT, LED3_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
#endif
    }
}
void _Device_Set_Timer1_Channel_3_PWM_Duty(uint16_t duty_value)
{
    /* Set the Pulse value */
    TIM1->CCR3H = (uint8_t)(duty_value >> 8);
    TIM1->CCR3L = (uint8_t)(duty_value);
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//#if 0
///**
//  * @brief  Configure TIM1 peripheral
//  * @param  None
//  * @retval None
//  */
//void _Device_TIM1_Config(void)
//{
//    /* GPIO configuration: TIM1 channel 1 (PD2)(LED1), channel 2 (PD4)(LED2) and channel 3 (PD5)(LED3) */
//    /* GPIO configuration: TIM2 channel 1 (PB0)(LED4) and  channel 2 (PB2)(LED5) */
//	GPIO_Init(LED1_PORT, LED1_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
//	GPIO_Init(LED2_PORT, LED2_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
//	GPIO_Init(LED3_PORT, LED3_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
//	GPIO_Init(LED4_PORT, LED4_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
//	GPIO_Init(LED5_PORT, LED5_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
//
//  /*
//  - TIM1CLK = 2 MHz
//  - TIM1 counter clock = TIM1CLK / TIM1_PRESCALER+1 = 2 MHz/1+1 = 1 MHz
//  */
//  /* Time base configuration */
//  TIM1_TimeBaseInit(TIM1_PRESCALER, TIM1_CounterMode_Up, TIM1_PERIOD, TIM1_REPTETION_COUNTER);
//
//  /*
//  - The TIM1 CCR1 register value is equal to 32768:
//  - CC1 update rate = TIM1 counter clock / CCR1_Val = 30.51 Hz,
//  - So the TIM1 Channel 1 generates a periodic signal with a frequency equal to 15.25 Hz.
//  */
//  /* Toggle Mode configuration: Channel1 */
//  TIM1_OC1Init(TIM1_OCMode_Toggle, TIM1_OutputState_Enable, TIM1_OutputNState_Disable,
//               CCR1_Val, TIM1_OCPolarity_Low, TIM1_OCNPolarity_Low, TIM1_OCIdleState_Set,
//               TIM1_OCNIdleState_Set);
//  TIM1_OC1PreloadConfig(DISABLE);
//
//  /*
//  - The TIM1 CCR2 register is equal to 16384:
//  - CC2 update rate = TIM1 counter clock / CCR2_Val = 61.03 Hz
//  - So the TIM1 channel 2 generates a periodic signal with a frequency equal to 30.51 Hz.
//  */
//  /* Toggle Mode configuration: Channel2 */
//  TIM1_OC2Init(TIM1_OCMode_Toggle, TIM1_OutputState_Enable, TIM1_OutputNState_Disable,
//               CCR2_Val, TIM1_OCPolarity_Low, TIM1_OCNPolarity_Low, TIM1_OCIdleState_Set,
//               TIM1_OCNIdleState_Set);
//  TIM1_OC2PreloadConfig(DISABLE);
//
//  /*
//  -The TIM1 CCR3 register is equal to 8192:
//  - CC3 update rate = TIM1 counter clock / CCR3_Val = 123.01 Hz
//  - So the TIM1 channel 3 generates a periodic signal with a frequency equal to 61.5 Hz.
//  */
//  /* Toggle Mode configuration: Channel3 */
//  TIM1_OC3Init(TIM1_OCMode_Toggle, TIM1_OutputState_Enable, TIM1_OutputNState_Disable,
//               CCR3_Val, TIM1_OCPolarity_Low, TIM1_OCNPolarity_Low, TIM1_OCIdleState_Set,
//               TIM1_OCNIdleState_Set);
//  TIM1_OC3PreloadConfig(DISABLE);
//
//  TIM1_ARRPreloadConfig(ENABLE);
//
//  /* TIM1 Interrupt enable */
//  TIM1_ITConfig(TIM1_IT_CC1, ENABLE);
//  TIM1_ITConfig(TIM1_IT_CC2, ENABLE);
//  TIM1_ITConfig(TIM1_IT_CC3, ENABLE);
//
//  /* Enable TIM1 outputs */
//  TIM1_CtrlPWMOutputs(ENABLE);
//  /* TIM1 enable counter */
//  TIM1_Cmd(ENABLE);
//}
//void _Device_Set_Timer1_Enable(uint8_t enable)
//{
//    if(enable){
//        /* Enable TIM1 */
//        TIM1_Cmd(ENABLE);
//    }else{
//        /* Disable TIM1 */
//        TIM1_Cmd(DISABLE);
//    }
//}
//
//
///********************************************************************************
//* TIM1_CC_IRQHandler													*
//*******************************************************************************/
///**
//  * @brief TIM1 Capture/Compare Interrupt routine.
//  * @par Parameters:
//  * None
//  * @retval
//  * None
//  */
//#if defined(_IAR_)	
//INTERRUPT_HANDLER(TIM1_CC_IRQHandler,24)
//{
//#endif
//#if defined(_COSMIC_)	
//INTERRUPT void TIM1_CC_IRQHandler(void)
//{
//#endif
//	int i;
//  /* TIM1 channel 1 toggling */
//  if (TIM1_GetITStatus(TIM1_IT_CC1) != RESET)
//  {
//    TIM1_ClearITPendingBit(TIM1_IT_CC1 );
//    Capture = TIM1_GetCapture1();
//    TIM1_SetCompare1(Capture + CCR1_Val);
//  }
//
//  /* TIM1 channel 2 toggling */
//  if (TIM1_GetITStatus(TIM1_IT_CC2) != RESET)
//  {
//    TIM1_ClearITPendingBit(TIM1_IT_CC2);
//    Capture = TIM1_GetCapture2();
//    TIM1_SetCompare2(Capture + CCR2_Val);
//  }
//
//  /* TIM1 channel 3 toggling */
//  if (TIM1_GetITStatus(TIM1_IT_CC3) != RESET)
//  {
//    TIM1_ClearITPendingBit(TIM1_IT_CC3);
//    Capture = TIM1_GetCapture3();
//    TIM1_SetCompare3(Capture + CCR3_Val);
//  }
//}
//
//#endif
