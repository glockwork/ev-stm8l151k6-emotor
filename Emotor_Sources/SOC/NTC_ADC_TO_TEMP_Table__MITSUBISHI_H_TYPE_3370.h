
///////////////////////////////////
//Mitsubishi NTC
//MITSUBISHI H
//BH30-3H103FB
//B�� : 25/50 �� 3370 K��1%
// Resistor1 = 10K
///////////////////////////////////
#define TEMPERATURE_TABLE_POINTS        141
#define NTC_DATA_LINE                   2

#define TEMPERATURE_Celsius_Index   0
#define TEMPERATURE_ADC_Index       1
const signed int NTC_ADC_TO_TEMP_Table[TEMPERATURE_TABLE_POINTS][NTC_DATA_LINE] =
{
  // NTC �ū�(��), ADC
  //    Celsius
        {  -40,    3898},    //index = 000
        {  -39,    3888},    //index = 001
        {  -38,    3876},    //index = 002
        {  -37,    3865},    //index = 003
        {  -36,    3853},    //index = 004
        {  -35,    3841},    //index = 005
        {  -34,    3828},    //index = 006
        {  -33,    3815},    //index = 007
        {  -32,    3801},    //index = 008
        {  -31,    3788},    //index = 009
        {  -30,    3770},    //index = 010
        {  -29,    3757},    //index = 011
        {  -28,    3739},    //index = 012
        {  -27,    3722},    //index = 013
        {  -26,    3705},    //index = 014
        {  -25,    3686},    //index = 015
        {  -24,    3667},    //index = 016
        {  -23,    3648},    //index = 017
        {  -22,    3628},    //index = 018
        {  -21,    3607},    //index = 019
        {  -20,    3585},    //index = 020
        {  -19,    3563},    //index = 021
        {  -18,    3540},    //index = 022
        {  -17,    3516},    //index = 023
        {  -16,    3492},    //index = 024
        {  -15,    3467},    //index = 025
        {  -14,    3441},    //index = 026
        {  -13,    3415},    //index = 027
        {  -12,    3388},    //index = 028
        {  -11,    3360},    //index = 029
        {  -10,    3331},    //index = 030
        {  -9 ,    3302},    //index = 031
        {  -8 ,    3271},    //index = 032
        {  -7 ,    3242},    //index = 033
        {  -6 ,    3211},    //index = 034
        {  -5 ,    3179},    //index = 035
        {  -4 ,    3145},    //index = 036
        {  -3 ,    3113},    //index = 037
        {  -2 ,    3079},    //index = 038
        {  -1 ,    3045},    //index = 039
        {  0  ,    3009},    //index = 040
        {  1  ,    2976},    //index = 041
        {  2  ,    2938},    //index = 042
        {  3  ,    2901},    //index = 043
        {  4  ,    2865},    //index = 044
        {  5  ,    2827},    //index = 045
        {  6  ,    2791},    //index = 046
        {  7  ,    2753},    //index = 047
        {  8  ,    2716},    //index = 048
        {  9  ,    2678},    //index = 049
        {  10 ,    2638},    //index = 050
        {  11 ,    2601},    //index = 051
        {  12 ,    2561},    //index = 052
        {  13 ,    2520},    //index = 053
        {  14 ,    2483},    //index = 054
        {  15 ,    2444},    //index = 055
        {  16 ,    2403},    //index = 056
        {  17 ,    2360},    //index = 057
        {  18 ,    2322},    //index = 058
        {  19 ,    2283},    //index = 059
        {  20 ,    2242},    //index = 060
        {  21 ,    2208},    //index = 061
        {  22 ,    2163},    //index = 062
        {  23 ,    2126},    //index = 063
        {  24 ,    2088},    //index = 064
        {  25 ,    2048},    //index = 065
        {  26 ,    2009},    //index = 066
        {  27 ,    1971},    //index = 067
        {  28 ,    1933},    //index = 068
        {  29 ,    1895},    //index = 069
        {  30 ,    1857},    //index = 070
        {  31 ,    1820},    //index = 071
        {  32 ,    1784},    //index = 072
        {  33 ,    1747},    //index = 073
        {  34 ,    1711},    //index = 074
        {  35 ,    1676},    //index = 075
        {  36 ,    1641},    //index = 076
        {  37 ,    1607},    //index = 077
        {  38 ,    1573},    //index = 078
        {  39 ,    1539},    //index = 079
        {  40 ,    1506},    //index = 080
        {  41 ,    1473},    //index = 081
        {  42 ,    1441},    //index = 082
        {  43 ,    1410},    //index = 083
        {  44 ,    1378},    //index = 084
        {  45 ,    1348},    //index = 085
        {  46 ,    1319},    //index = 086
        {  47 ,    1288},    //index = 087
        {  48 ,    1259},    //index = 088
        {  49 ,    1231},    //index = 089
        {  50 ,    1203},    //index = 090
        {  51 ,    1176},    //index = 091
        {  52 ,    1149},    //index = 092
        {  53 ,    1123},    //index = 093
        {  54 ,    1097},    //index = 094
        {  55 ,    1070},    //index = 095
        {  56 ,    1048},    //index = 096
        {  57 ,    1023},    //index = 097
        {  58 ,    1000},    //index = 098
        {  59 ,    976 },    //index = 099
        {  60 ,    952 },    //index = 100
        {  61 ,    930 },    //index = 101
        {  62 ,    910 },    //index = 102
        {  63 ,    888 },    //index = 103
        {  64 ,    868 },    //index = 104
        {  65 ,    847 },    //index = 105
        {  66 ,    827 },    //index = 106
        {  67 ,    808 },    //index = 107
        {  68 ,    790 },    //index = 108
        {  69 ,    771 },    //index = 109
        {  70 ,    752 },    //index = 110
        {  71 ,    735 },    //index = 111
        {  72 ,    719 },    //index = 112
        {  73 ,    702 },    //index = 113
        {  74 ,    685 },    //index = 114
        {  75 ,    668 },    //index = 115
        {  76 ,    653 },    //index = 116
        {  77 ,    639 },    //index = 117
        {  78 ,    624 },    //index = 118
        {  79 ,    610 },    //index = 119
        {  80 ,    595 },    //index = 120
        {  81 ,    580 },    //index = 121
        {  82 ,    568 },    //index = 122
        {  83 ,    555 },    //index = 123
        {  84 ,    540 },    //index = 124
        {  85 ,    528 },    //index = 125
        {  86 ,    518 },    //index = 126
        {  87 ,    506 },    //index = 127
        {  88 ,    493 },    //index = 128
        {  89 ,    484 },    //index = 129
        {  90 ,    471 },    //index = 130
        {  91 ,    461 },    //index = 131
        {  92 ,    451 },    //index = 132
        {  93 ,    438 },    //index = 133
        {  94 ,    429 },    //index = 134
        {  95 ,    419 },    //index = 135
        {  96 ,    412 },    //index = 136
        {  97 ,    402 },    //index = 137
        {  98 ,    392 },    //index = 138
        {  99 ,    385 },    //index = 139
        {  100,    375 }     //index = 140
};



