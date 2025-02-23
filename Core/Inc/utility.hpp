#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cstdint>
#include <utility>

namespace Utility {

    [[nodiscard]] inline std::uint32_t time_of_flight_ms_to_distance_mm(std::uint32_t const time_of_flight_ms) noexcept
    {
        return (1000U * 340U) * (time_of_flight_ms / 1000U) / 2U;
    }

    inline void delay_us(std::uint32_t const time_us) noexcept
    {}

    [[nodiscard]] inline std::uint32_t count_to_freq_hz(std::uint32_t const count,
                                                        std::uint32_t const prescaler,
                                                        std::uint32_t const clock_frequency,
                                                        std::uint32_t const clock_divider = 0UL) noexcept
    {
        return clock_frequency / (count + 1UL) / (prescaler + 1UL) / (clock_divider + 1UL);
    }

    [[nodiscard]] inline std::uint32_t count_to_time_ms(std::uint32_t const count,
                                                        std::uint32_t const prescaler,
                                                        std::uint32_t const clock_frequency,
                                                        std::uint32_t const clock_divider = 0UL) noexcept
    {
        return 1000UL / count_to_freq_hz(count, prescaler, clock_frequency, clock_divider);
    }

    [[nodiscard]] inline std::uint32_t freq_hz_to_count(std::uint32_t const frequency_hz,
                                                        std::uint32_t const prescaler,
                                                        std::uint32_t const clock_frequency_hz,
                                                        std::uint32_t const clock_divider = 0UL) noexcept
    {
        return clock_frequency_hz / (prescaler + 1UL) / (clock_divider + 1UL) / frequency_hz - 1UL;
    }

    [[nodiscard]] inline std::uint32_t time_ms_to_count(std::uint32_t const time_ms,
                                                        std::uint32_t const prescaler,
                                                        std::uint32_t const clock_frequency_hz,
                                                        std::uint32_t const clock_divider = 0UL) noexcept
    {
        return freq_hz_to_count(1000UL / time_ms, prescaler, clock_frequency_hz, clock_divider);
    }

}; // namespace Utility

#endif // UTILITY_HPP