#include "paging.h"

//page directory 
uint32_t pde[ENTRY_NUMBER1] __attribute__((aligned (ALIGN_4KB)));
//page table 
uint32_t pte[ENTRY_NUMBER1] __attribute__((aligned (ALIGN_4KB)));
//page table for fish
uint32_t uPT[ENTRY_NUMBER1] __attribute__((aligned (ALIGN_4KB)));

/* 
 * page_init
 *   DESCRIPTION: set the page directory and page table entries to map to physical memory (kernel space, video meory and buffers)
 *   INPUTS:NONE
 *   OUTPUTS:change the entries in page directory , page table and value for cr3, cr0,cr4
 *   RETURN VALUE: none
 *   SIDE EFFECTS: maps to physical address making it accesible to user
 */
void page_init()
{
	int iterator = 0;
	for (iterator = 0; iterator < ENTRY_NUMBER1; iterator++)
	{
		pde[iterator] = PDE_INIT; //write enabled in pde for all entries. (Hence 2)
		
	}
	for (iterator = 0; iterator < ENTRY_NUMBER1; iterator++)
	{
		pte[iterator] = (iterator * KB_4) | DEC_2; //supervisor level,read write,1000 is 4kb
	}
	pde[0] = ((unsigned int)pte) | DEC_3; //set the bits for present and r/w bit field
	unsigned int present,read_write;
	//setting the 4mb address in the page directory
	//setting the present, read_write and the page size bits and base address. 
	pde[1] = KERNEL_4MB;	
	//setting the page table entry for video memory
	present = 1; 	//setting 1 for present.
	read_write = DEC_2; //setting 2 in for read write.
	//actual video memory
	pte[VIDEO_BUF] |= PTE_BITS  ; 
	//buffer for teminal 1
	pte[VIDEO_BUF+1] |=PTE_BITS ;
	//buffer for teminal 2
	pte[VIDEO_BUF+DEC_2] |=PTE_BITS ;
	//buffer for teminal 2
	pte[VIDEO_BUF+DEC_3] |=PTE_BITS ;
	uint32_t cr4_val=0;
	asm volatile ( "mov %%cr4, %0" :"=r"(cr4_val) :  );	 
	cr4_val |= PAE_BITS; 							//setting the 7th and the 5th bit to 1 , PAE
	asm volatile ( "mov %0, %%cr4" : :"r"(cr4_val)  );	 
	uint32_t pde_addr;
	pde_addr=(unsigned int)pde ; 			
	asm volatile ( "mov %0, %%cr3" : : "r"(pde_addr) );	//put the pde base addr	
	//setting cr0 to 0.
	uint32_t cr0_value = 0;
	asm volatile ( "mov %%cr0, %0" :"=r"(cr0_value) :  );//enable page size extension
	cr0_value |= (1 << SHIFT_BITS) |1; 	//setting the 1st and the last bit to 1 to enable paging hence shift it by 31
	asm volatile ( "mov %0, %%cr0" : :"r"(cr0_value)  );	
}

/* 
 * user_paging
 *   DESCRIPTION: loads the program into physical memory and maps it
 *   INPUTS:str-filename , new_proc_id- pid of the process
 *   OUTPUTS: changes the tss and restores esp and ebp
 *   RETURN VALUE: eip of the program
 *   SIDE EFFECTS: change the pde entry
 */
