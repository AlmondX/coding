#ifndef __BSP_DRIVE_CAN_H_
#define __BSP_DRIVE_CAN_H_

#include "stm32f4xx.h"

void Read_Slaver_Parameter(uint16_t index,uint8_t sub_index);
void Transform_Data(void);
void NMT_Manage_Disconnect(uint8_t nodeid,uint16_t time);
void CANopen_Init(void);
void Master_NMT_Manage(void);
#endif
