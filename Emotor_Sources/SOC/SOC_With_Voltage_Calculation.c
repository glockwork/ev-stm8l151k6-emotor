#include "Driver_User_Interface.h"
#include "Global_Variable_Define.h"
#include "Vars_Bits_Define.h"
#include "Protection_Polling_Func.h"
#include "Config_Info\System_Config_Info.h"
#include "SOC_With_Temperature_Calculation.h"

#if (_Capacity_Showing_Use_Voltage_ == 1)

#if defined(_CELL_TYPE_SDI_26H_) && (_CELL_SERIES_NUMBER_ == 10) && (_CELL_PARALLEL_NUMBER_ == 5)
    #include "inc_SOC_10S_SDI_26H\SOC_TABLE_CHG_10S_5P_WITH_TEMP_26H.h"
#elif defined(_CELL_TYPE_SDI_26H_) && (_CELL_SERIES_NUMBER_ == 10) && (_CELL_PARALLEL_NUMBER_ == 4)
    #include "inc_SOC_10S_SDI_26H\SOC_TABLE_CHG_10S_4P_WITH_TEMP_26H.h"
#elif defined(_CELL_TYPE_SDI_26H_) && (_CELL_SERIES_NUMBER_ == 10) && (_CELL_PARALLEL_NUMBER_ == 3)
    #include "inc_SOC_10S_SDI_26H\SOC_TABLE_CHG_10S_3P_WITH_TEMP_26H.h"


#elif defined(_CELL_TYPE_SDI_26H_) && (_CELL_SERIES_NUMBER_ == 7) && (_CELL_PARALLEL_NUMBER_ == 3)
    #include "inc_SOC_7S_SDI_26H\SOC_TABLE_CHG_7S_3P_WITH_TEMP_26H.h"
#elif defined(_CELL_TYPE_SDI_26H_) && (_CELL_SERIES_NUMBER_ == 7) && (_CELL_PARALLEL_NUMBER_ == 2)
    #include "inc_SOC_7S_SDI_26H\SOC_TABLE_CHG_7S_2P_WITH_TEMP_26H.h"


#elif defined(_CELL_TYPE_SDI_26H_) && (_CELL_SERIES_NUMBER_ == 13) && (_CELL_PARALLEL_NUMBER_ == 4)
    #include "inc_SOC_13S_SDI_26H\SOC_TABLE_CHG_13S_4P_WITH_TEMP_26H.h"
#elif defined(_CELL_TYPE_SDI_26H_) && (_CELL_SERIES_NUMBER_ == 13) && (_CELL_PARALLEL_NUMBER_ == 3)
    #include "inc_SOC_13S_SDI_26H\SOC_TABLE_CHG_13S_3P_WITH_TEMP_26H.h"

#elif defined(_CELL_TYPE_SDI_22H_) && (_CELL_SERIES_NUMBER_ == 13) && (_CELL_PARALLEL_NUMBER_ == 4)
    #include "inc_SOC_13S_SDI_22H\SOC_TABLE_CHG_13S_4P_WITH_TEMP_22H.h"
#elif defined(_CELL_TYPE_SDI_22H_) && (_CELL_SERIES_NUMBER_ == 13) && (_CELL_PARALLEL_NUMBER_ == 3)
    #include "inc_SOC_13S_SDI_22H\SOC_TABLE_CHG_13S_3P_WITH_TEMP_22H.h"

#elif defined(_CELL_TYPE_SDI_26F_) && (_CELL_SERIES_NUMBER_ == 10) && (_CELL_PARALLEL_NUMBER_ == 4)
    #include "inc_SOC_10S_SDI_26F\SOC_TABLE_CHG_10S_4P_WITH_TEMP_26F.h"
#elif defined(_CELL_TYPE_SDI_26F_) && (_CELL_SERIES_NUMBER_ == 10) && (_CELL_PARALLEL_NUMBER_ == 3)
    #include "inc_SOC_10S_SDI_26F\SOC_TABLE_CHG_10S_3P_WITH_TEMP_26F.h"

#else
    #error "Please select Cell Type and SERIES/PARALLEL Number ."
#endif

////////////////////////////////////////////////////////////////////////////////
#if (_LED_SETTING_NUMBERS_ == 0)
    #error "Can not use _Capacity_Showing_Use_Voltage_ without showing Led capacity."
#endif
////////////////////////////////////////////////////////////////////////////////
#if (_CELL_SERIES_NUMBER_ == 13)

