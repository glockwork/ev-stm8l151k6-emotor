
//#include "..\SystemInitialData\SystemInformation.h"



/***********************************************
 * not put the data in memory
 * this is for SOC function to use
 ***********************************************/
//#define SOC_BATTERY_OV_VOLTAGE     __2ND_BATTERY_OV_PROTECTION_     //5600
//#define SOC_BATTERY_UV_VOLTAGE     __2ND_BATTERY_UV_PROTECTION_     //3700
//#define SOC_1st_CELL_OV_VOLTAGE     4250 //mV
//#define SOC_1st_CELL_UV_VOLTAGE     2500 //mV



/*
; TERMINAL_VOLTAGE units is mV
; RESIDUAL_CAPACITY units is percentage * 100
; Please sort from largest to smallest
// 2600mAh cell, 25 degree, 0.5C OCV Table
*/
#define TEMPERATURE_TABLE_SECTIONS      4

#define RESIDUAL_DSG_1st_TEMPERATURE_INDEX  0
#define RESIDUAL_DSG_2nd_TEMPERATURE_INDEX  1
#define RESIDUAL_DSG_3rd_TEMPERATURE_INDEX  2
#define RESIDUAL_DSG_4th_TEMPERATURE_INDEX  3

#define SOC_DSG_TABLE_POINTS                21

#define NUM_OF_SOC_DSG_LINES                7

#define RESIDUAL_OCV_DSG_CAP_INDEX          0
#define RESIDUAL_DSG_1st_CURRENT_INDEX  1
#define RESIDUAL_DSG_2nd_CURRENT_INDEX  2
#define RESIDUAL_DSG_3rd_CURRENT_INDEX  3
#define RESIDUAL_DSG_4th_CURRENT_INDEX  4
#define RESIDUAL_DSG_5th_CURRENT_INDEX  5
#define RESIDUAL_DSG_6th_CURRENT_INDEX  6
#define RESIDUAL_DSG_7th_CURRENT_INDEX  7

