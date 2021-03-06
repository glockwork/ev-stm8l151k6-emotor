
//#include "..\SystemInitialData\SystemInformation.h"


''
/***********************************************
 * not put the data in memory
 * this is for SOC function to use
 ***********************************************/
//#define SOC_BATTERY_OV_VOLTAGE     __2ND_BATTERY_OV_PROTECTION_     //5600
//#define SOC_BATTERY_UV_VOLTAGE     __2ND_BATTERY_UV_PROTECTION_     //3700
//#define SOC_1st_CELL_OV_VOLTAGE     4250 //mV
//#define SOC_1st_CELL_UV_VOLTAGE     2500 //mV
//=====================================================================================================================
//========== Use for new SOC Table for 6 lines ( 1 line OCV, four lines DSG, 1 line CHG )==============================
//========================_NUMBER_OF_PARALLEL_CELLS_= 4  ==============================================================
// OCV TABLE Line Current Range, 7 ocv lines, (DSG)
// Battery for a cell capacity ==> 2600 mAH * 4p
// 10.4Ah四並聯,  DSG  5A,   DSG 7.5A,  DSG 10A,   DSG 15A 
// OCV 2.5 A 以下
// line 1 range = 2.5A~ 6.25A (for DSG 5A),   
// line 2 range = 6.25A ~ 8.75A (for DSG 7.5A), 
// line 3 range = 8.75A ~ 12.5A (for DSG 10A), 
// line 4 range = ( > 12.5A) (for DSG 15A), 
//  _DSG_mA_to_ADC_factor_   (參考上面之設定)
// ADC 10 bit==> max adc = 1024
#define ADC_LOOKUP_1_POINT_OCV_CURRENT_TH     509     // 2500mA; 2bytes; 
#define ADC_LOOKUP_2_POINT_OCV_CURRENT_TH     1272     // 6250mA; 2bytes; 
#define ADC_LOOKUP_3_POINT_OCV_CURRENT_TH     1781     // 8750mA; 2bytes; 
#define ADC_LOOKUP_4_POINT_OCV_CURRENT_TH     2544     // 12500mA; 2bytes; 
//=====================================================================================================================


#define OCV_TABLE_POINTS 51
#define NUM_OF_OCV_LINE  6

#define RESIDUAL_CAPACITY_INDEX         0
#define RESIDUAL_DSG_1st_CURRENT_INDEX  1
#define RESIDUAL_DSG_2nd_CURRENT_INDEX  2
#define RESIDUAL_DSG_3rd_CURRENT_INDEX  3
#define RESIDUAL_DSG_4th_CURRENT_INDEX  4
#define RESIDUAL_OCV_CURRENT_INDEX      5
#define RESIDUAL_CHG_1st_CURRENT_INDEX  6


/*
; TERMINAL_VOLTAGE units is mV
; RESIDUAL_CAPACITY units is percentage
; Please sort from largest to smallest
// 2600mAh cell, 25 degree, OCV Table
*/

