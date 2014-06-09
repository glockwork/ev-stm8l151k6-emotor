
/**
  ******************************************************************************
  * @file    User_Define.h
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    20-May-2014
  * @brief   User Define Header
  ******************************************************************************
  * @attention
  *
  * 每一個新增專案，需修改的參數為 :
  * 1) check VERSION, MINOR_VERSION, EEPROM_VERSION版本號.
  * 2) NUMBER_OF_PARALLEL_CELLS, NUMBER_OF_SERIES_CELLS
  * 3) MANUFACTURE_DATE
  * 4) CELL_TYPE and CELL_TYPE_LENGTH
  * 5) MANUFACTURE_NAME and MANUFACTURE_NAME_LENGTH
  * 6) PROJECT_NAME and PROJECT_NAME_MAX_LENGTH
  * 7) Check All Protection Values and Factors
  *
  * <h2><center>&copy; COPYRIGHT 2012 Dynapack</center></h2>
  ******************************************************************************
  */

////////////////////////////////////////////////////////////////////////////////
// This File could not be used directly,
// have to be converted to new header file, then could be used.
////////////////////////////////////////////////////////////////////////////////
// STM8L151K6 , EEPROM Size = 1K bytes
//=====================================================================================================================
//=====================================================================================================================
// below vars List have to be use in Decimal
// put "_ee_" at head means the vars will be collected for burrning-in EEPROM by external appilication
// "str_len_",  Data type: unsigned char, 1 byte, show next string var length.
// "str_",      Data type: (unsigned char *), str_len_XX bytes,  show char string.
// "uchar_",    Data type: unsigned char, 1 byte.
// "char_",     Data type: signed char, 1 byte.
// "uint_",     Data type: unsigned int, 2 byte.
// "int_",      Data type: signed int, 2 byte.
// "ulong_",    Data type: unsigned long, 4 byte.
// "long_",     Data type: signed long, 4 byte.
// "float_",    Data type: float, 4 byte.
// "double_",   Data type: double, 4 byte.
//=====================================================================================================================
#define _ee_address_CONFIG_SEGMENT          0x1000   //EEPROM Start Address, must use Hexadecimal

//=====================================================================================================================
// RESERVED 96 bytes (0x60 bytes) for  calibration, recording data and Reserved Data
// For calibration data offset address from 0x0000 to 0x001f (offset: 0 ~ 31 ): 32 bytes
// For recording data offset address from 0x0020 to 0x003f (offset: 32 ~ 63 )Recording data to EEPROM: 32 bytes
// For recording data offset address from 0x0040 to 0x005f (offset: 64 ~ 95 )Recording data to EEPROM: 32 bytes
// For Reserved data offset address from 0x0140 to 0x015f (offset: 320 ~ 352 ): 32 bytes
////////////////////////////////////////////////////////////////////////////////
// Calibration, ==> The address could not be change.
// (from 0x0000 to 0x001f (offset: 0 ~ 31 )): 32 bytes
////////////////////////////////////////////////////////////////////////////////
#define _ee_float_CHG_mA_To_ADC_Factor          0.446836364f        // 4 bytes;
#define _ee_float_DSG_mA_To_ADC_Factor          0.248242424f        // 4 bytes;
#define _ee_float_VBAT_mV_To_ADC_Factor         0.065821855f        // 4 bytes;
#define _ee_float_Thermistor_mV_To_ADC_Factor   1.241212f         // 4 bytes; = 1/ADC_Step
#define _ee_char_DSG_OP_ADC_OFFSET             0      //1byte ; 實際值-理論值 (signed char) //used
#define _ee_char_CHG_OP_ADC_OFFSET             0      //1byte ; 實際值-理論值 (signed char) //used
#define _ee_char_VBAT_ADC_OFFSET               0      //1byte ; 實際值-理論值 (signed char) //used
#define _ee_char_NTC1_ADC_OFFSET               0      //1byte ; 實際值-理論值 Thermistor (signed char)  //used
#define _ee_char_NTC2_ADC_OFFSET               0      //1byte ; 實際值-理論值 Thermistor (signed char)  //used
#define _ee_char_SOC_ADC_OFFSET                0      //1byte ; 實際值-理論值 (signed char)
//------------------------------------------------------------------------------------------
#define _ee_uint_R_Sense_10u_ohm                 200    //2 bytes; 200 * 10u ohm = 2.00 m-ohm

//------------------------------------------------------------------------------------------
// MCU_Major_Type_Code ==> MCU Supplier: 0=> ST, 1=>TI, 2=> Renesas
// Major_Type_Code and Minor_Type_Code List as below
// Type_Code : 0.0 ==> STM8L151K6C6
// Type_Code : 0.1 ==> STM8S005K6C6
#define _ee_uchar_MCU_Major_Type_Code            0      //1 byte; MCU Supplier: 0=> ST, 1=> TI, 2=> Renesas
#define _ee_uchar_MCU_Minor_Type_Code            0
#define _ee_ulong_RESERVED_CAL_FOR_OFFSET2       0
#define _ee_uint_RESERVED_CAL_FOR_OFFSET3        0
////////////////////////////////////////////////////////////////////////////////
// Recording data to EEPROM, ==> The address could not be change.
// (from 0x0020 to 0x003f (offset: 32 ~ 63 )): 32 bytes
////////////////////////////////////////////////////////////////////////////////
// they have to set the start offset at 4的倍數 below vars.
// and the order could not be changed below vars.
////////////////////////////////////////////////////////////////////////////////
#define _ee_uint_MAX_DSG_C_ADC_RECORD_EEPROM        0
#define _ee_uint_MAX_CHG_C_ADC_RECORD_EEPROM        0
#define _ee_uint_MAX_VBAT_ADC_RECORD_EEPROM         0
#define _ee_uint_MIN_VBAT_ADC_RECORD_EEPROM         65535
#define _ee_uint_MAX_VBAT_SocLo_ADC_RECORD_EEPROM   0
#define _ee_uint_MAX_VBAT_SocHi_ADC_RECORD_EEPROM   0

