/**
  ******************************************************************************
  * @file    EEPROM_Access.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   EEPROM Write/Read setting
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
  * @brief  EEPROM Access Init
  * @param  None
  * @retval None
  */
void _Device_EEPROM_Access_Enable(){

  /* Define flash programming Time*/
  FLASH_SetProgrammingTime(FLASH_ProgramTime_Standard);

  /* Unlock flash data eeprom memory */
  FLASH_Unlock(FLASH_MemType_Data);
  /* Wait until Data EEPROM area unlocked flag is set*/
  while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET);
}

void _Device_EEPROM_Access_Disable(){

    /* Lock Data memory */
    FLASH_Lock(FLASH_MemType_Data);
}

// abour 5.6ms
unsigned char _Device_EEPROM_WriteByte(unsigned int Write_Address, unsigned char data){

    unsigned char val;

    if((Write_Address < Eeprom_Start_Add) || (Write_Address > Eeprom_End_Add)){
        return Func_Fail;   //fail
    }

//    /* Define FLASH programming time */
//    FLASH_SetProgrammingTime(FLASH_ProgramTime_Standard);
//
//    /* Unlock Data memory */
//    FLASH_Unlock(FLASH_MEMTYPE_DATA);
//    /* Wait until Data EEPROM area unlocked flag is set*/
//    while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET)
//    {}

    /* Program byte at the address */
    FLASH_ProgramByte( Write_Address, data);

    //_Device_delay_cycles(500);     //500 = 5ms at CCLK=4MHz.
    //_Device_delay_cycles(1000);    //1000 = 5.38ms at CCLK=8MHz.
    _Device_delay_cycles(500);     //500 = 2.6ms at CCLK=8MHz.
    _Device_delay_cycles(100);     //100 = 550us at CCLK=8MHz.

    /* Check program action */
    val = FLASH_ReadByte(Write_Address);
//    /* Lock Data memory */
//    FLASH_Lock(FLASH_MemType_Data);
    if (val != data)
    {
        /* Error */
        //OperationStatus = FAILED;
        ///* OperationStatus = PASSED, if the data written/read to/from DATA EEPROM memory is correct */
        ///* OperationStatus = FAILED, if the data written/read to/from DATA EEPROM memory is corrupted */
        return Func_Fail;    //fail
    }else{
        return Func_Complete;    //pass
    }
}

// abour 5.6ms
unsigned char _Device_EEPROM_WriteDoubleWord(unsigned int Write_Address, unsigned long data){

    unsigned char val, val1, check;
	int i;

    if((Write_Address < Eeprom_Start_Add) || ((Write_Address + 4) > Eeprom_End_Add)){
        return Func_Fail;   //fail
    }

    /* Program Dword at the address*/
    FLASH_ProgramWord(Write_Address, data);

    //_Device_delay_cycles(500);     //500 = 5ms at CCLK=4MHz.
    //_Device_delay_cycles(1000);    //1000 = 5.38ms at CCLK=8MHz.
    _Device_delay_cycles(500);     //500 = 2.6ms at CCLK=8MHz.
    _Device_delay_cycles(100);     //100 = 550us at CCLK=8MHz.

    /* Check program action */
    check = 0;
    for( i=0; i<4; i++){
        val = FLASH_ReadByte(Write_Address + i);
        val1 = *((unsigned char *)(&data)+i);
        if (val != val1)
        {
            /* Error */
            //OperationStatus = FAILED;
            ///* OperationStatus = PASSED, if the data written/read to/from DATA EEPROM memory is correct */
            ///* OperationStatus = FAILED, if the data written/read to/from DATA EEPROM memory is corrupted */
            check += 1;    //fail
        }else{
            check += 0;    //pass
        }

    }

//    /* Lock Data memory */
//    FLASH_Lock(FLASH_MEMTYPE_DATA);

    if(check == 0){
        return Func_Complete;
    }else{
        return Func_Fail;
    }
}

