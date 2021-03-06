

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
        {    10000   ,           54527,            54531,             54534    },    // index = 00 
        {    9750    ,           54272,            54259,             54246    },    // index = 01 
        {    9500    ,           54098,            54062,             54026    },    // index = 02 
        {    9250    ,           53942,            53882,             53821    },    // index = 03 
        {    9000    ,           53784,            53695,             53607    },    // index = 04 
        {    8750    ,           53641,            53463,             53285    },    // index = 05 
        {    8500    ,           53422,            53195,             52969    },    // index = 06 
        {    8250    ,           53156,            52911,             52666    },    // index = 07 
        {    8000    ,           52924,            52659,             52395    },    // index = 08 
        {    7750    ,           52712,            52427,             52142    },    // index = 09 
        {    7500    ,           52522,            52217,             51913    },    // index = 10 
        {    7250    ,           52336,            52014,             51691    },    // index = 11 
        {    7000    ,           52180,            51841,             51503    },    // index = 12 
        {    6750    ,           52033,            51681,             51328    },    // index = 13 
        {    6500    ,           51909,            51545,             51182    },    // index = 14 
        {    6250    ,           51810,            51438,             51066    },    // index = 15 
        {    6000    ,           51628,            51250,             50872    },    // index = 16 
        {    5750    ,           51546,            51163,             50780    },    // index = 17 
        {    5500    ,           51357,            50967,             50576    },    // index = 18 
        {    5250    ,           51302,            50896,             50489    },    // index = 19 
        {    5000    ,           51200,            50781,             50362    },    // index = 20 
        {    4750    ,           51173,            50749,             50324    },    // index = 21 
        {    4500    ,           51091,            50665,             50238    },    // index = 22 
        {    4250    ,           51045,            50617,             50188    },    // index = 23 
        {    4000    ,           50988,            50557,             50127    },    // index = 24 
        {    3750    ,           50949,            50516,             50082    },    // index = 25 
        {    3500    ,           50912,            50473,             50035    },    // index = 26 
        {    3250    ,           50875,            50429,             49983    },    // index = 27 
        {    3000    ,           50820,            50365,             49911    },    // index = 28 
        {    2750    ,           50743,            50280,             49817    },    // index = 29 
        {    2500    ,           50604,            50140,             49675    },    // index = 30 
        {    2250    ,           50432,            49998,             49564    },    // index = 31 
        {    2000    ,           49977,            49644,             49310    },    // index = 32 
        {    1750    ,           49311,            49085,             48860    },    // index = 33 
        {    1500    ,           48500,            48281,             48061    },    // index = 34 
        {    1250    ,           48110,            47855,             47600    },    // index = 35 
        {    1000    ,           47618,            47337,             47057    },    // index = 36 
        {    750     ,           47323,            47017,             46712    },    // index = 37 
        {    500     ,           46634,            46274,             45914    },    // index = 38 
        {    250     ,           45740,            45329,             44919    },    // index = 39 
        {    0       ,           39000,            39000,             39000    }     // index = 40 
};