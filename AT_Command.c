/*
 * AT_Command.c
 *
 *  Created on: 4 sie 2018
 *      Author: 3ctko
 */

#include "AT_Command.h"
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
char* TAB[] = {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};
char ASCII_sign(int sign)
{
	switch(sign)
	{
	case 0: return *"0";
	case 1: return *"1";
	case 2: return *"2";
	case 3: return *"3";
	case 4: return *"4";
	case 5: return *"5";
	case 6: return *"6";
	case 7: return *"7";
	case 8: return *"8";
	case 9: return *"9";
	case 10: return *"A";
	case 11: return *"B";
	case 12: return *"C";
	case 13: return *"D";
	case 14: return *"E";
	case 15: return *"F";

	}
	return *"0";
}
void Hex_to_ASCII(char HEX[], char ASCII[], int Tab_size)
{
	int HEX_4b[30] = {0};
	for(int i = 0 ; i < Tab_size ; i++)
	{
		if((HEX[i] & (1<<7))>0)
			HEX_4b[2*i] += 8;
		if((HEX[i] & (1<<6))>0)
			HEX_4b[2*i] += 4;
		if((HEX[i] & (1<<5))>0)
			HEX_4b[2*i] += 2;
		if((HEX[i] & (1<<4))>0)
			HEX_4b[2*i] += 1;
		if((HEX[i] & (1<<3))>0)
			HEX_4b[2*i+1] += 8;
		if((HEX[i] & (1<<2))>0)
			HEX_4b[2*i+1] += 4;
		if((HEX[i] & (1<<1))>0)
			HEX_4b[2*i+1] += 2;
		if((HEX[i] & (1<<0))>0)
			HEX_4b[2*i+1] += 1;

	}
	for(int i = 0 ; i < Tab_size ; i++)
	{
		ASCII[2*i] = ASCII_sign(HEX_4b[2*i]);
		ASCII[2*i+1] = ASCII_sign(HEX_4b[2*i+1]);
	}
}

