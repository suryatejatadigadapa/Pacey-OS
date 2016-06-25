#ifndef FILE_FUNC_H
#define FILE_FUNC_H

#include "lib.h"
#include "multiboot.h"
#include "descriptor.h"
#include "system_calls.h"

/*Macros*/
#define four_kb 4096
#define one_kb 1024
#define MAX_FNAME 32

fd_array_t file_arr_file;
fd_array_t file_arr_dir;

uint32_t base_file_addr;

uint32_t read_dentry_by_name (const uint8_t* fname, dentry_t* dentry);
uint32_t read_dentry_by_index (uint32_t index, dentry_t* dentry);
uint32_t read_data (uint32_t inode, uint32_t offset, uint8_t* buf, uint32_t length);

uint32_t file_length (uint32_t inode);

int32_t file_open (const uint8_t* filename); 
int32_t file_read (int32_t fd, void* buf, int32_t nbytes);
int32_t file_write (int32_t fd, const void* buf, int32_t nbytes);
int32_t file_close (int32_t fd);

int32_t dir_open (const uint8_t* filename);
int32_t dir_read (int32_t fd, void* buf, int32_t nbytes); 
int32_t dir_write (int32_t fd, const void* buf, int32_t nbytes);
int32_t dir_close (int32_t fd);

#endif /* FILE_FUNC_H */


