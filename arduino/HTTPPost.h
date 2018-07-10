#ifndef _HTTPPost_h
#define _HTTPPost_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

void http_init();

bool http_post(char * domainBuffer, int remoteport, char * page, const String & data);

#endif
