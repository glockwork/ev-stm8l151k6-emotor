/**
  ******************************************************************************
  * @file    Clock_config.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    23-May-2013
  * @brief   system colock setting
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
  * @brief  Configure System Clock
  * @param  None
  * @retval None
  */
void _Device_CLK_Config(void)
{
//  /* Select HSE as system clock source */
//  CLK_SYSCLKSourceSwitchCmd(ENABLE);
//  CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSE);

//  /* system clock prescaler: 1*/
//  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
//  while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_HSE)
//  {}

    CLK_SYSCLKDivConfig(dSourceFreqDivided);//HEI speed 16MHz / 4 = 4MHz, for peripheral device and MCU core
    //CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_8);//HEI speed 16MHz / 8 = 2MHz, for peripheral device and MCU core


//  /* Enable TIM1 clock */
//  CLK_PeripheralClockConfig(CLK_Peripheral_TIM1, ENABLE);
//  /* Enable TIM2 clock */
//  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);
//  /* Enable TIM4 CLK */
//  CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);
//  /* Enable DMA1 clock */
//  CLK_PeripheralClockConfig(CLK_Peripheral_DMA1, ENABLE);
//  /* Enable ADC1 clock */
//  CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);
  /* Enable USART1 clock */
  //CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);


}



void _Device_CLK_Config_Switch_To_HSI_Clock_Source(){

//    /* Switch the clock to HSI */
//    CLK_LSEConfig(CLK_LSE_OFF);
//    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_8);
//    CLK_HSICmd(ENABLE);
//    while (((CLK->ICKCR)& 0x02)!=0x02);
//    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
//    CLK_SYSCLKSourceSwitchCmd(ENABLE);
//    while (((CLK->SWCR)& 0x01)==0x01);
//    delay_ms(100);

    /* Switch to HSI as system clock source */

    CLK_HSEConfig(CLK_HSE_OFF);
    CLK_LSEConfig(CLK_LSE_OFF);
    CLK_LSICmd(DISABLE);

    /* system clock prescaler: */
    //CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//HEI speed 16MHz / 4 = 4MHz, for peripheral device and MCU core
    CLK_SYSCLKDivConfig(dSourceFreqDivided);//HEI speed 16MHz / 4 = 4MHz, for peripheral device and MCU core
    //CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_8);//HEI speed 16MHz / 8 = 2MHz, for peripheral device and MCU core

    CLK_HSICmd(ENABLE);
    while (((CLK->ICKCR)& 0x02)!=0x02);


    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
    CLK_SYSCLKSourceSwitchCmd(ENABLE);
    while (((CLK->SWCR)& 0x01)==0x01);

    while (CLK_GetFlagStatus(CLK_FLAG_HSIRDY) == 0);

    /* Set STM8 in low power */
    PWR_FastWakeUpCmd(DISABLE);
    PWR_UltraLowPowerCmd(ENABLE);
}

void _Device_CLK_Config_Switch_To_LSI_Clock_Source(){

    /* Switch to LSI as system clock source */
   /* system clock prescaler: 1*/
   CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
   CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_LSI);
   CLK_SYSCLKSourceSwitchCmd(ENABLE);
   while (CLK_GetFlagStatus(CLK_FLAG_LSIRDY) == 0);
   CLK_HSICmd(DISABLE);
   CLK_HSEConfig(CLK_HSE_OFF);

    /* Set STM8 in low power */
    PWR_FastWakeUpCmd(DISABLE);
    PWR_UltraLowPowerCmd(ENABLE);
}

/**
  * @brief  Configure RTC peripheral
  * @param  None
  * @retval None
  */
static void _Device_RTC_Config(void)
{
  /* Configures the RTC */
  CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);
  CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);

  RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits);
  RTC_ITConfig(RTC_IT_WUT, ENABLE);

  /* Enable Interrupts*/
  //enableInterrupts();
}

/**
  * @brief  Configure RTC peripheral
  * @param  None
  * @retval None
  */
void _Device_Disable_RTC(void)
{
  /* Configures the RTC */
  //CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);
  CLK_PeripheralClockConfig(CLK_Peripheral_RTC, DISABLE);

  //RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits);
  RTC_ITConfig(RTC_IT_WUT, DISABLE);

  /* Enable Interrupts*/
  //enableInterrupts();
}

void _Device_Active_Halt_Config_With_RTC_WakeUp(){

    _Device_CLK_Config_Switch_To_LSI_Clock_Source();
    _Device_RTC_Config();

    /* RTC will wake-up from (active) halt every 5 second */
    RTC_SetWakeUpCounter(RTC_WakeUp_Second_Times);
    RTC_WakeUpCmd(ENABLE);
}


void _Device_Normal_Config_For_Exit_Halt(){

    RTC_WakeUpCmd(DISABLE);
    _Device_Disable_RTC();

    _Device_CLK_Config_Switch_To_HSI_Clock_Source();
}
/********************************************************************************
* RTC_CSSLSE_IRQHandler										*
*******************************************************************************/
/**
  * @brief RTC / CSS_LSE Interrupt routine.
  * @param  None
  * @retval None
  */
#if defined(_IAR_)	
INTERRUPT_HANDLER(RTC_CSSLSE_IRQHandler, 4)
{
#endif
#if defined(_COSMIC_)	
INTERRUPT void RTC_CSSLSE_IRQHandler(void)
{
#endif

    //GPIO_TOGGLE(LED4_PORT, LED4_PIN);
    //GPIO_HIGH(LED1_PORT, LED1_PIN);
    //GPIO_LOW(LED1_PORT, LED1_PIN);

    //GPIO_TOGGLE(LED2_PORT, LED2_PIN);
    RTC_ClearITPendingBit(RTC_IT_WUT);
    //_Device_delay_cycles(15);     //100 = 1ms at CCLK=4MHz, 15 ~= 150 us
    /* Clear Interrupt pending bit */
}
//void Halt_Init(void)
//{
//   TIM1_Cmd(DISABLE);
//   TIM2_CtrlPWMOutputs(DISABLE);
//   TIM2_Cmd(DISABLE);
//   TIM3_Cmd(DISABLE);
//   TIM4_Cmd(DISABLE);
//   ADC_Cmd(ADC1, DISABLE);
//   PWR_PVDCmd(DISABLE);
//
//   /* Switch to LSI as system clock source */
//   /* system clock prescaler: 1*/
//   CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
//   CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_LSI);
//   CLK_SYSCLKSourceSwitchCmd(ENABLE);
//
//   while (CLK_GetFlagStatus(CLK_FLAG_LSIRDY) == 0);
//   CLK_HSICmd(DISABLE);
//   CLK_HSEConfig(CLK_HSE_OFF);
//
//   /* Set STM8 in low power */
//   PWR_UltraLowPowerCmd(ENABLE);
//
//   /* Set GPIO in low power*/
//   GPIO_LowPower_Config();
//
//   /* Stop RTC Source clock */
//   CLK_RTCClockConfig(CLK_RTCCLKSource_Off, CLK_RTCCLKDiv_1);
//
//   /* Stop clock RTC and LCD */
//   CLK_PeripheralClockConfig(CLK_Peripheral_RTC, DISABLE);
//   CLK_PeripheralClockConfig(CLK_Peripheral_LCD, DISABLE);
//}

/******************* (C) COPYRIGHT 2012 Dynapack *****END OF FILE****/
