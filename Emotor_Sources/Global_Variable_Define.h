
#define BAR_CODE_ID_Array_Size	                    (24)
#define BAR_CODE_ID_Array_Whole_Size	            (BAR_CODE_ID_Array_Size + 2 + 1)
extern unsigned char G_BAR_CODE_ID_Array[];

#define VarArray_Int_Size	                        (109)


extern unsigned int G_Var_Array[];


#define G_SysModeStatusCode                 (G_Var_Array[ 0])
#define G_Module_Status                     (G_Var_Array[ 1])   //use
#define G_Module_Function_Status            (G_Var_Array[ 2])   //use
#define G_Add_Module_Function_Status        (G_Var_Array[ 3])   //use
#define G_Device_Interface_Status           (G_Var_Array[ 4])  //use
#define G_Extend_Device_Interface_Status    (G_Var_Array[ 5])   //use
#define G_Capacity_Var_Bits_Status          (G_Var_Array[ 6])   //use
//#define G_Auxiliary_Module_Status       (G_Var_Array[ 5])   //use
//#define G_SystemFailureStatus           (G_Var_Array[ 3])
//#define G_LED_Interface_Status1         (G_Var_Array[ 4])   //use
//#define G_LED_Interface_Status2         (G_Var_Array[ 5])   //use
//#define G_Device_Interface_Status2      (G_Var_Array[ 7])  //use
//#define G_Add_Device_Interface_Status   (G_Var_Array[ 7])  //use
#define G_DSG_Current_ADC                   (G_Var_Array[ 7])
#define G_CHG_Current_ADC                   (G_Var_Array[ 8])
#define G_VBAT_ADC                          (G_Var_Array[ 9])
#define G_NTC1_ADC                          (G_Var_Array[ 10])
#define G_NTC2_ADC                          (G_Var_Array[ 11])
#define G_Vref_mVoltage                     (G_Var_Array[ 12])
#define G_Current_Capacity                  (G_Var_Array[ 13])
#define G_Hold_Capacity                     (G_Var_Array[ 14])
#define G_AVG_DSG_Current_ADC               (G_Var_Array[ 15])


///////////////////////////////////////////////////////////////////////////////
////recording data  (previous Total Items: 16)
#define RECORDING_DATA_Start_Array_Index    16
#define RECORDING_DATA_NUMBER               34
#define G_RECORD_DATA_COUNT             		(G_Var_Array[RECORDING_DATA_Start_Array_Index + 0 ])
#define G_MAX_DSG_C_ADC_RECORD          		(G_Var_Array[RECORDING_DATA_Start_Array_Index + 1 ])
#define G_MAX_CHG_C_ADC_RECORD          		(G_Var_Array[RECORDING_DATA_Start_Array_Index + 2 ])
#define G_MAX_VBAT_ADC_RECORD           		(G_Var_Array[RECORDING_DATA_Start_Array_Index + 3 ])
#define G_MIN_VBAT_ADC_RECORD           		(G_Var_Array[RECORDING_DATA_Start_Array_Index + 4 ])
#define G_MAX_VBAT_SocLo_ADC_RECORD     		(G_Var_Array[RECORDING_DATA_Start_Array_Index + 5 ])  // for SOC Low
#define G_MAX_VBAT_SocHi_ADC_RECORD     		(G_Var_Array[RECORDING_DATA_Start_Array_Index + 6 ])  // for SOC High
#define G_DSG_MAX_TH1_ADC_RECORD            	(G_Var_Array[RECORDING_DATA_Start_Array_Index + 7 ])
#define G_DSG_MIN_TH1_ADC_RECORD            	(G_Var_Array[RECORDING_DATA_Start_Array_Index + 8 ])
#define G_DSG_MAX_TH2_ADC_RECORD            	(G_Var_Array[RECORDING_DATA_Start_Array_Index + 9 ])
#define G_DSG_MIN_TH2_ADC_RECORD            	(G_Var_Array[RECORDING_DATA_Start_Array_Index + 10 ])

