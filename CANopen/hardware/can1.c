// Includes for the Canfestival driver
#include "can1.h"
#include "variable.h"

static CO_Data *co_data = NULL;


//Initialize the CAN hardware 
unsigned char CAN1_Init(CO_Data * d, uint32_t bitrate)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  NVIC_InitTypeDef  NVIC_InitStructure;
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
  
  /* save the canfestival handle */  
  co_data = d;

  /* CAN GPIOs configuration **************************************************/

  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(CAN_GPIO_CLK, ENABLE);

  /* Connect CAN pins to AF7 */
  GPIO_PinAFConfig(CAN_GPIO_PORT, CAN_RX_SOURCE, GPIO_AF_CANx);
  GPIO_PinAFConfig(CAN_GPIO_PORT, CAN_TX_SOURCE, GPIO_AF_CANx); 
  
  /* Configure CAN RX and TX pins */
  GPIO_InitStructure.GPIO_Pin = CAN_RX_PIN | CAN_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(CAN_GPIO_PORT, &GPIO_InitStructure);

  /* NVIC configuration *******************************************************/
  NVIC_InitStructure.NVIC_IRQChannel = CANx_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* CAN configuration ********************************************************/  
  /* Enable CAN clock */
  RCC_APB1PeriphClockCmd(CAN_CLK, ENABLE);
  
  /* CAN register init */
  CAN_DeInit(CANx);
  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	 
  /* CAN Baudrate (CAN clocked at 42 MHz)  42e6 / ( 6 * (1+BS1+BS2))  */
  CAN_InitStructure.CAN_SJW = CAN_SJW_2tq;
  if(bitrate == 20000){
  	CAN_InitStructure.CAN_BS1 = CAN_BS1_5tq;
  	CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;
  }
  else {	//��ȥ1MƵ�ʡ�ʣ�¶�����Ϊ500K
  	CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
  	CAN_InitStructure.CAN_BS2 = CAN_BS2_7tq;
  }

  CAN_InitStructure.CAN_Prescaler = 250;
  CAN_Init(CANx, &CAN_InitStructure);

  /* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber = 0;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
  
  /* Enable FIFO 0 message pending Interrupt */
  CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);

  return 1;
}

// The driver send a CAN message passed from the CANopen stack
unsigned char canSend(CAN_PORT notused, Message *m)
{
	int i, res;
	CanTxMsg TxMessage = {0};
	TxMessage.StdId = m->cob_id;
	TxMessage.IDE = CAN_ID_STD;
	if(m->rtr)
  		TxMessage.RTR = CAN_RTR_REMOTE;
	else
  		TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = m->len;
	for(i=0 ; i<m->len ; i++)
		TxMessage.Data[i] = m->data[i]; 
    res = CAN_Transmit(CANx, &TxMessage);
	if(res == CAN_TxStatus_NoMailBox)
		return 0; 	// error
    return 1;		// succesful
}

CanTxMsg TxMessage = {0};
void CAN1_send_data(u32 send_ID,u8 len,u8 *SendData)
{	   
	uint8_t ubCounter = 0;

	//TxMessage.StdId=0x00;						 
	TxMessage.ExtId=send_ID;					 //ʹ�õ���չID
	TxMessage.IDE=CAN_ID_EXT;					 //��չģʽ
	TxMessage.RTR=CAN_RTR_DATA;				 //���͵�������
	TxMessage.DLC=len;							 //���ݳ���Ϊ8�ֽ�

	/*����Ҫ���͵�����0-7*/
	for (ubCounter = 0; ubCounter < len; ubCounter++)
	{
		TxMessage.Data[ubCounter] = *SendData;
		SendData ++;
	}
  
	ubCounter = 0;
//	CAN_Transmit(CAN1,&TxMessage);
	
	while((CAN_Transmit(CAN1,&TxMessage) == CAN_TxStatus_NoMailBox)&&(ubCounter<50))
	{
			ubCounter++;
	}	
}

//The driver pass a received CAN message to the stack
/*
unsigned char canReceive(Message *m)
{
}
*/
unsigned char canChangeBaudRate_driver( CAN_HANDLE fd, char* baud)
{
	return 0;
}

/**
  * @brief  This function handles CAN1 RX0 interrupt request.
  * @param  None
  * @retval None
  */
