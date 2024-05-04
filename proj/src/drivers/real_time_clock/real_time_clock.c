#include "real_time_clock.h"

int rtc_hook_id = 5;
real_time_info time_info;

int rtc_get_config(uint8_t reg, uint8_t *config) {
    if (sys_outb(RTC_ADDR_REG, reg)) return 1;
	if (util_sys_inb(RTC_DATA_REG, config)) return 1;
    return 0;
}

int rtc_set_config(uint8_t reg, uint8_t config) {
    if (sys_outb(RTC_ADDR_REG, reg)) return 1;
	if (sys_outb(RTC_DATA_REG, config)) return 1;
    return 0;
}

int rtc_activate_interrupt(uint8_t interrupt) {
    uint8_t config;
    if (rtc_get_config(RTC_REG_B, &config)) return 1;
    config |= interrupt;
    if (rtc_set_config(RTC_REG_B, config)) return 1;
    return 0;
}

int rtc_deactivate_interrupts() {
    uint8_t config;
    if (rtc_get_config(RTC_REG_B, &config)) return 1;
    config &= 0x8F;
    if (rtc_set_config(RTC_REG_B, config)) return 1;
    return 0;
}

int rtc_is_binary() {
    uint8_t result;
    if (rtc_get_config(RTC_REG_B, &result)) return 1;
	return result & BINARY;
}

uint8_t transform_to_binary(uint8_t bcd_number) {
    return ((bcd_number >> 4) * 10) + (bcd_number & 0xF);
}

uint8_t transform_to_bcd(uint8_t binary_number) {
   int bcdResult = 0;
   int shift = 0;

   while (binary_number > 0) {
      bcdResult |= (binary_number % 10) << (shift++ << 2);
      binary_number /= 10;
   }

   return bcdResult;
}


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

void handle_alarm_int() {}
void handle_update_int() {}
void handle_periodic_int() {}

void rtc_ih() {
    uint8_t config;

    rtc_get_config(RTC_REG_C, &config);

    if(config & RTC_AF) handle_alarm_int();
    if(config & RTC_UF) handle_update_int();
    if(config & RTC_PF) handle_periodic_int();
}


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

int rtc_subscribe_interrupts(uint8_t *bit_no) {
    if (bit_no == NULL) return 1;
    *bit_no = BIT(rtc_hook_id);
    return sys_irqsetpolicy(IRQ_RTC, IRQ_REENABLE, &rtc_hook_id);

}

int rtc_unsubscribe_interrupts() {
    return sys_irqrmpolicy(&rtc_hook_id);
}


