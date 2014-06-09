
#define CHG_OCV_TABLE_POINTS 41
#define CHG_NUM_OF_OCV_LINE  3

#define RESIDUAL_CHG_CAPACITY_INDEX     0
#define RESIDUAL_CHG_1st_Degrees_INDEX  1
#define RESIDUAL_CHG_2nd_Degrees_INDEX  2
#define RESIDUAL_CHG_3rd_Degrees_INDEX  3



const unsigned int CHG_OCVTable[CHG_OCV_TABLE_POINTS][CHG_NUM_OF_OCV_LINE+1] =
{
        //////////////  (7S 3P) RESIDUAL CAPACITY  at 2A CHG    //////////////////////////
        //     Capacity,        1st mV              2nd mV            3rd mV        
        // 10.0Ah�|���p,        CHG 5 Degrees,      CHG 15 degrees,   CHG 25 degrees
        /////////////////////////////////////////////////////////////////////////////////
        //Current-10Ah,4P       CHG 5 Degrees,     CHG 15 degrees,   CHG 25 degrees
        //  SOC%,                 Pack V,           Pack V,           Pack V
        /////////////////////////////////////////////////////////////////////////////////
        {    10000   ,           29355,            29345,             29336    },    // index = 00 
        {    9750    ,           29210,            29203,             29195    },    // index = 01 
        {    9500    ,           29090,            29085,             29079    },    // index = 02 
        {    9250    ,           28994,            28967,             28940    },    // index = 03 
        {    9000    ,           28878,            28838,             28798    },    // index = 04 
        {    8750    ,           28763,            28683,             28603    },    // index = 05 
        {    8500    ,           28617,            28515,             28414    },    // index = 06 
        {    8250    ,           28452,            28342,             28232    },    // index = 07 
        {    8000    ,           28303,            28184,             28065    },    // index = 08 
        {    7750    ,           28197,            28094,             27990    },    // index = 09 
        {    7500    ,           28087,            27976,             27865    },    // index = 10 
        {    7250    ,           27984,            27869,             27754    },    // index = 11 
        {    7000    ,           27889,            27768,             27647    },    // index = 12 
        {    6750    ,           27801,            27678,             27555    },    // index = 13 
        {    6500    ,           27718,            27591,             27465    },    // index = 14 
        {    6250    ,           27655,            27524,             27393    },    // index = 15 
        {    6000    ,           27571,            27440,             27310    },    // index = 16 
        {    5750    ,           27492,            27360,             27228    },    // index = 17 
        {    5500    ,           27368,            27233,             27097    },    // index = 18 
        {    5250    ,           27286,            27145,             27004    },    // index = 19 
        {    5000    ,           27207,            27062,             26917    },    // index = 20 
        {    4750    ,           27163,            27018,             26873    },    // index = 21 
        {    4500    ,           27118,            26972,             26826    },    // index = 22 
        {    4250    ,           27091,            26945,             26799    },    // index = 23 
        {    4000    ,           27064,            26917,             26770    },    // index = 24 
        {    3750    ,           27044,            26896,             26749    },    // index = 25 
        {    3500    ,           27024,            26876,             26727    },    // index = 26 
        {    3250    ,           27008,            26857,             26705    },    // index = 27 
        {    3000    ,           26991,            26836,             26682    },    // index = 28 
        {    2750    ,           26964,            26808,             26651    },    // index = 29 
        {    2500    ,           26919,            26764,             26608    },    // index = 30 
        {    2250    ,           26819,            26674,             26528    },    // index = 31 
        {    2000    ,           26603,            26490,             26376    },    // index = 32 
        {    1750    ,           26270,            26187,             26103    },    // index = 33 
        {    1500    ,           25913,            25821,             25728    },    // index = 34 
        {    1250    ,           25635,            25540,             25444    },    // index = 35 
        {    1000    ,           25389,            25285,             25182    },    // index = 36 
        {    750     ,           25240,            25128,             25016    },    // index = 37 
        {    500     ,           25076,            24945,             24813    },    // index = 38 
        {    250     ,           24530,            24344,             24158    },    // index = 39 
        {    0       ,           21000,            21000,             21000    }     // index = 40 
};