#define G_CHG_Cycle_Count_RECORD            	(G_Var_Array[RECORDING_DATA_Start_Array_Index + 11 ])
#define G_CHG_ADC_AccumulatingQ_RECORD_Hi   	(G_Var_Array[RECORDING_DATA_Start_Array_Index + 12 ])
#define G_CHG_ADC_AccumulatingQ_RECORD_Lo   	(G_Var_Array[RECORDING_DATA_Start_Array_Index + 13 ])

#define G_DSG_ADC_AccumulatingQ_RECORD_Hi		(G_Var_Array[RECORDING_DATA_Start_Array_Index + 14 ])
#define G_DSG_ADC_AccumulatingQ_RECORD_Lo		(G_Var_Array[RECORDING_DATA_Start_Array_Index + 15 ])
#define G_DSG_Cycle_Count_RECORD            	(G_Var_Array[RECORDING_DATA_Start_Array_Index + 16 ])

#define G_CHG_MAX_TH1_ADC_RECORD            	(G_Var_Array[RECORDING_DATA_Start_Array_Index + 17 ])
#define G_CHG_MIN_TH1_ADC_RECORD            	(G_Var_Array[RECORDING_DATA_Start_Array_Index + 18 ])
#define G_CHG_MAX_TH2_ADC_RECORD            	(G_Var_Array[RECORDING_DATA_Start_Array_Index + 19 ])
#define G_CHG_MIN_TH2_ADC_RECORD            	(G_Var_Array[RECORDING_DATA_Start_Array_Index + 20 ])

#define G_OVP_TIMES		                        (G_Var_Array[RECORDING_DATA_Start_Array_Index + 21 ])
#define G_UVP_TIMES		                        (G_Var_Array[RECORDING_DATA_Start_Array_Index + 22 ])
#define G_COCP_TIMES		                    (G_Var_Array[RECORDING_DATA_Start_Array_Index + 23 ])
#define G_DOCP_TIMES		                    (G_Var_Array[RECORDING_DATA_Start_Array_Index + 24 ])


#define G_TH1_CHG_UTP_TIMES                 	(G_Var_Array[RECORDING_DATA_Start_Array_Index + 25 ])
#define G_TH2_CHG_UTP_TIMES                 	(G_Var_Array[RECORDING_DATA_Start_Array_Index + 26 ])
#define G_CHG_TH1_OTP_TIMES                 	(G_Var_Array[RECORDING_DATA_Start_Array_Index + 27 ])
#define G_CHG_TH2_OTP_TIMES                 	(G_Var_Array[RECORDING_DATA_Start_Array_Index + 28 ])

#define G_DSG_TH1_LOW_CURRENT_OTP_TIMES         (G_Var_Array[RECORDING_DATA_Start_Array_Index + 29 ])
#define G_DSG_TH1_HIGH_CURRENT_OTP_TIMES        (G_Var_Array[RECORDING_DATA_Start_Array_Index + 30 ])
#define G_DSG_TH2_LOW_CURRENT_OTP_TIMES         (G_Var_Array[RECORDING_DATA_Start_Array_Index + 31 ])
#define G_DSG_TH2_HIGH_CURRENT_OTP_TIMES        (G_Var_Array[RECORDING_DATA_Start_Array_Index + 32 ])

#define G_RECORD_2nd_DATA_COUNT                 (G_Var_Array[RECORDING_DATA_Start_Array_Index + 33 ])
////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// second recording data    (previous Total Items: 16 + 34 = 50)
#define _2nd_RECORDING_DATA_Start_Array_Index       (RECORDING_DATA_Start_Array_Index + RECORDING_DATA_NUMBER)
#define _2nd_RECORDING_DATA_NUMBER                  (26)

#define G_REAL_FCC_UPDATE_TIMES                 (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 0])
#define G_Real_FCC_In_CoulombCounter            (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 1])
#define G_Derating_FCC_In_CoulombCounter        (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 2])
#define G_RM_In_CoulombCounter                  (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 3])
#define G_Capacity_In_CoulombCounter            (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 4])

