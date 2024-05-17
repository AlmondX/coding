#ifndef __LED_H
#define	__LED_H

#include "stm32f4xx.h"

//引脚定义
/*******************************************************/
//R 红色灯
#define LED1_PIN                  GPIO_Pin_10                 
#define LED1_GPIO_PORT            GPIOH                      
#define LED1_GPIO_CLK             RCC_AHB1Periph_GPIOH

//G 绿色灯
#define LED2_PIN                  GPIO_Pin_11                 
#define LED2_GPIO_PORT            GPIOH                      
#define LED2_GPIO_CLK             RCC_AHB1Periph_GPIOH

//B 蓝色灯
#define LED3_PIN                  GPIO_Pin_12                 
#define LED3_GPIO_PORT            GPIOH                       
#define LED3_GPIO_CLK             RCC_AHB1Periph_GPIOH

//小指示灯
#define LED4_PIN                  GPIO_Pin_11                 
#define LED4_GPIO_PORT            GPIOD                       
#define LED4_GPIO_CLK             RCC_AHB1Periph_GPIOD

//读参数IO
#define READ_PARA_PIN                  GPIO_Pin_5     
#define READ_PARA_GPIO_PORT            GPIOC                                 
#define READ_PARA_GPIO_CLK             RCC_AHB1Periph_GPIOC

/************************************************************/


/** 控制LED灯亮灭的宏，
	* LED低电平亮，设置ON=0，OFF=1
	* 若LED高电平亮，把宏设置成ON=1 ，OFF=0 即可
	*/
#define ON  0
#define OFF 1

/* 带参宏，可以像内联函数一样使用 */
#define LED1(a)	if (a)	\
					GPIO_SetBits(LED1_GPIO_PORT,LED1_PIN);\
					else		\
					GPIO_ResetBits(LED1_GPIO_PORT,LED1_PIN)

#define LED2(a)	if (a)	\
					GPIO_SetBits(LED2_GPIO_PORT,LED2_PIN);\
					else		\
					GPIO_ResetBits(LED2_GPIO_PORT,LED2_PIN)

#define LED3(a)	if (a)	\
					GPIO_SetBits(LED3_GPIO_PORT,LED3_PIN);\
					else		\
					GPIO_ResetBits(LED3_GPIO_PORT,LED3_PIN)
					
#define LED4(a)	if (a)	\
					GPIO_SetBits(LED4_GPIO_PORT,LED4_PIN);\
					else		\
					GPIO_ResetBits(LED4_GPIO_PORT,LED4_PIN)


/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)			{p->BSRRL=i;}			  //设置为高电平		
#define digitalLo(p,i)			{p->BSRRH=i;}				//输出低电平
#define digitalToggle(p,i)		{p->ODR ^=i;}			//输出反转状态


/* 定义控制IO的宏 */
#define LED1_TOGGLE		GPIO_ToggleBits(LED1_GPIO_PORT,LED1_PIN)
#define LED1_OFF		 GPIO_SetBits(LED1_GPIO_PORT,LED1_PIN)
#define LED1_ON			 GPIO_ResetBits(LED1_GPIO_PORT,LED1_PIN)

#define LED2_TOGGLE		GPIO_ToggleBits(LED2_GPIO_PORT,LED2_PIN)
#define LED2_OFF		GPIO_SetBits(LED2_GPIO_PORT,LED2_PIN)
#define LED2_ON			GPIO_ResetBits(LED2_GPIO_PORT,LED2_PIN)

#define LED3_TOGGLE		GPIO_ToggleBits(LED3_GPIO_PORT,LED3_PIN)
#define LED3_OFF		GPIO_SetBits(LED3_GPIO_PORT,LED3_PIN)
#define LED3_ON			GPIO_ResetBits(LED3_GPIO_PORT,LED3_PIN)

#define LED4_TOGGLE		GPIO_ToggleBits(LED4_GPIO_PORT,LED4_PIN)
#define LED4_OFF		GPIO_SetBits(LED4_GPIO_PORT,LED4_PIN)
#define LED4_ON			GPIO_ResetBits(LED4_GPIO_PORT,LED4_PIN)

#define READ_PARA_TOGGLE		GPIO_ToggleBits(READ_PARA_GPIO_PORT,READ_PARA_PIN)
#define READ_PARA_OFF		    GPIO_ResetBits(READ_PARA_GPIO_PORT,READ_PARA_PIN)
#define READ_PARA_ON			  GPIO_SetBits(READ_PARA_GPIO_PORT,READ_PARA_PIN)

/* 基本混色，后面高级用法使用PWM可混出全彩颜色,且效果更好 */

//红
#define LED_RED  \
					LED1_ON;\
					LED2_OFF\
					LED3_OFF

//绿
#define LED_GREEN		\
					LED1_OFF;\
					LED2_ON\
					LED3_OFF

//蓝
#define LED_BLUE	\
					LED1_OFF;\
					LED2_OFF\
					LED3_ON

					
//黄(红+绿)					
#define LED_YELLOW	\
					LED1_ON;\
					LED2_ON\
					LED3_OFF
//紫(红+蓝)
#define LED_PURPLE	\
					LED1_ON;\
					LED2_OFF\
					LED3_ON

//青(绿+蓝)
#define LED_CYAN \
					LED1_OFF;\
					LED2_ON\
					LED3_ON
					
//白(红+绿+蓝)
#define LED_WHITE	\
					LED1_ON;\
					LED2_ON\
					LED3_ON
					

//黑(全部关闭)					
#define LED_RGBOFF	\
					LED1_OFF;\
					LED2_OFF\
					LED3_OFF



void LED_GPIO_Config(void);

#endif /* __LED_H */