#define _ee_uint_DSG_MAX_TH1_ADC_RECORD_EEPROM          0
#define _ee_uint_DSG_MIN_TH1_ADC_RECORD_EEPROM          65535
#define _ee_uint_DSG_MAX_TH2_ADC_RECORD_EEPROM          0
#define _ee_uint_DSG_MIN_TH2_ADC_RECORD_EEPROM          65535
// record count
#define _ee_uint_RECORD_DATA_COUNT_EEPROM               0
#define _ee_uint_CHG_Cycle_Count_RECORD_EEPROM          0
#define _ee_ulong_CHG_ADC_AccumulatingQ_RECORD_EEPROM   0   //max = 4,294,967,295 = 0xffff ffff
//------------------------------------------------------------------------------------------
#define _ee_ulong_DSG_ADC_AccumulatingQ_RECORD_EEPROM   0   //max = 4,294,967,295 = 0xffff ffff

////////////////////////////////////////////////////////////////////////////////
// Reserved data ==> The address could not be change.
// (from 0x0040 to 0x005f (offset: 64 ~ 95 )): 32 bytes
////////////////////////////////////////////////////////////////////////////////
#define _ee_uint_DSG_Cycle_Count_RECORD_EEPROM          0
#define _ee_uint_RESERVED_Recording_FOR_OFFSET1         0 //Reserved

#define _ee_uint_CHG_MAX_TH1_ADC_RECORD_EEPROM          0
#define _ee_uint_CHG_MIN_TH1_ADC_RECORD_EEPROM          65535
#define _ee_uint_CHG_MAX_TH2_ADC_RECORD_EEPROM          0
#define _ee_uint_CHG_MIN_TH2_ADC_RECORD_EEPROM          65535

#define _ee_uint_G_OVP_TIMES_RECORD_EEPROM              0
#define _ee_uint_G_UVP_TIMES_RECORD_EEPROM              0
#define _ee_uint_G_COCP_TIMES_RECORD_EEPROM             0
#define _ee_uint_G_DOCP_TIMES_RECORD_EEPROM             0

#define _ee_uint_G_TH1_CHG_UTP_TIMES_RECORD_EEPROM      0
#define _ee_uint_G_TH2_CHG_UTP_TIMES_RECORD_EEPROM      0

#define _ee_uint_G_CHG_TH1_OTP_TIMES_RECORD_EEPROM      0
#define _ee_uint_G_CHG_TH2_OTP_TIMES_RECORD_EEPROM      0

#define _ee_uint_RECORD_2nd_DATA_COUNT_EEPROM           0 //Reserved
#define _ee_uint_RESERVED_Recording_FOR_OFFSET3         0 //Reserved

//=====================================================================================================================

////////////////////////////////////////////////////////////////////////////////
// Default init Data start offset address : 0x0060  (offset = 96)
//////////////////////////////////////////////////////////////////
#define _ee_uchar_SystemSetting_Info_Byte1          0       //write by F/W
#define _ee_uchar_SystemSetting_Info_Byte2          0       //write by F/W
#define _ee_uchar_System_Control_Bit_EEPROM         12      // 1 byte
#define _ee_uchar_SystemSetting_Info_Byte3          0       //write by F/W


////////////////////////////////////////////////////////////////////////////////
#define _ee_uchar_VERSION                       255//(don't change), has to be define at FW_Version_Define, 1 bytes//for main function addition and EEPROM Format changing
#define _ee_uchar_MINOR_VERSION                 255//(don't change), has to be define at FW_Version_Define, 1 bytes//only for minor functions changing

#define _ee_uchar_EEPROM_VERSION                26      // 1 bytes //only for EEPROM values changing

#define _ee_uchar_RESERVED_VERSION              255//(don't change),has to be define at FW_Version_Define, 1 bytes//0x00: Protuction, 0x01: Samples
////////////////////////////////////////////////////////////////////////////////

#define _ee_uchar_NUMBER_OF_PARALLEL_CELLS      4       // 1 bytes
#define _ee_uchar_NUMBER_OF_SERIES_CELLS        10      // 1 bytes

//#define MANUFACTURE_DATE_YEAR   2014
//#define MANUFACTURE_DATE_MONTH  6
//#define MANUFACTURE_DATE_DAY    4
#define _ee_uint_MANUFACTURE_DATE               17604   //(MANUFACTURE_DATE_YEAR - 1980) * 512 + MANUFACTURE_DATE_MONTH * 32 + MANUFACTURE_DATE_DAY  // 2 bytes
#define _ee_uint_SERIAL_NUMBER                  65530      // 2 bytes

