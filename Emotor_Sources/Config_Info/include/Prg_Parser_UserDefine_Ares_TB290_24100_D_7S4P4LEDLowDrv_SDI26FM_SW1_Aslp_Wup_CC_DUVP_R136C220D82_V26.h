/////////////////////////////////////////////////////////////////////////// 
// 
// this file is created by Header Parser Application written by Hsinmo.
// this file is parsed from the file : 
// file Name: D:\Temp\ST_MCU_Codes\LEV_G2_STM8L151K6_2_v2\IAR_project\..\Source_Codes\Config_Info\UserDefine_Ares_TB290_24100_D_7S4P4LEDLowDrv_SDI26FM_SW1_Aslp_Wup_CC_DUVP_R136C220D82_V26.h
// 
/////////////////////////////////////////////////////////////////////////// 
#define ParsingFileName               "UserDefine_Ares_TB290_24100_D_7S4P4LEDLowDrv_SDI26FM_SW1_Aslp_Wup_CC_DUVP_R136C220D82_V26.h"
#define ParsingDate                   __DATE__
#define ParsingTime                   __TIME__
#define ParsingProjectName            "Ares_TB290_24100_D"

/////////////////////////////////////////////////////////////////////////// 
// 
// 
// Extra Var Define
// 
/////////////////////////////////////////////////////////////////////////// 
#define  RECORDING_ADC_OVER_VOLTAGE_TH                                 1942       //29.5V; for 7S Cell = 26V; unit: mV; check charging > over voltag for a long time
#define  RECORDING_ADC_DSG_OVER_CURRENT_TH                             1388       //10A=10000mA; unit: mA; check > discharging TH current for recording
#define  RECORDING_ADC_CHG_FASTER_CHARGING_CURRENT_TH                  931        //2500mA; unit: mA; check > charging TH current for detecting faster charging and recording
#define  RECORDING_ADC_HIGH_TEMP_TH_FOR_CHARGING                       1350       //45 Celcius; unit: mV; check > high temp for recording
#define  RECORDING_ADC_LOW_TEMP_TH_FOR_CHARGING                        2815       // 5 Celcius; unit: mV; check < low temp for recording
#define  RECORDING_ADC_LOW_TEMP_GRADE_TH1                              2628       // 10 Celcius; unit: mV; check < temp for recording
#define  RECORDING_ADC_LOW_TEMP_GRADE_TH2                              2992       // 0 Celcius; unit: mV; check < temp for recording
#define  RECORDING_ADC_LOW_TEMP_GRADE_TH3                              3301       // -10 Celcius; unit: mV; check < temp for recording
#define  RECORDING_ADC_LOW_TEMP_GRADE_TH4                              3548       // -20 Celcius; unit: mV; check < temp for recording
#define  RECORDING_ADC_HIGH_TEMP_GRADE_TH1                             953        // 60 Celcius; unit: mV; check > temp for recording
#define  RECORDING_ADC_HIGH_TEMP_GRADE_TH2                             750        // 70 Celcius; unit: mV; check > temp for recording
#define  RECORDING_ADC_HIGH_TEMP_GRADE_TH3                             590        // 80 Celcius; unit: mV; check > temp for recording
#define  RECORDING_ADC_HIGH_TEMP_GRADE_TH4                             466        // 90 Celcius; unit: mV; check > temp for recording
#define  RECORDING_ADC_HIGH_TEMP_GRADE_TH5                             369        // 100 Celcius; unit: mV; check > temp for recording
#define  Enter_Auto_Sleeping_ADC_Vol_Condition                         1843       // 28V; unit: mV; for 7S Cell = 26V
#define  Dynamic_UVP_ADC_TEMP_TH1                                      2992       // 0 Celcius; unit: mV;
#define  Dynamic_UVP_ADC_TEMP_TH2                                      2436       // 15 Celcius; unit: mV;
#define  Dynamic_UVP_ADC_TEMP_TH3                                      2048       // 25 Celcius; unit: mV;
#define  Dynamic_UVP_ADC_BATTERY_Vol_TH1                               1290       // 19.6V(cell:2.8); unit: 1mV; UVP < Dynamic_UVP_ADC_TEMP_TH1
#define  Dynamic_UVP_ADC_BATTERY_Vol_TH2                               1336       // 20.3V(cell:2.9); unit: 1mV; Dynamic_UVP_ADC_TEMP_TH1 <= UVP < Dynamic_UVP_ADC_TEMP_TH2
#define  Dynamic_UVP_ADC_BATTERY_Vol_TH3                               1382       // 21V(cell:3.0); unit: 1mV; Dynamic_UVP_ADC_TEMP_TH2 <= UVP < Dynamic_UVP_ADC_TEMP_TH3
#define  Dynamic_UVP_ADC_BATTERY_Vol_TH4                               1382       // 21V(cell:3.0); unit: 1mV; UVP > Dynamic_UVP_ADC_TEMP_TH3
#define  RECORDING_ADC_LOW_TEMP_IN_DSG_ACT_TH1                         2992       // 0 Celcius; unit: mV; check < temp for recording
#define  RECORDING_ADC_LOW_TEMP_IN_DSG_ACT_TH2                         3301       // -10 Celcius; unit: mV; check < temp for recording
#define  RECORDING_ADC_LOW_TEMP_IN_DSG_ACT_TH3                         3548       // -20 Celcius; unit: mV; check < temp for recording
#define  CELL_OV_VOLTAGE_FOR_SOC                                       4240       //mv
#define  CELL_UV_VOLTAGE_FOR_SOC                                       2800       //mv
// 
// 
/////////////////////////////////////////////////////////////////////////// 
#define CONFIG_SEGMENT                                              0x1000
// 
// Data Offset
#define CHG_mA_To_ADC_Factor_Offset                                 0     // 0x0
#define DSG_mA_To_ADC_Factor_Offset                                 4     // 0x4
#define VBAT_mV_To_ADC_Factor_Offset                                8     // 0x8
#define Thermistor_mV_To_ADC_Factor_Offset                          12    // 0xC
#define DSG_OP_ADC_OFFSET_Offset                                    16    // 0x10
#define CHG_OP_ADC_OFFSET_Offset                                    17    // 0x11
#define VBAT_ADC_OFFSET_Offset                                      18    // 0x12
#define NTC1_ADC_OFFSET_Offset                                      19    // 0x13
#define NTC2_ADC_OFFSET_Offset                                      20    // 0x14
#define SOC_ADC_OFFSET_Offset                                       21    // 0x15
#define R_Sense_10u_ohm_Offset                                      22    // 0x16
#define MCU_Major_Type_Code_Offset                                  24    // 0x18
#define MCU_Minor_Type_Code_Offset                                  25    // 0x19
#define RESERVED_CAL_FOR_OFFSET2_Offset                             26    // 0x1A
#define RESERVED_CAL_FOR_OFFSET3_Offset                             30    // 0x1E
#define MAX_DSG_C_ADC_RECORD_EEPROM_Offset                          32    // 0x20
#define MAX_CHG_C_ADC_RECORD_EEPROM_Offset                          34    // 0x22
#define MAX_VBAT_ADC_RECORD_EEPROM_Offset                           36    // 0x24
#define MIN_VBAT_ADC_RECORD_EEPROM_Offset                           38    // 0x26
#define MAX_VBAT_SocLo_ADC_RECORD_EEPROM_Offset                     40    // 0x28
#define MAX_VBAT_SocHi_ADC_RECORD_EEPROM_Offset                     42    // 0x2A
#define DSG_MAX_TH1_ADC_RECORD_EEPROM_Offset                        44    // 0x2C
#define DSG_MIN_TH1_ADC_RECORD_EEPROM_Offset                        46    // 0x2E
#define DSG_MAX_TH2_ADC_RECORD_EEPROM_Offset                        48    // 0x30
#define DSG_MIN_TH2_ADC_RECORD_EEPROM_Offset                        50    // 0x32
#define RECORD_DATA_COUNT_EEPROM_Offset                             52    // 0x34
#define CHG_Cycle_Count_RECORD_EEPROM_Offset                        54    // 0x36
#define CHG_ADC_AccumulatingQ_RECORD_EEPROM_Offset                  56    // 0x38
#define DSG_ADC_AccumulatingQ_RECORD_EEPROM_Offset                  60    // 0x3C
#define DSG_Cycle_Count_RECORD_EEPROM_Offset                        64    // 0x40
#define RESERVED_Recording_FOR_OFFSET1_Offset                       66    // 0x42
#define CHG_MAX_TH1_ADC_RECORD_EEPROM_Offset                        68    // 0x44
#define CHG_MIN_TH1_ADC_RECORD_EEPROM_Offset                        70    // 0x46
#define CHG_MAX_TH2_ADC_RECORD_EEPROM_Offset                        72    // 0x48
#define CHG_MIN_TH2_ADC_RECORD_EEPROM_Offset                        74    // 0x4A
#define G_OVP_TIMES_RECORD_EEPROM_Offset                            76    // 0x4C
#define G_UVP_TIMES_RECORD_EEPROM_Offset                            78    // 0x4E
#define G_COCP_TIMES_RECORD_EEPROM_Offset                           80    // 0x50
#define G_DOCP_TIMES_RECORD_EEPROM_Offset                           82    // 0x52
#define G_TH1_CHG_UTP_TIMES_RECORD_EEPROM_Offset                    84    // 0x54
#define G_TH2_CHG_UTP_TIMES_RECORD_EEPROM_Offset                    86    // 0x56
#define G_CHG_TH1_OTP_TIMES_RECORD_EEPROM_Offset                    88    // 0x58
#define G_CHG_TH2_OTP_TIMES_RECORD_EEPROM_Offset                    90    // 0x5A
#define RECORD_2nd_DATA_COUNT_EEPROM_Offset                         92    // 0x5C
#define RESERVED_Recording_FOR_OFFSET3_Offset                       94    // 0x5E
#define SystemSetting_Info_Byte1_Offset                             96    // 0x60
#define SystemSetting_Info_Byte2_Offset                             97    // 0x61
#define System_Control_Bit_EEPROM_Offset                            98    // 0x62
#define SystemSetting_Info_Byte3_Offset                             99    // 0x63
#define VERSION_Offset                                              100   // 0x64
#define MINOR_VERSION_Offset                                        101   // 0x65
#define EEPROM_VERSION_Offset                                       102   // 0x66
#define RESERVED_VERSION_Offset                                     103   // 0x67
#define NUMBER_OF_PARALLEL_CELLS_Offset                             104   // 0x68
#define NUMBER_OF_SERIES_CELLS_Offset                               105   // 0x69
#define MANUFACTURE_DATE_Offset                                     106   // 0x6A
#define SERIAL_NUMBER_Offset                                        108   // 0x6C
#define CELL_TYPE_LENGTH_Offset                                     110   // 0x6E
#define CELL_TYPE_Offset                                            111   // 0x6F
#define MANUFACTURE_NAME_LENGTH_Offset                              119   // 0x77
#define MANUFACTURE_NAME_Offset                                     120   // 0x78
#define ADC_CURRENT_DETECT_FOR_DSG_STATUS_Offset                    128   // 0x80
#define ADC_CURRENT_DETECT_FOR_CHG_STATUS_Offset                    130   // 0x82
#define ADC_DOC_PROTECTION_Offset                                   132   // 0x84
#define ADC_COC_PROTECTION_Offset                                   134   // 0x86
#define ADC_DSG_HIGH_CURRENT_DETECT_Offset                          136   // 0x88
#define ADC_CHG_CHARGER_TAPE_CURRENT_Offset                         138   // 0x8A
#define ADC_AccQ_FOR_CHG_TH_Offset                                  140   // 0x8C
#define Cycle_Count_FOR_CHG_1st_TH_Offset                           144   // 0x90
#define Cycle_Count_FOR_CHG_2nd_TH_Offset                           146   // 0x92
#define ADC_BATTERY_OV_PROTECTION_Offset                            148   // 0x94
#define ADC_BATTERY_OV_RELEASE_Offset                               150   // 0x96
#define ADC_BATTERY_UV_PROTECTION_Offset                            152   // 0x98
#define ADC_BATTERY_UV_RELEASE_Offset                               154   // 0x9A
#define ADC_DSG_OT_HIGH_PROTECTION_Offset                           156   // 0x9C
#define ADC_DSG_OT_HIGH_RELEASE_Offset                              158   // 0x9E
#define ADC_DSG_OT_LOW_PROTECTION_Offset                            160   // 0xA0
#define ADC_DSG_OT_LOW_RELEASE_Offset                               162   // 0xA2
#define ADC_CHG_OT_PROTECTION_Offset                                164   // 0xA4
#define ADC_CHG_OT_RELEASE_Offset                                   166   // 0xA6
#define ADC_UT_PROTECTION_Offset                                    168   // 0xA8
#define ADC_UT_RELEASE_Offset                                       170   // 0xAA
#define ADC_INITIAL_CHARGING_TEMP_RANGE_HI_Offset                   172   // 0xAC
#define ADC_INITIAL_CHARGING_TEMP_RANGE_LO_Offset                   174   // 0xAE
#define ADC_LOW_TEMP_SOC_CHARGING_RANGE_HI_Offset                   176   // 0xB0
#define ADC_LOW_TEMP_SOC_CHARGING_RANGE_LO_Offset                   178   // 0xB2
#define ADC_AccQ_FOR_DSG_TH_Offset                                  180   // 0xB4
#define DSG_CAPACITY_DISPLAY_TH_1_Offset                            184   // 0xB8
#define DSG_CAPACITY_DISPLAY_TH_2_Offset                            186   // 0xBA
#define DSG_CAPACITY_DISPLAY_TH_3_Offset                            188   // 0xBC
#define DSG_CAPACITY_DISPLAY_TH_4_Offset                            190   // 0xBE
#define Reserved_DSG_CAPACITY_DISPLAY_TH_5_Offset                   192   // 0xC0
#define CHG_CAPACITY_DISPLAY_TH_1_Offset                            194   // 0xC2
#define CHG_CAPACITY_DISPLAY_TH_2_Offset                            196   // 0xC4
#define CHG_CAPACITY_DISPLAY_TH_3_Offset                            198   // 0xC6
#define Reserved_CHG_CAPACITY_DISPLAY_TH_4_Offset                   200   // 0xC8
#define _ADC_LOOKUP_DSG_TEMP_1_TH__Offset                           202   // 0xCA
#define _ADC_LOOKUP_DSG_TEMP_2_TH__Offset                           204   // 0xCC
#define _ADC_LOOKUP_DSG_TEMP_3_TH__Offset                           206   // 0xCE
#define _ADC_LOOKUP_CHG_TEMP_1_TH__Offset                           208   // 0xD0
#define _ADC_LOOKUP_CHG_TEMP_2_TH__Offset                           210   // 0xD2
#define _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH1__Offset               212   // 0xD4
#define _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH2__Offset               214   // 0xD6
#define _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH3__Offset               216   // 0xD8
#define _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH4__Offset               218   // 0xDA
#define _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH5__Offset               220   // 0xDC
#define _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH6__Offset               222   // 0xDE
#define AUTO_ENTRY_SLEEPING_DELAY_MINUTES_Offset                    224   // 0xE0
#define CAPACITY_DIFFERENCE_VALUES_Offset                           226   // 0xE2
#define PROJECT_NAME_MAX_LENGTH_Offset                              228   // 0xE4
#define PROJECT_NAME_Offset                                         229   // 0xE5
#define MCU_UID_MAX_LENGTH_Offset                                   253   // 0xFD
#define MCU_UID_Offset                                              254   // 0xFE
#define BAR_CODE_REAL_STORE_LENGTH_Offset                           266   // 0x10A
#define BAR_CODE_MAX_LENGTH_Offset                                  267   // 0x10B
#define BAR_CODE_Offset                                             268   // 0x10C
#define DESIGN_CAPACITY_mAH_Offset                                  292   // 0x124
#define Last_Record_FCC_mAh_RECORD_EEPROM_Offset                    294   // 0x126
#define REAL_FCC_UPDATE_TIMES_RECORD_EEPROM_Offset                  296   // 0x128
#define REAL_FCC_mAH_RECORD_EEPROM_Offset                           298   // 0x12A
#define STATIC_OVER_VOLTAGE_HOURS_TIMES_RECORD_EEPROM_Offset        300   // 0x12C
#define CHG_OVER_VOLTAGE_MINUTES_TIMES_RECORD_EEPROM_Offset         302   // 0x12E
#define OVER_LOADING_MINUTES_TIMES_RECORD_EEPROM_Offset             304   // 0x130
#define FASTER_CHARGING_MINUTES_TIMES_RECORD_EEPROM_Offset          306   // 0x132
#define CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_RECORD_EEPROM_Offset    308   // 0x134
#define CHARGING_IN_LOW_TEMP_MINUTES_TIMES_RECORD_EEPROM_Offset     310   // 0x136
#define STORE_IN_LOW_TEMP1_HOURS_TIMES_RECORD_EEPROM_Offset         312   // 0x138
#define STORE_IN_LOW_TEMP2_HOURS_TIMES_RECORD_EEPROM_Offset         314   // 0x13A
#define STORE_IN_LOW_TEMP3_HOURS_TIMES_RECORD_EEPROM_Offset         316   // 0x13C
#define STORE_IN_LOW_TEMP4_HOURS_TIMES_RECORD_EEPROM_Offset         318   // 0x13E
#define G_DSG_TH1_LOW_CURRENT_OTP_TIMES_RECORD_EEPROM_Offset        320   // 0x140
#define G_DSG_TH1_HIGH_CURRENT_OTP_TIMES_RECORD_EEPROM_Offset       322   // 0x142
#define G_DSG_TH2_LOW_CURRENT_OTP_TIMES_RECORD_EEPROM_Offset        324   // 0x144
#define G_DSG_TH2_HIGH_CURRENT_OTP_TIMES_RECORD_EEPROM_Offset       326   // 0x146
#define STORE_IN_HIGH_TEMP1_MINUTES_TIMES_RECORD_EEPROM_Offset      328   // 0x148
#define STORE_IN_HIGH_TEMP2_MINUTES_TIMES_RECORD_EEPROM_Offset      330   // 0x14A
#define STORE_IN_HIGH_TEMP3_MINUTES_TIMES_RECORD_EEPROM_Offset      332   // 0x14C
#define STORE_IN_HIGH_TEMP4_MINUTES_TIMES_RECORD_EEPROM_Offset      334   // 0x14E
#define STORE_IN_HIGH_TEMP5_MINUTES_TIMES_RECORD_EEPROM_Offset      336   // 0x150
#define RECORD_3rd_TRACKING_DATA_COUNT_EEPROM_Offset                338   // 0x152
#define LOW_TEMP1_IN_DSG_ACT_RECORD_MINUTES_EEPROM_Offset           340   // 0x154
#define LOW_TEMP2_IN_DSG_ACT_RECORD_MINUTES_EEPROM_Offset           342   // 0x156
#define LOW_TEMP3_IN_DSG_ACT_RECORD_MINUTES_EEPROM_Offset           344   // 0x158
#define RECORDING_System_Activated_Times_For_TotalHours_Offset      346   // 0x15A
#define RECORDING_Reserved_Data_Offset                              348   // 0x15C
#define RECORDING_Reserved_Data1_Offset                             349   // 0x15D
#define RECORDING_Reserved_Data2_Offset                             350   // 0x15E
#define RECORDING_System_Activated_Times_Minutes_For_1_Hours_Offset 351   // 0x15F
#define ShakeSwitchDetect_RangeTime_By_AutoWakeUp_TimeCycles_Offset 352   // 0x160
#define ShakeSwitchTriggerTimes_For_WakeUp_Offset                   353   // 0x161
#define GSM_SetInterLockTimes_BeforeBMSSendData_Offset              354   // 0x162
#define GSM_SetDelayTimes_ForBMSCheckMosStatus_Offset               355   // 0x163
#define GSM_System_Enter_SleepingMode_DelayTime_For_STATIC_Offset   356   // 0x164
#define GSM_SendDataFor_EachDelayTimes_For_DSG_Offset               358   // 0x166
#define GSM_SendDataFor_EachDelayTimes_For_CHG_Offset               360   // 0x168
#define GSM_SendData_For_StaticSleeping_By_AutoWakeUp_TimeCycles_Offset 362   // 0x16A
#define GSM_System_WakeUp_ReadyTimes_In_SleepingMode_Offset         364   // 0x16C
#define SleepMode_Autowakeup_Intervaltimes_ms_Offset                366   // 0x16E
#define SleepMode_Autowakeup_Intervaltimes_sec_Offset               368   // 0x170
#define SleepMode_Autowakeup_Intervaltimes_min_Offset               372   // 0x174
#define LastTotalTimes_Without_Charging_Minutes_RECORD_EEPROM_Offset 376   // 0x178
#define MaxTotalTimes_Without_Charging_Minutes_RECORD_EEPROM_Offset 380   // 0x17C
#define LastTotalTimes_Without_DisCharging_Minutes_RECORD_EEPROM_Offset 384   // 0x180
#define MaxTotalTimes_Without_DisCharging_Minutes_RECORD_EEPROM_Offset 388   // 0x184
#define Last_ChargingTimes_Minutes_RECORD_EEPROM_Offset             392   // 0x188
#define Max_ChargingTimes_Minutes_RECORD_EEPROM_Offset              394   // 0x18A
#define EEPROM_END_DATA_POSITION_Offset                             396   // 0x18C
#define EEPROM_PN_INFO_START_DATA_POSITION_Offset                   397   // 0x18D
#define PN_DAK_NAME_MAX_LENGTH_Offset                               398   // 0x18E
#define PN_DAK_NAME_Offset                                          399   // 0x18F
#define PN_85K_NAME_MAX_LENGTH_Offset                               423   // 0x1A7
#define PN_85K_NAME_Offset                                          424   // 0x1A8
#define Cell_PN_NAME_MAX_LENGTH_Offset                              448   // 0x1C0
#define Cell_PN_NAME_Offset                                         449   // 0x1C1
#define EEPROM_PN_INFO_END_DATA_POSITION_Offset                     473   // 0x1D9
// 
/////////////////////////////////////////////////////////////////////////// 
// 
// Data Var Point
#define CHG_mA_To_ADC_Factor                                        *((float *)(CONFIG_SEGMENT + CHG_mA_To_ADC_Factor_Offset ))
#define DSG_mA_To_ADC_Factor                                        *((float *)(CONFIG_SEGMENT + DSG_mA_To_ADC_Factor_Offset ))
#define VBAT_mV_To_ADC_Factor                                       *((float *)(CONFIG_SEGMENT + VBAT_mV_To_ADC_Factor_Offset ))
#define Thermistor_mV_To_ADC_Factor                                 *((float *)(CONFIG_SEGMENT + Thermistor_mV_To_ADC_Factor_Offset ))
#define DSG_OP_ADC_OFFSET                                           *((signed char *)(CONFIG_SEGMENT + DSG_OP_ADC_OFFSET_Offset ))
#define CHG_OP_ADC_OFFSET                                           *((signed char *)(CONFIG_SEGMENT + CHG_OP_ADC_OFFSET_Offset ))
#define VBAT_ADC_OFFSET                                             *((signed char *)(CONFIG_SEGMENT + VBAT_ADC_OFFSET_Offset ))
#define NTC1_ADC_OFFSET                                             *((signed char *)(CONFIG_SEGMENT + NTC1_ADC_OFFSET_Offset ))
#define NTC2_ADC_OFFSET                                             *((signed char *)(CONFIG_SEGMENT + NTC2_ADC_OFFSET_Offset ))
#define SOC_ADC_OFFSET                                              *((signed char *)(CONFIG_SEGMENT + SOC_ADC_OFFSET_Offset ))
#define R_Sense_10u_ohm                                             *((unsigned int *)(CONFIG_SEGMENT + R_Sense_10u_ohm_Offset ))
#define MCU_Major_Type_Code                                         *((unsigned char *)(CONFIG_SEGMENT + MCU_Major_Type_Code_Offset ))
#define MCU_Minor_Type_Code                                         *((unsigned char *)(CONFIG_SEGMENT + MCU_Minor_Type_Code_Offset ))
#define RESERVED_CAL_FOR_OFFSET2                                    *((unsigned long *)(CONFIG_SEGMENT + RESERVED_CAL_FOR_OFFSET2_Offset ))
#define RESERVED_CAL_FOR_OFFSET3                                    *((unsigned int *)(CONFIG_SEGMENT + RESERVED_CAL_FOR_OFFSET3_Offset ))
#define MAX_DSG_C_ADC_RECORD_EEPROM                                 *((unsigned int *)(CONFIG_SEGMENT + MAX_DSG_C_ADC_RECORD_EEPROM_Offset ))
#define MAX_CHG_C_ADC_RECORD_EEPROM                                 *((unsigned int *)(CONFIG_SEGMENT + MAX_CHG_C_ADC_RECORD_EEPROM_Offset ))
#define MAX_VBAT_ADC_RECORD_EEPROM                                  *((unsigned int *)(CONFIG_SEGMENT + MAX_VBAT_ADC_RECORD_EEPROM_Offset ))
#define MIN_VBAT_ADC_RECORD_EEPROM                                  *((unsigned int *)(CONFIG_SEGMENT + MIN_VBAT_ADC_RECORD_EEPROM_Offset ))
#define MAX_VBAT_SocLo_ADC_RECORD_EEPROM                            *((unsigned int *)(CONFIG_SEGMENT + MAX_VBAT_SocLo_ADC_RECORD_EEPROM_Offset ))
#define MAX_VBAT_SocHi_ADC_RECORD_EEPROM                            *((unsigned int *)(CONFIG_SEGMENT + MAX_VBAT_SocHi_ADC_RECORD_EEPROM_Offset ))
#define DSG_MAX_TH1_ADC_RECORD_EEPROM                               *((unsigned int *)(CONFIG_SEGMENT + DSG_MAX_TH1_ADC_RECORD_EEPROM_Offset ))
#define DSG_MIN_TH1_ADC_RECORD_EEPROM                               *((unsigned int *)(CONFIG_SEGMENT + DSG_MIN_TH1_ADC_RECORD_EEPROM_Offset ))
#define DSG_MAX_TH2_ADC_RECORD_EEPROM                               *((unsigned int *)(CONFIG_SEGMENT + DSG_MAX_TH2_ADC_RECORD_EEPROM_Offset ))
#define DSG_MIN_TH2_ADC_RECORD_EEPROM                               *((unsigned int *)(CONFIG_SEGMENT + DSG_MIN_TH2_ADC_RECORD_EEPROM_Offset ))
#define RECORD_DATA_COUNT_EEPROM                                    *((unsigned int *)(CONFIG_SEGMENT + RECORD_DATA_COUNT_EEPROM_Offset ))
#define CHG_Cycle_Count_RECORD_EEPROM                               *((unsigned int *)(CONFIG_SEGMENT + CHG_Cycle_Count_RECORD_EEPROM_Offset ))
#define CHG_ADC_AccumulatingQ_RECORD_EEPROM                         *((unsigned long *)(CONFIG_SEGMENT + CHG_ADC_AccumulatingQ_RECORD_EEPROM_Offset ))
#define DSG_ADC_AccumulatingQ_RECORD_EEPROM                         *((unsigned long *)(CONFIG_SEGMENT + DSG_ADC_AccumulatingQ_RECORD_EEPROM_Offset ))
#define DSG_Cycle_Count_RECORD_EEPROM                               *((unsigned int *)(CONFIG_SEGMENT + DSG_Cycle_Count_RECORD_EEPROM_Offset ))
#define RESERVED_Recording_FOR_OFFSET1                              *((unsigned int *)(CONFIG_SEGMENT + RESERVED_Recording_FOR_OFFSET1_Offset ))
#define CHG_MAX_TH1_ADC_RECORD_EEPROM                               *((unsigned int *)(CONFIG_SEGMENT + CHG_MAX_TH1_ADC_RECORD_EEPROM_Offset ))
#define CHG_MIN_TH1_ADC_RECORD_EEPROM                               *((unsigned int *)(CONFIG_SEGMENT + CHG_MIN_TH1_ADC_RECORD_EEPROM_Offset ))
#define CHG_MAX_TH2_ADC_RECORD_EEPROM                               *((unsigned int *)(CONFIG_SEGMENT + CHG_MAX_TH2_ADC_RECORD_EEPROM_Offset ))
#define CHG_MIN_TH2_ADC_RECORD_EEPROM                               *((unsigned int *)(CONFIG_SEGMENT + CHG_MIN_TH2_ADC_RECORD_EEPROM_Offset ))
#define G_OVP_TIMES_RECORD_EEPROM                                   *((unsigned int *)(CONFIG_SEGMENT + G_OVP_TIMES_RECORD_EEPROM_Offset ))
#define G_UVP_TIMES_RECORD_EEPROM                                   *((unsigned int *)(CONFIG_SEGMENT + G_UVP_TIMES_RECORD_EEPROM_Offset ))
#define G_COCP_TIMES_RECORD_EEPROM                                  *((unsigned int *)(CONFIG_SEGMENT + G_COCP_TIMES_RECORD_EEPROM_Offset ))
#define G_DOCP_TIMES_RECORD_EEPROM                                  *((unsigned int *)(CONFIG_SEGMENT + G_DOCP_TIMES_RECORD_EEPROM_Offset ))
#define G_TH1_CHG_UTP_TIMES_RECORD_EEPROM                           *((unsigned int *)(CONFIG_SEGMENT + G_TH1_CHG_UTP_TIMES_RECORD_EEPROM_Offset ))
#define G_TH2_CHG_UTP_TIMES_RECORD_EEPROM                           *((unsigned int *)(CONFIG_SEGMENT + G_TH2_CHG_UTP_TIMES_RECORD_EEPROM_Offset ))
#define G_CHG_TH1_OTP_TIMES_RECORD_EEPROM                           *((unsigned int *)(CONFIG_SEGMENT + G_CHG_TH1_OTP_TIMES_RECORD_EEPROM_Offset ))
#define G_CHG_TH2_OTP_TIMES_RECORD_EEPROM                           *((unsigned int *)(CONFIG_SEGMENT + G_CHG_TH2_OTP_TIMES_RECORD_EEPROM_Offset ))
#define RECORD_2nd_DATA_COUNT_EEPROM                                *((unsigned int *)(CONFIG_SEGMENT + RECORD_2nd_DATA_COUNT_EEPROM_Offset ))
#define RESERVED_Recording_FOR_OFFSET3                              *((unsigned int *)(CONFIG_SEGMENT + RESERVED_Recording_FOR_OFFSET3_Offset ))
#define SystemSetting_Info_Byte1                                    *((unsigned char *)(CONFIG_SEGMENT + SystemSetting_Info_Byte1_Offset ))
#define SystemSetting_Info_Byte2                                    *((unsigned char *)(CONFIG_SEGMENT + SystemSetting_Info_Byte2_Offset ))
#define System_Control_Bit_EEPROM                                   *((unsigned char *)(CONFIG_SEGMENT + System_Control_Bit_EEPROM_Offset ))
#define SystemSetting_Info_Byte3                                    *((unsigned char *)(CONFIG_SEGMENT + SystemSetting_Info_Byte3_Offset ))
#define VERSION                                                     *((unsigned char *)(CONFIG_SEGMENT + VERSION_Offset ))
#define MINOR_VERSION                                               *((unsigned char *)(CONFIG_SEGMENT + MINOR_VERSION_Offset ))
#define EEPROM_VERSION                                              *((unsigned char *)(CONFIG_SEGMENT + EEPROM_VERSION_Offset ))
#define RESERVED_VERSION                                            *((unsigned char *)(CONFIG_SEGMENT + RESERVED_VERSION_Offset ))
#define NUMBER_OF_PARALLEL_CELLS                                    *((unsigned char *)(CONFIG_SEGMENT + NUMBER_OF_PARALLEL_CELLS_Offset ))
#define NUMBER_OF_SERIES_CELLS                                      *((unsigned char *)(CONFIG_SEGMENT + NUMBER_OF_SERIES_CELLS_Offset ))
#define MANUFACTURE_DATE                                            *((unsigned int *)(CONFIG_SEGMENT + MANUFACTURE_DATE_Offset ))
#define SERIAL_NUMBER                                               *((unsigned int *)(CONFIG_SEGMENT + SERIAL_NUMBER_Offset ))
#define CELL_TYPE_LENGTH                                            *((unsigned char *)(CONFIG_SEGMENT + CELL_TYPE_LENGTH_Offset ))
#define CELL_TYPE                                                   *((unsigned char *)(CONFIG_SEGMENT + CELL_TYPE_Offset ))
#define MANUFACTURE_NAME_LENGTH                                     *((unsigned char *)(CONFIG_SEGMENT + MANUFACTURE_NAME_LENGTH_Offset ))
#define MANUFACTURE_NAME                                            *((unsigned char *)(CONFIG_SEGMENT + MANUFACTURE_NAME_Offset ))
#define ADC_CURRENT_DETECT_FOR_DSG_STATUS                           *((unsigned int *)(CONFIG_SEGMENT + ADC_CURRENT_DETECT_FOR_DSG_STATUS_Offset ))
#define ADC_CURRENT_DETECT_FOR_CHG_STATUS                           *((unsigned int *)(CONFIG_SEGMENT + ADC_CURRENT_DETECT_FOR_CHG_STATUS_Offset ))
#define ADC_DOC_PROTECTION                                          *((unsigned int *)(CONFIG_SEGMENT + ADC_DOC_PROTECTION_Offset ))
#define ADC_COC_PROTECTION                                          *((unsigned int *)(CONFIG_SEGMENT + ADC_COC_PROTECTION_Offset ))
#define ADC_DSG_HIGH_CURRENT_DETECT                                 *((unsigned int *)(CONFIG_SEGMENT + ADC_DSG_HIGH_CURRENT_DETECT_Offset ))
#define ADC_CHG_CHARGER_TAPE_CURRENT                                *((unsigned int *)(CONFIG_SEGMENT + ADC_CHG_CHARGER_TAPE_CURRENT_Offset ))
#define ADC_AccQ_FOR_CHG_TH                                         *((unsigned long *)(CONFIG_SEGMENT + ADC_AccQ_FOR_CHG_TH_Offset ))
#define Cycle_Count_FOR_CHG_1st_TH                                  *((unsigned int *)(CONFIG_SEGMENT + Cycle_Count_FOR_CHG_1st_TH_Offset ))
#define Cycle_Count_FOR_CHG_2nd_TH                                  *((unsigned int *)(CONFIG_SEGMENT + Cycle_Count_FOR_CHG_2nd_TH_Offset ))
#define ADC_BATTERY_OV_PROTECTION                                   *((unsigned int *)(CONFIG_SEGMENT + ADC_BATTERY_OV_PROTECTION_Offset ))
#define ADC_BATTERY_OV_RELEASE                                      *((unsigned int *)(CONFIG_SEGMENT + ADC_BATTERY_OV_RELEASE_Offset ))
#define ADC_BATTERY_UV_PROTECTION                                   *((unsigned int *)(CONFIG_SEGMENT + ADC_BATTERY_UV_PROTECTION_Offset ))
#define ADC_BATTERY_UV_RELEASE                                      *((unsigned int *)(CONFIG_SEGMENT + ADC_BATTERY_UV_RELEASE_Offset ))
#define ADC_DSG_OT_HIGH_PROTECTION                                  *((unsigned int *)(CONFIG_SEGMENT + ADC_DSG_OT_HIGH_PROTECTION_Offset ))
#define ADC_DSG_OT_HIGH_RELEASE                                     *((unsigned int *)(CONFIG_SEGMENT + ADC_DSG_OT_HIGH_RELEASE_Offset ))
#define ADC_DSG_OT_LOW_PROTECTION                                   *((unsigned int *)(CONFIG_SEGMENT + ADC_DSG_OT_LOW_PROTECTION_Offset ))
#define ADC_DSG_OT_LOW_RELEASE                                      *((unsigned int *)(CONFIG_SEGMENT + ADC_DSG_OT_LOW_RELEASE_Offset ))
#define ADC_CHG_OT_PROTECTION                                       *((unsigned int *)(CONFIG_SEGMENT + ADC_CHG_OT_PROTECTION_Offset ))
#define ADC_CHG_OT_RELEASE                                          *((unsigned int *)(CONFIG_SEGMENT + ADC_CHG_OT_RELEASE_Offset ))
#define ADC_UT_PROTECTION                                           *((unsigned int *)(CONFIG_SEGMENT + ADC_UT_PROTECTION_Offset ))
#define ADC_UT_RELEASE                                              *((unsigned int *)(CONFIG_SEGMENT + ADC_UT_RELEASE_Offset ))
#define ADC_INITIAL_CHARGING_TEMP_RANGE_HI                          *((unsigned int *)(CONFIG_SEGMENT + ADC_INITIAL_CHARGING_TEMP_RANGE_HI_Offset ))
#define ADC_INITIAL_CHARGING_TEMP_RANGE_LO                          *((unsigned int *)(CONFIG_SEGMENT + ADC_INITIAL_CHARGING_TEMP_RANGE_LO_Offset ))
#define ADC_LOW_TEMP_SOC_CHARGING_RANGE_HI                          *((unsigned int *)(CONFIG_SEGMENT + ADC_LOW_TEMP_SOC_CHARGING_RANGE_HI_Offset ))
#define ADC_LOW_TEMP_SOC_CHARGING_RANGE_LO                          *((unsigned int *)(CONFIG_SEGMENT + ADC_LOW_TEMP_SOC_CHARGING_RANGE_LO_Offset ))
#define ADC_AccQ_FOR_DSG_TH                                         *((unsigned long *)(CONFIG_SEGMENT + ADC_AccQ_FOR_DSG_TH_Offset ))
#define DSG_CAPACITY_DISPLAY_TH_1                                   *((unsigned int *)(CONFIG_SEGMENT + DSG_CAPACITY_DISPLAY_TH_1_Offset ))
#define DSG_CAPACITY_DISPLAY_TH_2                                   *((unsigned int *)(CONFIG_SEGMENT + DSG_CAPACITY_DISPLAY_TH_2_Offset ))
#define DSG_CAPACITY_DISPLAY_TH_3                                   *((unsigned int *)(CONFIG_SEGMENT + DSG_CAPACITY_DISPLAY_TH_3_Offset ))
#define DSG_CAPACITY_DISPLAY_TH_4                                   *((unsigned int *)(CONFIG_SEGMENT + DSG_CAPACITY_DISPLAY_TH_4_Offset ))
#define Reserved_DSG_CAPACITY_DISPLAY_TH_5                          *((unsigned int *)(CONFIG_SEGMENT + Reserved_DSG_CAPACITY_DISPLAY_TH_5_Offset ))
#define CHG_CAPACITY_DISPLAY_TH_1                                   *((unsigned int *)(CONFIG_SEGMENT + CHG_CAPACITY_DISPLAY_TH_1_Offset ))
#define CHG_CAPACITY_DISPLAY_TH_2                                   *((unsigned int *)(CONFIG_SEGMENT + CHG_CAPACITY_DISPLAY_TH_2_Offset ))
#define CHG_CAPACITY_DISPLAY_TH_3                                   *((unsigned int *)(CONFIG_SEGMENT + CHG_CAPACITY_DISPLAY_TH_3_Offset ))
#define Reserved_CHG_CAPACITY_DISPLAY_TH_4                          *((unsigned int *)(CONFIG_SEGMENT + Reserved_CHG_CAPACITY_DISPLAY_TH_4_Offset ))
#define _ADC_LOOKUP_DSG_TEMP_1_TH_                                  *((unsigned int *)(CONFIG_SEGMENT + _ADC_LOOKUP_DSG_TEMP_1_TH__Offset ))
#define _ADC_LOOKUP_DSG_TEMP_2_TH_                                  *((unsigned int *)(CONFIG_SEGMENT + _ADC_LOOKUP_DSG_TEMP_2_TH__Offset ))
#define _ADC_LOOKUP_DSG_TEMP_3_TH_                                  *((unsigned int *)(CONFIG_SEGMENT + _ADC_LOOKUP_DSG_TEMP_3_TH__Offset ))
#define _ADC_LOOKUP_CHG_TEMP_1_TH_                                  *((unsigned int *)(CONFIG_SEGMENT + _ADC_LOOKUP_CHG_TEMP_1_TH__Offset ))
#define _ADC_LOOKUP_CHG_TEMP_2_TH_                                  *((unsigned int *)(CONFIG_SEGMENT + _ADC_LOOKUP_CHG_TEMP_2_TH__Offset ))
#define _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH1_                      *((unsigned int *)(CONFIG_SEGMENT + _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH1__Offset ))
#define _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH2_                      *((unsigned int *)(CONFIG_SEGMENT + _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH2__Offset ))
#define _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH3_                      *((unsigned int *)(CONFIG_SEGMENT + _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH3__Offset ))
#define _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH4_                      *((unsigned int *)(CONFIG_SEGMENT + _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH4__Offset ))
#define _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH5_                      *((unsigned int *)(CONFIG_SEGMENT + _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH5__Offset ))
#define _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH6_                      *((unsigned int *)(CONFIG_SEGMENT + _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH6__Offset ))
#define AUTO_ENTRY_SLEEPING_DELAY_MINUTES                           *((unsigned int *)(CONFIG_SEGMENT + AUTO_ENTRY_SLEEPING_DELAY_MINUTES_Offset ))
#define CAPACITY_DIFFERENCE_VALUES                                  *((unsigned int *)(CONFIG_SEGMENT + CAPACITY_DIFFERENCE_VALUES_Offset ))
#define PROJECT_NAME_MAX_LENGTH                                     *((unsigned char *)(CONFIG_SEGMENT + PROJECT_NAME_MAX_LENGTH_Offset ))
#define PROJECT_NAME                                                *((unsigned char *)(CONFIG_SEGMENT + PROJECT_NAME_Offset ))
#define MCU_UID_MAX_LENGTH                                          *((unsigned char *)(CONFIG_SEGMENT + MCU_UID_MAX_LENGTH_Offset ))
#define MCU_UID                                                     *((unsigned char *)(CONFIG_SEGMENT + MCU_UID_Offset ))
#define BAR_CODE_REAL_STORE_LENGTH                                  *((unsigned char *)(CONFIG_SEGMENT + BAR_CODE_REAL_STORE_LENGTH_Offset ))
#define BAR_CODE_MAX_LENGTH                                         *((unsigned char *)(CONFIG_SEGMENT + BAR_CODE_MAX_LENGTH_Offset ))
#define BAR_CODE                                                    *((unsigned char *)(CONFIG_SEGMENT + BAR_CODE_Offset ))
#define DESIGN_CAPACITY_mAH                                         *((unsigned int *)(CONFIG_SEGMENT + DESIGN_CAPACITY_mAH_Offset ))
#define Last_Record_FCC_mAh_RECORD_EEPROM                           *((unsigned int *)(CONFIG_SEGMENT + Last_Record_FCC_mAh_RECORD_EEPROM_Offset ))
#define REAL_FCC_UPDATE_TIMES_RECORD_EEPROM                         *((unsigned int *)(CONFIG_SEGMENT + REAL_FCC_UPDATE_TIMES_RECORD_EEPROM_Offset ))
#define REAL_FCC_mAH_RECORD_EEPROM                                  *((unsigned int *)(CONFIG_SEGMENT + REAL_FCC_mAH_RECORD_EEPROM_Offset ))
#define STATIC_OVER_VOLTAGE_HOURS_TIMES_RECORD_EEPROM               *((unsigned int *)(CONFIG_SEGMENT + STATIC_OVER_VOLTAGE_HOURS_TIMES_RECORD_EEPROM_Offset ))
#define CHG_OVER_VOLTAGE_MINUTES_TIMES_RECORD_EEPROM                *((unsigned int *)(CONFIG_SEGMENT + CHG_OVER_VOLTAGE_MINUTES_TIMES_RECORD_EEPROM_Offset ))
#define OVER_LOADING_MINUTES_TIMES_RECORD_EEPROM                    *((unsigned int *)(CONFIG_SEGMENT + OVER_LOADING_MINUTES_TIMES_RECORD_EEPROM_Offset ))
#define FASTER_CHARGING_MINUTES_TIMES_RECORD_EEPROM                 *((unsigned int *)(CONFIG_SEGMENT + FASTER_CHARGING_MINUTES_TIMES_RECORD_EEPROM_Offset ))
#define CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_RECORD_EEPROM           *((unsigned int *)(CONFIG_SEGMENT + CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_RECORD_EEPROM_Offset ))
#define CHARGING_IN_LOW_TEMP_MINUTES_TIMES_RECORD_EEPROM            *((unsigned int *)(CONFIG_SEGMENT + CHARGING_IN_LOW_TEMP_MINUTES_TIMES_RECORD_EEPROM_Offset ))
#define STORE_IN_LOW_TEMP1_HOURS_TIMES_RECORD_EEPROM                *((unsigned int *)(CONFIG_SEGMENT + STORE_IN_LOW_TEMP1_HOURS_TIMES_RECORD_EEPROM_Offset ))
#define STORE_IN_LOW_TEMP2_HOURS_TIMES_RECORD_EEPROM                *((unsigned int *)(CONFIG_SEGMENT + STORE_IN_LOW_TEMP2_HOURS_TIMES_RECORD_EEPROM_Offset ))
#define STORE_IN_LOW_TEMP3_HOURS_TIMES_RECORD_EEPROM                *((unsigned int *)(CONFIG_SEGMENT + STORE_IN_LOW_TEMP3_HOURS_TIMES_RECORD_EEPROM_Offset ))
#define STORE_IN_LOW_TEMP4_HOURS_TIMES_RECORD_EEPROM                *((unsigned int *)(CONFIG_SEGMENT + STORE_IN_LOW_TEMP4_HOURS_TIMES_RECORD_EEPROM_Offset ))
#define G_DSG_TH1_LOW_CURRENT_OTP_TIMES_RECORD_EEPROM               *((unsigned int *)(CONFIG_SEGMENT + G_DSG_TH1_LOW_CURRENT_OTP_TIMES_RECORD_EEPROM_Offset ))
#define G_DSG_TH1_HIGH_CURRENT_OTP_TIMES_RECORD_EEPROM              *((unsigned int *)(CONFIG_SEGMENT + G_DSG_TH1_HIGH_CURRENT_OTP_TIMES_RECORD_EEPROM_Offset ))
#define G_DSG_TH2_LOW_CURRENT_OTP_TIMES_RECORD_EEPROM               *((unsigned int *)(CONFIG_SEGMENT + G_DSG_TH2_LOW_CURRENT_OTP_TIMES_RECORD_EEPROM_Offset ))
#define G_DSG_TH2_HIGH_CURRENT_OTP_TIMES_RECORD_EEPROM              *((unsigned int *)(CONFIG_SEGMENT + G_DSG_TH2_HIGH_CURRENT_OTP_TIMES_RECORD_EEPROM_Offset ))
#define STORE_IN_HIGH_TEMP1_MINUTES_TIMES_RECORD_EEPROM             *((unsigned int *)(CONFIG_SEGMENT + STORE_IN_HIGH_TEMP1_MINUTES_TIMES_RECORD_EEPROM_Offset ))
#define STORE_IN_HIGH_TEMP2_MINUTES_TIMES_RECORD_EEPROM             *((unsigned int *)(CONFIG_SEGMENT + STORE_IN_HIGH_TEMP2_MINUTES_TIMES_RECORD_EEPROM_Offset ))
#define STORE_IN_HIGH_TEMP3_MINUTES_TIMES_RECORD_EEPROM             *((unsigned int *)(CONFIG_SEGMENT + STORE_IN_HIGH_TEMP3_MINUTES_TIMES_RECORD_EEPROM_Offset ))
#define STORE_IN_HIGH_TEMP4_MINUTES_TIMES_RECORD_EEPROM             *((unsigned int *)(CONFIG_SEGMENT + STORE_IN_HIGH_TEMP4_MINUTES_TIMES_RECORD_EEPROM_Offset ))
#define STORE_IN_HIGH_TEMP5_MINUTES_TIMES_RECORD_EEPROM             *((unsigned int *)(CONFIG_SEGMENT + STORE_IN_HIGH_TEMP5_MINUTES_TIMES_RECORD_EEPROM_Offset ))
#define RECORD_3rd_TRACKING_DATA_COUNT_EEPROM                       *((unsigned int *)(CONFIG_SEGMENT + RECORD_3rd_TRACKING_DATA_COUNT_EEPROM_Offset ))
#define LOW_TEMP1_IN_DSG_ACT_RECORD_MINUTES_EEPROM                  *((unsigned int *)(CONFIG_SEGMENT + LOW_TEMP1_IN_DSG_ACT_RECORD_MINUTES_EEPROM_Offset ))
#define LOW_TEMP2_IN_DSG_ACT_RECORD_MINUTES_EEPROM                  *((unsigned int *)(CONFIG_SEGMENT + LOW_TEMP2_IN_DSG_ACT_RECORD_MINUTES_EEPROM_Offset ))
#define LOW_TEMP3_IN_DSG_ACT_RECORD_MINUTES_EEPROM                  *((unsigned int *)(CONFIG_SEGMENT + LOW_TEMP3_IN_DSG_ACT_RECORD_MINUTES_EEPROM_Offset ))
#define RECORDING_System_Activated_Times_For_TotalHours             *((signed int *)(CONFIG_SEGMENT + RECORDING_System_Activated_Times_For_TotalHours_Offset ))
#define RECORDING_Reserved_Data                                     *((unsigned char *)(CONFIG_SEGMENT + RECORDING_Reserved_Data_Offset ))
#define RECORDING_Reserved_Data1                                    *((unsigned char *)(CONFIG_SEGMENT + RECORDING_Reserved_Data1_Offset ))
#define RECORDING_Reserved_Data2                                    *((unsigned char *)(CONFIG_SEGMENT + RECORDING_Reserved_Data2_Offset ))
#define RECORDING_System_Activated_Times_Minutes_For_1_Hours        *((unsigned char *)(CONFIG_SEGMENT + RECORDING_System_Activated_Times_Minutes_For_1_Hours_Offset ))
#define ShakeSwitchDetect_RangeTime_By_AutoWakeUp_TimeCycles        *((unsigned char *)(CONFIG_SEGMENT + ShakeSwitchDetect_RangeTime_By_AutoWakeUp_TimeCycles_Offset ))
#define ShakeSwitchTriggerTimes_For_WakeUp                          *((unsigned char *)(CONFIG_SEGMENT + ShakeSwitchTriggerTimes_For_WakeUp_Offset ))
#define GSM_SetInterLockTimes_BeforeBMSSendData                     *((unsigned char *)(CONFIG_SEGMENT + GSM_SetInterLockTimes_BeforeBMSSendData_Offset ))
#define GSM_SetDelayTimes_ForBMSCheckMosStatus                      *((unsigned char *)(CONFIG_SEGMENT + GSM_SetDelayTimes_ForBMSCheckMosStatus_Offset ))
#define GSM_System_Enter_SleepingMode_DelayTime_For_STATIC          *((unsigned int *)(CONFIG_SEGMENT + GSM_System_Enter_SleepingMode_DelayTime_For_STATIC_Offset ))
#define GSM_SendDataFor_EachDelayTimes_For_DSG                      *((unsigned int *)(CONFIG_SEGMENT + GSM_SendDataFor_EachDelayTimes_For_DSG_Offset ))
#define GSM_SendDataFor_EachDelayTimes_For_CHG                      *((unsigned int *)(CONFIG_SEGMENT + GSM_SendDataFor_EachDelayTimes_For_CHG_Offset ))
#define GSM_SendData_For_StaticSleeping_By_AutoWakeUp_TimeCycles    *((unsigned int *)(CONFIG_SEGMENT + GSM_SendData_For_StaticSleeping_By_AutoWakeUp_TimeCycles_Offset ))
#define GSM_System_WakeUp_ReadyTimes_In_SleepingMode                *((unsigned int *)(CONFIG_SEGMENT + GSM_System_WakeUp_ReadyTimes_In_SleepingMode_Offset ))
#define SleepMode_Autowakeup_Intervaltimes_ms                       *((unsigned int *)(CONFIG_SEGMENT + SleepMode_Autowakeup_Intervaltimes_ms_Offset ))
#define SleepMode_Autowakeup_Intervaltimes_sec                      *((float *)(CONFIG_SEGMENT + SleepMode_Autowakeup_Intervaltimes_sec_Offset ))
#define SleepMode_Autowakeup_Intervaltimes_min                      *((float *)(CONFIG_SEGMENT + SleepMode_Autowakeup_Intervaltimes_min_Offset ))
#define LastTotalTimes_Without_Charging_Minutes_RECORD_EEPROM       *((unsigned long *)(CONFIG_SEGMENT + LastTotalTimes_Without_Charging_Minutes_RECORD_EEPROM_Offset ))
#define MaxTotalTimes_Without_Charging_Minutes_RECORD_EEPROM        *((unsigned long *)(CONFIG_SEGMENT + MaxTotalTimes_Without_Charging_Minutes_RECORD_EEPROM_Offset ))
#define LastTotalTimes_Without_DisCharging_Minutes_RECORD_EEPROM    *((unsigned long *)(CONFIG_SEGMENT + LastTotalTimes_Without_DisCharging_Minutes_RECORD_EEPROM_Offset ))
#define MaxTotalTimes_Without_DisCharging_Minutes_RECORD_EEPROM     *((unsigned long *)(CONFIG_SEGMENT + MaxTotalTimes_Without_DisCharging_Minutes_RECORD_EEPROM_Offset ))
#define Last_ChargingTimes_Minutes_RECORD_EEPROM                    *((unsigned int *)(CONFIG_SEGMENT + Last_ChargingTimes_Minutes_RECORD_EEPROM_Offset ))
#define Max_ChargingTimes_Minutes_RECORD_EEPROM                     *((unsigned int *)(CONFIG_SEGMENT + Max_ChargingTimes_Minutes_RECORD_EEPROM_Offset ))
#define EEPROM_END_DATA_POSITION                                    *((unsigned char *)(CONFIG_SEGMENT + EEPROM_END_DATA_POSITION_Offset ))
#define EEPROM_PN_INFO_START_DATA_POSITION                          *((unsigned char *)(CONFIG_SEGMENT + EEPROM_PN_INFO_START_DATA_POSITION_Offset ))
#define PN_DAK_NAME_MAX_LENGTH                                      *((unsigned char *)(CONFIG_SEGMENT + PN_DAK_NAME_MAX_LENGTH_Offset ))
#define PN_DAK_NAME                                                 *((unsigned char *)(CONFIG_SEGMENT + PN_DAK_NAME_Offset ))
#define PN_85K_NAME_MAX_LENGTH                                      *((unsigned char *)(CONFIG_SEGMENT + PN_85K_NAME_MAX_LENGTH_Offset ))
#define PN_85K_NAME                                                 *((unsigned char *)(CONFIG_SEGMENT + PN_85K_NAME_Offset ))
#define Cell_PN_NAME_MAX_LENGTH                                     *((unsigned char *)(CONFIG_SEGMENT + Cell_PN_NAME_MAX_LENGTH_Offset ))
#define Cell_PN_NAME                                                *((unsigned char *)(CONFIG_SEGMENT + Cell_PN_NAME_Offset ))
#define EEPROM_PN_INFO_END_DATA_POSITION                            *((unsigned char *)(CONFIG_SEGMENT + EEPROM_PN_INFO_END_DATA_POSITION_Offset ))
// 
/////////////////////////////////////////////////////////////////////////// 
// 
// Define Var Type
// 
// ========================================
//  #define  _ee_address_CONFIG_SEGMENT                                                                           0x1000 //EEPROM Start Address, must use Hexadecimal
//  #define  _ee_float_CHG_mA_To_ADC_Factor                                                                       0.372363636f // 4 bytes;
//  #define  _ee_float_DSG_mA_To_ADC_Factor                                                                       0.138790083f // 4 bytes;
//  #define  _ee_float_VBAT_mV_To_ADC_Factor                                                                      0.065821855f // 4 bytes;
//  #define  _ee_float_Thermistor_mV_To_ADC_Factor                                                                1.241212f // 4 bytes; = 1/ADC_Step
//  #define  _ee_char_DSG_OP_ADC_OFFSET                                                                           0 //1byte ; 實際值-理論值 (signed char) //used
//  #define  _ee_char_CHG_OP_ADC_OFFSET                                                                           0 //1byte ; 實際值-理論值 (signed char) //used
//  #define  _ee_char_VBAT_ADC_OFFSET                                                                             0 //1byte ; 實際值-理論值 (signed char) //used
//  #define  _ee_char_NTC1_ADC_OFFSET                                                                             0 //1byte ; 實際值-理論值 Thermistor (signed char) //used
//  #define  _ee_char_NTC2_ADC_OFFSET                                                                             0 //1byte ; 實際值-理論值 Thermistor (signed char) //used
//  #define  _ee_char_SOC_ADC_OFFSET                                                                              0 //1byte ; 實際值-理論值 (signed char)
//  #define  _ee_uint_R_Sense_10u_ohm                                                                             136 //2 bytes; 200 * 10u ohm = 2.00 m-ohm
//  #define  _ee_uchar_MCU_Major_Type_Code                                                                        0 //1 byte; MCU Supplier: 0=> ST, 1=> TI, 2=> Renesas
//  #define  _ee_uchar_MCU_Minor_Type_Code                                                                        0
//  #define  _ee_ulong_RESERVED_CAL_FOR_OFFSET2                                                                   0
//  #define  _ee_uint_RESERVED_CAL_FOR_OFFSET3                                                                    0
//  #define  _ee_uint_MAX_DSG_C_ADC_RECORD_EEPROM                                                                 0
//  #define  _ee_uint_MAX_CHG_C_ADC_RECORD_EEPROM                                                                 0
//  #define  _ee_uint_MAX_VBAT_ADC_RECORD_EEPROM                                                                  0
//  #define  _ee_uint_MIN_VBAT_ADC_RECORD_EEPROM                                                                  65535
//  #define  _ee_uint_MAX_VBAT_SocLo_ADC_RECORD_EEPROM                                                            0
//  #define  _ee_uint_MAX_VBAT_SocHi_ADC_RECORD_EEPROM                                                            0
//  #define  _ee_uint_DSG_MAX_TH1_ADC_RECORD_EEPROM                                                               0
//  #define  _ee_uint_DSG_MIN_TH1_ADC_RECORD_EEPROM                                                               65535
//  #define  _ee_uint_DSG_MAX_TH2_ADC_RECORD_EEPROM                                                               0
//  #define  _ee_uint_DSG_MIN_TH2_ADC_RECORD_EEPROM                                                               65535
//  #define  _ee_uint_RECORD_DATA_COUNT_EEPROM                                                                    0
//  #define  _ee_uint_CHG_Cycle_Count_RECORD_EEPROM                                                               0
//  #define  _ee_ulong_CHG_ADC_AccumulatingQ_RECORD_EEPROM                                                        0 //max = 4,294,967,295 = 0xffff ffff
//  #define  _ee_ulong_DSG_ADC_AccumulatingQ_RECORD_EEPROM                                                        0 //max = 4,294,967,295 = 0xffff ffff
//  #define  _ee_uint_DSG_Cycle_Count_RECORD_EEPROM                                                               0
//  #define  _ee_uint_RESERVED_Recording_FOR_OFFSET1                                                              0 //Reserved
//  #define  _ee_uint_CHG_MAX_TH1_ADC_RECORD_EEPROM                                                               0
//  #define  _ee_uint_CHG_MIN_TH1_ADC_RECORD_EEPROM                                                               65535
//  #define  _ee_uint_CHG_MAX_TH2_ADC_RECORD_EEPROM                                                               0
//  #define  _ee_uint_CHG_MIN_TH2_ADC_RECORD_EEPROM                                                               65535
//  #define  _ee_uint_G_OVP_TIMES_RECORD_EEPROM                                                                   0
//  #define  _ee_uint_G_UVP_TIMES_RECORD_EEPROM                                                                   0
//  #define  _ee_uint_G_COCP_TIMES_RECORD_EEPROM                                                                  0
//  #define  _ee_uint_G_DOCP_TIMES_RECORD_EEPROM                                                                  0
//  #define  _ee_uint_G_TH1_CHG_UTP_TIMES_RECORD_EEPROM                                                           0
//  #define  _ee_uint_G_TH2_CHG_UTP_TIMES_RECORD_EEPROM                                                           0
//  #define  _ee_uint_G_CHG_TH1_OTP_TIMES_RECORD_EEPROM                                                           0
//  #define  _ee_uint_G_CHG_TH2_OTP_TIMES_RECORD_EEPROM                                                           0
//  #define  _ee_uint_RECORD_2nd_DATA_COUNT_EEPROM                                                                0 //Reserved
//  #define  _ee_uint_RESERVED_Recording_FOR_OFFSET3                                                              0 //Reserved
//  #define  _ee_uchar_SystemSetting_Info_Byte1                                                                   0 //write by F/W
//  #define  _ee_uchar_SystemSetting_Info_Byte2                                                                   0 //write by F/W
//  #define  _ee_uchar_System_Control_Bit_EEPROM                                                                  12 // 1 byte
//  #define  _ee_uchar_SystemSetting_Info_Byte3                                                                   0 //write by F/W
//  #define  _ee_uchar_VERSION                                                                                    255//(don't change), has to be define at FW_Version_Define, 1 bytes//for main function addition and EEPROM Format changing
//  #define  _ee_uchar_MINOR_VERSION                                                                              255//(don't change), has to be define at FW_Version_Define, 1 bytes//only for minor functions changing
//  #define  _ee_uchar_EEPROM_VERSION                                                                             26 // 1 bytes //only for EEPROM values changing
//  #define  _ee_uchar_RESERVED_VERSION                                                                           255//(don't change),has to be define at FW_Version_Define, 1 bytes//0x00: Protuction, 0x01: Samples
//  #define  _ee_uchar_NUMBER_OF_PARALLEL_CELLS                                                                   4 // 1 bytes
//  #define  _ee_uchar_NUMBER_OF_SERIES_CELLS                                                                     7 // 1 bytes
//  #define  _ee_uint_MANUFACTURE_DATE                                                                            17604 //(MANUFACTURE_DATE_YEAR - 1980) * 512 + MANUFACTURE_DATE_MONTH * 32 + MANUFACTURE_DATE_DAY // 2 bytes
//  #define  _ee_uint_SERIAL_NUMBER                                                                               65530 // 2 bytes
//  #define  _ee_str_len_CELL_TYPE_LENGTH                                                                         8
//  #define  _ee_str_CELL_TYPE                                                                                    "SDI 26FM"
//  #define  _ee_str_len_MANUFACTURE_NAME_LENGTH                                                                  8
//  #define  _ee_str_MANUFACTURE_NAME                                                                             "Dynapack"
//  #define  _ee_uint_ADC_CURRENT_DETECT_FOR_DSG_STATUS                                                           17 //120mA; unit: mA; 2bytes; if current > the define, in discharging status
//  #define  _ee_uint_ADC_CURRENT_DETECT_FOR_CHG_STATUS                                                           45 //120mA; unit: mA; 2bytes; if current > the define, in charging status
//  #define  _ee_uint_ADC_DOC_PROTECTION                                                                          6940 // 50A; unit: 1mA; (OVER) discharging current protection is positive
//  #define  _ee_uint_ADC_COC_PROTECTION                                                                          1676 // 4.5A; unit: 1mA; charging current protection
//  #define  _ee_uint_ADC_DSG_HIGH_CURRENT_DETECT                                                                 1110 // 8000mA; 2bytes; for switch High/Low OT Protection
//  #define  _ee_uint_ADC_CHG_CHARGER_TAPE_CURRENT                                                                559 // 1500mA; 2bytes;
//  #define  _ee_ulong_ADC_AccQ_FOR_CHG_TH                                                                        22305600 //one Cycle Count Threshold; //long int => max = 4,294,967,295 = 0xffff ffff ffff ffff
//  #define  _ee_uint_Cycle_Count_FOR_CHG_1st_TH                                                                  150 // 150 times; unit: times; 2byte; Cycle Count times for charger to set CHG voltage
//  #define  _ee_uint_Cycle_Count_FOR_CHG_2nd_TH                                                                  500 // 500 times; unit: times; 2byte; Cycle Count times for charger to set CHG voltage
//  #define  _ee_uint_ADC_BATTERY_OV_PROTECTION                                                                   1961 // 29.8V(cell:4.24); unit: 1mV; 2bytes; 2nd level BATTERY OV PROTECTION
//  #define  _ee_uint_ADC_BATTERY_OV_RELEASE                                                                      1909 // 29V(cell:4.15); unit: 1mV; 2bytes; 2nd level BATTERY OV RELEASE
//  #define  _ee_uint_ADC_BATTERY_UV_PROTECTION                                                                   1284 // 19.5V(cell:2.8); unit: 1mV; 2bytes; 2nd level BATTERY UV PROTECTION
//  #define  _ee_uint_ADC_BATTERY_UV_RELEASE                                                                      1544 // 23.45V;For Delay reach Vol while UVP ; (org) 22.4V(cell:3.2); unit: 1mV; 2bytes; 2nd level BATTERY UV RELEASE
//  #define  _ee_uint_ADC_DSG_OT_HIGH_PROTECTION                                                                  666 //unit: 75 Celcius; mV;Over temperature protection for discharging(High current)
//  #define  _ee_uint_ADC_DSG_OT_HIGH_RELEASE                                                                     846 //unit: 65 Celcius; mV; Over temperature release for discharging(High current)
//  #define  _ee_uint_ADC_DSG_OT_LOW_PROTECTION                                                                   750 //unit: 70 Celcius; mV; Over temperature protection for discharging(Low current)
//  #define  _ee_uint_ADC_DSG_OT_LOW_RELEASE                                                                      846 //unit: 65 Celcius; mV; Over temperature release for discharging(Low current)
//  #define  _ee_uint_ADC_CHG_OT_PROTECTION                                                                       909 //unit: 62 Celcius; mV; Over temperature protection for charging()
//  #define  _ee_uint_ADC_CHG_OT_RELEASE                                                                          1000 //unit: 58 Celcius; mV; Over temperature release for charging()
//  #define  _ee_uint_ADC_UT_PROTECTION                                                                           3155 //unit: -5 Celcius; mV; Under temperature protection()
//  #define  _ee_uint_ADC_UT_RELEASE                                                                              2992 //unit: 0 Celcius; mV; Under temperature release()
//  #define  _ee_uint_ADC_INITIAL_CHARGING_TEMP_RANGE_HI                                                          909 //unit: 62 Celcius; mV; initial start charging High temperature range
//  #define  _ee_uint_ADC_INITIAL_CHARGING_TEMP_RANGE_LO                                                          3155 //unit: -5 Celcius; mV; initial start charging Low temperature range
//  #define  _ee_uint_ADC_LOW_TEMP_SOC_CHARGING_RANGE_HI                                                          2628 //unit: 10 Celcius; mV; At Low temperature, High temperature range for setting SOC signal High for charging
//  #define  _ee_uint_ADC_LOW_TEMP_SOC_CHARGING_RANGE_LO                                                          3155 //unit: -5 Celcius; mV; At Low temperature, Low temperature range for setting SOC signal High for charging
//  #define  _ee_ulong_ADC_AccQ_FOR_DSG_TH                                                                        8316000 //one Cycle Count Threshold; //long int => max = 4,294,967,295 = 0xffff ffff ffff ffff
//  #define  _ee_uint_DSG_CAPACITY_DISPLAY_TH_1                                                                   16
//  #define  _ee_uint_DSG_CAPACITY_DISPLAY_TH_2                                                                   37
//  #define  _ee_uint_DSG_CAPACITY_DISPLAY_TH_3                                                                   58
//  #define  _ee_uint_DSG_CAPACITY_DISPLAY_TH_4                                                                   79
//  #define  _ee_uint_Reserved_DSG_CAPACITY_DISPLAY_TH_5                                                          0 //reserved for 5 Leds
//  #define  _ee_uint_CHG_CAPACITY_DISPLAY_TH_1                                                                   19
//  #define  _ee_uint_CHG_CAPACITY_DISPLAY_TH_2                                                                   35
//  #define  _ee_uint_CHG_CAPACITY_DISPLAY_TH_3                                                                   60
//  #define  _ee_uint_Reserved_CHG_CAPACITY_DISPLAY_TH_4                                                          0 //reserved for 5 Leds
//  #define  _ee_uint__ADC_LOOKUP_DSG_TEMP_1_TH_                                                                  2992 // 0 Celcius;
//  #define  _ee_uint__ADC_LOOKUP_DSG_TEMP_2_TH_                                                                  2628 //10 Celcius;
//  #define  _ee_uint__ADC_LOOKUP_DSG_TEMP_3_TH_                                                                  2241 //20 Celcius;
//  #define  _ee_uint__ADC_LOOKUP_CHG_TEMP_1_TH_                                                                  2628 //10 Celcius;
//  #define  _ee_uint__ADC_LOOKUP_CHG_TEMP_2_TH_                                                                  2241 //20 Celcius;
//  #define  _ee_uint__ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH1_                                                      736 // <= 5300mA; 2bytes;
//  #define  _ee_uint__ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH2_                                                      930 // <= 6700mA; 2bytes;
//  #define  _ee_uint__ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH3_                                                      1291 // <= 9300mA; 2bytes;
//  #define  _ee_uint__ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH4_                                                      1665 // <= 12000mA; 2bytes;
//  #define  _ee_uint__ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH5_                                                      2082 // <= 15000mA; 2bytes;
//  #define  _ee_uint__ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH6_                                                      2415 // <= 17400mA; 2bytes;
//  #define  _ee_uint_AUTO_ENTRY_SLEEPING_DELAY_MINUTES                                                           1440 //1440 minutes = 24 hours
//  #define  _ee_uint_CAPACITY_DIFFERENCE_VALUES                                                                  1 // % ; 2bytes;
//  #define  _ee_str_len_PROJECT_NAME_MAX_LENGTH                                                                  24
//  #define  _ee_str_PROJECT_NAME                                                                                 "Ares_TB290_24100_D"
//  #define  _ee_str_len_MCU_UID_MAX_LENGTH                                                                       12
//  #define  _ee_str_MCU_UID                                                                                      "-----"
//  #define  _ee_uchar_BAR_CODE_REAL_STORE_LENGTH                                                                 24
//  #define  _ee_str_len_BAR_CODE_MAX_LENGTH                                                                      24
//  #define  _ee_str_BAR_CODE                                                                                     "-----"
//  #define  _ee_uint_DESIGN_CAPACITY_mAH                                                                         10000 //mAH,
//  #define  _ee_uint_Last_Record_FCC_mAh_RECORD_EEPROM                                                           10000 //mAH,
//  #define  _ee_uint_REAL_FCC_UPDATE_TIMES_RECORD_EEPROM                                                         0
//  #define  _ee_uint_REAL_FCC_mAH_RECORD_EEPROM                                                                  10000 //mAH,
//  #define  _ee_uint_STATIC_OVER_VOLTAGE_HOURS_TIMES_RECORD_EEPROM                                               0 // record over voltage hours in static
//  #define  _ee_uint_CHG_OVER_VOLTAGE_MINUTES_TIMES_RECORD_EEPROM                                                0 // record over voltage MINUTES in chg
//  #define  _ee_uint_OVER_LOADING_MINUTES_TIMES_RECORD_EEPROM                                                    0 // record over loading minutes
//  #define  _ee_uint_FASTER_CHARGING_MINUTES_TIMES_RECORD_EEPROM                                                 0 // record over voltage hours in chg
//  #define  _ee_uint_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_RECORD_EEPROM                                           0 // record charging in high temp MINUTES
//  #define  _ee_uint_CHARGING_IN_LOW_TEMP_MINUTES_TIMES_RECORD_EEPROM                                            0 // record charging in low temp MINUTES
//  #define  _ee_uint_STORE_IN_LOW_TEMP1_HOURS_TIMES_RECORD_EEPROM                                                0 // record store in low temp 1 hours
//  #define  _ee_uint_STORE_IN_LOW_TEMP2_HOURS_TIMES_RECORD_EEPROM                                                0 // record store in low temp 2 hours
//  #define  _ee_uint_STORE_IN_LOW_TEMP3_HOURS_TIMES_RECORD_EEPROM                                                0 // record store in low temp 3 hours
//  #define  _ee_uint_STORE_IN_LOW_TEMP4_HOURS_TIMES_RECORD_EEPROM                                                0 // record store in low temp 4 hours
//  #define  _ee_uint_G_DSG_TH1_LOW_CURRENT_OTP_TIMES_RECORD_EEPROM                                               0
//  #define  _ee_uint_G_DSG_TH1_HIGH_CURRENT_OTP_TIMES_RECORD_EEPROM                                              0
//  #define  _ee_uint_G_DSG_TH2_LOW_CURRENT_OTP_TIMES_RECORD_EEPROM                                               0
//  #define  _ee_uint_G_DSG_TH2_HIGH_CURRENT_OTP_TIMES_RECORD_EEPROM                                              0
//  #define  _ee_uint_STORE_IN_HIGH_TEMP1_MINUTES_TIMES_RECORD_EEPROM                                             0 // record store in high temp 1 minutes
//  #define  _ee_uint_STORE_IN_HIGH_TEMP2_MINUTES_TIMES_RECORD_EEPROM                                             0 // record store in high temp 2 minutes
//  #define  _ee_uint_STORE_IN_HIGH_TEMP3_MINUTES_TIMES_RECORD_EEPROM                                             0 // record store in high temp 3 minutes
//  #define  _ee_uint_STORE_IN_HIGH_TEMP4_MINUTES_TIMES_RECORD_EEPROM                                             0 // record store in high temp 4 minutes
//  #define  _ee_uint_STORE_IN_HIGH_TEMP5_MINUTES_TIMES_RECORD_EEPROM                                             0 // record store in high temp 5 minutes
//  #define  _ee_uint_RECORD_3rd_TRACKING_DATA_COUNT_EEPROM                                                       0 //
//  #define  _ee_uint_LOW_TEMP1_IN_DSG_ACT_RECORD_MINUTES_EEPROM                                                  0 // record DSG_ACT in low temp 1 minutes
//  #define  _ee_uint_LOW_TEMP2_IN_DSG_ACT_RECORD_MINUTES_EEPROM                                                  0 // record DSG_ACT in low temp 2 minutes
//  #define  _ee_uint_LOW_TEMP3_IN_DSG_ACT_RECORD_MINUTES_EEPROM                                                  0 // record DSG_ACT in low temp 3 minutes
//  #define  _ee_int_RECORDING_System_Activated_Times_For_TotalHours                                              0 // record system activated times for total hours
//  #define  _ee_uchar_RECORDING_Reserved_Data                                                                    0 //
//  #define  _ee_uchar_RECORDING_Reserved_Data1                                                                   0 //
//  #define  _ee_uchar_RECORDING_Reserved_Data2                                                                   0 //
//  #define  _ee_uchar_RECORDING_System_Activated_Times_Minutes_For_1_Hours                                       0 // record system activated times for 1 hours(60min)
//  #define  _ee_uchar_ShakeSwitchDetect_RangeTime_By_AutoWakeUp_TimeCycles                                       1 // RangeTime * interval cycle time,偵測Shake_Switch的時間
//  #define  _ee_uchar_ShakeSwitchTriggerTimes_For_WakeUp                                                         5 // times for valide singal,在時間內Shake_Switch的被觸發的次數, wakeup成立
//  #define  _ee_uchar_GSM_SetInterLockTimes_BeforeBMSSendData                                                    20 //unit:cycles(100ms) , 2sec(org:1 sec) = GSM_SetInterLockTimes_BeforeSendData * TimerIntervalTimeBase_MS
//  #define  _ee_uchar_GSM_SetDelayTimes_ForBMSCheckMosStatus                                                     110 //unit:cycles(100ms) , 11 sec(org:5 sec) = GSM_SetDelayTimes_ForBMSCheckMosStatus * TimerIntervalTimeBase_MS
//  #define  _ee_uint_GSM_System_Enter_SleepingMode_DelayTime_For_STATIC                                          1800 //unit:cycles(100ms) , 1800 = 180 sec = 3 min (org:10 min) = GSM_System_Enter_SleepingMode_DelayTime_For_STATIC * TimerIntervalTimeBase_MS
//  #define  _ee_uint_GSM_SendDataFor_EachDelayTimes_For_DSG                                                      300 //unit:cycles(100ms) , 300 = 30 sec = GSM_SendDataFor_EachDelayTimes_For_DSG * TimerIntervalTimeBase_MS
//  #define  _ee_uint_GSM_SendDataFor_EachDelayTimes_For_CHG                                                      3000 //unit:cycles(100ms) , 3000 = 5 min = 300 sec = GSM_SendDataFor_EachDelayTimes_For_CHG * TimerIntervalTimeBase_MS
//  #define  _ee_uint_GSM_SendData_For_StaticSleeping_By_AutoWakeUp_TimeCycles                                    6136 //180 min = 6136 * 1.76 sec = 10799 sec = 179.9 min; TimeCycle * interval cycle time; in sleeping mode
//  #define  _ee_uint_GSM_System_WakeUp_ReadyTimes_In_SleepingMode                                                150 //unit:cycles(100ms) , 150 = 15 sec = GSM_System_WakeUp_ReadyTimes_In_SleepingMode * TimerIntervalTimeBase_MS
//  #define  _ee_uint_SleepMode_Autowakeup_Intervaltimes_ms                                                       1780 //unit:ms ; 2bytes
//  #define  _ee_float_SleepMode_Autowakeup_Intervaltimes_sec                                                     1.78f // 4 bytes; unit: sec
//  #define  _ee_float_SleepMode_Autowakeup_Intervaltimes_min                                                     0.0296666f // 4 bytes; unit: min (1.78/60)
//  #define  _ee_ulong_LastTotalTimes_Without_Charging_Minutes_RECORD_EEPROM                                      0 //max = 4,294,967,295 = 0xffff ffff
//  #define  _ee_ulong_MaxTotalTimes_Without_Charging_Minutes_RECORD_EEPROM                                       0 //max = 4,294,967,295 = 0xffff ffff
//  #define  _ee_ulong_LastTotalTimes_Without_DisCharging_Minutes_RECORD_EEPROM                                   0 //max = 4,294,967,295 = 0xffff ffff
//  #define  _ee_ulong_MaxTotalTimes_Without_DisCharging_Minutes_RECORD_EEPROM                                    0 //max = 4,294,967,295 = 0xffff ffff
//  #define  _ee_uint_Last_ChargingTimes_Minutes_RECORD_EEPROM                                                    0 // 2bytes; unit:min
//  #define  _ee_uint_Max_ChargingTimes_Minutes_RECORD_EEPROM                                                     0 // 2bytes; unit:min
//  #define  _ee_uchar_EEPROM_END_DATA_POSITION                                                                   160 // EEPROM/Flash End code = 160 = 0xA0
//  #define  _ee_uchar_EEPROM_PN_INFO_START_DATA_POSITION                                                         165 // EEPROM/Flash End code = 165 = 0xA5
//  #define  _ee_str_len_PN_DAK_NAME_MAX_LENGTH                                                                   24
//  #define  _ee_str_PN_DAK_NAME                                                                                  "-----"
//  #define  _ee_str_len_PN_85K_NAME_MAX_LENGTH                                                                   24
//  #define  _ee_str_PN_85K_NAME                                                                                  "-----"
//  #define  _ee_str_len_Cell_PN_NAME_MAX_LENGTH                                                                  24
//  #define  _ee_str_Cell_PN_NAME                                                                                 "-----"
//  #define  _ee_uchar_EEPROM_PN_INFO_END_DATA_POSITION                                                           165 // EEPROM/Flash End code = 165 = 0xA5
//// 
/////////////////////////////////////////////////////////////////////////// 
//// 
//// For Programer Test variable in C.
//// 
//  float Var_float;
//  double Var_double;
//  signed char Var_char;
//  unsigned char Var_uchar;
//  signed int Var_int;
//  unsigned int Var_uint;
//  signed long Var_long;
//  unsigned long Var_ulong;
//// 
//// 
// Var_float      =  CHG_mA_To_ADC_Factor;
// Var_float      =  DSG_mA_To_ADC_Factor;
// Var_float      =  VBAT_mV_To_ADC_Factor;
// Var_float      =  Thermistor_mV_To_ADC_Factor;
// Var_char       =  DSG_OP_ADC_OFFSET;
// Var_char       =  CHG_OP_ADC_OFFSET;
// Var_char       =  VBAT_ADC_OFFSET;
// Var_char       =  NTC1_ADC_OFFSET;
// Var_char       =  NTC2_ADC_OFFSET;
// Var_char       =  SOC_ADC_OFFSET;
// Var_uint       =  R_Sense_10u_ohm;
// Var_uchar      =  MCU_Major_Type_Code;
// Var_uchar      =  MCU_Minor_Type_Code;
// Var_ulong      =  RESERVED_CAL_FOR_OFFSET2;
// Var_uint       =  RESERVED_CAL_FOR_OFFSET3;
// Var_uint       =  MAX_DSG_C_ADC_RECORD_EEPROM;
// Var_uint       =  MAX_CHG_C_ADC_RECORD_EEPROM;
// Var_uint       =  MAX_VBAT_ADC_RECORD_EEPROM;
// Var_uint       =  MIN_VBAT_ADC_RECORD_EEPROM;
// Var_uint       =  MAX_VBAT_SocLo_ADC_RECORD_EEPROM;
// Var_uint       =  MAX_VBAT_SocHi_ADC_RECORD_EEPROM;
// Var_uint       =  DSG_MAX_TH1_ADC_RECORD_EEPROM;
// Var_uint       =  DSG_MIN_TH1_ADC_RECORD_EEPROM;
// Var_uint       =  DSG_MAX_TH2_ADC_RECORD_EEPROM;
// Var_uint       =  DSG_MIN_TH2_ADC_RECORD_EEPROM;
// Var_uint       =  RECORD_DATA_COUNT_EEPROM;
// Var_uint       =  CHG_Cycle_Count_RECORD_EEPROM;
// Var_ulong      =  CHG_ADC_AccumulatingQ_RECORD_EEPROM;
// Var_ulong      =  DSG_ADC_AccumulatingQ_RECORD_EEPROM;
// Var_uint       =  DSG_Cycle_Count_RECORD_EEPROM;
// Var_uint       =  RESERVED_Recording_FOR_OFFSET1;
// Var_uint       =  CHG_MAX_TH1_ADC_RECORD_EEPROM;
// Var_uint       =  CHG_MIN_TH1_ADC_RECORD_EEPROM;
// Var_uint       =  CHG_MAX_TH2_ADC_RECORD_EEPROM;
// Var_uint       =  CHG_MIN_TH2_ADC_RECORD_EEPROM;
// Var_uint       =  G_OVP_TIMES_RECORD_EEPROM;
// Var_uint       =  G_UVP_TIMES_RECORD_EEPROM;
// Var_uint       =  G_COCP_TIMES_RECORD_EEPROM;
// Var_uint       =  G_DOCP_TIMES_RECORD_EEPROM;
// Var_uint       =  G_TH1_CHG_UTP_TIMES_RECORD_EEPROM;
// Var_uint       =  G_TH2_CHG_UTP_TIMES_RECORD_EEPROM;
// Var_uint       =  G_CHG_TH1_OTP_TIMES_RECORD_EEPROM;
// Var_uint       =  G_CHG_TH2_OTP_TIMES_RECORD_EEPROM;
// Var_uint       =  RECORD_2nd_DATA_COUNT_EEPROM;
// Var_uint       =  RESERVED_Recording_FOR_OFFSET3;
// Var_uchar      =  SystemSetting_Info_Byte1;
// Var_uchar      =  SystemSetting_Info_Byte2;
// Var_uchar      =  System_Control_Bit_EEPROM;
// Var_uchar      =  SystemSetting_Info_Byte3;
// Var_uchar      =  VERSION;
// Var_uchar      =  MINOR_VERSION;
// Var_uchar      =  EEPROM_VERSION;
// Var_uchar      =  RESERVED_VERSION;
// Var_uchar      =  NUMBER_OF_PARALLEL_CELLS;
// Var_uchar      =  NUMBER_OF_SERIES_CELLS;
// Var_uint       =  MANUFACTURE_DATE;
// Var_uint       =  SERIAL_NUMBER;
// Var_uchar      =  CELL_TYPE_LENGTH;
// Var_uchar      =  CELL_TYPE;
// Var_uchar      =  MANUFACTURE_NAME_LENGTH;
// Var_uchar      =  MANUFACTURE_NAME;
// Var_uint       =  ADC_CURRENT_DETECT_FOR_DSG_STATUS;
// Var_uint       =  ADC_CURRENT_DETECT_FOR_CHG_STATUS;
// Var_uint       =  ADC_DOC_PROTECTION;
// Var_uint       =  ADC_COC_PROTECTION;
// Var_uint       =  ADC_DSG_HIGH_CURRENT_DETECT;
// Var_uint       =  ADC_CHG_CHARGER_TAPE_CURRENT;
// Var_ulong      =  ADC_AccQ_FOR_CHG_TH;
// Var_uint       =  Cycle_Count_FOR_CHG_1st_TH;
// Var_uint       =  Cycle_Count_FOR_CHG_2nd_TH;
// Var_uint       =  ADC_BATTERY_OV_PROTECTION;
// Var_uint       =  ADC_BATTERY_OV_RELEASE;
// Var_uint       =  ADC_BATTERY_UV_PROTECTION;
// Var_uint       =  ADC_BATTERY_UV_RELEASE;
// Var_uint       =  ADC_DSG_OT_HIGH_PROTECTION;
// Var_uint       =  ADC_DSG_OT_HIGH_RELEASE;
// Var_uint       =  ADC_DSG_OT_LOW_PROTECTION;
// Var_uint       =  ADC_DSG_OT_LOW_RELEASE;
// Var_uint       =  ADC_CHG_OT_PROTECTION;
// Var_uint       =  ADC_CHG_OT_RELEASE;
// Var_uint       =  ADC_UT_PROTECTION;
// Var_uint       =  ADC_UT_RELEASE;
// Var_uint       =  ADC_INITIAL_CHARGING_TEMP_RANGE_HI;
// Var_uint       =  ADC_INITIAL_CHARGING_TEMP_RANGE_LO;
// Var_uint       =  ADC_LOW_TEMP_SOC_CHARGING_RANGE_HI;
// Var_uint       =  ADC_LOW_TEMP_SOC_CHARGING_RANGE_LO;
// Var_ulong      =  ADC_AccQ_FOR_DSG_TH;
// Var_uint       =  DSG_CAPACITY_DISPLAY_TH_1;
// Var_uint       =  DSG_CAPACITY_DISPLAY_TH_2;
// Var_uint       =  DSG_CAPACITY_DISPLAY_TH_3;
// Var_uint       =  DSG_CAPACITY_DISPLAY_TH_4;
// Var_uint       =  Reserved_DSG_CAPACITY_DISPLAY_TH_5;
// Var_uint       =  CHG_CAPACITY_DISPLAY_TH_1;
// Var_uint       =  CHG_CAPACITY_DISPLAY_TH_2;
// Var_uint       =  CHG_CAPACITY_DISPLAY_TH_3;
// Var_uint       =  Reserved_CHG_CAPACITY_DISPLAY_TH_4;
// Var_uint       =  _ADC_LOOKUP_DSG_TEMP_1_TH_;
// Var_uint       =  _ADC_LOOKUP_DSG_TEMP_2_TH_;
// Var_uint       =  _ADC_LOOKUP_DSG_TEMP_3_TH_;
// Var_uint       =  _ADC_LOOKUP_CHG_TEMP_1_TH_;
// Var_uint       =  _ADC_LOOKUP_CHG_TEMP_2_TH_;
// Var_uint       =  _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH1_;
// Var_uint       =  _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH2_;
// Var_uint       =  _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH3_;
// Var_uint       =  _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH4_;
// Var_uint       =  _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH5_;
// Var_uint       =  _ADC_DSG_CURRENT_LOOKUP_OCV_TABLE_TH6_;
// Var_uint       =  AUTO_ENTRY_SLEEPING_DELAY_MINUTES;
// Var_uint       =  CAPACITY_DIFFERENCE_VALUES;
// Var_uchar      =  PROJECT_NAME_MAX_LENGTH;
// Var_uchar      =  PROJECT_NAME;
// Var_uchar      =  MCU_UID_MAX_LENGTH;
// Var_uchar      =  MCU_UID;
// Var_uchar      =  BAR_CODE_REAL_STORE_LENGTH;
// Var_uchar      =  BAR_CODE_MAX_LENGTH;
// Var_uchar      =  BAR_CODE;
// Var_uint       =  DESIGN_CAPACITY_mAH;
// Var_uint       =  Last_Record_FCC_mAh_RECORD_EEPROM;
// Var_uint       =  REAL_FCC_UPDATE_TIMES_RECORD_EEPROM;
// Var_uint       =  REAL_FCC_mAH_RECORD_EEPROM;
// Var_uint       =  STATIC_OVER_VOLTAGE_HOURS_TIMES_RECORD_EEPROM;
// Var_uint       =  CHG_OVER_VOLTAGE_MINUTES_TIMES_RECORD_EEPROM;
// Var_uint       =  OVER_LOADING_MINUTES_TIMES_RECORD_EEPROM;
// Var_uint       =  FASTER_CHARGING_MINUTES_TIMES_RECORD_EEPROM;
// Var_uint       =  CHARGING_IN_HIGH_TEMP_MINUTES_TIMES_RECORD_EEPROM;
// Var_uint       =  CHARGING_IN_LOW_TEMP_MINUTES_TIMES_RECORD_EEPROM;
// Var_uint       =  STORE_IN_LOW_TEMP1_HOURS_TIMES_RECORD_EEPROM;
// Var_uint       =  STORE_IN_LOW_TEMP2_HOURS_TIMES_RECORD_EEPROM;
// Var_uint       =  STORE_IN_LOW_TEMP3_HOURS_TIMES_RECORD_EEPROM;
// Var_uint       =  STORE_IN_LOW_TEMP4_HOURS_TIMES_RECORD_EEPROM;
// Var_uint       =  G_DSG_TH1_LOW_CURRENT_OTP_TIMES_RECORD_EEPROM;
// Var_uint       =  G_DSG_TH1_HIGH_CURRENT_OTP_TIMES_RECORD_EEPROM;
// Var_uint       =  G_DSG_TH2_LOW_CURRENT_OTP_TIMES_RECORD_EEPROM;
// Var_uint       =  G_DSG_TH2_HIGH_CURRENT_OTP_TIMES_RECORD_EEPROM;
// Var_uint       =  STORE_IN_HIGH_TEMP1_MINUTES_TIMES_RECORD_EEPROM;
// Var_uint       =  STORE_IN_HIGH_TEMP2_MINUTES_TIMES_RECORD_EEPROM;
// Var_uint       =  STORE_IN_HIGH_TEMP3_MINUTES_TIMES_RECORD_EEPROM;
// Var_uint       =  STORE_IN_HIGH_TEMP4_MINUTES_TIMES_RECORD_EEPROM;
// Var_uint       =  STORE_IN_HIGH_TEMP5_MINUTES_TIMES_RECORD_EEPROM;
// Var_uint       =  RECORD_3rd_TRACKING_DATA_COUNT_EEPROM;
// Var_uint       =  LOW_TEMP1_IN_DSG_ACT_RECORD_MINUTES_EEPROM;
// Var_uint       =  LOW_TEMP2_IN_DSG_ACT_RECORD_MINUTES_EEPROM;
// Var_uint       =  LOW_TEMP3_IN_DSG_ACT_RECORD_MINUTES_EEPROM;
// Var_int        =  RECORDING_System_Activated_Times_For_TotalHours;
// Var_uchar      =  RECORDING_Reserved_Data;
// Var_uchar      =  RECORDING_Reserved_Data1;
// Var_uchar      =  RECORDING_Reserved_Data2;
// Var_uchar      =  RECORDING_System_Activated_Times_Minutes_For_1_Hours;
// Var_uchar      =  ShakeSwitchDetect_RangeTime_By_AutoWakeUp_TimeCycles;
// Var_uchar      =  ShakeSwitchTriggerTimes_For_WakeUp;
// Var_uchar      =  GSM_SetInterLockTimes_BeforeBMSSendData;
// Var_uchar      =  GSM_SetDelayTimes_ForBMSCheckMosStatus;
// Var_uint       =  GSM_System_Enter_SleepingMode_DelayTime_For_STATIC;
// Var_uint       =  GSM_SendDataFor_EachDelayTimes_For_DSG;
// Var_uint       =  GSM_SendDataFor_EachDelayTimes_For_CHG;
// Var_uint       =  GSM_SendData_For_StaticSleeping_By_AutoWakeUp_TimeCycles;
// Var_uint       =  GSM_System_WakeUp_ReadyTimes_In_SleepingMode;
// Var_uint       =  SleepMode_Autowakeup_Intervaltimes_ms;
// Var_float      =  SleepMode_Autowakeup_Intervaltimes_sec;
// Var_float      =  SleepMode_Autowakeup_Intervaltimes_min;
// Var_ulong      =  LastTotalTimes_Without_Charging_Minutes_RECORD_EEPROM;
// Var_ulong      =  MaxTotalTimes_Without_Charging_Minutes_RECORD_EEPROM;
// Var_ulong      =  LastTotalTimes_Without_DisCharging_Minutes_RECORD_EEPROM;
// Var_ulong      =  MaxTotalTimes_Without_DisCharging_Minutes_RECORD_EEPROM;
// Var_uint       =  Last_ChargingTimes_Minutes_RECORD_EEPROM;
// Var_uint       =  Max_ChargingTimes_Minutes_RECORD_EEPROM;
// Var_uchar      =  EEPROM_END_DATA_POSITION;
// Var_uchar      =  EEPROM_PN_INFO_START_DATA_POSITION;
// Var_uchar      =  PN_DAK_NAME_MAX_LENGTH;
// Var_uchar      =  PN_DAK_NAME;
// Var_uchar      =  PN_85K_NAME_MAX_LENGTH;
// Var_uchar      =  PN_85K_NAME;
// Var_uchar      =  Cell_PN_NAME_MAX_LENGTH;
// Var_uchar      =  Cell_PN_NAME;
// Var_uchar      =  EEPROM_PN_INFO_END_DATA_POSITION;
//// 
