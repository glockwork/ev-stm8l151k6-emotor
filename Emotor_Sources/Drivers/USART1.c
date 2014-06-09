/**
  ******************************************************************************
  * @file    USART1.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   USART1 setting
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
//#define UratBaudRates		115200
//#define UratBaudRates		57600
//#define UratBaudRates		38400
//#define UratBaudRates		19200
#define UratBaudRates		9600

#define SendingTimeOutCycle	1000

#if defined(_USE_UART_PORT_MAPPING_)
    #define USART_TX_PORT       GPIOA
    #define USART_TX_PIN        GPIO_Pin_2
    #define USART_RX_PORT       GPIOA
    #define USART_RX_PIN        GPIO_Pin_3
    #define USART_RX_EXTI_PIN   EXTI_Pin_3
#else
    #define USART_TX_PORT       GPIOC
    #define USART_TX_PIN        GPIO_Pin_3
    #define USART_RX_PORT       GPIOC
    #define USART_RX_PIN        GPIO_Pin_2
    #define USART_RX_EXTI_PIN   EXTI_Pin_2
#endif

/* Usart_Peripheral_Flag Control Bits */
/* For Usart_Peripheral_Flag ; unsigned char */
//Low byte
#define fUart_Enable                    (0x01)    //
#define fUart_RX_IT_Enable              (0x02)    //
#define fUart_RX_IT_Received            (0x04)    //
//#define fDSG_LOW_CURRENT_OTP_COUNT      (0x08)    //
//#define fCHARGING_IN_HIGH_TEMP          (0x10)
//#define fCHARGING_IN_LOW_TEMP           (0x20)    //
//#define fSTORE_IN_LOW_TEMP1             (0x40)    //
//#define fSTORE_IN_LOW_TEMP2             (0x80)    //
//==============================================================================
// Private macro
//==============================================================================
//==============================================================================
// Private Enum
//==============================================================================
//==============================================================================
// Private variables
//==============================================================================

static unsigned int SendingWhileTimeOutCount;

//static unsigned char Usart_Peripheral_Enable_Flag;
static unsigned char Usart_Peripheral_Flag;
//==============================================================================
// Private function prototypes
//==============================================================================
void (*Interrupt_USART1_ReceiveData_ptr_fuc)(__IO unsigned char receivedByte);
void Empty_USART1_fun(unsigned char receivedByte){}


//==============================================================================
// Private functions
//==============================================================================
/**
  * @brief  Configure USART1 peripheral
  * @param  None
  * @retval None
  */
//void _Device_Uart_Enable(void){
//
//    USART_DeInit(USART1);
//
//    //SYSCFG_REMAPPinConfig((REMAP_Pin_TypeDef)REMAP_Pin_USART1TxRxPortA, ENABLE);   /*!< USART1 Tx- Rx (PC3- PC2) remapping to PA2- PA3 */
//
//    GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_Out_PP_High_Fast); // USART1 TX
//    GPIO_ExternalPullUpConfig(GPIOC, GPIO_Pin_3, ENABLE);
//    GPIO_Init(GPIOC, GPIO_Pin_2, GPIO_Mode_In_PU_No_IT);  // USART1 RX
//    GPIO_ExternalPullUpConfig(GPIOC, GPIO_Pin_2, ENABLE);
//
//    /* Enable USART1 clock */
//    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);
//
//    /* USART configured as follow:
//        - BaudRate = 115200 baud
//        - Word Length = 8 Bits
//        - One Stop Bit
//        - Odd parity
//        - Receive and transmit enabled
//        - USART Clock disabled
//    */
//    USART_Init(USART1, UratBaudRates, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No, (USART_Mode_TypeDef)(USART_Mode_Tx | USART_Mode_Rx));
//    //USART_Init(USART1, (uint32_t)115200, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No, (USART_Mode_TypeDef)USART_Mode_Tx );
//    USART_ClearITPendingBit(USART1, USART_IT_TC);
//    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//
//    /* Enable the USART Receive interrupt: this interrupt is generated when the USART
//    receive data register is not empty */
//    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//
//    /* Enable the USART Transmit complete interrupt: this interrupt is generated when the USART
//    transmit Shift Register is empty */
//    //USART_ITConfig(USART1, USART_IT_TC, ENABLE);
//
//    /* Enable USART */
//    USART_Cmd(USART1, ENABLE);
//
//    SendingWhileTimeOutCount = 0;
//
//    Interrupt_USART1_ReceiveData_ptr_fuc = Empty_USART1_fun;
//
//    Usart_Peripheral_Enable_Flag = DeviceOn;
//}

