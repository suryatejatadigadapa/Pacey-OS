#include "file_func.h"

int32_t dirIndex = 0; // global variable that keeps track of directory index for reading the directory

/* 
 * read_dentry_by_name
 *   DESCRIPTION: Identifies the file by name, then fills in the dentry 
 *				  block with the corresponding file type and inode number. 
 *   INPUTS: fname -- name of file we want to find
 *			 dentry -- block whose entries we want to fill
 *   OUTPUTS: Writes to dentry block
 *   RETURN VALUE: 0 on success, -1 on failure
 *   SIDE EFFECTS: none
 */
uint32_t read_dentry_by_name (const uint8_t* fname, dentry_t* dentry)
{
	//Iterator.
	int i;
	//Initialize boot_block to the base address of the boot block.
	file_boot_struct_t* boot_block = (file_boot_struct_t*)base_file_addr; 
	//Look for a matching file name by iterating through all the directory entries.
	for (i = 0; i < boot_block->num_dir_entries; i++) 
	{
		uint32_t length=strlen((const int8_t*)fname);
		//Checking for the matching file name.
		if (strncmp((const int8_t*)fname, (const int8_t*)(boot_block->diren[i]).filename, length)==0)
		{
			uint32_t length1 = strlen((const int8_t*)boot_block->diren[i].filename);
			if (length1 == length)
			{
				//If matching file found, fill in the dentry.
				dentry->filetype = (boot_block->diren[i]).filetype;
				dentry->inode_index = (boot_block->diren[i]).inode_index;		
				//Return successfully.
				return 0;
			}
		}		
	}
	//Return unsuccessfully. Invalid index or nonexistent file.
	return -1;
}

/* 
 * read_dentry_by_index
 *   DESCRIPTION: Identifies the file by index, then fills in the dentry 
 *				  block with the corresponding file name, file type, and
 *				  inode number. 
 *   INPUTS: index -- directory index
 *			 dentry -- block whose entries we want to fill
 *   OUTPUTS: Writes to dentry block
 *   RETURN VALUE: 0 on success, -1 on failure
 *   SIDE EFFECTS: none
 */
uint32_t read_dentry_by_index (uint32_t index, dentry_t* dentry)
{
	//Initialize boot_block to the base address of the boot block.
	file_boot_struct_t* boot_block = (file_boot_struct_t*)base_file_addr;
	//If the index is invalid return unsuccessfully
	if (index < 0 || index >= boot_block->num_dir_entries)
		return -1;
	//Else fill in the dentry block with the gathered data
	else
	{
		strcpy((int8_t*)dentry->filename,(int8_t*)boot_block->diren[index].filename);
		dentry->filetype = (boot_block->diren[index]).filetype;
		dentry->inode_index = (boot_block->diren[index]).inode_index;
		return 0;
	}
}

/* 
 * read_data
 *   DESCRIPTION: Reads up to a certain number of bytes from a certain position in
 *				  a file, and writes these bytes to a buffer. 
 *   INPUTS: inode -- inode of file we want to read from
 *			 offset -- position in file to start reading from
 *			 buf -- buffer to write bytes to
 *			 length -- number of bytes to read up to
 *   OUTPUTS: Writes to a buffer
 *   RETURN VALUE: Number of bytes written to buffer on success, -1 on failure
 *   SIDE EFFECTS: none
 */