//=====================================================================================================================
//First set String Length
//then second set String
#define _ee_str_len_CELL_TYPE_LENGTH            8
#define _ee_str_CELL_TYPE                       "SDI 26FM"
#define _ee_str_len_MANUFACTURE_NAME_LENGTH     8
#define _ee_str_MANUFACTURE_NAME                "Dynapack"
//#define _ee_str_len_PRODUCT_NAME_LENGTH         8
//#define _ee_str_PRODUCT_NAME                    "LEV36"

//#define _ee_uchar_RESERVED_FOR_OFFSET1            0


//=====================================================================================================================
// CHG / DSG Current Detector (op amp)
////////////////////////////////////////////////////////////////////////////////
//ADC_resolution  4096    // 12 bit ADC
//ADC_Ref         3300    // mV
//ADC_Step        0.805664f  ==>(float)ADC_Ref /  ADC_resolution ==> (mV)
////////////////////////////////////////////////////////////////////////////////
//Rsense                  2.0f    //mR
////////////////////////////////////////////////////////////////////////////////
//mA to ADC factor
//Factor = Rsense(R) * op_gain / ADC step(mV) => Multiplicative inverse Factor
////////////////////////////////////////////////////////////////
// CHG_OP_Gain             180.0f
// _CHG_mA_to_ADC_factor_    0.065821855f   ==> (Rsense_mR * CHG_OP_Gain / ADC_Step / 1000)==>小數點6位
// CHG_OP_ADC_OFFSET         (signed char)0    //實際值-理論值
////////////////////////////////////////////////////////////////
// DSG_OP_Gain   100.0f
// _DSG_mA_to_ADC_factor_     0.248242424f  ==> (Rsense_mR * DSG_OP_Gain/ADC_Step/1000)==>小數點6位
// DSG_OP_ADC_OFFSET         (signed char)0    //實際值-理論值
// 理論值 = 實際值 - Offset
////////////////////////////////////////////////////////////////////////////////
//(無條件進位==> 會比實際值還大一點)
//(使用四捨五入)
#define _ee_uint_ADC_CURRENT_DETECT_FOR_DSG_STATUS       30       //120mA; unit: mA; 2bytes; if current > the define, in discharging status
#define _ee_uint_ADC_CURRENT_DETECT_FOR_CHG_STATUS       54       //120mA; unit: mA; 2bytes; if current > the define, in charging status

#define _ee_uint_ADC_DOC_PROTECTION                      10178    // 50A; unit: 1mA; (OVER) discharging current protection is positive
#define _ee_uint_ADC_COC_PROTECTION                      2011     // 4.5A; unit: 1mA; charging current protection
#define _ee_uint_ADC_DSG_HIGH_CURRENT_DETECT             1986     // 8000mA; 2bytes; for switch High/Low OT Protection
#define _ee_uint_ADC_CHG_CHARGER_TAPE_CURRENT            670      // 1500mA; 2bytes;
//////////////////////////////////////////////////////////////////////////////////
//for one cycle count
// 4p * 2600mah * 0.8 = 8320 mah * _CHG_mA_to_ADC_factor_ = 3718 ADC,
// Accumulating interval time = 500 ms. ==> 1 hour = 3600 second. = 3,600,000 ms = 7200 (per 500ms)
// 3718 ADC * 7200 = 26769600 ADC
#define _ee_ulong_ADC_AccQ_FOR_CHG_TH           26769600       //one Cycle Count Threshold; //long int => max = 4,294,967,295 = 0xffff ffff ffff ffff
#define _ee_uint_Cycle_Count_FOR_CHG_1st_TH     150          // 150 times; unit: times; 2byte; Cycle Count times for charger to set CHG voltage
#define _ee_uint_Cycle_Count_FOR_CHG_2nd_TH     500          // 500 times; unit: times; 2byte; Cycle Count times for charger to set CHG voltage


//=====================================================================================================================
// Battery Voltage circuit and setting
////////////////////////////////////////////////////////////////
//    Battery |------Resistor1----+---Resistor2-----|GND
//    Vltage  |       1000KR      |   56KR
//                                |
//                                |
//                       voltage output
//                       to MCU ADC in
////////////////////////////////////////////////////////////////
//ADC_Step        0.805664f  ==>(float)ADC_Ref /  ADC_resolution ==> (mV)
//VBAT_mV_To_ADC_Factor    (float)1/(ADC_Step/(VBAT_Resistor2/(VBAT_Resistor1+VBAT_Resistor2))==>小數點6位
// _VBAT_mV_To_ADC_Factor_      0.065821855f
//VBAT_ADC_OFFSET          (signed char)(-5)   //實際值-理論值
// 理論值 = 實際值 - Offset
////////////////////////////////////////////////////////////////
#define _ee_uint_ADC_BATTERY_OV_PROTECTION             2791 // 42.4V(cell:4.24); unit: 1mV; 2bytes; 2nd level BATTERY OV PROTECTION
#define _ee_uint_ADC_BATTERY_OV_RELEASE                2732 // 41.5V(cell:4.15); unit: 1mV; 2bytes; 2nd level BATTERY OV RELEASE
#define _ee_uint_ADC_BATTERY_UV_PROTECTION             1843 // 28V(cell:2.8); unit: 1mV; 2bytes; 2nd level BATTERY UV PROTECTION
#define _ee_uint_ADC_BATTERY_UV_RELEASE                2205 // 33.5V;For Delay reach Vol while UVP ; (org) 32V(cell:3.2); unit: 1mV; 2bytes; 2nd level BATTERY UV RELEASE


