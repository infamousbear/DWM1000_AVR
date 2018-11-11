/*
 * DWM1000_Reg_Operation.c
 *
 *  Created on: 5 mar 2018
 *      Author: kynio
 */

#include "DWM1000_Reg_Operation.h"
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <util/atomic.h>

void New_Line()
{
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = 0x0A;
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = 0x0D;
}
char ArrayEqual(unsigned char A1[], unsigned char A2[])
{
	for(int i = 0 ; i < 5 ; i++)
	{
		if(A1[i] != A2[i])
			return 0;
	}
	return 1;
}
void Transmit_Disable(void)
{
	PORTB |= (1<<PB4);
}
void Transmit_Enable(void)
{
	PORTB &= ~(1<<PB4);
}
void SPI_Init(void)
{
	DDRB |= (1<<PB5)|(1<<PB7)|(1<<PB4); // MOSI, SS and SCK as Output
	DDRB &= ~((1<<PB3)|(1<<PB6)); // RST and MISO as input
	SPCR0 |= (1<<SPE0)|(1<<MSTR0)|(1<<SPI2X0); // SPI Enable, Master Set
	Transmit_Disable();

}
unsigned char WriteByteSPI(unsigned char data)
{
    // Load data into the buffer
    SPDR0 = data;

    //Wait until transmission complete
    while(!(SPSR0 & (1<<SPIF0) ));

    // Return received data
    return(SPDR0);
}
void SetBit(char txt[], int Bit_Nr, int Nr_32b, char Set_Clr)
{
	unsigned char tab0[4], tab1[4], tab2[4], tab3[4], tab4[4], tab5[4], tab6[4];
	int Octet_Nr, Bit, Register_ID;
	Register_ID = Get_Select(txt);
	Octet_Nr = 3 - Bit_Nr/8;
	Bit = Bit_Nr%8;
	//UDR0 = Register_ID;
	//UDR0 = Octet_Nr;
	switch(Register_ID)
	{
	case 0:Get_ID(tab0);break;
	case 1:Get_SystemConfiguration(tab0);break;
	case 2:Get_SystemTimeCounter( tab0,  tab1);break;
	case 3:Get_TransmitFrameControl( tab0,  tab1);break;
	case 4:Get_SystemControlRegister( tab0);break;
	case 5:Get_SystemEventMaskRegister( tab0);break;
	case 6:Get_SystemEventStatusRegister( tab0,  tab1);break;
	case 7:Get_RXFrameInformationRegister( tab0);break;
	case 8:Get_RXFrameQualityInformation( tab0,  tab1);break;
	case 9:Get_ReceiverTimeTrackingInterval( tab0);break;
	case 10:Get_ReceiverTimeTrackingOffset( tab0,  tab1);break;
	case 11:Get_ReceiveTimeStamp( tab0,  tab1,  tab2,  tab3);break;
	case 12:Get_TransmitTimeStamp( tab0,  tab1,  tab2);break;
	case 13:Get_TransmitterAntennaDelay( tab0);break;
	case 14:Get_AcknowledgementTimeAndResponceTime( tab0);break;
	case 15:Get_SNIFFMode( tab0);break;
	case 16:Get_TransmitPowerControl( tab0);break;
	case 17:Get_ChannelControl( tab0);break;
	case 18:Get_AGCConfigurationAndControl( tab0,  tab1,  tab2,  tab3,  tab4);break;
	case 19:Get_ExternalSynchronizationControl( tab0,  tab1,  tab2);break;
	case 20:Get_GPIOModeControlRegister( tab0);break;
	case 21:Get_GPIODirectionControlRegister( tab0);break;
	case 22:Get_GPIODataOutputRegister( tab0);break;
	case 23:Get_GPIOInterruptEnable( tab0);break;
	case 24:Get_GPIOInterruptSenseSelection( tab0);break;
	case 25:Get_GPIOInterruptMode( tab0);break;
	case 26:Get_GPIOInterruptBoth_EdgeSelect( tab0);break;
	case 27:Get_GPIOInterruptLatchClear( tab0);break;
	case 28:Get_GPIOInterruptDebounceEnable( tab0);break;
	case 29:Get_GPIORawState( tab0);break;
	case 30:Get_DigitalReceiverConfiguration( tab0, tab1,  tab2,  tab3,  tab4,  tab5,  tab6);break;
	case 31:Get_AnalogRFConfigurationBlock( tab0, tab1,  tab2,  tab3,  tab4,  tab5);break;
	case 32:Get_TransimtterCalibrationBlock( tab0, tab1,  tab2,  tab3,  tab4);break;
	case 33:Get_FrequencySynthesiserControlBlock( tab0, tab1,  tab2);break;
	case 34:Get_OTPWriteData( tab0);break;
	case 35:Get_OTPAddress( tab0);break;
	case 36:Get_OTPControl( tab0);break;
	case 37:Get_OTPStatus( tab0);break;
	case 38:Get_OTPReadData( tab0);break;
	case 39:Get_OTPSpecialRegisterReadData( tab0);break;
	case 40:Get_OTPSpecialFunction( tab0);break;
	case 41:Get_LeadingEdgeDetectionInterface( tab0, tab1,  tab2,  tab3,  tab4,  tab5,  tab6);break;
	case 42:Get_PowerManagementAndSystemControl(tab0, tab1,  tab2,  tab3,  tab4);break;
	case 43:Get_AlwaysONSystemControlInterface(tab0, tab1,  tab2,  tab3,  tab4,  tab5);break;
	}
	_delay_ms(1);
	//UDR0 = tab0[Octet_Nr];
	if(Set_Clr == 1)
		switch(Nr_32b)
		{
			case 1:	tab0[Octet_Nr] |= (1<<Bit);break;
			case 2:	tab1[Octet_Nr] |= (1<<Bit);break;
			case 3:	tab2[Octet_Nr] |= (1<<Bit);break;
			case 4:	tab3[Octet_Nr] |= (1<<Bit);break;
			case 5:	tab4[Octet_Nr] |= (1<<Bit);break;
			case 6:	tab5[Octet_Nr] |= (1<<Bit);break;
			case 7:	tab6[Octet_Nr] |= (1<<Bit);break;
		}
	if(Set_Clr == 0)
		switch(Nr_32b)
		{
			case 1:	tab0[Octet_Nr] &= ~(1<<Bit);break;
			case 2:	tab1[Octet_Nr] &= ~(1<<Bit);break;
			case 3:	tab2[Octet_Nr] &= ~(1<<Bit);break;
			case 4:	tab3[Octet_Nr] &= ~(1<<Bit);break;
			case 5:	tab4[Octet_Nr] &= ~(1<<Bit);break;
			case 6:	tab5[Octet_Nr] &= ~(1<<Bit);break;
			case 7:	tab6[Octet_Nr] &= ~(1<<Bit);break;
		}
	_delay_ms(1);
	//UDR0 = tab0[Octet_Nr];
	_delay_ms(1);
	switch(Register_ID)
	{
	case 0:Set_ID(tab0);break;
	case 1:Set_SystemConfiguration(tab0);break;
	case 2:Set_SystemTimeCounter( tab0,  tab1);break;
	case 3:Set_TransmitFrameControl( tab0,  tab1);break;
	case 4:Set_SystemControlRegister( tab0);break;
	case 5:Set_SystemEventMaskRegister( tab0);break;
	case 6:Set_SystemEventStatusRegister( tab0,  tab1);break;
	case 7:Set_RXFrameInformationRegister( tab0);break;
	case 8:Set_RXFrameQualityInformation( tab0,  tab1);break;
	case 9:Set_ReceiverTimeTrackingInterval( tab0);break;
	case 10:Set_ReceiverTimeTrackingOffset( tab0,  tab1);break;
	case 11:Set_ReceiveTimeStamp( tab0,  tab1,  tab2,  tab3);break;
	case 12:Set_TransmitTimeStamp( tab0,  tab1,  tab2);break;
	case 13:Set_TransmitterAntennaDelay( tab0);break;
	case 14:Set_AcknowledgementTimeAndResponceTime( tab0);break;
	case 15:Set_SNIFFMode( tab0);break;
	case 16:Set_TransmitPowerControl( tab0);break;
	case 17:Set_ChannelControl( tab0);break;
	case 18:Set_AGCConfigurationAndControl( tab0,  tab1,  tab2,  tab3,  tab4);break;
	case 19:Set_ExternalSynchronizationControl( tab0,  tab1,  tab2);break;
	case 20:Set_GPIOModeControlRegister( tab0);break;
	case 21:Set_GPIODirectionControlRegister( tab0);break;
	case 22:Set_GPIODataOutputRegister( tab0);break;
	case 23:Set_GPIOInterruptEnable( tab0);break;
	case 24:Set_GPIOInterruptSenseSelection( tab0);break;
	case 25:Set_GPIOInterruptMode( tab0);break;
	case 26:Set_GPIOInterruptBoth_EdgeSelect( tab0);break;
	case 27:Set_GPIOInterruptLatchClear( tab0);break;
	case 28:Set_GPIOInterruptDebounceEnable( tab0);break;
	case 29:Set_GPIORawState( tab0);break;
	case 30:Set_DigitalReceiverConfiguration( tab0, tab1,  tab2,  tab3,  tab4,  tab5,  tab6);break;
	case 31:Set_AnalogRFConfigurationBlock( tab0, tab1,  tab2,  tab3,  tab4,  tab5);break;
	case 32:Set_TransimtterCalibrationBlock( tab0, tab1,  tab2,  tab3,  tab4);break;
	case 33:Set_FrequencySynthesiserControlBlock( tab0, tab1,  tab2);break;
	case 34:Set_OTPWriteData( tab0);break;
	case 35:Set_OTPAddress( tab0);break;
	case 36:Set_OTPControl( tab0);break;
	case 37:Set_OTPStatus( tab0);break;
	case 38:Set_OTPReadData( tab0);break;
	case 39:Set_OTPSpecialRegisterReadData( tab0);break;
	case 40:Set_OTPSpecialFunction( tab0);break;
	case 41:Set_LeadingEdgeDetectionInterface( tab0, tab1,  tab2,  tab3,  tab4,  tab5,  tab6);break;
	case 42:Set_PowerManagementAndSystemControl(tab0, tab1,  tab2,  tab3,  tab4);break;
	case 43:Set_AlwaysONSystemControlInterface(tab0, tab1,  tab2,  tab3,  tab4,  tab5);break;
	}
	_delay_ms(1);

}
int Get_Select(char txt[])
{
	int tmp=0;
	tmp = (strcmp(txt,"ID")==0)? 0:tmp;
	tmp = (strcmp(txt,"SystemConfiguration")==0)? 1:tmp;
	tmp = (strcmp(txt,"SystemTimeCounter")==0)? 2:tmp;
	tmp = (strcmp(txt,"TransmitFrameControl")==0)? 3:tmp;
	tmp = (strcmp(txt,"SystemControlRegister")==0)? 4:tmp;
	tmp = (strcmp(txt,"SystemEventMaskRegister")==0)? 5:tmp;
	tmp = (strcmp(txt,"SystemEventStatusRegister")==0)? 6:tmp;
	tmp = (strcmp(txt,"RXFrameInformationRegister")==0)? 7:tmp;
	tmp = (strcmp(txt,"RXFrameQualityInformation")==0)? 8:tmp;
	tmp = (strcmp(txt,"ReceiverTimeTrackingInterval")==0)? 9:tmp;
	tmp = (strcmp(txt,"ReceiverTimeTrackingOffset")==0)? 10:tmp;
	tmp = (strcmp(txt,"ReceiveTimeStamp")==0)? 11:tmp;
	tmp = (strcmp(txt,"TransmitTimeStamp")==0)? 12:tmp;
	tmp = (strcmp(txt,"TransmitterAntennaDelay")==0)? 13:tmp;
	tmp = (strcmp(txt,"AcknowledgementTimeAndResponceTime")==0)? 14:tmp;
	tmp = (strcmp(txt,"SNIFFMode")==0)? 15:tmp;
	tmp = (strcmp(txt,"TransmitPowerControl")==0)? 16:tmp;
	tmp = (strcmp(txt,"ChannelControl")==0)? 17:tmp;
	tmp = (strcmp(txt,"AGCConfigurationAndControl")==0)? 18:tmp;
	tmp = (strcmp(txt,"ExternalSynchronizationControl")==0)? 19:tmp;
	tmp = (strcmp(txt,"GPIOModeControlRegister")==0)? 20:tmp;
	tmp = (strcmp(txt,"GPIODirectionControlRegister")==0)? 21:tmp;
	tmp = (strcmp(txt,"GPIODataOutputRegister")==0)? 22:tmp;
	tmp = (strcmp(txt,"GPIOInterruptEnable")==0)? 23:tmp;
	tmp = (strcmp(txt,"GPIOInterruptSenseSelection")==0)? 24:tmp;
	tmp = (strcmp(txt,"GPIOInterruptMode")==0)? 25:tmp;
	tmp = (strcmp(txt,"GPIOInterruptBoth_EdgeSelect")==0)? 26:tmp;
	tmp = (strcmp(txt,"GPIOInterruptLatchClear")==0)? 27:tmp;
	tmp = (strcmp(txt,"GPIOInterruptDebounceEnable")==0)? 28:tmp;
	tmp = (strcmp(txt,"GPIORawState")==0)? 29:tmp;
	tmp = (strcmp(txt,"DigitalReceiverConfiguration")==0)? 30:tmp;
	tmp = (strcmp(txt,"AnalogRFConfigurationBlock")==0)? 31:tmp;
	tmp = (strcmp(txt,"TransimtterCalibrationBlock")==0)? 32:tmp;
	tmp = (strcmp(txt,"FrequencySynthesiserControlBlock")==0)? 33:tmp;
	tmp = (strcmp(txt,"OTPWriteData")==0)? 34:tmp;
	tmp = (strcmp(txt,"OTPAddress")==0)? 35:tmp;
	tmp = (strcmp(txt,"OTPControl")==0)? 36:tmp;
	tmp = (strcmp(txt,"OTPStatus")==0)? 37:tmp;
	tmp = (strcmp(txt,"OTPReadData")==0)? 38:tmp;
	tmp = (strcmp(txt,"OTPSpecialRegisterReadData")==0)? 38:tmp;
	tmp = (strcmp(txt,"OTPSpecialFunction")==0)? 40:tmp;
	tmp = (strcmp(txt,"LeadingEdgeDetectionInterface")==0)? 41:tmp;
	tmp = (strcmp(txt,"PowerManagementAndSystemControl")==0)? 42:tmp;
	tmp = (strcmp(txt,"AlwaysONSystemControlInterface")==0)? 43:tmp;


	return tmp;

}





