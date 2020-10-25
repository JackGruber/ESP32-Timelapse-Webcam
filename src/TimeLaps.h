#pragma once
#ifndef _TIMELAPS_H
#define _TIMELAPS_H

extern unsigned long DEFAULT_INTERVAL;

void TimeLapsSetInterval(unsigned long delta);
bool TimeLapsStart();
bool TimeLapsStop();
bool TimeLapsProcess();

#endif