//=====================================================================================================================
// NTC Thermistor setting by voltage  (Mitsubishi NTC R1=10K)
// NTC : MITSUBISHI H Type, BH30-3H103FB, B values : 25/50 ＝ 3370 K±1%
////////////////////////////////////////////////////////////////
//    VDD (3.3V) |------Resistor1--+---NTC-----|GND     (Resistor1 = 10kR)
//                                 |
//                                 |
//                       thermal voltage output
////////////////////////////////////////////////////////////////
//Thermistor_mV_To_ADC_Factor     1.241212f   // = 1/ADC_Step = 1 / (Vref / 4096)
//=====================================================================================================================
#define _ee_uint_ADC_DSG_OT_HIGH_PROTECTION              666    //unit: 75 Celcius;  mV;Over temperature protection for discharging(High current)
#define _ee_uint_ADC_DSG_OT_HIGH_RELEASE                 846    //unit: 65 Celcius;  mV; Over temperature release for discharging(High current)
#define _ee_uint_ADC_DSG_OT_LOW_PROTECTION               750    //unit: 70 Celcius;  mV; Over temperature protection for discharging(Low current)
#define _ee_uint_ADC_DSG_OT_LOW_RELEASE                  846    //unit: 65 Celcius;  mV; Over temperature release for discharging(Low current)
#define _ee_uint_ADC_CHG_OT_PROTECTION                   909    //unit: 62 Celcius;  mV; Over temperature protection for charging()
#define _ee_uint_ADC_CHG_OT_RELEASE                      1000   //unit: 58 Celcius;  mV;  Over temperature release for charging()
#define _ee_uint_ADC_UT_PROTECTION                       3155   //unit: -5 Celcius;  mV;  Under temperature protection()
#define _ee_uint_ADC_UT_RELEASE                          2992   //unit: 0 Celcius;   mV;  Under temperature release()
//
#define _ee_uint_ADC_INITIAL_CHARGING_TEMP_RANGE_HI      909    //unit: 62 Celcius;  mV; initial start charging High temperature range
#define _ee_uint_ADC_INITIAL_CHARGING_TEMP_RANGE_LO      3155   //unit: -5 Celcius;  mV; initial start charging Low temperature range
#define _ee_uint_ADC_LOW_TEMP_SOC_CHARGING_RANGE_HI      2628   //unit: 10 Celcius;  mV; At Low temperature, High temperature range for setting SOC signal High for charging
#define _ee_uint_ADC_LOW_TEMP_SOC_CHARGING_RANGE_LO      3155   //unit: -5 Celcius;  mV; At Low temperature, Low temperature range for setting SOC signal High for charging

//////////////////////////////////////////////////////////////////////////////////
// DSG for one cycle count
// 4p * 2600mah * 0.8 = 8320 mah * _DSG_mA_to_ADC_factor_ = 2065 ADC,
// Accumulating interval time = 500 ms. ==> 1 hour = 3600 second. = 3,600,000 ms = 7200 times(per 500ms)
// 2065 ADC * 7200 = 14868000 ADC
#define _ee_ulong_ADC_AccQ_FOR_DSG_TH           14868000       //one Cycle Count Threshold; //long int => max = 4,294,967,295 = 0xffff ffff ffff ffff
//////////////////////////////////////////////////////////////////////////////////

//=====================================================================================================================
// For 3rd version Recording information condition
//=====================================================================================================================
//#define RECORDING_ADC_OVER_VOLTAGE_TH                       1942      //29.5V; for 7S Cell = 26V; unit: mV; check charging > over voltag for a long time
#define RECORDING_ADC_OVER_VOLTAGE_TH                       2771      //42.1V; for 10S Cell = 36V; unit: mV; check charging > over voltag for a long time
//#define RECORDING_ADC_OVER_VOLTAGE_TH                       3600      //54.7V; for 13S Cell = 48V; unit: mV; check charging > over voltag for a long time
//=====================================================================================================================

#define RECORDING_ADC_DSG_OVER_CURRENT_TH                   2482      //10A=10000mA; unit: mA; check > discharging TH current for recording
#define RECORDING_ADC_CHG_FASTER_CHARGING_CURRENT_TH        1117      //2500mA; unit: mA; check > charging TH current for detecting faster charging and recording
#define RECORDING_ADC_HIGH_TEMP_TH_FOR_CHARGING             1350      //45 Celcius; unit: mV; check > high temp for recording
#define RECORDING_ADC_LOW_TEMP_TH_FOR_CHARGING              2815      // 5 Celcius; unit: mV; check < low  temp for recording

