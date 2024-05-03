# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}/controllers/
.PATH: ${.CURDIR}/controllers/mouse_keyboard
.PATH: ${.CURDIR}/controllers/serial_port
.PATH: ${.CURDIR}/controllers/timer
.PATH: ${.CURDIR}/controllers/video

# source code files to be compiled  serial_pPOrt.Port.c
SRCS = 	utils.c timer.c KBC.c keyboard.c mouse.c graphics.c project.c main.c

# ./controllers/keyboardMouse/KBC.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -D_LCOM_OPTIMIZED_

# list of library dependencies
DPADD += ${LIBLCF}
LDADD += -llcf -lxpm -llm

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>