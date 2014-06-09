/**
  ******************************************************************************
  * @file    BackLightControl.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    27-June-2013
  * @brief   Back Light Control setting
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
#include "Config_Info\System_Config_Info.h"
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
#define BackLight_BUTTON_PORT   GPIOC
#define BackLight_BUTTON_PIN    GPIO_Pin_5
#define BackLight_BUTTON_EXTI   EXTI_Pin_5

#define BackLight_SignalOutput_PORT   GPIOC
#define BackLight_SignalOutput_PIN    GPIO_Pin_6

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
void (*Intupt_BackLight_Button_ptr_fuc)(void);
void empty_BackLight_ButtonEvent_Press_Trigger_fun(){}

//==============================================================================
// Private functions
//==============================================================================
/**
  * @brief  Configure Optput Signal Control GPIO peripheral
  * @param  None
  * @retval None
  */
void _Device_BackLightControl_Init(void){

    GPIO_Init(BackLight_SignalOutput_PORT, BackLight_SignalOutput_PIN, GPIO_Mode_Out_PP_Low_Fast);  // set as output and PP High level

   /* Pin configured in input floating mode with interrupt enabled
                       --> connected to EXTIx Interrupt, where x:0..7 */
    GPIO_Init(BackLight_BUTTON_PORT, BackLight_BUTTON_PIN, GPIO_Mode_In_FL_IT);  /*!< Input floating, external interrupt */
#if defined(_SET_BUTTON_V_LEVEL_REVERSE_)
	/* Initialize the Interrupt sensitivity */
    EXTI_SetPinSensitivity(BackLight_BUTTON_EXTI, EXTI_Trigger_Falling);  /*!< Interrupt on Falling edge only */
#elif defined(_SET_BUTTON_V_LEVEL_NORMAL_)
	/* Initialize the Interrupt sensitivity */
    EXTI_SetPinSensitivity(BackLight_BUTTON_EXTI, EXTI_Trigger_Rising);  /*!< Interrupt on Rising edge only */
#else
    #error "Please select Use _SW_Button_LEVEL_Reverse_ 0(disable)/1(enable)"
#endif

    Intupt_BackLight_Button_ptr_fuc = empty_BackLight_ButtonEvent_Press_Trigger_fun;
}

void _Device_Set_BackLight_Button_Interrupt_Enable(unsigned char enable){
    if(enable){
        GPIO_Init(BackLight_BUTTON_PORT, BackLight_BUTTON_PIN, GPIO_Mode_In_FL_IT);  /*!< Input floating, external interrupt */
    }else{
        GPIO_Init(BackLight_BUTTON_PORT, BackLight_BUTTON_PIN, GPIO_Mode_In_FL_No_IT);  /*!< Input floating, No external interrupt */
    }
}

unsigned char _Device_Get_BackLight_Button_Status(){

#if defined(_SET_BUTTON_V_LEVEL_REVERSE_)
    // hi : normal,  Lo : button Press
    return (GPIO_ReadInputDataBit(BackLight_BUTTON_PORT, BackLight_BUTTON_PIN)== 0)? ButtonPress : ButtonRelease;
#elif defined(_SET_BUTTON_V_LEVEL_NORMAL_)
    // hi : button Press,  Lo : normal
    return (GPIO_ReadInputDataBit(BackLight_BUTTON_PORT, BackLight_BUTTON_PIN)== 0)? ButtonRelease : ButtonPress;
#else
    #error "Please select Use _SW_Button_LEVEL_Reverse_ 0(disable)/1(enable)"
#endif
}

void _Device_Set_Interrupt_BackLight_ButtonEvent_Press_Trigger_Function(void (*calling_fun)()){
    Intupt_BackLight_Button_ptr_fuc = calling_fun;
}
void _Device_Remove_Interrupt_BackLight_ButtonEvent_Press_Trigger_Function(){
    Intupt_BackLight_Button_ptr_fuc = empty_BackLight_ButtonEvent_Press_Trigger_fun;
}

void _Device_BackLight_SignalOutput_Pin_High(){
    BackLight_SignalOutput_PORT->ODR |= BackLight_SignalOutput_PIN;
}
void _Device_BackLight_SignalOutput_Pin_Low(){
    BackLight_SignalOutput_PORT->ODR &= ~BackLight_SignalOutput_PIN;
}


/********************************************************************************
* EXTI5_IRQHandler										*
*******************************************************************************/
/**
  * @brief External IT PIN5 Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#if defined(_IAR_)	
INTERRUPT_HANDLER(EXTI5_IRQHandler, 13)
{
#endif
#if defined(_COSMIC_)	
INTERRUPT void EXTI4_IRQHandler(void)
{
#endif

    //GPIO_TOGGLE(LED4_PORT, LED4_PIN);
    //GPIO_HIGH(LED1_PORT, LED1_PIN);
    //GPIO_LOW(LED1_PORT, LED1_PIN);

    _Device_delay_cycles(100);     //100 = 1ms at CCLK=4MHz, 15 ~= 150 us
    /* button is pressed */
    if(_Device_Get_BackLight_Button_Status() == ButtonPress)
	{   // press
        (*Intupt_BackLight_Button_ptr_fuc)();
	}

    /* Cleat Interrupt pending bit */
    EXTI_ClearITPendingBit(EXTI_IT_Pin5);
}
