/**
  ******************************************************************************
  * @file    ADC_config.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   ADC1 setting
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
#define ADC1_DR_ADDRESS             ((uint16_t)0x5344)
#define ADC_DETECTION_CHANNEL_NUMS  ((uint16_t) 6)
const ADC_Channel_TypeDef ADC_Channel_Array[] =
{   ADC_Channel_0,  /* connected to IDSG */
    ADC_Channel_1,  /* connected to ICHG */
    ADC_Channel_2,  /* connected to VBAT */
    ADC_Channel_4,  /* connected to T1 */
    //ADC_Channel_5,  /* connected to T2 */
    //ADC_Channel_6,  /* connected to None */
    ADC_Channel_11,  /* connected to new t2 */
    ADC_Channel_Vrefint /* connected to Vrefint */ //¶q´ú¤º³¡Vref­È
};

#define BUFFER_SIZE                 ADC_DETECTION_CHANNEL_NUMS
#define BUFFER_ADDRESS              ((uint16_t)(&ADC_Buffer))

//////////////////////////////////////////////////////////////////////////////////////////////////
// Var of ADC_SUM_Of_Temp_Buffer_Shift_TIMES bounds up with Var of ADC_REPEAT_TIMES
// for example: if ADC_REPEAT_TIMES set as 2, ADC_SUM_Of_Temp_Buffer_Shift_TIMES has to be set as 1.
// if ADC_REPEAT_TIMES set as 4, ADC_SUM_Of_Temp_Buffer_Shift_TIMES has to be set as 2.
// if ADC_REPEAT_TIMES set as 8, ADC_SUM_Of_Temp_Buffer_Shift_TIMES has to be set as 3. and so on.
#define ADC_REPEAT_TIMES                    ((uint16_t) 2)
#define ADC_SUM_Of_Temp_Buffer_Shift_TIMES  (1)
//////////////////////////////////////////////////////////////////////////////////////////////////


#define ADC_IDSG_PORT	    GPIOA
#define ADC_IDSG_PIN	    GPIO_Pin_6
#define ADC_ICHG_PORT	    GPIOA
#define ADC_ICHG_PIN	    GPIO_Pin_5
#define ADC_VBAT_PORT	    GPIOA
#define ADC_VBAT_PIN	    GPIO_Pin_4
#define ADC_NTC1_PORT	    GPIOC
#define ADC_NTC1_PIN	    GPIO_Pin_4
#define ADC_NTC2_PORT	    GPIOC
#define ADC_NTC2_PIN	    GPIO_Pin_3

//==============================================================================
// Private macro
//==============================================================================
//==============================================================================
// Private Enum
//==============================================================================
//==============================================================================
// Private variables
//==============================================================================

uint16_t ADC_Buffer[ADC_DETECTION_CHANNEL_NUMS];
uint16_t ADC_SUM_TEMP_Buffer;

//==============================================================================
// Private function prototypes
//==============================================================================

//==============================================================================
// Private functions
//==============================================================================

/**
  * @brief  Configure ADC peripheral
  * @param  None
  * @retval None
  */
void _Device_ADC_Config_Init(void){
    unsigned int i;


    GPIO_Init(ADC_IDSG_PORT, ADC_IDSG_PIN, GPIO_Mode_In_FL_No_IT);  /*!< Input floating, No external interrupt */
    GPIO_Init(ADC_ICHG_PORT, ADC_ICHG_PIN, GPIO_Mode_In_FL_No_IT);  /*!< Input floating, No external interrupt */
    GPIO_Init(ADC_VBAT_PORT, ADC_VBAT_PIN, GPIO_Mode_In_FL_No_IT);  /*!< Input floating, No external interrupt */
    GPIO_Init(ADC_NTC1_PORT, ADC_NTC1_PIN, GPIO_Mode_In_FL_No_IT);  /*!< Input floating, No external interrupt */
    GPIO_Init(ADC_NTC2_PORT, ADC_NTC2_PIN, GPIO_Mode_In_FL_No_IT);  /*!< Input floating, No external interrupt */

    _Device_ADC_Config_All_Channel_Scan();
    for(i = 0; i < ADC_DETECTION_CHANNEL_NUMS; i++){
        ADC_Buffer[i] = 0;
    }
    ADC_SUM_TEMP_Buffer = 0;
}



/**
  * @brief  Configure ADC peripheral
  * @param  None
  * @retval None
  */