#define RECORDING_ADC_LOW_TEMP_GRADE_TH1                    2628      // 10 Celcius; unit: mV; check < temp for recording
#define RECORDING_ADC_LOW_TEMP_GRADE_TH2                    2992      // 0 Celcius; unit: mV; check < temp for recording
#define RECORDING_ADC_LOW_TEMP_GRADE_TH3                    3301      // -10 Celcius; unit: mV; check < temp for recording
#define RECORDING_ADC_LOW_TEMP_GRADE_TH4                    3548      // -20 Celcius; unit: mV; check < temp for recording

#define RECORDING_ADC_HIGH_TEMP_GRADE_TH1                   953      // 60 Celcius; unit: mV; check > temp for recording
#define RECORDING_ADC_HIGH_TEMP_GRADE_TH2                   750      // 70 Celcius; unit: mV; check > temp for recording
#define RECORDING_ADC_HIGH_TEMP_GRADE_TH3                   590      // 80 Celcius; unit: mV; check > temp for recording
#define RECORDING_ADC_HIGH_TEMP_GRADE_TH4                   466      // 90 Celcius; unit: mV; check > temp for recording
#define RECORDING_ADC_HIGH_TEMP_GRADE_TH5                   369      // 100 Celcius; unit: mV; check > temp for recording
//=====================================================================================================================
//#define Enter_Auto_Sleeping_ADC_Vol_Condition               1843     // 28V; unit: mV; for 7S Cell = 26V
#define Enter_Auto_Sleeping_ADC_Vol_Condition               2633     // 40V; unit: mV; for 10S Cell = 36V
//#define Enter_Auto_Sleeping_ADC_Vol_Condition               3423     // 52V; unit: mV; for 13S Cell = 48V
//=====================================================================================================================
// For _Dynamic_UVP_With_Temperature_
#define Dynamic_UVP_ADC_TEMP_TH1                            2992      // 0 Celcius; unit: mV;
#define Dynamic_UVP_ADC_TEMP_TH2                            2436      // 15 Celcius; unit: mV;
#define Dynamic_UVP_ADC_TEMP_TH3                            2048      // 25 Celcius; unit: mV;

#define Dynamic_UVP_ADC_BATTERY_Vol_TH1                     1843      // 28V(cell:2.8); unit: 1mV; UVP < Dynamic_UVP_ADC_TEMP_TH1
#define Dynamic_UVP_ADC_BATTERY_Vol_TH2                     1909      // 29V(cell:2.9); unit: 1mV; Dynamic_UVP_ADC_TEMP_TH1 <= UVP < Dynamic_UVP_ADC_TEMP_TH2
#define Dynamic_UVP_ADC_BATTERY_Vol_TH3                     1975      // 30V(cell:3.0); unit: 1mV; Dynamic_UVP_ADC_TEMP_TH2 <= UVP < Dynamic_UVP_ADC_TEMP_TH3
//#define Dynamic_UVP_ADC_BATTERY_Vol_TH4                     2040      // 31V(cell:3.1); unit: 1mV; UVP > Dynamic_UVP_ADC_TEMP_TH3
#define Dynamic_UVP_ADC_BATTERY_Vol_TH4                     1975      // 30V(cell:3.0); unit: 1mV; UVP > Dynamic_UVP_ADC_TEMP_TH3

//=====================================================================================================================
// to record in low temp activities(dsg)
#define RECORDING_ADC_LOW_TEMP_IN_DSG_ACT_TH1               2992      // 0 Celcius; unit: mV; check < temp for recording
#define RECORDING_ADC_LOW_TEMP_IN_DSG_ACT_TH2               3301      // -10 Celcius; unit: mV; check < temp for recording
#define RECORDING_ADC_LOW_TEMP_IN_DSG_ACT_TH3               3548      // -20 Celcius; unit: mV; check < temp for recording
//=====================================================================================================================
// For Smart Charger Adapter

//=====================================================================================================================



//=====================================================================================================================
//=====================================================================================================================
// For SOC Setting
//////////////////////////////////////////////////////////////////////////
#define CELL_OV_VOLTAGE_FOR_SOC    4240 //mv
#define CELL_UV_VOLTAGE_FOR_SOC    2800 //mv
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// for 4 LEDs DSG display with 5 status
// 5 status :
// status1 : blinking led1 ==> under and include DSG_CAPACITY_DISPLAY_TH_1.
// status2 : light led1 ==>    under and include DSG_CAPACITY_DISPLAY_TH_2. and bigger than DSG_CAPACITY_DISPLAY_TH_1.
// status3 : light led2 ==>    under and include DSG_CAPACITY_DISPLAY_TH_3. and bigger than DSG_CAPACITY_DISPLAY_TH_2.
// status4 : light led3 ==>    under and include DSG_CAPACITY_DISPLAY_TH_4. and bigger than DSG_CAPACITY_DISPLAY_TH_3.
// status5 : light led4 ==>    bigger than DSG_CAPACITY_DISPLAY_TH_4.
// status6 : light led5 ==>    reserved for 5 Leds
#define _ee_uint_DSG_CAPACITY_DISPLAY_TH_1     16
#define _ee_uint_DSG_CAPACITY_DISPLAY_TH_2     37
#define _ee_uint_DSG_CAPACITY_DISPLAY_TH_3     58
#define _ee_uint_DSG_CAPACITY_DISPLAY_TH_4     79
#define _ee_uint_Reserved_DSG_CAPACITY_DISPLAY_TH_5     0    //reserved for 5 Leds
//////////////////////////////////////////////////////////////////////////
// for 4 LEDs CHG display with 5 status
// 5 status :
// status1 : led1 Breathing ==>    under and include CHG_CAPACITY_DISPLAY_TH_1.
// status2 : led2 Breathing ==>    under and include CHG_CAPACITY_DISPLAY_TH_2. and bigger than CHG_CAPACITY_DISPLAY_TH_1.
// status3 : led3 Breathing ==>    under and include CHG_CAPACITY_DISPLAY_TH_3. and bigger than CHG_CAPACITY_DISPLAY_TH_2.
// status4 : led4 Breathing ==>    bigger than CHG_CAPACITY_DISPLAY_TH_3 without Tape current.
// status5 : 4 leds light on ==>    bigger than CHG_CAPACITY_DISPLAY_TH_3 and CHG Current under Tape current.
// status6 : reserved for 5 Leds
#define _ee_uint_CHG_CAPACITY_DISPLAY_TH_1     19
#define _ee_uint_CHG_CAPACITY_DISPLAY_TH_2     35
#define _ee_uint_CHG_CAPACITY_DISPLAY_TH_3     60
#define _ee_uint_Reserved_CHG_CAPACITY_DISPLAY_TH_4     0       //reserved for 5 Leds

