#include "Driver_User_Interface.h"
#include "Global_Variable_Define.h"
#include "Vars_Bits_Define.h"
#include "Protection_Polling_Func.h"
#include "Config_Info\System_Config_Info.h"
#include "SOC_With_Temperature_Calculation.h"

#if (_Capacity_Showing_Use_Voltage_ == 0) && (_Capacity_Showing_Use_Coulomb_Counter_ == 0)
//==========SDI 26H===============================
#if defined(_CELL_TYPE_SDI_26H_) && (_CELL_SERIES_NUMBER_ == 10) && (_CELL_PARALLEL_NUMBER_ == 5)
    #include "inc_SOC_10S_SDI_26H\SOC_TABLE_DSG_10S_3P_4P_5P_WITH_TEMP_26H.h"
    #include "inc_SOC_10S_SDI_26H\SOC_TABLE_STATIC_10S_3P_4P_5P_OCV_26H.h"
    #include "inc_SOC_10S_SDI_26H\SOC_TABLE_CHG_10S_5P_WITH_TEMP_26H.h"
#elif defined(_CELL_TYPE_SDI_26H_) && (_CELL_SERIES_NUMBER_ == 10) && (_CELL_PARALLEL_NUMBER_ == 4)
    #include "inc_SOC_10S_SDI_26H\SOC_TABLE_DSG_10S_3P_4P_WITH_TEMP_26H.h"
    #include "inc_SOC_10S_SDI_26H\SOC_TABLE_STATIC_10S_3P_4P_OCV_26H.h"
    #include "inc_SOC_10S_SDI_26H\SOC_TABLE_CHG_10S_4P_WITH_TEMP_26H.h"
#elif defined(_CELL_TYPE_SDI_26H_) && (_CELL_SERIES_NUMBER_ == 10) && (_CELL_PARALLEL_NUMBER_ == 3)
    #include "inc_SOC_10S_SDI_26H\SOC_TABLE_DSG_10S_3P_4P_WITH_TEMP_26H.h"
    #include "inc_SOC_10S_SDI_26H\SOC_TABLE_STATIC_10S_3P_4P_OCV_26H.h"
    #include "inc_SOC_10S_SDI_26H\SOC_TABLE_CHG_10S_3P_WITH_TEMP_26H.h"


#elif defined(_CELL_TYPE_SDI_26H_) && (_CELL_SERIES_NUMBER_ == 7) && (_CELL_PARALLEL_NUMBER_ == 4)
    #include "inc_SOC_7S_SDI_26H\SOC_TABLE_DSG_7S_3P_4P_WITH_TEMP_26H.h"
    #include "inc_SOC_7S_SDI_26H\SOC_TABLE_STATIC_7S_2P_3P_4P_OCV_26H.h"
    #include "inc_SOC_7S_SDI_26H\SOC_TABLE_CHG_7S_4P_WITH_TEMP_26H.h"
#elif defined(_CELL_TYPE_SDI_26H_) && (_CELL_SERIES_NUMBER_ == 7) && (_CELL_PARALLEL_NUMBER_ == 3)
    #include "inc_SOC_7S_SDI_26H\SOC_TABLE_DSG_7S_3P_4P_WITH_TEMP_26H.h"
    #include "inc_SOC_7S_SDI_26H\SOC_TABLE_STATIC_7S_2P_3P_4P_OCV_26H.h"
    #include "inc_SOC_7S_SDI_26H\SOC_TABLE_CHG_7S_3P_WITH_TEMP_26H.h"
#elif defined(_CELL_TYPE_SDI_26H_) && (_CELL_SERIES_NUMBER_ == 7) && (_CELL_PARALLEL_NUMBER_ == 2)
    #include "inc_SOC_7S_SDI_26H\SOC_TABLE_DSG_7S_2P_WITH_TEMP_26H.h"
    #include "inc_SOC_7S_SDI_26H\SOC_TABLE_STATIC_7S_2P_3P_4P_OCV_26H.h"
    #include "inc_SOC_7S_SDI_26H\SOC_TABLE_CHG_7S_2P_WITH_TEMP_26H.h"


