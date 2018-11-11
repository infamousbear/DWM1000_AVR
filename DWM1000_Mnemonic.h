/*
 * DWM1000_Mnemonic.h
 *
 *  Created on: 19.04.2018
 *      Author: Smith
 */

#ifndef DWM1000_MNEMONIC_H_
#define DWM1000_MNEMONIC_H_

// Device Identifier (0x00)
#define REV 0
#define VER 4
#define MODEL 8
#define RIDTAG 16

// System Configuration (0x04)

#define FFEN 0
#define FFBC 1
#define FFAB 2
#define FFAD 3
#define FFAA 4
#define FFAM 5
#define FFER 6
#define FFA4 7
#define FFA5 8
#define HIRQ_POL 9
#define SPI_EDGE 10
#define DIS_FCE 11
#define DIS_DRXB 12
#define DIS_PHE 13
#define DIS_RSDE 14
#define FCS_INIT2F 15
#define PHR_MODE 16
#define DIS_STXP 18
#define RXM110K 22
#define RXWTOE 28
#define RXAUTR 29
#define AUTOACK 30
#define AACKPEND 31

// Transmit Frame Control (0x08:00)

#define TFLEN 0
#define TFLE 7
#define R 10
#define TXBR 13
#define TR 15
#define TXPRF 16
#define PE 20
#define TXBOFFS 22

// ---||--- (0x008:04)

#define IFSDELAY 0

// Receive Frame Wait Timeout Period (0x0C)

#define RXFWTO 0

//System Control Register (0x0D)

#define SFCTS 0
#define TXSTRT 1
#define TXDLYS 2
#define CANSFCS 3
#define TRXOFF 6
#define WAIT4RESP 7
#define RXENAB 8
#define RXDLYE 9
#define HRBPT 24

// System Event Mask Register (0x0E)

#define MCPLOCK 1
#define MESYNCR 2
#define MAAT 3
#define MTXFRB 4
#define MTXPRS 5
#define MTXPHS 6
#define MTXFRS 7
#define MRXPRD 8
#define MRXSFDD 9
#define MLDEDON 10
#define MRXPHD 11
#define MRXPHE 12
#define MRXDFR 13
#define MRXFCG 14
#define MRXFCE 15
#define MRXRFSL 16
#define MRXRFTO 17
#define MLDEERR 18
#define MRXOVRR 20
#define MRXPTO 21
#define MGPIOIRQ 22
#define MSLP2INIT 23
#define MRFPLLLL 24
#define MPLLHILO 25
#define MRXSFDTO 26
#define MHPDWARN 27
#define MTXBERR 28
#define MAFFREJ 29

// System Event Status Register (0x0F:00)

#define IRQS 0
#define CPLOCK 1
#define ESYNCR 2
#define AAT 3
#define TXFRB 4
#define TXPRS 5
#define TXPHS 6
#define TXFRS 7
#define RXPRD 8
#define RXSFDD 9
#define LDEDONE 10
#define RXPHD 11
#define RXPHE 12
#define RXDFR 13
#define RXFCG 14
#define RXFCE 15
#define RXRFSL 16
#define RXRFTO 17
#define LDEERR 18
#define RX0VRR 20
#define RXPTO 21
#define GPIOIRQ 22
#define SLP2INIT 23
#define RFPLL_LL 24
#define CLKPLL_LL 25
#define RXSFDTO 26
#define HPDWARN 27
#define TXBERR 28
#define AFFREJ 29
#define HSRBP 30
#define ICRBP 31

// ---||--- (0x0F:04)

#define RXRSCS 0
#define RXPREJ 1
#define TXPUTE 2

// RX Frame Information Register (0x10)

#define RXFLEN 0
#define RXFLE 7
#define RXNSPL 11
#define RXBR 13
#define RNG 15
#define RXPRF 16
#define RXPSR 18
#define RXPACC 20

// RX Frame Quality Information (0x12:00)

#define STD_NOISE 0
#define FP_AMPL2 16

// ---||--- (0x12:04)

#define PP_AMPL3 0
#define CIR_PWR 16

// Receiver Time Tracking Offset (0x14:00)

#define RXTOFS 0
#define RSMPDEL 24

// ---||--- (0x14:04)

#define RCPHASE 0

// Receive Time Stamp (0x15:00)

#define RX_STAMP_L 0

// ---||--- (0x15:04)

#define RX_STAMP_H 0
#define FP_INDEX 8
#define FP_AMPL1_L 24

// ---||--- (0X15:08)

#define FP_AMPL1_H 0
#define RX_RAWST_L 8

// ---||--- (0x15:0C)

#define RX_RAWST_H 0

// Transmit Time Stamp (0x17:00)

#define TX_STAMP_L 0

// ---||--- (0x17:04)

#define TX_STAMP_H 0
#define TX_RAWST_L 8

// ---||--- (0x17:08)

#define TX_RAWST_H 0

// Acknowledgement Time and Response Time (0x1A)

#define W4R_TIM 0
#define ACK_TIM 24

// SNIFF Mode (0x1D)

#define SNIFF_ONT 0
#define SNIFF_OFFT 8

// Transmit Power Control (0x1E)

#define BOOSTNORM 0
#define BOOSTP500 8
#define BOOSTP250 16
#define BOOSTP125 24

// Channel Control (0x1F)

