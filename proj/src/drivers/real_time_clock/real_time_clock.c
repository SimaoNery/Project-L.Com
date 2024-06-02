#include "real_time_clock.h"

int rtc_hook_id = 5;
real_time_info time_info;
uint8_t config_RTC;

/*!
 * @brief Retrieves the configuration from a specified RTC register.
 * 
 * @param reg The register to read from.
 * @param config Pointer to a variable where the configuration will be stored.
 * @return int Returns 0 upon success and 1 upon failure.
 */
int rtc_get_config(uint8_t reg, uint8_t *config) {
    if (sys_outb(RTC_ADDR_REG, reg)) return 1;
	if (util_sys_inb(RTC_DATA_REG, config)) return 1;
    return 0;
}

/*!
 * @brief Sets the configuration of a specified RTC register.
 * 
 * @param reg The register to write to.
 * @param config The configuration value to write.
 * @return int Returns 0 upon success and 1 upon failure.
 */
int rtc_set_config(uint8_t reg, uint8_t config) {
    if (sys_outb(RTC_ADDR_REG, reg)) return 1;
	if (sys_outb(RTC_DATA_REG, config)) return 1;
    return 0;
}

/*!
 * @brief Activates a specified RTC interrupt.
 * 
 * @param interrupt The interrupt to activate.
 * @return int Returns 0 upon success and 1 upon failure.
 */
int rtc_activate_interrupt(uint8_t interrupt) {
    uint8_t config;
    if (rtc_get_config(RTC_REG_B, &config)) return 1;
    config |= interrupt;
    if (rtc_set_config(RTC_REG_B, config)) return 1;
    return 0;
}

/*!
 * @brief Deactivates RTC interrupts.
 * 
 * @return int Returns 0 upon success and 1 upon failure.
 */
int rtc_deactivate_interrupts() {
    uint8_t config;
    if (rtc_get_config(RTC_REG_B, &config)) return 1;
    config &= 0x8F;
    if (rtc_set_config(RTC_REG_B, config)) return 1;
    return 0;
}

/*!
 * @brief Checks if the RTC is in binary mode.
 * 
 * @return int Returns 1 if in binary mode, 0 otherwise.
 */
int rtc_is_binary() {
    uint8_t result;
    if (rtc_get_config(RTC_REG_B, &result)) return 1;
	return result & BINARY;
}

/*!
 * @brief Converts a BCD number to binary.
 * 
 * @param bcd_number The BCD number to convert.
 * @return uint8_t The converted binary number.
 */
uint8_t transform_to_binary(uint8_t bcd_number) {
    return ((bcd_number >> 4) * 10) + (bcd_number & 0xF);
}

/*!
 * @brief Converts a binary number to BCD.
 * 
 * @param binary_number The binary number to convert.
 * @return uint8_t The converted BCD number.
 */
uint8_t transform_to_bcd(uint8_t binary_number) {
   int bcdResult = 0;
   int shift = 0;

   while (binary_number > 0) {
      bcdResult |= (binary_number % 10) << (shift++ << 2);
      binary_number /= 10;
   }

   return bcdResult;
}

/*!
 * @brief Sets the RTC alarm time.
 * 
 * @param hours The hours value for the alarm.
 * @param minutes The minutes value for the alarm.
 * @param seconds The seconds value for the alarm.
 * @return int Returns 0 upon success and 1 upon failure.
 */
int rtc_set_alarm(uint8_t hours, uint8_t minutes, uint8_t seconds) {
    if (rtc_is_binary()) {
        if (rtc_set_config(HOURS_ALARM, hours)) return 1;
        if (rtc_set_config(MINUTES_ALARM, minutes)) return 1;
        if (rtc_set_config(SECONDS_ALARM, seconds)) return 1;
    }
    else {
        if (rtc_set_config(HOURS_ALARM, transform_to_bcd(hours))) return 1;
        if (rtc_set_config(MINUTES_ALARM, transform_to_bcd(minutes))) return 1;
        if (rtc_set_config(SECONDS_ALARM, transform_to_bcd(seconds))) return 1;
    }

    return 0;
}

/*!
 * @brief RTC interrupt handler.
 * 
 * Reads the RTC configuration and calls the appropriate interrupt handler.
 */
void rtc_ih() {
    rtc_get_config(RTC_REG_C, &config_RTC);
}

/*!
 * @brief Retrieves the current time from the RTC.
 * 
 * @return int Returns 0 upon success and 1 upon failure.
 */
int rtc_get_time() {

    uint8_t out;

    do {
        if (rtc_get_config(RTC_REG_A, &out)) return 1;
    } while (out & RTC_UIP);

    if (rtc_is_binary()) {
        if (rtc_get_config(SECONDS, &out)) return 1;
        time_info.seconds = out;

        if (rtc_get_config(MINUTES, &out)) return 1;
        time_info.minutes = out;

        if (rtc_get_config(HOURS, &out)) return 1;
        time_info.hours = out;


        if (rtc_get_config(DAY_OF_THE_MONTH, &out)) return 1;
        time_info.day = out;


        if (rtc_get_config(MONTH, &out)) return 1;
        time_info.month = out;


        if (rtc_get_config(YEAR, &out)) return 1;
        time_info.year = out;
    }

    else {
        if (rtc_get_config(SECONDS, &out)) return 1;
        time_info.seconds = transform_to_binary(out);

        if (rtc_get_config(MINUTES, &out)) return 1;
        time_info.minutes = transform_to_binary(out);

        if (rtc_get_config(HOURS, &out)) return 1;
        time_info.hours = transform_to_binary(out);


        if (rtc_get_config(DAY_OF_THE_MONTH, &out)) return 1;
        time_info.day = transform_to_binary(out);


        if (rtc_get_config(MONTH, &out)) return 1;
        time_info.month = transform_to_binary(out);


        if (rtc_get_config(YEAR, &out)) return 1;
        time_info.year = transform_to_binary(out);
    }

    return 0;
}

/*!
 * @brief Subscribes to RTC interrupts.
 * 
 * @param bit_no Pointer to a variable where the bit number will be stored.
 * @return int Returns 0 upon success and 1 upon failure.
 */
int rtc_subscribe_int(uint8_t *bit_no) {
    if (bit_no == NULL) return 1;
    *bit_no = BIT(rtc_hook_id);
    return sys_irqsetpolicy(IRQ_RTC, IRQ_REENABLE, &rtc_hook_id);

}

/*!
 * @brief Unsubscribes from RTC interrupts.
 * 
 * @return int Returns 0 upon success and 1 upon failure.
 */
int rtc_unsubscribe_int() {
    return sys_irqrmpolicy(&rtc_hook_id);
}


