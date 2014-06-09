
/**
  ******************************************************************************
  * @file    Driver_User_Interface for UARt.c
  * @author  Dynapack ADT, Hsinmo
  * @version V1.0.0
  * @date    2-November-2012
  * @brief   for user to calling and control Devices
  ******************************************************************************
  * @attention
  *
  * DESCRIPTION....
  *
  * <h2><center>&copy; COPYRIGHT 2012 Dynapack</center></h2>
  */

//==============================================================================
// Includes
//==============================================================================
#include "Driver_User_Interface.h"
#include "Global_Variable_Define.h"
#include "Vars_Bits_Define.h"
#include "Protection_Polling_Func.h"
//#include "Config_Info\User_Define_Parser.h"
#include "SOC\Calculate_NTC_ADC_TO_TEMPERATURE.h"

#include "Capacity_Display_Polling_Func.h"

//==============================================================================
// Global/Extern variables
//==============================================================================
//==============================================================================
// Extern functions
//==============================================================================
extern unsigned int usMBCRC16( unsigned char * pucFrame, unsigned int usLen );
extern unsigned int usCheckSum16( unsigned char * pucFrame, unsigned int usLen );
//==============================================================================
// Private typedef
//==============================================================================
//==============================================================================
// Private define
//==============================================================================
#if (_Simulate_Cell_Voltages_ == 1)
void Calculation_Cell_Voltage_Different();
void _DUI_Send_First_7_Cell_voltages_CheckSum(unsigned char RespondCmd);
void _DUI_Send_Remain_Cell_voltages_WithoutFirst7_CheckSum(unsigned char RespondCmd);
#endif
//==============================================================================
// Private macro
//==============================================================================
//==============================================================================
// Private Enum
//==============================================================================
//==============================================================================
// Private variables
//==============================================================================
extern unsigned int g_Capacity_Remaining_Capacity;

////unsigned char G_All_LED_Bits_Mask;
//unsigned char Button_Interrupt_Counter;

unsigned char G_Communication_Array[CommunicationArray_Total_Bytes_Size];


unsigned char Receiving_Data[Receiving_Buffer_Size ];
unsigned int Communication_Receive_Temp_count;
unsigned char Communication_Receive_Temp;

//==============================================================================
// Private function prototypes
//==============================================================================

//==============================================================================
// Private functions
//==============================================================================





////////////////////////////////////////////////////////////////////////
// Uart2  : (section start)	
//
//Baud rate : 9600
//=======Receiving Data Structure===============================
//typedef struct{
//    static char cStart = 0X3A;	//起始字元
//    unsigned char 0X16;		    //Slave Address
//    unsigned char Command;		//命令
//    unsigned char LenExpected;	//數據長度
//    unsigned char DataBuf[DATA_BUF_NUM];//數據內容
//    unsigned char LRCDataLow;	    //checkSum Low byte, included slave address, command, length and data.
//    unsigned char LRCDataHigh;	//checkSum High byte, included slave address, command, length and data.
//    static char cEND1= 0X0D;	//結束字元 1
//    static char cEND1= 0X0A;	//結束字元 2
//} LEV Protocol Packet;
//
//========Transmiting Data Structure===========================
//typedef struct{
//    static char cStart = 0X3A;	//起始字元
//    unsigned char 0X16;		//Slave Address
//    unsigned char Command;		//應回應的命令
//    unsigned char LenExpected;	//數據長度
//    unsigned char DataBuf[DATA_BUF_NUM];//數據內容
//    unsigned char LRCDataLow;	    //checkSum Low byte, included slave address, command, length and data.
//    unsigned char LRCDataHigh;	//checkSum High byte, included slave address, command, length and data.
//    static char cEND1= 0X0D;	//結束字元 1
//    static char cEND1= 0X0A;	//結束字元 2
//} LEV Protocol Packet;
//
////=========Transmiting Accept Respond Structure ( No used )===================================================================
//typedef struct{
//    static char cStart = 0X3A;	//起始字元
//    unsigned char 0X16;		//Slave Address
//    unsigned char Respond_Accept_Check_Code = 0x80; //Accept 碼
//    unsigned char LenExpected = 1;	//數據長度
//    unsigned char Command;		//應回應的命令
//    unsigned char LRCDataLow;	    //checkSum Low byte, included slave address, command, length and data.
//    unsigned char LRCDataHigh;	//checkSum High byte, included slave address, command, length and data.
//    static char cEND1= 0X0D;	//結束字元 1
//    static char cEND1= 0X0A;	//結束字元 2
//} LEV Protocol Packet;
//
//=========Transmiting Error-Respond Structure ( No used )===================================================================
//typedef struct{
//    static char cStart = 0X3A;	//起始字元
//    unsigned char 0X16;		//Slave Address
//    unsigned char Respond_Error_Check_Code = 0x83; //錯誤碼
//    unsigned char LenExpected = 1;	//數據長度
//    unsigned char Command;		//應回應的命令
//    unsigned char LRCDataLow;	    //checkSum Low byte, included slave address, command, length and data.
//    unsigned char LRCDataHigh;	//checkSum High byte, included slave address, command, length and data.
//    static char cEND1= 0X0D;	//結束字元 1
//    static char cEND1= 0X0A;	//結束字元 2
//} LEV Protocol Packet;
//
//========One Wire Transmiting Data Structure=======================================================
//typedef struct{
//    static uint cStart1 = 0x80f8;	//起始字元 // send High byte first, then send Low byte second.
//    static uint cStart2 = 0x80A0;	//function字元 // send High byte first, then send Low byte second.
//                                    // 0x80A0 : data 資料,
//                                    // 0x80D0 ~ 0x80DF : EEPROM Seg 0 ~ 15 (a segment = 64 bytes),
//    unsigned int LenExpected;//數據長度 ; send High byte first, then send Low byte second. 0x80D0:無數據長度
//    unsigned char DataBuf[LenExpected];//數據內容
//    unsigned char LRCDataHigh;	//CRC16  High byte, calculating only include LenExpected and DataBuf
//    unsigned char LRCDataLow;	//CRC16 Low byte, calculating only include LenExpected and DataBuf
//    static uint cEND1= 0x70f7;	//結束字組 1 // send High byte first, then send Low byte second.
//    static uint cEND1= 0x70f7;	//結束字組 2 // send High byte first, then send Low byte second.
//} ModbusProtocolPacket;//RTU mode
//========One Wire Transmiting EEPROM Data Structure=======================================================
//typedef struct{
//    static uint cStart1 = 0x80f8;	//起始字元 // send High byte first, then send Low byte second.
//    static uint cStart2 = 0x80D0;	//function字元 // send High byte first, then send Low byte second.
//    unsigned char DataBuf[];//數據內容
//    unsigned char LRCDataHigh;	//CRC16 High byte, calculating only include LenExpected and DataBuf
//    unsigned char LRCDataLow;	//CRC16 Low byte, calculating only include LenExpected and DataBuf
//    static uint cEND1= 0x70f7;	//結束字組 1 // send High byte first, then send Low byte second.
//    static uint cEND1= 0x70f7;	//結束字組 2 // send High byte first, then send Low byte second.
//} ModbusProtocolPacket;//RTU mode
//
//#define LeadingCode                 (0x3A)
//#define SlaveAddressCode            (0x16)
//#define EndCode1                    (0x0D)
//#define EndCode2                    (0x0A)
//#define Respond_Error_Check_Code    (0xF3)
//#define Respond_Accept_Check_Code   (0xF0)
//
//#define MIN_Receive_Packet_Num      (9)
//#define MIN_Receive_Packet_Index    (MIN_Receive_Packet_Num - 1)
//
//#define ONE_WIRE_PrecedingCheckCode         (0x80f8)
//#define ONE_WIRE_Data_PrecedingCode         (0x80A0)
//#define ONE_WIRE_EEPROM_Seg_PrecedingCode   (0x80D0)
//#define ONE_WIRE_EndCheckCode               (0x70f7)


//#define UratRXFrameInternalGapTime	    20  // unit: 1ms
#define UratRXFrameInternalGapTime	    5  // unit: 10ms


unsigned char Receive_First_Index;  //0x3A
unsigned char Receive_End_Index;  //0x0A
unsigned char Receive_Cmd;  //
unsigned char Receive_DATA_Length;  //
unsigned char Receiving_Data_Array[ Receiving_Buffer_Size ];

__IO unsigned char Communication_Receive_Calling_Index;
__IO unsigned char G_Receiving_Buffer[ Receiving_Buffer_Total_Bytes_Size ];

//__IO unsigned int g_UART_FLAG;
//__IO unsigned char g_UART_Receive_First_Index;  //0x3A
//__IO unsigned char g_UART_Receive_End_Index;  //0x0A



