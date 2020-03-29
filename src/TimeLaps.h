#pragma once
#ifndef _TIMELAPS_H
#define _TIMELAPS_H

extern unsigned long TIMELAPSINTERVAL;

void TimeLapsSetInterval(unsigned long delta);
bool TimeLapsStart();
bool TimeLapsStop();
bool TimeLapsProcess();

#endif
