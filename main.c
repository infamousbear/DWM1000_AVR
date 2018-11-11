/*
 * main.c
 *
 *  Created on: 5 mar 2018
 *      Author: kynio
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>
#include "DWM1000_Reg_Operation.h"
#include "DWM1000_Mnemonic.h"
#include "AT_Command.h"

#define USART_BAUDRATE 19200
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define delay 2
#define DELAY 3500
void TIMER_Init(void) {
	TCCR0B |= (1 << CS00)|(1 << CS02);
	TCCR2B |= (1 << CS20);
}

void Usart_Init(void) {
	// UBRR0H = (BAUD_PRESCALE >> 8);
	UBRR0L = 0x0A;
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
}
int ESP8266_Init(void) {
	AT_CWMODE(3);
	AT_CIPMUX(1);
	AT_CWJAP("DW1000_TEST", "DW1000_TEST");
	AT_CIPSTART(1, "TCP", "192.168.0.100", "80");
	_delay_ms(DELAY);
	AT_CIPSTART(1, "TCP", "192.168.0.101", "80");
	_delay_ms(DELAY);
	AT_CIPSTART(1, "TCP", "192.168.0.102", "80");
	_delay_ms(DELAY);
	AT_CIPSTART(1, "TCP", "192.168.0.103", "80");
	_delay_ms(DELAY);
	AT_CIPSTART(1, "TCP", "192.168.0.104", "80");
	_delay_ms(DELAY);
	AT_CIPSTART(1, "TCP", "192.168.0.105", "80");
	return 0;
}
int tflag = 1;
volatile int Break_time = 0, Repeat_time = 0, Delay_time = 0;
volatile unsigned char Break_flag = 0, Repeat_flag = 0;
char Data[15],Data_Out[30];
unsigned char A1[4], A2[4], A3[4], A4[4], A5[4], A6[4], A7[4]; //0x001E3FE0
unsigned char TMP_Receive[5], TMP_Transmit[5];
unsigned char Receive_STAMP[5], Send1_STAMP[5], Send2_STAMP[5];
unsigned char AGC_TUNE2[4] = { 0x25, 0x02, 0xA9, 0x07 };
unsigned char AGC_TUNE3[2] = { 0x00, 0x35 };
unsigned char DRX_TUNE0b[2] = { 0x00, 0x01 };
unsigned char DRX_TUNE1a[2] = { 0x00, 0x87 };
unsigned char DRX_TUNE1b[2] = { 0x00, 0x20 };
unsigned char DRX_TUNE2[4] = { 0x31, 0x1A, 0x00, 0x2D };
unsigned char DRX_TUNE4H[2] = { 0x00, 0x28 };
unsigned char LDE_CFG1[1] = { 0x6D };
unsigned char LDE_CFG2[2] = { 0x16, 0x07 };
unsigned char TX_POWER[4] = { 0x0E, 0x08, 0x28, 0x48 };
unsigned char RF_RXCTRL[1] = { 0xD8 };
unsigned char RF_TXCTRL[3] = { 0x1E, 0x3F, 0xE0 };
unsigned char TC_PGDELAY[1] = { 0xC0 };
unsigned char FS_PLLCFG[4] = { 0x08, 0x00, 0x04, 0x1D };
unsigned char FS_PLLTUNE[1] = { 0xBE };
unsigned char OTP_CONTROL_Value[2] = { 0x80, 0x00 };

unsigned char BLINK[4] = { 0x00, 0x00, 0x14, 0x00 };
unsigned char BLINK_TEST[4] = { 0xDE, 0x1F, 0x01, 0x20 };

unsigned char TRANSMIT_FRAME[4] = { 0x00, 0x06, 0xC0, 0x01 };
unsigned char TRANSMIT_DATA[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
unsigned char START[4] = { 0x00, 0x00, 0x00, 0x02 };
unsigned char Reset[4] = { 0xFF, 0xFF, 0xFF, 0xFF };
unsigned char WAKEUP[2] = { 0x18, 0x00 };

void Reset_timeout(void) {
	Break_time = 0;
	Break_flag = 0;
	TCNT0 = 0;
}
void Delay(void) {
	TIMSK2 |= (1 << TOIE2);
	TCNT2 = 0;
	while (Delay_time != delay)
		;
	Delay_time = 0;
	TIMSK2 &= ~(1 << TOIE2);
}
int Distance_Measure(unsigned char Send1_STAMP[], unsigned char Send2_STAMP[], unsigned char Receive_STAMP[]
								,unsigned char TMP_Receive[], unsigned char TMP_Transmit[], char Data[], char Data_Out[])
 {
	Stop_Transmiter();
	Set_TransmitBuffer(TRANSMIT_DATA);
	Get_FastReceiveTimeStamp(Receive_STAMP);
	for (int i = 0; i < 5; i++) {
		TMP_Receive[i] = Receive_STAMP[i];

	}
	Get_FastTransmitTimeStamp(Send1_STAMP);
	for (int i = 0; i < 5; i++) {
		TMP_Transmit[i] = Send1_STAMP[i];
		Send2_STAMP[i] = Send1_STAMP[i];
	}
	Reset_timeout();
	TIMSK0 |= (1 << TOIE0);
	Start_Transmit();
	while (ArrayEqual(TMP_Transmit, Send1_STAMP)){
		Get_FastTransmitTimeStamp(Send1_STAMP);
		if(Break_flag == 1)
			return 0;
	}
	Start_Receiving();
	while (ArrayEqual(TMP_Receive, Receive_STAMP)){
		Get_FastReceiveTimeStamp(Receive_STAMP);
		if(Break_flag == 1)
			return 0;
	}
	Get_FastTransmitTimeStamp(Send1_STAMP);
	for (int i = 0; i < 5; i++) {
		TMP_Transmit[i] = Send1_STAMP[i];
		Send2_STAMP[i] = Send1_STAMP[i];
	}

	Start_Transmit();
	while (ArrayEqual(TMP_Transmit, Send2_STAMP)){
		Get_FastTransmitTimeStamp(Send2_STAMP);
		if(Break_flag == 1)
			return 0;
	}
	TIMSK0 &= ~(1 << TOIE0);
	Get_FastReceiveTimeStamp(Receive_STAMP);
	Get_FastTransmitTimeStamp(Send2_STAMP);
	for (int i = 0; i < 5; i++)
		Data[i] = Send1_STAMP[i];
	for (int i = 0; i < 5; i++)
		Data[i+ 5] = Receive_STAMP[i];
	for (int i = 0; i < 5; i++)
		Data[i + 10] = Send2_STAMP[i];
	Hex_to_ASCII(Data,Data_Out,15);
	/*
	for(int i = 0 ; i < 30 ; i++)
	{
		while (!( UCSR0A & (1<<UDRE0)));
		UDR0 = Data_Out[i];
	}
	*/
	_delay_ms(5);
	AT_CIPSEND(1,Data_Out, 1);
	return 1;
 }

