/**
  ******************************************************************************
  * @file    OptputSignalControl.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   Optput Signal Control setting
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
#define AdapterSOCControl_PORT      GPIOD
#define AdapterSOCControl_PIN       GPIO_Pin_6

#define OneWireControl_PORT	        GPIOD
#define OneWireControl_PIN	        GPIO_Pin_3

#define UartIsolationControl_PORT   GPIOB
#define UartIsolationControl_PIN    GPIO_Pin_1

#define NTC_Control_PORT	        GPIOB
#define NTC_Control_PIN	            GPIO_Pin_3
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
  * @brief  Configure Optput Signal Control GPIO peripheral   
  * @param  None
  * @retval None
  */
void _Device_OptputSignalControl_Init(void){
        GPIO_Init(AdapterSOCControl_PORT, AdapterSOCControl_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
        GPIO_Init(OneWireControl_PORT, OneWireControl_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
        GPIO_Init(UartIsolationControl_PORT, UartIsolationControl_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
        GPIO_Init(NTC_Control_PORT, NTC_Control_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level
}

void _Device_AdapterSOCControl_Pin_High(){
    AdapterSOCControl_PORT->ODR |= AdapterSOCControl_PIN;
}
void _Device_AdapterSOCControl_Pin_Low(){
    AdapterSOCControl_PORT->ODR &= ~AdapterSOCControl_PIN;
}

void _Device_OneWireControl_Pin_High(){
    OneWireControl_PORT->ODR |= OneWireControl_PIN;
}
void _Device_OneWireControl_Pin_Low(){
    OneWireControl_PORT->ODR &= ~OneWireControl_PIN;
}

void _Device_UartIsolationControl_Pin_High(){
    UartIsolationControl_PORT->ODR |= UartIsolationControl_PIN;
}
void _Device_UartIsolationControl_Pin_Low(){
    UartIsolationControl_PORT->ODR &= ~UartIsolationControl_PIN;
}

void _Device_NTC_Control_Pin_High(){
    NTC_Control_PORT->ODR |= NTC_Control_PIN;
}
void _Device_NTC_Control_Pin_Low(){
    NTC_Control_PORT->ODR &= ~NTC_Control_PIN;
}

