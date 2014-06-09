



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
        {    10000   ,         20925   },    // index = 00
        {    9750    ,         20779   },    // index = 01
        {    9500    ,         20632   },    // index = 02
        {    9250    ,         20510   },    // index = 03
        {    9000    ,         20383   },    // index = 04
        {    8750    ,         20265   },    // index = 05
        {    8500    ,         20148   },    // index = 06
        {    8250    ,         20043   },    // index = 07
        {    8000    ,         19937   },    // index = 08
        {    7750    ,         19841   },    // index = 09
        {    7500    ,         19749   },    // index = 10
        {    7250    ,         19663   },    // index = 11
        {    7000    ,         19581   },    // index = 12
        {    6750    ,         19508   },    // index = 13
        {    6500    ,         19436   },    // index = 14
        {    6250    ,         19384   },    // index = 15
        {    6000    ,         19311   },    // index = 16
        {    5750    ,         19238   },    // index = 17
        {    5500    ,         19102   },    // index = 18
        {    5250    ,         19025   },    // index = 19
        {    5000    ,         18948   },    // index = 20
        {    4750    ,         18919   },    // index = 21
        {    4500    ,         18883   },    // index = 22
        {    4250    ,         18872   },    // index = 23
        {    4000    ,         18856   },    // index = 24
        {    3750    ,         18848   },    // index = 25
        {    3500    ,         18835   },    // index = 26
        {    3250    ,         18824   },    // index = 27
        {    3000    ,         18808   },    // index = 28
        {    2750    ,         18778   },    // index = 29
        {    2500    ,         18736   },    // index = 30
        {    2250    ,         18663   },    // index = 31
        {    2000    ,         18559   },    // index = 32
        {    1750    ,         18419   },    // index = 33
        {    1500    ,         18210   },    // index = 34
        {    1250    ,         18054   },    // index = 35
        {    1000    ,         17857   },    // index = 36
        {    750     ,         17756   },    // index = 37
        {    500     ,         17581   },    // index = 38
        {    250     ,         17276   },    // index = 39
        {    0       ,         15000   }     // index = 40
};