#include "event.h"
#include "rtc.h"

unsigned int event;

struct tm dateTime = {0,0,0,0,1,1,0,2017};

void configureClock(){
  int state = 0;
  int value;
  int i = 1;

  UI_ClearScreen();
  while(1){
    UI_DrawConfigClock(&dateTime, state);

    value = EVENT_GetEvent();
    if(value == CONFIG_DATETIME_NEXT){
      if(++state == 2)
        return;
      i = 1;
      continue;
    }

    switch(state){
      case 0:
        value = i == 1 ? value * 10 : dateTime.tm_hour + value;
        if(value > 24){
          value = 24;
          i = 1;
        }
        dateTime.tm_hour = value;
        if(--i < 0)
          i = 1;
        break;
      case 1:
        value = i == 1 ? value * 10 : dateTime.tm_min + value;
        if(value > 60){
          value = 60;
          i = 1;
        }
        dateTime.tm_min = value;
        if(--i < 0)
          i = 1;
        break;
      case 2:
        return;
    }
  }
}

unsigned int pow(int number, int exponent){
  if(exponent == 0)
    return 1;
  int mult = number;
  for(; exponent > 1; exponent--)
    number *= mult;
  return number;
}

void configureDate(){
  int state = 0;
  int value;
  int i = 3;

  UI_ClearScreen();
  while(1){
    UI_DrawConfigDate(&dateTime, state);

    value = EVENT_GetEvent();
    if(value == CONFIG_DATETIME_NEXT){
      if(++state == 3)
        return;
      i = 3;
      continue;
    }

    switch(state){
      case 0:
        value = (i % 2) == 1 ? value * (10 * (i % 2)) : dateTime.tm_mday + value;
        if(value > 31){
          value = 31;
          i = 3;
        }
        dateTime.tm_mday = value;
        if(--i < 2)
          i = 3;
        break;
      case 1:
        value = (i % 2) == 1 ? value * (10 * (i % 2)) : dateTime.tm_mon + value;
        if(value > 12){
          value = 12;
          i = 3;
        }
        dateTime.tm_mon = value;
        if(--i < 2)
          i = 3;
        break;
      case 2:
        value = i == 3 ? value * pow(10,i) : dateTime.tm_year + (value * pow(10,i));
        if(value > 9999){
          value = 9999;
          i = 3;
        }
        dateTime.tm_year = value;
        if(--i < 0)
          i = 3;
        break;
      case 4:
        return;
    }
  }
}

//struct Flash_Sector sector = FILLSECT(13);

void deleteResults(){
  UI_ClearScreen();
  UI_DrawConfigDeleteResults();
  event = EVENT_GetEvent();
  switch (event) {
    case CONFIG_GAME_RESULTS_DELETE:{
      STORAGE_ClearGameResults();
      break;
    }
    case CONFIG_GAME_RESULTS_EXIT:
      break;
  }
  UI_ClearScreen();
}

void CONFIG_StartConfiguration(){
  UI_ClearScreen();
  while(1){
    UI_DrawMainConfigScreen();
    event = EVENT_GetEvent();
    switch(event){
      case CONFIG_CLOCK:
        configureClock();
        UI_ClearScreen();
        break;
      case CONFIG_DATE:
        configureDate();
        UI_ClearScreen();
        break;
      case CONFIG_GAME_RESULTS:
        deleteResults();
        UI_ClearScreen();
        break;
      case CONFIG_EXIT:
        TIME_SetDateTime(&dateTime);
        UI_ClearScreen();
        return;
    }
  }
}