//=====================================================================================================================
//////////////////////////////////////////////////////////////////
//Thermistor_mV_To_ADC_Factor     1.241212f   // = 1/ADC_Step = 1 / (Vref / 4096)
//=====================================================================================================================
// DSG OCV TABLE Line Temperature Range, 4 stages, (DSG)
// 1: -5 degrees, 2: 5 degrees, 3: 15 degrees, 4: 25 degrees
// TABLE Line Temperature Range 1 (-5 degrees) : <= 0 degrees
// TABLE Line Temperature Range 2 ( 5 degrees):  0 degrees ~ 10 degrees
// TABLE Line Temperature Range 3 (15 degrees): 10 degrees ~ 20 degrees
// TABLE Line Temperature Range 4 (25 degrees): > 20 degrees
#define _ee_uint__ADC_LOOKUP_DSG_TEMP_1_TH_     2992      // 0 Celcius;
#define _ee_uint__ADC_LOOKUP_DSG_TEMP_2_TH_     2628      //10 Celcius;
#define _ee_uint__ADC_LOOKUP_DSG_TEMP_3_TH_     2241      //20 Celcius;
//=====================================================================================================================
// CHG OCV TABLE Line Temperature Range, 4 stages, (CHG)
// 1: 5 degrees, 2: 15 degrees, 3: 25 degrees
// TABLE Line Temperature Range 1 (5 degrees) : <= 10 degrees
// TABLE Line Temperature Range 2 (15 degrees): 10 degrees ~ 20 degrees
// TABLE Line Temperature Range 3 (25 degrees): > 20 degrees
#define _ee_uint__ADC_LOOKUP_CHG_TEMP_1_TH_     2628      //10 Celcius;
#define _ee_uint__ADC_LOOKUP_CHG_TEMP_2_TH_     2241      //20 Celcius;
//=====================================================================================================================

//=====================================================================================================================
//========================_NUMBER_OF_PARALLEL_CELLS_= 4  ==============================================================
////////////////////////////////////////////////////////////////
// DSG_OP_Gain   100.0f
// _DSG_mA_to_ADC_factor_     0.248242424f  ==> (Rsense_mR * DSG_OP_Gain/ADC_Step/1000)==>小數點6位
// DSG_OP_ADC_OFFSET         (signed char)0    //實際值-理論值
// 理論值 = 實際值 - Offset
////////////////////////////////////////////////////////////////////////////////
// OCV TABLE Line Current Range, 7 ocv lines, (DSG)
// Battery for a cell capacity ==> 2600 mAH * 4p
// 10.4Ah四並聯,  DSG  Current Th
//Current-10.4Ah,4P:  <=5.3A,    5.4~6.7A,   6.8~9.3A,   9.4~12.0A,  >12.1A, TBD: 15.0A, TBD: > 17.4A
#define _ee_uint__ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH1_     1316     // <= 5300mA; 2bytes;
#define _ee_uint__ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH2_     1663     // <= 6700mA; 2bytes;
#define _ee_uint__ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH3_     2309     // <= 9300mA; 2bytes;
#define _ee_uint__ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH4_     2979     // <= 12000mA; 2bytes;
#define _ee_uint__ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH5_     3724     // <= 15000mA; 2bytes;
#define _ee_uint__ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH6_     4319     // <= 17400mA; 2bytes;
//=====================================================================================================================
//=====================================================================================================================
#define _ee_uint_AUTO_ENTRY_SLEEPING_DELAY_MINUTES          1440     //1440 minutes = 24 hours
//=====================================================================================================================
// Capacity Difference values for keeping
#define _ee_uint_CAPACITY_DIFFERENCE_VALUES                 1    // % ; 2bytes;
//=====================================================================================================================
#define _ee_str_len_PROJECT_NAME_MAX_LENGTH     24
#define _ee_str_PROJECT_NAME                    "Ares_SSHT3280_36100_N"
#define _ee_str_len_MCU_UID_MAX_LENGTH          12
#define _ee_str_MCU_UID                         "-----"
#define _ee_uchar_BAR_CODE_REAL_STORE_LENGTH    24
#define _ee_str_len_BAR_CODE_MAX_LENGTH         24
#define _ee_str_BAR_CODE                         "-----"

