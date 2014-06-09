



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
        {    10000   ,         29275   },    // index = 00
        {    9750    ,         29158   },    // index = 01
        {    9500    ,         28916   },    // index = 02
        {    9250    ,         28702   },    // index = 03
        {    9000    ,         28491   },    // index = 04
        {    8750    ,         28279   },    // index = 05
        {    8500    ,         28073   },    // index = 06
        {    8250    ,         27880   },    // index = 07
        {    8000    ,         27689   },    // index = 08
        {    7750    ,         27504   },    // index = 09
        {    7500    ,         27314   },    // index = 10
        {    7250    ,         27138   },    // index = 11
        {    7000    ,         26963   },    // index = 12
        {    6750    ,         26794   },    // index = 13
        {    6500    ,         26626   },    // index = 14
        {    6250    ,         26469   },    // index = 15
        {    6000    ,         26319   },    // index = 16
        {    5750    ,         26148   },    // index = 17
        {    5500    ,         25964   },    // index = 18
        {    5250    ,         25802   },    // index = 19
        {    5000    ,         25666   },    // index = 20
        {    4750    ,         25562   },    // index = 21
        {    4500    ,         25491   },    // index = 22
        {    4250    ,         25428   },    // index = 23
        {    4000    ,         25374   },    // index = 24
        {    3750    ,         25322   },    // index = 25
        {    3500    ,         25274   },    // index = 26
        {    3250    ,         25224   },    // index = 27
        {    3000    ,         25169   },    // index = 28
        {    2750    ,         25120   },    // index = 29
        {    2500    ,         25076   },    // index = 30
        {    2250    ,         24993   },    // index = 31
        {    2000    ,         24877   },    // index = 32
        {    1750    ,         24721   },    // index = 33
        {    1500    ,         24507   },    // index = 34
        {    1250    ,         24289   },    // index = 35
        {    1000    ,         24176   },    // index = 36
        {    750     ,         24085   },    // index = 37
        {    500     ,         23945   },    // index = 38
        {    250     ,         23431   },    // index = 39
        {    0       ,         21000   }     // index = 40
};