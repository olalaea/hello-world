/*
 * can1.c
 *
 *  Created on: 10 May 2018
 *      Author: USER
 */

#include <io_read_write.h>
#include "stm32f4xx.h"
#include "stdio.h"
#include "config.h"
#include "general_purpose_func.h"
#include "io_pin.h"
#include "can.h"
#include "io_config.h"
#include "flash.h"

CAN_RxHeaderTypeDef CAN1_RXMesaji;
CAN_TxHeaderTypeDef CAN1_TXMesaji;
uint8_t CAN1_RxData[8];
uint8_t CAN1_TxData[8];

uint8_t CAN1_newDataFlag=0; //yeni bilgi geldiginde interrupt icinde guncelleniyor
uint8_t paket_sayisi=0, CAN_timestamp=0;
uint8_t mesaj[CAN_MESAJ_ALMA_SIZE];
uint8_t CAN_gondermeye_hazir_mesaj[1024];

uint8_t mesaj_state=BASLA;
uint16_t qos=0, paket_no=0,joystick_y_value;
uint16_t CAN_mesaji_toplam_uzunluk=72;
uint8_t mesaj_data[CAN_MESAJ_ALMA_SIZE]; //CAN'den alinip dogrulanan mesaj bu array icinde tutulur

uint32_t TxMailbox;

uint16_t FIFODataSayisi=0, FIFOKuyruk=0, FIFOKafa=0;
uint8_t FIFO[CAN_FIFO_AZAMI_BOYUT];

extern short int motor_position_flag;
extern char sendUSART2[DEBUG_SEND_MESSAGE_SIZE];

extern uint8_t firstRunFlag;
extern uint8_t firstRunCounter;
extern uint8_t firstRunCounterFlag;

extern uint8_t fastMovingFLag;
		
uint8_t CAN_gondermeye_hazirla(uint8_t alt_adres,uint8_t *gonderilecek_mesaj,uint8_t mesaj_uzunluk){
	uint16_t counter=0;
	uint8_t checksum=0;
	CAN_gondermeye_hazir_mesaj[0]=STX;
	CAN_gondermeye_hazir_mesaj[1]=alt_adres;
	CAN_gondermeye_hazir_mesaj[2]=mesaj_uzunluk;

	for(counter=0;counter<mesaj_uzunluk;counter++){
		CAN_gondermeye_hazir_mesaj[3+counter]=*gonderilecek_mesaj;
		checksum+=*gonderilecek_mesaj;
		gonderilecek_mesaj++;
	}

	CAN_gondermeye_hazir_mesaj[3+counter]=checksum+ CAN_timestamp+ mesaj_uzunluk + ADR;
	CAN_gondermeye_hazir_mesaj[4+counter]=CAN_timestamp;
	CAN_timestamp++;
	CAN_gondermeye_hazir_mesaj[5+counter]=ETX;

	return 1;
}


//CAN1 icin icine yüklenen tum bilgiyi gonderir.
//CAN_Bilgi tum bilgiyi iceren array'i
//CAN_BilgiSayisi gonderilmesi hedeflenen toplam bilgi miktarini gosterir
//her paket 8bayt oldugundan, artik paket kalir ise kalan baytlarý 0 gonderir.
uint8_t CAN1_TX(uint8_t CAN_Adresi, uint8_t *CAN_Bilgi, uint8_t CAN_BilgiSayisi)
{
	uint8_t counter=0;
	uint8_t CAN_Bilgi8Bayt_Paket[8];
	while (CAN_BilgiSayisi){
		CAN_Bilgi8Bayt_Paket[counter]=*CAN_Bilgi;
		counter++;
		CAN_Bilgi++;
		CAN_BilgiSayisi--;
		if(counter==8)
		{
			counter=0;
			CAN1_TX_8Bayt(CAN_Adresi,CAN_Bilgi8Bayt_Paket);
		}
	}
	if(counter>0){

		while(counter<8){
		 CAN_Bilgi8Bayt_Paket[counter]=0;
		 counter++;
		}
		CAN1_TX_8Bayt(CAN_Adresi,CAN_Bilgi8Bayt_Paket);

	}
	return 1;
}

//bir CAN frame gonderilmesi icin Busy Wait
void CAN_TX_Bekle()
{
	uint16_t counter = 0;
	while(counter != 0x9FF ){
		counter++;
	}
}
//CAN1 uzerinden 8 bayt bilgi gonderir,
//tum CAN1 iletisim paketleri 8 bayt olacaktir.
//CAN_Adresi bilginin gonderilecegi hedefi
//CAN_8Bayt_Bilgi 8 baytlik TX array'i gosterir
uint8_t CAN1_TX_8Bayt(uint8_t CAN_Adresi, uint8_t CAN_8BaytBilgi[REMOTE_WRITE_SIZE])
{
	uint8_t counter=0;
	CAN1_TXMesaji.IDE = CAN_ID_STD;
	CAN1_TXMesaji.StdId = CAN_Adresi;
	CAN1_TXMesaji.ExtId = CAN_KENDI_ADRESI;
	CAN1_TXMesaji.RTR = CAN_RTR_DATA;
	CAN1_TXMesaji.DLC = REMOTE_WRITE_SIZE;

	//sprintf(CAN1_TXMesaji.Data,CAN_8BaytBilgi);
	while(counter<REMOTE_WRITE_SIZE){
		CAN1_TxData[counter]=CAN_8BaytBilgi[counter];
		counter++;
	}
	HAL_CAN_AddTxMessage(&CanHandle, &CAN1_TXMesaji, (uint8_t *)CAN1_TxData, &TxMailbox);
	CAN_TX_Bekle();
	paket_sayisi++;
	return 1;
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CAN1_RXMesaji, CAN1_RxData);
	CAN1_newDataFlag=1;
	CAN1_RX8Bayt();
	bootModeControl(CAN1_RxData);
}

