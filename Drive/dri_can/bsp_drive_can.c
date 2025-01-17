#include "bsp_drive_can.h"
#include "variable.h"
#include "./key/bsp_key.h"
#include "./led/bsp_led.h"   

unsigned char read_slaver_parameter[8]={0};
unsigned char write_slaver_parameter[8]={0};
uint8_t write_para_data_1[4]={0x00,0x00,0xB3,0xB4};
uint8_t write_para_data_2[4]={0xB7,0xB8,0xB9,0xB1};

uint8_t detect_slaverstatus_count = detect_slaverstatus_N;
/*****************主站读取从站的参数*******************************/
void Read_Slaver_Parameter(uint16_t index,uint8_t sub_index)
{
			 read_slaver_parameter[0] =read_cs;          //cs命令符号——读取数据
			 read_slaver_parameter[1] =index&0xFF;    // 索引 
			 read_slaver_parameter[2] =index>>8; 
			 read_slaver_parameter[3] =sub_index;     //子索引 
	     read_slaver_parameter[4] =0;             //未用补0
			 read_slaver_parameter[5] =0;   
			 read_slaver_parameter[6] =0;    
			 read_slaver_parameter[7] =0;   
			 sendSDO(&Master_Data,SDO_CLIENT,0,read_slaver_parameter);
}
/*****************主站写从站的参数*******************************/
void Write_Slaver_Parameter(uint8_t cs,uint16_t index,uint8_t sub_index,uint8_t *write_data)
{
			 write_slaver_parameter[0] =cs;          //cs命令符号——写入
			 write_slaver_parameter[1] =index&0xFF;    // 索引 
			 write_slaver_parameter[2] =index>>8; 
			 write_slaver_parameter[3] =sub_index;     //子索引 
	     write_slaver_parameter[4] =write_data[3];             
			 write_slaver_parameter[5] =write_data[2];   
			 write_slaver_parameter[6] =write_data[1];    
			 write_slaver_parameter[7] =write_data[0];   
			 sendSDO(&Master_Data,SDO_CLIENT,0,write_slaver_parameter);
}

