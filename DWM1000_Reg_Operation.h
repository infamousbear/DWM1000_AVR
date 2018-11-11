/*
 * DWM1000_Reg_Operation.h
 *
 *  Created on: 5 mar 2018
 *      Author: kynio
 */

#ifndef DWM1000_REG_OPERATION_H_
#define DWM1000_REG_OPERATION_H_
void New_Line();
char ArrayEqual(unsigned char A1[], unsigned char A2[]);
void Transmit_Disable(void);
void Transmit_Enable(void);
void SPI_Init(void);
unsigned char WriteByteSPI(unsigned char data);
void SetBit(char txt[], int Bit_Nr, int Nr_32b, char Set_Clr);
int Get_Select(char txt[]);
void Get_ID(unsigned char tab00[]);
void Get_SystemConfiguration(unsigned char tab00[]);
void Get_SystemTimeCounter(unsigned char tab00[], unsigned char tab04[]);
void Get_TransmitFrameControl(unsigned char tab00[], unsigned char tab04[]);
void Get_SystemControlRegister(unsigned char tab00[]);
void Get_SystemEventMaskRegister(unsigned char tab00[]);
void Get_SystemEventStatusRegister(unsigned char tab00[], unsigned char tab04[]);
void Get_RXFrameInformationRegister(unsigned char tab00[]);
void Get_RXFrameQualityInformation(unsigned char tab00[], unsigned char tab04[]);
void Get_ReceiverTimeTrackingInterval(unsigned char tab00[]);
void Get_ReceiverTimeTrackingOffset(unsigned char tab00[], unsigned char tab04[]);
void Get_FastReceiveTimeStamp(unsigned char tab[]);
void Get_ReceiveTimeStamp(unsigned char tab00[], unsigned char tab04[], unsigned char tab08[], unsigned char tab0C[]);
void Get_FastTransmitTimeStamp(unsigned char tab[]);
void Get_TransmitTimeStamp(unsigned char tab00[], unsigned char tab04[], unsigned char tab08[]);
void Get_TransmitterAntennaDelay(unsigned char tab00[]);
void Get_AcknowledgementTimeAndResponceTime(unsigned char tab00[]);
void Get_SNIFFMode(unsigned char tab00[]);
void Get_TransmitPowerControl(unsigned char tab00[]);
void Get_ChannelControl(unsigned char tab00[]);
void Get_AGCConfigurationAndControl(unsigned char tab02[], unsigned char tab04[], unsigned char tab0C[], unsigned char tab12[], unsigned char tab1E[]);
void Get_ExternalSynchronizationControl(unsigned char tab00[], unsigned char tab04[], unsigned char tab08[]);
void Get_GPIOModeControlRegister(unsigned char tab00[]);
void Get_GPIODirectionControlRegister(unsigned char tab00[]);
void Get_GPIODataOutputRegister(unsigned char tab00[]);
void Get_GPIOInterruptEnable(unsigned char tab00[]);
void Get_GPIOInterruptSenseSelection(unsigned char tab00[]);
void Get_GPIOInterruptMode(unsigned char tab00[]);
void Get_GPIOInterruptBoth_EdgeSelect(unsigned char tab00[]);
void Get_GPIOInterruptLatchClear(unsigned char tab00[]);
void Get_GPIOInterruptDebounceEnable(unsigned char tab00[]);
void Get_GPIORawState(unsigned char tab00[]);
void Get_DigitalReceiverConfiguration(unsigned char tab02[],unsigned char tab04[], unsigned char tab06[], unsigned char tab08[], unsigned char tab20[], unsigned char tab24[], unsigned char tab26[]);
void Get_AnalogRFConfigurationBlock(unsigned char tab00[],unsigned char tab0B[], unsigned char tab0C[], unsigned char tab2C[], unsigned char tab30[], unsigned char tab34[]);
void Get_TransimtterCalibrationBlock(unsigned char tab00[],unsigned char tab03[], unsigned char tab06[], unsigned char tab0B[], unsigned char tab0C[]);
void Get_FrequencySynthesiserControlBlock(unsigned char tab07[],unsigned char tab0B[], unsigned char tab0E[]);
void Get_OTPWriteData(unsigned char tab00[]);
void Get_OTPAddress(unsigned char tab00[]);
void Get_OTPControl(unsigned char tab00[]);
void Get_OTPStatus(unsigned char tab00[]);
void Get_OTPReadData(unsigned char tab00[]);
void Get_OTPSpecialRegisterReadData(unsigned char tab00[]);
void Get_OTPSpecialFunction(unsigned char tab00[]);
void Get_LeadingEdgeDetectionInterface(unsigned char tab0000[],unsigned char tab0806[], unsigned char tab1000[], unsigned char tab1002[], unsigned char tab1804[], unsigned char tab1806[], unsigned char tab2804[]);
void Get_PowerManagementAndSystemControl(unsigned char tab00[],unsigned char tab04[], unsigned char tab0C[], unsigned char tab26[], unsigned char tab28[]);
void Get_AlwaysONSystemControlInterface(unsigned char tab00[],unsigned char tab02[], unsigned char tab03[], unsigned char tab04[], unsigned char tab06[], unsigned char tab0A[]);
void Get_TransmitBuffer(unsigned char tab00[]);
void Get_ReceiveFrameWaitTimeoutPeriod(unsigned char tab00[]);