//CAN1'den 8bayt bilgiyi alip CAN1_uzun_buffera yaziyor.
//Bu ya main altinda,
//if(CAN1_newDataFlag)
// CAN1_RX8Bayt()   seklinde bulundurulmalidir, ya da interrupt icine yazilmalidir.
//CAN datasi geldiginde okunmak uzere CAN1_uzun_buffer'a yazar.
//
uint8_t CAN1_RX8Bayt(){
	uint8_t counter=0;

	if(!CAN1_newDataFlag){
		return 0;
	}
	CAN1_newDataFlag=0;
	for (counter=0;counter<8;counter++)
		FIFO_push(CAN1_RxData[counter]);
	return 1;
}


uint8_t CAN1_RX(uint8_t *CAN_Bilgi,uint16_t CAN_BilgiSayisi)
{
	uint16_t counter=0;
	if(FIFODataSayisi<CAN_BilgiSayisi)
		return 0; // Hatali istek yapilmis

	for (counter=0;counter<CAN_BilgiSayisi;counter++)
	{
		*CAN_Bilgi=FIFO_pull();
		CAN_Bilgi++;
	}
	
	return 1;
}

uint8_t FIFO_data_dolu_mu(void)
{
	if(FIFODataSayisi<CAN_FIFO_AZAMI_BOYUT)
		return 0;
	return 1;
}

uint8_t FIFO_data_var_mi(void)
{
	if(FIFODataSayisi>0)
		return 1;
	return 0;
}

uint8_t FIFO_data_sayisi_kac(void)
{
	return FIFODataSayisi;
}

uint8_t FIFO_push(uint8_t data)
{
	if(!FIFO_data_dolu_mu())
	{
		FIFO[FIFOKafa]=data;
		if(FIFOKafa<(CAN_FIFO_AZAMI_BOYUT-1))
			FIFOKafa++;
		else
			FIFOKafa=0;
		FIFODataSayisi++;
		return 1;
	}
	else
		return 0;
}


uint8_t FIFO_pull(void)
{
	uint8_t data=0;
	if(FIFO_data_var_mi())
	{
		data=FIFO[FIFOKuyruk];
		if(FIFOKuyruk<(CAN_FIFO_AZAMI_BOYUT-1))
		{
			FIFOKuyruk++;
		}
		else
			FIFOKuyruk=0;
		FIFODataSayisi--;
		return data;
	}
	return 0;

}

void CAN1_FIFO_temizle(void)
{
	FIFODataSayisi=0;
	FIFOKuyruk=0;
	FIFOKafa=0;
}

uint8_t mesaj_dogrulama(void){
	uint16_t counter=0, counter_data=0;
	uint8_t mesaj_data_uzunluk=0;
	uint8_t checksum_hesaplanan=0, checksum_okunan=0, timestamp;

	while(counter<CAN_mesaji_toplam_uzunluk)
	{
		switch(mesaj_state)
		{
			case BASLA:
				if(mesaj[counter]==STX)
					mesaj_state=ADRES;
				counter++;
				break;
			case ADRES:
				if(mesaj[counter]==0x04)
					mesaj_state=DATA;
				else
				{	mesaj_state=BASLA;
					qos++;
				}
					counter++;
				break;
			case DATA:
				mesaj_data_uzunluk=mesaj[counter];
				counter++;
				for(counter_data=0;counter_data<mesaj_data_uzunluk;counter_data++)
				{
					mesaj_data[counter_data]=mesaj[counter];
					checksum_hesaplanan+= mesaj_data[counter_data];
					counter++;
				}
				checksum_okunan= mesaj[counter];
				counter++;
				timestamp= mesaj[counter];
				counter++;
				mesaj_state=SON;
				break;
			case SON:
				if(mesaj[counter]==ETX)
					mesaj_state=CHECKSUM;
				else
				{	mesaj_state=BASLA;
					qos++;
				}
				counter++;
				break;
			case CHECKSUM:
				checksum_hesaplanan=checksum_hesaplanan+mesaj_data_uzunluk+timestamp;
				if(checksum_hesaplanan!=checksum_okunan)
				{
					mesaj_state=BASLA;
					qos++;
					counter++;
					//PARSE_mesaj_data[countr_data];
				}
				else
				{
					mesaj_state=BASLA;
					paket_no++;
					//(PARSE_mesaj_data[counter_data])
					return 1; //mesaj bitti dogru paket mesaj_data icinde dondu.
				}
				break;
			default:
				break;

			}//switch
	}//while
	return 0; //mesaj bitti, dogru paketi bulamadik
}
uint16_t joystick_y_old_value=0;
void parse_CAN_message(void){
	uint8_t var;	char gaz[4];
	if(mesaj_dogrulama()){
		zeroChar(gaz,4);
		copyChar(gaz,sendUSART2,4,23);
		joystick_y_value = 0;
		joystick_y_value += (gaz[0] - 0x30);				// (char to int converter)
		for (var = 1; var < 4; var++) {
			joystick_y_value *=10;
			joystick_y_value += (gaz[var] - 0x30);			
		}
		
		if (firstRunCounterFlag) firstRunCounter++;
		
		if (abs(joystick_y_value - joystick_y_old_value) > 100)
			fastMovingFLag = 1;
		else
			fastMovingFLag = 0;
		
		joystick_y_old_value = joystick_y_value;
		
		if (firstRunCounter >= 50)
		{
			firstRunCounterFlag = 0;
			firstRunCounter = 0;
			firstRunFlag = 1;
		}
	}
}