void _Device_ADC_Config_All_Channel_Scan(void)
{
    unsigned int i,j;
//GPIO_HIGH(LED2_PORT, LED2_PIN);
    /* Enable ADC1 clock */
    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);
    /* Initialise and configure ADC1 */
    ADC_Init(ADC1, ADC_ConversionMode_Single,ADC_Resolution_12Bit, ADC_Prescaler_1);
    ADC_SamplingTimeConfig(ADC1, ADC_Group_SlowChannels, ADC_SamplingTime_16Cycles);

    /* Enable ADC1 */
    ADC_Cmd(ADC1, ENABLE);
    /* disable SchmittTrigger for ADC_Channel_24, to save power */
    ADC_SchmittTriggerConfig(ADC1, ADC_Channel_24, DISABLE);
    for(i = 0; i < ADC_DETECTION_CHANNEL_NUMS; i++){
        if(ADC_Channel_Array[i] == ADC_Channel_Vrefint){
            /* for the Internal Voltage reference */
            ADC_VrefintCmd(ENABLE);
            /* Enable ADC1 ADC_Channel_Vrefint channels */
            ADC_ChannelCmd(ADC1, ADC_Channel_Vrefint, ENABLE);
        }else{
            ADC_SchmittTriggerConfig(ADC1, ADC_Channel_Array[i], DISABLE);
            /* Enable ADC1 Channels*/
            ADC_ChannelCmd(ADC1, ADC_Channel_Array[i], ENABLE);
        }
        // read for dummy and for stable
        /* start ADC convertion by software */
        ADC_SoftwareStartConv(ADC1);
        /* wait until end-of-covertion */
        while( ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0 );
        /* read ADC convertion result */
        ADC_SUM_TEMP_Buffer = ADC_GetConversionValue(ADC1);// for stable

        /* read result */
        ADC_SUM_TEMP_Buffer = 0;
        for(j = 0; j < ADC_REPEAT_TIMES; j++)
        //for(j = 0; j < 2; j++)
        {
            /* start ADC convertion by software */
            ADC_SoftwareStartConv(ADC1);
            /* wait until end-of-covertion */
            while( ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0 );
            /* read ADC convertion result */
            //ADC_Buffer[i] = ADC_GetConversionValue(ADC1);   // get last adc values
            ADC_SUM_TEMP_Buffer += ADC_GetConversionValue(ADC1);   // sum of adc values
        }
        ADC_Buffer[i] = (ADC_SUM_TEMP_Buffer >> ADC_SUM_Of_Temp_Buffer_Shift_TIMES);  // sum / times
        if(ADC_Channel_Array[i] == ADC_Channel_Vrefint){
            /* de-initialize ADC */
            ADC_VrefintCmd(DISABLE);
            ADC_ChannelCmd(ADC1, ADC_Channel_Vrefint, DISABLE);
        }else{
            ADC_ChannelCmd(ADC1, ADC_Channel_Array[i], DISABLE);
        }
    }

    /* disable ADC1 */
    ADC_Cmd(ADC1, DISABLE);
    /* Enable ADC1 clock */
    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, DISABLE);


//    /* for the Internal Voltage reference */
//    ADC_VrefintCmd(ENABLE);
//    /* Enable ADC1 ADC_Channel_Vrefint channels */
//    ADC_ChannelCmd(ADC1, ADC_Channel_Vrefint, ENABLE);

    //GPIO_HIGH(LED1_PORT, LED1_PIN);
    //GPIO_LOW(LED1_PORT, LED1_PIN);
//GPIO_LOW(LED2_PORT, LED2_PIN);
}

unsigned int _Device_Get_ADC_Channel_Buffer(unsigned int channelNum){
    if(channelNum >= ADC_DETECTION_CHANNEL_NUMS){
        return 0;
    }else{
        return    ADC_Buffer[channelNum];
    }
}

unsigned int _Device_Get_VRef_mVoltage(){
    unsigned int i;
    float fl;
    for(i = 0; i < ADC_DETECTION_CHANNEL_NUMS; i++){
        if(ADC_Channel_Array[i] == ADC_Channel_Vrefint){
            //fl = 1.224f; //internal Vref (V)
            fl = 1224.0f; //internal Vref (mV)
            fl = fl / (float)ADC_Buffer[i];
            fl = fl * 4096.0f;
            return (unsigned int)fl;
        }
    }
    return 0;
}

/**
  * @brief  Configure DMA peripheral
  * @param  None
  * @retval None
  */
void ADC_DMA_Config(void)
{
//    unsigned int i,j;
//    ADCRepeatReadIndex = 0;
//    for(i = 0; i < BUFFER_SIZE; i++){
//        for( j = 0; j < ADC_REPEAT_TIMES; j++){
//            ADC_Read_Buffers[i][j] = 0;
//        }
//        Buffer[i] = 0;
//    }
    /* Enable ADC1 clock */
    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);

    /* Enable DMA1 clock */
    CLK_PeripheralClockConfig(CLK_Peripheral_DMA1, ENABLE);

    /* Initialize and configure ADC1 */
