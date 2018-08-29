/*
 * can1.h
 *
 *  Created on: 10 May 2018
 *      Author: USER
 */

#ifndef CAN_H_
#define CAN_H_

#include <stdint.h>

uint8_t CAN1_TX_8Bayt(uint8_t CAN_Adresi, uint8_t *CAN_8BaytBilgi);
uint8_t CAN1_TX(uint8_t CAN_Adresi, uint8_t *CAN_Bilgi, uint8_t CAN_BilgiSayisi);

uint8_t CAN1_RX8Bayt(void);
uint8_t CAN1_RX(uint8_t *CAN_Bilgi,uint16_t CAN_BilgiSayisi);
void CAN1_RX0_IRQHandler(void);

uint8_t FIFO_data_dolu_mu(void);
uint8_t FIFO_pull(void);
uint8_t FIFO_push(uint8_t data);
uint8_t FIFO_data_var_mi(void);

void CAN1_FIFO_temizle(void);
uint8_t CAN_gondermeye_hazirla(uint8_t alt_adres,uint8_t *gonderilecek_mesaj,uint8_t mesaj_uzunluk);

uint8_t mesaj_dogrulama(void);
void parse_CAN_message(void);

#endif /* CAN_H_ */