#define G_STATIC_OVER_VOLTAGE_HOURS_TIMES       (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 5])
#define G_CHG_OVER_VOLTAGE_MINUTES_TIMES          (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 6])
#define G_OVER_LOADING_MINUTES_TIMES            (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 7])
#define G_FASTER_CHARGING_MINUTES_TIMES         (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 8])

#define G_CHARGING_IN_HIGH_TEMP_MINUTES_TIMES     (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 9])
#define G_CHARGING_IN_LOW_TEMP_MINUTES_TIMES      (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 10])

#define G_STORE_IN_LOW_TEMP1_HOURS_TIMES        (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 11])
#define G_STORE_IN_LOW_TEMP2_HOURS_TIMES        (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 12])
#define G_STORE_IN_LOW_TEMP3_HOURS_TIMES        (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 13])
#define G_STORE_IN_LOW_TEMP4_HOURS_TIMES        (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 14])

#define G_STORE_IN_HIGH_TEMP1_MINUTES_TIMES     (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 15])
#define G_STORE_IN_HIGH_TEMP2_MINUTES_TIMES     (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 16])
#define G_STORE_IN_HIGH_TEMP3_MINUTES_TIMES     (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 17])
#define G_STORE_IN_HIGH_TEMP4_MINUTES_TIMES     (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 18])
#define G_STORE_IN_HIGH_TEMP5_MINUTES_TIMES     (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 19])
#define G_RECORD_3rd_TRACKING_DATA_COUNT        (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 20])
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Real Time Information
#define G_NTC1_Real_0p1_KelvinDegree            (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 21])
#define G_NTC2_Real_0p1_KelvinDegree            (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 22])

#define G_Last_FCC_Updated_Values               (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 23])
#define G_AVG_Battery_Voltage_ADC               (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 24])

#define G_System_Activated_TotalHours           (G_Var_Array[ _2nd_RECORDING_DATA_Start_Array_Index + 25])

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 3rd status   (previous Total Items: 50 + 26 = 76)
#define _3rd_STATUS_DATA_Start_Array_Index          (_2nd_RECORDING_DATA_Start_Array_Index + _2nd_RECORDING_DATA_NUMBER)
#define _3rd_STATUS_DATA_NUMBER                     (32)

#define G_Count_TimesOfAutoWakeUp_InSleeping_Hi     (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 0])
#define G_Count_TimesOfAutoWakeUp_InSleeping_Lo     (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 1])
#define G_System_Device_Extend_1_Status             (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 2])

#define G_Current_ChargingTimes_Minutes             (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 3])
#define G_Last_ChargingTimes_Minutes                (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 4])
#define G_Max_ChargingTimes_Minutes                 (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 5])
//=========================================================================================================
// the address starting is fit for Data type of Long, Double, float (which is four bytes) can use Point (long *) to access it
#define G_Current_InSleepingMode_Times_Hi               (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 6])
#define G_Current_InSleepingMode_Times_Lo               (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 7])

#define G_NowTotalTimes_Without_Charging_Minutes_Hi     (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 8])
#define G_NowTotalTimes_Without_Charging_Minutes_Lo     (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 9])
#define G_LastTotalTimes_Without_Charging_Minutes_Hi    (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 10])
#define G_LastTotalTimes_Without_Charging_Minutes_Lo    (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 11])
#define G_MaxTotalTimes_Without_Charging_Minutes_Hi     (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 12])
#define G_MaxTotalTimes_Without_Charging_Minutes_Lo     (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 13])

