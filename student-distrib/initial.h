#ifndef INITIAL_H
#define INITIAL_H

/*Macros*/
#define INDEX_PORT 0x70
#define DATA_PORT 0x71
#define REG_8B 	0x8B
#define MASK_B 0x40

void keyboard_init();
void rtc_initialize();
void pit_initialize();

#endif /* INITIAL_H */


