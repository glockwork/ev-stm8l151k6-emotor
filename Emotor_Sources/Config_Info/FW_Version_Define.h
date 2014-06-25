

#define FW_MAJOR_VERSION        ( 3 )   //1 byte, for main function addition and EEPROM Format changing
#define FW_MINOR_VERSION        ( 9 )   //1 byte, only for minor functions changing

//#define FW_EEPROM_VERSION        ( xx )   //1 byte,have to define at EEPROM Data File (UserDefine_xxxx_.h)

#define FW_RESERVED_VERSION     ( 1 )   // 1 bytes, (128 = 0x80 or more):Protuction, (0~20): Samples¡A (): 4MHz MCU Samples, (): 8MHz MCU Samples
