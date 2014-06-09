
///////////////////////////////////////////////////////////////////////////////
// modified by Hsinmo 20131205
//include and define from calling function
//disable dsg FCCupdate function

#include "coulomb_counter.h"


#include "..\Config_Info\System_Config_Info.h"

#if (_Enable_Coulomb_Counter_FCC_RM_ == 1)

#include "Vars_Bits_Define.h"
//#include "Global_Variable_Define.h"
#include "SOC\Calculate_NTC_ADC_TO_TEMPERATURE.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Coulomb Counter FCC Updated in CHG Voltage
#if (_CELL_SERIES_NUMBER_ == 5)
    #define CHG_Update_Vol_TH   20000   //mV, when voltage > this th, fit update condition
#elif (_CELL_SERIES_NUMBER_ == 7)
    #define CHG_Update_Vol_TH   28000   //mV, when voltage > this th, fit update condition
#elif (_CELL_SERIES_NUMBER_ == 10)
    #define CHG_Update_Vol_TH   40000   //mV, when voltage > this th, fit update condition
#elif (_CELL_SERIES_NUMBER_ == 13)
    #define CHG_Update_Vol_TH   52000   //mV, when voltage > this th, fit update condition
#else
    #error "Please select Cell SERIES Number. (in Coulomb Counter)"
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//  SDI 22FM
#if defined(_CELL_TYPE_SDI_22FM_) && (_CELL_SERIES_NUMBER_ == 7)
    #include "OCV_Table_SDI_22FM_7S.h"
#elif defined(_CELL_TYPE_SDI_22FM_) && (_CELL_SERIES_NUMBER_ == 8)
    #include "OCV_Table_SDI_22FM_8S.h"
#elif defined(_CELL_TYPE_SDI_22FM_) && (_CELL_SERIES_NUMBER_ == 10)
    #include "OCV_Table_SDI_22FM_10S.h"
#elif defined(_CELL_TYPE_SDI_22FM_) && (_CELL_SERIES_NUMBER_ == 13)
    #include "OCV_Table_SDI_22FM_13S.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//  LGC 26 B4
#elif defined(_CELL_TYPE_LGC_26B4_) && (_CELL_SERIES_NUMBER_ == 7)
    #include "OCV_Table_LGC_26B4_7S.h"
#elif defined(_CELL_TYPE_LGC_26B4_) && (_CELL_SERIES_NUMBER_ == 8)
    #include "OCV_Table_LGC_26B4_8S.h"
#elif defined(_CELL_TYPE_LGC_26B4_) && (_CELL_SERIES_NUMBER_ == 10)
    #include "OCV_Table_LGC_26B4_10S.h"
#elif defined(_CELL_TYPE_LGC_26B4_) && (_CELL_SERIES_NUMBER_ == 13)
    #include "OCV_Table_LGC_26B4_13S.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//  SDI 29E
#elif defined(_CELL_TYPE_SDI_29E_) && (_CELL_SERIES_NUMBER_ == 7)
    #include "OCV_Table_SDI_29E_7S.h"
#elif defined(_CELL_TYPE_SDI_29E_) && (_CELL_SERIES_NUMBER_ == 8)
    #include "OCV_Table_SDI_29E_8S.h"
#elif defined(_CELL_TYPE_SDI_29E_) && (_CELL_SERIES_NUMBER_ == 10)
    #include "OCV_Table_SDI_29E_10S.h"
#elif defined(_CELL_TYPE_SDI_29E_) && (_CELL_SERIES_NUMBER_ == 13)
    #include "OCV_Table_SDI_29E_13S.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//  SDI 26F / SDI 26FM
#elif defined(_CELL_TYPE_SDI_26F_) && (_CELL_SERIES_NUMBER_ == 5)
    #include "OCV_Table_SDI_26F_5S.h"
#elif defined(_CELL_TYPE_SDI_26F_) && (_CELL_SERIES_NUMBER_ == 7)
    #include "OCV_Table_SDI_26F_7S.h"
