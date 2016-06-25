#ifndef _DESCRIPTOR_H
#define _DESCRIPTOR_H

#include "types.h"

#define FD_SLOTS 8

//FD ARRAY
typedef struct fd_array
{
	int32_t (*open)(const uint8_t* filename);
	int32_t (*read)(int32_t fd, void* buf, int32_t nbytes);
	int32_t (*write)(int32_t fd, const void* buf, int32_t nbytes);
	int32_t (*close)(int32_t fd);
} fd_array_t;

//FILE DESCRIPTOR
typedef struct file_descriptor_content
{
	fd_array_t* file_operations_table_pointer;
	uint32_t inode;
	uint32_t file_position;
	uint32_t flags;
} file_descriptor_content_t;

//FILE DESCRIPTOR
typedef struct file_descriptor
{
	file_descriptor_content_t fd[FD_SLOTS];

} file_descriptor_t;

//PCB
typedef struct pcb
{	
	uint32_t esp;
	uint32_t ebp;
	int32_t parent_id;
	file_descriptor_t file;

} pcb_t;

#endif /* _DESCRIPTOR_H */


