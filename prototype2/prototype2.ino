#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>       // this is needed for display
#include <Adafruit_ILI9341.h>
#include <Wire.h>      // this is needed for FT6206
#include <Adafruit_FT6206.h>
#include <Adafruit_TFTLCD.h>
#include <Fonts/FreeMonoBoldOblique12pt7b.h>
#include <TouchScreen.h>

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

enum ButtonState {
  NewExercise,
  DisabledDone,
  EnabledDone
};
ButtonState buttonState = NewExercise;

// The display also uses hardware SPI, plus #9 & #10
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

Adafruit_FT6206 ts = Adafruit_FT6206();

boolean isButtonEnabled = false;
boolean wasButtonPressed = false;
#define NUMBEROFEXERCISES 4
String Exercises[NUMBEROFEXERCISES] = {"Do some streches", "Do 10 squats", "Take a walk", "Do 5 pushups"};

unsigned long currentMillis;
unsigned long interval = 3000; //in milliseconds
unsigned long millisToNextExercise = interval;

void setup() {

  Serial.begin(9600);

  tft.begin();
  ts.begin();

  tft.setRotation(1);
  tft.fillScreen(CYAN);
  tft.drawRect(0, 0, 320, 240, YELLOW);

  

  tft.fillRect(70, 180, 170, 35, RED);
  tft.drawRect(70, 180, 170, 35, BLACK);
  tft.setCursor(82, 190);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("New exercise");


}

void loop() {
  currentMillis = millis();

  EnableButton();
  ButtonRead();
}

bool isButtonAvailableToBeEnabled() {
  if (currentMillis > millisToNextExercise) {
    return true;
  }

  return false;
}


void EnableButton() {
  if (!isButtonEnabled) {
    isButtonEnabled = true;
    tft.fillRect(70, 180, 170, 35, RED);
    tft.drawRect(70, 180, 170, 35, BLACK);
    tft.setCursor(82, 190);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("New exercise");
    //code to make the button clickable?
  }
}

void DisableButton() {
  tft.fillRect(70, 180, 170, 35, BLACK);
  isButtonEnabled = false;
  millisToNextExercise = currentMillis + interval;
}

void ButtonRead() {
  TS_Point p = ts.getPoint();
  Serial.println(p.y);

  if (p.x > 180 && p.x < 215 && p.y > 80 && p.y < 240 && buttonState == NewExercise  && !wasButtonPressed) {
    tft.setCursor(30, 40);
    tft.print(" ");

    tft.fillRect(70, 180, 170, 35, YELLOW);
    tft.drawRect(70, 180, 170, 35, BLACK);
    tft.setCursor(82, 190);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("New exercise");

    wasButtonPressed = true;
  }

  if (p.x == 0 && p.y == 0 && wasButtonPressed && buttonState == NewExercise) {
    tft.fillRect(70, 180, 170, 35, RED);
    tft.drawRect(70, 180, 170, 35, BLACK);
    tft.setCursor(82, 190);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("New exercise");
    wasButtonPressed = false;

    buttonState = DisabledDone;
    millisToNextExercise = currentMillis + interval;
    //DisableButton();

    GenerateExerciseMessage();
  }

  if(buttonState == DisabledDone && !isButtonAvailableToBeEnabled()){
     tft.fillRect(70, 180, 170, 35, BLACK);
  }

  if(buttonState == DisabledDone && isButtonAvailableToBeEnabled()){
    tft.fillRect(70, 180, 170, 35, GREEN);
    tft.drawRect(70, 180, 170, 35, BLACK);
    tft.setCursor(82, 190);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("Done!");

    buttonState = EnabledDone;
  }

  if(buttonState == EnabledDone && p.x > 180 && p.x < 215 && p.y > 80 && p.y < 240 && !wasButtonPressed){
    tft.fillRect(70, 180, 170, 35, YELLOW);
    tft.drawRect(70, 180, 170, 35, BLACK);
    tft.setCursor(82, 190);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("Done!");

    wasButtonPressed = true;
  }

  if(buttonState == EnabledDone && p.x == 0 && p.y == 0 && wasButtonPressed){
    tft.fillRect(70, 180, 170, 35, RED);
    tft.drawRect(70, 180, 170, 35, BLACK);
    tft.setCursor(82, 190);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("New exercise");

    wasButtonPressed = false;

    buttonState = NewExercise;
    GenerateCongratsMessage();
  }
  
}


void GenerateExerciseMessage() {
  tft.fillRect(1, 40, 318, 60, CYAN);

  tft.setCursor(30, 40);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print(Exercises[random(NUMBEROFEXERCISES)]);
}

void GenerateCongratsMessage(){
  tft.fillRect(1, 40, 318, 60, CYAN);

  tft.setCursor(30, 40);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("Ready for another one?");
}
