/**
  ******************************************************************************
  * @file    Timer4.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   Timer4 setting
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
__IO uint16_t Setting_Interrupt_Calling_TimingDelay_Timer4[Max_Timer4_INTERRUPT_Function_Calling];
__IO uint16_t Interrupt_Calling_TimingDelay_counter_Timer4[Max_Timer4_INTERRUPT_Function_Calling];
__IO uint16_t Interrupt_Calling_Function_Bit_Flag;

__IO uint32_t TimingDelay;
//==============================================================================
// Private function prototypes
//==============================================================================
void (*Interrupt_Timer4_ptr_fuc[Max_Timer4_INTERRUPT_Function_Calling])(void);
void empty_timer4_fun(void){}

//==============================================================================
// Private functions
//==============================================================================
/**
  * @brief  Configure TIM4 peripheral   
  * @param  None
  * @retval None
  */
void _Device_Timer4_Init(void)
{
	int i;
    
    TIM4_DeInit();
                
    for(i = 0; i < Max_Timer4_INTERRUPT_Function_Calling; i++){
        Interrupt_Timer4_ptr_fuc[i] = empty_timer4_fun;
        Setting_Interrupt_Calling_TimingDelay_Timer4[i] = 0;
        Interrupt_Calling_TimingDelay_counter_Timer4[i] = 0;
    }

    TimingDelay = 0;
    
    /* for example, TIM4 configuration:
   - TIM4CLK is set to 16 MHz, the TIM4 Prescaler is equal to 128 so the TIM1 counter
   clock used is 16 MHz / 128 = 125 000 Hz
  - With 125 000 Hz we can generate time base:
      max time base is 2.048 ms if TIM4_PERIOD = 255 --> (255 + 1) / 125000 = 2.048 ms
      min time base is 0.016 ms if TIM4_PERIOD = 1   --> (  1 + 1) / 125000 = 0.016 ms
    */
    
  /*  - In this example , TIM4CLK is set to 4 MHz,
        the TIM4 Prescaler is equal to 64,
        so the TIM1 counter clock used is 4 MHz / 64 = 62,500 Hz.
        we need to generate a time base equal to 1 ms
        so TIM4_PERIOD = (0.001 * 62500 - 1) = 61 */

}

