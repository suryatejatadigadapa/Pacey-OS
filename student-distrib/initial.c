#include "initial.h"
#include "i8259.h"

/* 
 * keyboard_init
 *   DESCRIPTION: Configure the keyboard by enabling IRQ(1)
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void keyboard_init()
{
	enable_irq(1); //enabling irq with 1 to enable keyboard
}

/* 
 * rtc_initialize
 *   DESCRIPTION: Configure the RTC by enabling IRQ(2) and IRQ(8)
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void rtc_initialize()
{
	cli();
	enable_irq(2); //enabling irq with 2 to enable rtc
	enable_irq(DEC_8); //enabling irq with 8
	outb(REG_8B,INDEX_PORT); //Select register B and diable NMI
	unsigned char c =inb(DATA_PORT); //read fom data port
	outb(REG_8B,INDEX_PORT);   //reset it again , because the register gets set to d after read
	outb(MASK_B|c, DATA_PORT); 
	sti();
}

/* 
 * pit_initialize
 *   DESCRIPTION: Configure the PIT by enabling IRQ(0)
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void pit_initialize()
{
	enable_irq(0); //enable irq with 0 to enable pit
}

/*Referenced from OSDev and Linux Source for RTC*/




