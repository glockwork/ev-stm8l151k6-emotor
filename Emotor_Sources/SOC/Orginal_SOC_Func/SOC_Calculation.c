


#include "NEW_SOC_NTC_TABLE.h"
#include "..\Config_Info\System_Config_Info.h"

//unsigned char OV_Capacity;
//unsigned char UV_Capacity;

//float getCapacityByNewNTC_DSG_Table(int real_mVoltage, unsigned char Current_Index, unsigned char Temp_Index);

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
unsigned char getRealCapacityByBatteryVoltage(unsigned int ADC_Voltage, unsigned int ADC_current,  unsigned int ADC_NTC, unsigned char isDSG){
  float temp_f2;
  float cap;
  float OV_Capacity;
  float UV_Capacity;
  unsigned char Temp_Index;
  unsigned char Current_Index;
  unsigned char Use_Old_Table_Flag;
  unsigned int real_vol;
  
  temp_f2 = ADC_Voltage;
  real_vol = (unsigned int)(temp_f2 / VBAT_mV_To_ADC_Factor);

  Use_Old_Table_Flag = 0;
  
  if(ADC_NTC > _ADC_LOOKUP_DSG_TEMP_1_TH_){
      Temp_Index = RESIDUAL_DSG_1st_TEMPERATURE_INDEX;
  }else if (ADC_NTC > _ADC_LOOKUP_DSG_TEMP_2_TH_){
      Temp_Index = RESIDUAL_DSG_2nd_TEMPERATURE_INDEX;
  }else if (ADC_NTC > _ADC_LOOKUP_DSG_TEMP_3_TH_){
      Temp_Index = RESIDUAL_DSG_3rd_TEMPERATURE_INDEX;
  }else{
      Temp_Index = RESIDUAL_DSG_4th_TEMPERATURE_INDEX;
  }

  if(  isDSG ){
    //DSG
      if(ADC_current <= ADC_LOOKUP_1_POINT_OCV_CURRENT_TH){
          Use_Old_Table_Flag = 1;
      }else if(ADC_current <= ADC_LOOKUP_2_POINT_OCV_CURRENT_TH){
        Current_Index = RESIDUAL_DSG_1st_CURRENT_INDEX;
      }else if(ADC_current <= ADC_LOOKUP_3_POINT_OCV_CURRENT_TH){
        Current_Index = RESIDUAL_DSG_2nd_CURRENT_INDEX;
      }else if(ADC_current <= ADC_LOOKUP_4_POINT_OCV_CURRENT_TH){
        Current_Index = RESIDUAL_DSG_3rd_CURRENT_INDEX;
      }else if(ADC_current <= ADC_LOOKUP_5_POINT_OCV_CURRENT_TH){
        Current_Index = RESIDUAL_DSG_4th_CURRENT_INDEX;
      }else if(ADC_current <= ADC_LOOKUP_6_POINT_OCV_CURRENT_TH){
        Current_Index = RESIDUAL_DSG_5th_CURRENT_INDEX;
      }else if(ADC_current <= ADC_LOOKUP_7_POINT_OCV_CURRENT_TH){
        Current_Index = RESIDUAL_DSG_6th_CURRENT_INDEX;
      }else{
        Current_Index = RESIDUAL_DSG_7th_CURRENT_INDEX;
      }
  }else{
    //CHG
    Use_Old_Table_Flag = 1;
  }
  
  if(Use_Old_Table_Flag){
    return getRealCapacityByCell(ADC_Voltage, ADC_current, isDSG);   
  }
  
  OV_Capacity = getCapacityByNewNTC_DSG_Table(CELL_OV_VOLTAGE_FOR_SOC, Current_Index, Temp_Index);
  UV_Capacity = getCapacityByNewNTC_DSG_Table(CELL_UV_VOLTAGE_FOR_SOC, Current_Index, Temp_Index);
  cap = getCapacityByNewNTC_DSG_Table(real_vol, Current_Index, Temp_Index);
  
  temp_f2 = OV_Capacity - UV_Capacity;
  temp_f2 = (cap - UV_Capacity) / temp_f2 * 100;
  //return (unsigned char)temp_f2;
  return (unsigned char)cap;
}

