#ifndef PAGING_H
#define PAGING_H

#include "lib.h"
#include "file_func.h"
#include "system_calls.h"

/*Macros*/
#define MAX_PROCESSES 6
#define ALIGN_4KB 	4096
#define VAL_4KB 	4096
#define VAL_4MB 0x400000
#define ENTRY_NUMBER1 	1024
#define LENGTH 4
#define LARGE_PAGE 0x8000e7
#define FOUR_MB 0x400000
#define PDE_IDX_128MB 32
#define PROG_BASE_LOAD 0x8048000
#define ONE_BYTE 8 
#define TWO_BYTE 16
#define THREE_BYTE 24
#define PAGING_OR 0x107
#define UPT_START 0xB8000
#define VID_PAGING 0xC800000
#define VIDMEM_BASE_ADDR 0xB8000
#define TERM_1_PAGE 0xB9000
#define TERM_2_PAGE 0xBA000
#define TERM_3_PAGE 0xBB000
#define TERM_1_PT_IDX 185
#define TERM_2_PT_IDX 186
#define TERM_3_PT_IDX 187
#define PDE_INIT	0x00000002
#define KERNEL_4MB 	0x400087
#define KB_4		0x1000
#define PTE_BITS 	0x87
#define VIDEO_BUF  184
#define DEC_1		1
#define DEC_2		2
#define DEC_3		3
#define PAE_BITS 	0x90
#define SHIFT_BITS 	31

unsigned int num_processes;
unsigned int cur_process;
uint8_t block_in_use[MAX_PROCESSES];

void page_init();
uint32_t user_paging(const unsigned char * str, int new_proc_id);
void videmap_paging(uint8_t ** p2);
void halt_paging_helper(int parent_id);
void change_terminal(int cur_term, int switch_term);
void context_switch_paging_helper(int proc_id);
int lowest_available_block_idx();

#endif /* PAGING_H */