#elif defined(_CELL_TYPE_SDI_26H_) && (_CELL_SERIES_NUMBER_ == 13) && (_CELL_PARALLEL_NUMBER_ == 5)
    #include "inc_SOC_13S_SDI_26H\SOC_TABLE_STATIC_13S_3P_4P_5P_OCV_26H.h"
    #include "inc_SOC_13S_SDI_26H\SOC_TABLE_CHG_13S_5P_WITH_TEMP_26H.h"
    #include "inc_SOC_13S_SDI_26H\SOC_TABLE_DSG_13S_3P_4P_5P_WITH_TEMP_26H.h"
#elif defined(_CELL_TYPE_SDI_26H_) && (_CELL_SERIES_NUMBER_ == 13) && (_CELL_PARALLEL_NUMBER_ == 4)
    #include "inc_SOC_13S_SDI_26H\SOC_TABLE_DSG_13S_3P_4P_WITH_TEMP_26H.h"
    #include "inc_SOC_13S_SDI_26H\SOC_TABLE_STATIC_13S_3P_4P_OCV_26H.h"
    #include "inc_SOC_13S_SDI_26H\SOC_TABLE_CHG_13S_4P_WITH_TEMP_26H.h"
#elif defined(_CELL_TYPE_SDI_26H_) && (_CELL_SERIES_NUMBER_ == 13) && (_CELL_PARALLEL_NUMBER_ == 3)
    #include "inc_SOC_13S_SDI_26H\SOC_TABLE_DSG_13S_3P_4P_WITH_TEMP_26H.h"
    #include "inc_SOC_13S_SDI_26H\SOC_TABLE_STATIC_13S_3P_4P_OCV_26H.h"
    #include "inc_SOC_13S_SDI_26H\SOC_TABLE_CHG_13S_3P_WITH_TEMP_26H.h"

//==========SDI 22H===============================
#elif defined(_CELL_TYPE_SDI_22H_) && (_CELL_SERIES_NUMBER_ == 13) && (_CELL_PARALLEL_NUMBER_ == 4)
    #include "inc_SOC_13S_SDI_22H\SOC_TABLE_DSG_13S_3P_4P_WITH_TEMP_22H.h"
    #include "inc_SOC_13S_SDI_22H\SOC_TABLE_STATIC_13S_3P_4P_OCV_22H.h"
    #include "inc_SOC_13S_SDI_22H\SOC_TABLE_CHG_13S_4P_WITH_TEMP_22H.h"
#elif defined(_CELL_TYPE_SDI_22H_) && (_CELL_SERIES_NUMBER_ == 13) && (_CELL_PARALLEL_NUMBER_ == 3)
    #include "inc_SOC_13S_SDI_22H\SOC_TABLE_DSG_13S_3P_4P_WITH_TEMP_22H.h"
    #include "inc_SOC_13S_SDI_22H\SOC_TABLE_STATIC_13S_3P_4P_OCV_22H.h"
    #include "inc_SOC_13S_SDI_22H\SOC_TABLE_CHG_13S_3P_WITH_TEMP_22H.h"

//==========SDI 26F/ SDI 26FM===============================
#elif defined(_CELL_TYPE_SDI_26F_) && (_CELL_SERIES_NUMBER_ == 5) && (_CELL_PARALLEL_NUMBER_ == 1)
    #include "inc_SOC_5S_SDI_26F\SOC_TABLE_DSG_5S_1P_WITH_TEMP_26F.h"
    #include "inc_SOC_5S_SDI_26F\SOC_TABLE_STATIC_5S_OCV_26F.h"
    #include "inc_SOC_5S_SDI_26F\SOC_TABLE_CHG_5S_1P_WITH_TEMP_26F.h"

#elif defined(_CELL_TYPE_SDI_26F_) && (_CELL_SERIES_NUMBER_ == 10) && (_CELL_PARALLEL_NUMBER_ == 7)
    #include "inc_SOC_10S_SDI_26F\SOC_TABLE_DSG_10S_6P_7P_WITH_TEMP_26F.h"
    #include "inc_SOC_10S_SDI_26F\SOC_TABLE_STATIC_10S_3P_4P_5P_6P_7P_OCV_26F.h"
    #include "inc_SOC_10S_SDI_26F\SOC_TABLE_CHG_10S_7P_WITH_TEMP_26F.h"
