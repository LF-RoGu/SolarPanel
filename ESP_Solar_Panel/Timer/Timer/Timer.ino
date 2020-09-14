/*
    Ticker ESP8266
    Hardware: NodeMCU
    Circuits4you.com
    2018
    LED Blinking using Ticker
*/
//=======================================================================
//                               Lib
//=======================================================================
#include <ESP8266WiFi.h>
#include <Ticker.h>  //Ticker Library
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//=======================================================================
//                               Tickers
//=======================================================================
Ticker blinker_one;
Ticker blinker_two;
//=======================================================================
//                               Definitions
//=======================================================================
#define LED 2  //On board LED
#define OLED_RESET     LED_BUILTIN // Reset pin # (or -1 if sharing Arduino reset pin)

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Initialize the OLED display using Wire library
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//=======================================================================
//                               Prototype
//=======================================================================
void ledOn()
{
  Serial.println("HIGH");
  digitalWrite(LED, HIGH);  //Invert Current State of LED
}
void ledOff()
{
  Serial.println("LOW");
  digitalWrite(LED, LOW);  //Invert Current State of LED
}
//=======================================================================
//                               Setup
//=======================================================================
void setup()
{
  Serial.begin(115200);
  Serial.println("");

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  pinMode(LED, OUTPUT);

  //Initialize Ticker every 0.5s
  blinker_one.attach(0.8, task_OLED_id); //Use <strong>attach_ms</strong> if you need time in ms
  blinker_two.attach(0.5, ledOff); //Use <strong>attach_ms</strong> if you need time in ms
}
//=======================================================================
//                MAIN LOOP
//=======================================================================
void loop()
{
}