const unsigned int SOC_DSG__Table[TEMPERATURE_TABLE_SECTIONS][SOC_TABLE_POINTS][NUM_OF_SOC_LINES+1] =
{
    {// 1st Dim
        ////////////// RESIDUAL CAPACITY  at 5 degrees ////////////////////////////////////////////////////////////////////
        //     Capacity,     1st mV  2nd mV     3rd mV      4th mV    5th mV      6th mV     7th mV
        //  7.8Ah三並聯,  DSG  3A,   DSG 5A,    DSG 7A,     DSG 9A,   DSG 11.2A,  DSG 13A,   DSG 15A,
        // 10.4Ah四並聯,  DSG  4A,   DSG 6.7A,  DSG 9.3A,   DSG 12A,  DSG 14.9A,  DSG 17.3A, DSG 20A,
        //    cap*100,  DSG 0.384C, DSG 0.641C, DSG 0.89C, DSG1.153C, DSG 1.435C, DSG1.666C, DSG 1.923C //////////////////
          {     9456 ,     41127,     40641,     40148,     39712,     39307,     38931,     38592 },   //index = 00           
          {     8908 ,     40320,     39876,     39399,     38977,     38589,     38272,     37903 },   //index = 01           
          {     8361 ,     39693,     39250,     38815,     38366,     37940,     37620,     37260 },   //index = 02           
          {     7814 ,     39112,     38696,     38241,     37795,     37546,     37062,     36710 },   //index = 03           
          {     7268 ,     38584,     38125,     37700,     37300,     36904,     36536,     36248 },   //index = 04           
          {     6721 ,     38041,     37599,     37180,     36738,     36344,     36146,     35688 },   //index = 05           
          {     6174 ,     37524,     37112,     36646,     36237,     35848,     35592,     35204 },   //index = 06           
          {     5630 ,     37061,     36597,     36157,     35769,     35433,     35132,     34870 },   //index = 07           
          {     5083 ,     36584,     36162,     35766,     35390,     35016,     34668,     34452 },   //index = 08           
          {     4536 ,     36220,     35808,     35388,     35044,     34628,     34369,     34044 },   //index = 09           
          {     3989 ,     35936,     35525,     35108,     34731,     34384,     34082,     33702 },   //index = 10           
          {     3442 ,     35712,     35297,     34880,     34496,     34117,     33839,     33503 },   //index = 11           
          {     2895 ,     35525,     35119,     34702,     34320,     33889,     33571,     33224 },   //index = 12           
          {     2349 ,     35349,     34913,     34477,     34115,     33717,     33397,     32993 },   //index = 13           
          {     1805 ,     35191,     34714,     34262,     33851,     33479,     33097,     32734 },   //index = 14           
          {     1259 ,     34978,     34482,     34034,     33570,     33130,     32771,     32392 },   //index = 15           
          {     712  ,     34707,     34172,     33673,     33145,     32728,     32259,     31841 },   //index = 16           
          {     165  ,     34260,     33639,     32977,     32273,     31809,     31465,     30673 },   //index = 17           
          {     0    ,     30387,     30702,     30911,     30370,     30163,     31465,     30673 },   //index = 18 
          {     0    ,     30387,     30702,     30911,     30370,     30163,     31465,     30673 },   //index = 19 
          {     0    ,     30387,     30702,     30911,     30370,     30163,     31465,     30673 }    //index = 20 
    },          
         
    {// 2nd Dim
        ////////////// RESIDUAL CAPACITY  at 25 degrees ////////////////////////////////////////////////////////////////////
        //     Capacity,     1st mV  2nd mV     3rd mV      4th mV    5th mV      6th mV     7th mV
        //  7.8Ah三並聯,  DSG  3A,   DSG 5A,    DSG 7A,     DSG 9A,   DSG 11.2A,  DSG 13A,   DSG 15A,
        // 10.4Ah四並聯,  DSG  4A,   DSG 6.7A,  DSG 9.3A,   DSG 12A,  DSG 14.9A,  DSG 17.3A, DSG 20A,
        //    cap*100,  DSG 0.384C, DSG 0.641C, DSG 0.89C, DSG1.153C, DSG 1.435C, DSG1.666C, DSG 1.923C //////////////////
            {    9494,     41422,     41094,     40848,     40486,     40109,     39841,     39570   },    //index = 00
            {    8988,     40639,     40336,     40076,     39725,     39386,     39175,     38768   },    //index = 01
            {    8481,     40012,     39704,     39415,     39052,     38708,     38457,     38127   },    //index = 02
            {    7975,     39435,     39123,     38831,     38466,     38122,     37867,     37539   },    //index = 03
            {    7469,     38899,     38609,     38288,     37920,     37671,     37372,     36995   },    //index = 04
            {    6964,     38404,     38101,     37777,     37444,     37119,     36812,     36480   },    //index = 05
            {    6458,     37911,     37619,     37293,     36962,     36637,     36376,     36051   },    //index = 06
            {    5953,     37519,     37156,     36886,     36483,     36152,     35889,     35571   },    //index = 07
            {    5446,     37018,     36715,     36459,     36054,     35778,     35478,     35168   },    //index = 08
            {    4941,     36607,     36309,     36025,     35665,     35388,     35136,     34794   },    //index = 09
            {    4434,     36293,     35998,     35734,     35361,     35047,     34791,     34492   },    //index = 10
            {    3929,     36050,     35757,     35493,     35122,     34835,     34548,     34284   },    //index = 11
            {    3423,     35862,     35569,     35283,     34928,     34615,     34384,     34046   },    //index = 12
            {    2917,     35707,     35411,     35122,     34760,     34434,     34184,     33947   },    //index = 13
            {    2411,     35569,     35259,     34973,     34596,     34300,     34001,     33675   },    //index = 14
            {    1904,     35404,     35097,     34800,     34417,     34080,     33850,     33477   },    //index = 15
            {    1399,     35216,     34916,     34595,     34198,     33851,     33613,     33226   },    //index = 16
            {    892 ,     34920,     34611,     34268,     33853,     33484,     33230,     32822   },    //index = 17
            {    387 ,     34387,     34038,     33659,     33170,     32760,     32415,     31995   },    //index = 18
            {    0   ,     30473,     30605,     30846,     31192,     31389,     30846,     30362   },    //index = 19
            {    0   ,     30473,     30605,     30846,     31192,     31389,     30846,     30362   }     //index = 20
    },
    
    {// 3rd Dim
        ////////////// RESIDUAL CAPACITY  at 40 degrees ////////////////////////////////////////////////////////////////////
        //     Capacity,     1st mV  2nd mV     3rd mV      4th mV    5th mV      6th mV     7th mV
        //  7.8Ah三並聯,  DSG  3A,   DSG 5A,    DSG 7A,     DSG 9A,   DSG 11.2A,  DSG 13A,   DSG 15A,
        // 10.4Ah四並聯,  DSG  4A,   DSG 6.7A,  DSG 9.3A,   DSG 12A,  DSG 14.9A,  DSG 17.3A, DSG 20A,
        //    cap*100,  DSG 0.384C, DSG 0.641C, DSG 0.89C, DSG1.153C, DSG 1.435C, DSG1.666C, DSG 1.923C //////////////////
            {    9514,     41478,     41200,     40892,     40610,     40331,     40065,     39780 },     //index = 00 
            {    9028,     40728,     40451,     40159,     39876,     39596,     39293,     39046 },     //index = 01 
            {    8541,     40102,     39817,     39568,     39234,     38923,     38644,     38405 },     //index = 02 
            {    8059,     39522,     39231,     38931,     38638,     38327,     38057,     37774 },     //index = 03 
            {    7572,     38977,     38684,     38381,     38086,     37814,     37492,     37212 },     //index = 04 
            {    7086,     38474,     38188,     37861,     37566,     37295,     36971,     36741 },     //index = 05 
            {    6599,     37975,     37596,     37367,     37073,     36761,     36479,     36198 },     //index = 06 
            {    6112,     37531,     37133,     36981,     36626,     36355,     36081,     35751 },     //index = 07 
            {    5625,     37140,     36773,     36558,     36233,     35961,     35645,     35360 },     //index = 08 
            {    5138,     36767,     36361,     36187,     35897,     35562,     35332,     35012 },     //index = 09 
            {    4655,     36360,     36011,     35805,     35528,     35211,     34981,     34676 },     //index = 10 
            {    4169,     36101,     35789,     35535,     35254,     34958,     34698,     34418 },     //index = 11 
            {    3682,     35916,     35620,     35356,     35097,     34802,     34545,     34229 },     //index = 12 
            {    3195,     35765,     35466,     35200,     34919,     34643,     34386,     34068 },     //index = 13 
            {    2708,     35611,     35297,     35059,     34758,     34453,     34261,     33902 },     //index = 14 
            {    2221,     35450,     35149,     34893,     34586,     34308,     34050,     33717 },     //index = 15 
            {    1734,     35250,     34931,     34658,     34387,     34123,     33825,     33477 },     //index = 16 
            {    1251,     34942,     34565,     34317,     34033,     33704,     33477,     33107 },     //index = 17 
            {    763 ,     34430,     34048,     33789,     33460,     33151,     32883,     32576 },     //index = 18 
            {    276 ,     33922,     33526,     33233,     32918,     32575,     32289,     31844 },     //index = 19 
            {    0   ,     30368,     30679,     30895,     31105,     31386,     31148,     31844 }      //index = 20     
    },


    {// 4th Dim
        ////////////// RESIDUAL CAPACITY  at 60 degrees ////////////////////////////////////////////////////////////////////
        //     Capacity,     1st mV  2nd mV     3rd mV      4th mV    5th mV      6th mV     7th mV
        //  7.8Ah三並聯,  DSG  3A,   DSG 5A,    DSG 7A,     DSG 9A,   DSG 11.2A,  DSG 13A,   DSG 15A,
        // 10.4Ah四並聯,  DSG  4A,   DSG 6.7A,  DSG 9.3A,   DSG 12A,  DSG 14.9A,  DSG 17.3A, DSG 20A,
        //    cap*100,  DSG 0.384C, DSG 0.641C, DSG 0.89C, DSG1.153C, DSG 1.435C, DSG1.666C, DSG 1.923C //////////////////
        {    9519,     41483,     41176,     40872,     40625,     40271,     39998,     39685 },      //index = 00 
        {    9038,     40753,     40454,     40170,     39891,     39527,     39285,     38973 },      //index = 01 
        {    8558,     40135,     39825,     39538,     39230,     38882,     38607,     38329 },      //index = 02 
        {    8076,     39546,     39255,     38930,     38665,     38316,     38047,     37734 },      //index = 03 
        {    7595,     39011,     38698,     38401,     38088,     37767,     37465,     37133 },      //index = 04 
        {    7114,     38488,     38179,     37884,     37564,     37208,     36926,     36611 },      //index = 05 
        {    6633,     38008,     37686,     37363,     37077,     36792,     36426,     36112 },      //index = 06 
        {    6152,     37545,     37229,     36908,     36607,     36256,     35963,     35704 },      //index = 07 
        {    5670,     37156,     36855,     36511,     36244,     35860,     35610,     35262 },      //index = 08 
        {    5188,     36813,     36494,     36190,     35897,     35549,     35227,     34921 },      //index = 09 
        {    4707,     36389,     36080,     35830,     35487,     35151,     34872,     34610 },      //index = 10 
        {    4226,     36109,     35822,     35522,     35221,     34884,     34632,     34339 },      //index = 11 
        {    3745,     35943,     35635,     35347,     35045,     34701,     34418,     34115 },      //index = 12 
        {    3264,     35797,     35489,     35186,     34891,     34550,     34299,     33961 },      //index = 13 
        {    2783,     35654,     35375,     35045,     34749,     34413,     34121,     33853 },      //index = 14 
        {    2301,     35488,     35198,     34907,     34577,     34231,     33942,     33639 },      //index = 15 
        {    1819,     35160,     34859,     34562,     34243,     33917,     33666,     33333 },      //index = 16 
        {    1338,     34846,     34553,     34219,     33915,     33586,     33263,     33013 },      //index = 17 
        {    857 ,     34371,     34100,     33752,     33459,     33061,     32758,     32470 },      //index = 18 
        {    374 ,     33931,     33626,     33266,     32975,     32610,     32269,     31958 },      //index = 19
        {    0   ,     30362,     30707,     30883,     31085,     31387,     31592,     31387 }       //index = 20
    }

};