/* Driver g_UART_FLAG Control Bits */
/* For g_UART_FLAG ; unsigned int */
//Low byte
//#define UART_Frame_Start                     (0x0001)    //
//#define UART_Packet_Find               (0x0002)    //
//#define UART_RX_IT_STATUS               (0x0004)    //
//#define UART_RX_FRAME_DONE              (0x0008)    //
//#define UART_RX_PrecedingCode_Find      (0x0010)    //
//#define UART_RX_EndingCode_Find         (0x0020)    //
//#define UART_RX_FRAME_ADDRESS_FAIL      (0x0040)    //
//#define UART_RX_FRAME_PACKET_FAIL       (0x0080)    //
////Hight byte
//#define    (0x0100)    //
//#define                   (0x0200)    //
//#define                   (0x0400)    //
//#define               (0x0800)    //
//#define         (0x1000)    ///
//#define         (0x2000)    //
//#define            (0x4000)    //
//#define            (0x8000)    //
unsigned char ReceiveDataParsingPacketAndCheck(){
    unsigned char last_idx;
    unsigned char i, length;
    unsigned int chkSum;
    unsigned char chkSum_hi, chkSum_lo;
    unsigned char CheckFlag;

    last_idx = Communication_Receive_Calling_Index - 1;

    CheckFlag = false;

    G_Extend_Device_Interface_Status &= ~UART_RX_PrecedingCode_Find;
    G_Extend_Device_Interface_Status &= ~UART_RX_EndingCode_Find;
    G_Extend_Device_Interface_Status &= ~UART_RX_FRAME_DONE;
    G_Extend_Device_Interface_Status &= ~UART_RX_FRAME_ADDRESS_FAIL;

    //check ending codes and Preceding Codes, if it's match.
    Receive_End_Index = 0;
    for(i = last_idx; i > 0; i--){
        if((G_Receiving_Buffer[i] == EndCode2) && (G_Receiving_Buffer[i - 1] == EndCode1)){
            G_Extend_Device_Interface_Status |= UART_RX_EndingCode_Find;
            Receive_End_Index = i;
            break;
        }
    }
    Receive_First_Index =0;
    for(i = 0; i < Receive_End_Index; i++){
        if((G_Receiving_Buffer[i] == LeadingCode) && (G_Receiving_Buffer[i+1] == SlaveAddressCode)){
            G_Extend_Device_Interface_Status |= UART_RX_PrecedingCode_Find;
            Receive_First_Index = i;
            break;
        }
    }

    //if find receiving packet, calculate chech sum.
    //and transfer data to Arrays
    if( (G_Extend_Device_Interface_Status & UART_RX_EndingCode_Find) &&
        (G_Extend_Device_Interface_Status & UART_RX_PrecedingCode_Find) &&
        (Receive_End_Index > Receive_First_Index)){

        length = Receive_End_Index - Receive_First_Index - 4; // length include slaveAdd, DataLength byte, Data bytes
        if( length > 0){
            for(i = 0; i < length; i++){
                Receiving_Data_Array[i] = G_Receiving_Buffer[i + 1];
            }
            //chkSum = usCheckSum16( &(G_Receiving_Buffer[1]), length );
            chkSum = usCheckSum16( Receiving_Data_Array, length );
            chkSum_hi = chkSum >> 8;
            chkSum_lo = chkSum & 0x00ff;
            if((chkSum_hi == G_Receiving_Buffer[Receive_End_Index - 2]) && (chkSum_lo == G_Receiving_Buffer[Receive_End_Index - 3])){
                Receive_Cmd = G_Receiving_Buffer[Receive_First_Index + 2];
                Receive_DATA_Length = G_Receiving_Buffer[Receive_First_Index + 3];
                i = Receive_First_Index + 3; // data length index
                last_idx = Receive_End_Index - 4;// last data index without checkSum
                last_idx = last_idx - i; // Really Data Length
                if((Receive_DATA_Length <= Receiving_Buffer_Size)&&(last_idx == Receive_DATA_Length)){
                    for(i=0; i< Receive_DATA_Length; i++){
                        Receiving_Data_Array[i] = G_Receiving_Buffer[Receive_First_Index + 4 + i];
                    }
                    CheckFlag = true;
                }
            }
        }//if( length > 0){
    }


//    //clear Receiving Buffer
//    for(i = 0; i < Communication_Receive_Calling_Index; i++){
//        G_Receiving_Buffer[i] = 0;
//    }
    Communication_Receive_Calling_Index = 0;
    if((G_Extend_Device_Interface_Status & UART_RX_PrecedingCode_Find) == 0){
           G_Extend_Device_Interface_Status |= UART_RX_FRAME_ADDRESS_FAIL;
       }

    G_Extend_Device_Interface_Status &= ~UART_RX_PrecedingCode_Find;
    G_Extend_Device_Interface_Status &= ~UART_RX_EndingCode_Find;

    G_Extend_Device_Interface_Status |= UART_RX_FRAME_DONE;
    if(CheckFlag){
        G_Extend_Device_Interface_Status &= ~UART_RX_FRAME_PACKET_FAIL;
        for(i = 0; i < Communication_Receive_Calling_Index; i++){
            G_Receiving_Buffer[i] = 0;
        }
        return true;
    }else{
        G_Extend_Device_Interface_Status |= UART_RX_FRAME_PACKET_FAIL;
        for(i = 0; i < Communication_Receive_Calling_Index; i++){
            G_Receiving_Buffer[i] = 0;
        }
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////
// calling by Timer4 for define frame
////////////////////////////////////////////////////////////////////////////////
void Communication_Receive_Frame_Timer_Calling_Counter(){
        //GPIO_HIGH(LED4_PORT, LED4_PIN);
        _Device_Remove_Timer4_Interrupt_Timer_Calling_Function(2);
        _DUI_Communication_RX_Interrupt_Set(DeviceOff);
        ReceiveDataParsingPacketAndCheck();
        _DUI_ReceiveDataParsingBy_RX_FRAME_DONE_For_Polling();
        Communication_Receive_Calling_Index = 0;
        //_UART_FLAG &= ~UART_Frame_Start;
        _DUI_Communication_RX_Interrupt_Set(DeviceOn);
        //GPIO_LOW(LED3_PORT, LED3_PIN);
        //GPIO_LOW(LED4_PORT, LED4_PIN);
}

////////////////////////////////////////////////////////////////////////////////
// calling by Uart Interrupt RX
////////////////////////////////////////////////////////////////////////////////
void Communication_Interrupt_Receive_Calling_Function_With_Timer(__IO unsigned char receivedByte){
//GPIO_HIGH(LED3_PORT, LED3_PIN);
    unsigned char temp;
//    if((g_UART_FLAG & UART_Frame_Start) == 0){
//            GPIO_HIGH(LED3_PORT, LED3_PIN);
//        _Device_Set_Timer4_Interrupt_Timer_Calling_Function_With_Delay_And_Exec(2, Communication_Receive_Frame_Timer_Calling_Counter, UratRXFrameInternalGapTime);
//        g_UART_FLAG |= UART_Frame_Start;
//    }

    if(Communication_Receive_Calling_Index == 0){
        _Device_Set_Timer4_Interrupt_Timer_Calling_Function_With_Delay_And_Exec(2, Communication_Receive_Frame_Timer_Calling_Counter, UratRXFrameInternalGapTime);
    }

    temp = receivedByte;
    G_Receiving_Buffer[Communication_Receive_Calling_Index++] = temp;


    if(Communication_Receive_Calling_Index >= Receiving_Buffer_Total_Bytes_Size){
        Communication_Receive_Calling_Index = Receiving_Buffer_Total_Bytes_Size - 1;
    }
//GPIO_LOW(LED3_PORT, LED3_PIN);
}

unsigned int g_uiTemp1;//, uiTemp2;
void Communication_ReceiveDataParsing(){
    unsigned int uiTemp1, uiTemp2;
    unsigned char ucTemp1, ucTemp2;
    //unsigned long ulTemp1;
    float fTemp1;//, uiTemp2;
    unsigned char Failure_Flag;

    Failure_Flag = false;
    //////////////////////////////////////
    // Communication
    switch(Receive_Cmd){

//////////////////////////////////////
// Communication for user
//////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Calculation Temperature to 0.1K (Kelvin Degree)
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0x08;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
        case 0x08:
            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
                uiTemp1 = Get_KelvinDegree_By_NTC_ADC(G_NTC1_ADC);
                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
            }
#if (_ENABLE_NTC_2_DETECTION_ == 1)
            else if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0C)){
                uiTemp1 = Get_KelvinDegree_By_NTC_ADC(G_NTC2_ADC);
                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
            }
#endif
            else{
                //Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Calculation Current Hi word
        // Calculation Voltage Hi word
        // Calculation Avg Current Hi word
        // Calculation Remaining Capacity Hi word
        // Calculation Full Charge Capacity Hi word
        // Cell Voltages Block 1
        // Cell Voltages Block 2
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0x06;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
        case 0x04:
        case 0x06:
        case 0x07:
        case 0x1e:
        case 0x1f:
            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
                uiTemp1 = 0;
                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
            }else{
                //Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Calculation Voltage word (mV)
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0x09;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd = 0x09;  Send_Bytes[3] = data length = 2;
        // Send_Bytes[4] = Read Data Lo byte;  Send_Bytes[5] = Read Data Hi byte;
        // Send_Bytes[6] = CheckSum Lo;  Send_Bytes[7] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        case 0x09:
            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
                fTemp1 = VBAT_mV_To_ADC_Factor;
                fTemp1 = G_AVG_Battery_Voltage_ADC / fTemp1;
                uiTemp1 = (unsigned int)fTemp1;
                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
            }else{
                //Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Calculation Current word (mA)
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0x0A;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd = 0x0A;  Send_Bytes[3] = data length = 2;
        // Send_Bytes[4] = Read Data Lo byte;  Send_Bytes[5] = Read Data Hi byte;
        // Send_Bytes[6] = CheckSum Lo;  Send_Bytes[7] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        case 0x0A:
            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
                fTemp1 = DSG_mA_To_ADC_Factor;
                fTemp1 = G_DSG_Current_ADC / fTemp1;
                uiTemp1 = (unsigned int)fTemp1;
                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
            }else{
                //Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Calculation Average Current word (mA)
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0x0B;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd = 0x0B;  Send_Bytes[3] = data length = 2;
        // Send_Bytes[4] = Read Data Lo byte;  Send_Bytes[5] = Read Data Hi byte;
        // Send_Bytes[6] = CheckSum Lo;  Send_Bytes[7] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        case 0x0B:
            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
                fTemp1 = DSG_mA_To_ADC_Factor;
                fTemp1 = G_AVG_DSG_Current_ADC / fTemp1;
                uiTemp1 = (unsigned int)fTemp1;
                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
            }else{
                //Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //  Relative State Of Charge (%)
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0x0D;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd = 0x0D;  Send_Bytes[3] = data length = 2;
        // Send_Bytes[4] = Read Data Lo byte;  Send_Bytes[5] = Read Data Hi byte;
        // Send_Bytes[6] = CheckSum Lo;  Send_Bytes[7] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        case 0x0D:
            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
//                if(g_uiTemp1 > 100){
//                    g_uiTemp1 = 0;
//                }else{
//                    g_uiTemp1++;
//                }
//                uiTemp1 = g_uiTemp1;
//                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);

                uiTemp1 = G_Hold_Capacity;
                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
            }else{
                //Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //  Absolute State Of Charge (%)
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0x0E;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd = 0x0E;  Send_Bytes[3] = data length = 2;
        // Send_Bytes[4] = Read Data Lo byte;  Send_Bytes[5] = Read Data Hi byte;
        // Send_Bytes[6] = CheckSum Lo;  Send_Bytes[7] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        case 0x0E:
            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
                uiTemp1 = G_Hold_Capacity;
                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
            }else{
                //Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //  Remaining Capacity (mah)(Lo Byte)
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0x0F;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd = 0x0F;  Send_Bytes[3] = data length = 2;
        // Send_Bytes[4] = Read Data Lo byte;  Send_Bytes[5] = Read Data Hi byte;
        // Send_Bytes[6] = CheckSum Lo;  Send_Bytes[7] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        case 0x0F:
            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
                uiTemp1 = g_Capacity_Remaining_Capacity;
                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
            }else{
                //Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //  Full Charge Capacity (mah)(Lo Byte)
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0x10;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd = 0x10;  Send_Bytes[3] = data length = 2;
        // Send_Bytes[4] = Read Data Lo byte;  Send_Bytes[5] = Read Data Hi byte;
        // Send_Bytes[6] = CheckSum Lo;  Send_Bytes[7] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        case 0x10:
            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
                uiTemp1 = DESIGN_CAPACITY_mAH;
                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
            }else{
                //Failure_Flag = true;
            }
            break;

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Calculation Cycle_Count_RECORD word
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0x17;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd = 0x17;  Send_Bytes[3] = data length = 2;
        // Send_Bytes[4] = Read Data Lo byte;  Send_Bytes[5] = Read Data Hi byte;
        // Send_Bytes[6] = CheckSum Lo;  Send_Bytes[7] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        case 0x17:
            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
                uiTemp1 = G_CHG_Cycle_Count_RECORD;
                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, &uiTemp1, 1, true, true);
            }else{
                //Failure_Flag = true;
            }
            break;
