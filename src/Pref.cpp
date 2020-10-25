#include "Arduino.h"
#include "Pref.h"
#include <Preferences.h>

Preferences pref;

void PrefInit(void)
{
    pref.begin("timelapsepref", false);
}

int PrefLoadInt(const char *preferences, int default_value, bool initpref)
{
    int value;
    if(initpref == true) { PrefInit(); }
    value = pref.getInt(preferences, default_value);
    if(initpref == true) { PrefEnd(); }
    return value;
}

void PrefSaveInt(const char *preferences, int value, bool initpref)
{
    if(initpref == true) { PrefInit(); }
    pref.putInt(preferences, value); 
    if(initpref == true) { PrefEnd(); }
}

void PrefEnd(void)
{
    pref.end();
}

void PrefClear(void)
{
    Serial.println("Clear Preferences ...");
    PrefInit();
    pref.clear();  
    PrefEnd();
}