#elif (_CELL_SERIES_NUMBER_ == 10)
    #if (_LED_SETTING_NUMBERS_ == 3)
        //////////////////////////////////////////////////////////////////////////
        // for 3 LEDs DSG display with 4 status
        // 4 status :
        // status1 : blinking led1 ==> under and include Capacity_Voltage_mV_TH_1.
        // status2 : light led1 ==>    under and include Capacity_Voltage_mV_TH_2. and bigger than Capacity_Voltage_mV_TH_1.
        // status3 : light led2 ==>    under and include Capacity_Voltage_mV_TH_3. and bigger than Capacity_Voltage_mV_TH_2.
        // status4 : light led3 ==>    bigger than Capacity_Voltage_mV_TH_3.
        #define Capacity_Voltage_mV_TH_1    (36500)
        #define Capacity_Voltage_mV_TH_2    (37500)
        #define Capacity_Voltage_mV_TH_3    (39000)
    #elif (_LED_SETTING_NUMBERS_ == 4)
        //////////////////////////////////////////////////////////////////////////
        // for 4 LEDs DSG display with 5 status
        // 5 status :
        // status1 : blinking led1 ==> under and include Capacity_Voltage_mV_TH_1.
        // status2 : light led1 ==>    under and include Capacity_Voltage_mV_TH_2. and bigger than Capacity_Voltage_mV_TH_1.
        // status3 : light led2 ==>    under and include Capacity_Voltage_mV_TH_3. and bigger than Capacity_Voltage_mV_TH_2.
        // status4 : light led3 ==>    under and include Capacity_Voltage_mV_TH_4. and bigger than Capacity_Voltage_mV_TH_3.
        // status5 : light led4 ==>    bigger than Capacity_Voltage_mV_TH_4.
        #define Capacity_Voltage_mV_TH_1    (36500)
        #define Capacity_Voltage_mV_TH_2    (37500)
        #define Capacity_Voltage_mV_TH_3    (38000)
        #define Capacity_Voltage_mV_TH_4    (39000)
    #elif (_LED_SETTING_NUMBERS_ == 5)
        //////////////////////////////////////////////////////////////////////////
        // for 5 LEDs DSG display with 6 status
        // 6 status :
        // status1 : blinking led1 ==> under and include Capacity_Voltage_mV_TH_1.
        // status2 : light led1 ==>    under and include Capacity_Voltage_mV_TH_2. and bigger than Capacity_Voltage_mV_TH_1.
        // status3 : light led2 ==>    under and include Capacity_Voltage_mV_TH_3. and bigger than Capacity_Voltage_mV_TH_2.
        // status4 : light led3 ==>    under and include Capacity_Voltage_mV_TH_4. and bigger than Capacity_Voltage_mV_TH_3.
        // status5 : light led4 ==>    under and include Capacity_Voltage_mV_TH_5. and bigger than Capacity_Voltage_mV_TH_4.
        // status6 : light led5 ==>    bigger than Capacity_Voltage_mV_TH_5.
        #define Capacity_Voltage_mV_TH_1    (33500)
        #define Capacity_Voltage_mV_TH_2    (36500)
        #define Capacity_Voltage_mV_TH_3    (37500)
        #define Capacity_Voltage_mV_TH_4    (38000)
        #define Capacity_Voltage_mV_TH_5    (39000)
    #endif
#elif (_CELL_SERIES_NUMBER_ == 7)
#else
    #error "Please select Cell Type and SERIES Number ."
#endif