int main(void) {
	DDRD &= ~(1 << PD2);
	Usart_Init();
	SPI_Init();
	TIMER_Init();
	sei();
	DDRC |= (1<<PC4);
	_delay_ms(4000);

	Get_PowerManagementAndSystemControl(A1, A2, A3, A4, A5);
	A1[2] = 0x03;
	A1[3] = 0x01;
	Set_PowerManagementAndSystemControl(A1, A2, A3, A4, A5);
	Set_OTPControl(OTP_CONTROL_Value);
	_delay_us(1000);
	Get_PowerManagementAndSystemControl(A1, A2, A3, A4, A5);
	A1[2] = 0x02;
	A1[3] = 0x00;
	Set_PowerManagementAndSystemControl(A1, A2, A3, A4, A5);

	Get_AGCConfigurationAndControl(A1, A2, A3, A4, A5);
	Set_AGCConfigurationAndControl(A1, A2, AGC_TUNE2, AGC_TUNE3, A5);

	//Get_DigitalReceiverConfiguration(A1,A2,A3,A4,A5,A6,A7);
	//Set_DigitalReceiverConfiguration(DRX_TUNE0b,DRX_TUNE1a,DRX_TUNE1b,DRX_TUNE2,A5,A6,DRX_TUNE4H);

	Get_LeadingEdgeDetectionInterface(A1, A2, A3, A4, A5, A6, A7);
	Set_LeadingEdgeDetectionInterface(A1, LDE_CFG1, A3, A4, A5, LDE_CFG2, A7);
	Set_TransmitPowerControl(TX_POWER);
	Get_AnalogRFConfigurationBlock(A1, A2, A3, A4, A5, A6);
	Set_AnalogRFConfigurationBlock(A1, RF_RXCTRL, RF_TXCTRL, A4, A5, A6);
	Get_TransimtterCalibrationBlock(A1, A2, A3, A4, A5);
	Set_TransimtterCalibrationBlock(A1, A2, A3, TC_PGDELAY, A5);
	Get_FrequencySynthesiserControlBlock(A1, A2, A3);
	Set_FrequencySynthesiserControlBlock(FS_PLLCFG, FS_PLLTUNE, A3);
	_delay_ms(4000);

	Get_AlwaysONSystemControlInterface(A1, A2, A3, A4, A5, A6);
	Set_AlwaysONSystemControlInterface(WAKEUP, A2, A3, A4, A5, A6);

	ESP8266_Init();
	//UDR0 = 0xFA;

	//Get_TransmitFrameControl(A1,A2);
	//Set_TransmitBuffer(TRANSMIT_DATA);
	//Set_TransmitFrameControl(TRANSMIT_FRAME,A2);
	SetBit("TransmitFrameControl", 4, 1, 1);
	//SetBit("TransmitFrameControl",4,16,0);
	//SetBit("TransmitFrameControl",4,17,1);
//	SetBit("SystemConfiguration",FFAD,1,1);
//	SetBit("SystemConfiguration",FFEN,1,1);
		while (1) {
			if(tflag == 1)
			{
			WaitForStart();
			_delay_ms(10);
			}
			tflag = Distance_Measure(Send1_STAMP,Send2_STAMP,Receive_STAMP,TMP_Receive,TMP_Transmit,Data,Data_Out);

		}

}

ISR(TIMER0_OVF_vect) {
	Break_time++;
	if (Break_time == 2) {
		Break_flag = 1;
		Break_time = 0;
	}
}
/*
ISR(TIMER2_OVF_vect) {
	Delay_time++;
}
*/
