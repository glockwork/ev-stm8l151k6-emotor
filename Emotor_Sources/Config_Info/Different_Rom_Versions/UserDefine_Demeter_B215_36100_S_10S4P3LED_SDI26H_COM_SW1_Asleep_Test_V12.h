
/**
  ******************************************************************************
  * @file    User_Define.h
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
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
#define _ee_ulong_RESERVED_CAL_FOR_OFFSET1       0
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
#define _ee_ulong_CHG_ADC_AccumulatingQ_RECORD_EEPROM   0   //max = 4,294,967,295 = 0xffff ffff ffff ffff
//------------------------------------------------------------------------------------------
#define _ee_ulong_DSG_ADC_AccumulatingQ_RECORD_EEPROM   0   //max = 4,294,967,295 = 0xffff ffff ffff ffff

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

#define _ee_uint_G_TH1_UTP_TIMES_RECORD_EEPROM          0
#define _ee_uint_G_TH2_UTP_TIMES_RECORD_EEPROM          0

#define _ee_uint_G_CHG_TH1_OTP_TIMES_RECORD_EEPROM      0
#define _ee_uint_G_CHG_TH2_OTP_TIMES_RECORD_EEPROM      0

#define _ee_uint_RECORD_2nd_DATA_COUNT_EEPROM           0 //Reserved
#define _ee_uint_RESERVED_Recording_FOR_OFFSET3         0 //Reserved

//=====================================================================================================================

////////////////////////////////////////////////////////////////////////////////
// Default init Data start offset address : 0x0060  (offset = 96)
//////////////////////////////////////////////////////////////////
#define _ee_uint_RESERVED_FOR_OFFSET2               160     // 2 bytes // no used //NUMBER_OF_USED_EEPROM_BYTES
#define _ee_uchar_System_Control_Bit_EEPROM         12      // 1 byte
#define _ee_uchar_RESERVED_FOR_OFFSET1              0


////////////////////////////////////////////////////////////////////////////////
#define _ee_uchar_VERSION                       255//(don't change), has to be define at FW_Version_Define, 1 bytes//for main function addition and EEPROM Format changing
#define _ee_uchar_MINOR_VERSION                 255//(don't change), has to be define at FW_Version_Define, 1 bytes//only for minor functions changing

#define _ee_uchar_EEPROM_VERSION                12      // 1 bytes //only for EEPROM values changing

#define _ee_uchar_RESERVED_VERSION              255//(don't change),has to be define at FW_Version_Define, 1 bytes//0x00: Protuction, 0x01: Samples
////////////////////////////////////////////////////////////////////////////////

#define _ee_uchar_NUMBER_OF_PARALLEL_CELLS      4       // 1 bytes
#define _ee_uchar_NUMBER_OF_SERIES_CELLS        10      // 1 bytes

//#define MANUFACTURE_DATE_YEAR   2013
//#define MANUFACTURE_DATE_MONTH  1
//#define MANUFACTURE_DATE_DAY    22
#define _ee_uint_MANUFACTURE_DATE               16950   //(MANUFACTURE_DATE_YEAR - 1980) * 512 + MANUFACTURE_DATE_MONTH * 32 + MANUFACTURE_DATE_DAY  // 2 bytes
#define _ee_uint_SERIAL_NUMBER                  10      // 2 bytes

//=====================================================================================================================
//First set String Length
//then second set String
#define _ee_str_len_CELL_TYPE_LENGTH            8
#define _ee_str_CELL_TYPE                       "SDI 26H_"
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
//#define _ee_uint_ADC_CURRENT_DETECT_FOR_DSG_STATUS       22       //89mA; unit: mA; 2bytes; if current > the define, in discharging status
//#define _ee_uint_ADC_CURRENT_DETECT_FOR_CHG_STATUS       38       //85mA; unit: mA; 2bytes; if current > the define, in charging status
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
#define _ee_uint_ADC_DSG_OT_HIGH_PROTECTION              524    //unit: 85 Celcius;  mV;Over temperature protection for discharging(High current)
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
#define RECORDING_ADC_OVER_VOLTAGE_TH                       2771      //42.1V; unit: mV; check charging > over voltag for a long time
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
// for 3 LEDs DSG display with 4 status
// 4 status :
// status1 : blinking led1 ==> under and include DSG_CAPACITY_DISPLAY_TH_1.
// status2 : light led1 ==>    under and include DSG_CAPACITY_DISPLAY_TH_2. and bigger than DSG_CAPACITY_DISPLAY_TH_1.
// status3 : light led2 ==>    under and include DSG_CAPACITY_DISPLAY_TH_3. and bigger than DSG_CAPACITY_DISPLAY_TH_2.
// status4 : light led3 ==>    bigger than DSG_CAPACITY_DISPLAY_TH_3.
// status5 : light led4 ==>    reserved for 4 Leds
// status6 : light led5 ==>    reserved for 5 Leds
#define _ee_uint_DSG_CAPACITY_DISPLAY_TH_1     30
#define _ee_uint_DSG_CAPACITY_DISPLAY_TH_2     50
#define _ee_uint_DSG_CAPACITY_DISPLAY_TH_3     80
#define _ee_uint_Reserved_DSG_CAPACITY_DISPLAY_TH_4     0
#define _ee_uint_Reserved_DSG_CAPACITY_DISPLAY_TH_5     0
//////////////////////////////////////////////////////////////////////////
// for 3 LEDs CHG display with 4 status
// 4 status :
// status1 : led1 Breathing ==>    under and include CHG_CAPACITY_DISPLAY_TH_1.
// status2 : led2 Breathing ==>    under and include CHG_CAPACITY_DISPLAY_TH_2. and bigger than CHG_CAPACITY_DISPLAY_TH_1.
// status3 : led3 Breathing ==>    bigger than CHG_CAPACITY_DISPLAY_TH_2 without Tape current.
// status4 : 3 leds light on ==>   bigger than CHG_CAPACITY_DISPLAY_TH_2 and CHG Current under Tape current.
// status5 : reserved for 4 Leds
// status6 : reserved for 5 Leds
#define _ee_uint_CHG_CAPACITY_DISPLAY_TH_1     40
#define _ee_uint_CHG_CAPACITY_DISPLAY_TH_2     70
#define _ee_uint_Reserved_CHG_CAPACITY_DISPLAY_TH_3     0
#define _ee_uint_Reserved_CHG_CAPACITY_DISPLAY_TH_4     0

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
#define _ee_uint_AUTO_ENTRY_SLEEPING_DELAY_MINUTES          720     //720 minutes = 12 hours
//=====================================================================================================================
// Capacity Difference values for keeping
#define _ee_uint_CAPACITY_DIFFERENCE_VALUES                 1    // % ; 2bytes;
//=====================================================================================================================
#define _ee_str_len_PROJECT_NAME_MAX_LENGTH     24
#define _ee_str_PROJECT_NAME                    "Demeter_B215_36100"
#define _ee_str_len_MCU_UID_MAX_LENGTH          12
#define _ee_str_MCU_UID                         "-----"
#define _ee_uchar_BAR_CODE_REAL_STORE_LENGTH    24
#define _ee_str_len_BAR_CODE_MAX_LENGTH         24
#define _ee_str_BAR_CODE                         "-----"

#define _ee_uint_DESIGN_CAPACITY_mAH                        10000    //mAH,
#define _ee_uint_RESERVED_NoUsed__User_Define_FOR_OFFSET1   0

#define _ee_uint_REAL_FCC_UPDATE_TIMES_RECORD_EEPROM        0
#define _ee_uint_REAL_FCC_mAH_RECORD_EEPROM                 10000    //mAH,

#define _ee_uint_STATIC_OVER_VOLTAGE_HOURS_TIMES_RECORD_EEPROM      0    // record over voltage hours in static
#define _ee_uint_CHG_OVER_VOLTAGE_HOURS_TIMES_RECORD_EEPROM         0    // record over voltage hours in chg

#define _ee_uint_OVER_LOADING_MINUTES_TIMES_RECORD_EEPROM           0    // record over loading minutes
#define _ee_uint_FASTER_CHARGING_MINUTES_TIMES_RECORD_EEPROM        0    // record over voltage hours in chg

#define _ee_uint_CHARGING_IN_HIGH_TEMP_HOURS_TIMES_RECORD_EEPROM    0    // record charging in high temp hours
#define _ee_uint_CHARGING_IN_LOW_TEMP_HOURS_TIMES_RECORD_EEPROM     0    // record charging in low temp hours

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

//=====================================================================================================================
#define _ee_uchar_EEPROM_END_DATA_POSITION          85  // EEPROM/Flash End code = 85 = 0x55
//=====================================================================================================================