void Set_ID(unsigned char tab00[]);
void Set_SystemConfiguration(unsigned char tab00[]);
void Set_SystemTimeCounter(unsigned char tab00[], unsigned char tab04[]);
void Set_TransmitFrameControl(unsigned char tab00[], unsigned char tab04[]);
void Stop_Transmiter(void);
void Start_Transmit(void);
void Start_Receiving(void);
void Set_SystemControlRegister(unsigned char tab00[]);
void Set_SystemEventMaskRegister(unsigned char tab00[]);
void Set_SystemEventStatusRegister(unsigned char tab00[], unsigned char tab04[]);
void Set_RXFrameInformationRegister(unsigned char tab00[]);
void Set_RXFrameQualityInformation(unsigned char tab00[], unsigned char tab04[]);
void Set_ReceiverTimeTrackingInterval(unsigned char tab00[]);
void Set_ReceiverTimeTrackingOffset(unsigned char tab00[], unsigned char tab04[]);
void Set_ReceiveTimeStamp(unsigned char tab00[], unsigned char tab04[], unsigned char tab08[], unsigned char tab0C[]);
void Set_TransmitTimeStamp(unsigned char tab00[], unsigned char tab04[], unsigned char tab08[]);
void Set_TransmitterAntennaDelay(unsigned char tab00[]);
void Set_AcknowledgementTimeAndResponceTime(unsigned char tab00[]);
void Set_SNIFFMode(unsigned char tab00[]);
void Set_TransmitPowerControl(unsigned char tab00[]);
void Set_ChannelControl(unsigned char tab00[]);
void Set_AGCConfigurationAndControl(unsigned char tab02[], unsigned char tab04[], unsigned char tab0C[], unsigned char tab12[], unsigned char tab1E[]);
void Set_ExternalSynchronizationControl(unsigned char tab00[], unsigned char tab04[], unsigned char tab08[]);
void Set_GPIOModeControlRegister(unsigned char tab00[]);
void Set_GPIODirectionControlRegister(unsigned char tab00[]);
void Set_GPIODataOutputRegister(unsigned char tab00[]);
void Set_GPIOInterruptEnable(unsigned char tab00[]);
void Set_GPIOInterruptSenseSelection(unsigned char tab00[]);
void Set_GPIOInterruptMode(unsigned char tab00[]);
void Set_GPIOInterruptBoth_EdgeSelect(unsigned char tab00[]);
void Set_GPIOInterruptLatchClear(unsigned char tab00[]);
void Set_GPIOInterruptDebounceEnable(unsigned char tab00[]);
void Set_GPIORawState(unsigned char tab00[]);
void Set_DigitalReceiverConfiguration(unsigned char tab02[],unsigned char tab04[], unsigned char tab06[], unsigned char tab08[], unsigned char tab20[], unsigned char tab24[], unsigned char tab26[]);
void Set_AnalogRFConfigurationBlock(unsigned char tab00[],unsigned char tab0B[], unsigned char tab0C[], unsigned char tab2C[], unsigned char tab30[], unsigned char tab34[]);
void Set_TransimtterCalibrationBlock(unsigned char tab00[],unsigned char tab03[], unsigned char tab06[], unsigned char tab0B[], unsigned char tab0C[]);
void Set_FrequencySynthesiserControlBlock(unsigned char tab07[],unsigned char tab0B[], unsigned char tab0E[]);
void Set_OTPWriteData(unsigned char tab00[]);
void Set_OTPAddress(unsigned char tab00[]);
void Set_OTPControl(unsigned char tab00[]);
void Set_OTPStatus(unsigned char tab00[]);
void Set_OTPReadData(unsigned char tab00[]);
void Set_OTPSpecialRegisterReadData(unsigned char tab00[]);
void Set_OTPSpecialFunction(unsigned char tab00[]);
void Set_LeadingEdgeDetectionInterface(unsigned char tab0000[],unsigned char tab0806[], unsigned char tab1000[], unsigned char tab1002[], unsigned char tab1804[], unsigned char tab1806[], unsigned char tab2804[]);
void Set_PowerManagementAndSystemControl(unsigned char tab00[],unsigned char tab04[], unsigned char tab0C[], unsigned char tab26[], unsigned char tab28[]);
void Set_AlwaysONSystemControlInterface(unsigned char tab00[],unsigned char tab02[], unsigned char tab03[], unsigned char tab04[], unsigned char tab06[], unsigned char tab0A[]);
void Set_TransmitBuffer(unsigned char tab00[]);
void Set_ReceiveFrameWaitTimeoutPeriod(unsigned char tab00[]);

#endif /* DWM1000_REG_OPERATION_H_ */
