#ifndef __LED_H
#define	__LED_H

#include "stm32f4xx.h"

//���Ŷ���
/*******************************************************/
//R ��ɫ��
#define LED1_PIN                  GPIO_Pin_10                 
#define LED1_GPIO_PORT            GPIOH                      
#define LED1_GPIO_CLK             RCC_AHB1Periph_GPIOH

//G ��ɫ��
#define LED2_PIN                  GPIO_Pin_11                 
#define LED2_GPIO_PORT            GPIOH                      
#define LED2_GPIO_CLK             RCC_AHB1Periph_GPIOH

//B ��ɫ��
#define LED3_PIN                  GPIO_Pin_12                 
#define LED3_GPIO_PORT            GPIOH                       
#define LED3_GPIO_CLK             RCC_AHB1Periph_GPIOH

//Сָʾ��
#define LED4_PIN                  GPIO_Pin_11                 
#define LED4_GPIO_PORT            GPIOD                       
#define LED4_GPIO_CLK             RCC_AHB1Periph_GPIOD

//������IO
#define READ_PARA_PIN                  GPIO_Pin_5     
#define READ_PARA_GPIO_PORT            GPIOC                                 
#define READ_PARA_GPIO_CLK             RCC_AHB1Periph_GPIOC

/************************************************************/


/** ����LED������ĺ꣬
	* LED�͵�ƽ��������ON=0��OFF=1
	* ��LED�ߵ�ƽ�����Ѻ����ó�ON=1 ��OFF=0 ����
	*/
#define ON  0
#define OFF 1

/* ���κ꣬��������������һ��ʹ�� */
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


/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)			{p->BSRRL=i;}			  //����Ϊ�ߵ�ƽ		
#define digitalLo(p,i)			{p->BSRRH=i;}				//����͵�ƽ
#define digitalToggle(p,i)		{p->ODR ^=i;}			//�����ת״̬


/* �������IO�ĺ� */
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

/* ������ɫ������߼��÷�ʹ��PWM�ɻ��ȫ����ɫ,��Ч������ */

//��
#define LED_RED  \
					LED1_ON;\
					LED2_OFF\
					LED3_OFF

//��
#define LED_GREEN		\
					LED1_OFF;\
					LED2_ON\
					LED3_OFF

//��
#define LED_BLUE	\
					LED1_OFF;\
					LED2_OFF\
					LED3_ON

					
//��(��+��)					
#define LED_YELLOW	\
					LED1_ON;\
					LED2_ON\
					LED3_OFF
//��(��+��)
#define LED_PURPLE	\
					LED1_ON;\
					LED2_OFF\
					LED3_ON

//��(��+��)
#define LED_CYAN \
					LED1_OFF;\
					LED2_ON\
					LED3_ON
					
//��(��+��+��)
#define LED_WHITE	\
					LED1_ON;\
					LED2_ON\
					LED3_ON
					

//��(ȫ���ر�)					
#define LED_RGBOFF	\
					LED1_OFF;\
					LED2_OFF\
					LED3_OFF



void LED_GPIO_Config(void);

#endif /* __LED_H */
