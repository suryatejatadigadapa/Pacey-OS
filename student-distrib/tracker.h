#ifndef _TRACKER_H
#define _TRACKER_H

#include "multiboot.h"
#include "x86_desc.h"
#include "lib.h"
#include "i8259.h"
#include "debug.h"
#include "exceptions.h"
#include "initial.h"
#include "paging.h"
#include "idt.h"
#include "file_func.h"
#include "rtc_driver.h"
#include "system_calls.h"

void tracker_init();

#endif /* _TRACKER_H */


