#ifndef __ESP8266_HPP
#define __ESP8266_HPP

#include "cpp_uart.hpp"
#include "tim.h"
#define RxBufferSize 2048  //接收缓存大小

/* ESP8266命名空间 */
namespace ESP8266_Space
{
	/* ESP8266当前工作模式 */
	enum mode_set {
		NOINIT,      //未初始化
		STA,         //从机模式
		AP,          //主机模式
		APSTA,       //从机+主机模式
		DISCONNECT   //断开连接
	};
	/* 串口执行的状态 */
	enum uart_state_set {
		Idle,         //空闲
		Busy,         //忙
		Sent,         //发送完毕,等待接收
	};
	/* 动作执行的结果 */
	enum result {
		Fail,        //失败
		Success,     //成功
		Timeout      //超时
	};
}
/* 使用命名空间 */
using namespace ESP8266_Space;


class ESP8266{
public:
	CPP_UART uart;                 //ESP8266所用的串口
	DMA_HandleTypeDef *dma_rx;     //用于串口接收的DMA
	TIM_HandleTypeDef *tim;        //用于记录是否超时的定时器
	mode_set mode;                 //ESP8266的工作模式
	uart_state_set uart_state;     //记录用于通信的串口的状态
	char RxBuffer[RxBufferSize];   //接收缓存
	char AckBuffer[RxBufferSize];  //存放响应内容的缓存
	//char TxBuffer[TxBufferSize]; //接收缓存

	/* 构造函数 */
	ESP8266(UART_HandleTypeDef* huart, DMA_HandleTypeDef *dma_rx, TIM_HandleTypeDef *htim);
	/* 发送内容 */
	result send(char *str, const char* response, uint16_t timeout);
	/* 发送内容(无要求响应) */
	void sendNoAck(uint8_t *str);
	/* 发送指令 */
	result sendCmd(const char *str, const char* response, uint16_t timeout);
	/* 退出透传模式 */
	void quitTrans(void);
	/* 接收回调函数（需自己添加） */
	void RxCallback();
	/* 设置超时时间 */
	void setTimeout(uint16_t ms);
	/* 判断是否超时 */
	bool isTimeout(void);
	/* 延迟函数 */
	void delay(uint16_t ms);
	/* 判断是否被响应 */
	bool isResponded(const char* response);
	/* 初始化 */
	result init();
};


extern ESP8266 wifi;

#endif