//用查表法，計算SOC
float getCapacityByNewNTC_DSG_Table(unsigned int real_mVoltage, unsigned char Current_Index, unsigned char Temp_Index){

  float cap1;
  unsigned char i;
  cap1 = 0.0f;
  
    if(real_mVoltage >= SOCTable[Temp_Index][0][Current_Index]){
        return 100.0f;
    }else if(real_mVoltage <= SOCTable[Temp_Index][SOC_TABLE_POINTS - 1][Current_Index]){
        return 0.0f;
    }else{
        for(i = 1; i < SOC_TABLE_POINTS; i++){
            if(real_mVoltage == SOCTable[Temp_Index][i][Current_Index]){
                cap1 = (float)SOCTable[Temp_Index][i][RESIDUAL_OCV_CAP_INDEX];
                break;
            }else if(real_mVoltage > SOCTable[Temp_Index][i][Current_Index]){
                //取較大值
                cap1 = (float)SOCTable[Temp_Index][i - 1][RESIDUAL_OCV_CAP_INDEX];
                break;
            }
        }
        cap1 = (cap1/100.0f);
        return cap1;
    }
}

/////////////////////////////////////////////////////////////////////////
// old calculation capacity
unsigned char getRealCapacityByCell(int ADC_Voltage, int ADC_current,  unsigned char isDSG){
  float temp_f2;
  float cap;
  float OV_Capacity;
  float UV_Capacity;
  unsigned char index;
  int real_vol;

  temp_f2 = ADC_Voltage;
  temp_f2 = temp_f2 / VBAT_mV_To_ADC_Factor;
  real_vol = (unsigned int)(temp_f2 / NUMBER_OF_SERIES_CELLS);

  if(  isDSG ){
    //DSG
        index = RESIDUAL_OCV_CAPACITY_INDEX;
  }else{
    //CHG
      if(ADC_current <= ADC_LOOKUP_1st_LEVEL_OCV_CHG_CURRENT_VALUES){
        index = RESIDUAL_OCV_CAPACITY_INDEX;
      }else if(ADC_current <= ADC_LOOKUP_2nd_LEVEL_OCV_CHG_CURRENT_VALUES){
        index = RESIDUAL_CHG_1st_CAPACITY_INDEX;
      }else{
        index = RESIDUAL_CHG_2nd_CAPACITY_INDEX;
      }
  }
  
  OV_Capacity = getCapacityByTable(CELL_OV_VOLTAGE_FOR_SOC, index);
  UV_Capacity = getCapacityByTable(CELL_UV_VOLTAGE_FOR_SOC, index);
  cap = getCapacityByTable( real_vol, index);
  
  temp_f2 = OV_Capacity - UV_Capacity;
  temp_f2 = (cap - UV_Capacity) / temp_f2 * 100;
  return (unsigned char)temp_f2;
}


//用查表法，計算SOC
float getCapacityByTable(int real_mVoltage, unsigned char cap_Index){

  float cap1;
  unsigned char i;
  cap1 = 0.0f;
  if(real_mVoltage >= RealOCVTable[0][TERMINAL_VOLTAGE_INDEX]){
    cap1 = RealOCVTable[0][cap_Index];
  }else if(real_mVoltage <= RealOCVTable[OCV_TABLE_POINTS - 1][TERMINAL_VOLTAGE_INDEX]){
    cap1 = RealOCVTable[OCV_TABLE_POINTS - 1][cap_Index];
  }else{
    for(i = 1; i < OCV_TABLE_POINTS; i++){
      if(real_mVoltage > RealOCVTable[i][TERMINAL_VOLTAGE_INDEX]){
        //取較大值
        //cap1 = RealOCVTable[i - 1][cap_Index];
        //取較小值
        cap1 = RealOCVTable[i][cap_Index];
        break;
      }
    }
  }
  cap1 = (cap1/100);
  return cap1;
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