uint32_t read_data (uint32_t inode, uint32_t offset, uint8_t* buf, uint32_t length)
{
	//Initialize boot_block to the base address of the boot block.
	file_boot_struct_t* boot_block = (file_boot_struct_t*)base_file_addr;
	//Parameter Check & Error Check
	if ( inode<0 || inode>(boot_block->num_inodes-1) || offset<0 || length<1 || buf == NULL)
	{
		return -1;
	}
	//Find the starting address of the datablocks & correct inode address
	uint32_t* data_block_base_addr = (uint32_t*)(boot_block + 1 + boot_block->num_inodes); //(+1 is to add bootblock size)
	uint32_t* correct_inode_address = (uint32_t*)(boot_block + 1 + inode); //(+1 is to add bootblock size)
	//Check that length and offset is not more than the file length itself. If so change number of bytes to copy.
	int bytes = length;
	if ((offset + length) > *correct_inode_address)
	{
		bytes = ((*correct_inode_address) - offset);
		//If bytes is 0 or negative (hence < 1)
		if (bytes<0)
		{
			return -1;
		}
	}
	//Find the starting data block number & the data block address in the correct inode
	int data_block_number = offset/four_kb;
	uint32_t* data_block_address = (uint32_t*)(correct_inode_address + 1 + data_block_number); //(+1 is to add 4 bytes for file size)
	//Find data block index and current byte andd remaining bytes in the datablock
	int data_block_index = (int)*data_block_address;
	uint8_t* current_byte = (uint8_t*)(data_block_base_addr + (data_block_index*one_kb));
	current_byte = current_byte + (offset%four_kb);
	int bytes_remaining = four_kb - (offset-(data_block_number*four_kb));

	// Traverse the whole data block copying all the bytes into the buffer
	int i=0;
	for(i=0;i<bytes;i++)
	{	
		//If bytes remaining is 0 then update datablocks and other variables
		if (bytes_remaining == 0)
		{
			data_block_number++;
			data_block_address = correct_inode_address + 1 + data_block_number;
			data_block_index=(int) *data_block_address;
			current_byte = (uint8_t*)(data_block_base_addr + data_block_index*one_kb);
			bytes_remaining = four_kb;
		}	
		//Copying the bytes into the buffer and incrementing / decrementing the current byte and bytes remaining
		buf[i]= *current_byte;
		current_byte++;
		bytes_remaining--;
	}
	//return the number of bytes copied 
	return i;
}

/* 
 * file_length
 *   DESCRIPTION: Reads lenthg of a file in number of bytes.
 *   INPUTS: inode -- inode of file we want to read from
 *   OUTPUTS: none
 *   RETURN VALUE: Lenth of a file in bytes on success, -1 on failure
 *   SIDE EFFECTS: none
 */
uint32_t file_length (uint32_t inode)
{
	//Initialize boot_block to the base address of the boot block.
	file_boot_struct_t* boot_block = (file_boot_struct_t*)base_file_addr;
	//Parameter Check & Error Check
	if ( inode<0 || inode>(boot_block->num_inodes-1))
	{
		//Return unsuccessfully
		return -1;
	}
	//Get to the correct inode address. The +1 is to add the bootblock size.
	uint32_t* correct_inode_address = (uint32_t*)(boot_block + 1 + inode); 
	return *correct_inode_address;
} 

/* 
 * file_open 
 *   DESCRIPTION: Determines if the file exists
 *   INPUTS: filename -- name of file we want to use
 *   OUTPUTS: none
 *   RETURN VALUE: 0 if it exists, -1 on failure
 *   SIDE EFFECTS: none
 */ 
int32_t file_open (const uint8_t* filename)
{
	// initialize dentry block
	dentry_t dentry; 
	uint32_t fname_check = read_dentry_by_name(filename, &dentry);
	// file name is valid
	if (fname_check == 0) 
		return 0;
	else // file name is invalid
		return -1;
}

/* 
 * file_read 
 *   DESCRIPTION: Reads up to a certain number of bytes from a certain position in
 *				  a file, and writes these bytes to a buffer. For CP2, use fd as the 
 *				  directory index. Offset (i.e. position in file to start reading
 *				  from) is set to 0 unless you change the parameter when calling read_data. 
 *   INPUTS: fd -- directory index
 *			 buf -- buffer to write bytes to
 *			 nbytes -- number of bytes to read up to
 *   OUTPUTS: Writes file contents to a buffer
 *   RETURN VALUE: Number of bytes written to buffer if fd is valid, -1 otherwise
 *   SIDE EFFECTS: none
 */
int32_t file_read (int32_t fd, void* buf, int32_t nbytes)
{
	int32_t buf_bytes; // number of bytes that get written to buffer
	uint32_t inode_num = pcb_template_array[cur_process].file.fd[fd].inode;
	uint32_t filepos = pcb_template_array[cur_process].file.fd[fd].file_position;
	buf_bytes = read_data(inode_num, filepos, buf, nbytes); // read data from file
	pcb_template_array[cur_process].file.fd[fd].file_position += buf_bytes; // update file_position
	return buf_bytes;
}

/* 
 * file_write
 *   DESCRIPTION: Does nothing. File system is read-only, so return -1
 *   INPUTS: fd -- directory index
 *			 buf -- buffer to write bytes to
 *			 nbytes -- number of bytes to read up to
 *   OUTPUTS: none
 *   RETURN VALUE: -1
 *   SIDE EFFECTS: none
 */
