#include <Wire.h>
#include <LiquidCrystal_I2C.h>

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
LiquidCrystal_I2C lcd(0x27,16,2);


int count = 0;

enum States currentState;
enum States previousState;

int clearCycle = 500;
int pendingCycle = 200;

int DoorIn = 0;
int DoorOut = 0;


enum Transition defineTransition(int Entr, int Exit){
  if (Entr == HIGH && Exit == HIGH){
    return noTrig;
  } else if (Entr == LOW && Exit == HIGH){
    return entTrig;
  } else if (Entr == HIGH && Exit == LOW){
    return exitTrig;
  } else if (Entr == LOW && Exit == LOW){
    return bothTrig;
  } else {
    Serial.print("Invalid Transition: Find Error");
    return NULL;
  }
}

void clearLCD(){
  if (clearCycle == 0){
    lcd.clear();
    Serial.print("Clearing LCD\n");
    clearCycle = 500;
  }
  clearCycle--;
}


void occupancyMachine(enum States state, enum Transition transition){
  switch (state){

    case IDLE:
      Serial.print("Current State: IDLE\n");
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
      Serial.print("Current State: PENDING\n");
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
            currentState = COUNT_DOWN;
            pendingCycle = 200;
          }
        break;

        case exitTrig:
          if (previousState == EXIT_TRIG){
            currentState = EXIT_TRIG;
          } else if (previousState == ENT_TRIG){
            currentState = COUNT_UP;
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
      Serial.print("Current State: ENT_TRIG\n");
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
      Serial.print("Current State: EXIT_TRIG\n");
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
      Serial.print("Current State: PENDING_ENT\n");
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
      Serial.print("Current State: PENDING_EXT\n");
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
      Serial.print("Current State: COUNT_UP\n");
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
      Serial.print("Current State: COUNT_DOWN\n");
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

void setup() {
  // put your setup code here, to run once:
  currentState = IDLE;
  lcd.init();
  lcd.clear();
  lcd.backlight();

  analogReference(DEFAULT);
  pinMode(A0,INPUT);

  pinMode(9,INPUT);
  pinMode(8,INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  float temp = ((analogRead(A0) * (5.0/1024))-0.5)/0.01;
  clearLCD();

  //DEFINING Transitions
  DoorIn = digitalRead(9);
  DoorOut = digitalRead(8);
  enum Transition currentTransition = defineTransition(DoorIn,DoorOut);

  occupancyMachine(currentState ,currentTransition);

  lcd.setCursor(0,0);
  lcd.print("Count: ");
  lcd.print(count);


  //"CLEARING SERIAL TERMINAL" (PUT IT IN AIR-QUOTE)
  for (int i = 0;  i < 200; i++){
    Serial.print(" \n");
  }
}