#ifndef _I8259_H
#define _I8259_H

#include "types.h"
#include "lib.h"

/* Decimal value 8 for irq_num */
#define DEC_8	8
/* Ports that each PIC sits on */
#define MASTER_8259_PORT 0x20
#define SLAVE_8259_PORT  0xA0

/* Data Ports for the PICs */
#define MASTER_8259_DATA 0x21
#define SLAVE_8259_DATA 0xA1

/* Initialization control words to init each PIC.*/
#define ICW1		  0x11
#define ICW2_MASTER   0x20
#define ICW2_SLAVE    0x28
#define ICW3_MASTER   0x04
#define ICW3_SLAVE    0x02
#define ICW4          0x01
/* PIC Values */
#define MASK 	0xFF
#define DEC_2	2
#define DEC_7	7
/* End-of-interrupt byte.  This gets OR'd with the interrupt number and sent out to the PIC to declare the interrupt finished */
#define EOI             0x60

/* Initialize both PICs */
void i8259_init(void);
/* Enable (unmask) the specified IRQ */
void enable_irq(uint32_t irq_num);
/* Disable (mask) the specified IRQ */
void disable_irq(uint32_t irq_num);
/* Send end-of-interrupt signal for the specified IRQ */
void send_eoi(uint32_t irq_num);

#endif /* _I8259_H */


