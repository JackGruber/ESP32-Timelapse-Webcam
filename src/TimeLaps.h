#pragma once
#ifndef _TIMELAPS_H
#define _TIMELAPS_H

void TimeLapsSetInterval(unsigned long delta);
bool TimeLapsStart();
bool TimeLapsStop();
bool TimeLapsProcess(unsigned long dt);

#endif