#if (_Simulate_Cell_Voltages_ == 1)
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Get Each Series Cell Voltage for first 7 th Voltages
        // voltage(mv) : 2 bytes (example: 4200mV = 0X1068)
        // send data: lo-byte firse ==> 0x68, 0x10
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0x24;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd = 0x24;  Send_Bytes[3] = data length = 14 (0x0e);
        // Send_Bytes[4] = 1st cell vol(Lo-byte);  Send_Bytes[5] = 1st cell vol(Hi-byte);
        // Send_Bytes[6] = 2nd cell vol(Lo-byte);  Send_Bytes[7] = 2nd cell vol(Hi-byte);
        // Send_Bytes[8] = 3rd cell vol(Lo-byte);  Send_Bytes[9] = 3rd cell vol(Hi-byte);
        // Send_Bytes[10] = 4th cell vol(Lo-byte);  Send_Bytes[11] = 4th cell vol(Hi-byte);
        // Send_Bytes[12] = 5th cell vol(Lo-byte);  Send_Bytes[13] = 5th cell vol(Hi-byte);
        // Send_Bytes[14] = 6th cell vol(Lo-byte);  Send_Bytes[15] = 6th cell vol(Hi-byte);
        // Send_Bytes[16] = 7th cell vol(Lo-byte);  Send_Bytes[17] = 7th cell vol(Hi-byte);
        // Send_Bytes[18] = CheckSum Lo;  Send_Bytes[19] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        case 0x24:
            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
                Calculation_Cell_Voltage_Different();
                _DUI_Send_First_7_Cell_voltages_CheckSum(Receive_Cmd);
            }else{
                //Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Get Each Series Cell Voltage from 8th Voltages to last
        // voltage(mv) : 2 bytes (example: 4200mV = 0X1068)
        // send data: lo-byte firse ==> 0x68, 0x10
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0x25;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd = 0x24;  Send_Bytes[3] = data length = XXXXX;
        // Send_Bytes[4] = 8th cell vol(Lo-byte);  Send_Bytes[5] = 8th cell vol(Hi-byte);
        // Send_Bytes[6] = 9th cell vol(Lo-byte);  Send_Bytes[7] = 9th cell vol(Hi-byte);
        // Send_Bytes[8] = 10th cell vol(Lo-byte);  Send_Bytes[9] = 10th cell vol(Hi-byte);
        // Send_Bytes[10] = 11th cell vol(Lo-byte);  Send_Bytes[11] = 11th cell vol(Hi-byte);
        // Send_Bytes[12] = 12th cell vol(Lo-byte);  Send_Bytes[13] = 12th cell vol(Hi-byte);
        // Send_Bytes[14] = 13th cell vol(Lo-byte);  Send_Bytes[15] = 13th cell vol(Hi-byte);
        // Send_Bytes[] = CheckSum Lo;  Send_Bytes[] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        case 0x25:
            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
                _DUI_Send_Remain_Cell_voltages_WithoutFirst7_CheckSum(Receive_Cmd);
            }else{
                //Failure_Flag = true;
            }
            break;
