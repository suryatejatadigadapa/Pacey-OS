#include "exceptions.h"

/*K is the interrupt vector number.*/

/* 
 * create_exceptions
 *   DESCRIPTION: Calls respective exception in handler.c. Loads exceptions in IDT by iterating through k values, where k is the interrupt vector number
 *   INPUTS: none
 *   OUTPUTS: Calls respective exception in handler.c
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void create_exceptions()
{
	int k=0; //Divide By Zero
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_divide_by_zero);			
	}
	
	k = 1; //Debugger
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_debugger);			
	}

	k = 2; //NMI
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_nmi);			
	}

	k = 3; //Breakpoint
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_breakpoint);			
	}

	k = 4; //Overflow
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_overflow);			
	}
	
	k = 5; //Bounds
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_bounds);			
	}

	k = 6; //Invalid Opcode
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_invalid_opcode);			
	}
	
	k = 7; //Coprocessor Not Available
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_coprocessor_not_available);			
	}
	
	k = 8; //Double Fault
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_double_fault);			
	}
	
	k = 9; //Coprocessor Segment Overrun
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_coprocessor_segment_overrun);			
	}

	k = 10; //Invalid Task State Segment
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_invalid_task_state_segment);			
	}
	
	k = 11; //Segment Not Present
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_segment_not_present);			
	}
	
	k = 12; //Stack Fault
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_stack_fault);			
	}

	k = 13; //General Protection Fault
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_general_protection_fault);			
	}

	k = 14; //Page Fault
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_page_fault);			
	}
	
	k = 15; //Reserved
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_reserved);			
	}
	
	k = 16; //Math Fault
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_math_fault);			
	}

	k = 17; //Alignment Check
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_alignment_check);			
	}
	
	k = 18; //Machine Check
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_machine_check);			
	}
	
	k = 19; //SIMD Floating Point
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_simd_floating_point);			
	}

	k = 0x20; //PIT
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_pit_handler);			
	}

	k =0x21 ; //Keyboard Vector
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_key_init);			
	}


	k =0x28 ; //RTC
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_rtc_handler);			
	}

	k =0x80 ; //Generic System Call
	{
		idt[k].present = 1;
		idt[k].dpl = 3;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_sys_call);			
	}
	
	k =0x20+12 ; // mouse
	{
		idt[k].present = 1;
		idt[k].dpl = 0;
		idt[k].reserved0 = 0;
		idt[k].size = 1;
		idt[k].reserved1 = 1;
		idt[k].reserved2 = 1;
		idt[k].reserved3 = 1;
		idt[k].reserved4 = 0;
		idt[k].seg_selector = KERNEL_CS;	
		SET_IDT_ENTRY(idt[k],a_mouse_handler);			
	}
}

/*Gates referenced from OSDev and Linux Source and Wikipedia.*/




