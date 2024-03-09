#ifndef _LCOM_KEYBOARD_H_
#define _LCOM_KEYBOARD_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "i8042.h"
#include "kb_controller.h"

int (kbc_subscribe_int)(uint8_t *bit_no);

int (kbc_unsubscribe_int)();

void (kbc_int_handler)();

int (kbc_restore)();


#endif /* _LCOM_KBCONTROLLER_H_ */
