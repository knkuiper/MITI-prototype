// prototype 1 with blinking LED; programmed by George
#include <LiquidCrystal.h>

#define NUMBEROFEXERCISES 4
String Exercises[NUMBEROFEXERCISES] = {"Do some streches", "Do 10 squats", "Take a walk", "Take 5 pushups"};
String exerciseMessage;

bool isLedOn = false;
unsigned long currentMillis;
int greenLedPin=9;
int buttonPin=7;
unsigned long interval = 3000; //in milliseconds
unsigned long millisToTurnOnLed = interval;
int buttonState = 0;
int previousButtonState = 0;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
  Serial.begin(9600);
  
  pinMode(buttonPin, INPUT);
  
  lcd.begin(16, 2);
}


void loop() {  
  currentMillis = millis();
  TurnOnLed();
  ButtonRead();

  GenerateExerciseMessage(previousButtonState, buttonState);
}


bool isLedAvailableToTurnOn(){
  if(currentMillis > millisToTurnOnLed){
    return true;
  }

  return false;
}

void TurnOffLed(){
  analogWrite(greenLedPin, 0);
  isLedOn = false;
}

void TurnOnLed(){
  if(isLedAvailableToTurnOn()){
    isLedOn = true;
    analogWrite(greenLedPin, 20);
  }
}

void ButtonRead(){
  previousButtonState = buttonState;

  if(isLedOn){
    buttonState = digitalRead(buttonPin);
    if(buttonState == LOW){
      millisToTurnOnLed = currentMillis + interval;
      TurnOffLed();
    }
  }
}

void GenerateExerciseMessage(int previousButtonState, int buttonState){
  if(previousButtonState == 1 && buttonState == 0){
    lcd.clear();
    lcd.print(Exercises[random(NUMBEROFEXERCISES)]);
  }
}
