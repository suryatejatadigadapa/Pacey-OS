#include "i8259.h"
#include "lib.h"

/* Interrupt masks to determine which interrupts are enabled and disabled */
uint8_t master_mask; /* IRQs 0-7 */
uint8_t slave_mask; /* IRQs 8-15 */

/* 
 * i8259_init
 *   DESCRIPTION: Initialize the 8259 PIC 
 *   INPUTS: none
 *   OUTPUTS: Initializes the PIC
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void i8259_init(void)
{
	//save masks
	master_mask = MASK;
	slave_mask = MASK;
	outb(master_mask, MASTER_8259_DATA); 
	outb(slave_mask,SLAVE_8259_DATA);
	 
	//tell both PICS they have to inp
	outb( ICW1,MASTER_8259_PORT); 	
	outb( ICW1,SLAVE_8259_PORT); 
	
	//send remaining wrds
	outb(ICW2_MASTER,MASTER_8259_DATA); 		
	outb(ICW2_SLAVE,SLAVE_8259_DATA); 	
	outb(ICW3_MASTER,MASTER_8259_DATA); 		
	outb(ICW3_SLAVE,SLAVE_8259_DATA); 	
	outb(ICW4,MASTER_8259_DATA); 	
	outb(ICW4,SLAVE_8259_DATA); 	
	outb(master_mask, MASTER_8259_DATA); 
	outb(slave_mask,SLAVE_8259_DATA); 	
}

/* 
 * enable_irq
 *   DESCRIPTION: Enable (unmask) the specified IRQ 
 *   INPUTS: Irq_num - IRQ Number
 *   OUTPUTS: Unmask given IRQ
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void enable_irq(uint32_t irq_num)
{
	//unsigned char output_mask;
	if(irq_num < DEC_8)
	{
		//output the mask
		master_mask = master_mask & (~(1<<irq_num));
		outb(master_mask,MASTER_8259_DATA);
	}
	else 
	{
		//Set master mask
		master_mask = master_mask & (~(1<<DEC_2));
		outb(master_mask,MASTER_8259_DATA);
		//if slave, subtract 8 from irq num for the PIC to know what you're talking about
		slave_mask = slave_mask & (~(1<<(irq_num-DEC_8) ));
		//output the mask
		outb(slave_mask,SLAVE_8259_DATA);
	}	
}

/* 
 * disable_irq
 *   DESCRIPTION: Disable(mask) the specified IRQ 
 *   INPUTS: Irq_num - IRQ Number
 *   OUTPUTS: Mask given IRQ
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void disable_irq(uint32_t irq_num)
{
	unsigned char output_mask;
	if(irq_num < DEC_8)
	{
		///output the mask
		output_mask = master_mask | (1<<irq_num);
		outb( output_mask,MASTER_8259_PORT);
	}
	else 
	{
		//if slave, subtract 8 from irq num for the PIC to know what you're talking about	
		output_mask = slave_mask & (1<< (irq_num-DEC_8) );	
		//output the mask
		outb( output_mask,SLAVE_8259_PORT);		
	}
}

/* 
 * send_eoi
 *   DESCRIPTION: Send end-of-interrupt signal for the specified IRQ 
 *   INPUTS: Irq_num - IRQ Number
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void send_eoi(uint32_t irq_num)
{
	//Master
	if(irq_num < DEC_8)
	{	
		//bitmask, zero's all bits higher than bit 3
		outb( EOI+irq_num,MASTER_8259_PORT);
		
	}
	//Slave
	else
	{
		//bitmask, zero's all bits higher than bit 3
		outb( EOI+(irq_num&DEC_7) ,SLAVE_8259_PORT);
		//2 is irq number on master that the slaves connects to 	
		outb( EOI+DEC_2,MASTER_8259_PORT);	
	}
}

/* Referenced from OSDev and Linux Source for PIC */




