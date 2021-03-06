
#define CHG_OCV_TABLE_POINTS 41
#define CHG_NUM_OF_OCV_LINE  3

#define RESIDUAL_CHG_CAPACITY_INDEX     0
#define RESIDUAL_CHG_1st_Degrees_INDEX  1
#define RESIDUAL_CHG_2nd_Degrees_INDEX  2
#define RESIDUAL_CHG_3rd_Degrees_INDEX  3



const unsigned int CHG_OCVTable[CHG_OCV_TABLE_POINTS][CHG_NUM_OF_OCV_LINE+1] =
{
        ////////////// (10S 3P) RESIDUAL CAPACITY  at 2A CHG    //////////////////////////
        //     Capacity,        1st mV              2nd mV            3rd mV        
        //  7.8Ah�T���p,        CHG 5 Degrees,      CHG 15 degrees,   CHG 25 degrees
        /////////////////////////////////////////////////////////////////////////////////
        //Current-7.8Ah,3P       CHG 5 Degrees,     CHG 15 degrees,   CHG 25 degrees
        //  SOC%,                 Pack V,           Pack V,           Pack V
        /////////////////////////////////////////////////////////////////////////////////
        {    10000   ,           41964,            41950,             41936    },    // index = 00 
        {    9750    ,           41804,            41782,             41760    },    // index = 01 
        {    9500    ,           41807,            41791,             41775    },    // index = 02 
        {    9250    ,           41836,            41759,             41682    },    // index = 03 
        {    9000    ,           41806,            41692,             41579    },    // index = 04 
        {    8750    ,           41780,            41552,             41324    },    // index = 05 
        {    8500    ,           41658,            41368,             41078    },    // index = 06 
        {    8250    ,           41463,            41149,             40835    },    // index = 07 
        {    8000    ,           41309,            40970,             40630    },    // index = 08 
        {    7750    ,           41167,            40801,             40436    },    // index = 09 
        {    7500    ,           41048,            40657,             40266    },    // index = 10 
        {    7250    ,           40928,            40514,             40100    },    // index = 11 
        {    7000    ,           40838,            40404,             39969    },    // index = 12 
        {    6750    ,           40748,            40296,             39844    },    // index = 13 
        {    6500    ,           40681,            40215,             39749    },    // index = 14 
        {    6250    ,           40625,            40148,             39671    },    // index = 15 
        {    6000    ,           40500,            40015,             39530    },    // index = 16 
        {    5750    ,           40496,            40005,             39514    },    // index = 17 
        {    5500    ,           40429,            39929,             39428    },    // index = 18 
        {    5250    ,           40451,            39930,             39409    },    // index = 19 
        {    5000    ,           40407,            39870,             39333    },    // index = 20 
        {    4750    ,           40398,            39854,             39310    },    // index = 21 
        {    4500    ,           40336,            39789,             39242    },    // index = 22 
        {    4250    ,           40289,            39740,             39191    },    // index = 23 
        {    4000    ,           40234,            39682,             39130    },    // index = 24 
        {    3750    ,           40194,            39638,             39082    },    // index = 25 
        {    3500    ,           40161,            39599,             39037    },    // index = 26 
        {    3250    ,           40131,            39559,             38988    },    // index = 27 
        {    3000    ,           40090,            39507,             38925    },    // index = 28 
        {    2750    ,           40048,            39454,             38861    },    // index = 29 
        {    2500    ,           39950,            39354,             38758    },    // index = 30 
        {    2250    ,           39840,            39284,             38728    },    // index = 31 
        {    2000    ,           39400,            38972,             38545    },    // index = 32 
        {    1750    ,           38740,            38451,             38161    },    // index = 33 
        {    1500    ,           37965,            37684,             37403    },    // index = 34 
        {    1250    ,           37628,            37301,             36975    },    // index = 35 
        {    1000    ,           37247,            36887,             36527    },    // index = 36 
        {    750     ,           37020,            36628,             36236    },    // index = 37 
        {    500     ,           36499,            36037,             35575    },    // index = 38 
        {    250     ,           35856,            35329,             34803    },    // index = 39 
        {    0       ,           30000,            30000,             30000    }     // index = 40 
};