#define TX_CHAN 0
#define RX_CHAN 4
#define DWSFD 17
#define RXPRF1 18
#define TNSSFD 20
#define RNSSFD 21
#define TX_PCODE 22
#define RX_PCODE 27

// AGC Configuration and Control Overview (0x23:02)

#define DIS_AM 0

// ---||--- (0x23:1E)

#define EDG1 6
#define EDV2 11

// External Synchronization Control (0x24:00)

#define OSTSM 0
#define OSRSM 1
#define PLLLDT 2
#define WAIT 3
#define OSTRM 11

// GPIO_MODE (0x26)

#define MSGP0 6
#define MSGP1 8
#define MSGP2 10
#define MSGP3 12
#define MSGP4 14
#define MSGP5 16
#define MSGP6 18
#define MSGP7 20
#define MSGP8 22

//GPIO_Direction_Control_Register

#define GDP0 0
#define GDP1 1
#define GDP2 2
#define GDP3 3
#define GDM0 4
#define GDM1 5
#define GDM2 6
#define GDM3 7
#define GDP4 8
#define GDP5 9
#define GDP6 10
#define GDP7 11
#define GDM4 12
#define GDM5 13
#define GDM6 14
#define GDM7 15
#define GDP8 16
#define GDM8 20

//GPIO_Data_Output_Register

#define GOP0 0
#define GOP1 1
#define GOP2 2
#define GOP3 3
#define GOM0 4
#define GOM1 5
#define GOM2 6
#define GOM3 7
#define GOP4 8
#define GOP5 9
#define GOP6 10
#define GOP7 11
#define GOM4 12
#define GOM5 13
#define GOM6 14
#define GOM7 15
#define GOP8 16
#define GOM8 20

//GPIO_Interrupt_Enable_Register

#define GIRQE0 0
#define GIRQE1 1
#define GIRQE2 2
#define GIRQE3 3
#define GIRQE4 4
#define GIRQE5 5
#define GIRQE6 6
#define GIRQE7 7
#define GIRQE8 8

//GPIO_Interrupt_Sense_Selection_Register

#define GISEN0 0
#define GISEN1 1
#define GISEN2 2
#define GISEN3 3
#define GISEN4 4
#define GISEN5 5
#define GISEN6 6
#define GISEN7 7
#define GISEN8 8

//GPIO_Interrupt_Mode

#define GIMOD0 0
#define GIMOD1 1
#define GIMOD2 2
#define GIMOD3 3
#define GIMOD4 4
#define GIMOD5 5
#define GIMOD6 6
#define GIMOD7 7
#define GIMOD8 8

//GPIO_Both_Edge_Mode

#define GIBES0 0
#define GIBES1 1
#define GIBES2 2
#define GIBES3 3
#define GIBES4 4
#define GIBES5 5
#define GIBES6 6
#define GIBES7 7
#define GIBES8 8


//GPIO_Raw_State

#define GRAWP0 0
#define GRAWP1 1
#define GRAWP2 2
#define GRAWP3 3
#define GRAWP4 4
#define GRAWP5 5
#define GRAWP6 6
#define GRAWP7 7
#define GRAWP8 8

//RF_Configuration_Register

#define TXFEN 8
#define PLLFEN 13
#define LDOFEN 16
#define TXRXSW 21

//Transmitter_Analog_Settings

#define TXMTUNE 5
#define TXMQ 9

//RF_Status_Register

#define CPLLLOCK 0
#define CPLLLOW 1
#define CPLLHIGH 2
#define RFPLLLOCK 3

//Transmitter_Calibration_SAR_Control

#define SAR_CTRL 0

//Transmitter_Calibration_Latest_SAR_Readings

#define SAR_LVBAT 0
#define SAR_LTEMP 8

//Transmitter_Calibration_SAR_Readings_Last_Wake_Up

#define SAR_WVBAT 0
#define SAR_WTEMP 8

//Frequency_Synthesiser_Crystal_Trim

#define XTALT 0

//AON_Wake_Up_Configuration_Register

#define ONW_RADC 0
#define ONW_RX 1
#define ONW_LEUI 3
#define ONW_LDC 6
#define ONW_L64P 7
#define PRES_SLEEP 8
#define ONW_LLDE 11
#define ONW_LLDO 12

//AON_Control_Register

#define RESTORE 0
#define SAVE 1
#define UPL_CFG 2
#define DCA_READ 3
#define DCA_ENAB 7

//AON_Configuration_Register_0

#define SLEEP_EN 0
#define WAKE_PIN 1
#define WAKE_SPI 2
#define WAKE_CNT 3
#define LPDIV_EN 4
#define LPCLKDIVA 5
#define SLEEP_TIM 16

//AON_Configuration_Register_1

#define SLEEP_CEN 0
#define SMXX 1
#define LPOSC_CAL 2

//OTP_Address

#define OTPADDR 0

//OTP_Control

#define OTPRDEN 0
#define OTPREAD 1
#define OTPMRWR 3
#define OTPPROG 6
#define OTPMR 7
#define LDELOAD 15

//OTP_Status

#define OTPPRGD 0
#define OTPVPOK 1

//OTP_Special_Function

#define OPS_KICK 0
#define LDO_KICK 1
#define OPS_SEL 5

//LDE_Configuration_Register

#define NTM 0
#define PMULT 4





#endif /* DWM1000_MNEMONIC_H_ */
