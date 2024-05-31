# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}/drivers/
.PATH: ${.CURDIR}/drivers/mouse_keyboard
.PATH: ${.CURDIR}/drivers/timer
.PATH: ${.CURDIR}/drivers/video
.PATH: ${.CURDIR}/drivers/real_time_clock
.PATH: ${.CURDIR}/drivers/serial_port
.PATH: ${.CURDIR}/handlers/
.PATH: ${.CURDIR}/visuals/
.PATH: ${.CURDIR}/visuals/xpm_files
.PATH: ${.CURDIR}/visuals/xpm_files/dateTime
.PATH: ${.CURDIR}/visuals/xpm_files/RES_800_600
.PATH: ${.CURDIR}/visuals/xpm_files/RES_800_600/buttons
.PATH: ${.CURDIR}/visuals/xpm_files/RES_1152_864
.PATH: ${.CURDIR}/visuals/xpm_files/RES_1152_864/buttons
.PATH: ${.CURDIR}/handlers/command_line


# source code files to be compiled 
SRCS = 	utils.c timer.c KBC.c keyboard.c mouse.c graphics.c draw.c sprite.c project.c main.c real_time_clock.c timer_handler.c keyboard_handler.c mouse_handler.c real_time_clock_handler.c command_line.c lights.c queue.c serial.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -D_LCOM_OPTIMIZED_

# list of library dependencies
DPADD += ${LIBLCF}
LDADD += -llcf -lxpm -llm

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>