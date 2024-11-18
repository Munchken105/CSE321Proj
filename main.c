#include <Wire.h>
#include <LiquidCrystal_I2C.h>


//Define the States
#define IDLE = 0; //zero sensor triggered
#define ENT_TRIG = 1; //entrance sensor triggered
#define EXIT_TRIG = 2; //exit sensor triggered
#define PENDING_ENT = 3; //both sensor triggered, pending entrance
#define PENDING_EXIT = 4; //both sensor triggered, pending exit
#define COUNTUP = 5;
#define COUNTDOWN = 6;

//Define the Transition
#define noTrig;
#define entTrig;
#define exitTrig;
#define bothTrig;


LiquidCrystal_I2C lcd(0x27,16,2);
int count = 0;
int currentState;
int cycle = 500;

int DoorIn = 0;
int DoorOut = 0;

int defineTransition(int Entr, int Exit){
  if (Entr == HIGH && Exit == HIGH){
    return 0;
  } else if (Entr == LOW && Exit == HIGH){
    return 1;
  } else if (Entr == HIGH && Exit == LOW){
    return 2;
  } else if (Entr == LOW && Exit == LOW){
    return 3;
  } else {
    Serial.print("Invalid Transition: Find Error");
    return -1;
  }
}

void setup() {
  // put your setup code here, to run once:
  currentState = 0;
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
  


  if (cycle == 0){
    lcd.clear();
    Serial.print("Clearing LCD\n");
    cycle = 500;
  }

  cycle--;

  DoorIn = digitalRead(9);
  DoorOut = digitalRead(8);
  //DEFINING Transitions
  int currentTransition = defineTransition(DoorIn,DoorOut);

  //FSM
  switch (currentState){
    case 0:
      switch (currentTransition){
        case 0:
          Serial.print("Current State: Idle\n");
          break;
        case 1:
          Serial.print("Current Transition: Entrance Triggered\n");
          currentState = 1;
          break;
        case 2:
          Serial.print("Current Transition: Exit Triggered\n");
          currentState = 2;
          break;
      }
    break;
    
    case 1:
      switch (currentTransition){
        case 0:
          Serial.print("Current State: Idle\n");
          currentState = 0;
          break;

        case 1:
          Serial.print("Someone Step on the Entrance Sensor\n");
          currentState = 1;
          break;

        case 2:
          currentState = 5;
          break;

        case 3:
          Serial.print("Both Trigger Triggered from Entrance\n");
          currentState = 3;
          break;
      }
      break;

      case 2:
      switch (currentTransition){
        case 0:
          Serial.print("Current State: Idle\n");
          currentState = 0;
          break;

        case 1:
          currentState = 6;
          break;

        case 2:
          Serial.print("Someone Step on the Exit Sensor\n");
          currentState = 2;
          break;

        case 3:
          Serial.print("Both Trigger Triggered from Exit\n");
          currentState = 4;
          break;
      }
      break;

      case 3:
        switch (currentTransition){
        case 2:
          currentState = 5;
          break;

        case 3:
          Serial.print("Pending Entrance\n");
          currentState = 3;
          break;
      }
      break;

      case 4:
      switch (currentTransition){
        case 1:
          currentState = 6;
          break;

        case 3:
          Serial.print("Pending Exit\n");
          currentState = 4;
          break;
      }
      break;

      case 5:
        switch (currentTransition){
        case 0:
          Serial.print("Completed Entrance\n");
          count++;
          currentState = 0;
          break;

        case 2:
          Serial.print("Confirming Entrance\n");
          currentState = 5;
          break;

        case 3:
          Serial.print("Confirming Entrance\n");
          currentState = 5;
          break;
      }
      break;

      case 6:
        switch (currentTransition){
        case 0:
          Serial.print("Completed Exit\n");
          if (count > 0){
            count--;
          }
          currentState = 0;
          break;

        case 1:
          Serial.print("Confirming Exit\n");
          currentState = 6;
          break;
        
        case 3:
          Serial.print("Confirming Exit\n");
          currentState = 6;
          break;

      }
      break;
  }



  lcd.setCursor(0,0);
  lcd.print("Count: ");
  lcd.print(count);



}



