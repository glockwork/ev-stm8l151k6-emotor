



#define Static_OCV_TABLE_POINTS 41
#define Static_OCV_LINE  1

#define RESIDUAL_Static_CAPACITY_INDEX     0
#define RESIDUAL_Static_CURRENT_INDEX  1

const unsigned int Static_OCVTable[Static_OCV_TABLE_POINTS][Static_OCV_LINE+1] =
{
        //// RESIDUAL CAPACITY  OCV (Static Status)  ///////////
        //     Capacity,       OCV
        //  7.8Ah 三並聯,      
        //  10.4Ah四並聯,      
        ////////////////////////////////////////////////////////
        //Current-7.8Ah, 3P    OCV
        //Current-10.4Ah,4P    
        //  SOC%,              Pack V, 
        ////////////////////////////////////////////////////////
        {    10000   ,         41850    },    // index = 00
        {    9750    ,         41557    },    // index = 01
        {    9500    ,         41264    },    // index = 02
        {    9250    ,         41019    },    // index = 03
        {    9000    ,         40766    },    // index = 04
        {    8750    ,         40530    },    // index = 05
        {    8500    ,         40296    },    // index = 06
        {    8250    ,         40087    },    // index = 07
        {    8000    ,         39874    },    // index = 08
        {    7750    ,         39683    },    // index = 09
        {    7500    ,         39498    },    // index = 10
        {    7250    ,         39327    },    // index = 11
        {    7000    ,         39161    },    // index = 12
        {    6750    ,         39015    },    // index = 13
        {    6500    ,         38873    },    // index = 14
        {    6250    ,         38768    },    // index = 15
        {    6000    ,         38622    },    // index = 16
        {    5750    ,         38475    },    // index = 17
        {    5500    ,         38204    },    // index = 18
        {    5250    ,         38050    },    // index = 19
        {    5000    ,         37895    },    // index = 20
        {    4750    ,         37838    },    // index = 21
        {    4500    ,         37767    },    // index = 22
        {    4250    ,         37743    },    // index = 23
        {    4000    ,         37712    },    // index = 24
        {    3750    ,         37696    },    // index = 25
        {    3500    ,         37670    },    // index = 26
        {    3250    ,         37649    },    // index = 27
        {    3000    ,         37616    },    // index = 28
        {    2750    ,         37557    },    // index = 29
        {    2500    ,         37473    },    // index = 30
        {    2250    ,         37326    },    // index = 31
        {    2000    ,         37118    },    // index = 32
        {    1750    ,         36837    },    // index = 33
        {    1500    ,         36421    },    // index = 34
        {    1250    ,         36108    },    // index = 35
        {    1000    ,         35714    },    // index = 36
        {    750     ,         35511    },    // index = 37
        {    500     ,         35161    },    // index = 38
        {    250     ,         34553    },    // index = 39
        {    0       ,         30000    }     // index = 40
};