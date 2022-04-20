#include "usart.h"
#include "esp8266.hpp"


extern "C" void USART6_IRQHandler(void)
{
	wifi.RxCallback();
}
