#ifndef RTC_DRIVER_H
#define RTC_DRIVER_H

#include "initial.h"
#include "types.h"
#include "lib.h"
#include "descriptor.h"
#include "terminal_driver.h"

#define MAX_ARR_TERM_VAL 4

volatile int rtc_flag[MAX_ARR_TERM_VAL];
volatile int tick[MAX_ARR_TERM_VAL];

int32_t read_rtc(int32_t fd, void* buf, int32_t nbytes);
int32_t write_rtc(int32_t fd, const void* buf, int32_t rate);
int32_t close_rtc(int32_t fd);
int32_t open_rtc(const uint8_t* filename);

#endif /*RTC_DRIVER_H */


