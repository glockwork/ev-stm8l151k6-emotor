/**
  ******************************************************************************
  * @file    Utility_Functions.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   Utility Functions setting
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
  * @brief  delay_cycles
  * @param  setting cycles
  * @retval None
  */
void _Device_delay_cycles(unsigned long cycleCount)
{
	unsigned long count;
	for(count = 0l; count < cycleCount; count++){
#if defined(_IAR_)	
        asm("nop");
#endif
#if defined(_COSMIC_)	
        _asm("nop");
#endif
	}
}



/**
  * @brief  configure GPIOs before entering low power
	* @caller Halt_Init and ADC_Icc_Test
  * @param None
  * @retval None
  */
void _Device_GPIO_LowPower_Config(void)
{

/* Port A in output push-pull 0 */
  //GPIO_Init(GPIOA,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7 ,GPIO_Mode_Out_PP_Low_Slow);
  GPIO_Init(GPIOA, GPIO_Pin_All ,GPIO_Mode_Out_PP_Low_Slow);
	
/* Port B in output push-pull 0 */
  GPIO_Init(GPIOB, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);

/* Port C in output push-pull 0 except Button pins */
  //GPIO_Init(GPIOC, GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);
//  GPIO_Init(GPIOC, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);
//  GPIO_Init(GPIOC, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Slow);
//  GPIO_Init(GPIOC, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);
//  GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Slow);
//  GPIO_Init(GPIOC, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);
//  GPIO_Init(GPIOC, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);
//  GPIO_Init(GPIOC, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);
//  GPIO_Init(GPIOC, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);
  GPIO_Init(GPIOC, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);

/* Port D in output push-pull 0 */
  //GPIO_Init(GPIOD, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);
  GPIO_Init(GPIOD, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);

/* Port E in output push-pull 0 */
  //GPIO_Init(GPIOE, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);
  GPIO_Init(GPIOE, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);

/* Port F in output push-pull 0 */
/* Not PF0 because Input for ICC measurement */
  //GPIO_Init(GPIOF,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7 ,GPIO_Mode_Out_PP_Low_Slow);
  GPIO_Init(GPIOF, GPIO_Pin_All,GPIO_Mode_Out_PP_Low_Slow);


#if(_LED_Control_Reverse_With_Lo_LEVEL_Turn_ON_ == 1)
    //for low power setting
	GPIO_Init(LED1_PORT, LED1_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
	GPIO_Init(LED2_PORT, LED2_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
	GPIO_Init(LED3_PORT, LED3_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
	GPIO_Init(LED4_PORT, LED4_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
	GPIO_Init(LED5_PORT, LED5_PIN, GPIO_Mode_Out_PP_High_Slow);  // set as output and PP High level
#endif


  //GPIO_Init(GPIOC, GPIO_Pin_1, GPIO_Mode_Out_PP_High_Slow);
}