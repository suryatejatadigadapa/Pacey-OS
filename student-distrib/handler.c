#include "handler.h"

int terminal_flag=1;//Flag for terminal

/* 
 * divide_by_zero
 *   DESCRIPTION: alerts that there's been a divide by 0 exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void divide_by_zero()
{
	printf("program terminated by div/zero exception\n");
	sys_halt(0,HALT_S,0,0);
}

/* 
 * debugger
 *   DESCRIPTION: alerts that there's been a debugger exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void debugger()
{
	printf("program terminated by debugger exception\n");
	sys_halt(0,HALT_S,0,0);
}

/* 
 * nmi
 *   DESCRIPTION: alerts that there's been an NMI exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void nmi()
{
	printf("program terminated by nmi exception\n");
	sys_halt(0,HALT_S,0,0);
}

/* 
 * breakpoint
 *   DESCRIPTION: alerts that there's been a breakpoint exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void breakpoint()
{
	printf("program terminated by breakpoint exception\n");
	sys_halt(0,HALT_S,0,0);
}

/* 
 * overflow
 *   DESCRIPTION: alerts that there's been an overflow exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void overflow()
{
	printf("program terminated by overflow exception\n");
	sys_halt(0,HALT_S,0,0);
}

/* 
 * bounds
 *   DESCRIPTION: alerts that there's been a bounds exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void bounds()
{
	printf("program terminated by bounds exception\n");
	sys_halt(0,HALT_S,0,0);
}

/* 
 * invalid_opcode
 *   DESCRIPTION: alerts that there's been an invalid opcode exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void invalid_opcode()
{
	printf("program terminated by invalid_opcode exception\n");
	sys_halt(0,HALT_S,0,0);
} 

/* 
 * coprocessor_not_available
 *   DESCRIPTION: alerts that there's been a coprocessor_not_available exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void coprocessor_not_available()
{
	printf("program terminated by coprocessor_not_available exception\n");
	sys_halt(0,HALT_S,0,0);
}

/* 
 * double_fault
 *   DESCRIPTION: alerts that there's been a double fault exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void double_fault()
{
	printf("program terminated by double fault exception\n");
	sys_halt(0,HALT_S,0,0);
}

/* 
 * coprocessor_segment_overrun
 *   DESCRIPTION: alerts that there's been a coprocessor_segment_overrun exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void coprocessor_segment_overrun()
{
	printf("program terminated by coprocessor_segment_overrun exception\n");
	sys_halt(0,HALT_S,0,0);
}

/* 
 * invalid_task_state_segment
 *   DESCRIPTION: alerts that there's been an invalid_task_state_segment exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void invalid_task_state_segment()
{
	printf("program terminated by invalid_task_state_segment exception\n");
	sys_halt(0,HALT_S,0,0);
}

/* 
 * segment_not_present
 *   DESCRIPTION: alerts that there's been a segment_not_present exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void segment_not_present()
{
	printf("program terminated by segment_not_present exception\n");
	sys_halt(0,HALT_S,0,0);
}

/* 
 * stack_fault
 *   DESCRIPTION: alerts that there's been a stack fault exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void stack_fault()
{
	printf("program terminated by stack_fault exception\n");
	sys_halt(0,HALT_S,0,0);
}

/* 
 * general_protection_fault
 *   DESCRIPTION: alerts that there's been a general_protection_fault exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void general_protection_fault()
{
	printf("program terminated by general_protection_fault exception\n");
	 sys_halt(0,HALT_S,0,0);
}

/* 
 * page_fault
 *   DESCRIPTION: alerts that there's been a page fault exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void page_fault()
{
	printf("program terminated by page_fault exception\n");
	sys_halt(0,HALT_S,0,0);

}

/* 
 * reserved
 *   DESCRIPTION: alerts that there's been a reserved exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void reserved()
{
	printf("program terminated by reserved exception\n");
	sys_halt(0,HALT_S,0,0);
}

/* 
 * math_fault
 *   DESCRIPTION: alerts that there's been a math fault exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void math_fault()
{
	printf("program terminated by math_fault exception\n");
	sys_halt(0,HALT_S,0,0);
}

/* 
 * alignment_check
 *   DESCRIPTION: alerts that there's been an alignment check exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void alignment_check()
{
	printf("program terminated by alignment_check exception\n");
	sys_halt(0,HALT_S,0,0);
}

/* 
 * machine_check
 *   DESCRIPTION: alerts that there's been a machine check exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void machine_check()
{
	printf("program terminated by machine_check exception\n");
	sys_halt(0,HALT_S,0,0);
}

/* 
 * simd_floating_point
 *   DESCRIPTION: alerts that there's been a simd_floating_point exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void simd_floating_point()
{
	printf("program terminated by simd_floating_point exception\n");
	sys_halt(0,HALT_S,0,0);
}

/* 
 * sys_call
 *   DESCRIPTION: alerts that there's been a system call exception
 *   INPUTS: none
 *   OUTPUTS: prints to terminal
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void sys_call()
{
	printf("Exception: system_call");
}

/* 
 * is_alphanum
 *   DESCRIPTION: checks if input character is an alphanumeric
 *   INPUTS: c -- character to check
 *   OUTPUTS: none
 *   RETURN VALUE: 1 if input is alphanumeric, 0 if not
 *   SIDE EFFECTS: none
 */
