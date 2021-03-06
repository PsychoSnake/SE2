#include "rtc.h"

static struct tm dateTime = {0,0,0,0,1,1,1,2017};

void TIME_Init(unsigned int timerFreq){
  TIMER0_Init(timerFreq);
  RTC_Init(&dateTime);
}

struct tm *TIME_GetDateTime(){
  RTC_GetValue(&dateTime);
  return &dateTime;
}

void TIME_SetDateTime(struct tm *setDate){
  RTC_SetValue(setDate);
}

void TIME_Wait(int waitTime){
  int time = TIMER0_GetValue();
  while(TIMER0_Elapse(time) < waitTime);
}
