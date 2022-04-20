#include "esp8266.hpp"
#include "string.h"

extern DMA_HandleTypeDef hdma_usart6_rx;

CPP_UART test_uart = CPP_UART(&huart3);
ESP8266 wifi = ESP8266(&huart6, &hdma_usart6_rx, &htim6);

/**
 * @brief  ESP8266 类 构造函数
 * @param  huart  : 连接ESP8266所用到的串口
 * @param  dma_rx : 串口接收对应的DMA
 * @param  htim   : 用于计数是否超时的定时器
 * @note  huart 对应的串口配置要求正确，波特率用默认的115200(也可自己更改，
 * @            但要注意ESP8266本身接收串口的速率)，并且需要打开中断
 * @     dma_rx 串口设置dma的接收，一次一个字节，循环模式(circle)
 * @       htim 不用开启定时器中断，不用关心预分频系数和自动重装载值和OnePulse模式
 * @retval None
 **/
ESP8266::ESP8266(UART_HandleTypeDef* huart, DMA_HandleTypeDef *dma_rx, TIM_HandleTypeDef *htim)
	:uart(huart)
{
	this->dma_rx     = dma_rx;
	this->tim        = htim;
	this->uart_state = Idle;
	this->mode       = NOINIT;
}

/**
 * @brief  ESP8266 初始化函数
 * @retval None
 **/
void ESP8266::RxCallback(){
	UART_HandleTypeDef*  huart = uart.huart; //ESP8266用到的串口

	/* 判断是否发生空闲中断 */
	if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) != RESET) {
		__HAL_UART_CLEAR_IDLEFLAG(huart); //清除IDLE中断标志位
		HAL_UART_DMAStop(huart);          // 停止DMA接收

		//以下步骤是将接收到的内容存入 AckBuffer 中
		int recv_end    = RxBufferSize - __HAL_DMA_GET_COUNTER(dma_rx); // 得到接收到的字符长度
		int recv_start  = recv_end % RxBufferSize;                      // 接收到的内容地起始索引
		while(RxBuffer[recv_start] == 0) { //找出接收的起始
			recv_start = (recv_start + 1) % RxBufferSize;
		}
		int index = recv_start;
		int i;
		for(i=0; index != recv_end; i++)
		{
			AckBuffer[i] = RxBuffer[index];
			RxBuffer[index] = 0;
			index = (index+1)%RxBufferSize;
		}
		AckBuffer[i] = 0; //用作字符串分隔符

		//调试用，将接收到的响应通过串口输出
		test_uart << "\r\n接收:\r\n";
		test_uart << AckBuffer;
		//使用队列来接收
		//if(uart_state == Sent) {//如果串口发送完毕，等待接收
		//uart_state = Idle; //变为空闲模式
		//}
		//if(uart_state == Idle) { //（一般是被动地接收到信息）
		//for(;;); //TODO:
		//}

		/* 准备下一次DMA接收 */
		__HAL_DMA_SET_COUNTER(dma_rx, 0);
		HAL_UART_Receive_DMA(huart, (uint8_t*)RxBuffer, RxBufferSize);
	}
}

/**
 * @brief  ESP8266 设置发送指令或内容后，最大的等待超时时间
 * @note ms不能超过43,690
 * @retval None
 **/
void ESP8266::setTimeout(uint16_t ms){
	__HAL_TIM_SET_AUTORELOAD(tim, ms*3/2);  //要设置延迟10ms的中断，则需要设置 ARR 为 10*3/2;
	__HAL_TIM_SET_COUNTER(tim, 1);          //因为要根据CNT是否为0来判断是否超时，所以这里设置为1
	__HAL_TIM_ENABLE(tim);                  //开启定时器，定时器在溢出后自动归0，并停止运作
}

/**
 * @brief  ESP8266 判断是否超时
 * @note   必须在setTimeout之后才能使用
 * @retval None
 **/
bool ESP8266::isTimeout(void){
	if(__HAL_TIM_GET_COUNTER(tim) == 0){
		return true;
	}
	else {
		return false;
	}
}

/*
 *
 * */
void ESP8266::sendNoAck(uint8_t *str) {
	uart << str;
	//TODO: 调试用
	if(!(str[0] == '\r' && str[1] == '\n')) {
		test_uart << "\r\n发送:\r\n";
		test_uart << str;
	}
	/////////////////
}

