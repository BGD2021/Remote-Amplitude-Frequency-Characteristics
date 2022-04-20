#ifndef __UART_HPP
#define __UART_HPP
#include "usart.h"
#include "stdio.h"

#define bufferSize 2048

class CPP_UART{
private:
	char buffer[bufferSize];								/*缓存*/
public:
	UART_HandleTypeDef* huart;
	/*构造函数*/
	CPP_UART(UART_HandleTypeDef* huart){
		this->huart = huart;
	};

	/* 定义运算符 --- const char * */
	void operator <<(const char *str)	{
		int strSize = sprintf(buffer, "%s", str);
		HAL_UART_Transmit(huart, (uint8_t*)buffer, strSize, 0xffffffff);
	}

	/* 定义运算符 --- char * */
	void operator <<(char *str)	{
		int strSize = sprintf(buffer, "%s", str);
		HAL_UART_Transmit(huart, (uint8_t*)buffer, strSize, 0xffffffff);
	}

	void operator <<(uint8_t *str){
		int strSize = sprintf(buffer, "%s", (char*)str);
		HAL_UART_Transmit(huart, (uint8_t*)buffer, strSize, 0xffffffff);
	}

	/* 定义运算符 --- int */
	void operator <<(int num)	{
		int strSize = sprintf(buffer, "%d", num);
		HAL_UART_Transmit(huart, (uint8_t*)buffer, strSize, 0xffffffff);
	}


};

#endif