#define G_NowTotalTimes_Without_DisCharging_Minutes_Hi      (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 14])
#define G_NowTotalTimes_Without_DisCharging_Minutes_Lo      (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 15])
#define G_LastTotalTimes_Without_DisCharging_Minutes_Hi     (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 16])
#define G_LastTotalTimes_Without_DisCharging_Minutes_Lo     (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 17])
#define G_MaxTotalTimes_Without_DisCharging_Minutes_Hi      (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 18])
#define G_MaxTotalTimes_Without_DisCharging_Minutes_Lo      (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 19])
// use Point (long *) to access it
#define G_ul_Current_InSleepingMode_Times                   (*((unsigned long *)(&G_Current_InSleepingMode_Times_Hi)))
#define G_ul_NowTotalTimes_Without_Charging_Minutes         (*((unsigned long *)(&G_NowTotalTimes_Without_Charging_Minutes_Hi)))
#define G_ul_LastTotalTimes_Without_Charging_Minutes        (*((unsigned long *)(&G_LastTotalTimes_Without_Charging_Minutes_Hi)))
#define G_ul_MaxTotalTimes_Without_Charging_Minutes         (*((unsigned long *)(&G_MaxTotalTimes_Without_Charging_Minutes_Hi)))
#define G_ul_NowTotalTimes_Without_DisCharging_Minutes      (*((unsigned long *)(&G_NowTotalTimes_Without_DisCharging_Minutes_Hi)))
#define G_ul_LastTotalTimes_Without_DisCharging_Minutes     (*((unsigned long *)(&G_LastTotalTimes_Without_DisCharging_Minutes_Hi)))
#define G_ul_MaxTotalTimes_Without_DisCharging_Minutes      (*((unsigned long *)(&G_MaxTotalTimes_Without_DisCharging_Minutes_Hi)))
//=========================================================================================================
// the address starting is fit for Data type of Long, Double, float (which is four bytes) can use Point (long *) to access it
#define G_RECORDING_ADC_DSG_OVER_CURRENT_1_6sec_Hi               (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 20])
#define G_RECORDING_ADC_DSG_OVER_CURRENT_1_6sec_Lo               (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 21])
#define G_RECORDING_ADC_DSG_OVER_CURRENT_2_6sec_Hi               (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 22])
#define G_RECORDING_ADC_DSG_OVER_CURRENT_2_6sec_Lo               (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 23])
#define G_RECORDING_ADC_DSG_OVER_CURRENT_3_6sec_Hi               (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 24])
#define G_RECORDING_ADC_DSG_OVER_CURRENT_3_6sec_Lo               (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 25])
#define G_RECORDING_ADC_DSG_OVER_CURRENT_4_6sec_Hi               (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 26])
#define G_RECORDING_ADC_DSG_OVER_CURRENT_4_6sec_Lo               (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 27])
#define G_RECORDING_ADC_DSG_OVER_CURRENT_5_6sec_Hi               (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 28])
#define G_RECORDING_ADC_DSG_OVER_CURRENT_5_6sec_Lo               (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 29])
#define G_RECORDING_ADC_DSG_OVER_CURRENT_6_6sec_Hi               (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 30])
#define G_RECORDING_ADC_DSG_OVER_CURRENT_6_6sec_Lo               (G_Var_Array[ _3rd_STATUS_DATA_Start_Array_Index + 31])
// use Point (long *) to access it
#define G_ul_RECORDING_ADC_DSG_OVER_CURRENT_1_6sec         (*((unsigned long *)(&G_RECORDING_ADC_DSG_OVER_CURRENT_1_6sec_Hi)))
#define G_ul_RECORDING_ADC_DSG_OVER_CURRENT_2_6sec         (*((unsigned long *)(&G_RECORDING_ADC_DSG_OVER_CURRENT_2_6sec_Hi)))
#define G_ul_RECORDING_ADC_DSG_OVER_CURRENT_3_6sec         (*((unsigned long *)(&G_RECORDING_ADC_DSG_OVER_CURRENT_3_6sec_Hi)))
#define G_ul_RECORDING_ADC_DSG_OVER_CURRENT_4_6sec         (*((unsigned long *)(&G_RECORDING_ADC_DSG_OVER_CURRENT_4_6sec_Hi)))
#define G_ul_RECORDING_ADC_DSG_OVER_CURRENT_5_6sec         (*((unsigned long *)(&G_RECORDING_ADC_DSG_OVER_CURRENT_5_6sec_Hi)))
#define G_ul_RECORDING_ADC_DSG_OVER_CURRENT_6_6sec         (*((unsigned long *)(&G_RECORDING_ADC_DSG_OVER_CURRENT_6_6sec_Hi)))