#elif defined(_CELL_TYPE_SDI_26F_) && (_CELL_SERIES_NUMBER_ == 10)
    #include "OCV_Table_SDI_26F_10S.h"
#elif defined(_CELL_TYPE_SDI_26F_) && (_CELL_SERIES_NUMBER_ == 13)
    #include "OCV_Table_SDI_26F_13S.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//  SDI 26H
#elif defined(_CELL_TYPE_SDI_26H_) && (_CELL_SERIES_NUMBER_ == 10)
    #include "OCV_Table_SDI_26H_10S.h"

#else
    #error "Please select Cell Type and SERIES/PARALLEL Number. (in Coulomb Counter)"
#endif


///////////////////////////////////////////////////////////////////////////////

#define sec_counter 9
#define min_counter 599
#define day_counter 1439
#define hour_counter 9

#define false   0
#define true    1
#define bool    unsigned char

///////////////////////////////////////////////////////////////////////////////
// modified by Hsinmo 20130219
//input values by calling function
#define Param_Num   4
unsigned int g_ADC_Values[Param_Num];
float g_Factor_Values[Param_Num];
enum For_ParamArrayIndex  //unsigned char
{
  Param_DSG_Index,   // == 0, because initial values is '0'
  Param_CHG_Index,
  Param_VBAT_Index,
  Param_NTC_Index
};
//////////////////////////////////////////////////////////////////////////////

double RM;
unsigned int current_sec;
unsigned int current_min;
unsigned int static_min;
unsigned int static_day;
unsigned int static_hour;
unsigned int row;
long Over_Dsg_Cap;
long DC;
long DC_calculation;
long CC_calculation;
long FCC_derating;
unsigned int FCC_mAh;
int percentage_calculation;
unsigned int percentage_static;
bool lut_enable;
bool current_stop;
bool Chg_Fcc_update_flag;
unsigned int real_vbat;

/////////////////////////////
//hsinmo function
void (*coulombCounterFccUpdatedCalling_ptr_fuc)(unsigned int updatedFCC, unsigned char re_Changed);
void emptyFccUpdatedCalling_ptr_fuc(unsigned int updatedFCC, unsigned char re_Changed){}

void init_Coulomb_counter(void (*Fcc_Updated_calling_fun)(unsigned int, unsigned char), unsigned int design_capacity_mAH){
    RM = 0;
    current_sec = 0;
    current_min = 0;
    static_min = 0;
    static_day = 0;
    static_hour = 0;
    DC = 0;
    DC_calculation = 0;
    CC_calculation = 0;
    Over_Dsg_Cap=0;
    lut_enable = false;
    Chg_Fcc_update_flag = false;
    /////////////////////////////////////////////
    // calculation FCC (modified by hsinmo)
    //FCC_derating = FCC;
    FCC_derating = design_capacity_mAH;
    FCC_derating = FCC_derating * 60;
    /////////////////////////////////////////////
    percentage_calculation=0;
    percentage_static = 0;
    real_vbat = 0;
    current_stop = false;
    // clear and init array
    for(row=0; row < Param_Num; row++)
    {
        g_ADC_Values[row] = 0;
        g_Factor_Values[row] = 0.0f;
    }
    coulombCounterFccUpdatedCalling_ptr_fuc = Fcc_Updated_calling_fun;

}
void SetADCValuesToCoulombCounterFunc(unsigned int adc_dsg_i,unsigned int adc_chg_i,unsigned int adc_vbat,unsigned int adc_ntc1){
    g_ADC_Values[Param_DSG_Index] = adc_dsg_i;
    g_ADC_Values[Param_CHG_Index] = adc_chg_i;
    g_ADC_Values[Param_VBAT_Index] = adc_vbat;
    g_ADC_Values[Param_NTC_Index] = adc_ntc1;
}
void SetFactorValuesToCoulombCounterFunc(float dsg_factor, float chg_factor, float vbat_factor){
    g_Factor_Values[Param_DSG_Index] = dsg_factor;
    g_Factor_Values[Param_CHG_Index] = chg_factor;
    g_Factor_Values[Param_VBAT_Index] = vbat_factor;
}
void Discharge_capacity(float ocv_percent)
{
  if(lut_enable == false)
  {
    RM=(double)(FCC_derating*ocv_percent/100);
    DC=(unsigned long)(FCC_derating-RM);
    DC_calculation = 0;
    CC_calculation = 0;
    lut_enable = true;
  }
}