#elif defined(_CELL_TYPE_SDI_26F_) && (_CELL_SERIES_NUMBER_ == 10) && (_CELL_PARALLEL_NUMBER_ == 6)
    #include "inc_SOC_10S_SDI_26F\SOC_TABLE_DSG_10S_6P_7P_WITH_TEMP_26F.h"
    #include "inc_SOC_10S_SDI_26F\SOC_TABLE_STATIC_10S_3P_4P_5P_6P_7P_OCV_26F.h"
    #include "inc_SOC_10S_SDI_26F\SOC_TABLE_CHG_10S_6P_WITH_TEMP_26F.h"
#elif defined(_CELL_TYPE_SDI_26F_) && (_CELL_SERIES_NUMBER_ == 10) && (_CELL_PARALLEL_NUMBER_ == 5)
    #include "inc_SOC_10S_SDI_26F\SOC_TABLE_DSG_10S_3P_4P_5P_WITH_TEMP_26F.h"
    #include "inc_SOC_10S_SDI_26F\SOC_TABLE_STATIC_10S_3P_4P_5P_6P_7P_OCV_26F.h"
    #include "inc_SOC_10S_SDI_26F\SOC_TABLE_CHG_10S_5P_WITH_TEMP_26F.h"
#elif defined(_CELL_TYPE_SDI_26F_) && (_CELL_SERIES_NUMBER_ == 10) && (_CELL_PARALLEL_NUMBER_ == 4)
    #include "inc_SOC_10S_SDI_26F\SOC_TABLE_DSG_10S_3P_4P_5P_WITH_TEMP_26F.h"
    #include "inc_SOC_10S_SDI_26F\SOC_TABLE_STATIC_10S_3P_4P_5P_6P_7P_OCV_26F.h"
    #include "inc_SOC_10S_SDI_26F\SOC_TABLE_CHG_10S_4P_WITH_TEMP_26F.h"
#elif defined(_CELL_TYPE_SDI_26F_) && (_CELL_SERIES_NUMBER_ == 10) && (_CELL_PARALLEL_NUMBER_ == 3)
    #include "inc_SOC_10S_SDI_26F\SOC_TABLE_DSG_10S_3P_4P_5P_WITH_TEMP_26F.h"
    #include "inc_SOC_10S_SDI_26F\SOC_TABLE_STATIC_10S_3P_4P_5P_6P_7P_OCV_26F.h"
    #include "inc_SOC_10S_SDI_26F\SOC_TABLE_CHG_10S_3P_WITH_TEMP_26F.h"


#elif defined(_CELL_TYPE_SDI_26F_) && (_CELL_SERIES_NUMBER_ == 13) && (_CELL_PARALLEL_NUMBER_ == 5)
    #include "inc_SOC_13S_SDI_26F\SOC_TABLE_DSG_13S_3P_4P_5P_WITH_TEMP_26F.h"
    #include "inc_SOC_13S_SDI_26F\SOC_TABLE_STATIC_13S_3P_4P_5P_OCV_26F.h"
    #include "inc_SOC_13S_SDI_26F\SOC_TABLE_CHG_13S_5P_WITH_TEMP_26F.h"
#elif defined(_CELL_TYPE_SDI_26F_) && (_CELL_SERIES_NUMBER_ == 13) && (_CELL_PARALLEL_NUMBER_ == 4)
    #include "inc_SOC_13S_SDI_26F\SOC_TABLE_DSG_13S_3P_4P_5P_WITH_TEMP_26F.h"
    #include "inc_SOC_13S_SDI_26F\SOC_TABLE_STATIC_13S_3P_4P_5P_OCV_26F.h"
    #include "inc_SOC_13S_SDI_26F\SOC_TABLE_CHG_13S_4P_WITH_TEMP_26F.h"
#elif defined(_CELL_TYPE_SDI_26F_) && (_CELL_SERIES_NUMBER_ == 13) && (_CELL_PARALLEL_NUMBER_ == 3)
    #include "inc_SOC_13S_SDI_26F\SOC_TABLE_DSG_13S_3P_4P_5P_WITH_TEMP_26F.h"
    #include "inc_SOC_13S_SDI_26F\SOC_TABLE_STATIC_13S_3P_4P_5P_OCV_26F.h"
    #include "inc_SOC_13S_SDI_26F\SOC_TABLE_CHG_13S_3P_WITH_TEMP_26F.h"


