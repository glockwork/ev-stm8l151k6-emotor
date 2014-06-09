#include "Driver_User_Interface.h"
#include "Global_Variable_Define.h"
#include "Vars_Bits_Define.h"
#include "Protection_Polling_Func.h"
#include "Config_Info\System_Config_Info.h"

#if _USE_3_PARALLEL_CELLS_ == 0
    #if _LEV_48V_ == 0
        #include "New_SOC_OCV_Table_36V_4_PARALLEL_CELLS.h"
    #else
        #include "New_SOC_OCV_Table_48V_4_PARALLEL_CELLS.h"
    #endif
#else
    #if _LEV_48V_ == 0
        #include "New_SOC_OCV_Table_36V_3_PARALLEL_CELLS.h"
    #else
        #include "New_SOC_OCV_Table_48V_3_PARALLEL_CELLS.h"
    #endif
#endif

//#include "SOC_OCV_Table.h"

//unsigned char OV_Capacity;
//unsigned char UV_Capacity;

unsigned int getCapacityByTable(unsigned int real_mVoltage, unsigned char vol_Index);

//float temp_f1;

//void InitSOC(){
//  //////////////////////////////////////////////////////////////////
//  temp_f1 = SOC_1st_CELL_OV_VOLTAGE;
//  //temp_f1 = temp_f1 / NUMBER_OF_BATTERY_SERIES * 10;
//  OV_Capacity = getCapacityByTable(SOC_1st_CELL_OV_VOLTAGE);
//  
//  temp_f1 = SOC_1st_CELL_UV_VOLTAGE;
//  //temp_f1 = temp_f1 / NUMBER_OF_BATTERY_SERIES * 10;
//  UV_Capacity = getCapacityByTable((int)temp_f1);
//}

unsigned char getRealCapacity(unsigned int ADC_Voltage, unsigned int ADC_current,  unsigned int ADC_Temperature, unsigned char CurrentCode){
  float temp_f2;
  unsigned int real_vol;
  unsigned char index;
  unsigned int OV_Capacity;
  unsigned int UV_Capacity;
  unsigned int cap;


  temp_f2 = (float)ADC_Voltage;
  real_vol = (unsigned int)(temp_f2 / VBAT_mV_To_ADC_Factor);
  
  if(  CurrentCode == CurrentInCHG ){
    //CHG
    index = RESIDUAL_CHG_1st_CURRENT_INDEX;
  }else{
    //DSG
      if(ADC_current <= ADC_LOOKUP_1_POINT_OCV_CURRENT_TH){
        index = RESIDUAL_OCV_CURRENT_INDEX;
      }else if(ADC_current <= ADC_LOOKUP_2_POINT_OCV_CURRENT_TH){
        index = RESIDUAL_DSG_1st_CURRENT_INDEX;
      }else if(ADC_current <= ADC_LOOKUP_3_POINT_OCV_CURRENT_TH){
        index = RESIDUAL_DSG_2nd_CURRENT_INDEX;
      }else if(ADC_current <= ADC_LOOKUP_4_POINT_OCV_CURRENT_TH){
        index = RESIDUAL_DSG_3rd_CURRENT_INDEX;
      }else{
        index = RESIDUAL_DSG_4th_CURRENT_INDEX;
      }
  }
  
  OV_Capacity = CELL_OV_VOLTAGE_FOR_SOC * NUMBER_OF_SERIES_CELLS;
  UV_Capacity = CELL_UV_VOLTAGE_FOR_SOC * NUMBER_OF_SERIES_CELLS;
  OV_Capacity = getCapacityByTable( OV_Capacity, index);
  UV_Capacity = getCapacityByTable( UV_Capacity, index);
  cap = getCapacityByTable( real_vol, index);
  
  temp_f2 = OV_Capacity - UV_Capacity;
  temp_f2 = (cap - UV_Capacity) / temp_f2 * 100;
  return (unsigned char)temp_f2;
}

//用查表法，計算SOC
unsigned int getCapacityByTable(unsigned int real_mVoltage, unsigned char vol_Index){
  unsigned int capacity;

  unsigned char i;

  capacity = 0;
  if(real_mVoltage >= RealOCVTable[0][vol_Index]){
    capacity = RealOCVTable[0][RESIDUAL_CAPACITY_INDEX];
  }else if(real_mVoltage <= RealOCVTable[OCV_TABLE_POINTS - 1][vol_Index]){
    capacity = RealOCVTable[OCV_TABLE_POINTS - 1][RESIDUAL_CAPACITY_INDEX];
  }else{
    for(i = 1; i < OCV_TABLE_POINTS; i++){
      if(real_mVoltage > RealOCVTable[i][vol_Index]){
        //取較大值
        capacity = RealOCVTable[i - 1][RESIDUAL_CAPACITY_INDEX];
        //取較小值
        //capacity = RealOCVTable[i][RESIDUAL_CAPACITY_INDEX];
        break;
      }
    }
  }
  return capacity;
}
/*
unsigned int getCapacity1(int mVoltage){
  unsigned int cap;
  float cap1;
  long rm_ADC;
  unsigned char i,j;
  
  cap1 = 0.0f;
  if(mVoltage >= RealOCVTable[0][TERMINAL_VOLTAGE_INDEX]){
    cap1 = RealOCVTable[0][RESIDUAL_CAPACITY_INDEX];
  }else if(mVoltage <= RealOCVTable[OCV_TABLE_POINTS - 1][TERMINAL_VOLTAGE_INDEX]){
    cap1 = RealOCVTable[OCV_TABLE_POINTS - 1][RESIDUAL_CAPACITY_INDEX];
  }else{
    for(i = 0; i < (OCV_TABLE_POINTS - 1); i++){
      if(mVoltage < RealOCVTable[i][TERMINAL_VOLTAGE_INDEX]){
        cap1 = RealOCVTable[i + 1][RESIDUAL_CAPACITY_INDEX];
      }
    }
  }
  cap = cap1/100;
  return cap;
}

*/