unsigned int get_RM()
{
  unsigned long RM2;
  RM2 = (unsigned long)RM;
  RM2 = RM2/60;
  return (unsigned int)RM2;
}

unsigned int get_FCC()
{
  FCC_mAh = FCC_derating/60;
  return FCC_mAh;
}

void FCC_update_EX()
{
  FCC_derating=(long)RM;
  percentage_calculation = 100;
  DC = 0;
  CC_calculation =0;
  DC_calculation =0;
  (*coulombCounterFccUpdatedCalling_ptr_fuc)(get_FCC(), true);
}

unsigned int get_percentage()
{
  int percentage_display = 0;
  if(percentage_calculation >= 100)
  {
    percentage_display = 100;
  }
  else
  {
    percentage_display = (int)(100-(100-percentage_calculation)*1.053);
  }
  if(percentage_display <= 0)
  {
    percentage_display = 0;
  }
  return (unsigned int)percentage_display;
}

void FCC_calculator_DSG()
{
  DC_calculation = (unsigned long)(DC_calculation/(g_Factor_Values[Param_DSG_Index]*600));
  DC = DC+DC_calculation;
  RM = FCC_derating-DC;
  if(RM>=FCC_derating)
  {
     RM = FCC_derating;
     percentage_calculation = 100;
  }
  else if(RM <= 0)
  {
     DC = FCC_derating;
     Over_Dsg_Cap += DC_calculation;
     RM=0;
     percentage_calculation=0;
  }
  else
  {
     percentage_calculation = (unsigned int)(RM*100/FCC_derating);
  }
  if(percentage_calculation < 70 && Chg_Fcc_update_flag == true)
  {
    Chg_Fcc_update_flag = false;
  }
  DC_calculation = 0;
}
void FCC_calculator_CHG()
{
  CC_calculation = (unsigned long)(CC_calculation/(g_Factor_Values[Param_CHG_Index]*600));// mAm
  DC = DC-CC_calculation;
  if(DC < 0)
  {
    RM = FCC_derating+CC_calculation;
    FCC_derating=(long)RM;
    percentage_calculation = 100;
    DC = 0;
  }
  else
  {
    RM = FCC_derating-DC;
    percentage_calculation = (unsigned int)(RM*100/FCC_derating);
  }
  CC_calculation = 0;

  if(RM <= 0)
  {
    RM = 0;
    percentage_calculation =0;
  }

  if((((unsigned int)(g_ADC_Values[Param_CHG_Index]/g_Factor_Values[Param_CHG_Index])) < 200) &&
     (RM <= FCC_derating) &&
     (((unsigned int)(g_ADC_Values[Param_VBAT_Index]/g_Factor_Values[Param_VBAT_Index])) > CHG_Update_Vol_TH) && Chg_Fcc_update_flag == false)
  {
     DC = 0;
     Chg_Fcc_update_flag = true;
     FCC_derating = (long)RM;
     percentage_calculation = 100;
     (*coulombCounterFccUpdatedCalling_ptr_fuc)(get_FCC(), true);
  }
}

