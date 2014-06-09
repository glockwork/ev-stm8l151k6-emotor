/**
  ******************************************************************************
  * @file    Timer3.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   Timer3 setting
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
uint16_t Setting_Interrupt_Calling_TimingDelay_Timer3;
__IO uint16_t Interrupt_Calling_TimingDelay_counter_Timer3;
//==============================================================================
// Private function prototypes
//==============================================================================
void (*Interrupt_Timer3_ptr_fuc[Max_Timer3_INTERRUPT_Function_Calling])(void);
void empty_timer3_fun(void){}

#if defined(System_Clock_Freq_8MHz)
uint16_t Setting_Fast_Interrupt_Calling_TimingDelay_Timer3;
__IO uint16_t Fast_Interrupt_Calling_TimingDelay_counter_Timer3;

void (*Fast_Interrupt_Timer3_ptr_fuc[Max_Timer3_Fast_INTERRUPT_Function_Calling])(void);

#endif


//==============================================================================
// Private functions
//==============================================================================
/**
  * @brief  Configure TIM3 peripheral   
  * @param  None
  * @retval None
  */
void _Device_Timer3_Init(void)
{
	int i;
    
    TIM3_DeInit();
                
    for(i = 0; i < Max_Timer3_INTERRUPT_Function_Calling; i++){
        Interrupt_Timer3_ptr_fuc[i] = empty_timer3_fun;
    }

    Setting_Interrupt_Calling_TimingDelay_Timer3 = 0;
    Interrupt_Calling_TimingDelay_counter_Timer3 = 0;


#if defined(System_Clock_Freq_8MHz)
    for(i = 0; i < Max_Timer3_Fast_INTERRUPT_Function_Calling; i++){
        Fast_Interrupt_Timer3_ptr_fuc[i] = empty_timer3_fun;
    }
    Setting_Fast_Interrupt_Calling_TimingDelay_Timer3 = 0;
    Fast_Interrupt_Calling_TimingDelay_counter_Timer3 = 0;
#endif

}

void _Device_Setting_Timer3_Enable(uint8_t enable)
{
    if(enable){
        /* Enable TIM3 clock */
        CLK_PeripheralClockConfig(CLK_Peripheral_TIM3, ENABLE);
        /* Time Base configuration */
        TIM3_TimeBaseInit(TIM3_PRESCALER, TIM3_CounterMode_Up, TIM3_PERIOD);
        /* Enable update interrupt */
        TIM3_ITConfig(TIM3_IT_Update, ENABLE); 
        /* Enable TIM3 */
        TIM3_Cmd(ENABLE);
        
    }else{
        /* Enable TIM3 clock */
        CLK_PeripheralClockConfig(CLK_Peripheral_TIM3, DISABLE);
        /* Enable update interrupt */
        TIM3_ITConfig(TIM3_IT_Update, DISABLE); 
        /* Enable TIM3 */
        TIM3_Cmd(DISABLE);
        /* Cleat Interrupt Pending bit */
        TIM3_ClearITPendingBit(TIM3_IT_Update);
    }
}
void _Device_Set_Timer3_Interrupt_Timer_Calling_Interval_Times(uint16_t ms_Dealy){
    if(ms_Dealy == 0){
        Setting_Interrupt_Calling_TimingDelay_Timer3 = 0;
    }else{
        Setting_Interrupt_Calling_TimingDelay_Timer3 = ms_Dealy - 1;
    }
}

void _Device_Set_Timer3_Interrupt_Timer_Calling_Function(uint8_t fun_index, void (*calling_fun)()){
    if(fun_index >= Max_Timer3_INTERRUPT_Function_Calling){
        return;
    }
    Interrupt_Timer3_ptr_fuc[fun_index] = calling_fun;
}
void _Device_Remove_Timer3_Interrupt_Timer_Calling_Function(uint8_t fun_index){
    if(fun_index >= Max_Timer3_INTERRUPT_Function_Calling){
        return;
    }
    Interrupt_Timer3_ptr_fuc[fun_index] = empty_timer3_fun;
}


#if defined(System_Clock_Freq_8MHz)
void _Device_Set_Timer3_Fast_Interrupt_Timer_Calling_Function(uint8_t fun_index, void (*calling_fun)()){
    if(fun_index >= Max_Timer3_Fast_INTERRUPT_Function_Calling){
        return;
    }
    Fast_Interrupt_Timer3_ptr_fuc[fun_index] = calling_fun;
}
void _Device_Remove_Timer3_Fast_Interrupt_Timer_Calling_Function(uint8_t fun_index){
    if(fun_index >= Max_Timer3_Fast_INTERRUPT_Function_Calling){
        return;
    }
    Fast_Interrupt_Timer3_ptr_fuc[fun_index] = empty_timer3_fun;
}

#endif

/********************************************************************************
* TIM3_UPD_OVF_TRG_BRK_USART3_TX_IRQHandler										*
*******************************************************************************/
/**
  * @brief Timer3 Update/Overflow/Trigger/Break Interrupt routine.
  * @par Parameters:
  * None
  * @retval 
  * None
  */
#if defined(_IAR_)	
INTERRUPT_HANDLER(TIM3_UPD_OVF_TRG_BRK_IRQHandler, 21)
{
#endif
#if defined(_COSMIC_)	
INTERRUPT void TIM3_UPD_OVF_TRG_BRK_IRQHandler(void)
{
#endif
	int i;
    
    //GPIO_TOGGLE(LED3_PORT, LED3_PIN);
    //GPIO_HIGH(LED1_PORT, LED1_PIN); 
    
    /* Cleat Interrupt Pending bit */
    TIM3_ClearITPendingBit(TIM3_IT_Update);
    
    
#if defined(System_Clock_Freq_8MHz)
    for( i = 0; i < Max_Timer3_Fast_INTERRUPT_Function_Calling; i++){
        (*Fast_Interrupt_Timer3_ptr_fuc[i])();
    }

    Fast_Interrupt_Calling_TimingDelay_counter_Timer3++;
    if(Fast_Interrupt_Calling_TimingDelay_counter_Timer3 >= TIM3_Count_For_50MS_Interval){
        for( i = 0; i < Max_Timer3_INTERRUPT_Function_Calling; i++){
            (*Interrupt_Timer3_ptr_fuc[i])();
        }

        Fast_Interrupt_Calling_TimingDelay_counter_Timer3 = 0;
    }
#else
    if(Interrupt_Calling_TimingDelay_counter_Timer3 >= Setting_Interrupt_Calling_TimingDelay_Timer3){
        for( i = 0; i < Max_Timer3_INTERRUPT_Function_Calling; i++){
            (*Interrupt_Timer3_ptr_fuc[i])();
        }
        Interrupt_Calling_TimingDelay_counter_Timer3 = 0;
    }else{
        Interrupt_Calling_TimingDelay_counter_Timer3++;
    }
    
#endif
    
    //GPIO_LOW(LED1_PORT, LED1_PIN); 
    
}