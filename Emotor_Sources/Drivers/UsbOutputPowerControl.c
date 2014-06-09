/**
  ******************************************************************************
  * @file    UsbOptputPowerControl.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   USB Output Power Signal Control setting
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
#define USB_OCP_Signal_PORT                 GPIOB
#define USB_OCP_Signal_PIN                  GPIO_Pin_6

#define USB_OutputPower_ONOFF_Signal_PORT   GPIOB
#define USB_OutputPower_ONOFF_Signal_PIN    GPIO_Pin_5


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
void _Device_UsbOutputPowerSignalControl_Init(void){
        GPIO_Init(USB_OutputPower_ONOFF_Signal_PORT, USB_OutputPower_ONOFF_Signal_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP Low level

       /* Pin configured in input floating mode  */
        GPIO_Init(USB_OCP_Signal_PORT, USB_OCP_Signal_PIN, GPIO_Mode_In_FL_No_IT);  /*!< Input floating, No external interrupt */
}

void _Device_USB_OutputPower_ONOFF_Signal_Pin_High(){
    USB_OutputPower_ONOFF_Signal_PORT->ODR |= USB_OutputPower_ONOFF_Signal_PIN;
}
void _Device_USB_OutputPower_ONOFF_Signal_Pin_Low(){
    USB_OutputPower_ONOFF_Signal_PORT->ODR &= ~USB_OutputPower_ONOFF_Signal_PIN;
}
unsigned char _Device_Get_USB_OCP_Signal_Status(){
    // hi : normal,  Lo : button Press
    return (GPIO_ReadInputDataBit(USB_OCP_Signal_PORT, USB_OCP_Signal_PIN)== 0)? USB_Output_Power_Normal : USB_Output_Power_OCP;
}


