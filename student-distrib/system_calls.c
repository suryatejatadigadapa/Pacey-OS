#include "system_calls.h"
#include "x86_desc.h"

//global array for extra arguments
uint8_t args[ARGS_SIZE];

//stdin fd_array
fd_array_t file_arr; 

//stdout fd_array
fd_array_t file_arr1;

//declaring function operation pointers for rtc file_descriptor 
fd_array_t file_arr_rtc =
{
	.open = open_rtc,
	.close = close_rtc,
	.read = read_rtc,
	.write = write_rtc
};

//declaring function operation pointers for file  
fd_array_t file_arr_file =
{
	.open = file_open,
	.close = file_close,
	.read = file_read,
	.write = file_write
};

//declaring function operation pointers for directory  
fd_array_t file_arr_dir =
{
	.open = dir_open,
	.close = dir_close,
	.read = dir_read,
	.write = dir_write
};

//declaring function operation pointers for stdin  
fd_array_t file_arr =
{
	.open = open_terminal,
	.close = close_terminal,
	.read = read_terminal,
	.write = NULL
};

//declaring function operation pointers for stdout  
fd_array_t file_arr1=
{
	.open = open_terminal,
	.close = close_terminal,
	.read = NULL,
	.write = write_terminal
};


/* 
 * sys_halt
 *   DESCRIPTION: halts the process unless its a base shell
 *   INPUTS: p2- status - thats is the retrun value to be returned to the handler
 *   OUTPUTS: none
 *   RETURN VALUE: 0 on success, -1 on failure
 *   SIDE EFFECTS: halts the process, restarts the shell if base shell is terminated
 */
int32_t sys_halt(unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4)
{
	uint8_t status = (uint8_t)p2;
	//close all the files
	int i=0;
	for(i=2;i<=FD_LEN;i++)
		sys_close(0,i,0,0);

	//decrement the number of processes
	num_processes--;

	//condition to check if you re trying to halt base shell of any terminal
	if (base_shell_pid[terminal_num] == cur_process )
	{
		printf("YOU TRIED EXITING THE BASE SHELL\n");
		block_in_use[cur_process] = 0; 	//set the block_in_use array to 0 , sice that block is freed
		is_a_shell[cur_process] = 0;   	//is_a_shell is set to 0 , because we restart base shell
		terminal_num_of_proc_id[cur_process] = 0;  //the current process of a terminal is also 0
		int newidx = lowest_available_block_idx();  //find the available block
		active_proc_id_of_terminal[terminal_num] = newidx;
		base_shell_pid[terminal_num] = newidx;
		unsigned char command[6] = "shell";  //call shell again
		sys_execute(1, (unsigned int)command, 0, 0);
	}
	//set the paging for parent 
	halt_paging_helper(pcb_template_array[cur_process].parent_id);

	//restore the esp and ebp of the current process
	asm volatile("mov %0, %%esp " : :"r"(pcb_template_array[cur_process].esp));
	asm volatile("mov %0, %%ebp " : :"r"(pcb_template_array[cur_process].ebp));
	
	//set shells and terminals
	is_a_shell[cur_process] = 0;
	terminal_num_of_proc_id[cur_process] = 0;
	
	//restore the tss for the parent
	tss.esp0 = KSTACK_BASE_ADDR - (pcb_template_array[cur_process].parent_id)*(EIGHT_KB);
	tss.ss0 = KERNEL_DS;

	//check if the active process of a terminal is this current process , if yes then set its parent id as the current process of that terminal
	if(active_proc_id_of_terminal[terminal_num] == cur_process)
		active_proc_id_of_terminal[terminal_num] = pcb_template_array[cur_process].parent_id;

	//set the current process as its parent 
	cur_process = pcb_template_array[cur_process].parent_id;
	//return the return value passed in 
	asm volatile("mov %0, %%eax ": :"r"((uint32_t)status));
	//jump to halt return in sys_execute
	asm volatile("jmp hal_return");

	return 0;
}

/* 
 * sys_execute
 *   DESCRIPTION: executes the process , by loading the program in the physical memory, 
 * 				 process stack in kernel space, initalizes its own pcb and context switches into user space
 *   INPUTS: p2- command - command given by the user
 *   OUTPUTS: changes the mapping and initializes pcb structures 
 *   RETURN VALUE: 0 on success, -1 on failure
 *   SIDE EFFECTS: executes the process
 */
