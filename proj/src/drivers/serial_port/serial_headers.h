#ifndef _SERIAL_HEADERS_H_
#define _SERIAL_HEADERS_H_

#define COM1_IRQ 4
#define COM1_BASE_REG 0x3F8

#define RBR 0x00
#define THR 0x00
#define IER 0x01
#define IIR 0x02
#define FCR 0x02
#define LCR 0x03
#define MCR 0x04
#define LSR 0x05
#define MSR 0x06
#define SR 0x07

#define DLL 0
#define DLM 1

#define IER_LS4B_MASK 0xF0

#define TRANSMITTER_EMPTY 0x20
#define RECEIVER_READY 0x01
#define SER_OVERRUN_ERR 0x02
#define SER_PARITY_ERR 0x04
#define SER_FRAME_ERR 0x08

#define NO_INT_PENDING 0x01
#define INT_PENDING 0x0E
#define CHAR_TIMEOUT_FIFO 0x0C
#define FIFO_CLEAR 0x07

#define SERIAL_PORT_HOOK_ID 7

#endif
