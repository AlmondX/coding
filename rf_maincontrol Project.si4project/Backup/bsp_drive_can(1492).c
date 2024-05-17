#include "bsp_drive_can.h"
#include "variable.h"
#include "./key/bsp_key.h"

unsigned char get_passageway_parameter[8]={0};
#define read_passageway_parameter_index  0x2004


#define master_nodeID              0x00  
#define slaver_passageway_nodeId   0x01 
#define slaver_test_nodeId         0x03 

#define detect_disconnect_time     3000 //时间检测间隔

#define detect_disconnect_node_N   3  //需要检查的节点数量
uint8_t detect_node_count = detect_disconnect_node_N;

void Read_Passageway_Parameter(uint8_t sub_index)
{
			 get_passageway_parameter[0] =0x40; //cs命令符号——读取数据
			 get_passageway_parameter[1] =read_passageway_parameter_index&0xFF; 
			 get_passageway_parameter[2] =read_passageway_parameter_index>>8; 
			 get_passageway_parameter[3] =sub_index;   //子索引 
	     get_passageway_parameter[4] =0;   
			 get_passageway_parameter[5] =0;   
			 get_passageway_parameter[6] =0;    
			 get_passageway_parameter[7] =0;   
   
			 sendSDO(&Master_Data,SDO_CLIENT,0,get_passageway_parameter);
}

void Transform_Data(void)
{
	 #ifdef debug_passageway_on 
	  			passageway_tx_internal_data.detector_cps_left_1_low   = detector_cps_left_1_low;
					passageway_tx_internal_data.detector_cps_left_1_high  = detector_cps_left_1_high;
					passageway_tx_internal_data.detector_cps_right_1_low  = detector_cps_right_1_low;
					passageway_tx_internal_data.detector_cps_right_1_high = detector_cps_right_1_high;
					passageway_tx_internal_data.detector_cps_left_2_low   = detector_cps_left_2_low;
					passageway_tx_internal_data.detector_cps_left_2_high  = detector_cps_left_2_high;
					passageway_tx_internal_data.detector_cps_right_2_low  = detector_cps_right_2_low;
					passageway_tx_internal_data.detector_cps_right_2_high = detector_cps_right_2_high;
					passageway_tx_internal_data.detector_cps_left_3_low   = detector_cps_left_3_low;
					passageway_tx_internal_data.detector_cps_left_3_high  = detector_cps_left_3_high;
					passageway_tx_internal_data.detector_cps_right_3_low  = detector_cps_right_3_low;
					passageway_tx_internal_data.detector_cps_right_3_high = detector_cps_right_3_high;
					passageway_tx_internal_data.detector_cps_left_4_low   = detector_cps_left_4_low;
					passageway_tx_internal_data.detector_cps_left_4_high  = detector_cps_left_4_high;
					passageway_tx_internal_data.detector_cps_right_4_low  = detector_cps_right_4_low;
					passageway_tx_internal_data.detector_cps_right_4_high = detector_cps_right_4_high;
	
	      	passageway_tx_internal_data.alarm_data_channel_left  = alarm_data_channel_left;
					passageway_tx_internal_data.alarm_data_channel_right = alarm_data_channel_right;
					passageway_tx_internal_data.alarm_data_monitor_speed =  alarm_data_monitor_speed;
	
	        passageway_tx_internal_data.fault_data_channel_left  = fault_data_channel_left;
				  passageway_tx_internal_data.fault_data_channel_right = fault_data_channel_right;
					
					passageway_tx_internal_data.status_data_work = status_data_work;
					passageway_tx_internal_data.status_data_monitor = status_data_monitor;
					passageway_tx_internal_data.status_data_preheat_left = status_data_preheat_left;
					passageway_tx_internal_data.status_data_preheat_right = status_data_preheat_right;
	 #endif
}

void NMT_Manage_Disconnect(uint8_t nodeid,uint16_t time)
{
	  if(nodeid>0)
		{
				Master_Data.ConsumerHeartbeatEntries[nodeid-1] = time;
	      Master_Data.ConsumerHeartbeatEntries[nodeid-1] |= nodeid<<16;
		}
}
void CANopen_Init(void)
{
			setNodeId(&Master_Data, master_nodeID);
			setState(&Master_Data, Initialisation);				//节点初始化
			setState(&Master_Data, Operational);	

			Master_Data.ConsumerHeartbeatCount = &detect_node_count;
			NMT_Manage_Disconnect(slaver_passageway_nodeId,detect_disconnect_time);
			NMT_Manage_Disconnect(2,detect_disconnect_time);
			NMT_Manage_Disconnect(slaver_test_nodeId,detect_disconnect_time);
			
			masterSendNMTstateChange(&Master_Data,slaver_test_nodeId,NMT_Start_Node);	
			masterSendNMTstateChange(&Master_Data,slaver_passageway_nodeId,NMT_Start_Node);
}
void Master_NMT_Manage(void)
{
	 		if(Key_Scan(KEY1_GPIO_PORT,KEY1_PIN)==1)    //读取参数命令
		{
        Read_Passageway_Parameter(0x01);
			  Read_Passageway_Parameter(0x02);
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
//		else
//		{
//			Transform_Data();
//		}
}
