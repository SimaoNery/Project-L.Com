#ifndef _LCOM_REAL_TIME_CLOCK_H_
#define _LCOM_REAL_TIME_CLOCK_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "RTC.h"

typedef struct {
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} real_time_info;


int rtc_subscribe_int(uint8_t *bit_no);
int rtc_unsubscribe_int();
int rtc_get_config(uint8_t reg, uint8_t *config);
int rtc_set_config(uint8_t reg, uint8_t config);
int rtc_get_time();
int rtc_set_alarm(uint8_t hours, uint8_t minutes, uint8_t seconds);
int rtc_activate_interrupt(uint8_t interrupt);
int rtc_deactivate_interrupts();
void rtc_ih();

#endif /* _LCOM_REAL_TIME_CLOCK_H_ */