uint32_t user_paging(const unsigned char * str, int new_proc_id)
{
	int32_t test_ret_val;
	dentry_t dentry_test;
	int length = LENGTH;
	int offset = 24; //offset into file to read eip (Where address is stored)
	uint8_t v_add_buf[length];
	test_ret_val = read_dentry_by_name (str, &dentry_test);		//err check for filename
	if(test_ret_val == -1)
		return -1;
	test_ret_val = read_data(dentry_test.inode_index,offset,v_add_buf,length);
	if(test_ret_val == -1)										//err check for read_data while reading the eip
		return -1;
	uint32_t v_add = 0;
	//getting the address by extracting bytes 24-27 stored in vaddbuff 0,1,2,3.
	v_add = v_add | (v_add_buf[DEC_3] << THREE_BYTE) | (v_add_buf[DEC_2] << TWO_BYTE) | (v_add_buf[DEC_1] << ONE_BYTE) | v_add_buf[0];	
	//get the file length
	uint32_t length_file = file_length(dentry_test.inode_index);
	//map the page directory entruy to the correct block
	pde[PDE_IDX_128MB] = LARGE_PAGE + FOUR_MB*(new_proc_id);
	//flush TLB
	asm volatile ("mov	%%cr3, %%eax" : :);
	asm volatile ("mov	%%eax, %%cr3" : :);
	offset = 0;
	//load it in userspace of 128 MB
	uint8_t * LD_address = (uint8_t *)PROG_BASE_LOAD;
	test_ret_val = read_data(dentry_test.inode_index, offset,  LD_address, length_file);
	if(test_ret_val == -1)
		return -1;
	//FLUSH TLB
	asm volatile ("mov	%%cr3, %%eax" : :);
	asm volatile ("mov	%%eax, %%cr3" : :);
	return v_add;
}

/* 
 * context_switch_paging_helper
 *   DESCRIPTION: changes the mapping to map to process that has been switched to
 *   INPUTS:proc-id- process id 
 *   OUTPUTS:none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: flushes tlb and changes pde
 */
void context_switch_paging_helper(int proc_id)
{
	//map it to correct program
	pde[PDE_IDX_128MB] = LARGE_PAGE + FOUR_MB*(proc_id);	
	//FLUSH TLB
	asm volatile ("mov	%%cr3, %%eax" : :);
	asm volatile ("mov	%%eax, %%cr3" : :);
	//FLUSH TLB
	asm volatile ("mov	%%cr3, %%eax" : :);
	asm volatile ("mov	%%eax, %%cr3" : :);

}	

/* 
 * halt_paging_helper
 *   DESCRIPTION: changes the mapping to map to parent process
 *   INPUTS:proc-id- process id 
 *   OUTPUTS:none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: flushes tlb and changes pde
 */
void halt_paging_helper(int parent_id)
{
	if(num_processes > 0)
	{
		block_in_use[cur_process] = 0; 							//free the block
		pde[PDE_IDX_128MB] =LARGE_PAGE + FOUR_MB*(parent_id);	//set it to correct program
		asm volatile ("mov	%%cr3, %%eax" : :);					//flush TLB
		asm volatile ("mov	%%eax, %%cr3" : :);
	}
}	

/* 
 * videmap_paging
 *   DESCRIPTION: 
 *   INPUTS:proc-id- p2
 *   OUTPUTS:none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: flushes tlb and changes pde
 */
void videmap_paging(uint8_t ** p2)
{
//	cli();
	pde[50] = ((unsigned int)uPT) | PAGING_OR;//50th entry in page descriptor
	//Flush TLB
	asm volatile ("mov	%%cr3, %%eax" : :);
	asm volatile ("mov	%%eax, %%cr3" : :);
	uPT[terminal_num] = (UPT_START + VAL_4KB*terminal_num) | PAGING_OR; //Filling page table for fish
	//Flush TLB
	asm volatile ("mov	%%cr3, %%eax" : :);
	asm volatile ("mov	%%eax, %%cr3" : :);
	*p2 = (uint8_t*)VID_PAGING + terminal_num*VAL_4KB; //Giving the address
//	sti();
}	

/* 
 * lowest_available_block_idx
 *   DESCRIPTION: finds the lowest avilable block 
 *   INPUTS:none
 *   OUTPUTS:none
 *   RETURN VALUE: returns the available block 
 *   SIDE EFFECTS: finds the available block
 */
int lowest_available_block_idx()
{
	int i;
	//find the lowest avialble block
	for(i = 0; i < MAX_PROCESSES; i++)
	{
		//return block number if the block is free
		if(block_in_use[i] == 0)
			return i;
	}
	return -1;
}




