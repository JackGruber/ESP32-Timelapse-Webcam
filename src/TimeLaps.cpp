#include "Arduino.h"
#include "esp_camera.h"
#include <stdio.h>
#include "SD.h"
#include "Pref.h"
#include "settings.h"
#include "driver/rtc_io.h"

RTC_DATA_ATTR bool DEEPSLEEP_TIMELAPS;
RTC_DATA_ATTR unsigned int fileIndex = 0;
RTC_DATA_ATTR unsigned int lapseIndex = 0;
unsigned long DEFAULT_INTERVAL = 10;
unsigned short DEFAULT_DEEPSLEEP = 0;
bool mjpeg = true;
bool lapseRunning = false;
unsigned long nexttimelaps = 0;

bool TimeLapsStart()
{
    if(lapseRunning) return true;
    fileIndex = 0;
    char path[32];
    for(; lapseIndex < 10000; lapseIndex++)
    {
        sprintf(path, "/lapse%03u", lapseIndex);
        if (!SDFileExists(path))
        {
            SDCreateDir(path);
            lapseRunning = true;

            if(PrefLoadInt("deepsleep", DEFAULT_DEEPSLEEP, true) == 1) { DEEPSLEEP_TIMELAPS = true; }
            else { DEEPSLEEP_TIMELAPS = false; }
            return true;
        }
    }
	return false;
}

bool TimeLapsStop()
{
    lapseRunning = false;
    return true;
}

bool TimeLapsProcess()
{
    if(DEEPSLEEP_TIMELAPS != true)
    {
        if(!lapseRunning) return false;
        if(nexttimelaps >  millis() ) return false;
        nexttimelaps = millis() + (1000 * PrefLoadInt("interval", DEFAULT_INTERVAL, true));
    }

    camera_fb_t *fb = NULL;
    fb = esp_camera_fb_get();
    if (!fb)
    {
        Serial.println("Camera capture failed");
        return false;
    }

    char path[32];
    sprintf(path, "/lapse%03u/pic%05u.jpg", lapseIndex, fileIndex);
    Serial.println(path);
    if(!SDWriteFile(path, (const unsigned char *)fb->buf, fb->len))
    {
        lapseRunning = false;
        return false;
    }
    fileIndex++;
    esp_camera_fb_return(fb);

    if(DEEPSLEEP_TIMELAPS == true)
    {
        Serial.println("GoDeepSleep");
        Serial.flush();

        // disable flash
        pinMode(GPIO_NUM_4, OUTPUT);
        digitalWrite(GPIO_NUM_4, LOW);
        rtc_gpio_hold_en(GPIO_NUM_4); 

        gpio_deep_sleep_hold_en();
        esp_sleep_enable_timer_wakeup(PrefLoadInt("interval", DEFAULT_INTERVAL, true) * 1000000);
        esp_deep_sleep_start();
    }

    return true;
}