#elif defined(_CELL_TYPE_SDI_26F_) && (_CELL_SERIES_NUMBER_ == 7) && (_CELL_PARALLEL_NUMBER_ == 6)
    #include "inc_SOC_7S_SDI_26F\SOC_TABLE_STATIC_7S_OCV_26F.h"
    #include "inc_SOC_7S_SDI_26F\SOC_TABLE_DSG_7S_3P_4P_5P_6P_WITH_TEMP_26F.h"
    #include "inc_SOC_7S_SDI_26F\SOC_TABLE_CHG_7S_6P_WITH_TEMP_26F.h"
#elif defined(_CELL_TYPE_SDI_26F_) && (_CELL_SERIES_NUMBER_ == 7) && (_CELL_PARALLEL_NUMBER_ == 4)
    #include "inc_SOC_7S_SDI_26F\SOC_TABLE_STATIC_7S_OCV_26F.h"
    #include "inc_SOC_7S_SDI_26F\SOC_TABLE_DSG_7S_3P_4P_5P_6P_WITH_TEMP_26F.h"
    #include "inc_SOC_7S_SDI_26F\SOC_TABLE_CHG_7S_4P_WITH_TEMP_26F.h"
#elif defined(_CELL_TYPE_SDI_26F_) && (_CELL_SERIES_NUMBER_ == 7) && (_CELL_PARALLEL_NUMBER_ == 3)
    #include "inc_SOC_7S_SDI_26F\SOC_TABLE_STATIC_7S_OCV_26F.h"
    #include "inc_SOC_7S_SDI_26F\SOC_TABLE_DSG_7S_3P_4P_5P_6P_WITH_TEMP_26F.h"
    #include "inc_SOC_7S_SDI_26F\SOC_TABLE_CHG_7S_3P_WITH_TEMP_26F.h"


#else
    #error "Please select Cell Type and SERIES/PARALLEL Number ."
#endif


//#include "SOC_TABLE_DSG_10S_3P_4P_WITH_TEMP_26H.h"
//#include "SOC_TABLE_STATIC_10S_3P_4P_OCV_26H.h"

//#if defined(_USE_4_PARALLEL_CELLS_)
//    #if defined(_LEV_36V_)
//        #include "SOC_TABLE_CHG_10S_4P_WITH_TEMP_26H.h"
//    #else
//        #error "Please select first the target Of LEV Voltage using."
//    #endif
//#elif defined(_USE_3_PARALLEL_CELLS_)
//    #if defined(_LEV_36V_)
//        #include "SOC_TABLE_CHG_10S_3P_WITH_TEMP_26H.h"
//    #else
//        #error "Please select first the target Of LEV Voltage using."
//    #endif
//#else
//    #error "Please select PARALLEL CELLS Number Of LEV System using."
//#endif



