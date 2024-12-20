#ifndef _LCOM_KBC_H_
#define _LCOM_KBC_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "i8042.h"
#include "headers.h"

int (get_kbc_status)(uint8_t *status);

int (write_kbc_cmd)(uint8_t port, uint8_t cmd);

int (read_kbc_output)(uint8_t port, uint8_t *of, bool mouse);

#endif /* _LCOM_KBC_H_ */


