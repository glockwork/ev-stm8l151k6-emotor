



#define Static_OCV_TABLE_POINTS 41
#define Static_OCV_LINE  1

#define RESIDUAL_Static_CAPACITY_INDEX     0
#define RESIDUAL_Static_CURRENT_INDEX  1

const unsigned int Static_OCVTable[Static_OCV_TABLE_POINTS][Static_OCV_LINE+1] =
{
        //// RESIDUAL CAPACITY  OCV (Static Status)  ///////////
        //     Capacity,       OCV
        //  5.2Ah 二並聯,      
        //  7.8Ah 三並聯,      
        ////////////////////////////////////////////////////////
        //Current-5.2Ah, 2P    OCV
        //Current-7.8Ah, 3P    
        //  SOC%,              Pack V, 
        ////////////////////////////////////////////////////////
        {    10000   ,         29295   },    // index = 00
        {    9750    ,         29090   },    // index = 01
        {    9500    ,         28885   },    // index = 02
        {    9250    ,         28714   },    // index = 03
        {    9000    ,         28536   },    // index = 04
        {    8750    ,         28371   },    // index = 05
        {    8500    ,         28207   },    // index = 06
        {    8250    ,         28061   },    // index = 07
        {    8000    ,         27912   },    // index = 08
        {    7750    ,         27778   },    // index = 09
        {    7500    ,         27648   },    // index = 10
        {    7250    ,         27529   },    // index = 11
        {    7000    ,         27413   },    // index = 12
        {    6750    ,         27311   },    // index = 13
        {    6500    ,         27211   },    // index = 14
        {    6250    ,         27138   },    // index = 15
        {    6000    ,         27035   },    // index = 16
        {    5750    ,         26933   },    // index = 17
        {    5500    ,         26743   },    // index = 18
        {    5250    ,         26635   },    // index = 19
        {    5000    ,         26527   },    // index = 20
        {    4750    ,         26486   },    // index = 21
        {    4500    ,         26437   },    // index = 22
        {    4250    ,         26420   },    // index = 23
        {    4000    ,         26398   },    // index = 24
        {    3750    ,         26387   },    // index = 25
        {    3500    ,         26369   },    // index = 26
        {    3250    ,         26354   },    // index = 27
        {    3000    ,         26331   },    // index = 28
        {    2750    ,         26290   },    // index = 29
        {    2500    ,         26231   },    // index = 30
        {    2250    ,         26128   },    // index = 31
        {    2000    ,         25983   },    // index = 32
        {    1750    ,         25786   },    // index = 33
        {    1500    ,         25494   },    // index = 34
        {    1250    ,         25276   },    // index = 35
        {    1000    ,         25000   },    // index = 36
        {    750     ,         24858   },    // index = 37
        {    500     ,         24613   },    // index = 38
        {    250     ,         24187   },    // index = 39
        {    0       ,         21000   }     // index = 40
};