int32_t file_write (int32_t fd, const void* buf, int32_t nbytes) {
	return -1;
}

/* 
 * file_close
 *   DESCRIPTION: Does nothing. Return 0.
 *   INPUTS: fd -- directory index
 *   OUTPUTS: none
 *   RETURN VALUE: 0
 *   SIDE EFFECTS: none
 */
int32_t file_close (int32_t fd) {
	return 0;
}

/* 
 * dir_open
 *   DESCRIPTION: Checks if the specified directory exists. Sets the global
 *				  variable dirIndex back to 0 if it does.
 *   INPUTS: name -- name of directory we want to check for existence
 *   OUTPUTS: resets dirIndex to 0
 *   RETURN VALUE: 0 on success, -1 on failure
 *   SIDE EFFECTS: none
 */
int32_t dir_open (const uint8_t* filename)
{
	//dirIndex = 0;
	uint32_t length = strlen((const int8_t*)filename);
	//If succesful return 0
	if (strncmp((const int8_t*)".", (const int8_t*)filename, length)==0) {
		return 0;
	}
	//Else return unsuccessfully
	else 
		return -1;
}

/* 
 * dir_read 
 *   DESCRIPTION: Writes up to a certain number of bytes of the (fd)th file name into 
 *				  a buffer. Note that the 0th file name is "." 
 *   INPUTS: fd -- does nothing, just serves as a placeholder for CP3
 *			 buf -- buffer to write bytes to
 *			 nbytes -- number of bytes of the file name to read up to
 *   OUTPUTS: Writes file name to a buffer
 *   RETURN VALUE: -1 if fd is out of bounds; number of bytes written to the buffer otherwise
 *   SIDE EFFECTS: none
 */ 
int32_t dir_read (int32_t fd, void* buf, int32_t nbytes)
{
	uint32_t buf_length;
	dentry_t dentry;
	unsigned char* temp_fname;
	uint8_t* temp_buf = (uint8_t*)buf;
	int i; // iterator
	uint32_t filepos = pcb_template_array[cur_process].file.fd[fd].file_position; // directory index
	int32_t fd_check = read_dentry_by_index(filepos, &dentry);
	
	if (fd_check != 0 || nbytes < 1) // invalid directory index 
		return -1;

	// Get address of bootblock and file address
	file_boot_struct_t* boot_block=(file_boot_struct_t*)base_file_addr;
	dentry_t* file_addr = (dentry_t*)boot_block;
	file_addr += filepos; 
	dirIndex++;
	if(dirIndex >= (boot_block->num_dir_entries+1))
	{
		dirIndex = 0;
		return 0;
	}

	//get filename and filename length
	temp_fname = (&dentry)->filename;
	buf_length = strlen((const int8_t*)((&dentry)->filename));

	if (filepos < boot_block->num_dir_entries - 1)
		(pcb_template_array[cur_process].file.fd[fd].file_position)++; // increment directory index
	
	if (nbytes <= MAX_FNAME) { // user specified length <= 32
		for (i = 0; i < nbytes; i++) 
			temp_buf[i] = temp_fname[i]; // write nth file name into buffer
		if (nbytes < buf_length) 
			return nbytes;
		else 		
			return buf_length;
	}
	else { // user specified length > 32
		for (i = 0; i < buf_length; i++) 
			temp_buf[i] = temp_fname[i]; // write nth file name into buffer
		return buf_length;
	}
	return 0;
}

/* 
 * dir_write
 *   DESCRIPTION: Does nothing. File system is read-only, so return -1
 *   INPUTS: fd -- directory index
 *			 buf -- buffer to write bytes to
 *			 nbytes -- number of bytes to read up to
 *   OUTPUTS: none
 *   RETURN VALUE: -1
 *   SIDE EFFECTS: none
 */
int32_t dir_write (int32_t fd, const void* buf, int32_t nbytes) 
{
	return -1;
}

/* 
 * dir_close
 *   DESCRIPTION: Does nothing. Return 0.
 *   INPUTS: fd -- directory index
 *   OUTPUTS: none
 *   RETURN VALUE: 0
 *   SIDE EFFECTS: none
 */
int32_t dir_close (int32_t fd) 
{
	return 0;
}




