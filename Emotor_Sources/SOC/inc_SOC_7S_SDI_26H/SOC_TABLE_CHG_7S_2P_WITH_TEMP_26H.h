

#define CHG_OCV_TABLE_POINTS 41
#define CHG_NUM_OF_OCV_LINE  3

#define RESIDUAL_CHG_CAPACITY_INDEX     0
#define RESIDUAL_CHG_1st_Degrees_INDEX  1
#define RESIDUAL_CHG_2nd_Degrees_INDEX  2
#define RESIDUAL_CHG_3rd_Degrees_INDEX  3



const unsigned int CHG_OCVTable[CHG_OCV_TABLE_POINTS][CHG_NUM_OF_OCV_LINE+1] =
{
        ////////////// (7S 2P) RESIDUAL CAPACITY  at 2A CHG    //////////////////////////
        //     Capacity,        1st mV              2nd mV            3rd mV        
        //  5.2Ah�G���p,        CHG 5 Degrees,     CHG 15 degrees,   CHG 25 degrees
        /////////////////////////////////////////////////////////////////////////////////
        //Current-5.2Ah,2P      CHG 5 Degrees,     CHG 15 degrees,   CHG 25 degrees
        //  SOC%,                 Pack V,           Pack V,           Pack V
        /////////////////////////////////////////////////////////////////////////////////
        {    10000   ,           29395,            29380,             29366    },    // index = 00 
        {    9750    ,           29377,            29364,             29351    },    // index = 01 
        {    9500    ,           29357,            29339,             29322    },    // index = 02 
        {    9250    ,           29330,            29314,             29298    },    // index = 03 
        {    9000    ,           29313,            29278,             29244    },    // index = 04 
        {    8750    ,           29282,            29197,             29113    },    // index = 05 
        {    8500    ,           29254,            29074,             28895    },    // index = 06 
        {    8250    ,           29225,            28946,             28666    },    // index = 07 
        {    8000    ,           29196,            28840,             28483    },    // index = 08 
        {    7750    ,           29062,            28678,             28294    },    // index = 09 
        {    7500    ,           28942,            28531,             28121    },    // index = 10 
        {    7250    ,           28820,            28385,             27950    },    // index = 11 
        {    7000    ,           28723,            28267,             27811    },    // index = 12 
        {    6750    ,           28614,            28139,             27665    },    // index = 13 
        {    6500    ,           28525,            28035,             27546    },    // index = 14 
        {    6250    ,           28418,            27917,             27416    },    // index = 15 
        {    6000    ,           28291,            27782,             27272    },    // index = 16 
        {    5750    ,           28270,            27755,             27239    },    // index = 17 
        {    5500    ,           28300,            27774,             27249    },    // index = 18 
        {    5250    ,           28323,            27775,             27228    },    // index = 19 
        {    5000    ,           28304,            27740,             27175    },    // index = 20 
        {    4750    ,           28251,            27680,             27109    },    // index = 21 
        {    4500    ,           28188,            27614,             27040    },    // index = 22 
        {    4250    ,           28102,            27525,             26948    },    // index = 23 
        {    4000    ,           28022,            27442,             26863    },    // index = 24 
        {    3750    ,           27944,            27360,             26777    },    // index = 25 
        {    3500    ,           27889,            27299,             26708    },    // index = 26 
        {    3250    ,           27830,            27230,             26630    },    // index = 27 
        {    3000    ,           27767,            27155,             26543    },    // index = 28 
        {    2750    ,           27737,            27113,             26489    },    // index = 29 
        {    2500    ,           27677,            27051,             26426    },    // index = 30 
        {    2250    ,           27633,            27049,             26465    },    // index = 31 
        {    2000    ,           27273,            26824,             26375    },    // index = 32 
        {    1750    ,           26719,            26415,             26111    },    // index = 33 
        {    1500    ,           26128,            25833,             25538    },    // index = 34 
        {    1250    ,           25885,            25542,             25199    },    // index = 35 
        {    1000    ,           25786,            25408,             25030    },    // index = 36 
        {    750     ,           25669,            25257,             24846    },    // index = 37 
        {    500     ,           25349,            24864,             24380    },    // index = 38 
        {    250     ,           24799,            24246,             23694    },    // index = 39 
        {    0       ,           21000,            21000,             21000    }     // index = 40 
};