void Get_ID(unsigned char tab00[]) // Rejestr przechowuj¹cy ID urz¹dzenia
{

	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x00);break;
		default: tab00[4-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();
}
void Get_SystemConfiguration(unsigned char tab00[]) // Rejestr przechowuj¹cy ID urz¹dzenia
{

	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x04);break;
		default: tab00[4-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();
}
void Get_SystemTimeCounter(unsigned char tab00[], unsigned char tab04[]) // Rejestr przechowuj¹cy wartoœc licznika systemowego
{

	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x06);break;
		default: tab00[4-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x47);break;
		case 1: WriteByteSPI(0x04);break;
		default: tab04[2-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_TransmitFrameControl(unsigned char tab00[], unsigned char tab04[]) // Rejestr przechowuj¹cy podstawowe ustawienia ramki transmisyjnej
{

	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x08);break;
		default: tab00[4-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x48);break;
		case 1: WriteByteSPI(0x04);break;
		default: tab04[2-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_ReceiveFrameWaitTimeoutPeriod(unsigned char tab00[]) // Rejestr przechowuj¹cy podstawowe ustawienia ramki transmisyjnej
{

	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x4C);break;
		case 1: WriteByteSPI(0x00);break;
		default: tab00[3-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();

}
void Get_SystemControlRegister(unsigned char tab00[]) // Rejestr przechowuj¹cy ID urz¹dzenia
{

	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x0D);break;
		default: tab00[4-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();
}
void Get_SystemEventMaskRegister(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x0E);break;
		default: tab00[4-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();
}
void Get_SystemEventStatusRegister(unsigned char tab00[], unsigned char tab04[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x0F);break;
		default: tab00[4-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x4F);break;
		case 1: WriteByteSPI(0x04);break;
		default: tab04[2-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_RXFrameInformationRegister(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{

		switch(i)
		{
		case 0: WriteByteSPI(0x10);break;
		default: tab00[4-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();
}
void Get_RXFrameQualityInformation(unsigned char tab00[], unsigned char tab04[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x12);break;
		default: tab00[4-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x52);break;
		case 1: WriteByteSPI(0x04);break;
		default: tab04[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_ReceiverTimeTrackingInterval(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x13);break;
		default: tab00[4-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();
}
void Get_ReceiverTimeTrackingOffset(unsigned char tab00[], unsigned char tab04[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x14);break;
		default: tab00[4-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x54);break;
		case 1: WriteByteSPI(0x04);break;
		default: tab04[2-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_FastReceiveTimeStamp(unsigned char tab[]) // 0x0F:00 jest jeszcze 04
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		Transmit_Enable();
		for (int i = 0; i <= 4; i++) {
			switch (i) {
			case 0:
				WriteByteSPI(0x15);
				break;
			default:
				tab[5 - i] = WriteByteSPI(0x00);
				break;
			}
		}
		Transmit_Disable();
		Transmit_Enable();
		for (int i = 0; i <= 2; i++) {
			switch (i) {
			case 0:
				WriteByteSPI(0x55);
				break;
			case 1:
				WriteByteSPI(0x04);
				break;
			default:
				tab[0] = WriteByteSPI(0x00);
				break;
			}
		}
		Transmit_Disable();
	}
}

void Get_ReceiveTimeStamp(unsigned char tab00[], unsigned char tab04[], unsigned char tab08[], unsigned char tab0C[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x15);break;
		default: tab00[4-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x55);break;
		case 1: WriteByteSPI(0x04);break;
		default: tab04[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x55);break;
		case 1: WriteByteSPI(0x08);break;
		default: tab08[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x55);break;
		case 1: WriteByteSPI(0x0C);break;
		default: tab0C[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_FastTransmitTimeStamp(unsigned char tab[]) // 0x0F:00 jest jeszcze 04
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		Transmit_Enable();
		for (int i = 0; i <= 4; i++) {
			switch (i) {
			case 0:
				WriteByteSPI(0x17);
				break;
			default:
				tab[5 - i] = WriteByteSPI(0x00);
				break;
			}
		}
		Transmit_Disable();
		Transmit_Enable();
		for (int i = 0; i <= 2; i++) {
			switch (i) {
			case 0:
				WriteByteSPI(0x57);
				break;
			case 1:
				WriteByteSPI(0x04);
				break;
			default:
				tab[0] = WriteByteSPI(0x00);
				break;
			}
		}
		Transmit_Disable();
	}
}
void Get_TransmitTimeStamp(unsigned char tab00[], unsigned char tab04[], unsigned char tab08[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x17);break;
		default: tab00[4-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x57);break;
		case 1: WriteByteSPI(0x04);break;
		default: tab04[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x57);break;
		case 1: WriteByteSPI(0x08);break;
		default: tab08[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();

}
void Get_TransmitterAntennaDelay(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x18);break;
		default: tab00[2-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();
}
void Get_AcknowledgementTimeAndResponceTime(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x1A);break;
		default: tab00[4-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();
}
void Get_SNIFFMode(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x1D);break;
		default: tab00[4-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();
}
void Get_TransmitPowerControl(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x1E);break;
		default: tab00[4-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();
}
void Get_ChannelControl(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x1F);break;
		default: tab00[4-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();
}
void Get_AGCConfigurationAndControl(unsigned char tab02[], unsigned char tab04[], unsigned char tab0C[], unsigned char tab12[], unsigned char tab1E[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x63);break;
		case 1: WriteByteSPI(0x02);break;
		default: tab02[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x63);break;
		case 1: WriteByteSPI(0x04);break;
		default: tab04[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x63);break;
		case 1: WriteByteSPI(0x0C);break;
		default: tab0C[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x63);break;
		case 1: WriteByteSPI(0x12);break;
		default: tab12[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x63);break;
		case 1: WriteByteSPI(0x1E);break;
		default: tab1E[4-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_ExternalSynchronizationControl(unsigned char tab00[], unsigned char tab04[], unsigned char tab08[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x24);break;
		default: tab00[4-i] = WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x64);break;
		case 1: WriteByteSPI(0x04);break;
		default: tab04[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x64);break;
		case 1: WriteByteSPI(0x08);break;
		default: tab08[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();

}
void Get_GPIOModeControlRegister(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x66);break;
		case 1: WriteByteSPI(0x00);break;
		default: tab00[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_GPIODirectionControlRegister(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x66);break;
		case 1: WriteByteSPI(0x08);break;
		default: tab00[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_GPIODataOutputRegister(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x66);break;
		case 1: WriteByteSPI(0x0C);break;
		default: tab00[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_GPIOInterruptEnable(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x66);break;
		case 1: WriteByteSPI(0x10);break;
		default: tab00[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_GPIOInterruptSenseSelection(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x66);break;
		case 1: WriteByteSPI(0x14);break;
		default: tab00[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_GPIOInterruptMode(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x66);break;
		case 1: WriteByteSPI(0x18);break;
		default: tab00[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_GPIOInterruptBoth_EdgeSelect(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x66);break;
		case 1: WriteByteSPI(0x1C);break;
		default: tab00[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_GPIOInterruptLatchClear(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x66);break;
		case 1: WriteByteSPI(0x20);break;
		default: tab00[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_GPIOInterruptDebounceEnable(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x66);break;
		case 1: WriteByteSPI(0x24);break;
		default: tab00[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_GPIORawState(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x66);break;
		case 1: WriteByteSPI(0x28);break;
		default: tab00[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_DigitalReceiverConfiguration(unsigned char tab02[],unsigned char tab04[], unsigned char tab06[], unsigned char tab08[], unsigned char tab20[], unsigned char tab24[], unsigned char tab26[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x67);break;
		case 1: WriteByteSPI(0x02);break;
		default: tab02[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x67);break;
		case 1: WriteByteSPI(0x04);break;
		default: tab04[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x67);break;
		case 1: WriteByteSPI(0x06);break;
		default: tab06[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x67);break;
		case 1: WriteByteSPI(0x08);break;
		default: tab08[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x67);break;
		case 1: WriteByteSPI(0x20);break;
		default: tab20[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x67);break;
		case 1: WriteByteSPI(0x24);break;
		default: tab24[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x67);break;
		case 1: WriteByteSPI(0x26);break;
		default: tab26[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_AnalogRFConfigurationBlock(unsigned char tab00[],unsigned char tab0B[], unsigned char tab0C[], unsigned char tab2C[], unsigned char tab30[], unsigned char tab34[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x68);break;
		case 1: WriteByteSPI(0x00);break;
		default: tab00[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x68);break;
		case 1: WriteByteSPI(0x0B);break;
		default: tab0B[2-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x68);break;
		case 1: WriteByteSPI(0x0C);break;
		default: tab0C[4-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x68);break;
		case 1: WriteByteSPI(0x2C);break;
		default: tab2C[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x68);break;
		case 1: WriteByteSPI(0x30);break;
		default: tab30[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x68);break;
		case 1: WriteByteSPI(0x34);break;
		default: tab34[2-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_TransimtterCalibrationBlock(unsigned char tab00[],unsigned char tab03[], unsigned char tab06[], unsigned char tab0B[], unsigned char tab0C[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6A);break;
		case 1: WriteByteSPI(0x00);break;
		default: tab00[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6A);break;
		case 1: WriteByteSPI(0x03);break;
		default: tab03[4-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6A);break;
		case 1: WriteByteSPI(0x06);break;
		default: tab06[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6A);break;
		case 1: WriteByteSPI(0x0B);break;
		default: tab0B[2-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6A);break;
		case 1: WriteByteSPI(0x0C);break;
		default: tab0C[2-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_FrequencySynthesiserControlBlock(unsigned char tab07[],unsigned char tab0B[], unsigned char tab0E[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6B);break;
		case 1: WriteByteSPI(0x07);break;
		default: tab07[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6B);break;
		case 1: WriteByteSPI(0x0B);break;
		default: tab0B[2-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6B);break;
		case 1: WriteByteSPI(0x0E);break;
		default: tab0E[2-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_AlwaysONSystemControlInterface(unsigned char tab00[],unsigned char tab02[], unsigned char tab03[], unsigned char tab04[], unsigned char tab06[], unsigned char tab0A[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6C);break;
		case 1: WriteByteSPI(0x00);break;
		default: tab00[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6C);break;
		case 1: WriteByteSPI(0x02);break;
		default: tab02[2-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6C);break;
		case 1: WriteByteSPI(0x03);break;
		default: tab03[2-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6C);break;
		case 1: WriteByteSPI(0x04);break;
		default: tab04[2-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6C);break;
		case 1: WriteByteSPI(0x06);break;
		default: tab06[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6C);break;
		case 1: WriteByteSPI(0x0A);break;
		default: tab0A[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}

void Get_OTPWriteData(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6D);break;
		case 1: WriteByteSPI(0x00);break;
		default: tab00[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_OTPAddress(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6D);break;
		case 1: WriteByteSPI(0x04);break;
		default: tab00[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_OTPControl(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6D);break;
		case 1: WriteByteSPI(0x06);break;
		default: tab00[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_OTPStatus(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6D);break;
		case 1: WriteByteSPI(0x08);break;
		default: tab00[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_OTPReadData(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6D);break;
		case 1: WriteByteSPI(0x0A);break;
		default: tab00[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_OTPSpecialRegisterReadData(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6D);break;
		case 1: WriteByteSPI(0x0E);break;
		default: tab00[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_OTPSpecialFunction(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6D);break;
		case 1: WriteByteSPI(0x12);break;
		default: tab00[2-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_LeadingEdgeDetectionInterface(unsigned char tab0000[],unsigned char tab0806[], unsigned char tab1000[], unsigned char tab1002[], unsigned char tab1804[], unsigned char tab1806[], unsigned char tab2804[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6E);break;
		case 1: WriteByteSPI(0x80);break;
		case 2: WriteByteSPI(0x00);break;
		default: tab0000[4-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6E);break;
		case 1: WriteByteSPI(0x86);break;
		case 2: WriteByteSPI(0x10);break;
		default: tab0806[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6E);break;
		case 1: WriteByteSPI(0x80);break;
		case 2: WriteByteSPI(0x20);break;
		default: tab1000[4-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6E);break;
		case 1: WriteByteSPI(0x82);break;
		case 2: WriteByteSPI(0x20);break;
		default: tab1002[4-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6E);break;
		case 1: WriteByteSPI(0x84);break;
		case 2: WriteByteSPI(0x30);break;
		default: tab1804[4-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6E);break;
		case 1: WriteByteSPI(0x86);break;
		case 2: WriteByteSPI(0x30);break;
		default: tab1806[4-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x6E);break;
		case 1: WriteByteSPI(0x84);break;
		case 2: WriteByteSPI(0x50);break;
		default: tab2804[4-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_PowerManagementAndSystemControl(unsigned char tab00[],unsigned char tab04[], unsigned char tab0C[], unsigned char tab26[], unsigned char tab28[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x76);break;
		case 1: WriteByteSPI(0x00);break;
		default: tab00[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x76);break;
		case 1: WriteByteSPI(0x04);break;
		default: tab04[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x76);break;
		case 1: WriteByteSPI(0x0C);break;
		default: tab0C[2-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x76);break;
		case 1: WriteByteSPI(0x26);break;
		default: tab26[3-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x76);break;
		case 1: WriteByteSPI(0x28);break;
		default: tab28[5-i] = WriteByteSPI(0x00);break;
		}

	}
	Transmit_Disable();
}
void Get_RXFrameBuffer(unsigned char tab00[]) // Rejestr przechowuj¹cy podstawowe ustawienia ramki transmisyjnej
{

	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x51);break;
		case 1: WriteByteSPI(0x80);break;
		case 2: WriteByteSPI(0x00);break;
		default: tab00[3-i]=WriteByteSPI(0x00);break;
		}
	}
	Transmit_Disable();

}




void Set_ID(unsigned char tab00[]) // Rejestr przechowuj¹cy ID urz¹dzenia
{

	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x80);break;
		default: WriteByteSPI(tab00[4-i]);break;
		}
	}
	Transmit_Disable();
}
void Set_SystemConfiguration(unsigned char tab00[]) // Rejestr przechowuj¹cy ID urz¹dzenia
{

	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x84);break;
		default: WriteByteSPI(tab00[4-i]);break;
		}
	}
	Transmit_Disable();
}
void Set_SystemTimeCounter(unsigned char tab00[], unsigned char tab04[]) // Rejestr przechowuj¹cy wartoœc licznika systemowego
{

	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x87);break;
		default: WriteByteSPI(tab00[4-i]);break;
		}
	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xC7);break;
		case 1: WriteByteSPI(0x04);break;
		default: WriteByteSPI(tab04[2-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_TransmitFrameControl(unsigned char tab00[], unsigned char tab04[]) // Rejestr przechowuj¹cy podstawowe ustawienia ramki transmisyjnej
{

	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x88);break;
		default: WriteByteSPI(tab00[4-i]);break;
		}
	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xC8);break;
		case 1: WriteByteSPI(0x04);break;
		default: WriteByteSPI(tab04[2-i]);break;
		}

	}
	Transmit_Disable();
}
void Stop_Transmiter(void) // Rejestr przechowuj¹cy ID urz¹dzenia
{
	unsigned char tab[4] = {0x00,0x00,0x00,0x40};
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x8D);break;
		default: WriteByteSPI(tab[4-i]);break;
		}
	}
	Transmit_Disable();
}
void Start_Transmit(void) // Rejestr przechowuj¹cy ID urz¹dzenia
{
	unsigned char tab[4] = {0x00,0x00,0x00,0x02};
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x8D);break;
		default: WriteByteSPI(tab[4-i]);break;
		}
	}
	Transmit_Disable();
}
void Start_Receiving(void) // Rejestr przechowuj¹cy ID urz¹dzenia
{
	unsigned char tab[4] = {0x00,0x00,0x01,0x00};
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x8D);break;
		default: WriteByteSPI(tab[4-i]);break;
		}
	}
	Transmit_Disable();
}
void Set_SystemControlRegister(unsigned char tab00[]) // Rejestr przechowuj¹cy ID urz¹dzenia
{

	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x8D);break;
		default: WriteByteSPI(tab00[4-i]);break;
		}
	}
	Transmit_Disable();
}
void Set_SystemEventMaskRegister(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x8E);break;
		default: WriteByteSPI(tab00[4-i]);break;
		}
	}
	Transmit_Disable();
}
void Set_SystemEventStatusRegister(unsigned char tab00[], unsigned char tab04[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x8F);break;
		default: WriteByteSPI(tab00[4-i]);break;
		}
	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xCF);break;
		case 1: WriteByteSPI(0x04);break;
		default: WriteByteSPI(tab04[2-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_RXFrameInformationRegister(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{

	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x90);break;
		default: WriteByteSPI(tab00[4-i]);break;
		}
	}
	Transmit_Disable();
}
void Set_RXFrameQualityInformation(unsigned char tab00[], unsigned char tab04[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x92);break;
		default: WriteByteSPI(tab00[4-i]);break;
		}
	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xD2);break;
		case 1: WriteByteSPI(0x04);break;
		default: WriteByteSPI(tab04[5-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_ReceiverTimeTrackingInterval(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x93);break;
		default: WriteByteSPI(tab00[4-i]);break;
		}
	}
	Transmit_Disable();
}
void Set_ReceiverTimeTrackingOffset(unsigned char tab00[], unsigned char tab04[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x94);break;
		default: WriteByteSPI(tab00[4-i]);break;
		}
	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xD4);break;
		case 1: WriteByteSPI(0x04);break;
		default: WriteByteSPI(tab04[2-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_ReceiveTimeStamp(unsigned char tab00[], unsigned char tab04[], unsigned char tab08[], unsigned char tab0C[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x95);break;
		default: WriteByteSPI(tab00[4-i]);break;
		}
	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xD5);break;
		case 1: WriteByteSPI(0x04);break;
		default: WriteByteSPI(tab04[5-i]);break;
		}

	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xD5);break;
		case 1: WriteByteSPI(0x08);break;
		default: WriteByteSPI(tab08[5-i]);break;
		}

	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xD5);break;
		case 1: WriteByteSPI(0x0C);break;
		default: WriteByteSPI(tab0C[3-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_TransmitTimeStamp(unsigned char tab00[], unsigned char tab04[], unsigned char tab08[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x97);break;
		default: WriteByteSPI(tab00[4-i]);break;
		}
	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xD7);break;
		case 1: WriteByteSPI(0x04);break;
		default: WriteByteSPI(tab04[5-i]);break;
		}

	}
	Transmit_Disable();

	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xD7);break;
		case 1: WriteByteSPI(0x08);break;
		default: WriteByteSPI(tab08[3-i]);break;
		}

	}
	Transmit_Disable();

}
void Set_TransmitterAntennaDelay(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x98);break;
		default: WriteByteSPI(tab00[2-i]);break;
		}
	}
	Transmit_Disable();
}
void Set_AcknowledgementTimeAndResponceTime(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x9A);break;
		default: WriteByteSPI(tab00[4-i]);break;
		}
	}
	Transmit_Disable();
}
void Set_SNIFFMode(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x9D);break;
		default: WriteByteSPI(tab00[4-i]);break;
		}
	}
	Transmit_Disable();
}
void Set_TransmitPowerControl(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x9E);break;
		default: WriteByteSPI(tab00[4-i]);break;
		}
	}
	Transmit_Disable();
}
void Set_ChannelControl(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x9F);break;
		default: WriteByteSPI(tab00[4-i]);break;
		}
	}
	Transmit_Disable();
}
void Set_AGCConfigurationAndControl(unsigned char tab02[], unsigned char tab04[], unsigned char tab0C[], unsigned char tab12[], unsigned char tab1E[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE3);break;
		case 1: WriteByteSPI(0x02);break;
		default: WriteByteSPI(tab02[3-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE3);break;
		case 1: WriteByteSPI(0x04);break;
		default: WriteByteSPI(tab04[3-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE3);break;
		case 1: WriteByteSPI(0x0C);break;
		default: WriteByteSPI(tab0C[5-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE3);break;
		case 1: WriteByteSPI(0x12);break;
		default: WriteByteSPI(tab12[3-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE3);break;
		case 1: WriteByteSPI(0x1E);break;
		default: WriteByteSPI(tab1E[4-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_ExternalSynchronizationControl(unsigned char tab00[], unsigned char tab04[], unsigned char tab08[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xA4);break;
		default: WriteByteSPI(tab00[4-i]);break;
		}
	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE4);break;
		case 1: WriteByteSPI(0x04);break;
		default: WriteByteSPI(tab04[5-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE4);break;
		case 1: WriteByteSPI(0x08);break;
		default: WriteByteSPI(tab08[5-i]);break;
		}

	}
	Transmit_Disable();

}
void Set_GPIOModeControlRegister(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE6);break;
		case 1: WriteByteSPI(0x00);break;
		default: WriteByteSPI(tab00[5-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_GPIODirectionControlRegister(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE6);break;
		case 1: WriteByteSPI(0x08);break;
		default: WriteByteSPI(tab00[5-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_GPIODataOutputRegister(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE6);break;
		case 1: WriteByteSPI(0x0C);break;
		default: WriteByteSPI(tab00[5-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_GPIOInterruptEnable(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE6);break;
		case 1: WriteByteSPI(0x10);break;
		default: WriteByteSPI(tab00[5-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_GPIOInterruptSenseSelection(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE6);break;
		case 1: WriteByteSPI(0x14);break;
		default: WriteByteSPI(tab00[5-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_GPIOInterruptMode(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE6);break;
		case 1: WriteByteSPI(0x18);break;
		default: WriteByteSPI(tab00[5-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_GPIOInterruptBoth_EdgeSelect(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE6);break;
		case 1: WriteByteSPI(0x1C);break;
		default: WriteByteSPI(tab00[5-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_GPIOInterruptLatchClear(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE6);break;
		case 1: WriteByteSPI(0x20);break;
		default: WriteByteSPI(tab00[5-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_GPIOInterruptDebounceEnable(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE6);break;
		case 1: WriteByteSPI(0x24);break;
		default: WriteByteSPI(tab00[5-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_GPIORawState(unsigned char tab00[])
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE6);break;
		case 1: WriteByteSPI(0x28);break;
		default: WriteByteSPI(tab00[5-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_DigitalReceiverConfiguration(unsigned char tab02[],unsigned char tab04[], unsigned char tab06[], unsigned char tab08[], unsigned char tab20[], unsigned char tab24[], unsigned char tab26[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE7);break;
		case 1: WriteByteSPI(0x02);break;
		default: WriteByteSPI(tab02[3-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE7);break;
		case 1: WriteByteSPI(0x04);break;
		default: WriteByteSPI(tab04[3-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE7);break;
		case 1: WriteByteSPI(0x06);break;
		default: WriteByteSPI(tab06[3-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE7);break;
		case 1: WriteByteSPI(0x08);break;
		default: WriteByteSPI(tab08[5-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE7);break;
		case 1: WriteByteSPI(0x20);break;
		default: WriteByteSPI(tab20[3-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE7);break;
		case 1: WriteByteSPI(0x24);break;
		default: WriteByteSPI(tab24[3-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE7);break;
		case 1: WriteByteSPI(0x26);break;
		default: WriteByteSPI(tab26[3-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_AnalogRFConfigurationBlock(unsigned char tab00[],unsigned char tab0B[], unsigned char tab0C[], unsigned char tab2C[], unsigned char tab30[], unsigned char tab34[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE8);break;
		case 1: WriteByteSPI(0x00);break;
		default: WriteByteSPI(tab00[5-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE8);break;
		case 1: WriteByteSPI(0x0B);break;
		default: WriteByteSPI(tab0B[2-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE8);break;
		case 1: WriteByteSPI(0x0C);break;
		default: WriteByteSPI(tab0C[4-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE8);break;
		case 1: WriteByteSPI(0x2C);break;
		default: WriteByteSPI(tab2C[5-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE8);break;
		case 1: WriteByteSPI(0x30);break;
		default: WriteByteSPI(tab30[5-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xE8);break;
		case 1: WriteByteSPI(0x34);break;
		default: WriteByteSPI(tab34[2-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_TransimtterCalibrationBlock(unsigned char tab00[],unsigned char tab03[], unsigned char tab06[], unsigned char tab0B[], unsigned char tab0C[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEA);break;
		case 1: WriteByteSPI(0x00);break;
		default: WriteByteSPI(tab00[3-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEA);break;
		case 1: WriteByteSPI(0x03);break;
		default: WriteByteSPI(tab03[4-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEA);break;
		case 1: WriteByteSPI(0x06);break;
		default: WriteByteSPI(tab06[3-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEA);break;
		case 1: WriteByteSPI(0x0B);break;
		default: WriteByteSPI(tab0B[2-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEA);break;
		case 1: WriteByteSPI(0x0C);break;
		default: WriteByteSPI(tab0C[2-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_FrequencySynthesiserControlBlock(unsigned char tab07[],unsigned char tab0B[], unsigned char tab0E[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEB);break;
		case 1: WriteByteSPI(0x07);break;
		default: WriteByteSPI(tab07[5-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEB);break;
		case 1: WriteByteSPI(0x0B);break;
		default: WriteByteSPI(tab0B[2-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEB);break;
		case 1: WriteByteSPI(0x0E);break;
		default: WriteByteSPI(tab0E[2-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_OTPWriteData(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xED);break;
		case 1: WriteByteSPI(0x00);break;
		default: WriteByteSPI(tab00[5-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_OTPAddress(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xED);break;
		case 1: WriteByteSPI(0x04);break;
		default: WriteByteSPI(tab00[3-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_OTPControl(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xED);break;
		case 1: WriteByteSPI(0x06);break;
		default: WriteByteSPI(tab00[3-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_OTPStatus(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xED);break;
		case 1: WriteByteSPI(0x08);break;
		default: WriteByteSPI(tab00[3-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_OTPReadData(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xED);break;
		case 1: WriteByteSPI(0x0A);break;
		default: WriteByteSPI(tab00[5-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_OTPSpecialRegisterReadData(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xED);break;
		case 1: WriteByteSPI(0x0E);break;
		default: WriteByteSPI(tab00[5-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_OTPSpecialFunction(unsigned char tab00[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xED);break;
		case 1: WriteByteSPI(0x12);break;
		default: WriteByteSPI(tab00[2-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_LeadingEdgeDetectionInterface(unsigned char tab0000[],unsigned char tab0806[], unsigned char tab1000[], unsigned char tab1002[], unsigned char tab1804[], unsigned char tab1806[], unsigned char tab2804[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEE);break;
		case 1: WriteByteSPI(0x80);break;
		case 2: WriteByteSPI(0x00);break;
		default: WriteByteSPI(tab0000[4-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEE);break;
		case 1: WriteByteSPI(0x86);break;
		case 2: WriteByteSPI(0x10);break;
		default: WriteByteSPI(tab0806[3-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEE);break;
		case 1: WriteByteSPI(0x80);break;
		case 2: WriteByteSPI(0x20);break;
		default: WriteByteSPI(tab1000[4-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEE);break;
		case 1: WriteByteSPI(0x82);break;
		case 2: WriteByteSPI(0x20);break;
		default: WriteByteSPI(tab1002[4-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEE);break;
		case 1: WriteByteSPI(0x84);break;
		case 2: WriteByteSPI(0x30);break;
		default: WriteByteSPI(tab1804[4-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEE);break;
		case 1: WriteByteSPI(0x86);break;
		case 2: WriteByteSPI(0x30);break;
		default: WriteByteSPI(tab1806[4-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 4 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEE);break;
		case 1: WriteByteSPI(0x84);break;
		case 2: WriteByteSPI(0x50);break;
		default: WriteByteSPI(tab2804[4-i]);break;
		}

	}
	Transmit_Disable();
}
void Set_PowerManagementAndSystemControl(unsigned char tab00[],unsigned char tab04[], unsigned char tab0C[], unsigned char tab26[], unsigned char tab28[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xF6);break;
		case 1: WriteByteSPI(0x00);break;
		default:WriteByteSPI(tab00[5-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xF6);break;
		case 1: WriteByteSPI(0x04);break;
		default:WriteByteSPI(tab04[5-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xF6);break;
		case 1: WriteByteSPI(0x0C);break;
		default:WriteByteSPI(tab0C[2-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xF6);break;
		case 1: WriteByteSPI(0x26);break;
		default:WriteByteSPI(tab26[3-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xF6);break;
		case 1: WriteByteSPI(0x28);break;
		default:WriteByteSPI(tab28[5-i]);break;
		}

	}
	Transmit_Disable();
}

void Set_AlwaysONSystemControlInterface(unsigned char tab00[],unsigned char tab02[], unsigned char tab03[], unsigned char tab04[], unsigned char tab06[], unsigned char tab0A[]) // 0x0F:00 jest jeszcze 04
{
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEC);break;
		case 1: WriteByteSPI(0x00);break;
		default:WriteByteSPI( tab00[3-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEC);break;
		case 1: WriteByteSPI(0x02);break;
		default:WriteByteSPI( tab02[2-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEC);break;
		case 1: WriteByteSPI(0x03);break;
		default:WriteByteSPI( tab03[2-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 2 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEC);break;
		case 1: WriteByteSPI(0x04);break;
		default:WriteByteSPI( tab04[2-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 5 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEC);break;
		case 1: WriteByteSPI(0x06);break;
		default:WriteByteSPI( tab06[5-i]);break;
		}

	}
	Transmit_Disable();
	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xEC);break;
		case 1: WriteByteSPI(0x0A);break;
		default:WriteByteSPI(tab0A[3-i]);break;
		}

	}
	Transmit_Disable();
}

void Set_TransmitBuffer(unsigned char tab00[]) // Rejestr przechowuj¹cy podstawowe ustawienia ramki transmisyjnej
{

	Transmit_Enable();
	for(int i = 0 ; i <= 10 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0x89);break;
		default: WriteByteSPI(tab00[10-i]);break;
		}
	}
	Transmit_Disable();



}
void Set_ReceiveFrameWaitTimeoutPeriod(unsigned char tab00[]) // Rejestr przechowuj¹cy podstawowe ustawienia ramki transmisyjnej
{

	Transmit_Enable();
	for(int i = 0 ; i <= 3 ; i++)
	{
		switch(i)
		{
		case 0: WriteByteSPI(0xCC);break;
		case 1: WriteByteSPI(0x00);break;
		default: WriteByteSPI(tab00[3-i]);break;
		}
	}
	Transmit_Disable();

}
