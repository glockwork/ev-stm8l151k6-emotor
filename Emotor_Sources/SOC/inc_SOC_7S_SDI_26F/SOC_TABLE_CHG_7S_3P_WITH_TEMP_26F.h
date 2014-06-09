
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
        //  7.8Ah�T���p,        CHG 5 Degrees,      CHG 15 degrees,   CHG 25 degrees
        /////////////////////////////////////////////////////////////////////////////////
        //Current-7.8Ah,3P       CHG 5 Degrees,     CHG 15 degrees,   CHG 25 degrees
        //  SOC%,                 Pack V,           Pack V,           Pack V
        /////////////////////////////////////////////////////////////////////////////////
        {    10000   ,           29355,            29345,             29336    },    // index = 00 
        {    9750    ,           29331,            29316,             29300    },    // index = 01 
        {    9500    ,           29296,            29284,             29273    },    // index = 02 
        {    9250    ,           29274,            29220,             29166    },    // index = 03 
        {    9000    ,           29219,            29139,             29060    },    // index = 04 
        {    8750    ,           29154,            28995,             28835    },    // index = 05 
        {    8500    ,           29027,            28824,             28621    },    // index = 06 
        {    8250    ,           28843,            28624,             28404    },    // index = 07 
        {    8000    ,           28694,            28456,             28219    },    // index = 08 
        {    7750    ,           28617,            28409,             28201    },    // index = 09 
        {    7500    ,           28526,            28304,             28082    },    // index = 10 
        {    7250    ,           28439,            28210,             27980    },    // index = 11 
        {    7000    ,           28365,            28123,             27882    },    // index = 12 
        {    6750    ,           28292,            28045,             27799    },    // index = 13 
        {    6500    ,           28225,            27972,             27719    },    // index = 14 
        {    6250    ,           28171,            27910,             27649    },    // index = 15 
        {    6000    ,           28106,            27845,             27584    },    // index = 16 
        {    5750    ,           28052,            27787,             27522    },    // index = 17 
        {    5500    ,           27993,            27722,             27452    },    // index = 18 
        {    5250    ,           27936,            27655,             27373    },    // index = 19 
        {    5000    ,           27887,            27598,             27308    },    // index = 20 
        {    4750    ,           27839,            27550,             27260    },    // index = 21 
        {    4500    ,           27799,            27507,             27215    },    // index = 22 
        {    4250    ,           27761,            27470,             27178    },    // index = 23 
        {    4000    ,           27729,            27436,             27142    },    // index = 24 
        {    3750    ,           27701,            27405,             27110    },    // index = 25 
        {    3500    ,           27678,            27382,             27086    },    // index = 26 
        {    3250    ,           27662,            27359,             27056    },    // index = 27 
        {    3000    ,           27650,            27342,             27033    },    // index = 28 
        {    2750    ,           27639,            27326,             27012    },    // index = 29 
        {    2500    ,           27608,            27297,             26985    },    // index = 30 
        {    2250    ,           27511,            27219,             26928    },    // index = 31 
        {    2000    ,           27223,            26996,             26770    },    // index = 32 
        {    1750    ,           26755,            26587,             26420    },    // index = 33 
        {    1500    ,           26332,            26147,             25961    },    // index = 34 
        {    1250    ,           25994,            25804,             25613    },    // index = 35 
        {    1000    ,           25779,            25571,             25364    },    // index = 36 
        {    750     ,           25621,            25397,             25174    },    // index = 37 
        {    500     ,           25540,            25277,             25013    },    // index = 38 
        {    250     ,           24873,            24501,             24129    },    // index = 39 
        {    0       ,           21000,            21000,             21000    }     // index = 40 
};