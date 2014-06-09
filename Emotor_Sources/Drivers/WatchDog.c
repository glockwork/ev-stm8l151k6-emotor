
/**
  ******************************************************************************
  * @file    WatchDog.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   Watch Dog setting
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
////////////////////////////////////////////////////////////////////////////
// for SYSCLK = 4MHz
  /* WWDG configuration: WWDG is clocked by SYSCLK = 4MHz */
  /* WWDG timeout is equal to 196.608 ms */
  /* Watchdog Window = (COUNTER_INIT - 63) * 1 step
                     = (127 - 63) * (12288 / 4Mhz)
                     = 64 * (0.003072)
                     = 196.608 ms
  */
  /* Non Allowed Window = (COUNTER_INIT - WINDOW_VALUE) * 1 step
                        = (127 - 126) * 1 step
                        =  1 * 1 step
                        =  1 * (12288 / 4Mhz)
                        =  1 * (0.003072)
                        =  3.072 ms
   */
  /* So the non allowed window starts from 0.0 ms to 3.072 ms
  and the allowed window starts from 3.072 ms to 196.608 ms
  If refresh is done during non allowed window, a reset will occur.
  If refresh is done during allowed window, no reset will occur.
  If the WWDG down counter reaches 63, a reset will occur. */
////////////////////////////////////////////////////////////////////////////
// for SYSCLK = 8MHz
  /* WWDG configuration: WWDG is clocked by SYSCLK = 8MHz */
  /* WWDG timeout is equal to 251,9 ms */
  /* Watchdog Window = (COUNTER_INIT - 63) * 1 step
                     = (127 - 63) * (12288 / 8Mhz)
                     = 64 * (0.001536)
                     = 98.304 ms
  */
  /* Non Allowed Window = (COUNTER_INIT - WINDOW_VALUE) * 1 step
                        = (127 - 126) * 1 step
                        =  1 * 1 step
                        =  1 * (12288 / 8Mhz)
                        =  1 * (0.001536)
                        =  1.536 ms
   */
  /* So the non allowed window starts from 0.0 ms to 3.072 ms
  and the allowed window starts from 3.072 ms to 196.608 ms
  If refresh is done during non allowed window, a reset will occur.
  If refresh is done during allowed window, no reset will occur.
  If the WWDG down counter reaches 63, a reset will occur. */
#define WWDG_COUNTER_INIT       127  // 7 bits, max = 127 (0x7f)
#define WWDG_WINDOW_VALUE       (WWDG_COUNTER_INIT - 1)  // 7 bits, max = 127


#define IWDG_RELOAD_VALUE   254

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
  * @brief Configures the WWDG to generate a Reset if the WWDG is not refreshed
  *         during the correct window.
  * @param  None
  * @retval None
  */

void _Device_WWDG_Config(void)
{
    ////////////////////////////////////////////////////////////////////////////
    // for SYSCLK = 2MHz
  /* WWDG configuration: WWDG is clocked by SYSCLK = 2MHz */
  /* WWDG timeout is equal to 251.9 ms */
  /* Watchdog Window = (COUNTER_INIT - 63) * 1 step
                     = 41 * (12288 / 2Mhz)
                     = 41 * (0.006144)
                     = 251.9 ms
  */
  /* Non Allowed Window = (COUNTER_INIT - WINDOW_VALUE) * 1 step
                        = (104 - 97) * 1 step
                        =  7 * 1 step
                        =  7 * (12288 / 2Mhz)
                        =  7 * (0.006144)
                        =  43.008 ms
   */
  /* So the non allowed window starts from 0.0 ms to 43.008 ms
  and the allowed window starts from 43.008 ms to 251,9 ms
  If refresh is done during non allowed window, a reset will occur.
  If refresh is done during allowed window, no reset will occur.
  If the WWDG down counter reaches 63, a reset will occur. */

    ////////////////////////////////////////////////////////////////////////////
    // for SYSCLK = 4MHz
  /* WWDG configuration: WWDG is clocked by SYSCLK = 4MHz */
  /* WWDG timeout is equal to 251,9 ms */
  /* Watchdog Window = (COUNTER_INIT - 63) * 1 step
                     = 41 * (12288 / 4Mhz)
                     = 41 * (0.003072)
                     = 125.9 ms
  */
  /* Non Allowed Window = (COUNTER_INIT - WINDOW_VALUE) * 1 step
                        = (104 - 97) * 1 step
                        =  7 * 1 step
                        =  7 * (12288 / 4Mhz)
                        =  7 * (0.003072)
                        =  21.504 ms
   */
  /* So the non allowed window starts from 0.0 ms to 43.008 ms
  and the allowed window starts from 43.008 ms to 251,9 ms
  If refresh is done during non allowed window, a reset will occur.
  If refresh is done during allowed window, no reset will occur.
  If the WWDG down counter reaches 63, a reset will occur. */

    WWDG_Init(WWDG_COUNTER_INIT, WWDG_WINDOW_VALUE);
}

void _Device_Reset_WWDG_Counter(){
    /* wait until WWDG counter becomes higher than window value */
    if ((WWDG_GetCounter() & 0x7F) < WWDG_WINDOW_VALUE){
        /* Refresh WWDG counter during non allowed window so MCU reset will occur */
        WWDG_SetCounter(WWDG_COUNTER_INIT);
    }
}

//==============================================================================
// Private functions
//==============================================================================
/**
  * @brief  Configures the IWDG to generate a Reset if it is not refreshed at the
  *         correct time.
  * @param  None
  * @retval None
  */
void _Device_IWDG_Config(void)
{
  /* IWDG timeout equal to 214 ms (the timeout may varies due to LSI frequency
     dispersion) */
  /* Enable write access to IWDG_PR and IWDG_RLR registers */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

  /* IWDG configuration: IWDG is clocked by LSI = 38KHz */
  //IWDG_SetPrescaler(IWDG_Prescaler_64);
  IWDG_SetPrescaler(IWDG_Prescaler_256);

  /* IWDG timeout equal to 214.7 ms (the timeout may varies due to LSI frequency dispersion) */
  /* IWDG timeout = (RELOAD_VALUE + 1) * Prescaler / LSI
                  = (254 + 1) * 64 / 38 000
                  = 429.47 ms */
  /* IWDG timeout = (RELOAD_VALUE + 1) * Prescaler / LSI
                  = (254 + 1) * 32 / 38 000
                  = 214.7 ms */
  /* IWDG timeout = (RELOAD_VALUE + 1) * Prescaler / LSI
                  = (254 + 1) * 256 / 38 000
                  = 1717.8 ms */
  IWDG_SetReload((uint8_t)IWDG_RELOAD_VALUE);

  /* Reload IWDG counter */
  IWDG_ReloadCounter();

  /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
  IWDG_Enable();
}

unsigned char _Device_IsResumedByIWDG(){

  /* Check if the system has resumed from IWDG reset */
  if (RST_GetFlagStatus(RST_FLAG_IWDGF) != RESET)
  {
    /* IWDGF flag set */
    /* Clear IWDGF Flag */
    RST_ClearFlag(RST_FLAG_IWDGF);
      return true;
  }
  else
  {
    /* IWDGF flag is not set */
      return false;
  }
}


void _Device_Reload_IWDG_Counter(){
    /* Reload IWDG counter */
    IWDG_ReloadCounter();
}
