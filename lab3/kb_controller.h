#ifndef _LCOM_KBCONTROLLER_H_
#define _LCOM_KBCONTROLLER_H_

#include <minix/sysutil.h>
#include "i8042.h"
#include <lcom/lcf.h>
#include <minix/sysutil.h>

int (kbc_get_status)(uint8_t* st);

int (kbc_get_out)(uint8_t *of);

int (kbc_write_cmd)(uint8_t port, uint8_t cmd);

int (read_from_keyboard)(uint8_t port, uint8_t *of);

int (write_in_keyboard)(uint8_t port, uint8_t cmd);

#endif /* _LCOM_KBCONTROLLER_H_ */
