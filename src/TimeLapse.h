#pragma once
#ifndef _TIMELAPSE_H
#define _TIMELAPSE_H

extern RTC_DATA_ATTR bool DEEPSLEEP_TIMELAPSE;
extern unsigned long DEFAULT_INTERVAL;
extern unsigned short DEFAULT_DEEPSLEEP;

void TimeLapseSetInterval(unsigned long delta);
bool TimeLapseStart();
bool TimeLapseStop();
bool TimeLapseProcess();

#endif
