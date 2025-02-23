#include "hc_sr04.hpp"
#include "common.hpp"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_tim.h"
#include "utility.hpp"

namespace HC_SR04 {

    void HC_SR04::transmit_trig_signal() noexcept
    {
        gpio_reset_pin(this->trig_pin);
        gpio_set_pin(this->trig_pin);
        Utility::delay_us(10UL);
        gpio_reset_pin(this->trig_pin);

        __HAL_TIM_SetCounter(this->tof_timer, 0UL);
        HAL_TIM_Base_Start(this->tof_timer);
    }

    void HC_SR04::receive_echo_signal() noexcept
    {
        if (gpio_read_pin(this->echo_pin)) {
            ++this->echo_count;
        }

        if (this->echo_count > 8U) {
            HAL_TIM_Base_Stop(this->tof_timer);
            __HAL_TIM_SetCounter(this->tof_timer, 0UL);
            this->distance_mm = Utility::time_of_flight_ms_to_distance_mm(
                this->count_to_time_ms(__HAL_TIM_GetCounter(this->tof_timer)));
            this->echo_count = 0U;
        }
    }

    std::uint32_t HC_SR04::get_distance_mm() const noexcept
    {
        return this->distance_mm;
    }

}; // namespace HC_SR04