
#include "Config_Info\System_Config_Info.h"

#if     defined(_NTC_MITSUBISHI_H_TYPE_3370_)
    #include "NTC_ADC_TO_TEMP_Table__MITSUBISHI_H_TYPE_3370.h"
#elif   defined(_NTC_THINKING_TYPE_3435_)
    #include "NTC_ADC_TO_TEMP_Table__THINKING_TYPE_3435.h"
#elif   defined(_NTC_MITSUBISHI_H_TYPE_3413_)
    #include "NTC_ADC_TO_TEMP_Table__MITSUBISHI_H_TYPE_3413.h"
#elif   defined(_NTC_MITSUBISHI_J_TYPE_3450_)
    #include "NTC_ADC_TO_TEMP_Table__MITSUBISHI_J_TYPE_3450.h"
#else
    #error "Please select right NTC Type"
#endif


signed int Get_CentigradeDegree_By_NTC_ADC(unsigned int Ntc_Adc){
    signed int Celsius_temp;
    unsigned int i;
    signed int ntc_adc;
    ntc_adc = (signed int)Ntc_Adc;
    Celsius_temp = 0;
    if(ntc_adc >= NTC_ADC_TO_TEMP_Table[0][TEMPERATURE_ADC_Index]){
        Celsius_temp = NTC_ADC_TO_TEMP_Table[0][TEMPERATURE_Celsius_Index];
    }else if(ntc_adc <= NTC_ADC_TO_TEMP_Table[TEMPERATURE_TABLE_POINTS - 1][TEMPERATURE_ADC_Index]){
        Celsius_temp = NTC_ADC_TO_TEMP_Table[TEMPERATURE_TABLE_POINTS - 1][TEMPERATURE_Celsius_Index];
    }else{
      for(i = 1; i < TEMPERATURE_TABLE_POINTS; i++){
          if(ntc_adc >= NTC_ADC_TO_TEMP_Table[i][TEMPERATURE_ADC_Index]){ //取較小值
              Celsius_temp = NTC_ADC_TO_TEMP_Table[i][TEMPERATURE_Celsius_Index];
              break;
          }
      }//for
    }
    return Celsius_temp;
}
unsigned int Get_KelvinDegree_By_NTC_ADC(unsigned int Ntc_Adc){
    signed int Celsius_temp;

    Celsius_temp = Get_CentigradeDegree_By_NTC_ADC(Ntc_Adc);
    Celsius_temp = Celsius_temp * 10;   // transfor to 0.1 degrees unit
    Celsius_temp = 2731 + Celsius_temp; // transfor to 0.1 Kelvin Degree unit
    return (unsigned int)Celsius_temp;
}

#if 0   //bug
unsigned int Get_CentigradeDegree_By_NTC_ADC(unsigned int Ntc_Adc){
    unsigned int Celsius_temp;
    unsigned int i;

    Celsius_temp = 0;
    if(ntc_adc >= NTC_ADC_TO_TEMP_Table[0][TEMPERATURE_ADC_Index]){
        Celsius_temp = NTC_ADC_TO_TEMP_Table[0][TEMPERATURE_Celsius_Index];
    }else if(ntc_adc <= NTC_ADC_TO_TEMP_Table[TEMPERATURE_TABLE_POINTS - 1][TEMPERATURE_ADC_Index]){
        Celsius_temp = NTC_ADC_TO_TEMP_Table[TEMPERATURE_TABLE_POINTS - 1][TEMPERATURE_Celsius_Index];
    }else{
      for(i = 1; i < TEMPERATURE_TABLE_POINTS; i++){
          if(ntc_adc >= NTC_ADC_TO_TEMP_Table[i][TEMPERATURE_ADC_Index]){ //取較小值
              Celsius_temp = NTC_ADC_TO_TEMP_Table[i][TEMPERATURE_Celsius_Index];
              break;
          }
      }//for
    }
    return Celsius_temp;
}
unsigned int Get_KelvinDegree_By_NTC_ADC(unsigned int Ntc_Adc){
    unsigned int Celsius_temp;

    Celsius_temp = Get_CentigradeDegree_By_NTC_ADC(ntc_adc);
    Celsius_temp = Celsius_temp * 10;   // transfor to 0.1 degrees unit
    Celsius_temp = 2731 + Celsius_temp; // transfor to Kelvin Degree unit
    return Celsius_temp;
}
#endif
//unsigned int Get_KelvinDegree_By_NTC_ADC(unsigned int ntc_adc){
//    unsigned int Celsius_temp;
//    unsigned int i;
//
//    if(ntc_adc >= NTC_ADC_TO_TEMP_Table[0][TEMPERATURE_ADC_Index]){
//        Celsius_temp = NTC_ADC_TO_TEMP_Table[0][TEMPERATURE_Celsius_Index];
//    }else if(ntc_adc <= NTC_ADC_TO_TEMP_Table[TEMPERATURE_TABLE_POINTS - 1][TEMPERATURE_ADC_Index]){
//        Celsius_temp = NTC_ADC_TO_TEMP_Table[TEMPERATURE_TABLE_POINTS - 1][TEMPERATURE_Celsius_Index];
//    }else{
//      for(i = 1; i < TEMPERATURE_TABLE_POINTS; i++){
//          if(ntc_adc >= NTC_ADC_TO_TEMP_Table[i][TEMPERATURE_ADC_Index]){ //取較小值
//              Celsius_temp = NTC_ADC_TO_TEMP_Table[i][TEMPERATURE_Celsius_Index];
//              break;
//          }
//      }//for
//    }
//    Celsius_temp = Celsius_temp * 10;   // transfor to 0.1 degrees unit
//    Celsius_temp = 2731 + Celsius_temp; // transfor to Kelvin Degree unit
//    return Celsius_temp;
//}