unsigned char is_alphanum(unsigned char c)
{
// These magic numbers signify if keycode is within range for alphanumeric charcs.
	if( (c >= 16 && c <= 25) || (c >= 30 && c <= 38) || (c >= 44 && c <= 50) )
		return 1;
	else
		return 0;
}

/* key map. VIDL = 128 */
unsigned char key_map[VIDL] =
{
   0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
  '\t',	'q', 'w', 'e', 'r',	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';','\'', '`', 0, '\\', 'z', 
  'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,'*', 0,' ', 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0,  0, 0,  0, 0, 0, '-', 0, 0, 0,'+', 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0,
};

/* shift key map. VIDL = 128 */
unsigned char shift_key_map[VIDL] =
{
   0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
'\t',	'Q', 'W', 'E', 'R',	'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0,
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~', 0, '|', 'Z', 
  'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',   0,'*', 0,' ', 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0,  0, 0,  0, 0, 0, '-', 0, 0, 0,'+', 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0,
};

/* 
 * key_init
 *   DESCRIPTION: keyboard handler that allows corresponding characters to get printed to screen
 *   INPUTS: none
 *   OUTPUTS: writes to keyboard_buf and kbuf_curpos
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void key_init()
{
	
	int old_term_num = terminal_num;
	//only handle input and draw to screen of active terminal
	set_terminal_num(user_sel_terminal_num);
	unsigned char c;	
	c=inb(KEYBOARD_DATA_PORT);
	//set flags for various keys
	if(c == SHIFT_DOWN || c == SHIFT2_DOWN)
		shift_flag = 1;
	else if (c == SHIFT_UP || c == SHIFT2_UP)
		shift_flag = 0;
	else if (c == CAPSLOCK_DOWN)
		capslock_flag = !capslock_flag;
	else if (c == CTL_DOWN)
		ctl_flag = 1;	
	else if (c == CTL_UP)
		ctl_flag = 0;
	else if (c == ALT_DOWN)
		alt_flag = 1;
	else if (c == ALT_UP)
		alt_flag = 0;
	//if shift flag
	else if (shift_flag == 1 && c == ENTER_DOWN)
	{
		keyboard_buf[user_sel_terminal_num][kbuf_curpos[user_sel_terminal_num]] = '\n';
		enter_pos[user_sel_terminal_num] = kbuf_curpos[user_sel_terminal_num];
		kbuf_curpos[user_sel_terminal_num] = 0;
		putc('\n');
		shift_flag=1;		
	}
	//if enter flag
	else if (c == ENTER_DOWN)
	{
		keyboard_buf[user_sel_terminal_num][kbuf_curpos[user_sel_terminal_num]] = '\n';
		kbuf_curpos[user_sel_terminal_num]++;
		enter_pos[user_sel_terminal_num] = kbuf_curpos[user_sel_terminal_num];
		kbuf_curpos[user_sel_terminal_num] = 0;
		putc('\n');
		shift_flag=0;	
	}
	//if backspace
	else if (c == BACKSPACE_DOWN)
	{
		if(get_cursor_x() > kbuf_curpos[user_sel_terminal_num]-1)
		{
			//use actual, screen cursor x, NOT the kbuf curpos.
			backspace(0);
			keyboard_buf[user_sel_terminal_num][kbuf_curpos[user_sel_terminal_num]] = '\0';
			kbuf_curpos[user_sel_terminal_num]--;
		}		
		else if(get_cursor_x() <= kbuf_curpos[user_sel_terminal_num]-1 && kbuf_curpos[user_sel_terminal_num] > 0)
		{
			if(get_cursor_x() == 0)
				backspace(1);
			else
				backspace(0);
			keyboard_buf[user_sel_terminal_num][kbuf_curpos[user_sel_terminal_num]] = '\0';
			kbuf_curpos[user_sel_terminal_num]--;			
		}
	}
	//if less than 128 chars
	if(kbuf_curpos[user_sel_terminal_num] < VIDL-1)//128 is buffer size
	{
		unsigned char pchar = 0;
		if(c < DOWN_SIZE && c != SHIFT_DOWN && c != CAPSLOCK_DOWN && 
			c != ENTER_DOWN && c != BACKSPACE_DOWN && c != BACKSPACE_UP && c != ESC_DOWN &&
			c != PRSCREEN_DOWN && c != TAB_DOWN)
		{
			//if capslock is on
			if(capslock_flag == 0)
			{
				//if shift is off
				if(!shift_flag)
				 	pchar = key_map[c];
				else
					pchar = shift_key_map[c];
				//if clear
				if(ctl_flag == 1 && key_map[c] == 'l' )
				{
				 	clear_reset_cursor();
				 	kbuf_curpos[user_sel_terminal_num] = 0;
				 	//restore the old terminal
				 	set_terminal_num(old_term_num);
				 	send_eoi(1);
				 	return;
				 }
			}
			//if small case
			else
			{
				//if clear
				if(ctl_flag == 1 && shift_key_map[c] == 'L')
				{
				 	clear_reset_cursor();
				 	kbuf_curpos[user_sel_terminal_num] = 0;
				 	//restore the old terminal
				 	set_terminal_num(old_term_num);
				 	send_eoi(1);
				 	return;
				}
				//find which case and which char
				if(!shift_flag && is_alphanum(c) == 0)
					pchar = key_map[c];
				else if (shift_flag && is_alphanum(c) == 0)
					pchar = shift_key_map[c];
				else if(!shift_flag && is_alphanum(c) == 1)
					pchar = shift_key_map[c];
				else //if (shift_flag && is_alphanum(c) == 1)
					pchar = key_map[c];
			}
		}
		//if char is valid
		if(pchar != 0)
		{
			putc_wrap(pchar);
			keyboard_buf[user_sel_terminal_num][kbuf_curpos[user_sel_terminal_num]] = pchar;
			kbuf_curpos[user_sel_terminal_num]++;	

		}
	}
	if (c >= F1_DOWN && c <= F12_DOWN)
	{
		//get terminal number
		if(alt_flag && c <= F1_DOWN+2)
		{
			int cur_terminal = terminal_num;
			//ONLY when you select a new terminal should you change user select
			user_sel_terminal_num = c - F1_DOWN + 1;
			terminal_num = user_sel_terminal_num;
			//reset the terminal val if you change it
			set_terminal_num(user_sel_terminal_num);
			change_active_term_num(user_sel_terminal_num);
			//if on different terminal
			if(terminal_num != cur_terminal)			
			{
				int i;
				unsigned char command[6] = "shell";
				send_eoi(1);
				//dont open t2 & t3
				if(first_switch[terminal_num] == 1 && num_processes < 6)
				{
					//gets the id it will be assigned by execute
					int newidx = lowest_available_block_idx();
					base_shell_pid[terminal_num] = newidx;
					//fill buffer with 0
					for(i = 0; i < BUFSIZE; i++)
						keyboard_buf[user_sel_terminal_num][i] = 0;
					//set flags
					start_shell[terminal_num] = 0;
					first_switch[terminal_num] = 0;
					kbuf_curpos[user_sel_terminal_num] = 0;
					sys_execute(1, (unsigned int)command, 0, 0);
				}
			}
		}
	}
	//restore the old terminal once you leave the handler
	put_cursor();	
	scroll();
	set_terminal_num(old_term_num);
	send_eoi(1);
}

/* 
 * pit_init
 *   DESCRIPTION: PIT handler that allows scheduling to work
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void pit_init()
{
	/*Set frequency to 33HZ (interrupt every 30 milliseconds). */
    outb(COMMAND_REGISTER_1, COMMAND_REGISTER_2);
    outb(PIT_FREQUENCY & WRAP_AROUND, CH_0_DATA_PORT);
    outb(PIT_FREQUENCY >> DEC_8, CH_0_DATA_PORT);
	send_eoi(0);			
	//Set the terminals and what to display to screen
	set_terminal_num(user_sel_terminal_num);
	disp_active_term();
	set_terminal_num(terminal_num);
	//scheduling algorithm to switch based on which terminal and processes in and set sched term num
	int sched_term_num = terminal_num;
	sched_term_num++;
	if(sched_term_num > DEC_3)
		sched_term_num = 1;
	if(active_proc_id_of_terminal[sched_term_num] == -1)
		sched_term_num++;
	if(sched_term_num > DEC_3)
		sched_term_num = 1;
	if(active_proc_id_of_terminal[sched_term_num] == -1)
		sched_term_num = 1;
	//restore esp and ebp
	asm volatile("mov %%esp, %0" : "=r"(esp_proc_cswitch[cur_process]):);
	asm volatile("mov %%ebp, %0" : "=r"(ebp_proc_cswitch[cur_process]):);
	//check that not in base shell
	if(active_proc_id_of_terminal[sched_term_num] != -1)
	{
		//set terminal nos
		int cur_terminal = terminal_num;
		terminal_num = sched_term_num;
		//schedule/context switch based on if condition check
		if(cur_terminal != terminal_num || (terminal_num == user_sel_terminal_num && cur_process != active_proc_id_of_terminal[terminal_num]))
		{
			//context switch for scheduling
			set_terminal_num(terminal_num);
			context_switch(active_proc_id_of_terminal[terminal_num]);
		}
	}
}

/* 
 * rtc_init
 *   DESCRIPTION: RTC handler that allows for generating interrupts
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void rtc_init()
{
	//update tick and flag
	tick[terminal_num]++;
	rtc_flag[terminal_num]=0;
	//register c 
	outb(REG_C,INDEX_PORT);
	//read from port
	inb(DATA_PORT); 
	send_eoi(DEC_8);
}

/*Reference for keyboard mapping: http://www.osdever.net/bkerndev/Docs/keyboard.htm*/
/*Reference for rtc_init and key_init: OSDev*/




