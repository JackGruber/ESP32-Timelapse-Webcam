#pragma once
#ifndef _SD_H
#define _SD_H
#include "Arduino.h"

bool SDWriteFile(const char *path, const unsigned char *data, unsigned long len);
bool SDAppendFile(const char *path, const unsigned char *data, unsigned long len);
bool SDInitFileSystem();
bool SDCreateDir(const char *path);
bool SDFileExists(const char *path);

#endif
