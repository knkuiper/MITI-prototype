// prototype 1 with blinking LED; programmed by George

bool isLedOn = false;
unsigned long time;
int greenLedPin=9;
int buttonPin=7;
unsigned long interval = 3000; //in milliseconds
unsigned long newTimeToTurnOnLed = interval;
int buttonState = 0;
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(buttonPin, INPUT);
}

// the loop function runs over and over again forever
void loop() {  
  time = millis();
  TurnOnLed();
  ButtonRead();
}


bool isLedAvailableToTurnOn(){
  if(time > newTimeToTurnOnLed){
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
    analogWrite(greenLedPin, 80);
  }
}

void ButtonRead(){
  if(isLedOn){
    buttonState = digitalRead(buttonPin);
    if(buttonState == LOW){
      newTimeToTurnOnLed = time + interval;
      TurnOffLed();
    }
  }  
}
