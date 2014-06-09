/**
  ******************************************************************************
  * @file    Mos_Control.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   Mos FET Control setting
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
#define DSG_MosFET_Control_PORT	        GPIOD
#define DSG_MosFET_Control_PIN	        GPIO_Pin_0

#define CHG_MosFET_Control_PORT	        GPIOD
#define CHG_MosFET_Control_PIN	        GPIO_Pin_1
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
  * @brief  Configure Mos FET Control GPIO peripheral   
  * @param  None
  * @retval None
  */
void _Device_Mos_Control_Init(void){
        GPIO_Init(DSG_MosFET_Control_PORT, DSG_MosFET_Control_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
        GPIO_Init(CHG_MosFET_Control_PORT, CHG_MosFET_Control_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
}

void _Device_DSG_MosFET_Pin_High(){
    DSG_MosFET_Control_PORT->ODR |= DSG_MosFET_Control_PIN;
}
void _Device_DSG_MosFET_Pin_Low(){
    DSG_MosFET_Control_PORT->ODR &= ~DSG_MosFET_Control_PIN;
}

void _Device_CHG_MosFET_Pin_High(){
    CHG_MosFET_Control_PORT->ODR |= CHG_MosFET_Control_PIN;
}
void _Device_CHG_MosFET_Pin_Low(){
    CHG_MosFET_Control_PORT->ODR &= ~CHG_MosFET_Control_PIN;
}


