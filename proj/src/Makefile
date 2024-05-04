# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}/drivers/
.PATH: ${.CURDIR}/drivers/mouse_keyboard
.PATH: ${.CURDIR}/drivers/timer
.PATH: ${.CURDIR}/drivers/video
.PATH: ${.CURDIR}/drivers/real_time_clock
.PATH: ${.CURDIR}/drivers/serial_port
.PATH: ${.CURDIR}/visuals/
.PATH: ${.CURDIR}/visuals/xpm_files

# source code files to be compiled 
SRCS = 	utils.c timer.c KBC.c keyboard.c mouse.c graphics.c sprite.c project.c main.c real_time_clock.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -D_LCOM_OPTIMIZED_

# list of library dependencies
DPADD += ${LIBLCF}
LDADD += -llcf -lxpm -llm

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>