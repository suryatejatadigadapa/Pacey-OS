#include "mouse.h"
#include "i8259.h"
#include "lib.h"

#define BLACK_GRAY 0x07
#define GRAY_BLACK 0x70    
#define NUM_PACKETS 3
#define KBD_PORT 0x60
#define READ_PORT 0x64
#define EN_AUX_DEVICE 0xA8
#define STATUS_BYTE 0x20
#define D4_BYTE 0xD4
#define EN_PACKETS 0xF4
#define KBD_BYTE 0x47
#define X_SCALE 6
#define Y_SCALE 12

#define VIDEO_NUM_ROWS 25
#define VIDEO_NUM_COLS 80
#define MAX_X 256
#define MAX_Y 256

static uint8_t mouse_cycle = 1; // counter to cycle through different packets     
volatile uint8_t mouse_uint8_t[NUM_PACKETS]; // mouse packets
// initialize mouse cursor to start in top left corner
static int32_t mouse_x = 0;        
static int32_t mouse_y = 0;         

/* 
 * mouse handler
 *   DESCRIPTION: Mouse handler that updates cursor position by reading in
 *				  the mouse packets 
 *   INPUTS: none
 *   OUTPUTS: (mouse_x, mouse_y) -- mouse cursor position
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void mouse_handler() 
{	
	uint8_t x_sign; // sign of x movement
	uint8_t y_sign; // sign of y movement
	uint32_t dx; // x movement
	uint32_t dy; // y movement
	
	switch(mouse_cycle)
	{
		case 0: // x movement packet
			mouse_uint8_t[0] = inb(KBD_PORT);
			mouse_cycle++;
			break;
			
		case 1: // y movement packet
			mouse_uint8_t[1] = inb(KBD_PORT);
			mouse_cycle++;
			break;
			
		case 2:
			// get x_sign and y_sign
			x_sign = (mouse_uint8_t[2] >> 4) & 0x01;
			y_sign = (mouse_uint8_t[2] >> 5) & 0x01;
			mouse_uint8_t[2] = inb(KBD_PORT);
			
			// ensure cursor doesn't leave behind "trail"
			print_mouse(mouse_x/X_SCALE, mouse_y/Y_SCALE, BLACK_GRAY);

			dx = mouse_uint8_t[0]; // x movement
			dy = mouse_uint8_t[1]; // y movement
			//printf("dx = %x, dy = %x\n", dx, dy);
			
			if (x_sign == 1) // negative x movement
				dx = -1*(MAX_X - dx);
			if (y_sign == 1) // negative y movement
				dy = -1*(MAX_Y - dy);
			
			// update cursor coordinates
			mouse_x = mouse_x + dx;
			mouse_y = mouse_y - dy;
			
			// ensure cursor stays within bounds of terminal window
			if (mouse_x < 0)
				mouse_x = 0;
			else if (mouse_x >= VIDEO_NUM_COLS * X_SCALE)
				mouse_x = VIDEO_NUM_COLS * X_SCALE - 1;
			if (mouse_y < 0)
				mouse_y = 0;
			else if (mouse_y >= VIDEO_NUM_ROWS * Y_SCALE)
				mouse_y = VIDEO_NUM_ROWS * Y_SCALE - 1;
		
			//printf("mouse x = %d, mouse y = %d\n", mouse_x, mouse_y);
			mouse_cycle=0;
			break;
	}
	print_mouse (mouse_x/X_SCALE, mouse_y/Y_SCALE, GRAY_BLACK); 
	send_eoi(12);
}

/* 
 * mouse_install
 *   DESCRIPTION: Initializes the mouse by enabling packets and 
 *				  the handler 
 *   INPUTS: None
 *   OUTPUTS: Writes to keyboard port (0x60) and read port (0x64)
 *   RETURN VALUE: none
 *   SIDE EFFECTS: Enables mouse packets
 */
void mouse_install()
{
	uint8_t _status;  
	outb(EN_AUX_DEVICE, READ_PORT); // send Enable Auxiliary Device command
	
	outb(STATUS_BYTE, READ_PORT); // get Compaq status byte
	_status = (inb(KBD_PORT) | 2);
	
	outb(KBD_PORT, READ_PORT); // set Compaq status
	outb(_status, KBD_PORT); // send modified status byte
	
	outb(KBD_BYTE, KBD_PORT); 
	outb(D4_BYTE, READ_PORT);
	outb(EN_PACKETS, KBD_PORT); // enable packets
	
	enable_irq(12); // set up the mouse handler
}

// Referenced code from http://forum.osdev.org/viewtopic.php?t=10247

