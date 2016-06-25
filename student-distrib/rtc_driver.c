#include "rtc_driver.h"

#define INDEXP 0x70
#define DATAP 0x71
#define freq 32768
#define REG_8A 	0x8A
#define HIGH_FREQ 1024
#define MASK_BIT 0xF0

/* 
 * isPowerofTwo
 *   DESCRIPTION: Checks if the parameter (rate) passed is a power of two.
 *   INPUTS: fd -- none
 *			 buf -- rate - frequency
 *			 nbytes -- none
 *   OUTPUTS:none
 *   RETURN VALUE: 0
 *   SIDE EFFECTS: none
 */
int isPowerofTwo(unsigned int x)
{
	//Check if x is a power of 2
	return ((x != 0) && !(x & (x - 1)));
}

/* 
 * read_rtc
 *   DESCRIPTION: Waits for an interupt to be generated and reads it.
 *   INPUTS: fd -- none
 *			 buf -- rate - frequency
 *			 nbytes -- none
 *   OUTPUTS:none
 *   RETURN VALUE: 0
 *   SIDE EFFECTS: none
 */
int32_t read_rtc(int32_t fd, void* buf, int32_t nbytes)
{
	//waits for the rtc interrupt to occur
	//Set a temp int to tick and spin in a while loop till an interrupt is generated
	//Use terminal_num to update flags of every terminal
	int temp = tick[terminal_num];
	while(temp == tick[terminal_num]);
	//Set rtc flag to 1 and return 0 successfully
	rtc_flag[terminal_num]=1;
	return 0;
}

/* 
 * write_rtc
 *   DESCRIPTION: Sets the desired RTC frequency rate.
 *   INPUTS: fd -- none
 *			 buf -- rate - frequency
 *			 nbytes -- none
 *   OUTPUTS: Writes to the register A of RTC
 *   RETURN VALUE: 0 on success, -1 on failure
 *   SIDE EFFECTS: none
 */
int32_t write_rtc(int32_t fd, const void* buf, int32_t nbytes)
{
	uint32_t rate= *(uint32_t *)buf;
	//Error and Parameter Checking
	if(isPowerofTwo(rate)==0 || rate==1 || nbytes!=4)//4 because it should be 4 bytes always
	{
		return -1;
	}
	//Check if rate > max user prog allowed rate
	if(rate > HIGH_FREQ)
	{
		return -1;
	}

	int regb;

	//switch cases for setting the rtc frequency
	switch(rate)
	{
		case 2:
			regb = 0x0F; //setting the freq to 2Hz
			break;
		case 4:
			regb = 0x0E;//setting the freq to 4Hz
			break;
		case 8:
			regb = 0x0D;//setting the freq to 8Hz
			break;
		case 16:
			regb = 0x0C;//setting the freq to 16 Hz
			break;
		case 32:
			regb = 0x0B;//setting the freq to 32 Hz
			break;
		case 64:
			regb = 0x0A;//setting the freq to 64 Hz
			break;
		case 128:
			regb = 0x09;//setting the freq to 128 Hz
			break;
		case 256:
			regb = 0x08;//setting the freq to 256 Hz
			break;
		case 512:
			regb = 0x07;//setting the freq to 512 Hz
			break;
		default :
			regb = 0x06;//setting the freq to 1024 and above Hz
			break;
	}
	//printf("final rate: %x\n", regb);
	cli();
	outb(REG_8A,INDEXP); //Select register B and diable NMI
	unsigned char c =inb(DATAP); //read fom data port
	outb(REG_8A,INDEXP);   //reset it again , because the register gets set to d after read
	outb((c&MASK_BIT)|regb, DATAP);//setting the frequency 
	sti();
	return 0;
}

/* 
 * close_rtc
 *   DESCRIPTION: Does nothing. Return 0.
 *   INPUTS: fd -- directory index
 *   OUTPUTS: none
 *   RETURN VALUE: 0
 *   SIDE EFFECTS: none
 */
int32_t close_rtc(int32_t fd)
{
	//return successfully
	return 0;
}

/* 
 * open_rtc
 *   DESCRIPTION: initializes rtc and sets the default value to 2Hz.
 *   INPUTS: name -- name of directory we want to check for existence
 *   OUTPUTS: Writes to Reg A 
 *   RETURN VALUE: 0 on success
 *   SIDE EFFECTS: none
 */
int32_t open_rtc(const uint8_t* filename)
{
	rtc_initialize(); //enabling RTC
	cli(); //clear interrupts
	outb(REG_8A,INDEXP); //Select register B and diable NMI
	unsigned char c =inb(DATAP); //read fom data port
	outb(REG_8A,INDEXP);   //reset it again , because the register gets set to d after read
	outb(0x0F|c, DATAP);//setting the frequency to 2Hz. 0x0F = 2.
	sti(); //set interrupts
	return 0;//return successfully
}