void _Device_Uart_Enable(void){

    GPIO_Init(USART_RX_PORT, USART_RX_PIN, GPIO_Mode_In_FL_No_IT);  // Input floating, no external interrupt

    USART_DeInit(USART1);
    USART_ClearITPendingBit(USART1, USART_IT_TC);
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);

#if defined(_USE_UART_PORT_MAPPING_)
    SYSCFG_REMAPPinConfig((REMAP_Pin_TypeDef)REMAP_Pin_USART1TxRxPortA, ENABLE);  /*!< USART1 Tx- Rx (PC3- PC2) remapping to PA2- PA3 */
#elif defined(_USE_UART_PORT_WITHOUT_MAPPING_)
#else
    #error "Please select Use Usart_Port_Mapping 0(disable)/1(enable)"
#endif

    GPIO_Init(USART_TX_PORT, USART_TX_PIN, GPIO_Mode_Out_PP_High_Fast); // USART1 TX
    GPIO_ExternalPullUpConfig(USART_TX_PORT, USART_TX_PIN, ENABLE);

    GPIO_Init(USART_RX_PORT, USART_RX_PIN, GPIO_Mode_In_PU_No_IT);  // USART1 RX
    GPIO_ExternalPullUpConfig(USART_RX_PORT, USART_RX_PIN, ENABLE);

    /* Enable USART1 clock */
    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);

    /* USART configured as follow:
        - BaudRate = 115200 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - Odd parity
        - Receive and transmit enabled
        - USART Clock disabled
    */
    USART_Init(USART1, UratBaudRates, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No, (USART_Mode_TypeDef)(USART_Mode_Tx | USART_Mode_Rx));
    //USART_Init(USART1, (uint32_t)115200, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No, (USART_Mode_TypeDef)USART_Mode_Tx );
    USART_ClearITPendingBit(USART1, USART_IT_TC);
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);

    /* Enable the USART Receive interrupt: this interrupt is generated when the USART
    receive data register is not empty */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    /* Enable the USART Transmit complete interrupt: this interrupt is generated when the USART
    transmit Shift Register is empty */
    //USART_ITConfig(USART1, USART_IT_TC, ENABLE);


    SendingWhileTimeOutCount = 0;
    Interrupt_USART1_ReceiveData_ptr_fuc = Empty_USART1_fun;
    Usart_Peripheral_Flag = 0;
    Usart_Peripheral_Flag |= fUart_Enable;

    /* Enable USART */
    USART_Cmd(USART1, ENABLE);
}
void _Device_Uart_Disable(void){

    Usart_Peripheral_Flag &= ~fUart_Enable;


    Interrupt_USART1_ReceiveData_ptr_fuc = Empty_USART1_fun;

    /* disable the USART Receive interrupt: this interrupt is generated when the USART
    receive data register is not empty */
    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);

    /* disable the USART Transmit complete interrupt: this interrupt is generated when the USART
    transmit Shift Register is empty */
    USART_ITConfig(USART1, USART_IT_TC, DISABLE);

    /* disable USART */
    USART_Cmd(USART1, DISABLE);

    /* disable USART1 clock */
    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, DISABLE);

    USART_DeInit(USART1);