int32_t sys_execute(unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4)
{
	unsigned char * command = (unsigned char *)p2;
	unsigned char filename[MAX_FNAME];
	uint8_t buf_file[ELF_NUM];
	int32_t check_fname;
	int32_t read_test_exec;
	int i=0;
	int j=0;
	
	//initialize filename
	for(i = 0; i < MAX_FNAME; i++)
		filename[i] = '\0';
	//initializ argument
	for(i = 0; i < MAX_FNAME; i++)
		args[i] = '\0';

	//extract filename
	i = 0;
	j = 0;
	while(command[i]!='\0' && command[i] != '\n' && command[i] != ' ')
	{
		filename[j]=command[i];
		i++; j++;
	}
	//extract arguments
	j = 0;
	if(command[i] == ' ' && command[i+1] != '\0')
	{
		i++;
		while(command[i] != '\0')
		{
			args[j] = command[i];
			i++;	j++;
		}
	}

	//max num process check err condition
	if(num_processes >= 6)
	{
		printf("Cannot run more than SIX processes. Type exit to go back to previous shell.\n");
		return -1;
	}

	else
	{
		dentry_t dentry;
		//check if filename is correct
		check_fname = read_dentry_by_name ((const uint8_t*) filename, &dentry);
		if (check_fname != 0)
			return -1;
		
		uint32_t inode=(&dentry)->inode_index;
		//checking if its and exceutable
		read_test_exec = read_data (inode,0, buf_file, ELF_NUM);
		if (read_test_exec == -1)
		{
			return -1;
		}

		//ELF is extracted from buf_file 0,1,2,3, to check for executable.
		if(buf_file[1]!='E' || buf_file[2]!='L' || buf_file[3]!='F' || buf_file[0]!= START_EXECUTABLE)
			return -1;

		int new_process_id = lowest_available_block_idx();
		block_in_use[new_process_id] = 1;
		//load the program into the physical memory and map it , also return the eip of the program 
		uint32_t file_return_address = user_paging( (const uint8_t *) filename, new_process_id);
		//check the return address
		if(file_return_address == -1)
			return -1;

		//stdin
		pcb_template_array[new_process_id].file.fd[0].file_operations_table_pointer = (fd_array_t *) (&file_arr);		
		pcb_template_array[new_process_id].file.fd[0].flags=1;
		//stdout
		pcb_template_array[new_process_id].file.fd[1].file_operations_table_pointer = (fd_array_t *) (&file_arr1);
		pcb_template_array[new_process_id].file.fd[1].flags=1;

		//make the tss point to the correct stack for the process
		tss.esp0 = KSTACK_BASE_ADDR - new_process_id*(EIGHT_KB);
		tss.ss0 = KERNEL_DS;

		asm volatile("mov %%esp, %0" : "=r"(pcb_template_array[new_process_id].esp):);
		asm volatile("mov %%ebp, %0" : "=r"(pcb_template_array[new_process_id].ebp):);
		//unless it's a terminal/the base shell, always the current process
		if(new_process_id == 0)
			pcb_template_array[new_process_id].parent_id = -1;
		else
			pcb_template_array[new_process_id].parent_id = cur_process; 

		memcpy((void*) (PCB_PID_ADDRESS-(EIGHT_KB*new_process_id)), (void*)&pcb_template_array[new_process_id], PCB_SIZE);

		//if there is no current process running in a terminal set it to the process_id
		if(terminal_num_of_proc_id[new_process_id] == 0)
		{
			terminal_num_of_proc_id[new_process_id] = terminal_num;
			active_proc_id_of_terminal[terminal_num] = new_process_id;
		}

		//check for  running shells
		if(filename[0] == 's' && filename[1] == 'h' && filename[2] == 'e' && filename[3] == 'l' && filename[4] == 'l')
			is_a_shell[new_process_id] = 1;

		cur_process=new_process_id;
		//increment the num_processes
		num_processes++;
		//context switch to user stack
		asm volatile("mov %0 , %%ds" : :"r"(USER_DS));
		asm volatile("mov %0, %%eax " : :"r"(USER_DS));
		asm volatile("push %eax") ;//ss
		asm volatile("mov %0, %%eax" ::"r"(USER_BASE_STACK));
		asm volatile("push %eax"); //esp
		asm volatile("pushf") ;//eflags
		asm volatile("mov %0 , %%eax" : :"r"(USER_CS));
		asm volatile("push %eax") ;//cs
		asm volatile("mov %0, %%eax "::"r"(file_return_address)); 
		asm volatile("push %eax ") ;//eip
		asm volatile("mov %0, %%eax "::"r"(0)); 
		asm volatile("IRET");
		asm volatile("hal_return: ");
		return 0;
	}
}

