//=======================================================================
//                               Lib
//=======================================================================
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_INA219.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>  //Ticker Library

//=======================================================================
//                               Tickers
//=======================================================================

//=======================================================================
//                               GPIO
//=======================================================================
const uint8_t GPIO_D0   = 16;
const uint8_t GPIO_D1   = 5;
const uint8_t GPIO_D2   = 4;
const uint8_t GPIO_D3   = 0;
const uint8_t GPIO_D4   = 2;
const uint8_t GPIO_D5   = 14;
const uint8_t GPIO_D6   = 12;
const uint8_t GPIO_D7   = 13;
const uint8_t GPIO_D8   = 15;
const uint8_t GPIO_S2   = 9;
const uint8_t GPIO_S3  = 10;
//=======================================================================
//                               Definitions
//=======================================================================
#define OLED_RESET     LED_BUILTIN // Reset pin # (or -1 if sharing Arduino reset pin)

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define EVENT_TIME_ADC 100
#define EVENT_TIME_OLED 120
#define EVENT_TIME 1000

#define MOTOR_RED_WIRE GPIO_D5
#define MOTOR_WHITE_WIRE GPIO_D6
#define L293D_DRIVER_ENABLE  GPIO_D7

#define TRUE 1
#define FALSE 0

//=======================================================================
//                               Variables
//=======================================================================
uint8_t state = 0;

uint32_t previous_time_ADC = 0;
uint32_t previous_time_OLED = 0;
uint32_t previous_time_TIME = 0;

uint16_t time_s = 0;
uint16_t time_m = 0;
uint16_t time_h = 0;

uint16_t temp_time_m = 0;

uint8_t flag_motor = FALSE;

float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;
float power_mW = 0;
float energy_mWh = 0;

uint32_t currentTime = millis(); //ms

//=======================================================================
//                               INA219 Objects
//=======================================================================

// Initialize the INA display using Wire library
Adafruit_INA219 ina219;
//=======================================================================
//                               OLED Objects
//=======================================================================

// Initialize the OLED display using Wire library
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//=======================================================================
//                               Prototype
//=======================================================================
/*
 * 
 */
void task_sensorValue_id (void);
/*
 * 
 */
void task_OLED_id (void);
/*
 * 
 */
void task_RTC_id(void);
//=======================================================================
//                               Setup
//=======================================================================
void setup()
{
    Serial.begin(115200);
    Serial.println("");
    delay(1000);

    /*
     * OLED SetUp
     */
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
    }
    display.display();
    display.clearDisplay();
    /*
     * Motor Control Pin
     */
    pinMode(MOTOR_RED_WIRE, OUTPUT);
    pinMode(MOTOR_WHITE_WIRE, OUTPUT);

    /*
     * Driver L293D Enable Pin
     */
    pinMode(L293D_DRIVER_ENABLE, OUTPUT);
    digitalWrite(L293D_DRIVER_ENABLE, HIGH);
}
//=======================================================================
//                MAIN LOOP
//=======================================================================
void loop()
{
  /*
   * 
   */
  if(currentTime - previous_time_ADC >= EVENT_TIME_ADC)
  {    
    task_sensorValue_id();
    
    previous_time_ADC = currentTime;
  }
  /*
   * 
   */
  if(currentTime - previous_time_OLED >= EVENT_TIME_OLED)
  {     
    task_OLED_id();
    
    previous_time_OLED = currentTime;
  }
  /*
   * 
   */
  if(currentTime - previous_time_TIME >= EVENT_TIME)
  {  
    task_RTC_id();
    
    previous_time_TIME = currentTime;
  }
}
