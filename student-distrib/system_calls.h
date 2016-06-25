#ifndef SYSTEM_CALLS_H
#define SYSTEM_CALLS_H

#include "lib.h"
#include "types.h"
#include "descriptor.h"
#include "terminal_driver.h"
#include "file_func.h"
#include "rtc_driver.h"
#include "paging.h"
#include "handler.h"

/*Macros*/
#define MAX_PROCESSES 6
#define SYS_CALL_READ 3
#define SYS_CALL_WRITE 4
#define SYS_CALL_HALT 1
#define SYS_CALL_EXECUTE 2
#define SYS_CALL_GETARGS 7 
#define SYS_CALL_VIDMAP  
#define SYS_CALL_OPEN 5
#define SYS_CALL_CLOSE 6
#define START_EXECUTABLE 0x7F
#define PCB_PID_ADDRESS 0x7FA008
#define	PCB_ESP_BASE  0x7FA000
#define	PCB_EBP_BASE  0x7FA004
#define PCB_SIZE_BYTES 8
#define KSTACK_BASE_ADDR 0x7FFFFC
#define USER_BASE_STACK 0x83FFFFC
#define FD_LEN 7
#define MAX_FNAME 32
#define ELF_NUM 4
#define EIGHT_KB 8192
#define PCB_SIZE 148
#define ARGS_SIZE 100
#define VAL_4KB 	4096
#define VIDMAP_INVALID 0x400000
#define RTC_FILE 0
#define DIR_FILE 1
#define REG_FILE 2

file_descriptor_t file_desc;
int first_switch[4];
int start_shell[4];
uint8_t is_a_shell[MAX_PROCESSES];
uint32_t esp_proc_cswitch[MAX_PROCESSES];
uint32_t ebp_proc_cswitch[MAX_PROCESSES];
pcb_t pcb_template_array[MAX_PROCESSES];

int32_t sys_halt(unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4);
int32_t sys_execute(unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4);
int32_t sys_read(int p1,int32_t fd, void * buf,int32_t nbytes);
int32_t sys_write(int p1, int32_t fd,const void * buf,int32_t nbytes);
int32_t sys_open(unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4);
int32_t sys_close(unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4);
int32_t sys_getargs(unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4);
int32_t sys_vidmap(unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4);
int32_t set_handler();
int32_t sys_sigreturn();
int context_switch(int proc_id);

#endif /* _SYSTEM_CALLS_H */