unsigned char getBatteryCapacity(unsigned int ADC_Voltage, unsigned int ADC_current,  unsigned int ADC_Temperature, unsigned char CurrentCode){
  float temp_f2;
  unsigned int real_vol;
  unsigned char chg_temp_index;
  //unsigned char dsg_current_index;
  //const unsigned int *dsg_temp_ocv_table_ptr;
  //unsigned char dsg_temp_index;
  //unsigned int OV_Capacity;
  //unsigned int UV_Capacity;
  unsigned int Capa;


  temp_f2 = (float)ADC_Voltage;
  real_vol = (unsigned int)(temp_f2 / VBAT_mV_To_ADC_Factor);

    if(  CurrentCode == CurrentInCHG ){
        //CHG
        if(ADC_Temperature >= _ADC_LOOKUP_CHG_TEMP_1_TH_){
            chg_temp_index = RESIDUAL_CHG_1st_Degrees_INDEX;
        }else if(ADC_Temperature >= _ADC_LOOKUP_CHG_TEMP_2_TH_){
            chg_temp_index = RESIDUAL_CHG_2nd_Degrees_INDEX;
        }else{
            chg_temp_index = RESIDUAL_CHG_3rd_Degrees_INDEX;
        }
        Capa = getCHGCapacityByTable(real_vol, chg_temp_index);
    }else{
        //Static and DSG
        Capa = 0;
#if (_LED_SETTING_NUMBERS_ == 3)
        if(real_vol <= Capacity_Voltage_mV_TH_1){
            Capa = DSG_CAPACITY_DISPLAY_TH_1 - 1;
        }else if (real_vol <= Capacity_Voltage_mV_TH_2){
            Capa = DSG_CAPACITY_DISPLAY_TH_2 - 1;
        }else if (real_vol <= Capacity_Voltage_mV_TH_3){
            Capa = DSG_CAPACITY_DISPLAY_TH_3 - 1;
        }else{
            Capa = DSG_CAPACITY_DISPLAY_TH_3 + 5;
        }
#elif (_LED_SETTING_NUMBERS_ == 4)
        if(real_vol <= Capacity_Voltage_mV_TH_1){
            Capa = DSG_CAPACITY_DISPLAY_TH_1 - 1;
        }else if (real_vol <= Capacity_Voltage_mV_TH_2){
            Capa = DSG_CAPACITY_DISPLAY_TH_2 - 1;
        }else if (real_vol <= Capacity_Voltage_mV_TH_3){
            Capa = DSG_CAPACITY_DISPLAY_TH_3 - 1;
        }else if (real_vol <= Capacity_Voltage_mV_TH_4){
            Capa = DSG_CAPACITY_DISPLAY_TH_4 - 1;
        }else{
            Capa = DSG_CAPACITY_DISPLAY_TH_4 + 5;
        }
#elif (_LED_SETTING_NUMBERS_ == 5)
        if(real_vol <= Capacity_Voltage_mV_TH_1){
            Capa = DSG_CAPACITY_DISPLAY_TH_1 - 1;
        }else if (real_vol <= Capacity_Voltage_mV_TH_2){
            Capa = DSG_CAPACITY_DISPLAY_TH_2 - 1;
        }else if (real_vol <= Capacity_Voltage_mV_TH_3){
            Capa = DSG_CAPACITY_DISPLAY_TH_3 - 1;
        }else if (real_vol <= Capacity_Voltage_mV_TH_4){
            Capa = DSG_CAPACITY_DISPLAY_TH_4 - 1;
        }else if (real_vol <= Capacity_Voltage_mV_TH_5){
            Capa = DSG_CAPACITY_DISPLAY_TH_5 - 1;
        }else{
            Capa = DSG_CAPACITY_DISPLAY_TH_5 + 5;
        }
#endif
        return Capa;
    }//if(  CurrentCode == CurrentInCHG ){ - else - esle -


    temp_f2 = Capa;
    temp_f2 = temp_f2 / 100;
    return (unsigned char)temp_f2;
}
//用查表法，計算DSG SOC
unsigned int getDSGCapacityByTable(unsigned int real_mVoltage, unsigned char current_Index, unsigned char temp_Index){
  return 0;
}

//用查表法，計算CHG SOC
unsigned int getCHGCapacityByTable(unsigned int real_mVoltage, unsigned char temp_Index){
  unsigned int capacity;

  unsigned char i;

  capacity = 0;
  if(real_mVoltage >= CHG_OCVTable[0][temp_Index]){
      capacity = CHG_OCVTable[0][RESIDUAL_CHG_CAPACITY_INDEX];
  }else if(real_mVoltage <= CHG_OCVTable[CHG_OCV_TABLE_POINTS - 1][temp_Index]){
      capacity = CHG_OCVTable[CHG_OCV_TABLE_POINTS - 1][RESIDUAL_CHG_CAPACITY_INDEX];
  }else{
      for(i = 1; i < CHG_OCV_TABLE_POINTS; i++){
          if(real_mVoltage >= CHG_OCVTable[i][temp_Index]){ //取較小值
              capacity = CHG_OCVTable[i][RESIDUAL_CHG_CAPACITY_INDEX];
              break;
          }
      }//for
  }
  return capacity;
}
//用查表法，計算Static SOC
unsigned int getStaticCapacityByTable(unsigned int real_mVoltage){
  return 0;
}

#endif
