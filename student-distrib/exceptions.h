#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "multiboot.h"
#include "x86_desc.h"
#include "lib.h"
#include "i8259.h"
#include "debug.h"
#include "idt.h"
#include "handler.h"

void create_exceptions();	

#endif /* EXCEPTIONS_H */


