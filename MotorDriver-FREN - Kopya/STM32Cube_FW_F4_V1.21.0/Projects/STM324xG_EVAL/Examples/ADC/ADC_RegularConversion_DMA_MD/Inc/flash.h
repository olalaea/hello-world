/**
  ******************************************************************************
  * STM32 Bootloader
  ******************************************************************************
  * @author Asim Ahmed Demir
  * @file   flash.h
  * @brief  Flash Memory Header File
  *	        This file contains the flash configuration parameters,
  *	        function prototypes and other required macros and definitions.
  * @see    Please don't change anything without reading the related document!
  ******************************************************************************
  * Copyright (c) 2018 Best Grup Defence                  https://best-grup.com/
  ******************************************************************************
**/

#ifndef FLASH_H_
#define FLASH_H_

/* Includes *******************************************************************/
#include "stm32f4xx.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* Flash Memory Sector Addresses **********************************************/
#define ADDR_FLASH_SECTOR_0     		((uint32_t)0x08000000)		/*	Base address of Sector 0, 16 Kbytes		*/
#define ADDR_FLASH_SECTOR_1  		   	((uint32_t)0x08004000) 		/*	Base address of Sector 1, 16 Kbytes		*/
#define ADDR_FLASH_SECTOR_2  		   	((uint32_t)0x08008000) 		/*	Base address of Sector 2, 16 Kbytes 	*/
#define ADDR_FLASH_SECTOR_3   		  	((uint32_t)0x0800C000) 		/*	Base address of Sector 3, 16 Kbytes 	*/
#define ADDR_FLASH_SECTOR_4    		 	((uint32_t)0x08010000) 		/*	Base address of Sector 4, 64 Kbytes 	*/
#define ADDR_FLASH_SECTOR_5    			((uint32_t)0x08020000) 		/*	Base address of Sector 5, 128 Kbytes	*/
#define ADDR_FLASH_SECTOR_6     		((uint32_t)0x08040000) 		/*	Base address of Sector 6, 128 Kbytes 	*/
#define ADDR_FLASH_SECTOR_7     		((uint32_t)0x08060000) 		/*	Base address of Sector 7, 128 Kbytes 	*/
#define ADDR_FLASH_SECTOR_8    		 	((uint32_t)0x08080000) 		/*	Base address of Sector 8, 128 Kbytes 	*/
#define ADDR_FLASH_SECTOR_9    			((uint32_t)0x080A0000) 		/*	Base address of Sector 9, 128 Kbytes 	*/
#define ADDR_FLASH_SECTOR_10     		((uint32_t)0x080C0000) 		/*	Base address of Sector 10, 128 Kbytes	*/
#define ADDR_FLASH_SECTOR_11     		((uint32_t)0x080E0000) 		/*	Base address of Sector 11, 128 Kbytes	*/
#define ADDR_FLASH_SECTOR_11_END		((uint32_t)0x080FFFFF) 		/*	End address of Sector 11  				*/

/* Bootloader Mode Config Values **********************************************/
#define APPLICATION_SOFTWARE			0							/*	If the software is bootloader, this value must be 0. 	*/
#define BOOTLOADER_STATE_TIMEOUT		3000						/*	Bootloader state timeout value (ms).					*/
#define APP_VTOR_OFFSET					APP_START_ADDRESS - ADDR_FLASH_SECTOR_0

/* Application Space Addresses ************************************************/
#define APP_START_ADDRESS				(uint32_t)0x080E0000U		/*	Start address of application space in flash				*/
#define APP_END_ADDRESS					(uint32_t)0x080FFFFBU    	/*	End address of application space (addr. of last byte)	*/
#define APP_VTOR_OFFSET					APP_START_ADDRESS - ADDR_FLASH_SECTOR_0

/* SRAM Control Definitions ***************************************************/
#define CONTROL_VALUE_SRAM_ADDRESS		(uint32_t)0x20003FF0U		/*	The address of the bootloader control value in the SRAM */
#define BOOTLOADER_MODE_CONTROL_VALUE	(uint32_t)0x626F6F74U		/*	The bootloader mode control value. This value will be used in SystemInit function to check whether bootloader mode is enabled */
#define APPLICATION_MODE_CONTROL_VALUE	(uint32_t)0x61707062U		/*	The boot mode control value for application software. 	*/

/* CAN Communication Message Definitions **************************************/
#define CAN_BOOTMODE_REMOTE_ADDRESS		(uint32_t)11								/* Address of remote station 						*/
#define CAN_BOOTMODE_DEVICE_ADDRESS		(uint8_t)0x0B								/* Device CAN Address (ignores other IDs' messages) */
#define CAN_BOOTMODE_DEVICE_DEFINITION	"MTRDRVR"									/* Device ID Definitions (must be 7 letters) 		*/
#define CAN_BOOTMODE_START_MESSAGE		"0x42 0x6F 0x6F 0x74 0x4D 0x6F 0x64"		/* BootMOD */ /* Address will be added to the end	*/
#define CAN_BOOTMODE_ERASE_MESSAGE		"0x45 0x72 0x61 0x73 0x65 0x46 0x4C"		/* EraseFL */ /* Address will be added to the end	*/
#define CAN_BOOTMODE_ACK_MESSAGE		"0x44 0x61 0x74 0x61 0x41 0x43 0x4B"		/* DataACK */ /* Address will be added to the end	*/
#define CAN_BOOTMODE_FINISH_MESSAGE		"0x42 0x6F 0x6F 0x74 0x45 0x4E 0x44"		/* BootEND */ /* Address will be added to the end	*/
#define CAN_BOOTMODE_ERROR_MESSAGE		"0x45 0x72 0x72 0x6F 0x72 0x42 0x4C"		/* ErrorBL */ /* Address will be added to the end	*/
#define CAN_BOOTMODE_JUMP_MESSAGE		"0x4A 0x75 0x6D 0x70 0x4E 0x45 0x57"		/* JumpNEW */ /* Address will be added to the end	*/
#define CAN_BOOTMODE_SYSTEM_RESET_MSG	"0x73 0x79 0x73 0x5F 0x52 0x53 0x54"		/* sys_RST */ /* Address will be added to the end	*/
#define CAN_BOOTMODE_DEVICE_ID_MESSAGE	"0x44 0x65 0x76 0x69 0x63 0x65 0x49 0x44"	/* DeviceID */

/* Typedefs Structs ----------------------------------------------------------*/
typedef enum
{
	BL_IDLE = 0,
	BL_ERASE,
	BL_PROGRAM,
	BL_JUMP
} Typedef_bootStatus;

typedef struct
{
	Typedef_bootStatus	status;
	uint32_t address;
	uint32_t statusTimeout;
	uint8_t  rawData[7];
	bool	 firstDataFlag;
} Typedef_bootParams;

/* Private typedef -----------------------------------------------------------*/
typedef void (*pFunction)(void);

/* Extern --------------------------------------------------------------------*/
extern Typedef_bootParams bootParams;

/* Function Prototypes -------------------------------------------------------*/
void bootModeControl (uint8_t canData[8]);
uint8_t *stringToHex (char *str);
void stringMessageToByteArray (char *message, uint8_t dataArray[7]);
void sendBootloaderResponse (uint32_t address, uint8_t data[8]);

#endif /* FLASH_H_ */