//void CAN1_RX0_IRQHandler(void)
//{
//	int i;
//	CanRxMsg RxMessage = {0};
//	Message rxm = {0};
//	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
//	// Drop extended frames
//	if(RxMessage.IDE == CAN_ID_EXT) //��������չ֡
//		return;
//	rxm.cob_id = RxMessage.StdId;
//  	if(RxMessage.RTR == CAN_RTR_REMOTE)//Զ��֡
//		rxm.rtr = 1;
//	rxm.len = RxMessage.DLC;
//	for(i=0 ; i<rxm.len ; i++)
//  		 rxm.data[i] = RxMessage.Data[i];
//		
//		/*****�������Լ������ݽ��ղ���*******/
//	if( rxm.cob_id>>7==0xB)	//����SDO��ӦIDΪ0x580+�Է�id, ����7λ��Ϊ0xB 
//	{
//		uint32_t test=0;
//		uint8_t receive_num = 0;
//		switch(rxm.cob_id)
//		{
//			case 0x582:
//			{
//				receive_num  = rxm.data[0];
//				switch(receive_num)                    
//				{
//					/************��ȡ���ϴ���**********************/
////					case 0x4F:test=rxm.data[4];break;                                                //��ȡһ���ֽ�
////					case 0x47:test=rxm.data[4]|rxm.data[5]<<8|rxm.data[6]<<16;break;                 //��ȡ�����ֽ�
//					  case 0x4B:passageway_parameter_type_modbus_id=rxm.data[4]|rxm.data[5]<<8;break;                                 //��ȡ�����ֽ�
//					  case 0x43:passageway_parameter_factory_year_serial_number=rxm.data[4]|rxm.data[5]<<8|rxm.data[6]<<16|rxm.data[7]<<24;break; //��ȡ�ĸ��ֽ�
//					/********д�ɹ������أ�***********************/
//					case 0x60:printf("д���ݳɹ� \r\n");break;
//					/********�쳣��Ӧ***********************/
//					case 0x80:printf("�쳣��Ӧ  \r\n");break;
//					default:break;
//				}
//				printf("test=%d,\r\n",test);	//��ʵ���жϲ�Ӧ��ʹ�ô�ӡ�����ģ������Ƿ�����Զ���
//				break;
//			}
//			default:
//				break;
//		}
//	
//	}
//	else
//		canDispatch(co_data, &rxm);//CANopen�����Ĵ�����������Ϊ����SDO����Ҫ�������������ϱߴ�����Ͳ���Ҫ�����ⲽ��
//}

void CAN1_RX0_IRQHandler(void)
{
	int i;
	CanRxMsg RxMessage = {0};
	Message rxm = {0};
	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
	// Drop extended frames
	if(RxMessage.IDE == CAN_ID_EXT) //��������չ֡
		return;
	rxm.cob_id = RxMessage.StdId;
  	if(RxMessage.RTR == CAN_RTR_REMOTE)//Զ��֡
		rxm.rtr = 1;
	rxm.len = RxMessage.DLC;
	for(i=0 ; i<rxm.len ; i++)
  		 rxm.data[i] = RxMessage.Data[i];
		
		/*****�������Լ������ݽ��ղ���*******/
	if( rxm.cob_id>>7==0xB)	//����SDO��ӦIDΪ0x580+�Է�id, ����7λ��Ϊ0xB 
	{
		uint8_t receive_num = 0;
		switch(rxm.cob_id)
		{
			case readrespond_passgewag_parameter_id:
			{
				receive_num  = rxm.data[0];
				switch(receive_num)                    
				{
					/************��ȡ���ϴ���**********************/
					  case read_reply_2byte_cs:passageway_parameter_type_modbus_id=rxm.data[4]|rxm.data[5]<<8;break;                                            //��ȡ�����ֽ�
					  case read_reply_4byte_cs:passageway_parameter_factory_year_serial_number=rxm.data[4]|rxm.data[5]<<8|rxm.data[6]<<16|rxm.data[7]<<24;break; //��ȡ�ĸ��ֽ�
					default:break;
				}
				break;
			}
			default:
				break;
		}
	
	}
	else
		canDispatch(co_data, &rxm);//CANopen�����Ĵ�����������Ϊ����SDO����Ҫ�������������ϱߴ�����Ͳ���Ҫ�����ⲽ��
}