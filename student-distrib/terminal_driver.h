#ifndef TERMINAL_DRIVER_H
#define TERMINAL_DRIVER_H

#include "initial.h"
#include "types.h"
#include "lib.h"
#include "system_calls.h"

/*Macros*/
#define TEXT_WIDTH 80
#define ATTR 0x7
#define BACKSPACE_DOWN 14
#define BACKSPACE_UP 142
#define SHIFT_DOWN 42
#define SHIFT2_DOWN 54
#define SHIFT2_UP 182
#define SHIFT_UP 170
#define CTL_DOWN 29
#define CTL_UP 157
#define CAPSLOCK_DOWN 58
#define ENTER_DOWN 28
#define ENTER_UP 156
#define ALT_DOWN 0x38
#define ALT_UP 0xB8
#define F1_DOWN 0x3B
#define F2_DOWN 0x3C
#define F3_DOWN 0x3D
#define F12_DOWN 0x47
#define ESC_DOWN 1
#define PRSCREEN_DOWN 55
#define TAB_DOWN 15
#define DOWN_SIZE 128
#define BUFSIZE 128
#define MAX_PROCESSES 6
#define MAX_TERMINAL_ARR_SIZ 4

int terminal_num;
int user_sel_terminal_num;
int tcursor_x[MAX_TERMINAL_ARR_SIZ];
int tcursor_y[MAX_TERMINAL_ARR_SIZ];
int active_proc_id_of_terminal[MAX_TERMINAL_ARR_SIZ];
int pid_of_terminal[MAX_TERMINAL_ARR_SIZ];
int base_shell_pid[MAX_TERMINAL_ARR_SIZ];
unsigned char shift_flag;
unsigned char capslock_flag;
unsigned char ctl_flag;
unsigned char alt_flag;
unsigned char keyboard_buf[MAX_TERMINAL_ARR_SIZ][BUFSIZE];
unsigned int kbuf_curpos[MAX_TERMINAL_ARR_SIZ];
unsigned int enter_pos[MAX_TERMINAL_ARR_SIZ];
unsigned int terminal_num_of_proc_id[MAX_PROCESSES];

int32_t open_terminal(const uint8_t* filename);
int32_t close_terminal(int32_t fd);
int32_t read_terminal(int32_t fd, void* buf, int32_t nbytes);
int32_t write_terminal(int32_t fd,const void * buf ,int32_t nbytes);

#endif /* TERMINAL_DRIVER_H */