#define CHG_OCV_TABLE_POINTS 51
#define NUM_OF_OCV_CHG_LINE  3
#define TERMINAL_VOLTAGE_INDEX 0
#define RESIDUAL_OCV_CAPACITY_INDEX 1
#define RESIDUAL_CHG_1st_CAPACITY_INDEX 2
#define RESIDUAL_CHG_2nd_CAPACITY_INDEX 3


const int RealOCVTable[OCV_TABLE_POINTS][NUM_OF_OCV_LINE+1] =

{
////////////// RESIDUAL CAPACITY /////////////////////////////////////////////////////////
//            OCV       1nd      2st     3rd     1nd      2st
//cell(mV),     OCV,   CHG0.2C, CHG0.7C,     ///////////////////
    { 4200,   10000,    9723,    8811  },   //index = 00
    { 4176,    9824,    9533,    8556  },   //index = 01
    { 4152,    9651,    9350,    8361  },   //index = 02
    { 4128,    9479,    9160,    8161  },   //index = 03
    { 4104,    9280,    8966,    7956  },   //index = 04
    { 4080,    9082,    8765,    7744  },   //index = 05
    { 4056,    8883,    8560,    7527  },   //index = 06
    { 4032,    8684,    8347,    7303  },   //index = 07
    { 4008,    8479,    8130,    7073  },   //index = 08
    { 3984,    8260,    7907,    6834  },   //index = 09
    { 3960,    8040,    7677,    6583  },   //index = 10
    { 3936,    7816,    7442,    6319  },   //index = 11
    { 3912,    7591,    7200,    6037  },   //index = 12
    { 3888,    7364,    6946,    5725  },   //index = 13
    { 3864,    7120,    6678,    5372  },   //index = 14
    { 3840,    6880,    6391,    4948  },   //index = 15
    { 3816,    6626,    6087,    4428  },   //index = 16
    { 3792,    6375,    5746,    3801  },   //index = 17
    { 3768,    6096,    5339,    3173  },   //index = 18
    { 3744,    5831,    5004,    2566  },   //index = 19
    { 3720,    5603,    4633,    1932  },   //index = 20
    { 3696,    5373,    4073,    1502  },   //index = 21
    { 3672,    5074,    3359,    1218  },   //index = 22
    { 3648,    4662,    2567,     943  },   //index = 23
    { 3624,    3975,    1927,     636  },   //index = 24
    { 3600,    3141,    1542,     348  },   //index = 25
    { 3576,    2355,    1297,     107  },   //index = 26 
    { 3552,    1978,    1075,      56  },   //index = 27
    { 3528,    1720,     850,      27  },   //index = 28
    { 3504,    1523,     530,       7  },   //index = 29 
    { 3480,    1342,     159,       0  },   //index = 30
    { 3456,    1041,      44,       0  },   //index = 31
    { 3432,     627,       9,       0  },   //index = 32 
    { 3408,     451,       0,       0  },   //index = 33
    { 3384,     357,       0,       0  },   //index = 34
    { 3360,     264,       0,       0  },   //index = 35 
    { 3336,     244,       0,       0  },   //index = 36
    { 3312,     231,       0,       0  },   //index = 37
    { 3288,     218,       0,       0  },   //index = 38 
    { 3264,     205,       0,       0  },   //index = 39
    { 3240,     192,       0,       0  },   //index = 40
    { 3216,     179,       0,       0  },   //index = 41 
    { 3192,     166,       0,       0  },   //index = 42
    { 3168,     153,       0,       0  },   //index = 43
    { 3144,     140,       0,       0  },   //index = 44 
    { 3120,     127,       0,       0  },   //index = 45
    { 3096,     114,       0,       0  },   //index = 46
    { 3072,     101,       0,       0  },   //index = 47 
    { 3048,      88,       0,       0  },   //index = 48
    { 3024,      74,       0,       0  },   //index = 49
    { 3000,      61,       0,       0  }    //index = 50 
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
                                                              
                                                              
