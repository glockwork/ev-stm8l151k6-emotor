
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
        {    10000   ,           54553,            54535,             54517    },    // index = 00 
        {    9750    ,           54345,            54317,             54288    },    // index = 01 
        {    9500    ,           54349,            54328,             54307    },    // index = 02 
        {    9250    ,           54387,            54287,             54186    },    // index = 03 
        {    9000    ,           54348,            54200,             54053    },    // index = 04 
        {    8750    ,           54315,            54018,             53721    },    // index = 05 
        {    8500    ,           54156,            53779,             53402    },    // index = 06 
        {    8250    ,           53901,            53493,             53086    },    // index = 07 
        {    8000    ,           53701,            53260,             52819    },    // index = 08 
        {    7750    ,           53517,            53042,             52566    },    // index = 09 
        {    7500    ,           53362,            52854,             52346    },    // index = 10 
        {    7250    ,           53207,            52669,             52131    },    // index = 11 
        {    7000    ,           53089,            52525,             51960    },    // index = 12 
        {    6750    ,           52972,            52385,             51797    },    // index = 13 
        {    6500    ,           52885,            52279,             51673    },    // index = 14 
        {    6250    ,           52812,            52192,             51572    },    // index = 15 
        {    6000    ,           52650,            52020,             51389    },    // index = 16 
        {    5750    ,           52645,            52007,             51368    },    // index = 17 
        {    5500    ,           52558,            51907,             51256    },    // index = 18 
        {    5250    ,           52587,            51909,             51232    },    // index = 19 
        {    5000    ,           52530,            51831,             51133    },    // index = 20 
        {    4750    ,           52517,            51810,             51103    },    // index = 21 
        {    4500    ,           52436,            51725,             51014    },    // index = 22 
        {    4250    ,           52376,            51662,             50948    },    // index = 23 
        {    4000    ,           52304,            51587,             50870    },    // index = 24 
        {    3750    ,           52252,            51530,             50807    },    // index = 25 
        {    3500    ,           52210,            51479,             50748    },    // index = 26 
        {    3250    ,           52170,            51427,             50684    },    // index = 27 
        {    3000    ,           52117,            51360,             50602    },    // index = 28 
        {    2750    ,           52063,            51291,             50519    },    // index = 29 
        {    2500    ,           51934,            51160,             50386    },    // index = 30 
        {    2250    ,           51792,            51069,             50346    },    // index = 31 
        {    2000    ,           51220,            50664,             50108    },    // index = 32 
        {    1750    ,           50362,            49986,             49610    },    // index = 33 
        {    1500    ,           49354,            48989,             48623    },    // index = 34 
        {    1250    ,           48917,            48492,             48067    },    // index = 35 
        {    1000    ,           48421,            47953,             47485    },    // index = 36 
        {    750     ,           48126,            47616,             47107    },    // index = 37 
        {    500     ,           47449,            46848,             46248    },    // index = 38 
        {    250     ,           46613,            45928,             45244    },    // index = 39 
        {    0       ,           39000,            39000,             39000    }     // index = 40 
};