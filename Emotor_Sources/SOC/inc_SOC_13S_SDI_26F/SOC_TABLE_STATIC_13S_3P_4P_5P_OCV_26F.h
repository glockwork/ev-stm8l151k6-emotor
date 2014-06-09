



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
        {    10000   ,         54405   },    // index = 00
        {    9750    ,         54024   },    // index = 01
        {    9500    ,         53643   },    // index = 02
        {    9250    ,         53325   },    // index = 03
        {    9000    ,         52996   },    // index = 04
        {    8750    ,         52689   },    // index = 05
        {    8500    ,         52384   },    // index = 06
        {    8250    ,         52113   },    // index = 07
        {    8000    ,         51836   },    // index = 08
        {    7750    ,         51588   },    // index = 09
        {    7500    ,         51347   },    // index = 10
        {    7250    ,         51125   },    // index = 11
        {    7000    ,         50909   },    // index = 12
        {    6750    ,         50720   },    // index = 13
        {    6500    ,         50534   },    // index = 14
        {    6250    ,         50399   },    // index = 15
        {    6000    ,         50209   },    // index = 16
        {    5750    ,         50018   },    // index = 17
        {    5500    ,         49666   },    // index = 18
        {    5250    ,         49466   },    // index = 19
        {    5000    ,         49264   },    // index = 20
        {    4750    ,         49189   },    // index = 21
        {    4500    ,         49096   },    // index = 22
        {    4250    ,         49066   },    // index = 23
        {    4000    ,         49026   },    // index = 24
        {    3750    ,         49005   },    // index = 25
        {    3500    ,         48972   },    // index = 26
        {    3250    ,         48943   },    // index = 27
        {    3000    ,         48901   },    // index = 28
        {    2750    ,         48824   },    // index = 29
        {    2500    ,         48714   },    // index = 30
        {    2250    ,         48523   },    // index = 31
        {    2000    ,         48254   },    // index = 32
        {    1750    ,         47888   },    // index = 33
        {    1500    ,         47347   },    // index = 34
        {    1250    ,         46941   },    // index = 35
        {    1000    ,         46428   },    // index = 36
        {    750     ,         46165   },    // index = 37
        {    500     ,         45709   },    // index = 38
        {    250     ,         44918   },    // index = 39
        {    0       ,         39000   }     // index = 40
};