#define _ee_uint_DESIGN_CAPACITY_mAH                        10400    //mAH,
#define _ee_uint_Last_Record_FCC_mAh_RECORD_EEPROM          10400    //mAH,

#define _ee_uint_REAL_FCC_UPDATE_TIMES_RECORD_EEPROM        0
#define _ee_uint_REAL_FCC_mAH_RECORD_EEPROM                 10400    //mAH,

#define _ee_uint_STATIC_OVER_VOLTAGE_HOURS_TIMES_RECORD_EEPROM      0    // record over voltage hours in static
#define _ee_uint_CHG_OVER_VOLTAGE_MINUTES_TIMES_RECORD_EEPROM         0    // record over voltage MINUTES in chg

#define _ee_uint_OVER_LOADING_MINUTES_TIMES_RECORD_EEPROM           0    // record over loading minutes
#define _ee_uint_FASTER_CHARGING_MINUTES_TIMES_RECORD_EEPROM        0    // record over voltage hours in chg

#define _ee_uint_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_RECORD_EEPROM    0    // record charging in high temp MINUTES
#define _ee_uint_CHARGING_IN_LOW_TEMP_MINUTES_TIMES_RECORD_EEPROM     0    // record charging in low temp MINUTES

#define _ee_uint_STORE_IN_LOW_TEMP1_HOURS_TIMES_RECORD_EEPROM       0    // record store in low temp 1 hours
#define _ee_uint_STORE_IN_LOW_TEMP2_HOURS_TIMES_RECORD_EEPROM       0    // record store in low temp 2 hours
#define _ee_uint_STORE_IN_LOW_TEMP3_HOURS_TIMES_RECORD_EEPROM       0    // record store in low temp 3 hours
#define _ee_uint_STORE_IN_LOW_TEMP4_HOURS_TIMES_RECORD_EEPROM       0    // record store in low temp 4 hours

////////////////////////////////////////////////////////////////////////////////
// Recording data to EEPROM, ==> The address could not be change.
// (from 0x0140 to 0x015f (offset: 320 ~ 352 ): 32 bytes)
////////////////////////////////////////////////////////////////////////////////
// they have to set the start offset at 4的倍數 below vars.
// and the order could not be changed below vars.
////////////////////////////////////////////////////////////////////////////////
#define _ee_uint_G_DSG_TH1_LOW_CURRENT_OTP_TIMES_RECORD_EEPROM      0
#define _ee_uint_G_DSG_TH1_HIGH_CURRENT_OTP_TIMES_RECORD_EEPROM     0
#define _ee_uint_G_DSG_TH2_LOW_CURRENT_OTP_TIMES_RECORD_EEPROM      0
#define _ee_uint_G_DSG_TH2_HIGH_CURRENT_OTP_TIMES_RECORD_EEPROM     0

#define _ee_uint_STORE_IN_HIGH_TEMP1_MINUTES_TIMES_RECORD_EEPROM    0    // record store in high temp 1 minutes
#define _ee_uint_STORE_IN_HIGH_TEMP2_MINUTES_TIMES_RECORD_EEPROM    0    // record store in high temp 2 minutes
#define _ee_uint_STORE_IN_HIGH_TEMP3_MINUTES_TIMES_RECORD_EEPROM    0    // record store in high temp 3 minutes
#define _ee_uint_STORE_IN_HIGH_TEMP4_MINUTES_TIMES_RECORD_EEPROM    0    // record store in high temp 4 minutes

#define _ee_uint_STORE_IN_HIGH_TEMP5_MINUTES_TIMES_RECORD_EEPROM    0    // record store in high temp 5 minutes
#define _ee_uint_RECORD_3rd_TRACKING_DATA_COUNT_EEPROM              0    //

#define _ee_uint_LOW_TEMP1_IN_DSG_ACT_RECORD_MINUTES_EEPROM         0    // record DSG_ACT in low temp 1 minutes
#define _ee_uint_LOW_TEMP2_IN_DSG_ACT_RECORD_MINUTES_EEPROM         0    // record DSG_ACT in low temp 2 minutes
#define _ee_uint_LOW_TEMP3_IN_DSG_ACT_RECORD_MINUTES_EEPROM         0    // record DSG_ACT in low temp 3 minutes

////////////////////////////////////////////////////////////////////////////////
//=====================================================================================================================
// to record System activity Times (double word record
#define _ee_int_RECORDING_System_Activated_Times_For_TotalHours             0   // record system activated times for total hours
//(double word record)
#define _ee_uchar_RECORDING_Reserved_Data                                   0   //
#define _ee_uchar_RECORDING_Reserved_Data1                                  0   //
#define _ee_uchar_RECORDING_Reserved_Data2                                  0   //
#define _ee_uchar_RECORDING_System_Activated_Times_Minutes_For_1_Hours      0   // record system activated times for 1 hours(60min)
////////////////////////////////////////////////////////////////////////////////
//=====================================================================================================================
// For Shake Switch Define Variables
// : each AutoWakeUp TimeCycle ==> about 1.76 sec(AutoWakeUp interval cycle time)
#define _ee_uchar_ShakeSwitchDetect_RangeTime_By_AutoWakeUp_TimeCycles      1   // RangeTime * interval cycle time,偵測Shake_Switch的時間
#define _ee_uchar_ShakeSwitchTriggerTimes_For_WakeUp      									5   // times for valide singal,在時間內Shake_Switch的被觸發的次數, wakeup成立

