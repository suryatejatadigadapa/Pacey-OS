#ifndef HANDLER_H
#define HANDLER_H

#include "lib.h"
#include "i8259.h"
#include "paging.h"
#include "rtc_driver.h"
#include "terminal_driver.h"
#include "system_calls.h"

/*Macros*/
#define INDEX_PORT 			0x70
#define DATA_PORT 			0x71
#define COMMAND_REGISTER_1	0x36
#define	COMMAND_REGISTER_2	0x43
#define KEYBOARD_DATA_PORT 	0X60
#define CH_0_DATA_PORT		0x40
#define WRAP_AROUND			0xFF
#define REG_C				0x0C
#define VIDL 				128
#define PIT_FREQUENCY		36157
//#define PIT_FREQUENCY		22222
//#define PIT_FREQUENCY		20000
#define DEC_3				3
#define HALT_S				256

//Exception Handlers
void divide_by_zero();
void debugger();
void nmi();
void breakpoint();
void overflow();
void bounds();
void invalid_opcode();
void coprocessor_not_available();
void double_fault();
void coprocessor_segment_overrun();
void invalid_task_state_segment();
void segment_not_present();
void stack_fault();
void general_protection_fault();
void page_fault();
void reserved();
void math_fault();
void alignment_check();
void machine_check();
void simd_floating_point();
// System Call Handler
void sys_call();
// Keyboard Handler
void key_init();
// PIT Handler
void pit_init();
// RTC Handler
void rtc_init();


#endif /* HANDLER_H */


