#include "main.h"
#include "gpio.h"
#include "main.h"
#include "system_clock.h"
#include "tim.h"
#include "usart.h"

int main()
{
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_TIM1_Init();
    MX_TIM2_Init();

    while (true) {
    }

    return 0;
}
