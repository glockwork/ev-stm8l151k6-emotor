



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
        {    10000   ,         54369   },    // index = 00
        {    9750    ,         54151   },    // index = 01
        {    9500    ,         53700   },    // index = 02
        {    9250    ,         53304   },    // index = 03
        {    9000    ,         52912   },    // index = 04
        {    8750    ,         52518   },    // index = 05
        {    8500    ,         52136   },    // index = 06
        {    8250    ,         51778   },    // index = 07
        {    8000    ,         51423   },    // index = 08
        {    7750    ,         51078   },    // index = 09
        {    7500    ,         50726   },    // index = 10
        {    7250    ,         50400   },    // index = 11
        {    7000    ,         50074   },    // index = 12
        {    6750    ,         49761   },    // index = 13
        {    6500    ,         49449   },    // index = 14
        {    6250    ,         49156   },    // index = 15
        {    6000    ,         48878   },    // index = 16
        {    5750    ,         48561   },    // index = 17
        {    5500    ,         48219   },    // index = 18
        {    5250    ,         47918   },    // index = 19
        {    5000    ,         47665   },    // index = 20
        {    4750    ,         47473   },    // index = 21
        {    4500    ,         47340   },    // index = 22
        {    4250    ,         47224   },    // index = 23
        {    4000    ,         47122   },    // index = 24
        {    3750    ,         47026   },    // index = 25
        {    3500    ,         46937   },    // index = 26
        {    3250    ,         46844   },    // index = 27
        {    3000    ,         46743   },    // index = 28
        {    2750    ,         46652   },    // index = 29
        {    2500    ,         46569   },    // index = 30
        {    2250    ,         46415   },    // index = 31
        {    2000    ,         46200   },    // index = 32
        {    1750    ,         45910   },    // index = 33
        {    1500    ,         45512   },    // index = 34
        {    1250    ,         45108   },    // index = 35
        {    1000    ,         44898   },    // index = 36
        {    750     ,         44729   },    // index = 37
        {    500     ,         44469   },    // index = 38
        {    250     ,         43514   },    // index = 39
        {    0       ,         39000   }     // index = 40
};