const unsigned int RealOCVTable[OCV_TABLE_POINTS][NUM_OF_OCV_LINE+1] =
{
////////////// RESIDUAL CAPACITY ////////////////////////////////////////////////////////////////
//7.8Ah       1st       2nd      3rd        4th       OCV        1st 
//Capacity,  DSG 5A,  DSG 7.5A,  DSG 10A,  DSG 15A,    OCV,    CHG 2A,     ///////////////////////
//   (%)      (mV)       (mV)      (mV)      (mV)      (mV)      (mV)
    { 100,    41850,    41850,    41850,    41850,    41850,    41864  },   //index = 00       
    { 98 ,    40050,    39227,    38710,    37499,    41616,    41764  },   //index = 01       
    { 96 ,    39764,    38842,    38292,    36958,    41381,    41663  },   //index = 02       
    { 94 ,    39519,    38578,    38016,    36664,    41172,    41560  },   //index = 03       
    { 92 ,    39288,    38349,    37783,    36409,    40969,    41455  },   //index = 04       
    { 90 ,    39076,    38140,    37571,    36222,    40766,    41353  },   //index = 05       
    { 88 ,    38860,    37942,    37372,    36032,    40577,    41256  },   //index = 06       
    { 86 ,    38652,    37755,    37185,    35879,    40389,    41063  },   //index = 07       
    { 84 ,    38450,    37575,    37005,    35715,    40209,    40876  },   //index = 08       
    { 82 ,    38255,    37403,    36831,    35577,    40046,    40702  },   //index = 09       
    { 80 ,    38070,    37238,    36667,    35427,    39874,    40533  },   //index = 10       
    { 78 ,    37896,    37089,    36520,    35281,    39720,    40372  },   //index = 11       
    { 76 ,    37723,    36935,    36364,    35156,    39572,    40221  },   //index = 12       
    { 74 ,    37558,    36787,    36216,    35018,    39426,    40084  },   //index = 13       
    { 72 ,    37398,    36645,    36072,    34900,    39294,    39952  },   //index = 14       
    { 70 ,    37247,    36508,    35934,    34770,    39161,    39832  },   //index = 15       
    { 68 ,    37101,    36376,    35798,    34658,    39043,    39721  },   //index = 16       
    { 66 ,    36967,    36248,    35668,    34534,    38931,    39620  },   //index = 17       
    { 64 ,    36836,    36126,    35545,    34417,    38815,    39530  },   //index = 18       
    { 62 ,    36706,    36010,    35423,    34315,    38722,    39447  },   //index = 19       
    { 60 ,    36586,    35899,    35310,    34208,    38622,    39371  },   //index = 20       
    { 58 ,    36485,    35794,    35213,    34131,    38475,    39301  },   //index = 21       
    { 56 ,    36406,    35695,    35134,    34059,    38286,    39231  },   //index = 22       
    { 54 ,    36326,    35602,    35056,    33997,    38122,    39152  },   //index = 23       
    { 52 ,    36247,    35521,    34988,    33924,    37980,    39071  },   //index = 24       
    { 50 ,    36167,    35439,    34908,    33842,    37895,    39003  },   //index = 25       
    { 48 ,    36085,    35363,    34828,    33767,    37838,    38945  },   //index = 26       
    { 46 ,    36009,    35291,    34753,    33684,    37778,    38895  },   //index = 27       
    { 44 ,    35927,    35222,    34674,    33604,    37755,    38847  },   //index = 28       
    { 42 ,    35848,    35155,    34597,    33514,    37731,    38804  },   //index = 29       
    { 40 ,    35763,    35087,    34519,    33434,    37712,    38763  },   //index = 30       
    { 38 ,    35673,    35019,    34440,    33340,    37696,    38725  },   //index = 31       
    { 36 ,    35574,    34947,    34356,    33245,    37681,    38689  },   //index = 32       
    { 34 ,    35469,    34872,    34268,    33157,    37662,    38655  },   //index = 33       
    { 32 ,    35350,    34790,    34172,    33054,    37645,    38624  },   //index = 34       
    { 30 ,    35224,    34701,    34070,    32957,    37616,    38594  },   //index = 35       
    { 28 ,    35087,    34601,    33961,    32844,    37557,    38566  },   //index = 36       
    { 26 ,    34925,    34495,    33839,    32723,    37526,    38537  },   //index = 37       
    { 24 ,    34764,    34367,    33711,    32587,    37398,    38501  },   //index = 38       
    { 22 ,    34584,    34218,    33557,    32445,    37271,    38443  },   //index = 39       
    { 20 ,    34390,    34046,    33381,    32259,    37118,    38332  },   //index = 40       
    { 18 ,    34205,    33849,    33202,    32081,    36837,    38124  },   //index = 41       
    { 16 ,    33982,    33646,    33015,    31922,    36564,    37762  },   //index = 42       
    { 14 ,    33808,    33456,    32849,    31740,    36264,    37258  },   //index = 43       
    { 12 ,    33650,    33256,    32669,    31563,    35971,    36809  },   //index = 44       
    { 10 ,    33449,    33034,    32454,    31328,    35714,    36490  },   //index = 45       
    { 8  ,    33196,    32787,    32197,    31068,    35511,    36241  },   //index = 46       
    { 6  ,    32814,    32433,    31814,    30598,    35295,    36025  },   //index = 47       
    { 4  ,    31985,    31693,    31009,    29652,    34857,    35767  },   //index = 48       
    { 2  ,    30136,    30092,    29295,    28011,    33775,    34682  },   //index = 49       
    { 0  ,    25024,    27568,    26719,    25000,    31490,    31569  }    //index = 50 
};

//#define TERMINAL_VOLTAGE_INDEX 0                            
//#define RESIDUAL_CAPACITY_INDEX 1                           
//                                                            
//const int RealOCVTable[OCV_TABLE_POINTS][2] =               
//{                                                           
//  {  4087,  9994  },    //index=00,  1st                    
//  {  3997,  9496  },    //index=01,  2nd                    
//  {  3941,  8998  },    //index=02,  3rd                    
//  {  3890,  8499  },    //index=03,  4th                    
//  {  3843,  8000  },    //index=04,  5th                    
//  {  3800,  7501  },    //index=05,  6th                    
//  {  3761,  7002  },    //index=06,  7th                    
//  {  3727,  6504  },    //index=07,  8th                    
//  {  3695,  6005  },    //index=08,  9th                    
//  {  3666,  5507  },    //index=09,  10th                   
//  {  3641,  5009  },    //index=10,  11th                   
//  {  3618,  4510  },    //index=11,  12th                   
//  {  3596,  4012  },    //index=12,  13th                   
//  {  3572,  3513  },    //index=13,  14th                   
//  {  3544,  3015  },    //index=14,  15th                   
//  {  3511,  2515  },    //index=15,  16th                   
//  {  3473,  2016  },    //index=16,  17th                   
//  {  3432,  1518  },    //index=17,  18th                   
//  {  3381,  1019  },    //index=18,  19th                   
//  {  3299,  521   },    //index=19,  20th                   
//  {  2748,  0     }     //index=20,  21th                   
//};                                                          
                                                              
                                                              
