#include "main.h"
#include "gpio.h"
#include "gpio.hpp"
#include "hc_sr04.hpp"
#include "main.h"
#include "system_clock.h"
#include "tim.h"
#include "usart.h"
#include "utility.hpp"
#include <cstdio>

int main()
{
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_TIM1_Init();
    MX_TIM2_Init();

    using namespace Utility;

    auto hc_sr04 = HC_SR04::HC_SR04{
        .tof_timer = &htim2,
        .trig_pin = GPIO::PC0,
        .echo_pin = GPIO::PC1,
        .count_to_time_ms = [](std::uint32_t const count) {
            return Utility::count_to_time_ms(count, htim2.Init.Prescaler, 80000000UL, htim2.Init.ClockDivision);
        }};

    while (true) {
        auto const bits = get_event_bits(ECHO_TRIG);

        if ((bits & SAMPLING_TIMER) == SAMPLING_TIMER) {
            hc_sr04.transmit_trig_signal();
        }

        if ((bits & ECHO_TRIG) == ECHO_TRIG) {
            hc_sr04.receive_echo_signal();
        }

        auto distance = hc_sr04.get_distance_mm();
        printf("Distance mm: %ld\n\r", distance);
    }

    return 0;
}
