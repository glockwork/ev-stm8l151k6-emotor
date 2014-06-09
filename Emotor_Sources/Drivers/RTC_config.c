/**
  ******************************************************************************
  * @file    RTC_config.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   system colock setting
  ******************************************************************************
  * @attention
  *
  * DESCRIPTION....
  *
  * <h2><center>&copy; COPYRIGHT 2012 Dynapack</center></h2>
  ******************************************************************************
  */
#if 0
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
#define RTC_WakeUpCounterValues     1023    // RTC wake-up event every (timer_step x (RTC_WakeUpCounterValues + 1) ) us
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
  * @brief  Configure RTC peripheral
  * @param  None
  * @retval None
  */
void _Device_RTC_Config(void){

    CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
    /* Enable RTC clock */
    CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);
    RTC_DeInit();
    /* Configures the RTC wakeup timer_step = RTCCLK/2 = LSI/2 = 38K / 2 = 52.631 us */
    RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div2);
//    RTC_SetWakeUpCounter(100);
//    RTC_WakeUpCmd(ENABLE);
    /* Enable wake up unit Interrupt */
    RTC_ITConfig(RTC_IT_WUT, ENABLE);

}


void _Device_RTC_Wake_Up_Event_Enable( unsigned char enable){

    if(enable){
        /* RTC wake-up event every 100 ms (timer_step x (1999 + 1) )*/
        RTC_SetWakeUpCounter(1999);
        RTC_WakeUpCmd(ENABLE);
    }else{
        RTC_WakeUpCmd(DISABLE);
    }
}

/********************************************************************************
* RTC_IRQHandler										                        *
*******************************************************************************/
/**
  * @brief RTC Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */

#if defined(_IAR_)	
INTERRUPT_HANDLER(RTC_IRQHandler,4)
{
#endif
#if defined(_COSMIC_)	
INTERRUPT void RTC_IRQHandler(void)
{
#endif

    //GPIO_TOGGLE(LED2_PORT, LED2_PIN);
    //GPIO_HIGH(LED2_PORT, LED2_PIN);
    /* Clear the periodic wakeup unit flag */
    RTC_ClearITPendingBit(RTC_IT_WUT);
    //GPIO_LOW(LED2_PORT, LED2_PIN);
}

#endif