int Count_Array(char* arr)
{
	int count = 0;
	while(arr[count] != 0x00)
	{
		count++;
	}
	return count;
}
void End_Line(void)
{
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = 0x0D;
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = 0x0A;
	while (!( UCSR0A & (1<<UDRE0)));

}
void WaitIfOK(void)
{
	char check_text[] = "OK\r\n";
	char check[4]={0};
	while( !(strncmp(check,check_text,4)==0))
	{
			while (!( UCSR0A & (1<<RXC0)));
			check[0] = check[1];
			check[1] = check[2];
			check[2] = check[3];
			check[3]= UDR0;
	}

}
void WaitForStart(void)
{
	char check_text[] = ":ok";
	char check[3]={0};
	while( !(strncmp(check,check_text,3)==0))
	{
			while (!( UCSR0A & (1<<RXC0)));
			check[0] = check[1];
			check[1] = check[2];
			check[2] = UDR0;
	}

}
void AT(void)
{
	char TMP[] = "AT";
	int TMP_Size = (sizeof(TMP)/sizeof(*TMP))-1,j = 0;
	while(!(TMP_Size == j))
	{
		while (!( UCSR0A & (1<<UDRE0)));
		UDR0 = TMP[j];
		j++;
	}
	End_Line();
	WaitIfOK();
}
void AT_RST(void)
{
	char TMP[] = "AT+RST";
	int TMP_Size = sizeof(TMP)/sizeof(*TMP),j = 0;
	while(!(TMP_Size == j+1))
	{
		while (!( UCSR0A & (1<<UDRE0)));
		UDR0 = TMP[j];
		j++;
	}
	End_Line();
	WaitIfOK();
}
void AT_CWJAP(char* SSID, char* Password)
{
	int SSID_Size =Count_Array(SSID);
	int Password_Size = Count_Array(Password);
	char TMP[9] = "AT+CWJAP=";
	int i = 9,j = 0;
	while(!(i == j))
	{
		while (!( UCSR0A & (1<<UDRE0)));
		UDR0 = TMP[j];
		j++;
	}
	j = 0;
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = *"\"";
	while(!(SSID_Size == j))
	{
		while (!( UCSR0A & (1<<UDRE0)));
		UDR0 = SSID[j];
		j++;
	}
	j = 0;
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = *"\"";
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = *",";
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = *"\"";
	while(!(Password_Size == j))
	{
		while (!( UCSR0A & (1<<UDRE0)));
		UDR0 = Password[j];
		j++;
	}
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = *"\"";
	while (!( UCSR0A & (1<<UDRE0)));
	End_Line();
	WaitIfOK();
}
void AT_CWMODE(int mode)
{
	char TMP[] = "AT+CWMODE=";
	int TMP_Size = sizeof(TMP)/sizeof(*TMP)-1,j = 0;
	while(!(TMP_Size == j))
	{
		while (!( UCSR0A & (1<<UDRE0)));
		UDR0 = TMP[j];
		j++;
	}
	while (!( UCSR0A & (1<<UDRE0)));
	switch(mode)
	{
	case 1: UDR0 = *"1";break;
	case 2: UDR0 = *"2";break;
	case 3: UDR0 = *"3";break;
	}
	End_Line();
	WaitIfOK();
}
void AT_CIPMUX(int mode)
{
	char TMP[] = "AT+CIPMUX=";
	int TMP_Size = sizeof(TMP)/sizeof(*TMP)-1,j = 0;
	while(!(TMP_Size == j))
	{
		while (!( UCSR0A & (1<<UDRE0)));
		UDR0 = TMP[j];
		j++;
	}
	while (!( UCSR0A & (1<<UDRE0)));
	switch(mode)
	{
	case 0: UDR0 = *"0";break;
	case 1: UDR0 = *"1";break;
	}
	End_Line();
	WaitIfOK();
}
void AT_CIPSTART(int ID, char* Type, char* IP, char* Port)
{

	int Type_Size = Count_Array(Type);
	//UDR0 = Type_Size;
	int IP_Size = Count_Array(IP);
	int Port_Size = Count_Array(Port);
	char TMP[12] = "AT+CIPSTART=";
	int i = 12,j = 0;
	while(!(i == j))
	{
		while (!( UCSR0A & (1<<UDRE0)));
		UDR0 = TMP[j];
		j++;
	}
	j = 0;
	while (!( UCSR0A & (1<<UDRE0)));
	switch(ID)
	{
	case 0: UDR0 = *"0";break;
	case 1: UDR0 = *"1";break;
	case 2: UDR0 = *"2";break;
	case 3: UDR0 = *"3";break;
	case 4: UDR0 = *"4";break;
	}
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = *",";
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = *"\"";
	while(!(Type_Size == j))
	{
		while (!( UCSR0A & (1<<UDRE0)));
		UDR0 = Type[j];
		j++;
	}
	j = 0;
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = *"\"";
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = *",";
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = *"\"";
	while(!(IP_Size == j))
	{
		while (!( UCSR0A & (1<<UDRE0)));
		UDR0 = IP[j];
		j++;
	}
	j = 0;
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = *"\"";
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = *",";
	while (!( UCSR0A & (1<<UDRE0)));
	while(!(Port_Size == j))
	{
		while (!( UCSR0A & (1<<UDRE0)));
		UDR0 = Port[j];
		j++;
	}
	End_Line();
}
void AT_CIPSEND(int ID,  char* Data, int Device_ID)
{
	char TMP[12] = "AAT+CIPSEND=";
	char Device[7] = "Device_";
	int Data_Size = 39;
	int x;
	if(Data_Size < 10)
		x = 1;
	else
		x = 2;
	char Bytes[x];
	itoa(Data_Size,Bytes,10);
	int TMP_Size = 12, j = 1;
	while(!(TMP_Size == j))
	{
		while (!( UCSR0A & (1<<UDRE0)));
		UDR0 = TMP[j];
		j++;
	}
	j = 0;
	while (!( UCSR0A & (1<<UDRE0)));
	switch(ID)
	{
	case 0: UDR0 = *"0";break;
	case 1: UDR0 = *"1";break;
	case 2: UDR0 = *"2";break;
	case 3: UDR0 = *"3";break;
	case 4: UDR0 = *"4";break;
	}
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = *",";
	while(!(j == x))
	{
		while (!( UCSR0A & (1<<UDRE0)));
		UDR0 = Bytes[j];
		j++;
	}
	j = 0;
	End_Line();
	_delay_ms(20);
	//while(!(UDR0 == 62));
	while(!(j == 7))
	{
		while (!( UCSR0A & (1<<UDRE0)));
		UDR0 = Device[j];
		j++;
	}
	j=0;
	while (!( UCSR0A & (1<<UDRE0)));
	switch(Device_ID)
	{
	case 1: UDR0 = *"1";break;
	case 2: UDR0 = *"2";break;
	case 3: UDR0 = *"3";break;
	case 4: UDR0 = *"4";break;
	}
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = *":";
	while(!(Data_Size == j))
	{
		while (!( UCSR0A & (1<<UDRE0)));
		UDR0 = Data[j];
		j++;
	}
}

