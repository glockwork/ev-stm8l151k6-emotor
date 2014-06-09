/**
  ******************************************************************************
  * @file    Button.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   Button setting
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
#define BUTTON_PORT	    GPIOB
#define BUTTON_PIN	    GPIO_Pin_4
#define BUTTON_EXTI     EXTI_Pin_4

//==============================================================================
// Private macro
//==============================================================================
//==============================================================================
// Private Enum
//==============================================================================
//==============================================================================
// Private variables
//==============================================================================
//uint16_t Setting_Interrupt_Calling_TimingDelay;
//__IO uint16_t Interrupt_Calling_TimingDelay_counter;
//__IO uint32_t TimingDelay;
//==============================================================================
// Private function prototypes
//==============================================================================
void (*Intupt_Button_ptr_fuc)(void);
void empty_ButtonEvent_Press_Trigger_fun(){}

//==============================================================================
// Private functions
//==============================================================================
/**
  * @brief  Configure Button GPIO peripheral   
  * @param  None
  * @retval None
  */
void _Device_Button_Config(void){
   /* Pin configured in input floating mode with interrupt enabled
                       --> connected to EXTIx Interrupt, where x:0..7 */
    GPIO_Init(BUTTON_PORT, BUTTON_PIN, GPIO_Mode_In_FL_IT);  /*!< Input floating, external interrupt */
    

#if defined(_SET_BUTTON_V_LEVEL_REVERSE_)  
	/* Initialize the Interrupt sensitivity */
    EXTI_SetPinSensitivity(BUTTON_EXTI, EXTI_Trigger_Falling);  /*!< Interrupt on Falling edge only */
#elif defined(_SET_BUTTON_V_LEVEL_NORMAL_)
	/* Initialize the Interrupt sensitivity */
    EXTI_SetPinSensitivity(BUTTON_EXTI, EXTI_Trigger_Rising);  /*!< Interrupt on Rising edge only */
#else
    #error "Please select Use _SW_Button_LEVEL_Reverse_ 0(disable)/1(enable)"
#endif    

    
    Intupt_Button_ptr_fuc = empty_ButtonEvent_Press_Trigger_fun;
}

unsigned char _Device_Get_Button_Status(){

#if defined(_SET_BUTTON_V_LEVEL_REVERSE_)  
    // hi : normal,  Lo : button Press
    return (GPIO_ReadInputDataBit(BUTTON_PORT, BUTTON_PIN)== 0)? ButtonPress : ButtonRelease;
#elif defined(_SET_BUTTON_V_LEVEL_NORMAL_)
    // hi : button Press,  Lo : normal
    return (GPIO_ReadInputDataBit(BUTTON_PORT, BUTTON_PIN)== 0)? ButtonRelease : ButtonPress;
#else
    #error "Please select Use _SW_Button_LEVEL_Reverse_ 0(disable)/1(enable)"
#endif    
}

void _Device_Set_Interrupt_ButtonEvent_Press_Trigger_Function(void (*calling_fun)()){
    Intupt_Button_ptr_fuc = calling_fun;
}
void _Device_Remove_Interrupt_ButtonEvent_Press_Trigger_Function(){
    Intupt_Button_ptr_fuc = empty_ButtonEvent_Press_Trigger_fun;
}

/********************************************************************************
* EXTI4_IRQHandler										*
*******************************************************************************/
/**
  * @brief External IT PIN4 Interrupt routine.
  * @par Parameters:
  * None
  * @retval 
  * None
  */
#if defined(_IAR_)	
INTERRUPT_HANDLER(EXTI4_IRQHandler, 12)
{
#endif
#if defined(_COSMIC_)	
INTERRUPT void EXTI4_IRQHandler(void)
{
#endif
    
    //GPIO_TOGGLE(LED4_PORT, LED4_PIN);
    //GPIO_HIGH(LED1_PORT, LED1_PIN);
    //GPIO_LOW(LED1_PORT, LED1_PIN);
    
    _Device_delay_cycles(15);     //100 = 1ms at CCLK=4MHz, 15 ~= 150 us
    /* button is pressed */
    if(_Device_Get_Button_Status() == ButtonPress)
	{   // press
        (*Intupt_Button_ptr_fuc)();
	}

    /* Cleat Interrupt pending bit */
    EXTI_ClearITPendingBit(EXTI_IT_Pin4);
}

