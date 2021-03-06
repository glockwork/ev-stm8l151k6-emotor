

#define CHG_OCV_TABLE_POINTS 41
#define CHG_NUM_OF_OCV_LINE  3

#define RESIDUAL_CHG_CAPACITY_INDEX     0
#define RESIDUAL_CHG_1st_Degrees_INDEX  1
#define RESIDUAL_CHG_2nd_Degrees_INDEX  2
#define RESIDUAL_CHG_3rd_Degrees_INDEX  3



const unsigned int CHG_OCVTable[CHG_OCV_TABLE_POINTS][CHG_NUM_OF_OCV_LINE+1] =
{
        ////////////// (10S 4P) RESIDUAL CAPACITY  at 2A CHG    //////////////////////////
        //     Capacity,        1st mV              2nd mV            3rd mV        
        //  10.4Ah�|���p,        CHG 5 Degrees,     CHG 15 degrees,   CHG 25 degrees
        /////////////////////////////////////////////////////////////////////////////////
        //Current-10.4Ah,4P      CHG 5 Degrees,     CHG 15 degrees,   CHG 25 degrees
        //  SOC%,                 Pack V,           Pack V,           Pack V
        /////////////////////////////////////////////////////////////////////////////////
        {    10000   ,           41901,            41910,             41918    },    // index = 00 
        {    9750    ,           41948,            41936,             41923    },    // index = 01 
        {    9500    ,           41814,            41780,             41745    },    // index = 02 
        {    9250    ,           41674,            41616,             41558    },    // index = 03 
        {    9000    ,           41547,            41457,             41366    },    // index = 04 
        {    8750    ,           41402,            41231,             41060    },    // index = 05 
        {    8500    ,           41193,            40975,             40757    },    // index = 06 
        {    8250    ,           40947,            40706,             40464    },    // index = 07 
        {    8000    ,           40715,            40462,             40208    },    // index = 08 
        {    7750    ,           40498,            40220,             39941    },    // index = 09 
        {    7500    ,           40275,            39983,             39691    },    // index = 10 
        {    7250    ,           40077,            39764,             39451    },    // index = 11 
        {    7000    ,           39878,            39554,             39230    },    // index = 12 
        {    6750    ,           39686,            39346,             39005    },    // index = 13 
        {    6500    ,           39492,            39141,             38791    },    // index = 14 
        {    6250    ,           39310,            38952,             38594    },    // index = 15 
        {    6000    ,           39133,            38769,             38405    },    // index = 16 
        {    5750    ,           39007,            38639,             38271    },    // index = 17 
        {    5500    ,           38883,            38507,             38131    },    // index = 18 
        {    5250    ,           38763,            38373,             37982    },    // index = 19 
        {    5000    ,           38613,            38210,             37808    },    // index = 20 
        {    4750    ,           38474,            38065,             37656    },    // index = 21 
        {    4500    ,           38365,            37956,             37547    },    // index = 22 
        {    4250    ,           38254,            37841,             37428    },    // index = 23 
        {    4000    ,           38152,            37739,             37326    },    // index = 24 
        {    3750    ,           38059,            37641,             37223    },    // index = 25 
        {    3500    ,           37979,            37557,             37136    },    // index = 26 
        {    3250    ,           37907,            37478,             37049    },    // index = 27 
        {    3000    ,           37842,            37405,             36967    },    // index = 28 
        {    2750    ,           37823,            37378,             36932    },    // index = 29 
        {    2500    ,           37799,            37353,             36907    },    // index = 30 
        {    2250    ,           37735,            37321,             36906    },    // index = 31 
        {    2000    ,           37380,            37069,             36759    },    // index = 32 
        {    1750    ,           36900,            36691,             36482    },    // index = 33 
        {    1500    ,           36279,            36076,             35872    },    // index = 34 
        {    1250    ,           35873,            35620,             35367    },    // index = 35 
        {    1000    ,           35703,            35429,             35155    },    // index = 36 
        {    750     ,           35584,            35286,             34989    },    // index = 37 
        {    500     ,           35552,            35204,             34856    },    // index = 38 
        {    250     ,           34962,            34559,             34157    },    // index = 39 
        {    0       ,           29000,            29000,             29000    }     // index = 40 
};