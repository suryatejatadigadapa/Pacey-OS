#include "tracker.h"

/* 
 * tracker_init
 *   DESCRIPTION: Initialize all the tracking variables
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void tracker_init()
{
	rtc_flag[1]=1;
	rtc_flag[2]=1;
	rtc_flag[3]=1;

	cur_process = 0;
	num_processes = 0;

	first_switch[0] = -1;
	first_switch[1] = 0;
	first_switch[2] = 1;
	first_switch[3] = 1;
	
	start_shell[0] = -1;
	start_shell[1] = 0;
	start_shell[2] = 1;
	start_shell[3] = 1;

	tick[1] = 0;
	tick[2] = 0;
	tick[3] = 0;

	block_in_use[0] = 0;
	block_in_use[1] = 0;
	block_in_use[2] = 0;
	block_in_use[3] = 0;
	block_in_use[4] = 0;
	block_in_use[5] = 0;

	is_a_shell[0] = 0;
	is_a_shell[1] = 0;
	is_a_shell[2] = 0;
	is_a_shell[3] = 0;
	is_a_shell[4] = 0;
	is_a_shell[5] = 0;

	enter_pos[1] = 0;
	enter_pos[2] = 0;
	enter_pos[3] = 0;

	terminal_num_of_proc_id[0] = 0;
	terminal_num_of_proc_id[1] = 0;
	terminal_num_of_proc_id[2] = 0;
	terminal_num_of_proc_id[3] = 0;
	terminal_num_of_proc_id[4] = 0;
	terminal_num_of_proc_id[5] = 0;

	user_sel_terminal_num = 1;

	terminal_num = 1;
	
	tcursor_x[1] = 0;
	tcursor_y[1] = 0;
	tcursor_x[2] = 0;
	tcursor_y[2] = 0;
	tcursor_x[3] = 0;
	tcursor_y[3] = 0;

	base_shell_pid[0] = -1;
	base_shell_pid[1] = 0;
	base_shell_pid[2] = -1;
	base_shell_pid[3] = -1;

	active_proc_id_of_terminal[1] = -1;
	active_proc_id_of_terminal[2] = -1;
	active_proc_id_of_terminal[3] = -1;
}