void current_coulomb_counter(unsigned current_status)
{
    unsigned int i;
    if(current_status == CurrentInDSG && lut_enable == true)
    {
      DC_calculation += g_ADC_Values[Param_DSG_Index]; //每100ms累加一次dsg_adc_value
      current_stop = true;
      if(current_min >= min_counter)
      {
        FCC_calculator_DSG();
        current_stop = false;
        current_min=0;
        static_day=0;
      }
    }
    else if(current_status == CurrentInCHG && lut_enable == true)
    {
      CC_calculation += g_ADC_Values[Param_CHG_Index]; //每100ms累加一次dsg_adc_value
      current_stop = true;
      if(current_min >= min_counter)
      {
        FCC_calculator_CHG();
        Over_Dsg_Cap=0;
        current_min=0;
        static_day=0;
        current_stop = false;
      }
    }
    else
    {
      if(lut_enable == true && current_stop == true)
      {
        CC_calculation = (unsigned long)(CC_calculation/(g_Factor_Values[Param_CHG_Index]*600));
        DC_calculation = (unsigned long)(DC_calculation/(g_Factor_Values[Param_DSG_Index]*600));
        DC = DC+DC_calculation;
        DC = DC-CC_calculation;
        RM = FCC_derating-DC;

        if(RM > FCC_derating)
        {
          FCC_derating=(long)RM;
          percentage_calculation = 100;
        }
        else if(RM <= 0)
        {
           DC = FCC_derating;
           Over_Dsg_Cap += DC_calculation;
           RM = 0;
           percentage_calculation = 0;
        }
        else
        {
           percentage_calculation = (unsigned int)(RM*100/FCC_derating);
        }
        CC_calculation = 0;
        DC_calculation = 0;
        current_stop = false;
      }
      if(static_min >= min_counter || lut_enable == false)
      {
        static_day++;
        static_hour++;
        static_min=0;
        if(static_day >= day_counter || lut_enable == false)
        {
          lut_enable = false;
          real_vbat = (unsigned int)(g_ADC_Values[Param_VBAT_Index]/g_Factor_Values[Param_VBAT_Index]);
          for(i=0;i<101;i++)
          {
            if((ocv_table[i][1]>real_vbat) && (i != 0))
            {
              percentage_calculation = ocv_table[i-1][0];
              break;
            }
            else if(real_vbat>ocv_table[100][1])
            {
              percentage_calculation = ocv_table[100][0];
              break;
            }
            else
            {
              if(ocv_table[0][1]>real_vbat)
              {
                percentage_calculation = 0;
                break;
              }
            }
          }
          Discharge_capacity(percentage_calculation);
          static_day=0;
        }
        if(static_hour > hour_counter)
        {
          real_vbat = (unsigned int)(g_ADC_Values[Param_VBAT_Index]/g_Factor_Values[Param_VBAT_Index]);
          for(i=0;i<101;i++)
          {
            if((ocv_table[i][1]>real_vbat) && (i != 0))
            {
              percentage_static = ocv_table[i-1][0];
              break;
            }
            else if(real_vbat>ocv_table[100][1])
            {
              percentage_static = ocv_table[100][0];
              break;
            }
            else
            {
              if(ocv_table[0][1]>real_vbat)
              {
                percentage_static = 0;
                break;
              }
            }
            //jasper, 查表得到RM和DC值
            //Discharge_capacity(percentage_static);
          }
          if(percentage_static < 30)
          {
            //updated FCC IN STATIC
            DC += Over_Dsg_Cap;
            FCC_derating = (long)((DC*100)/(100-percentage_static));
            RM = FCC_derating - DC;
            percentage_calculation = (unsigned int)((RM*100)/FCC_derating);
            DC_calculation=0;
            CC_calculation=0;
            Over_Dsg_Cap=0;
            (*coulombCounterFccUpdatedCalling_ptr_fuc)(get_FCC(), false);
          }
          static_hour = 0;
        }
      }
    }
    if(current_status == CurrentInDSG || current_status == CurrentInCHG)
    {
      current_sec++;
      current_min++;
      static_min=0;
      static_day=0;
      static_hour=0;
    }
    else
    {
      current_sec=0;
      current_min=0;
      static_min++;
    }
}
#endif