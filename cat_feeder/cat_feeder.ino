/*
  OmNomCat
  Servo control
  
 */

// include the servo library
#include <Servo.h>
#include "Timer.h"

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
Servo myServo;  // create a servo object
Timer t;

int const SERVO_PIN = 9;
int const SWITCH_PIN = 13;
int const POT_PIN = A0;

int MAX_ANGLE = 179;
int MIN_ANGLE = 0;

int FOOD_TIME = 20;//ticks between each dispense
int TIMER_TICK = 1000;//ms between each "tick"
int FOOD_TIME_COUNTER = 20;

int tickEvent = 0;
int potVal;

byte newChar[8] = {
        B11111,
        B10101,
        B11111,
        B10101,
        B10101,
        B11111,
        B10101,
        B11111
};

void setup() {
  Serial.begin(9600); 
  
  myServo.attach(SERVO_PIN); 
  tickEvent = t.every(TIMER_TICK, doSomething);
  
  lcd.createChar(7, newChar);
  lcd.begin(16, 2);

}

void updateLCD(int percentage){
  Serial.println(percentage);
  //16 per line
  lcd.clear();
  int row = 0;
  while(row < 2){
    lcd.setCursor(0, row);
    float i = 0;
    while(i < percentage){//6.25
      lcd.write(byte(7));
      i += (float)100 / (float)16;
    }
    row++;
    }
}


void loop() {
  // print out the value to the serial monitor
  dispenseFoodButton();
  t.update();
  int potValNew = analogRead(POT_PIN);
  if(potVal != potValNew){//Value has changed - go in to a different mode!
    potVal = potValNew;
    changeTimer(potVal);
  }
}

void changeTimer(int potential){
  //Display a new value to the LCD
  int percentage = ((float)potential / (float)1024)*100;
  updateLCD(percentage);
  //Update globals
  FOOD_TIME = 20 + (percentage);
}

void timerTick(){
  FOOD_TIME_COUNTER = FOOD_TIME_COUNTER - 1;
  //Serial.println(FOOD_TIME_COUNTER);
  
  int percentage =  ((float)FOOD_TIME_COUNTER / (float)FOOD_TIME) * 100;
  updateLCD(percentage);
  
  if(FOOD_TIME_COUNTER == 0){
    dispenseFood();//OMNOMNOM
    FOOD_TIME_COUNTER = FOOD_TIME;//Reset time
  }
}


void doSomething(){
   resetTimer();
   //Serial.println("A tick");
   timerTick();
}

void resetTimer(){
  t.stop(tickEvent);
  tickEvent = t.every(FOOD_TIME, doSomething);
}

void dispenseFood(){
    myServo.write(MAX_ANGLE);    
    delay(1000);
    myServo.write(MIN_ANGLE);
    delay(1000);
}


void dispenseFoodButton(){
  if (isButtonPressed()) {
    resetTimer();
    dispenseFood();
  }
  // wait for the servo to get there
  delay(300);
}

boolean isButtonPressed(){
  return (digitalRead(SWITCH_PIN) == HIGH);
}



// To to
// digits to squares
// NFC + led
