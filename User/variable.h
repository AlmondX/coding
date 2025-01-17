#ifndef __VARIABLE_H_
#define __VARIABLE_H_
#include "stm32f4xx.h"

#include "Master.h"
#define device_type_passageway 

//节点ID
#define master_nodeID              0x00  
#define slaver_passageway_nodeId   0x01 
#define slaver_1_nodeId            0x02 
#define slaver_2_nodeId            0x03 

//检查从机状态
#define detect_slaverstatus_N   3  //需要检查的节点数量
#define detect_slaverstatus_time     3000 //时间检测间隔ms

//读取从站参数
#define read_passageway_parameter_index       0x2004
#define read_passageway_parameter_subindex_1  0x01
#define read_passageway_parameter_subindex_2  0x02
#define readrespond_passgewag_parameter_id    0x581
#define read_reply_1byte_cs        0x4F
#define read_reply_2byte_cs        0x4B
#define read_reply_3ebyte_cs       0x47
#define read_reply_4byte_cs        0x43
#define read_cs                    0x40

//写入从站参数
#define write_passageway_parameter_index       0x2004
#define write_passageway_parameter_subindex_1  0x01
#define write_passageway_parameter_subindex_2  0x02
#define write_1byte_cs        0x2F
#define write_2byte_cs        0x2B
#define write_3ebyte_cs       0x27
#define write_4byte_cs        0x23
#define write_reply_success   0x60

#define except_response       0x80

#define tx_num 100
union Mainc_Rx_Slaver_Data 
{
	UNS8 chardata[tx_num];
	struct
	{
			UNS16 passageway_detector_cps_left_1_low;		/* Mapped at index 0x2000, subindex 0x01 */
			UNS16 passageway_detector_cps_left_1_high;		/* Mapped at index 0x2000, subindex 0x02 */
			UNS16 passageway_detector_cps_right_1_low;	/* Mapped at index 0x2000, subindex 0x03 */
			UNS16 passageway_detector_cps_right_1_high;		/* Mapped at index 0x2000, subindex 0x04 */
			UNS16 passageway_detector_cps_left_2_low;		/* Mapped at index 0x2000, subindex 0x05 */
			UNS16 passageway_detector_cps_left_2_high;		/* Mapped at index 0x2000, subindex 0x06 */
			UNS16 passageway_detector_cps_right_2_low;		/* Mapped at index 0x2000, subindex 0x07 */
			UNS16 passageway_detector_cps_right_2_high;		/* Mapped at index 0x2000, subindex 0x08 */
			UNS16 passageway_detector_cps_left_3_low;		/* Mapped at index 0x2000, subindex 0x09 */
			UNS16 passageway_detector_cps_left_3_high;		/* Mapped at index 0x2000, subindex 0x0A */
			UNS16 passageway_detector_cps_right_3_low;		/* Mapped at index 0x2000, subindex 0x0B */
			UNS16 passageway_detector_cps_right_3_high;		/* Mapped at index 0x2000, subindex 0x0C */
			UNS16 passageway_detector_cps_left_4_low;		/* Mapped at index 0x2000, subindex 0x0D */
			UNS16 passageway_detector_cps_left_4_high;		/* Mapped at index 0x2000, subindex 0x0E */
			UNS16 passageway_detector_cps_right_4_low;		/* Mapped at index 0x2000, subindex 0x0F */
			UNS16 passageway_detector_cps_right_4_high;		/* Mapped at index 0x2000, subindex 0x10 */
			UNS8 passageway_alarm_data_channel_left;		/* Mapped at index 0x2001, subindex 0x01 */
			UNS8 passageway_alarm_data_channel_right;		/* Mapped at index 0x2001, subindex 0x02 */
			UNS16 passageway_alarm_data_monitor_speed;		/* Mapped at index 0x2001, subindex 0x03 */
			UNS8 passageway_fault_data_channel_left;		/* Mapped at index 0x2002, subindex 0x01 */
			UNS8 passageway_fault_data_channel_right;		/* Mapped at index 0x2002, subindex 0x02 */
			UNS8 passageway_status_data_work;		/* Mapped at index 0x2003, subindex 0x01 */
			UNS8 passageway_status_data_monitor;		/* Mapped at index 0x2003, subindex 0x02 */
			UNS8 passageway_status_data_preheat_left;		/* Mapped at index 0x2003, subindex 0x03 */
			UNS8 passageway_status_data_preheat_right;		/* Mapped at index 0x2003, subindex 0x04 */
			UNS16 passageway_parameter_type_modbus_id;		/* Mapped at index 0x2004, subindex 0x01 */
			UNS32 passageway_parameter_factory_year_serial_number;		/* Mapped at index 0x2004, subindex 0x02 */
			
			UNS8 test_1_test_1_1;		/* Mapped at index 0x2005, subindex 0x01 */
			UNS8 test_1_test_1_2;		/* Mapped at index 0x2005, subindex 0x02 */
			UNS8 test_1_test_1_3;		/* Mapped at index 0x2005, subindex 0x03 */
			UNS8 test_1_test_1_4;		/* Mapped at index 0x2005, subindex 0x04 */
			UNS8 test_2_test_2_1;		/* Mapped at index 0x2006, subindex 0x01 */
			UNS8 test_2_test_2_2;		/* Mapped at index 0x2006, subindex 0x02 */
			UNS8 test_2_test_2_3;		/* Mapped at index 0x2006, subindex 0x03 */
			UNS8 test_2_test_2_4;		/* Mapped at index 0x2006, subindex 0x04 */
			UNS8 test_3_test_3_1;		/* Mapped at index 0x2007, subindex 0x01 */
			UNS8 test_3_test_3_2;		/* Mapped at index 0x2007, subindex 0x02 */
			UNS8 test_3_test_3_3;		/* Mapped at index 0x2007, subindex 0x03 */
			UNS8 test_3_test_3_4;		/* Mapped at index 0x2007, subindex 0x04 */
			UNS8 test_4_test_4_1;		/* Mapped at index 0x2008, subindex 0x01 */
			UNS8 test_4_test_4_2;		/* Mapped at index 0x2008, subindex 0x02 */
			UNS8 test_4_test_4_3;		/* Mapped at index 0x2008, subindex 0x03 */
			UNS8 test_4_test_4_4;		/* Mapped at index 0x2008, subindex 0x04 */
	 }Data;
};

struct Systick_time
{
	 uint8_t  T_bool_10ms;
	 uint8_t  T_bool_60ms;
	 uint8_t  T_bool_1s;
	 uint8_t  T_bool_readdata_over;
	
	 uint8_t  Time_60ms;
	 uint8_t  Time_1s;
	 uint16_t Time_readdata_over;

	 uint8_t  time_send_readdata_flag;
};

extern union Mainc_Rx_Slaver_Data  mainc_rx_slaver_data;
extern struct Systick_time   systick_time;
#endif
