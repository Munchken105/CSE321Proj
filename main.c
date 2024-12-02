#include <Wire.h>
#include <LiquidCrystal_I2C.h>

enum States{
  IDLE,
  ENT_TRIG,
  EXIT_TRIG,
  PENDING_ENT,
  PENDING_EXT,
  COUNT_UP,
  COUNT_DOWN
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
int cycle = 500;
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
  if (cycle == 0){
    lcd.clear();
    Serial.print("Clearing LCD\n");
    cycle = 500;
  }
  cycle--;
}


void occupancyMachine(enum States state, enum Transition transition){
  switch (state){

    case IDLE:
      switch(transition){
        case noTrig:
          Serial.print("Current State: Idle\n");
          break;
        case entTrig:
          currentState = ENT_TRIG;
          break;
        case exitTrig:
          currentState = EXIT_TRIG;
          break;
      }
    break;

    case ENT_TRIG:
      case noTrig:
      break;
      case entTrig:
      break;
      case exitTrig:
      break;
      case bothTrig:
      break;
    break;

    case EXIT_TRIG:
      case noTrig:
      break;
      case entTrig:
      break;
      case exitTrig:
      break;
      case bothTrig:
      break;
    break;

    case PENDING_ENT:
      case noTrig:
      break;
      case entTrig:
      break;
      case exitTrig:
      break;
      case bothTrig:
      break;
    break;

    case PENDING_EXT:
      case noTrig:
      break;
      case entTrig:
      break;
      case exitTrig:
      break;
      case bothTrig:
      break;
    break;

    case COUNT_UP:
      case noTrig:
      break;
      case entTrig:
      break;
      case exitTrig:
      break;
      case bothTrig:
      break;
    break;

    case COUNT_DOWN:
      case noTrig:
      break;
      case entTrig:
      break;
      case exitTrig:
      break;
      case bothTrig:
      break;
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

  DoorIn = digitalRead(9);
  DoorOut = digitalRead(8);
  //DEFINING Transitions
  enum Transition currentTransition = defineTransition(DoorIn,DoorOut);

  occupancyMachine(currentState ,currentTransition);

  lcd.setCursor(0,0);
  lcd.print("Count: ");
  lcd.print(count);
}