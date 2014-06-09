

unsigned char getBatteryCapacity(unsigned int ADC_Voltage, unsigned int ADC_current,  unsigned int ADC_Temperature, unsigned char CurrentCode);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// not for user
unsigned int getDSGCapacityByTable(unsigned int real_mVoltage, unsigned char current_Index, unsigned char temp_Index);
unsigned int getCHGCapacityByTable(unsigned int real_mVoltage, unsigned char temp_Index);
unsigned int getStaticCapacityByTable(unsigned int real_mVoltage);