/* 
 * context_switch
 *   DESCRIPTION: scheduling context switch from on eprocess to another
 *   INPUTS:proc_id - process id that needs to be context switched to
 *   OUTPUTS: changes the tss and restores esp and ebp
 *   RETURN VALUE: 0 on success, -1 on failure
 *   SIDE EFFECTS: context switching
 */
int context_switch(int proc_id)
{	
	//restore the correct task segment 
	tss.esp0 = KSTACK_BASE_ADDR - proc_id*(EIGHT_KB);
	tss.ss0 = KERNEL_DS;
	//change the paging for the current program 
	context_switch_paging_helper(proc_id);
	//set the current process to the id 
	cur_process = proc_id;	
	//retsore esp and ebp to the process ids esp and ebp saved in the handler
	asm volatile("mov  %0, %%esp" : : "r"(esp_proc_cswitch[proc_id]));
	asm volatile("mov  %0, %%ebp" : : "r"(ebp_proc_cswitch[proc_id]));
	return 0;		
}

/* 
 * sys_read
 *   DESCRIPTION: Read system call, which calls the read function corresponding to
 *				  the passed in file descriptor
 *   INPUTS: p1 -- unused
 *			 fd -- file descriptor index
 *			 buf -- buffer for reading bytes
 *			 nbytes -- number of bytes to read up to
 *   OUTPUTS: none
 *   RETURN VALUE: read function corresponding to fd, or -1 if unsuccessful
 *   SIDE EFFECTS: none
 */ 
 int32_t sys_read(int p1,int32_t fd, void * buf,int32_t nbytes)
{
	//check if buf is inavlid
	if (buf == NULL)
	{
		return -1;
	}
	// fd out of range or stdout
	if (fd == 1 || fd > FD_LEN || fd < 0)
		return -1; 	
	// check if slot is closed
	if (pcb_template_array[cur_process].file.fd[fd].flags == 0)
		return -1;
	// execute the read function corresponding to fd
	return pcb_template_array[cur_process].file.fd[fd].file_operations_table_pointer->read(fd, buf, nbytes);
}

 /* 
 * sys_write
 *   DESCRIPTION: Write system call, which calls the write function corresponding to
 *				  the passed in file descriptor
 *   INPUTS: p1 -- unused
 *			 fd -- file descriptor index
 *			 buf -- buffer for writing bytes
 *			 nbytes -- number of bytes to write up to
 *   OUTPUTS: none
 *   RETURN VALUE: write function corresponding to fd, or -1 if unsuccessful
 *   SIDE EFFECTS: none
 */
int32_t sys_write(int p1,int32_t fd,const void * buf,int32_t nbytes)
{
	//check if buf is inavlid
	if (buf == NULL)
	{
		return -1;
	}
	// fd out of range or stdout
	if (fd == 0 || fd > FD_LEN || fd < 0)
		return -1; 	
	// check if slot is closed
	if (pcb_template_array[cur_process].file.fd[fd].flags == 0)
		return -1;
	// execute the read function corresponding to fd
	return pcb_template_array[cur_process].file.fd[fd].file_operations_table_pointer->write(fd, buf, nbytes);
}

 /* 
 * sys_open
 *   DESCRIPTION: Open system call, which finds the first available slot in the 
 *				  file descriptor array
 *   INPUTS: p1, p3, p4 -- unused
 *			 p2 -- filename for determining file type
 *   OUTPUTS: writes to file descriptor array
 *   RETURN VALUE: index of first open slot in fd array, or -1 if unsuccessful
 *   SIDE EFFECTS: none
 */ 