//    ADC_Init(ADC1, ADC_ConversionMode_Single, ADC_Resolution_12Bit, ADC_Prescaler_2);
//    ADC_SamplingTimeConfig(ADC1, ADC_Group_SlowChannels, ADC_SamplingTime_384Cycles);
//    ADC_SamplingTimeConfig(ADC1, ADC_Group_FastChannels, ADC_SamplingTime_384Cycles);
    ADC_Init(ADC1, ADC_ConversionMode_Single, ADC_Resolution_12Bit, ADC_Prescaler_1);
    ADC_SamplingTimeConfig(ADC1, ADC_Group_SlowChannels, ADC_SamplingTime_96Cycles);
    ADC_SamplingTimeConfig(ADC1, ADC_Group_FastChannels, ADC_SamplingTime_96Cycles);

    /* Enable ADC1 Channels*/
    ADC_ChannelCmd(ADC1, ADC_Channel_0, ENABLE);/* connected to VBAT */
    ADC_ChannelCmd(ADC1, ADC_Channel_1, ENABLE);/* connected to ICHG */
    ADC_ChannelCmd(ADC1, ADC_Channel_2, ENABLE);/* connected to IDSG */
    ADC_ChannelCmd(ADC1, ADC_Channel_4, ENABLE);/* connected to T1 */
    ADC_ChannelCmd(ADC1, ADC_Channel_5, ENABLE);/* connected to T2 */
    ADC_ChannelCmd(ADC1, ADC_Channel_6, ENABLE);/* connected to None */

    /* Disable SchmittTrigger for ADC_Channel, to save power */
    ADC_SchmittTriggerConfig(ADC1, ADC_Channel_0, DISABLE);
    ADC_SchmittTriggerConfig(ADC1, ADC_Channel_1, DISABLE);
    ADC_SchmittTriggerConfig(ADC1, ADC_Channel_2, DISABLE);
    ADC_SchmittTriggerConfig(ADC1, ADC_Channel_4, DISABLE);
    ADC_SchmittTriggerConfig(ADC1, ADC_Channel_5, DISABLE);
    ADC_SchmittTriggerConfig(ADC1, ADC_Channel_6, DISABLE);

    /* Enable ADC1 */
    ADC_Cmd(ADC1, ENABLE);

  /* Connect ADC to DMA channel 0 */
  SYSCFG_REMAPDMAChannelConfig(REMAP_DMA1Channel_ADC1ToChannel0);

  DMA_Init(DMA1_Channel0, BUFFER_ADDRESS,
           ADC1_DR_ADDRESS,
           BUFFER_SIZE,
           DMA_DIR_PeripheralToMemory,
           DMA_Mode_Circular,
           DMA_MemoryIncMode_Inc,
           DMA_Priority_High,
           DMA_MemoryDataSize_HalfWord);

  /* DMA Channel0 enable */
  DMA_Cmd(DMA1_Channel0, ENABLE);

  /* Enable DMA1 channel0 Transfer complete interrupt */
  DMA_ITConfig(DMA1_Channel0, DMA_ITx_TC, ENABLE);

  /* DMA enable */
  DMA_GlobalCmd(ENABLE);
}

void Setting_ADC_DMA_Enable(unsigned char enable){
    if(enable){
        ADC_DMA_Config();
    }else{
        /* disable ADC1 */
        ADC_Cmd(ADC1, DISABLE);
        /* DMA disable */
        DMA_GlobalCmd(DISABLE);
        /* DMA Channel0 disable */
        DMA_Cmd(DMA1_Channel0, DISABLE);
        /* Enable ADC1 clock */
        CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, DISABLE);

        /* Enable DMA1 clock */
        CLK_PeripheralClockConfig(CLK_Peripheral_DMA1, DISABLE);
    }

}



/********************************************************************************
* DMA1_CHANNEL0_1_IRQHandler													*
*******************************************************************************/
/**
  * @brief DMA1 channel0 and channel1 Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#if defined(_IAR_)	
INTERRUPT_HANDLER(DMA1_CHANNEL0_1_IRQHandler,2)
{
#endif
#if defined(_COSMIC_)	
INTERRUPT void DMA1_CHANNEL0_1_IRQHandler(void)
{
#endif
    //GPIO_HIGH(LED1_PORT, LED1_PIN);


    /* Clear IT Pending Bit */
    DMA_ClearITPendingBit(DMA1_IT_TC0);


    Setting_ADC_DMA_Enable(DeviceOff);

    //GPIO_LOW(LED1_PORT, LED1_PIN);

}
