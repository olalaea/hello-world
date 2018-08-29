#include <stdio.h>
#include "flash.h"

Typedef_bootParams bootParams;
extern CAN_TxHeaderTypeDef	CAN1_TXMesaji;
extern CAN_HandleTypeDef	CanHandle;

/* Tum bootloader islemlerinin kontrol edildigi state-machine fonksiyonudur.
 * CAN RX interrupt'i icerisinde cagirilmalidir. */
void bootModeControl (uint8_t canData[8])
{
	char 	canMessage[40];

	sprintf(canMessage, "0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X",
						canData[0], canData[1], canData[2], canData[3], canData[4], canData[5], canData[6], canData[7]);

	/* SEARCH islemini state machine disinda da yapabilmek icin */
	if (strcmp(canMessage, CAN_BOOTMODE_DEVICE_ID_MESSAGE) == 0)
	{
		uint8_t *idResponse = malloc(8 * sizeof(uint8_t));

		idResponse = stringToHex(CAN_BOOTMODE_DEVICE_DEFINITION);
		idResponse[7] = CAN_BOOTMODE_DEVICE_ADDRESS;

		sendBootloaderResponse(CAN_BOOTMODE_REMOTE_ADDRESS, (uint8_t *)idResponse);
	}
	else if (strstr(canMessage, CAN_BOOTMODE_SYSTEM_RESET_MSG) != NULL)
	{
		if (canData[7] == CAN_BOOTMODE_DEVICE_ADDRESS)
		{
			uint8_t *rstResponse = malloc(8 * sizeof(uint8_t));

			rstResponse = stringToHex(CAN_BOOTMODE_DEVICE_DEFINITION);
			rstResponse[7] = CAN_BOOTMODE_DEVICE_ADDRESS;

			sendBootloaderResponse(CAN_BOOTMODE_REMOTE_ADDRESS, (uint8_t *)rstResponse);
			NVIC_SystemReset();
		}
	}
	else if (strstr(canMessage, CAN_BOOTMODE_START_MESSAGE) != NULL)
	{
		if (canData[7] == CAN_BOOTMODE_DEVICE_ADDRESS)
		{
			*((unsigned long *)CONTROL_VALUE_SRAM_ADDRESS) = APPLICATION_MODE_CONTROL_VALUE;
			NVIC_SystemReset();
		}
	}
}

/* 7 Byte'lik String mesaji Byte array'e cevirmek icin kullanilir. */
void stringMessageToByteArray (char *message, uint8_t dataArray[7])
{
	message+=2;
	sscanf(message, "%02x", (unsigned int *)&dataArray[0]);

	message = strstr(message, "0x");
	message+=2;
	sscanf(message, "%02x", (unsigned int *)&dataArray[1]);

	message = strstr(message, "0x");
	message+=2;
	sscanf(message, "%02x", (unsigned int *)&dataArray[2]);

	message = strstr(message, "0x");
	message+=2;
	sscanf(message, "%02x", (unsigned int *)&dataArray[3]);

	message = strstr(message, "0x");
	message+=2;
	sscanf(message, "%02x", (unsigned int *)&dataArray[4]);

	message = strstr(message, "0x");
	message+=2;
	sscanf(message, "%02x", (unsigned int *)&dataArray[5]);

	message = strstr(message, "0x");
	message+=2;
	sscanf(message, "%02x", (unsigned int *)&dataArray[6]);
}


/* 8 Byte'lik bir string mesaji HEX'e cevirir. */
uint8_t *stringToHex (char *str)
{
	char *buffer= malloc (40 * sizeof(char));;
	char *pbuffer = buffer;

	uint8_t *hexArray = malloc (7 * sizeof(uint8_t));

	for (int i = 0; i < 8; i++)
	{
		sprintf(pbuffer, "0x%02X ", str[i]);
		pbuffer +=5;
	}

	stringMessageToByteArray (buffer, hexArray);

	return hexArray;
}

/* Bootloader islemleri esnasinda CAN uzerinden yanit gondermek icin kullanilir. */
void sendBootloaderResponse (uint32_t address, uint8_t data[8])
{
	uint8_t responseData[8];
	uint32_t TxMailbox = 0;
	
	CAN1_TXMesaji.IDE = CAN_ID_STD;
	CAN1_TXMesaji.StdId = address;
	CAN1_TXMesaji.ExtId = 0x01;
	CAN1_TXMesaji.RTR = CAN_RTR_DATA;
	CAN1_TXMesaji.DLC = 8;

	for (int i = 0; i < 8; i++)
		responseData[i] = data[i];

	HAL_CAN_AddTxMessage(&CanHandle, &CAN1_TXMesaji, (uint8_t *)responseData, &TxMailbox);
}
