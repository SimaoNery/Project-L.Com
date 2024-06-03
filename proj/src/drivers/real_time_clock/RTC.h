#ifndef _LCOM_RTC_H_
#define _LCOM_RTC_H_

#include <lcom/lcf.h>

/** @defgroup RTC RTC
 * @
 *
 */

#define IRQ_RTC             8
#define RTC_ADDR_REG      0x70
#define RTC_DATA_REG      0x71

#define RTC_REG_A   10
#define RTC_REG_B   11 
#define RTC_REG_C   12
#define RTC_REG_D   13

#define SECONDS          0
#define SECONDS_ALARM    1
#define MINUTES          2
#define MINUTES_ALARM    3
#define HOURS            4
#define HOURS_ALARM      5
#define DAY_OF_THE_WEEK  6
#define DAY_OF_THE_MONTH 7
#define MONTH            8
#define YEAR             9

#define BINARY         BIT(2)
#define RTC_UIP        BIT(7)
#define RTC_PIE        BIT(6)
#define RTC_AIE        BIT(5)
#define RTC_UIE        BIT(4)
#define RTC_PF         BIT(6)
#define RTC_AF         BIT(5)
#define RTC_UF         BIT(4)

#endif /* _LCOM_RTC_H */