#if defined(_USE_PHOTO_ISOALTOR_FOR_COMMUNICATION_)
    //set as floating pin
	//GPIO_Init(USART_RX_PORT, USART_RX_PIN, GPIO_Mode_In_FL_No_IT);  // Input floating, no external interrupt
	GPIO_Init(USART_TX_PORT, USART_TX_PIN, GPIO_Mode_In_FL_No_IT);  // Input floating, no external interrupt

	GPIO_Init(USART_RX_PORT, USART_RX_PIN, GPIO_Mode_In_PU_IT);  // Input pull-up, external interrupt
	//GPIO_Init(USART_TX_PORT, USART_TX_PIN, GPIO_Mode_In_PU_IT);  // Input pull-up, external interrupt
#else
    //for low power setting and save power
	//GPIO_Init(USART_RX_PORT, USART_RX_PIN, GPIO_Mode_Out_PP_Low_Slow);  // set as output and PP Low level
	GPIO_Init(USART_TX_PORT, USART_TX_PIN, GPIO_Mode_Out_PP_Low_Slow);  // set as output and PP Low level

	GPIO_Init(USART_RX_PORT, USART_RX_PIN, GPIO_Mode_In_PU_IT);  // Input pull-up, external interrupt
#endif

	/* Initialize the Interrupt sensitivity */
    EXTI_SetPinSensitivity(USART_RX_EXTI_PIN, EXTI_Trigger_Falling);  /*!< Interrupt on Falling edge only */

    _Device_delay_cycles(15);     //100 = 1ms at CCLK=4MHz, 15 ~= 150 us
    Usart_Peripheral_Flag |= fUart_RX_IT_Enable;
    Usart_Peripheral_Flag &= ~fUart_RX_IT_Received; //clear reveived status

    SendingWhileTimeOutCount = 0;


}
void _Device_Set_Uart_RX_Interrupt(unsigned char enable){
    if(enable){
        /* Enable the USART Receive interrupt: this interrupt is generated when the USART
        receive data register is not empty */
        USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    }else{
        /* Disable the USART Receive interrupt: this interrupt is generated when the USART
        receive data register is not empty */
        USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
    }
}

void _Device_Set_Uart_Interrupt_Receive_Calling_Function(void (*calling_fun)(__IO unsigned char receivedByte)){
    Interrupt_USART1_ReceiveData_ptr_fuc = calling_fun;
}
unsigned char _Device_Uart_Send_Bytes(unsigned char *sendByte, unsigned int length){
	unsigned int i;

    //if(Usart_Peripheral_Enable_Flag == DeviceOff){
    if((Usart_Peripheral_Flag & fUart_Enable) == 0){
        return Func_Fail;
    }
#if (_Set_UART_AS_Half_Duplex_Transmission_ == 1)
    _Device_Set_Uart_RX_Interrupt(DeviceOff);
#endif

    //GPIO_WriteHigh(LED2_PORT, LED2_PIN);


    //set TX status
//    GPIO_WriteHigh(URAT_TX_Setting_PORT, URAT_TX_Setting_PIN);
//    GPIO_WriteHigh(URAT_TX_Setting_PORT, URAT_TX_Setting_PIN);  //for delay

	for(i = 0; i < length; i++){
		USART_SendData8(USART1, (*(sendByte + i)));
		SendingWhileTimeOutCount = 0;
		//while (USART_GetFlagStatus(USART1, UART2_FLAG_TXE) == RESET){     //Transmit Data Register Empty flag
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){       //Transmission Complete flag
			if(SendingWhileTimeOutCount >= SendingTimeOutCycle){
				break;
			}
			SendingWhileTimeOutCount++;
		}//while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    }
    //disable TX status
//    GPIO_WriteLow(URAT_TX_Setting_PORT, URAT_TX_Setting_PIN);
//    GPIO_WriteLow(URAT_TX_Setting_PORT, URAT_TX_Setting_PIN);  //for delay

    //GPIO_WriteLow(LED2_PORT, LED2_PIN);

#if (_Set_UART_AS_Half_Duplex_Transmission_ == 1)
    _Device_Set_Uart_RX_Interrupt(DeviceOn);
#endif
    return Func_Complete;
}