int32_t sys_open(unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4)
{	
	const uint8_t* filename = (const uint8_t*)p2;
	int i = 2; // first fd's correspond to stdin/out
	int check;
	dentry_t dentry;
	
	while (pcb_template_array[cur_process].file.fd[i].flags == 1 && i <= FD_LEN) 
	{
		i++; // find first open slot
	}
	if (i > FD_LEN)
	{
		return -1; 
	}

	check = read_dentry_by_name(filename, &dentry);
	
	if (check != 0) 
	{
		return -1; // read_dentry_by_name failed
	}
	
	pcb_template_array[cur_process].file.fd[i].flags = 1; // open next available slot
	pcb_template_array[cur_process].file.fd[i].inode = dentry.inode_index; 
	pcb_template_array[cur_process].file.fd[i].file_position = 0; 	
	
	// identify type of file
	if (dentry.filetype == RTC_FILE) { // RTC
		pcb_template_array[cur_process].file.fd[i].file_operations_table_pointer = (&file_arr_rtc);
	}
	if (dentry.filetype == DIR_FILE) { // directory
		pcb_template_array[cur_process].file.fd[i].file_operations_table_pointer = (&file_arr_dir);
		
	}
	if (dentry.filetype == REG_FILE) { // regular file
		pcb_template_array[cur_process].file.fd[i].file_operations_table_pointer = (&file_arr_file);
	}
	pcb_template_array[cur_process].file.fd[i].file_operations_table_pointer->open(filename);
	return i;
}

 /* 
 * sys_close
 *   DESCRIPTION: Close system call, which marks the file descriptor array slot
 *				  corresponding to passed in parameter as closed
 *   INPUTS: p1, p3, p4 -- unused
 *			 p2 -- file descriptor array slot to close
 *   OUTPUTS: writes to file descriptor array
 *   RETURN VALUE: 0 if successfully closed, -1 otherwise
 *   SIDE EFFECTS: none
 */
int32_t sys_close(unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4)
{
	int32_t fd = (int32_t)p2;
	if (fd == 0 || fd == 1)
		return -1; // fail
	else if (fd > 1 && fd <= FD_LEN) 
	{
		if (pcb_template_array[cur_process].file.fd[fd].flags == 1) 
		{
			pcb_template_array[cur_process].file.fd[fd].flags = 0;
			return 0;
		}
		else // file is unopened
			return -1;
	}
	else
		return -1; // fd is out of range
}

 /* 
 * sys_get_args
 *   DESCRIPTION: gets the arguments
 *   INPUTS: p2,p3- buf, nbytes
 *   OUTPUTS: none
 *   RETURN VALUE: 0 if successfully closed, -1 otherwise
 *   SIDE EFFECTS: none
 */
int32_t sys_getargs(unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4)
{
	uint8_t * buf = (uint8_t*)p2;
	int32_t nbytes = (int32_t)p3;
	
	//check if buf is invalid
	if (buf == NULL)
	{
		return -1;
	}
	//err check condition to avoid args being longer than bytes asked to be copied
 	if (((strlen((const int8_t*)args))+1) > nbytes) 
 		return -1;
	int i;
	//traverse till its empty
	for(i = 0; i < nbytes; i++)
		buf[i] = '\0';
	//extract the arguments
	for(i = 0; args[i] != '\0'; i++)
		buf[i] = args[i];
	return 0;
}

/* 
 * sys_vidmap
 *   DESCRIPTION: checks the validity of the pointer passed as a parameter by the user program, calls videmap paging to change it
 *   INPUTS: none
 *   OUTPUTS: changes pointer value, pointer pass by pointer/reference
 *   RETURN VALUE: none
 *   SIDE EFFECTS: changes paging, allows a program to change terminal video mem
*/
int32_t sys_vidmap(unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4)
{
	//Set vidmpa pointers
	uint8_t ** vidmap_pointer = (uint8_t**)p2;
	//Check if pointer is null or invalid
	if(vidmap_pointer == NULL || vidmap_pointer == (uint8_t**)VIDMAP_INVALID)
		return -1;
	//set vidmap paging
	videmap_paging(vidmap_pointer);
	return 0;
}

/* 
 * set_handler
 *   DESCRIPTION: Does nothing.
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: 0
 *   SIDE EFFECTS: none
 */
int32_t set_handler()
{
	return 0;
}

/* 
 * sys_sigreturn
 *   DESCRIPTION: Does nothing.
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: 0
 *   SIDE EFFECTS: none
 */
int32_t sys_sigreturn()
{
	return 0;
}