#endif
//////////////////////////////////////
// Communication manufacture
//////////////////////////////////////
        case 0xA0:
            _Device_Uart_Send_Bytes(Receiving_Data_Array, Receive_DATA_Length);
            break;

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // get mcu uid data
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd;  Send_Bytes[3] = data length;
        // Send_Bytes[4 ~ (4 + length - 1 )] = UID 12 bytes Data
        // Send_Bytes[last - 3] = CheckSum Lo;  Send_Bytes[Last - 2] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        case 0xA1:
            //_Device_Uart_Send_Bytes((unsigned char *)Unique_ID_Registers_Address, Unique_ID_Registers_Length);
            //_DUI_Communication_Send_Bytes_CRC16(0xA1, (unsigned char *)Unique_ID_Registers_Address, Unique_ID_Registers_Length, 1, 1);
            _DUI_Communication_Send_Bytes_CheckSum(Receive_Cmd, (unsigned char *)Unique_ID_Registers_Address, Unique_ID_Registers_Length, true, true);
            break;

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // get F/W Version
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd = 0xA2;  Send_Bytes[3] = data length = 4;
        // Send_Bytes[4] = VERSION
        // Send_Bytes[5] = MINOR VERSION
        // Send_Bytes[6] = EEPROM VERSION
        // Send_Bytes[7] = REserved VERSION
        // Send_Bytes[8] = CheckSum Lo;  Send_Bytes[9] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        case 0xA2:
            uiTemp1 = VERSION_Offset + CONFIG_SEGMENT;
            _DUI_Communication_Send_Bytes_CheckSum(Receive_Cmd, (unsigned char *)uiTemp1, 4, true, true);
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set/get Serial Number
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // get Serial Number
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xA3;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd = 0xA3;  Send_Bytes[3] = data length = 2;
        // Send_Bytes[4] = Read Data Lo byte;  Send_Bytes[5] = Read Data Hi byte;
        // Send_Bytes[6] = CheckSum Lo;  Send_Bytes[7] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set Serial Number
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xA3;   Received_Byte[3] = Receive_DATA_Length = 2;
        // Received_Byte[4] = Write Data Lo byte;(Receiving_Data_Array[0])
        // Received_Byte[5] = Write data Hi byte;(Receiving_Data_Array[1])
        // Received_Byte[6] = CheckSum Lo;  Received_Byte[7] = CheckSum Hi;
        // Received_Byte[last - 1] = EndCode1;  Received_Byte[Last] = EndCode2;
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = Respond_Accept_Check_Code(0xf0);
        // Send_Bytes[3] = data length = 1;
        // Send_Bytes[4] = RespondCmd = 0xA3;
        // Send_Bytes[5] = CheckSum Lo;  Send_Bytes[6] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        case 0xA3:
            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
                //read data
                //uiTemp1 = SERIAL_NUMBER_Offset + CONFIG_SEGMENT;
                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, (unsigned int *)(CONFIG_SEGMENT + SERIAL_NUMBER_Offset ), 1, true, true);
            }else if(Receive_DATA_Length == 2){
                //write data to EEPROM
                uiTemp1 = SERIAL_NUMBER_Offset + CONFIG_SEGMENT;
                ucTemp1 = _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 1 ]);   //write Hi byte First
                ucTemp2 = _Device_EEPROM_WriteByte(uiTemp1 + 1, Receiving_Data_Array[ 0 ]);   //write Lo byte First
                if((ucTemp1 == Func_Complete) && (ucTemp2 == Func_Complete)){
                    _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
                }else{
                    Failure_Flag = true;
                }
            }else{
                Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set/get MANUFACTURE DATE
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // get MANUFACTURE DATE
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xA4;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd = 0xA4;  Send_Bytes[3] = data length = 2;
        // Send_Bytes[4] = Read Data Lo byte;  Send_Bytes[5] = Read Data Hi byte;
        // Send_Bytes[6] = CheckSum Lo;  Send_Bytes[7] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set MANUFACTURE DATE
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xA4;   Received_Byte[3] = Receive_DATA_Length = 2;
        // Received_Byte[4] = Write Data Lo byte;(Receiving_Data_Array[0])
        // Received_Byte[5] = Write data Hi byte;(Receiving_Data_Array[1])
        // Received_Byte[6] = CheckSum Lo;  Received_Byte[7] = CheckSum Hi;
        // Received_Byte[last - 1] = EndCode1;  Received_Byte[Last] = EndCode2;
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = Respond_Accept_Check_Code(0xf0);
        // Send_Bytes[3] = data length = 1;
        // Send_Bytes[4] = RespondCmd = 0xA4;
        // Send_Bytes[5] = CheckSum Lo;  Send_Bytes[6] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        case 0xA4:
            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
                //read data
                //uiTemp1 = MANUFACTURE_DATE_Offset + CONFIG_SEGMENT;
                _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, (unsigned int *)(CONFIG_SEGMENT + MANUFACTURE_DATE_Offset ), 1, true, true);
            }else if(Receive_DATA_Length == 2){
                //write data to EEPROM
                uiTemp1 = MANUFACTURE_DATE_Offset + CONFIG_SEGMENT;
                ucTemp1 = _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 1 ]);   //write Hi byte First
                ucTemp2 = _Device_EEPROM_WriteByte(uiTemp1 + 1, Receiving_Data_Array[ 0 ]);   //write Lo byte First
                if((ucTemp1 == Func_Complete) && (ucTemp2 == Func_Complete)){
                    _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
                }else{
                    Failure_Flag = true;
                }
            }else{
                Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // get ALL ADC data
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = Receive_Cmd;  Send_Bytes[3] = data length;
        // Send_Bytes[] = DSG_Current_ADC; Send_Bytes[] = CHG_Current_ADC; Send_Bytes[] = VBAT_ADC
        // Send_Bytes[] = NTC1_ADC; Send_Bytes[] = NTC2_ADC; Send_Bytes[] = Vref_mVoltage
        // Send_Bytes[] = Current_Capacity
        // Send_Bytes[last - 3] = CheckSum Lo;  Send_Bytes[Last - 2] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        case 0xA5:
            _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, (&G_DSG_Current_ADC), 8, true, true);
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // get ProjectName
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = Receive_Cmd;  Send_Bytes[3] = data length;
        // Send_Bytes[n] = Project Name String
        // Send_Bytes[last - 3] = CheckSum Lo;  Send_Bytes[Last - 2] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        case 0xA6:
            _DUI_Communication_Send_Bytes_CheckSum(Receive_Cmd, (unsigned char *)(CONFIG_SEGMENT + PROJECT_NAME_Offset ), PROJECT_NAME_MAX_LENGTH, true, true);
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // get Design Capacity
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xA7;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd = 0xA7;  Send_Bytes[3] = data length = 2;
        // Send_Bytes[4] = Read Data Lo byte;  Send_Bytes[5] = Read Data Hi byte;
        // Send_Bytes[6] = CheckSum Lo;  Send_Bytes[7] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        case 0xA7:
            _DUI_Communication_Send_Word_CheckSum(Receive_Cmd, (unsigned int *)(CONFIG_SEGMENT + DESIGN_CAPACITY_mAH_Offset ), 1, true, true);
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set/get Bar code First_12 bytes
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // get Bar code
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xA8;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd = 0xA8;  Send_Bytes[3] = data length = 2;
        // Send_Bytes[n] = Read Data;
        // Send_Bytes[n+1] = CheckSum Lo;  Send_Bytes[n+2] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set Bar code
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xA8;   Received_Byte[3] = Receive_DATA_Length >= 2;
        // Received_Byte[n] = Write Data Lo to Hi byte;(Receiving_Data_Array[0] ~ [n])
        // Received_Byte[6] = CheckSum Lo;  Received_Byte[7] = CheckSum Hi;
        // Received_Byte[last - 1] = EndCode1;  Received_Byte[Last] = EndCode2;
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = Respond_Accept_Check_Code(0xf0);
        // Send_Bytes[3] = data length = 1;
        // Send_Bytes[4] = RespondCmd = 0xA8;
        // Send_Bytes[5] = CheckSum Lo;  Send_Bytes[6] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        case 0xA8:
            uiTemp2 = BAR_CODE_REAL_STORE_LENGTH >> 1;
            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
                //read data
                _DUI_Communication_Send_Bytes_CheckSum(Receive_Cmd, (unsigned char *)(CONFIG_SEGMENT + BAR_CODE_Offset ), uiTemp2, true, true);
            }else if((Receive_DATA_Length >= 2)&&(Receive_DATA_Length <= uiTemp2)){
                //write data to EEPROM
                //uiTemp1 = BAR_CODE_REAL_STORE_LENGTH_Offset + CONFIG_SEGMENT;
                //ucTemp1 = _Device_EEPROM_WriteByte(uiTemp1, Receive_DATA_Length);   //Store Bar code Length
                //ucTemp1 = _Device_EEPROM_WriteByte(uiTemp1, BAR_CODE_REAL_STORE_LENGTH);   //Store Bar code Length

                uiTemp1 = BAR_CODE_Offset + CONFIG_SEGMENT;
                    //for(ucTemp2 = 0; ucTemp2 < Receive_DATA_Length; ucTemp2++){
                    for(ucTemp2 = 0; ucTemp2 < (uiTemp2); ucTemp2++){
                        if(ucTemp2 < Receive_DATA_Length){
                            ucTemp1 = _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ ucTemp2 ]);   //write byte
                        }else{
                            ucTemp1 = _Device_EEPROM_WriteByte(uiTemp1, 0x00);   //write byte
                        }
                        if(ucTemp1 != Func_Complete){
                            Failure_Flag = true;
                            break;
                        }
                        uiTemp1++;
                    }//for(ucTemp2 = 0; ucTemp2 < Receive_DATA_Length; ucTemp2++){
                    if(Failure_Flag == false){
                        _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
                    }
            }else{
                Failure_Flag = true;
            }
            break;

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set/get Bar code Second_12 bytes
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // get Bar code
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xA9;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd = 0xA9;  Send_Bytes[3] = data length = 2;
        // Send_Bytes[n] = Read Data;
        // Send_Bytes[n+1] = CheckSum Lo;  Send_Bytes[n+2] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set Bar code
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xA9;   Received_Byte[3] = Receive_DATA_Length >= 2;
        // Received_Byte[n] = Write Data Lo to Hi byte;(Receiving_Data_Array[0] ~ [n])
        // Received_Byte[6] = CheckSum Lo;  Received_Byte[7] = CheckSum Hi;
        // Received_Byte[last - 1] = EndCode1;  Received_Byte[Last] = EndCode2;
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = Respond_Accept_Check_Code(0xf0);
        // Send_Bytes[3] = data length = 1;
        // Send_Bytes[4] = RespondCmd = 0xA9;
        // Send_Bytes[5] = CheckSum Lo;  Send_Bytes[6] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        case 0xA9:
            uiTemp2 = BAR_CODE_REAL_STORE_LENGTH >> 1;
            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
                //read data
                _DUI_Communication_Send_Bytes_CheckSum(Receive_Cmd, (unsigned char *)(CONFIG_SEGMENT + BAR_CODE_Offset + uiTemp2 ), uiTemp2, true, true);
            }else if((Receive_DATA_Length >= 2)&&(Receive_DATA_Length <= uiTemp2)){
                //write data to EEPROM
                //uiTemp1 = BAR_CODE_REAL_STORE_LENGTH_Offset + CONFIG_SEGMENT;
                //ucTemp1 = _Device_EEPROM_WriteByte(uiTemp1, Receive_DATA_Length);   //Store Bar code Length
                //ucTemp1 = _Device_EEPROM_WriteByte(uiTemp1, BAR_CODE_REAL_STORE_LENGTH);   //Store Bar code Length

                uiTemp1 = BAR_CODE_Offset + CONFIG_SEGMENT + uiTemp2;
                    //for(ucTemp2 = 0; ucTemp2 < Receive_DATA_Length; ucTemp2++){
                    for(ucTemp2 = 0; ucTemp2 < (uiTemp2); ucTemp2++){
                        if(ucTemp2 < Receive_DATA_Length){
                            ucTemp1 = _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ ucTemp2 ]);   //write byte
                        }else{
                            ucTemp1 = _Device_EEPROM_WriteByte(uiTemp1, 0x00);   //write byte
                        }
                        if(ucTemp1 != Func_Complete){
                            Failure_Flag = true;
                            break;
                        }
                        uiTemp1++;
                    }//for(ucTemp2 = 0; ucTemp2 < Receive_DATA_Length; ucTemp2++){
                    if(Failure_Flag == false){
                        _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
                    }
            }else{
                Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set/get Bar code 24 bytes All bytes
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // get Bar code
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xAA;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0x0B : read data; (Receiving_Data_Array[0])
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd = 0xAA;  Send_Bytes[3] = data length = 2;
        // Send_Bytes[n] = Read Data(24bytes);
        // Send_Bytes[n+1] = CheckSum Lo;  Send_Bytes[n+2] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set Bar code
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xAA;   Received_Byte[3] = Receive_DATA_Length >= 2;
        // Received_Byte[n] = Write Data Hi to Lo byte;(Receiving_Data_Array[0] ~ [n])
        // Received_Byte[6] = CheckSum Lo;  Received_Byte[7] = CheckSum Hi;
        // Received_Byte[last - 1] = EndCode1;  Received_Byte[Last] = EndCode2;
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = Respond_Accept_Check_Code(0xf0);
        // Send_Bytes[3] = data length = 1;
        // Send_Bytes[4] = RespondCmd = 0xAA;
        // Send_Bytes[5] = CheckSum Lo;  Send_Bytes[6] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        case 0xAA:
            //uiTemp2 = BAR_CODE_REAL_STORE_LENGTH ;
            if((Receive_DATA_Length == 1) && (Receiving_Data_Array[0] == 0x0B)){
                //read data
                _DUI_Communication_Send_Bytes_CheckSum(Receive_Cmd, (unsigned char *)(CONFIG_SEGMENT + BAR_CODE_Offset ), BAR_CODE_REAL_STORE_LENGTH, true, true);
            }else if((Receive_DATA_Length >= 2)&&(Receive_DATA_Length <= BAR_CODE_REAL_STORE_LENGTH)){
                if((BAR_CODE_REAL_STORE_LENGTH) > BAR_CODE_ID_Array_Size){
                    Failure_Flag = true;
                }else{
                    uiTemp2 = 0;  //for index count
                    G_BAR_CODE_ID_Array[uiTemp2++] = 0x01; //set as enable for main function to execuse
                    G_BAR_CODE_ID_Array[uiTemp2++] = Receive_Cmd; //set as Receive_Cmd
                    //uiTemp1 = BAR_CODE_Offset + CONFIG_SEGMENT + uiTemp2;
                        //for(ucTemp2 = 0; ucTemp2 < Receive_DATA_Length; ucTemp2++){
                    for(ucTemp2 = 0; ucTemp2 < (BAR_CODE_REAL_STORE_LENGTH); ucTemp2++){
                        if(ucTemp2 < Receive_DATA_Length){
                            G_BAR_CODE_ID_Array[uiTemp2++] = Receiving_Data_Array[ ucTemp2 ];
                        }else{
                            G_BAR_CODE_ID_Array[uiTemp2++] = 0x00;
                        }
                    }//for(ucTemp2 = 0; ucTemp2 < (BAR_CODE_REAL_STORE_LENGTH); ucTemp2++){
                }
            }else{
                Failure_Flag = true;
            }
            break;

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // get System Setting Information
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd = 0xA2;  Send_Bytes[3] = data length = 4;
        // Send_Bytes[4] = SystemSetting_Info_Byte1
        // Send_Bytes[5] = SystemSetting_Info_Byte2
        // Send_Bytes[6] = System_Control_Bit_EEPROM
        // Send_Bytes[7] = SystemSetting_Info_Byte3
        // Send_Bytes[8] = CheckSum Lo;  Send_Bytes[9] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        case 0xAB:
            uiTemp1 = SystemSetting_Info_Byte1_Offset + CONFIG_SEGMENT;
            _DUI_Communication_Send_Bytes_CheckSum(Receive_Cmd, (unsigned char *)uiTemp1, 4, true, true);
            break;

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set One_Wire Enable by button
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xB0;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] =  Enable Data (1 byte); 0= disable, 1 or more = enable; (Receiving_Data_Array[0])
        // Received_Byte[5] = CheckSum Lo;  Received_Byte[6] = CheckSum Hi;
        // Received_Byte[last - 1] = EndCode1;  Received_Byte[Last] = EndCode2;
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = Respond_Accept_Check_Code(0xf0);
        // Send_Bytes[3] = data length = 1;
        // Send_Bytes[4] = RespondCmd = 0xB0;
        // Send_Bytes[5] = CheckSum Lo;  Send_Bytes[6] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        case 0xB0:
            if(Receive_DATA_Length == 1){
                if(Receiving_Data_Array[0]){
                    G_Add_Module_Function_Status |= ONE_WIRE_UART_SET_ENABLE;
                }else{
                    G_Add_Module_Function_Status &= ~ONE_WIRE_UART_SET_ENABLE;
                }
                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
            }else{
                Failure_Flag = true;
            }
            break;

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set One_Wire Enable Always Transmit
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xB1;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] =  Enable Data (1 byte); 0= disable, 1 or more = enable; (Receiving_Data_Array[0])
        // Received_Byte[5] = CheckSum Lo;  Received_Byte[6] = CheckSum Hi;
        // Received_Byte[last - 1] = EndCode1;  Received_Byte[Last] = EndCode2;
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = Respond_Accept_Check_Code(0xf0);
        // Send_Bytes[3] = data length = 1;
        // Send_Bytes[4] = RespondCmd = 0xB1;
        // Send_Bytes[5] = CheckSum Lo;  Send_Bytes[6] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        case 0xB1:
            if(Receive_DATA_Length == 1){
                if(Receiving_Data_Array[0]){
                    G_Add_Module_Function_Status |= ONE_WIRE_TRANSMIT_ALWAYS;
                }else{
                    G_Add_Module_Function_Status &= ~ONE_WIRE_TRANSMIT_ALWAYS;
                }
                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
            }else{
                Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // One_Wire Enable Transmit once by command
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xB2;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] =  Enable Data (1 byte); 0= disable, 1 or more = enable; (Receiving_Data_Array[0])
        // Received_Byte[5] = CheckSum Lo;  Received_Byte[6] = CheckSum Hi;
        // Received_Byte[last - 1] = EndCode1;  Received_Byte[Last] = EndCode2;
        //.................................................................................................
        case 0xB2:
            if(Receive_DATA_Length == 1){
                G_Add_Module_Function_Status &= ~ONE_WIRE_TRANSMIT_ALWAYS;
                G_Add_Module_Function_Status &= ~ONE_WIRE_Send_EEPROM_Data;
                G_Add_Module_Function_Status |= ONE_WIRE_TRANSMIT_ONCE_BY_CMD;
                if(Receiving_Data_Array[0]){
                }else{
                }
                //_DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
            }else{
                Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // [Testing] Displaying All LEDs
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xB3;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] =  X (Don't care); (Receiving_Data_Array[0])
        // Received_Byte[5] = CheckSum Lo;  Received_Byte[6] = CheckSum Hi;
        // Received_Byte[last - 1] = EndCode1;  Received_Byte[Last] = EndCode2;
        //.................................................................................................
        case 0xB3:
            if(Receive_DATA_Length == 1){
                Display_All_LEDs_For_Test();
                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
            }else{
                Failure_Flag = true;
            }
            break;

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set DSG Mos Fet Turn Off
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set DSG Mos Fet Status
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xB4;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = Set DSG Mos Fet Turn Off;(Receiving_Data_Array[0])
        // Received_Byte[5] = CheckSum Lo;  Received_Byte[6] = CheckSum Hi;
        // Received_Byte[last - 1] = EndCode1;  Received_Byte[Last] = EndCode2;
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = Respond_Accept_Check_Code(0xf0);
        // Send_Bytes[3] = data length = 1;
        // Send_Bytes[4] = RespondCmd = 0xB4;
        // Send_Bytes[5] = CheckSum Lo;  Send_Bytes[6] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        case 0xB4:
            if(Receive_DATA_Length == 1){
                if(Receiving_Data_Array[0] != 0){
                    //set dsg mos turn off
                    G_Extend_Device_Interface_Status |= Force_DSG_MOS_OFF;
                }else{
                    //set dsg mos To normal cotrol
                    G_Extend_Device_Interface_Status &= ~Force_DSG_MOS_OFF;
                }
                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
            }else {
                Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set CHG Mos Fet Turn Off
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set CHG Mos Fet Status
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xB5;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = Set DSG Mos Fet Turn Off;(Receiving_Data_Array[0])
        // Received_Byte[5] = CheckSum Lo;  Received_Byte[6] = CheckSum Hi;
        // Received_Byte[last - 1] = EndCode1;  Received_Byte[Last] = EndCode2;
        //.................................................................................................
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = Respond_Accept_Check_Code(0xf0);
        // Send_Bytes[3] = data length = 1;
        // Send_Bytes[4] = RespondCmd = 0xB5;
        // Send_Bytes[5] = CheckSum Lo;  Send_Bytes[6] = CheckSum Hi;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        case 0xB5:
            if(Receive_DATA_Length == 1){
                if(Receiving_Data_Array[0] != 0){
                    //set chg mos turn off
                    G_Extend_Device_Interface_Status |= Force_CHG_MOS_OFF;
                }else{
                    //set chg mos To normal cotrol
                    G_Extend_Device_Interface_Status &= ~Force_CHG_MOS_OFF;
                }
                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
            }else {
                Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set Calbriation data bytes
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // DSG_OP_ADC_OFFSET
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xD0;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = Offset Data (1 byte); (Receiving_Data_Array[0])
        case 0xD0:
            if(Receive_DATA_Length == 1){
                uiTemp1 = DSG_OP_ADC_OFFSET_Offset + CONFIG_SEGMENT;
                _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 0 ]);
                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
            }else{
                Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set Calbriation data bytes
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // CHG_OP_ADC_OFFSET
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xD1;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = Offset Data (1 byte); (Receiving_Data_Array[0])
        case 0xD1:
            if(Receive_DATA_Length == 1){
                uiTemp1 = CHG_OP_ADC_OFFSET_Offset + CONFIG_SEGMENT;
                _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 0 ]);
                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
            }else{
                Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set Calbriation data bytes
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // VBAT_ADC_OFFSET
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xD2;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = Offset Data (1 byte); (Receiving_Data_Array[0])
        case 0xD2:
            if(Receive_DATA_Length == 1){
                uiTemp1 = VBAT_ADC_OFFSET_Offset + CONFIG_SEGMENT;
                _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 0 ]);
                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
            }else{
                Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set Calbriation data bytes
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // NTC1_ADC_OFFSET
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xD3;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = Offset Data (1 byte); (Receiving_Data_Array[0])
        case 0xD3:
            if(Receive_DATA_Length == 1){
                uiTemp1 = NTC1_ADC_OFFSET_Offset + CONFIG_SEGMENT;
                _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 0 ]);
                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
            }else{
                Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set Calbriation data bytes
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // NTC2_ADC_OFFSET
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xD4;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = Offset Data (1 byte); (Receiving_Data_Array[0])
        case 0xD4:
            if(Receive_DATA_Length == 1){
                uiTemp1 = NTC2_ADC_OFFSET_Offset + CONFIG_SEGMENT;
                _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 0 ]);
                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
            }else{
                Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // set Calbriation data bytes
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // SOC_ADC_OFFSET
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xD5;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = Offset Data (1 byte); (Receiving_Data_Array[0])
        case 0xD5:
            if(Receive_DATA_Length == 1){
                uiTemp1 = SOC_ADC_OFFSET_Offset + CONFIG_SEGMENT;
                _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 0 ]);
                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
            }else{
                Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // get EEPROM data bytes
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xE0;   Received_Byte[3] = Receive_DATA_Length = 3;
        // Received_Byte[4] = EEPROM Address Offset (Lo byte); (Receiving_Data_Array[0])
        // Received_Byte[5] = EEPROM Address Offset (Hi byte); (Receiving_Data_Array[1])
        // Received_Byte[6] = Get Data Length (1 byte);    (Receiving_Data_Array[2])
        case 0xE0:
            if(Receive_DATA_Length == 3){
                uiTemp1 = Receiving_Data_Array[1];
                uiTemp1 = (uiTemp1 << 8) + Receiving_Data_Array[0] + CONFIG_SEGMENT;
                _DUI_Communication_Send_EEPROM_DATA_CheckSum( Receive_Cmd, uiTemp1, Receiving_Data_Array[2]);
            }else{
                Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // write EEPROM data one byte
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xE1;   Received_Byte[3] = Receive_DATA_Length = 3;
        // Received_Byte[4] = EEPROM Address Offset (Lo byte); (Receiving_Data_Array[0])
        // Received_Byte[5] = EEPROM Address Offset (Hi byte); (Receiving_Data_Array[1])
        // Received_Byte[6] = write Data(1 byte);              (Receiving_Data_Array[2])
        case 0xE1:
            if( Receive_DATA_Length ==  3){
                uiTemp1 = Receiving_Data_Array[1];
                uiTemp1 = (uiTemp1 << 8) + Receiving_Data_Array[0] + CONFIG_SEGMENT;
                _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 2 ]);
                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
            }else{
                Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // [Bug][For Old Version] write EEPROM data word (two bytes)
        // [bug] because write Data Hi Lo reverse
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xE2;   Received_Byte[3] = Receive_DATA_Length = 4;
        // Received_Byte[4] = EEPROM Address Offset (Lo byte); (Receiving_Data_Array[0])
        // Received_Byte[5] = EEPROM Address Offset (Hi byte); (Receiving_Data_Array[1])
        // Received_Byte[6] = write Data(1 byte)(Hi);              (Receiving_Data_Array[2])
        // Received_Byte[7] = write Data(1 byte)(Lo);              (Receiving_Data_Array[3])
        case 0xE2:
            if( Receive_DATA_Length ==  4){
                uiTemp1 = Receiving_Data_Array[1];
                uiTemp1 = (uiTemp1 << 8) + Receiving_Data_Array[0] + CONFIG_SEGMENT;
                _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 2 ]);
                _Device_EEPROM_WriteByte(uiTemp1 + 1, Receiving_Data_Array[ 3 ]);
                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
            }else{
                Failure_Flag = true;
            }
            break;

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // write EEPROM data two words (four bytes)
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xE3;   Received_Byte[3] = Receive_DATA_Length = 6;
        // Received_Byte[4] = EEPROM Address Offset (Lo byte); (Receiving_Data_Array[0])
        // Received_Byte[5] = EEPROM Address Offset (Hi byte); (Receiving_Data_Array[1])
        // Received_Byte[6] = write Data(1 byte)(Lo);          (Receiving_Data_Array[2])
        // Received_Byte[7] = write Data(1 byte);              (Receiving_Data_Array[3])
        // Received_Byte[8] = write Data(1 byte);              (Receiving_Data_Array[4])
        // Received_Byte[9] = write Data(1 byte)(Hi);          (Receiving_Data_Array[5])
        case 0xE3:
            if( Receive_DATA_Length ==  6){
                uiTemp1 = Receiving_Data_Array[1];
                uiTemp1 = (uiTemp1 << 8) + Receiving_Data_Array[0] + CONFIG_SEGMENT;
//                ulTemp1 = Receiving_Data_Array[2];
//                ulTemp1 = (ulTemp1 << 8) + Receiving_Data_Array[3];
//                ulTemp1 = (ulTemp1 << 8) + Receiving_Data_Array[4];
//                ulTemp1 = (ulTemp1 << 8) + Receiving_Data_Array[5];
//                _Device_EEPROM_WriteDoubleWord(uiTemp1, ulTemp1);
                _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 2 ]);
                _Device_EEPROM_WriteByte(uiTemp1 + 1, Receiving_Data_Array[ 3 ]);
                _Device_EEPROM_WriteByte(uiTemp1 + 2, Receiving_Data_Array[ 4 ]);
                _Device_EEPROM_WriteByte(uiTemp1 + 3, Receiving_Data_Array[ 5 ]);

                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
            }else{
                Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // [For New Version] write EEPROM data word (two bytes)
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xE2;   Received_Byte[3] = Receive_DATA_Length = 4;
        // Received_Byte[4] = EEPROM Address Offset (Lo byte); (Receiving_Data_Array[0])
        // Received_Byte[5] = EEPROM Address Offset (Hi byte); (Receiving_Data_Array[1])
        // Received_Byte[6] = write Data(1 byte)(Lo);              (Receiving_Data_Array[2])
        // Received_Byte[7] = write Data(1 byte)(Hi);              (Receiving_Data_Array[3])
        case 0xE4:
            if( Receive_DATA_Length ==  4){
                uiTemp1 = Receiving_Data_Array[1];
                uiTemp1 = (uiTemp1 << 8) + Receiving_Data_Array[0] + CONFIG_SEGMENT;
                _Device_EEPROM_WriteByte(uiTemp1, Receiving_Data_Array[ 3 ]);
                _Device_EEPROM_WriteByte(uiTemp1 + 1, Receiving_Data_Array[ 2 ]);
                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
            }else{
                Failure_Flag = true;
            }
            break;

        case 0xF0:
            //reserved for accept Codes
            break;
        case 0xF3:
            //reserved for Error Codes
            break;
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // reset system by commnuication
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xFA;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0xFF : read data; (Receiving_Data_Array[0])
        //.................................................................................................
        case 0xFA:
            if((Receive_DATA_Length == 1) &&(Receiving_Data_Array[0] == 0xff)){
//                for(uiTemp1 = 0; uiTemp1 < 19; uiTemp1++){
//                    _DUI_delay_cycles(10000);     //100 = 1ms at CCLK=4MHz. 10000 = 100ms
//                    GPIO_TOGGLE(LED1_PORT, LED1_PIN);
//                }
//                GPIO_TOGGLE(LED2_PORT, LED2_PIN);
//                GPIO_TOGGLE(LED3_PORT, LED3_PIN);
//                _DUI_delay_cycles(10000);     //10000 = 100ms at CCLK=4MHz.
//                _DUI_delay_cycles(10000);    //10000 = 53ms at CCLK=8MHz.
                WWDG_SWReset();
            }else{
                Failure_Flag = true;
            }
            break;
//        ////////////////////////////////////////////////////////////////////////////////////////////////////
//        // for updated F/W by communication
//        ///////////////////////////////////////////////////////////////////////////////////////////////////
//        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
//        // Received_Byte[2] = Receive_Cmd = 0xFB;   Received_Byte[3] = Receive_DATA_Length = 1;
//        // Received_Byte[4] = 0xFF : read data; (Receiving_Data_Array[0])
//        //.................................................................................................
//        case 0xFB:
//            if((Receive_DATA_Length == 1) &&(Receiving_Data_Array[0] == 0xff)){
////                for(uiTemp1 = 0; uiTemp1 < 19; uiTemp1++){
////                _DUI_delay_cycles(10000);     //10000 = 100ms at CCLK=4MHz.
////                _DUI_delay_cycles(10000);    //10000 = 53ms at CCLK=8MHz.
////                    GPIO_TOGGLE(LED1_PORT, LED1_PIN);
////                }
////                GPIO_TOGGLE(LED2_PORT, LED2_PIN);
////                GPIO_TOGGLE(LED3_PORT, LED3_PIN);
//                //////////////////////////////////////////////////
//                // enable for updated Firmware
//                _DUI_Set_System_Control_Bit_To_EEPROM(SYS_UPDATED_FW , Enable);
//                _DUI_delay_cycles(10000);     //10000 = 100ms at CCLK=4MHz.
//                _DUI_delay_cycles(10000);     //10000 = 53ms at CCLK=8MHz.
//                WWDG_SWReset();
//            }else{
//                Failure_Flag = true;
//            }
//            break;
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // for updated F/W by communication and send accept cmd
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Received_Byte[0] = LeadingCode;          Received_Byte[1] = SlaveAddressCode;
        // Received_Byte[2] = Receive_Cmd = 0xFC;   Received_Byte[3] = Receive_DATA_Length = 1;
        // Received_Byte[4] = 0xFF : read data; (Receiving_Data_Array[0])
        //.................................................................................................
        case 0xFC:
            if((Receive_DATA_Length == 1) &&(Receiving_Data_Array[0] == 0xff)){
                //////////////////////////////////////////////////
                // enable for updated Firmware
                _DUI_Set_System_Control_Bit_To_EEPROM(SYS_UPDATED_FW , Enable);
                //_DUI_Set_Mask_Control_Bit_To_Code_Flash(SYS_Ready_UPDATED_FW_Mask_Bit, Enable);
                //_DUI_delay_cycles(10000);     //10000 = 100ms at CCLK=4MHz.
                _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
                _DUI_delay_cycles(10000);     //10000 = 53ms at CCLK=8MHz.
                _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
                _DUI_Set_System_Control_Bit_To_EEPROM(SYS_UPDATED_FW , Enable);
                //_DUI_Set_Mask_Control_Bit_To_Code_Flash(SYS_Ready_UPDATED_FW_Mask_Bit, Enable);
                _DUI_Communication_Send_Bytes_CheckSum(Respond_Accept_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
                _DUI_delay_cycles(10000);     //10000 = 53ms at CCLK=8MHz.
                _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
                _DUI_delay_cycles(10000);     //10000 = 53ms at CCLK=8MHz.
                _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
                _DUI_delay_cycles(10000);     //10000 = 53ms at CCLK=8MHz.
                _Device_Reset_WWDG_Counter();   //Refresh WWDG counter to Stop MCU reset
                _DUI_delay_cycles(10000);     //10000 = 53ms at CCLK=8MHz.
                WWDG_SWReset();
            }else{
                Failure_Flag = true;
            }
            break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // get Respond_Error_Check_Code
        // Send_Bytes[0] = LeadingCode; Send_Bytes[1] = SlaveAddressCode;
        // Send_Bytes[2] = RespondCmd;  Send_Bytes[3] = data length;
        // Send_Bytes[] = DSG_Current_ADC; Send_Bytes[] = CHG_Current_ADC; Send_Bytes[] = VBAT_ADC
        // Send_Bytes[] = NTC1_ADC; Send_Bytes[] = NTC2_ADC; Send_Bytes[] = Vref_mVoltage
        // Send_Bytes[] = Current_Capacity
        // Send_Bytes[last - 3] = CRC Hi;  Send_Bytes[Last - 2] = CRC Lo;
        // Send_Bytes[last - 1] = EndCode1;  Send_Bytes[Last] = EndCode2;
        default:
            //receiveData[0] = Respond_Error_Check_Code;
            //_DUI_Communication_Send_Bytes_CRC16(Respond_Error_Check_Code, receiveData, 1, 1, 1);
            break;
    }

    if(Failure_Flag){
        _DUI_Communication_Send_Bytes_CheckSum(Respond_Error_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
    }
    Receive_Cmd = 0;
    Receive_DATA_Length = 0;
}
unsigned char FirstFindingCodeIndex;
unsigned char LastFindingCodeIndex;
void _DUI_ReceiveDataParsingBy_RX_FRAME_DONE_For_Polling(){


    if((G_Extend_Device_Interface_Status & UART_RX_FRAME_DONE) == 0){
        return;
    }
    G_Extend_Device_Interface_Status &= ~UART_RX_FRAME_DONE;
    G_Extend_Device_Interface_Status &= ~UART_RX_PrecedingCode_Find;
    G_Extend_Device_Interface_Status &= ~UART_RX_EndingCode_Find;
    //Communication_Receive_Calling_Index = 0;
    if(G_Extend_Device_Interface_Status & UART_RX_FRAME_PACKET_FAIL){
        G_Extend_Device_Interface_Status &= ~UART_RX_FRAME_PACKET_FAIL;
        Receive_Cmd = 0;
        if((G_Extend_Device_Interface_Status & UART_RX_FRAME_ADDRESS_FAIL)==0){
            _DUI_Communication_Send_Bytes_CheckSum(Respond_Error_Check_Code, (unsigned char *)(&Receive_Cmd), 1, true, true);
        }
        G_Extend_Device_Interface_Status &= ~UART_RX_FRAME_ADDRESS_FAIL;
    }else{
        Communication_ReceiveDataParsing();
    }
    //_DUI_Communication_RX_Interrupt_Set(DeviceOn);
}



void _DUI_Communication_Enable(){
    Communication_Receive_Calling_Index = 0;
    Communication_Receive_Temp_count = 0;
    Communication_Receive_Temp = 0;

    _DUI_Set_Uart_Isolation_Enable(DeviceOn);
    _Device_Uart_Enable();
    _Device_Set_Uart_Interrupt_Receive_Calling_Function(Communication_Interrupt_Receive_Calling_Function_With_Timer);
    //_Device_Set_Uart_Interrupt_Receive_Calling_Function(Communication_Interrupt_Receive_Calling_Function_With_LeadingCode);
    G_Extend_Device_Interface_Status |= UART_RX_IT_STATUS;
    G_Extend_Device_Interface_Status |= UART_STATUS;
}
void _DUI_Communication_Disable(){
    _Device_Uart_Disable();
    _DUI_Set_Uart_Isolation_Enable(DeviceOff);
    G_Extend_Device_Interface_Status &= ~UART_STATUS;
}

unsigned char _DUI_Get_Communication_Pin_Interrupt_Received(){
    return _Device_Get_Uart_Pin_Interrupt_Received();
}
void _DUI_Communication_RX_Interrupt_Set(unsigned char enable){
    if(enable){
        _Device_Set_Uart_RX_Interrupt(DeviceOn);
        G_Extend_Device_Interface_Status |= UART_RX_IT_STATUS;
    }else{
        _Device_Set_Uart_RX_Interrupt(DeviceOff);
        G_Extend_Device_Interface_Status &= ~UART_RX_IT_STATUS;
    }
}
void _DUI_Communication_Send_Bytes(unsigned char *sendData, unsigned int length){
	//unsigned int commLength;
    int i;

    if(length > CommunicationArray_Data_Bytes_Size){
        return;
    }
	for(i = 0; i < length; i++){
        G_Communication_Array[i] = sendData[i];
    }
    _Device_Uart_Send_Bytes( G_Communication_Array, length); // send high byte first, send low byte second

}
void _DUI_One_Wire_Send_Word_CRC16(unsigned int *sendData, unsigned int length){
	unsigned int sendingLength, usCRC16;
	unsigned int DataLength;
    int i;

    DataLength = length << 1;    // mul 2
    if(DataLength > CommunicationArray_Data_Bytes_Size){
        return;
    }
	for(i = 0; i < DataLength; i++){
        G_Communication_Array[i + 2] = (*(((unsigned char *)sendData) + i));
    }
    G_Communication_Array[0] = DataLength >> 8;
    G_Communication_Array[1] = DataLength & 0x00ff;
    DataLength = DataLength + 2;
    /* Calculate CRC16 checksum for Modbus-Serial-Line-PDU. */
    usCRC16 = usMBCRC16( G_Communication_Array, DataLength );

    G_Communication_Array[DataLength] = usCRC16 >> 8;   //high-bytes first
    G_Communication_Array[DataLength + 1] = usCRC16;    //low-bytes second

    sendingLength = DataLength + 2;

        //shift 4  position back
        for(i = sendingLength; i > 0; i--){
            G_Communication_Array[i + 3] = G_Communication_Array[i - 1];
        }
        G_Communication_Array[0] = ONE_WIRE_PrecedingCheckCode >> 8;
        G_Communication_Array[1] = ONE_WIRE_PrecedingCheckCode & 0x00ff;
        G_Communication_Array[2] = ONE_WIRE_Data_PrecedingCode >> 8;
        G_Communication_Array[3] = ONE_WIRE_Data_PrecedingCode & 0x00ff;
        sendingLength = sendingLength + 4;


        G_Communication_Array[sendingLength] = ONE_WIRE_EndCheckCode >> 8;
        G_Communication_Array[sendingLength + 1] = ONE_WIRE_EndCheckCode & 0x00ff;
        G_Communication_Array[sendingLength + 2] = ONE_WIRE_EndCheckCode >> 8;
        G_Communication_Array[sendingLength + 3] = ONE_WIRE_EndCheckCode & 0x00ff;
        sendingLength = sendingLength + 4;
    _Device_Uart_Send_Bytes( G_Communication_Array, sendingLength); // send high byte first, send low byte second
}

void _DUI_One_Wire_Send_Bytes_CRC16(unsigned char *sendData, unsigned int length){
	unsigned int sendingLength, usCRC16;
    int i;

    if(length > CommunicationArray_Data_Bytes_Size){
        return;
    }
	for(i = 0; i < length; i++){
        G_Communication_Array[i + 2] = sendData[i];
    }
    G_Communication_Array[0] = length >> 8;
    G_Communication_Array[1] = length & 0x00ff;
    length = length + 2;

    /* Calculate CRC16 checksum for Modbus-Serial-Line-PDU. */
    usCRC16 = usMBCRC16( G_Communication_Array, length );

    G_Communication_Array[length] = usCRC16 >> 8;   //high-bytes first
    G_Communication_Array[length + 1] = usCRC16;    //low-bytes second

    sendingLength = length + 2;

        //shift 4 position back
        for(i = sendingLength; i > 0; i--){
            G_Communication_Array[i + 3] = G_Communication_Array[i - 1];
        }
        G_Communication_Array[0] = ONE_WIRE_PrecedingCheckCode >> 8;
        G_Communication_Array[1] = ONE_WIRE_PrecedingCheckCode & 0x00ff;
        G_Communication_Array[2] = ONE_WIRE_Data_PrecedingCode >> 8;
        G_Communication_Array[3] = ONE_WIRE_Data_PrecedingCode & 0x00ff;
        sendingLength = sendingLength + 4;

        G_Communication_Array[sendingLength] = ONE_WIRE_EndCheckCode >> 8;
        G_Communication_Array[sendingLength + 1] = ONE_WIRE_EndCheckCode & 0x00ff;
        G_Communication_Array[sendingLength + 2] = ONE_WIRE_EndCheckCode >> 8;
        G_Communication_Array[sendingLength + 3] = ONE_WIRE_EndCheckCode & 0x00ff;
        sendingLength = sendingLength + 4;
    _Device_Uart_Send_Bytes( G_Communication_Array, sendingLength); // send high byte first, send low byte second
}

void _DUI_One_Wire_Send_EEPROM_DATA_CRC16(){
	unsigned int sendingLength, usCRC16;

    /* Calculate CRC16 checksum for Modbus-Serial-Line-PDU. */
    usCRC16 = usMBCRC16( (unsigned char *)CONFIG_SEGMENT, EEPROM_END_DATA_POSITION_Offset + 1);

        G_Communication_Array[0] = ONE_WIRE_PrecedingCheckCode >> 8;
        G_Communication_Array[1] = ONE_WIRE_PrecedingCheckCode & 0x00ff;
        G_Communication_Array[2] = ONE_WIRE_EEPROM_Seg_PrecedingCode >> 8;
        G_Communication_Array[3] = ONE_WIRE_EEPROM_Seg_PrecedingCode & 0x00ff;
        sendingLength = 4;

        G_Communication_Array[sendingLength] = usCRC16 >> 8;   //high-bytes first
        G_Communication_Array[sendingLength + 1] = usCRC16;    //low-bytes second
        G_Communication_Array[sendingLength + 2] = ONE_WIRE_EndCheckCode >> 8;
        G_Communication_Array[sendingLength + 3] = ONE_WIRE_EndCheckCode & 0x00ff;
        G_Communication_Array[sendingLength + 4] = ONE_WIRE_EndCheckCode >> 8;
        G_Communication_Array[sendingLength + 5] = ONE_WIRE_EndCheckCode & 0x00ff;

    _Device_Uart_Send_Bytes( G_Communication_Array, sendingLength); // send high byte first, send low byte second
    _Device_Uart_Send_Bytes( (unsigned char *)CONFIG_SEGMENT, EEPROM_END_DATA_POSITION_Offset + 1); // send high byte first, send low byte second
    _Device_Uart_Send_Bytes( &(G_Communication_Array[sendingLength]), sendingLength + 2); // send high byte first, send low byte second
}


void _DUI_One_Wire_Send_EEPROM_PN_INFO_DATA_CRC16(){
	unsigned int sendingLength, usCRC16;

    /* Calculate CRC16 checksum for Modbus-Serial-Line-PDU. */
    usCRC16 = usMBCRC16( (unsigned char *)(CONFIG_SEGMENT + EEPROM_PN_INFO_START_DATA_POSITION_Offset), EEPROM_PN_INFO_END_DATA_POSITION_Offset - EEPROM_PN_INFO_START_DATA_POSITION_Offset + 1);

        G_Communication_Array[0] = ONE_WIRE_PrecedingCheckCode >> 8;
        G_Communication_Array[1] = ONE_WIRE_PrecedingCheckCode & 0x00ff;
        G_Communication_Array[2] = ONE_WIRE_PN_INFO_Seg_PrecedingCode >> 8;
        G_Communication_Array[3] = ONE_WIRE_PN_INFO_Seg_PrecedingCode & 0x00ff;
        sendingLength = 4;

        G_Communication_Array[sendingLength] = usCRC16 >> 8;   //high-bytes first
        G_Communication_Array[sendingLength + 1] = usCRC16;    //low-bytes second
        G_Communication_Array[sendingLength + 2] = ONE_WIRE_EndCheckCode >> 8;
        G_Communication_Array[sendingLength + 3] = ONE_WIRE_EndCheckCode & 0x00ff;
        G_Communication_Array[sendingLength + 4] = ONE_WIRE_EndCheckCode >> 8;
        G_Communication_Array[sendingLength + 5] = ONE_WIRE_EndCheckCode & 0x00ff;

    _Device_Uart_Send_Bytes( G_Communication_Array, sendingLength); // send high byte first, send low byte second
    _Device_Uart_Send_Bytes( (unsigned char *)(CONFIG_SEGMENT + EEPROM_PN_INFO_START_DATA_POSITION_Offset), EEPROM_PN_INFO_END_DATA_POSITION_Offset - EEPROM_PN_INFO_START_DATA_POSITION_Offset + 1); // send high byte first, send low byte second
    _Device_Uart_Send_Bytes( &(G_Communication_Array[sendingLength]), sendingLength + 2); // send high byte first, send low byte second
}

void _DUI_Send_One_Wire_Information_Data_By_Step(unsigned char step){
        switch(step){
            case Sending_SysInfor:
                _DUI_One_Wire_Send_Word_CRC16(G_Var_Array, VarArray_Int_Size);
                break;
            case Sending_EEPROMInfor:
                 _DUI_One_Wire_Send_EEPROM_DATA_CRC16();
                break;
            case Sending_PNInfor:
                _DUI_One_Wire_Send_EEPROM_PN_INFO_DATA_CRC16();
                break;

            case Sending_Empty_Delay:
            default:
                break;
        }
}

void _DUI_Communication_Send_EEPROM_DATA_CheckSum(unsigned char RespondCmd, unsigned int sendStartAddress, unsigned int length){
	unsigned int usCkSum16;
	unsigned int i;

    usCkSum16 = 0;
            G_Communication_Array[0] = LeadingCode;
            G_Communication_Array[1] = SlaveAddressCode;
            G_Communication_Array[2] = RespondCmd;
            G_Communication_Array[3] = length;

        usCkSum16 = SlaveAddressCode + RespondCmd + length;
        for(i=0; i < length; i++){
            usCkSum16 += (*((unsigned char *)sendStartAddress));
        }
            G_Communication_Array[4] = usCkSum16;
            G_Communication_Array[5] = usCkSum16 >> 8;
            G_Communication_Array[6] = EndCode1;
            G_Communication_Array[7] = EndCode2;

    _Device_Uart_Send_Bytes( G_Communication_Array, 4); // send high byte first, send low byte second
    _Device_Uart_Send_Bytes( (unsigned char *)sendStartAddress, length); // send high byte first, send low byte second
    _Device_Uart_Send_Bytes( &(G_Communication_Array[4]), 4); // send high byte first, send low byte second
}
void _DUI_Communication_Send_Word_CheckSum(unsigned char RespondCmd, unsigned int *sendData, unsigned int length, unsigned char isAddPrecedingCode, unsigned char isAddEndCode){
	unsigned int sendingLength, usCkSum16;
	unsigned int DataLength;
    int i;

    DataLength = length << 1;    // mul 2
    if(DataLength > CommunicationArray_Data_Bytes_Size){
        return;
    }
//	for(i = 0; i < DataLength; i++){
//        G_Communication_Array[i] = (*(((unsigned char *)sendData) + i));
//    }
    DataLength = 0 ;
	for(i = 0; i < length; i++){
        G_Communication_Array[DataLength++] = (*(sendData + i)) ;       //low byte first
        G_Communication_Array[DataLength++] = (*(sendData + i)) >> 8 ;  //high byte second
    }

    /* Calculate checksum*/
    usCkSum16 = usCheckSum16( G_Communication_Array, DataLength );
    //usCkSum16 += SlaveAddressCode;

    G_Communication_Array[DataLength] = usCkSum16;    //low-bytes first
    G_Communication_Array[DataLength + 1] = usCkSum16 >> 8;   //high-bytes second

    sendingLength = DataLength + 2;


        if(isAddPrecedingCode){
            //shift 4 position back
            for(i = sendingLength; i > 0; i--){
                G_Communication_Array[i + 3] = G_Communication_Array[i - 1];
            }
            sendingLength = sendingLength + 4;

            G_Communication_Array[0] = LeadingCode;
            G_Communication_Array[1] = SlaveAddressCode;
            G_Communication_Array[2] = RespondCmd;
            G_Communication_Array[3] = DataLength;

            usCkSum16 += SlaveAddressCode;
            usCkSum16 += RespondCmd;
            usCkSum16 += DataLength;
        }//if(enable_with_PrecedingCode){
        if(isAddEndCode){
            G_Communication_Array[sendingLength] = EndCode1;
            G_Communication_Array[sendingLength + 1] = EndCode2;
            sendingLength = sendingLength + 2;
        }

        /* update checksum*/
        G_Communication_Array[sendingLength - 4] = usCkSum16;    //low-bytes first
        G_Communication_Array[sendingLength - 3] = usCkSum16 >> 8;   //high-bytes second

    _Device_Uart_Send_Bytes( G_Communication_Array, sendingLength); // send high byte first, send low byte second
}
void _DUI_Communication_Send_Bytes_CheckSum(unsigned char RespondCmd, unsigned char *sendData, unsigned int length, unsigned char isAddPrecedingCode, unsigned char isAddEndCode){
	unsigned int sendingLength, usCkSum16;
    int i;

    if(length > CommunicationArray_Data_Bytes_Size){
        return;
    }
	for(i = 0; i < length; i++){
        G_Communication_Array[i] = sendData[i];
    }

    /* Calculate checksum*/
    usCkSum16 = usCheckSum16( G_Communication_Array, length );

    //G_Communication_Array[length] = usCkSum16 >> 8;   //high-bytes first
    //G_Communication_Array[length + 1] = usCkSum16;    //low-bytes second

    sendingLength = length + 2;


        if(isAddPrecedingCode){
            //shift 4 position back
            for(i = sendingLength; i > 0; i--){
                G_Communication_Array[i + 3] = G_Communication_Array[i - 1];
            }
            sendingLength = sendingLength + 4;

            G_Communication_Array[0] = LeadingCode;
            G_Communication_Array[1] = SlaveAddressCode;
            G_Communication_Array[2] = RespondCmd;
            G_Communication_Array[3] = length;
            usCkSum16 += SlaveAddressCode;
            usCkSum16 += RespondCmd;
            usCkSum16 += length;
        }//if(enable_with_PrecedingCode){
        if(isAddEndCode){
            G_Communication_Array[sendingLength] = EndCode1;
            G_Communication_Array[sendingLength + 1] = EndCode2;
            sendingLength = sendingLength + 2;
        }

        /* update checksum*/
        G_Communication_Array[sendingLength - 4] = usCkSum16;    //low-bytes first
        G_Communication_Array[sendingLength - 3] = usCkSum16 >> 8;   //high-bytes second

    _Device_Uart_Send_Bytes( G_Communication_Array, sendingLength); // send high byte first, send low byte second
}
#if (_Simulate_Cell_Voltages_ == 1)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//單串電池電壓 之差值
// CellVoltage_Different (8 bits)(1byte)(unsigned char) as 加/減,Step 乘值
// 第8th bit (MSB 1st bit)。 當(8th bit = 0)為加值，當(8th bit = 1)為減值. (mask: 0x80)
// 其餘7bits中，最低2bits(LSB: 1st ~ 2nd bit), 為階層數,共3階 ;加上正負號 共6階(==>最大階層數). (mask: 0x03)
unsigned char CellVoltage_Different[_CELL_SERIES_NUMBER_];    //單串電池電壓(mV)+/- CellVoltage_Different[]
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//最大階層數為 6 ==> 6 * One_Step_CELL_VOLTAGE_mV = Max-Delta-mV,不可超過100 mV(max:可超過127, 因為只使用後7bits, 有正負號)
#define  One_Step_CELL_VOLTAGE_mV           16  //mv, ==> 6 * 16 = 96(Max-Delta-mV)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Calculation_Cell_Voltage_Different(){
    int i;
	unsigned int uiTemp2, uiTemp3;
    //////////////////////////////////////////////
    //get random seed,
    // from 4 Vars to get 2 bits as Step values.
    i = 0;
    for( uiTemp2 = 0; uiTemp2 < _CELL_SERIES_NUMBER_; uiTemp2++){
        uiTemp3 = uiTemp2 & 0x0003;
        switch(uiTemp3){
            case 0:
                CellVoltage_Different[uiTemp2] = (G_VBAT_ADC >> i) & 0x0003;
                break;
            case 1:
                CellVoltage_Different[uiTemp2] = (G_CHG_Current_ADC >> i) & 0x0003;
                break;
            case 2:
                CellVoltage_Different[uiTemp2] = (G_NTC1_ADC >> i) & 0x0003;
                break;
            case 3:
                CellVoltage_Different[uiTemp2] = (G_DSG_Current_ADC >> i) & 0x0003;
                i++;
                break;
        }
    }
    // calculate voltage different，and get last bit to determine plus/minus
    for( uiTemp2 = 0; uiTemp2 < _CELL_SERIES_NUMBER_; uiTemp2++){
         CellVoltage_Different[uiTemp2] =  CellVoltage_Different[uiTemp2] * One_Step_CELL_VOLTAGE_mV;
         if(CellVoltage_Different[uiTemp2] & 0x01){
             CellVoltage_Different[uiTemp2] = ~CellVoltage_Different[uiTemp2];
         }
    }
}
void _DUI_Send_First_7_Cell_voltages_CheckSum(unsigned char RespondCmd){
	unsigned int sendingLength, usCkSum16, uiT, uiTemp2;
    int iTemp;
    float fTemp1;

    sendingLength = 0;
            G_Communication_Array[sendingLength++] = LeadingCode;
            G_Communication_Array[sendingLength++] = SlaveAddressCode;
            G_Communication_Array[sendingLength++] = RespondCmd;
            G_Communication_Array[sendingLength++] = 14;
//            usCkSum16 += SlaveAddressCode;
//            usCkSum16 += RespondCmd;
//            usCkSum16 += length;

            //////////////////////////////////////////////////////////////////
            // calculation Cell Voltage
            fTemp1 = VBAT_mV_To_ADC_Factor;
            //fTemp1 = G_AVG_Battery_Voltage_ADC / fTemp1;
            fTemp1 = G_VBAT_ADC / fTemp1;   //mV

            fTemp1 = fTemp1/ _CELL_SERIES_NUMBER_;    // cell voltage(mV)

            for( uiTemp2 = 0; uiTemp2 < 7; uiTemp2++){
                iTemp = (signed int)CellVoltage_Different[uiTemp2];
                uiT = (unsigned int)(fTemp1 + iTemp);
                G_Communication_Array[sendingLength++] = uiT;       //low-bytes first
                G_Communication_Array[sendingLength++] = uiT >> 8;  //high-bytes second
            }
            /////////////////////////////////////////////////////////////


    /* Calculate checksum*/
    usCkSum16 = usCheckSum16( &(G_Communication_Array[1]), sendingLength - 1 );

    /* update checksum*/
    G_Communication_Array[sendingLength++] = usCkSum16;    //low-bytes first
    G_Communication_Array[sendingLength++] = usCkSum16 >> 8;   //high-bytes second
    G_Communication_Array[sendingLength++] = EndCode1;
    G_Communication_Array[sendingLength++] = EndCode2;
    _Device_Uart_Send_Bytes( G_Communication_Array, sendingLength); // send high byte first, send low byte second
}
void _DUI_Send_Remain_Cell_voltages_WithoutFirst7_CheckSum(unsigned char RespondCmd){
	unsigned int sendingLength, usCkSum16, uiT, uiTemp2;
    int iTemp;
    float fTemp1;
    unsigned char flag;
    uiT = _CELL_SERIES_NUMBER_ - 7;
    flag = (uiT > 0)?1:0;
    sendingLength = 0;
            G_Communication_Array[sendingLength++] = LeadingCode;
            G_Communication_Array[sendingLength++] = SlaveAddressCode;
            G_Communication_Array[sendingLength++] = RespondCmd;
            G_Communication_Array[sendingLength++] = uiT * 2;
//            usCkSum16 += SlaveAddressCode;
//            usCkSum16 += RespondCmd;
//            usCkSum16 += length;
        if(flag){
            //////////////////////////////////////////////////////////////////
            // calculation Cell Voltage
            fTemp1 = VBAT_mV_To_ADC_Factor;
            //fTemp1 = G_AVG_Battery_Voltage_ADC / fTemp1;
            fTemp1 = G_VBAT_ADC / fTemp1;   //mV

            fTemp1 = fTemp1/ _CELL_SERIES_NUMBER_;    // cell voltage(mV)

            for( uiTemp2 = 7; uiTemp2 < _CELL_SERIES_NUMBER_; uiTemp2++){
                iTemp = (signed int)CellVoltage_Different[uiTemp2];
                uiT = (unsigned int)(fTemp1 + iTemp);
                G_Communication_Array[sendingLength++] = uiT;       //low-bytes first
                G_Communication_Array[sendingLength++] = uiT >> 8;  //high-bytes second
            }
            /////////////////////////////////////////////////////////////
        }


    /* Calculate checksum*/
    usCkSum16 = usCheckSum16( &(G_Communication_Array[1]), sendingLength - 1 );

    /* update checksum*/
    G_Communication_Array[sendingLength++] = usCkSum16;    //low-bytes first
    G_Communication_Array[sendingLength++] = usCkSum16 >> 8;   //high-bytes second
    G_Communication_Array[sendingLength++] = EndCode1;
    G_Communication_Array[sendingLength++] = EndCode2;
    _Device_Uart_Send_Bytes( G_Communication_Array, sendingLength); // send high byte first, send low byte second
}
#endif
//void _DUI_Communication_Send_Word_CRC16(unsigned char RespondCmd, unsigned int *sendData, unsigned int length, unsigned char isAddPrecedingCode, unsigned char isAddEndCode){
//	unsigned int sendingLength, usCRC16;
//	unsigned int DataLength;
//    int i;
//
//    DataLength = length << 1;    // mul 2
//    if(DataLength > CommunicationArray_Data_Bytes_Size){
//        return;
//    }
//	for(i = 0; i < DataLength; i++){
//        G_Communication_Array[i] = (*(((unsigned char *)sendData) + i));
//    }
//
//    /* Calculate CRC16 checksum for Modbus-Serial-Line-PDU. */
//    usCRC16 = usMBCRC16( G_Communication_Array, DataLength );
//
//    G_Communication_Array[DataLength] = usCRC16 >> 8;   //high-bytes first
//    G_Communication_Array[DataLength + 1] = usCRC16;    //low-bytes second
//
//    sendingLength = DataLength + 2;
//
//
//        if(isAddPrecedingCode){
//            //shift 4 position back
//            for(i = sendingLength; i > 0; i--){
//                G_Communication_Array[i + 3] = G_Communication_Array[i - 1];
//            }
//            sendingLength = sendingLength + 4;
//
//            G_Communication_Array[0] = LeadingCode;
//            G_Communication_Array[1] = SlaveAddressCode;
//            G_Communication_Array[2] = RespondCmd;
//            G_Communication_Array[3] = DataLength;
//        }//if(enable_with_PrecedingCode){
//        if(isAddEndCode){
//            G_Communication_Array[sendingLength] = EndCode1;
//            G_Communication_Array[sendingLength + 1] = EndCode2;
//            sendingLength = sendingLength + 2;
//        }
//    _Device_Uart_Send_Bytes( G_Communication_Array, sendingLength); // send high byte first, send low byte second
//}
//void _DUI_Communication_Send_Bytes_CRC16(unsigned char RespondCmd, unsigned char *sendData, unsigned int length, unsigned char isAddPrecedingCode, unsigned char isAddEndCode){
//	unsigned int sendingLength, usCRC16;
//    int i;
//
//    if(length > CommunicationArray_Data_Bytes_Size){
//        return;
//    }
//	for(i = 0; i < length; i++){
//        G_Communication_Array[i] = sendData[i];
//    }
//
//    /* Calculate CRC16 checksum for Modbus-Serial-Line-PDU. */
//    usCRC16 = usMBCRC16( G_Communication_Array, length );
//
//    G_Communication_Array[length] = usCRC16 >> 8;   //high-bytes first
//    G_Communication_Array[length + 1] = usCRC16;    //low-bytes second
//
//    sendingLength = length + 2;
//
//
//        if(isAddPrecedingCode){
//            //shift 4 position back
//            for(i = sendingLength; i > 0; i--){
//                G_Communication_Array[i + 3] = G_Communication_Array[i - 1];
//            }
//            sendingLength = sendingLength + 4;
//
//            G_Communication_Array[0] = LeadingCode;
//            G_Communication_Array[1] = SlaveAddressCode;
//            G_Communication_Array[2] = RespondCmd;
//            G_Communication_Array[3] = length;
//        }//if(enable_with_PrecedingCode){
//        if(isAddEndCode){
//            G_Communication_Array[sendingLength] = EndCode1;
//            G_Communication_Array[sendingLength + 1] = EndCode2;
//            sendingLength = sendingLength + 2;
//        }
//    _Device_Uart_Send_Bytes( G_Communication_Array, sendingLength); // send high byte first, send low byte second
//}
// Uart2  : (section stop)	
////////////////////////////////////////////////////////////////////////







