



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
        {    10000   ,         41822    },    // index = 00
        {    9750    ,         41654    },    // index = 01
        {    9500    ,         41308    },    // index = 02
        {    9250    ,         41003    },    // index = 03
        {    9000    ,         40701    },    // index = 04
        {    8750    ,         40399    },    // index = 05
        {    8500    ,         40105    },    // index = 06
        {    8250    ,         39829    },    // index = 07
        {    8000    ,         39556    },    // index = 08
        {    7750    ,         39291    },    // index = 09
        {    7500    ,         39020    },    // index = 10
        {    7250    ,         38769    },    // index = 11
        {    7000    ,         38518    },    // index = 12
        {    6750    ,         38278    },    // index = 13
        {    6500    ,         38038    },    // index = 14
        {    6250    ,         37813    },    // index = 15
        {    6000    ,         37598    },    // index = 16
        {    5750    ,         37355    },    // index = 17
        {    5500    ,         37091    },    // index = 18
        {    5250    ,         36860    },    // index = 19
        {    5000    ,         36665    },    // index = 20
        {    4750    ,         36518    },    // index = 21
        {    4500    ,         36415    },    // index = 22
        {    4250    ,         36326    },    // index = 23
        {    4000    ,         36248    },    // index = 24
        {    3750    ,         36174    },    // index = 25
        {    3500    ,         36105    },    // index = 26
        {    3250    ,         36034    },    // index = 27
        {    3000    ,         35956    },    // index = 28
        {    2750    ,         35886    },    // index = 29
        {    2500    ,         35823    },    // index = 30
        {    2250    ,         35704    },    // index = 31
        {    2000    ,         35538    },    // index = 32
        {    1750    ,         35316    },    // index = 33
        {    1500    ,         35010    },    // index = 34
        {    1250    ,         34699    },    // index = 35
        {    1000    ,         34537    },    // index = 36
        {    750     ,         34407    },    // index = 37
        {    500     ,         34207    },    // index = 38
        {    250     ,         33473    },    // index = 39
        {    0       ,         29000    }     // index = 40
};