//=====================================================================================================================
// For GSM Define Variables
#define _ee_uchar_GSM_SetInterLockTimes_BeforeBMSSendData						20		//unit:cycles(100ms) , 2sec(org:1 sec) = GSM_SetInterLockTimes_BeforeSendData * TimerIntervalTimeBase_MS
#define _ee_uchar_GSM_SetDelayTimes_ForBMSCheckMosStatus						110		//unit:cycles(100ms) , 11 sec(org:5 sec) = GSM_SetDelayTimes_ForBMSCheckMosStatus * TimerIntervalTimeBase_MS

#define _ee_uint_GSM_System_Enter_SleepingMode_DelayTime_For_STATIC				1800	//unit:cycles(100ms) , 1800 = 180 sec = 3 min (org:10 min) = GSM_System_Enter_SleepingMode_DelayTime_For_STATIC * TimerIntervalTimeBase_MS

#define _ee_uint_GSM_SendDataFor_EachDelayTimes_For_DSG							300		//unit:cycles(100ms) , 300 = 30 sec = GSM_SendDataFor_EachDelayTimes_For_DSG * TimerIntervalTimeBase_MS
#define _ee_uint_GSM_SendDataFor_EachDelayTimes_For_CHG							3000	//unit:cycles(100ms) , 3000 = 5 min = 300 sec = GSM_SendDataFor_EachDelayTimes_For_CHG * TimerIntervalTimeBase_MS

// : each AutoWakeUp TimeCycle ==> about 1.76 sec(AutoWakeUp interval cycle time)
#define _ee_uint_GSM_SendData_For_StaticSleeping_By_AutoWakeUp_TimeCycles       6136	//180 min = 6136 * 1.76 sec = 10799 sec = 179.9 min; TimeCycle * interval cycle time; in sleeping mode

#define _ee_uint_GSM_System_WakeUp_ReadyTimes_In_SleepingMode					150		//unit:cycles(100ms) , 150 = 15 sec = GSM_System_WakeUp_ReadyTimes_In_SleepingMode * TimerIntervalTimeBase_MS
//#define _ee_uint_GSM_System_DelayTimes_After_Sending_In_SleepingMode				300		//unit:cycles(100ms) , 300 = 30 sec = GSM_System_DelayTimes_After_Sending_In_SleepingMode * TimerIntervalTimeBase_MS

#define _ee_uint_SleepMode_Autowakeup_Intervaltimes_ms                          1780    //unit:ms ; 2bytes		
//=====================================================================================================================
//start align 4
#define _ee_float_SleepMode_Autowakeup_Intervaltimes_sec          1.78f        // 4 bytes; unit: sec
#define _ee_float_SleepMode_Autowakeup_Intervaltimes_min          0.0296666f   // 4 bytes; unit: min (1.78/60)

#define _ee_ulong_LastTotalTimes_Without_Charging_Minutes_RECORD_EEPROM         0   //max = 4,294,967,295 = 0xffff ffff
#define _ee_ulong_MaxTotalTimes_Without_Charging_Minutes_RECORD_EEPROM          0   //max = 4,294,967,295 = 0xffff ffff
#define _ee_ulong_LastTotalTimes_Without_DisCharging_Minutes_RECORD_EEPROM      0   //max = 4,294,967,295 = 0xffff ffff
#define _ee_ulong_MaxTotalTimes_Without_DisCharging_Minutes_RECORD_EEPROM       0   //max = 4,294,967,295 = 0xffff ffff

#define _ee_uint_Last_ChargingTimes_Minutes_RECORD_EEPROM         0	// 2bytes; unit:min
#define _ee_uint_Max_ChargingTimes_Minutes_RECORD_EEPROM          0	// 2bytes; unit:min

//=====================================================================================================================
#define _ee_uchar_EEPROM_END_DATA_POSITION          160  // EEPROM/Flash End code = 160 = 0xA0
//=====================================================================================================================

//=====================================================================================================================
#define _ee_uchar_EEPROM_PN_INFO_START_DATA_POSITION    165  // EEPROM/Flash End code = 165 = 0xA5
//=====================================================================================================================

#define _ee_str_len_PN_DAK_NAME_MAX_LENGTH          24
#define _ee_str_PN_DAK_NAME                         "-----"
#define _ee_str_len_PN_85K_NAME_MAX_LENGTH          24
#define _ee_str_PN_85K_NAME                         "-----"
#define _ee_str_len_Cell_PN_NAME_MAX_LENGTH         24
#define _ee_str_Cell_PN_NAME                        "-----"


//=====================================================================================================================
#define _ee_uchar_EEPROM_PN_INFO_END_DATA_POSITION      165  // EEPROM/Flash End code = 165 = 0xA5
//=====================================================================================================================
