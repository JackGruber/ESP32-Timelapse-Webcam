#pragma once
#ifndef _TIMELAPS_H
#define _TIMELAPS_H

extern RTC_DATA_ATTR bool DEEPSLEEP_TIMELAPS;
extern unsigned long DEFAULT_INTERVAL;
extern unsigned short DEFAULT_DEEPSLEEP;

void TimeLapsSetInterval(unsigned long delta);
bool TimeLapsStart();
bool TimeLapsStop();
bool TimeLapsProcess();

#endif