result ESP8266::send(char *str,const char* response,uint16_t timeout){
	/* 发送内容 */
	sendNoAck((uint8_t*)str);

	/* 等待响应 */
	uart_state = Sent;
	setTimeout(timeout); //设置超时时间
	while(!isTimeout() && !isResponded(response));
	uart_state = Idle;

	/* 判断执行的结果 */
	if(isTimeout()) {
		return Timeout; //发送失败或者超时
	}
	else {
		return Success; //内容成功发送
	}
}

result ESP8266::sendCmd(const char *str,const char* response,uint16_t timeout){
	/* 发送内容 */
	sendNoAck((uint8_t*)str);
	sendNoAck((uint8_t*)"\r\n");

	/* 等待响应 */
	uart_state = Sent;
	setTimeout(timeout); //设置超时时间
	while(!isTimeout() && !isResponded(response));
	uart_state = Idle;

	/* 判断执行的结果 */
	if(isResponded(response)) {
		return Success;
	}
	else {
		return Timeout; //发送失败或者超时
	}
}

/**
 * @brief  退出透传模式
 * @retval None
 **/
void ESP8266::quitTrans(void) {
	/* 发送 "+++" 退出透传状态 */
	sendNoAck((uint8_t*)"+"); delay(15);//大于串口组帧时间(10ms)
	sendNoAck((uint8_t*)"+"); delay(15);
	sendNoAck((uint8_t*)"+"); delay(500);
	/* 关闭透传模式 */
	sendCmd("AT+CIPMODE=0", "OK", 200);
}

/**
 * @brief  延迟函数
 * @note   通过定时器实现的延迟，只是使用在quitTrans函数
 * @retval None
 **/
void ESP8266::delay(uint16_t ms) {
	setTimeout(ms);
	while(!isTimeout());
}

/**
 * @brief  判断是否从ESP8266得到期望的响应（母串找子串）
 * @retval 是否得到期望的响应
 **/
bool ESP8266::isResponded(const char* response){
	int responseLen = strlen(response);
	int rxBufferLen = strlen(RxBuffer);
	for(int i=0,j=0; i<rxBufferLen; i++) {
		if(RxBuffer[i] == response[j])	{
			if(++j == responseLen) { //找到字串 （即找到响应）
				return true;
			}
		}
		else {
			j = 0;
		}
	}
	return false; //未找到子串
}

/**
 * @brief  ESP8266 初始化函数
 * @retval 初始化是否成功
 **/
result ESP8266::init(){
	UART_HandleTypeDef*  huart = uart.huart; //ESP8266用到的串口
	/* 开启DMA接收 */
	HAL_UART_Receive_DMA(huart, (uint8_t*)RxBuffer, RxBufferSize);
	__HAL_UART_ENABLE_IT(huart, UART_IT_IDLE); //开启空闲中断

	/* 配置用于记录是否超时的定时器 */
	HAL_TIM_Base_Start(tim);
	HAL_TIM_OnePulse_Init(tim, TIM_OPMODE_SINGLE);                 //设置为 OnePulse 模式
	__HAL_TIM_SET_PRESCALER(tim, HAL_RCC_GetHCLKFreq()/3/1000-1);  //设置分频数为 56,000

	delay(100);
	
	
	
	char buf[128];
	quitTrans(); //退出透传
	
//*---- 以下内容只需要执行一次 -----*/
//	sendCmd("AT+RESTORE"  , "OK" , 4000); //恢复出厂设置
//	delay(5000);
//	sendCmd("AT+CWMODE=1" , "OK" , 4000); //设置成STA模式
//	sendCmd("AT+RST"      , "OK" , 1000); //重启生效
//	delay(5000);
//	sendCmd("AT+CIPSTAMAC=\"18:fe:36:98:d3:1b\"", "OK", 100); //设置 MAC 地址
	wifi.sendCmd("ATE0"        , "OK" , 100);  //关闭回显
	
	
	/* 加入wifi */
	sprintf(buf,"AT+CWJAP=\"%s\",\"%s\"","dxxy16-402-1","dxxy16402");
	sendCmd(buf, "WIFI GOT IP", 15000); //加入AP
	send((char*)"", "OK"         , 2000); //加入AP
	
	
	/* 进入透传模式 */
	sendCmd("AT+CIPMODE=1", "OK", 200); //开启透传模式

	/* 与PC机建立连接 */
	sprintf(buf,"AT+CIPSTART=\"%s\",\"%s\",%s", "TCP", "192.168.0.189", "9981");
	sendCmd(buf, "OK", 15000);

	sendCmd("AT+CIPSEND"  , ">", 100); //进入透传
	
	
//	for(;;) {
//		sendNoAck((uint8_t*)"hello world \r\n");
//		delay(1000);
//	}
	
	return Success;
}

