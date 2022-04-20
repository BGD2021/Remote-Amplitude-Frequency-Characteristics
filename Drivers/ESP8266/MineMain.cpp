#include "esp8266.hpp"
#include "main.h"
using namespace ESP8266_Space;

uint8_t res;
extern char chartdata[200];
extern "C" void MineMain(void)
{
	char buf[128];

	wifi.init();
	wifi.sendNoAck((uint8_t *)"³õÊ¼»¯Íê±Ï");
	HAL_UART_Receive_IT(&huart2, &res, 1);
	for(;;) {
//		printf("uart3\r\n");
		wifi.sendNoAck((uint8_t *)chartdata);
//		wifi.sendNoAck((uint8_t*)"[1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0]");
//		wifi.sendNoAck((uint8_t*)"hello world\r\n");
		HAL_Delay(1000);
	}

}