void _Device_Setting_Timer4_Enable(uint8_t enable)
{
    if(enable){
        /* Enable TIM4 CLK */
        CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);
        /* Time base configuration */
        TIM4_TimeBaseInit(dTimer4Divided, dTIM4_PERIOD);
        /* Clear TIM4 update flag */
        TIM4_ClearFlag(TIM4_FLAG_Update);
        /* Enable update interrupt */
        TIM4_ITConfig(TIM4_IT_Update, ENABLE);
        /* Enable TIM4 */
        TIM4_Cmd(ENABLE);
    }else{
        /* Disable update interrupt */
        TIM4_ITConfig(TIM4_IT_Update, DISABLE);
        /* Disable TIM4 */
        TIM4_Cmd(DISABLE);
        /* Disable TIM4 CLK */
        CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, DISABLE);
        /* Cleat Interrupt Pending bit */
        TIM4_ClearITPendingBit(TIM4_IT_Update);
    }
}
void _Device_Set_Timer4_Interrupt_Timer_Calling_Function_With_Delay_And_Exec(uint8_t fun_index, void (*calling_fun)(), __IO uint16_t ms_Dealy ){
    unsigned char calling_count;
    unsigned char i;
    
    if(fun_index >= Max_Timer4_INTERRUPT_Function_Calling){
        return;
    }
    Interrupt_Timer4_ptr_fuc[fun_index] = calling_fun;
    if(ms_Dealy == 0){
        Setting_Interrupt_Calling_TimingDelay_Timer4[fun_index] = 0;
    }else{
        Setting_Interrupt_Calling_TimingDelay_Timer4[fun_index] = ms_Dealy - 1;
    }
    Interrupt_Calling_TimingDelay_counter_Timer4[fun_index] = 0;
    ///////////////////////////////////////////////////////////////////////////
    calling_count=0;
    for( i = 0; i < Max_Timer4_INTERRUPT_Function_Calling; i++){
        if(i == fun_index){
            continue;
        }
        if(Interrupt_Timer4_ptr_fuc[i] != empty_timer4_fun){
            calling_count++;
        }
    }
    if(calling_count == 0){
        _Device_Setting_Timer4_Enable(DeviceOn);
    }
}
//// for 1 ms Interrupt
//void _Device_Set_Timer4_Interrupt_Timer_Calling_Function_With_Delay_And_Exec(uint8_t fun_index, void (*calling_fun)(),uint16_t ms_Dealy ){
//    unsigned char calling_count;
//    unsigned char i;
//    
//    if(fun_index >= Max_Timer4_INTERRUPT_Function_Calling){
//        return;
//    }
//    Interrupt_Timer4_ptr_fuc[fun_index] = calling_fun;
//    if(ms_Dealy == 0){
//        Setting_Interrupt_Calling_TimingDelay_Timer4[fun_index] = 0;
//    }else{
//        Setting_Interrupt_Calling_TimingDelay_Timer4[fun_index] = ms_Dealy - 1;
//    }
//    Interrupt_Calling_TimingDelay_counter_Timer4[fun_index] = 0;
//    ///////////////////////////////////////////////////////////////////////////
//    calling_count=0;
//    for( i = 0; i < Max_Timer4_INTERRUPT_Function_Calling; i++){
//        if(i == fun_index){
//            continue;
//        }
//        if(Interrupt_Timer4_ptr_fuc[i] != empty_timer4_fun){
//            calling_count++;
//        }
//    }
//    if(calling_count == 0){
//        _Device_Setting_Timer4_Enable(DeviceOn);
//    }
//}
void _Device_Remove_Timer4_Interrupt_Timer_Calling_Function(uint8_t fun_index){
    if(fun_index >= Max_Timer4_INTERRUPT_Function_Calling){
        return;
    }
    Interrupt_Timer4_ptr_fuc[fun_index] = empty_timer4_fun;
    Setting_Interrupt_Calling_TimingDelay_Timer4[fun_index] = 0;
    Interrupt_Calling_TimingDelay_counter_Timer4[fun_index] = 0;
}



/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void _Device_Delay(__IO uint32_t ms_Time)
{
  TimingDelay = ms_Time;

  while (TimingDelay != 0);
}


/********************************************************************************
* TIM4_UPDATE_OVFLOW_IRQHandler													*
*******************************************************************************/
/**
  * @brief TIM4 Update/Overflow/Trigger Interrupt routine.
  * @par Parameters:
  * None
  * @retval 
  * None
  */
#if defined(_IAR_)	
INTERRUPT_HANDLER(TIM4_UPD_OVF_TRG_IRQHandler,25)
{
#endif
#if defined(_COSMIC_)	
INTERRUPT void TIM4_UPD_OVF_TRG_IRQHandler(void)
{
#endif
	int i;
    unsigned char empty_Count;
    unsigned char setting_Count;
    
    /* Cleat Interrupt Pending bit */
    TIM4_ClearITPendingBit(TIM4_IT_Update);
    
    //TimingDelay_Decrement();
    //GPIO_TOGGLE(LED2_PORT, LED2_PIN);
    //GPIO_HIGH(LED4_PORT, LED4_PIN);
    //GPIO_TOGGLE(LED4_PORT, LED4_PIN);
    
    empty_Count = 0;
    for( i = 0; i < Max_Timer4_INTERRUPT_Function_Calling; i++){
        if(Interrupt_Timer4_ptr_fuc[i] == empty_timer4_fun){
            empty_Count++;
        }else{
            setting_Count = Setting_Interrupt_Calling_TimingDelay_Timer4[i];
            if(Interrupt_Calling_TimingDelay_counter_Timer4[i] >= setting_Count){
                (*Interrupt_Timer4_ptr_fuc[i])();
                Interrupt_Calling_TimingDelay_counter_Timer4[i] = 0;
            }else{
                Interrupt_Calling_TimingDelay_counter_Timer4[i]++;
            }
        }
    }
    
    if(empty_Count >= Max_Timer4_INTERRUPT_Function_Calling){
        _Device_Setting_Timer4_Enable(DeviceOff);
    }
    
    //GPIO_LOW(LED4_PORT, LED4_PIN);
    
}