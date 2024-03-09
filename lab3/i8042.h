#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

/** @defgroup i8042 i8042
 * @
 *
 */

#define KBC_IRQ 1 /**< @brief KBC 1 IRQ line */

#define ESC_BRK 0x81
#define BRK_MASK 0x80

/* I/O port addresses */

#define STATUS_REG 0x64 /**< @brief Status register */
#define OUT_BUF    0x60 /**< @brief Output buffer register */

#define READ_CMD_BYTE 0x20
#define KBC_IN_BUF 0x64
#define WRT_CMD_BYTE 0x60
#define ENABLE_KBD_INT BIT(0)
#define ENABLE_MOUSE_INT BIT(1)

#define INB_FULL 0x02

#define IBF_MASK 0x02
#define IBF 0x02
#define KBD_READ_STATUS_OK 0xE1

#define ATTEMPTS 5
#define DELAY_US 20000

#endif /* _LCOM_I8042_H */
