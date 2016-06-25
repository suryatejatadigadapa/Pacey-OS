#ifndef _IDT_H
#define _IDT_H
#include "types.h"

#ifndef ASM

extern void a_sys_call(void);
extern void a_rtc_handler(void);
extern void a_pit_handler(void);
extern void a_key_init(void);

extern void a_divide_by_zero(void);
extern void a_debugger(void);
extern void a_nmi(void);
extern void a_breakpoint(void);
extern void a_overflow(void);
extern void a_bounds(void);
extern void a_invalid_opcode(void);
extern void a_coprocessor_not_available(void);
extern void a_double_fault(void);
extern void a_coprocessor_segment_overrun(void);
extern void a_invalid_task_state_segment(void);
extern void a_segment_not_present(void);
extern void a_stack_fault(void);
extern void a_general_protection_fault(void);
extern void a_page_fault(void);
extern void a_reserved(void);
extern void a_math_fault(void);
extern void a_alignment_check(void);
extern void a_machine_check(void);
extern void a_simd_floating_point(void);
extern void a_mouse_handler(void);

#endif /* ASM */

#endif /* _IDT_H */


