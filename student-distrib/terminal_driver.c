#include "terminal_driver.h"

/* 
 * open_terminal
 *   DESCRIPTION: Initializes the skeleton terminal, clears screen, puts cursor
 *   INPUTS: filename -- dummy parameter
 *   OUTPUTS: writes to keyboard_buf and kbuf_curpos
 *   RETURN VALUE: 0
 *   SIDE EFFECTS: sets capslock_flag and shift_flag to 0
 */
int32_t open_terminal(const uint8_t* filename)
{
	int i;
	//initialize buffer
	for(i = 0; i < BUFSIZE; i++)
		keyboard_buf[terminal_num][i] = 0;
	//initialize flags
	kbuf_curpos[terminal_num] = 0;
	capslock_flag = 0;
 	shift_flag = 0;

 	//reset cursor position
	clear_reset_cursor();
	put_cursor();
	scroll();
	return 0;
}

/* 
 * close_terminal
 *   DESCRIPTION: Close the terminal (i.e. do nothing)
 *   INPUTS: fd -- file descriptor index
 *   OUTPUTS: none
 *   RETURN VALUE: 0
 *   SIDE EFFECTS: none
 */
int32_t close_terminal(int32_t fd)
{
	return 0;
}

/* 
 * strings_match
 *   DESCRIPTION: Helper function to check if 2 strings match
 *   INPUTS: inbuf -- contains first string
 *			 rebuf -- contains second string
 *			 len -- length of string
 *   OUTPUTS: none
 *   RETURN VALUE: 0 if strings match, 1 otherwise
 *   SIDE EFFECTS: none
 */
int strings_match(unsigned char * inbuf, unsigned char * refbuf, int len)
{
	int i;
	//check if 2 strings match
	for (i = 0; i < len; i++)
	{
		if (inbuf[i] != refbuf[i])
			return 0;
	}
	return 1;
}

/* 
 * read_terminal
 *   DESCRIPTION: Read what is typed onto the screen
 *   INPUTS: fd -- file descriptor index
 *			 buf -- stores what is typed
 *			 nbytes -- number of bytes stored in buf
 *   OUTPUTS: none
 *   RETURN VALUE: number of characters typed
 *   SIDE EFFECTS: none
 */
int32_t read_terminal(int32_t fd, void* buf, int32_t nbytes)
{
	int32_t ret_num_char;
	unsigned char * temp_buffer = (unsigned char *)buf;
	//check for enter  position in seperate terminals
	while(enter_pos[user_sel_terminal_num] == 0 || user_sel_terminal_num != terminal_num);
	int i;
	//fill individual keyboard 
	for(i = 0; i < enter_pos[user_sel_terminal_num]; i++)
		temp_buffer[i] = keyboard_buf[user_sel_terminal_num][i];
	ret_num_char = i;
	//set rest of the buffer to 0
	for(i = enter_pos[user_sel_terminal_num]; i < BUFSIZE; i++)
		temp_buffer[i] = 0;
	//reset enter position
	enter_pos[user_sel_terminal_num] = 0;
	return ret_num_char;
}

/* 
 * write_terminal
 *   DESCRIPTION: Write characters to the terminal
 *   INPUTS: fd -- file descriptor index
 *			 buf -- buffer containing contents to write to terminal
 *			 nbytes -- number of bytes to write to terminal
 *   OUTPUTS: none
 *   RETURN VALUE: number of bytes written
 *   SIDE EFFECTS: none
 */
int32_t write_terminal(int32_t fd,const void * buf ,int32_t nbytes)
{

	scroll();
	put_cursor();
	int k=0;
	uint8_t * temp_buffer= (uint8_t*)buf;

	//print the temp buffer on the screen
	int z= strlen((const int8_t*)buf);
	for(k = 0; ((k < z) && (k < nbytes)); k++)
	{
		putc_wrap(temp_buffer[k]);
		scroll();
	}

	return (int32_t)k;
	scroll();
	put_cursor();

}




