#include <stdio.h>
//for the sake of simplicity, FUNCTION and ATTRIBUTES copied from  main.c with Adjustments

enum States{
  IDLE,
  ENT_TRIG,
  EXIT_TRIG,
  PENDING_ENT,
  PENDING_EXT,
  COUNT_UP,
  COUNT_DOWN,
  PENDING
};

enum Transition{
  noTrig,
  entTrig,
  exitTrig,
  bothTrig
};

//defining varibles for the Arduino
int count = 0;

enum States currentState;
enum States previousState;

int clearCycle = 500;
int pendingCycle = 200;

int DoorIn = 0;
int DoorOut = 0;


void occupancyMachine(enum States state, enum Transition transition){
  switch (state){

    case IDLE:
      printf("Current State: IDLE\n");
      previousState = ENT_TRIG;
      switch(transition){
        case noTrig:
          currentState = IDLE;
          break;
        case entTrig:
          previousState = IDLE;
          currentState = ENT_TRIG;
          break;
        case exitTrig:
          previousState = IDLE;
          currentState = EXIT_TRIG;
          break;
      }
    break;

    case PENDING:
      printf("Current State: PENDING\n");
      switch(transition){
        case noTrig:
          currentState = PENDING;
          if (pendingCycle == 0){
            currentState = IDLE;
            pendingCycle = 200;
          }
          pendingCycle--;
        break;

        case entTrig:
          if (previousState == ENT_TRIG){
            currentState = ENT_TRIG;
          } else if (previousState == EXIT_TRIG){
            currentState = COUNT_UP;
            pendingCycle = 200;
          }
        break;

        case exitTrig:
          if (previousState == EXIT_TRIG){
            currentState = EXIT_TRIG;
          } else if (previousState == ENT_TRIG){
            currentState = COUNT_DOWN;
            pendingCycle = 200;
          }
        break;

        case bothTrig:
          if (previousState == EXIT_TRIG){
            currentState = COUNT_UP;
            pendingCycle = 200;
          }
          else if (previousState == ENT_TRIG){
            currentState = COUNT_DOWN;
            pendingCycle = 200;
          }
        break;
      }
    break;

    case ENT_TRIG:
      printf("Current State: ENT_TRIG\n");
      previousState = ENT_TRIG;
      switch(transition){
        case noTrig:
          currentState = PENDING;
          break;
        case entTrig:
          currentState = ENT_TRIG;
          break;
        case exitTrig:
          currentState = COUNT_UP;
          break;
        case bothTrig:
          currentState = PENDING_ENT;
          break;
      }
    break;

    case EXIT_TRIG:
      printf("Current State: EXIT_TRIG\n");
      previousState = EXIT_TRIG;
      switch(transition){
        case noTrig:
          currentState = IDLE;
          break;
        case entTrig:
          currentState = COUNT_DOWN;
          break;
        case exitTrig:
          currentState = EXIT_TRIG;
          break;
        case bothTrig:
          currentState = PENDING_EXT;
          break;
      }
    break;

    case PENDING_ENT:
      printf("Current State: PENDING_ENT\n");
      previousState = PENDING_ENT;
      switch(transition){
        case exitTrig:
          currentState = COUNT_UP;
          break;
        case bothTrig:
          currentState = PENDING_ENT;
          break;
      }
    break;

    case PENDING_EXT:
      printf("Current State: PENDING_EXT\n");
      previousState = PENDING_EXT;
      switch(transition){
        case entTrig:
          currentState = COUNT_DOWN;
          break;

        case bothTrig:
          currentState = PENDING_EXT;
          break;
      }
    break;

    case COUNT_UP:
      printf("Current State: COUNT_UP\n");
      previousState = COUNT_UP;
      switch(transition){
        case noTrig:
          count++;
          currentState = IDLE;
          break;

        case exitTrig:
          currentState = COUNT_UP;
          break;

        case bothTrig:
          currentState = 5;
          break;
      }
    break;

    case COUNT_DOWN:
      printf("Current State: COUNT_DOWN\n");
      previousState = COUNT_DOWN;
      switch(transition){
        case noTrig:
          if (count > 0){
            count--;
          } currentState = IDLE;
          break;
        case entTrig:
          currentState = COUNT_DOWN;
          break;

        case bothTrig:
          currentState = COUNT_DOWN;
          break;
      }
    break;
  }
}


int main(int argc, char const *argv[])
{
  int testingCylce = 0;

  currentState = IDLE;
  enum Transition transitions[] = {noTrig, entTrig, bothTrig, exitTrig, noTrig};
  int testingcycles1 = 6;
  
  for (int i = 0; i < testingcycles1; i++){
    occupancyMachine(currentState,transitions[i]);
  }

  printf("ENDING TESTINGCYCLE1 WITH COUNT : %d\n",count);
  printf("\n");

  

  return 0;
}