unsigned char getBatteryCapacity(unsigned int ADC_Voltage, unsigned int ADC_current,  unsigned int ADC_Temperature, unsigned char CurrentCode){
  float temp_f2;
  unsigned int real_vol;
  unsigned char chg_temp_index;
  unsigned char dsg_current_index;
  //const unsigned int *dsg_temp_ocv_table_ptr;
  unsigned char dsg_temp_index;
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
    }else if(CurrentCode == CurrentInRelax){
        //Static
        Capa = getStaticCapacityByTable(real_vol);
    }else{
//        //DSG
//#if defined(_USE_4_PARALLEL_CELLS_)
//        //4p current th
//        if(ADC_current <= ADC_10S_4P_LOOKUP_1_POINT_OCV_CURRENT_TH){
//            dsg_current_index = RESIDUAL_DSG_1st_CURRENT_INDEX;
//        }else if(ADC_current <= ADC_10S_4P_LOOKUP_2_POINT_OCV_CURRENT_TH){
//            dsg_current_index = RESIDUAL_DSG_2nd_CURRENT_INDEX;
//        }else if(ADC_current <= ADC_10S_4P_LOOKUP_3_POINT_OCV_CURRENT_TH){
//            dsg_current_index = RESIDUAL_DSG_3rd_CURRENT_INDEX;
//        }else if(ADC_current <= ADC_10S_4P_LOOKUP_4_POINT_OCV_CURRENT_TH){
//            dsg_current_index = RESIDUAL_DSG_4th_CURRENT_INDEX;
//        }else if(ADC_current <= ADC_10S_4P_LOOKUP_5_POINT_OCV_CURRENT_TH){
//            dsg_current_index = RESIDUAL_DSG_5th_CURRENT_INDEX;
//        }else if(ADC_current <= ADC_10S_4P_LOOKUP_6_POINT_OCV_CURRENT_TH){
//            dsg_current_index = RESIDUAL_DSG_6th_CURRENT_INDEX;
//        }else{
//            dsg_current_index = RESIDUAL_DSG_7th_CURRENT_INDEX;
//        }
//#elif  defined(_USE_3_PARALLEL_CELLS_)
//        //3p current th
//        if(ADC_current <= ADC_10S_3P_LOOKUP_1_POINT_OCV_CURRENT_TH){
//            dsg_current_index = RESIDUAL_DSG_1st_CURRENT_INDEX;
//        }else if(ADC_current <= ADC_10S_3P_LOOKUP_2_POINT_OCV_CURRENT_TH){
//            dsg_current_index = RESIDUAL_DSG_2nd_CURRENT_INDEX;
//        }else if(ADC_current <= ADC_10S_3P_LOOKUP_3_POINT_OCV_CURRENT_TH){
//            dsg_current_index = RESIDUAL_DSG_3rd_CURRENT_INDEX;
//        }else if(ADC_current <= ADC_10S_3P_LOOKUP_4_POINT_OCV_CURRENT_TH){
//            dsg_current_index = RESIDUAL_DSG_4th_CURRENT_INDEX;
//        }else if(ADC_current <= ADC_10S_3P_LOOKUP_5_POINT_OCV_CURRENT_TH){
//            dsg_current_index = RESIDUAL_DSG_5th_CURRENT_INDEX;
//        }else if(ADC_current <= ADC_10S_3P_LOOKUP_6_POINT_OCV_CURRENT_TH){
//            dsg_current_index = RESIDUAL_DSG_6th_CURRENT_INDEX;
//        }else{
//            dsg_current_index = RESIDUAL_DSG_7th_CURRENT_INDEX;
//        }
//#else
//    #error "Please select PARALLEL CELLS Number Of LEV System using."
//#endif
        //DSG
        //check current th
        if(ADC_current <= _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH1_){
            dsg_current_index = RESIDUAL_DSG_1st_CURRENT_INDEX;
        }else if(ADC_current <= _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH2_){
            dsg_current_index = RESIDUAL_DSG_2nd_CURRENT_INDEX;
        }else if(ADC_current <= _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH3_){
            dsg_current_index = RESIDUAL_DSG_3rd_CURRENT_INDEX;
        }else if(ADC_current <= _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH4_){
            dsg_current_index = RESIDUAL_DSG_4th_CURRENT_INDEX;
        }else if(ADC_current <= _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH5_){
            dsg_current_index = RESIDUAL_DSG_5th_CURRENT_INDEX;
        }else if(ADC_current <= _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH6_){
            dsg_current_index = RESIDUAL_DSG_6th_CURRENT_INDEX;
        }else{
            dsg_current_index = RESIDUAL_DSG_7th_CURRENT_INDEX;
        }

        if(ADC_Temperature >= _ADC_LOOKUP_DSG_TEMP_1_TH_){
            dsg_temp_index = RESIDUAL_DSG_1st_TEMPERATURE_INDEX;
        }else if(ADC_Temperature >= _ADC_LOOKUP_DSG_TEMP_2_TH_){
            dsg_temp_index = RESIDUAL_DSG_2nd_TEMPERATURE_INDEX;
        }else if(ADC_Temperature >= _ADC_LOOKUP_DSG_TEMP_3_TH_){
            dsg_temp_index = RESIDUAL_DSG_3rd_TEMPERATURE_INDEX;
        }else{
            dsg_temp_index = RESIDUAL_DSG_4th_TEMPERATURE_INDEX;
        }
//        if(ADC_Temperature >= _ADC_LOOKUP_DSG_TEMP_1_TH_){
//            dsg_temp_ocv_table_ptr = &(DSG_5d_OCVTable[41][8]);
//        }else if(ADC_Temperature >= _ADC_LOOKUP_DSG_TEMP_2_TH_){
//            dsg_temp_ocv_table_ptr = DSG_15d_OCVTable;
//        }else if(ADC_Temperature >= _ADC_LOOKUP_DSG_TEMP_3_TH_){
//            dsg_temp_ocv_table_ptr = DSG_25d_OCVTable;
//        }else{
//            dsg_temp_ocv_table_ptr = DSG_40d_OCVTable;
//        }
//        Capa = getDSGCapacityByTable(dsg_temp_ocv_table_ptr, real_vol, dsg_current_index);
        Capa = getDSGCapacityByTable( real_vol, dsg_current_index, dsg_temp_index);

    }//if(  CurrentCode == CurrentInCHG ){ - else - esle -