unsigned char _Device_Get_Uart_Pin_Interrupt_Received(){

    if((Usart_Peripheral_Flag & fUart_RX_IT_Enable) && (Usart_Peripheral_Flag & fUart_RX_IT_Received)){
        return true;
    }else{
        return false;
    }
}

/********************************************************************************
* USART1_RX_IRQHandler													        *
*******************************************************************************/
/**
  * @brief USART1 RX Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#if defined(_IAR_)	
INTERRUPT_HANDLER(USART1_RX_IRQHandler,28)
{
#endif
#if defined(_COSMIC_)	
INTERRUPT void USART1_RX_IRQHandler(void)
{
#endif
    //GPIO_HIGH(LED3_PORT, LED3_PIN);


    /* Read one byte from the receive data register and send it back */
    if (USART_GetFlagStatus(USART1, USART_FLAG_OR) != RESET){
        Interrupt_USART1_ReceiveData_ptr_fuc(USART1->DR);
    }else{
        Interrupt_USART1_ReceiveData_ptr_fuc(USART_ReceiveData8(USART1));
    }

    //USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    //GPIO_LOW(LED3_PORT, LED3_PIN);

}


/********************************************************************************
* USART1_TX_IRQHandler													        *
*******************************************************************************/
/**
  * @brief USART1 TX Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#if defined(_IAR_)	
INTERRUPT_HANDLER(USART1_TX_IRQHandler,27)
{
#endif
#if defined(_COSMIC_)	
INTERRUPT void USART1_TX_IRQHandler(void)
{
#endif


  /* Read one byte from the receive data register and send it back */


    USART_ClearITPendingBit(USART1, USART_IT_TC);

}



#if defined(_USE_UART_PORT_MAPPING_)

    /********************************************************************************
    * EXTI3_IRQHandler										*
    *******************************************************************************/
    /**
      * @brief External IT PIN3 Interrupt routine.
      * @par Parameters:
      * None
      * @retval
      * None
      */
    #if defined(_IAR_)	
    INTERRUPT_HANDLER(EXTI3_IRQHandler, 11)
    {
    #endif
    #if defined(_COSMIC_)	
    INTERRUPT void EXTI3_IRQHandler(void)
    {
    #endif

        //GPIO_TOGGLE(LED4_PORT, LED4_PIN);
        //GPIO_HIGH(LED1_PORT, LED1_PIN);
        //GPIO_LOW(LED1_PORT, LED1_PIN);

        _Device_delay_cycles(15);     //100 = 1ms at CCLK=4MHz, 15 ~= 150 us

        Usart_Peripheral_Flag |= fUart_RX_IT_Received;

        /* Cleat Interrupt pending bit */
        EXTI_ClearITPendingBit(EXTI_IT_Pin3);
    }
#else

    /********************************************************************************
    * EXTI2_IRQHandler										*
    *******************************************************************************/
    /**
      * @brief External IT PIN2 Interrupt routine.
      * @par Parameters:
      * None
      * @retval
      * None
      */
    #if defined(_IAR_)	
    INTERRUPT_HANDLER(EXTI2_IRQHandler, 10)
    {
    #endif
    #if defined(_COSMIC_)	
    INTERRUPT void EXTI2_IRQHandler(void)
    {
    #endif

        //GPIO_TOGGLE(LED4_PORT, LED4_PIN);
        //GPIO_HIGH(LED1_PORT, LED1_PIN);
        //GPIO_LOW(LED1_PORT, LED1_PIN);

        _Device_delay_cycles(15);     //100 = 1ms at CCLK=4MHz, 15 ~= 150 us

        Usart_Peripheral_Flag |= fUart_RX_IT_Received;

        /* Cleat Interrupt pending bit */
        EXTI_ClearITPendingBit(EXTI_IT_Pin2);
    }
#endif


