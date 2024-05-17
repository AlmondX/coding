/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   CAN通讯实验
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F429 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./led/bsp_led.h"
#include "./usart/bsp_debug_usart.h"
#include "./can/bsp_can.h"
#include "./key/bsp_key.h"
#include "can1.h"
#include "timer3.h"
#include "data.h"
#include "Master.h"
#include "canfestival.h"
#include "variable.h"
#include "bsp_drive_can.h"
#include "bsp_SysTick.h"
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	SysTick_Init();
	LED_GPIO_Config();
  Debug_USART_Config();          /*初始化USART1*/
	Key_GPIO_Config();             /*初始化按键*/
	CAN1_Init(&Master_Data,20000);
	TIM3_Init();
	CANopen_Init();
  while(1)
	{
      Master_NMT_Manage();
	}
}


/*********************************************END OF FILE**********************/

