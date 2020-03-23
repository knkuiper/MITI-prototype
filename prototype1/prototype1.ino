// prototype 1 with blinking LED; programmed by George

#define NUMBEROFEXERCISES 3
String Exercises[NUMBEROFEXERCISES] = {"test 1", "test 2", "test 3"};
String exerciseMessage;

bool isLedOn = false;
unsigned long currentMillis;
int greenLedPin=9;
int buttonPin=8;
unsigned long interval = 3000; //in milliseconds
unsigned long millisToTurnOnLed = interval;
int buttonState = 0;
int previousButtonState = 0;


void setup() {
  Serial.begin(9600);
  
  pinMode(buttonPin, INPUT);
}


void loop() {  
  currentMillis = millis();
  TurnOnLed();
  ButtonRead();

  exerciseMessage = GenerateExerciseMessage(previousButtonState, buttonState);  
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

String GenerateExerciseMessage(int previousButtonState, int buttonState){
  if(previousButtonState == 1 && buttonState == 0){
    return Exercises[random(NUMBEROFEXERCISES)];
  }
}