//  OV_Capacity = CELL_OV_VOLTAGE_FOR_SOC * NUMBER_OF_SERIES_CELLS;
//  UV_Capacity = CELL_UV_VOLTAGE_FOR_SOC * NUMBER_OF_SERIES_CELLS;
//  OV_Capacity = getCapacityByTable( OV_Capacity, index);
//  UV_Capacity = getCapacityByTable( UV_Capacity, index);
//  cap = getCapacityByTable( real_vol, index);
//
//  temp_f2 = OV_Capacity - UV_Capacity;
//  temp_f2 = (cap - UV_Capacity) / temp_f2 * 100;
//  return (unsigned char)temp_f2;
    temp_f2 = Capa;
    temp_f2 = temp_f2 / 100;
    return (unsigned char)temp_f2;
}
//用查表法，計算DSG SOC
unsigned int getDSGCapacityByTable(unsigned int real_mVoltage, unsigned char current_Index, unsigned char temp_Index){
  unsigned int capacity;

  unsigned char i;

  capacity = 0;
  if(real_mVoltage >= DSG_TEMPERATURE_OCVTable[temp_Index][0][current_Index]){
      capacity = DSG_TEMPERATURE_OCVTable[temp_Index][0][RESIDUAL_DSG_CAPACITY_INDEX];
  }else if(real_mVoltage <= DSG_TEMPERATURE_OCVTable[temp_Index][DSG_OCV_TABLE_POINTS - 1][current_Index]){
      capacity = DSG_TEMPERATURE_OCVTable[temp_Index][DSG_OCV_TABLE_POINTS - 1][RESIDUAL_DSG_CAPACITY_INDEX];
  }else{
      for(i = 1; i < DSG_OCV_TABLE_POINTS; i++){
          if(real_mVoltage >= DSG_TEMPERATURE_OCVTable[temp_Index][i][current_Index]){ //取較小值
              capacity = DSG_TEMPERATURE_OCVTable[temp_Index][i][RESIDUAL_DSG_CAPACITY_INDEX];
              break;
          }
      }//for
  }
  return capacity;
}
////用查表法，計算DSG SOC
//unsigned int getDSGCapacityByTable(unsigned int *look_up_Table, unsigned int real_mVoltage, unsigned char current_Index){
//  unsigned int capacity;
//
//  unsigned char i;
//
//  capacity = 0;
//  if(real_mVoltage >= look_up_Table[0][current_Index]){
//      capacity = look_up_Table[0][RESIDUAL_DSG_CAPACITY_INDEX];
//  }else if(real_mVoltage <= look_up_Table[DSG_OCV_TABLE_POINTS - 1][current_Index]){
//      capacity = look_up_Table[DSG_OCV_TABLE_POINTS - 1][RESIDUAL_DSG_CAPACITY_INDEX];
//  }else{
//      for(i = 1; i < DSG_OCV_TABLE_POINTS; i++){
//          if(real_mVoltage >= look_up_Table[i][current_Index]){ //取較小值
//              capacity = look_up_Table[i][RESIDUAL_DSG_CAPACITY_INDEX];
//          }
//      }//for
//  }
//  return capacity;
//}
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
  unsigned int capacity;

  unsigned char i;

  capacity = 0;
  if(real_mVoltage >= Static_OCVTable[0][RESIDUAL_Static_CURRENT_INDEX]){
      capacity = Static_OCVTable[0][RESIDUAL_Static_CAPACITY_INDEX];
  }else if(real_mVoltage <= Static_OCVTable[Static_OCV_TABLE_POINTS - 1][RESIDUAL_Static_CURRENT_INDEX]){
      capacity = Static_OCVTable[Static_OCV_TABLE_POINTS - 1][RESIDUAL_Static_CAPACITY_INDEX];
  }else{
      for(i = 1; i < Static_OCV_TABLE_POINTS; i++){
          if(real_mVoltage >= Static_OCVTable[i][RESIDUAL_Static_CURRENT_INDEX]){ //取較小值
              capacity = Static_OCVTable[i][RESIDUAL_Static_CAPACITY_INDEX];
              break;
          }
      }//for
  }
  return capacity;
}

#endif