void Transform_Data(void)
{
	  			mainc_rx_slaver_data.Data.passageway_detector_cps_left_1_low   = passageway_detector_cps_left_1_low;
					mainc_rx_slaver_data.Data.passageway_detector_cps_left_1_high  = passageway_detector_cps_left_1_high;
					mainc_rx_slaver_data.Data.passageway_detector_cps_right_1_low  = passageway_detector_cps_right_1_low;
					mainc_rx_slaver_data.Data.passageway_detector_cps_right_1_high = passageway_detector_cps_right_1_high;
					mainc_rx_slaver_data.Data.passageway_detector_cps_left_2_low   = passageway_detector_cps_left_2_low;
					mainc_rx_slaver_data.Data.passageway_detector_cps_left_2_high  = passageway_detector_cps_left_2_high;
					mainc_rx_slaver_data.Data.passageway_detector_cps_right_2_low  = passageway_detector_cps_right_2_low;
					mainc_rx_slaver_data.Data.passageway_detector_cps_right_2_high = passageway_detector_cps_right_2_high;
					mainc_rx_slaver_data.Data.passageway_detector_cps_left_3_low   = passageway_detector_cps_left_3_low;
					mainc_rx_slaver_data.Data.passageway_detector_cps_left_3_high  = passageway_detector_cps_left_3_high;
					mainc_rx_slaver_data.Data.passageway_detector_cps_right_3_low  = passageway_detector_cps_right_3_low;
					mainc_rx_slaver_data.Data.passageway_detector_cps_right_3_high = passageway_detector_cps_right_3_high;
					mainc_rx_slaver_data.Data.passageway_detector_cps_left_4_low   = passageway_detector_cps_left_4_low;
					mainc_rx_slaver_data.Data.passageway_detector_cps_left_4_high  = passageway_detector_cps_left_4_high;
					mainc_rx_slaver_data.Data.passageway_detector_cps_right_4_low  = passageway_detector_cps_right_4_low;
					mainc_rx_slaver_data.Data.passageway_detector_cps_right_4_high = passageway_detector_cps_right_4_high;
	
	      	mainc_rx_slaver_data.Data.passageway_alarm_data_channel_left  = passageway_alarm_data_channel_left;
					mainc_rx_slaver_data.Data.passageway_alarm_data_channel_right = passageway_alarm_data_channel_right;
					mainc_rx_slaver_data.Data.passageway_alarm_data_monitor_speed =  passageway_alarm_data_monitor_speed;
	
	        mainc_rx_slaver_data.Data.passageway_fault_data_channel_left  = passageway_fault_data_channel_left;
				  mainc_rx_slaver_data.Data.passageway_fault_data_channel_right = passageway_fault_data_channel_right;
					
					mainc_rx_slaver_data.Data.passageway_status_data_work = passageway_status_data_work;
					mainc_rx_slaver_data.Data.passageway_status_data_monitor = passageway_status_data_monitor;
					mainc_rx_slaver_data.Data.passageway_status_data_preheat_left = passageway_status_data_preheat_left;
					mainc_rx_slaver_data.Data.passageway_status_data_preheat_right = passageway_status_data_preheat_right;
					
					mainc_rx_slaver_data.Data.passageway_parameter_type_modbus_id = passageway_parameter_type_modbus_id;
					mainc_rx_slaver_data.Data.passageway_parameter_factory_year_serial_number = passageway_parameter_factory_year_serial_number;
					
					mainc_rx_slaver_data.Data.test_1_test_1_1 = test_1_test_1_1;
					mainc_rx_slaver_data.Data.test_1_test_1_2 = test_1_test_1_1;
					
					mainc_rx_slaver_data.Data.test_2_test_2_1=test_2_test_2_1;
					mainc_rx_slaver_data.Data.test_2_test_2_2=test_2_test_2_2;
					
					mainc_rx_slaver_data.Data.test_3_test_3_1=test_3_test_3_1;
					mainc_rx_slaver_data.Data.test_3_test_3_2=test_3_test_3_2;
					
					mainc_rx_slaver_data.Data.test_4_test_4_1=test_4_test_4_1;
					mainc_rx_slaver_data.Data.test_4_test_4_2=test_4_test_4_2;
}
/*****************主站检查从站节点状态*******************************/
void NMT_Detect_Slaver_Status(uint8_t nodeid,uint16_t time)
{
	  if(nodeid>0)
		{
			    Master_Data.ConsumerHeartbeatEntries[nodeid-1] = time;          //心跳消费时间       [0-16]检测时间间隔ms
	        Master_Data.ConsumerHeartbeatEntries[nodeid-1] |= nodeid<<16;   //[17-20]需要检测的节点ID
		}
}
void CANopen_Init(void)
{
			setNodeId(&Master_Data, master_nodeID);
			setState(&Master_Data, Initialisation);				//节点初始化
			setState(&Master_Data, Operational);	

			Master_Data.ConsumerHeartbeatCount = &detect_slaverstatus_count;  	           //需要检查的节点数量
			NMT_Detect_Slaver_Status(slaver_passageway_nodeId,detect_slaverstatus_time);   //检查间隔时间
			NMT_Detect_Slaver_Status(slaver_1_nodeId,5000);
			NMT_Detect_Slaver_Status(slaver_2_nodeId,detect_slaverstatus_time);
			

			masterSendNMTstateChange(&Master_Data,slaver_1_nodeId,NMT_Start_Node);					
			masterSendNMTstateChange(&Master_Data,slaver_2_nodeId,NMT_Start_Node);	
			masterSendNMTstateChange(&Master_Data,slaver_passageway_nodeId,NMT_Start_Node);
}
void Master_NMT_Manage(void)
{
	    static uint8_t key_num = 0;
	 		if(Key_Scan(KEY1_GPIO_PORT,KEY1_PIN)==1)    //读取参数命令
		{
			     key_num++;
			     if(key_num>4) key_num=0;
		}
	  switch(key_num)
		{		
				case 1:
				Read_Slaver_Parameter(read_passageway_parameter_index,read_passageway_parameter_subindex_1);
				Read_Slaver_Parameter(read_passageway_parameter_index,read_passageway_parameter_subindex_2);
				key_num ++;
				break;
				
				case 3:
				Write_Slaver_Parameter(write_2byte_cs,read_passageway_parameter_index,read_passageway_parameter_subindex_1,write_para_data_1);
				Write_Slaver_Parameter(write_4byte_cs,read_passageway_parameter_index,read_passageway_parameter_subindex_2,write_para_data_2);
				key_num ++;
				break;

				default:
				break;
		 }
		
		if(Key_Scan(KEY2_GPIO_PORT,KEY2_PIN)==1)  
		{
			if(Master_Data.NMTable[slaver_passageway_nodeId] == Operational)  //写关闭命令
			{
				masterSendNMTstateChange(&Master_Data,slaver_passageway_nodeId,NMT_Stop_Node);
			}
			if(Master_Data.NMTable[slaver_passageway_nodeId] == Stopped)      //写开启命令
			{
				masterSendNMTstateChange(&Master_Data,slaver_passageway_nodeId,NMT_Start_Node);
			}
		}
		
		if(systick_time.T_bool_1s ==1)
		{
			systick_time.T_bool_1s =0;
			Transform_Data();
			if((Master_Data.NMTable[slaver_passageway_nodeId] == Stopped)||(Master_Data.NMTable[slaver_passageway_nodeId] == Disconnected)||(Master_Data.NMTable[slaver_1_nodeId] == Disconnected))
			{
				memset(mainc_rx_slaver_data.chardata,0,100);
			}
//			LED1_TOGGLE;
		}
			if(Master_Data.NMTable[slaver_passageway_nodeId] == Disconnected)  LED1_ON; //写关闭命令
		  else  LED1_OFF;
			if(Master_Data.NMTable[slaver_1_nodeId] == Disconnected)      LED2_ON;//写开启命令
			else  LED2_OFF;
			
			
			
}
