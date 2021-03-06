#include "event.h"

unsigned int key_layout[13] = {1,2,3,4,5,6,7,8,9,10,0,11,21};

int lastKey;
static int time = 0;
static int waitBeforeKeyTime = 0;

void EVENT_Init(){
  KEYPAD_Init(key_layout);
}

int EVENT_GetIdleEvent(){
  TIME_Wait(400);
  int key = KEYPAD_Read();
  if(key == IDLE_CONFIG && time == 0)
    time = TIMER0_GetValue();
  if(key == IDLE_CONFIG){
    if(lastKey == IDLE_CONFIG && TIMER0_Elapse(time) > 2000){
      time = 0;
      return key;
    }
    else{
      lastKey = IDLE_CONFIG;
      return IDLE_NOTHING;
    }
  }
  lastKey = key;
  return key;
}

int EVENT_GetEvent(){
  int key;
  TIME_Wait(400);
  while((key = KEYPAD_Read()) == -1);
  return key;
}
