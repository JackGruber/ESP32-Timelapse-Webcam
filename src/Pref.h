#pragma once
#ifndef _NVS_H
#define _NVS_H

void PrefInit(void);
int PrefLoadInt(const char * preferences, int default_value, bool initpref);
void PrefSaveInt(const char * preferences, int value, bool initpref);
void PrefEnd(void);
void PrefClear(void);

#endif
