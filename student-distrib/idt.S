#define ASM     1

#include "idt.h"
#include "x86_desc.h"

#define MAX_FUNCTIONS 10

.data
	pcb_start_esp = 0x7FA000
	pcb_start_ebp = 0x7FA004

sys_call_ret_save: 
	.long 0

.text

	.global a_rtc_handler
	.extern rtc_init

	.global a_pit_handler
	.extern pit_init
	
	.global a_mouse_handler
	.extern mouse_install

	.global a_key_init
	.extern key_init

	.global a_sys_call
	.extern sys_call
	.extern sys_halt
	.extern sys_execute
	.extern sys_read
	.extern sys_write
	.extern sys_open
	.extern sys_close
	.extern sys_getargs
	.extern sys_vidmap
	.extern set_handler
	.extern sys_sigreturn

	.global a_divide_by_zero
	.extern divide_by_zero

	.global a_debugger
	.extern debugger

	.global a_nmi
	.extern nmi

	.global a_breakpoint
	.extern breakpoint

	.global a_overflow
	.extern overflow

	.global a_bounds
	.extern bounds

	.global a_invalid_opcode
	.extern invalid_opcode

	.global a_coprocessor_not_available
	.extern coprocessor_not_available

	.global a_double_fault
	.extern double_fault

	.global a_coprocessor_segment_overrun
	.extern coprocessor_segment_overrun

	.global a_invalid_task_state_segment
	.extern invalid_task_state_segment

	.global a_segment_not_present
	.extern segment_not_present

	.global a_stack_fault
	.extern stack_fault

	.global a_general_protection_fault
	.extern general_protection_fault

	.global a_page_fault
	.extern page_fault

	.global a_reserved
	.extern reserved

	.global a_math_fault
	.extern math_fault

	.global a_alignment_check
	.extern alignment_check

	.global a_machine_check
	.extern machine_check

	.global a_simd_floating_point
	.extern simd_floating_point

# a_sys_call
# Determines which system call to jump to
# Interface: C-style
#    Inputs: EAX -- pointer to system call 
#   Outputs: EAX -- sys_call_ret_save
# Registers: doesn't clobber any
a_sys_call:
	/*Parameter Check on eax to make sure it is within jump table bounds. Jump to done if failure*/
	cmpl $0, %eax
	jle done
	cmpl $(MAX_FUNCTIONS), %eax
	jg done
	/*Push registers and call sys_call_jump_table and get rid of values on stack*/
	pushal
	pushl %edx
	pushl %ecx
	pushl %ebx
	pushl %eax
	/*4 is for cmd*4 + jump table address (4 bytes)*/
	movl sys_call_jump_table(, %eax, 4), %eax 
	call *%eax
	addl $16, %esp	
	/*Move eax value into variable and pop registers*/
	movl %eax ,sys_call_ret_save
	popal
	/*Move ret value into eax and iret on success*/
	movl sys_call_ret_save, %eax
	iret
	/*move -1 into eax and iret on failure*/
done:
	movl $-1, %eax
	iret

/*Jump table to jump to required system call*/
sys_call_jump_table:
.long 0, sys_halt, sys_execute, sys_read, sys_write, sys_open, sys_close, sys_getargs, sys_vidmap, set_handler, sys_sigreturn

# a_rtc_handler
# Calls the RTC handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any
a_rtc_handler:
	cli
	pushal 
	call rtc_init
	popal 
	sti
	iret 

# a_pit_handler
# Calls the PIT handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any
a_pit_handler:
	cli
	pushal
	call pit_init
	popal
	sti
	iret
	
a_mouse_handler:
	//cli
	pushal
	call mouse_handler
	popal
	//sti
	iret

# a_key_init
# Calls the keyboard handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any		
a_key_init:
	pushal 
	call key_init
	popal 
	iret 

# a_divide_by_zero
# Calls the divide_by_zero handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any
a_divide_by_zero:
	cli
	call divide_by_zero
	sti 
	iret 

# a_debugger
# Calls the debugger handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any
a_debugger:
	cli
	call debugger
	sti 
	iret 

# a_nmi
# Calls the NMI handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any
a_nmi:
	cli
	call nmi
	sti 
	iret 

# a_breakpoint
# Calls the breakpoint handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any
a_breakpoint:
	cli
	call breakpoint
	sti 
	iret 

# a_overflow
# Calls the overflow handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any
a_overflow:
	cli
	call overflow
	sti 
	iret 

# a_bounds
# Calls the bounds handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any
a_bounds:
	cli
	call bounds
	sti 
	iret 

# a_invalid_opcode
# Calls the invalid opcode handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any	
a_invalid_opcode:
	cli
	call invalid_opcode
	sti 
	iret 

# a_coprocessor_not_available
# Calls the coprocessor_not_available handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any
a_coprocessor_not_available:
	cli
	call coprocessor_not_available
	sti 
	iret 

# a_double_fault
# Calls the double fault handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any
a_double_fault:
	cli
	call double_fault
	sti 
	iret 

# a_coprocessor_segment_overrun
# Calls the coprocessor_segment_overrun handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any
a_coprocessor_segment_overrun:
	cli
	call coprocessor_segment_overrun
	sti 
	iret 

# a_invalid_task_state_segment
# Calls the invalid task state segment handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any	
a_invalid_task_state_segment:
	cli
	call invalid_task_state_segment
	sti 
	iret 

# a_segment_not_present
# Calls the segment not present handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any
a_segment_not_present:
	cli
	call segment_not_present
	sti 
	iret 

# a_stack_fault
# Calls the stack fault handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any	
a_stack_fault:
	cli
	call stack_fault
	sti 
	iret 

# a_general_protection_fault
# Calls the general protection fault handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any	
a_general_protection_fault:
	cli
	call general_protection_fault
	sti 
	iret 

# a_page_fault
# Calls the page fault handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any
a_page_fault:
	cli
	call page_fault
	sti 
	iret 

# a_reserved
# Calls the reserved handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any	
a_reserved:
	cli
	call reserved
	sti 
	iret 

# a_math_fault
# Calls the math fault handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any
a_math_fault:
	cli
	call math_fault
	sti 
	iret 

# a_alignment_check
# Calls the alignment check handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any	
a_alignment_check:
	cli
	call alignment_check
	sti 
	iret 

# a_machine_check
# Calls the machine check handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any	
a_machine_check:
	cli
	call machine_check
	sti 
	iret 

# a_simd_floating_point
# Calls the simd floating point handler
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: doesn't clobber any
a_simd_floating_point:
	cli
	call simd_floating_point
	sti 
	iret 




