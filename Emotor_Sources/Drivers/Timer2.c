/**
  ******************************************************************************
  * @file    Timer2.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   Timer2 setting
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
  * @brief  Configure TIM2 peripheral
  * @param  None
  * @retval None
  */
void _Device_TIM2_Config(void)
{
    TIM2_DeInit();
#if(_LED_Control_Reverse_With_Lo_LEVEL_Turn_ON_ == 1)
    /* GPIO configuration: TIM2 channel 1 (PB0)(LED4) and  channel 2 (PB2)(LED5) */
    GPIO_Init(LED4_PORT, LED4_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
    GPIO_Init(LED5_PORT, LED5_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
#else
    /* GPIO configuration: TIM2 channel 1 (PB0)(LED4) and  channel 2 (PB2)(LED5) */
	GPIO_Init(LED4_PORT, LED4_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
	GPIO_Init(LED5_PORT, LED5_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
#endif
  /*
  - TIM2CLK = 4 MHz
  - TIM2_PRESCALER = TIM2_Prescaler_2
  - TIM2 counter clock(freq) = TIM1CLK / TIM2_PRESCALER = 2 MHz
  - TIM2_Period = 7999
  - TIM2 Channel output frequency = TIM2 counter clock / (TIM2 Period+1) = 250Hz

  ==> example for TIM2 configuration:
    - TIM2CLK is set to 4 MHz,
    - the TIM2 Prescaler is equal to 2,
    - so the TIM2 counter clock used is 4 MHz / 2 =  2 MHz
    - then set the TIM2_PERIOD is equal to 7999,
    - TIM1 Channel 1 output frequency   = TIM2 counter clock / (TIM2_PERIOD + 1)
                                        = 2 000 000 / (7999 + 1) = 250 Hz
  */

  /* Enable TIM2 clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);

  /* Time Base configuration */
  TIM2_TimeBaseInit(TIM2_PRESCALER, TIM2_CounterMode_Up, TIM2_PERIOD);

//  /* TIM2 Channel 1 Configuration in PWM1 mode */
//  TIM2_OC1Init(TIM2_OCMode_PWM1, TIM2_OutputState_Enable, _Init_TIM2_Duty_Values_,
//               TIM2_OCPolarity_High, TIM2_OCIdleState_Reset);
//  /* TIM2 Channel 2 Configuration in PWM1 mode */
//  TIM2_OC2Init(TIM2_OCMode_PWM1, TIM2_OutputState_Enable, _Init_TIM2_Duty_Values_,
//               TIM2_OCPolarity_High, TIM2_OCIdleState_Reset);


  /* TIM2 Main Output Enable */
  TIM2_CtrlPWMOutputs(ENABLE);

  /* TIM2 counter enable */
  TIM2_Cmd(ENABLE);
}

void _Device_Set_Timer2_PWM_Config_Enable(uint8_t enable)
{
    if(enable){
        _Device_TIM2_Config();
//        /* TIM2 Main Output Enable */
//        TIM2_CtrlPWMOutputs(ENABLE);
//        /* Enable TIM2 */
//        TIM2_Cmd(ENABLE);
    }else{
        /* TIM2 Main Output Disable */
        TIM2_CtrlPWMOutputs(DISABLE);
        /* Disable TIM2 */
        TIM2_Cmd(DISABLE);
        /* Enable TIM2 clock */
        CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, DISABLE);
        TIM2_DeInit();
#if(_LED_Control_Reverse_With_Lo_LEVEL_Turn_ON_ == 1)
        /* GPIO configuration: TIM2 channel 1 (PB0)(LED4) and  channel 2 (PB2)(LED5) */
        GPIO_Init(LED4_PORT, LED4_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
        GPIO_Init(LED5_PORT, LED5_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
#else
        /* GPIO configuration: TIM2 channel 1 (PB0)(LED4) and  channel 2 (PB2)(LED5) */
        GPIO_Init(LED4_PORT, LED4_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
        GPIO_Init(LED5_PORT, LED5_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
#endif
    }
}

void _Device_Set_Timer2_Channel_1_PWM(uint8_t enable)
{
    if(enable){
        /* TIM2 Channel 1 Configuration in PWM1 mode */
        TIM2_OC1Init(TIM2_OCMode_PWM1, TIM2_OutputState_Enable, _Init_TIM2_Duty_Values_,
                   TIM2_OCPolarity_High, TIM2_OCIdleState_Reset);
    }else{
        /* Disable the Channel 1: Reset the CCE Bit */
        TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC1E);
        /* Reset the Output Compare Bits */
        TIM2->CCMR1 &= (uint8_t)(~TIM_CCMR_OCM);
#if(_LED_Control_Reverse_With_Lo_LEVEL_Turn_ON_ == 1)
        /* GPIO configuration: TIM2 channel 1 (PB0)(LED4) and  channel 2 (PB2)(LED5) */
        GPIO_Init(LED4_PORT, LED4_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
#else
        /* GPIO configuration: TIM2 channel 1 (PB0)(LED4) and  channel 2 (PB2)(LED5) */
        GPIO_Init(LED4_PORT, LED4_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
#endif
    }
}
void _Device_Set_Timer2_Channel_1_PWM_Duty(uint16_t duty_value)
{
    /* Set the Pulse value */
    TIM2->CCR1H = (uint8_t)(duty_value >> 8);
    TIM2->CCR1L = (uint8_t)(duty_value);
}
void _Device_Set_Timer2_Channel_2_PWM(uint8_t enable)
{
    if(enable){
        /* TIM2 Channel 2 Configuration in PWM1 mode */
        TIM2_OC2Init(TIM2_OCMode_PWM1, TIM2_OutputState_Enable, _Init_TIM2_Duty_Values_,
                   TIM2_OCPolarity_High, TIM2_OCIdleState_Reset);
    }else{
        /* Disable the Channel 2: Reset the CCE Bit */
        TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC2E);
        /* Reset the Output Compare Bits */
        TIM2->CCMR2 &= (uint8_t)(~TIM_CCMR_OCM);
#if(_LED_Control_Reverse_With_Lo_LEVEL_Turn_ON_ == 1)
        /* GPIO configuration: TIM2 channel 1 (PB0)(LED4) and  channel 2 (PB2)(LED5) */
        GPIO_Init(LED5_PORT, LED5_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
#else
        /* GPIO configuration: TIM2 channel 1 (PB0)(LED4) and  channel 2 (PB2)(LED5) */
        GPIO_Init(LED5_PORT, LED5_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
#endif
    }
}
void _Device_Set_Timer2_Channel_2_PWM_Duty(uint16_t duty_value)
{
    /* Set the Pulse value */
    TIM2->CCR2H = (uint8_t)(duty_value >> 8);
    TIM2->CCR2L = (uint8_t)(duty_value);
}


