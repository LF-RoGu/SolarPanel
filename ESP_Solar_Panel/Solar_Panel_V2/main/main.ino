//=======================================================================
//                               Lib
//=======================================================================
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_INA219.h>
#include <Ticker.h>  //Ticker Library
/*
   Blynk
*/
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//=======================================================================
//                               Tickers
//=======================================================================
//Ticker blinker_one;
//Ticker blinker_two;
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
const uint8_t GPIO_S3   = 10;
//=======================================================================
//                               Definitions
//=======================================================================
#define OLED_RESET     LED_BUILTIN // Reset pin # (or -1 if sharing Arduino reset pin)

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define EVENT_TIME_INA219 100
#define EVENT_TIME_OLED 120
#define EVENT_TIME 1000

#define MOTOR_RED_WIRE GPIO_D3
#define MOTOR_WHITE_WIRE GPIO_D4
#define L293D_DRIVER_ENABLE  GPIO_D5

#define TRUE 1
#define FALSE 0

#define OLED_RESET     LED_BUILTIN // Reset pin # (or -1 if sharing Arduino reset pin)

#define BLYNK_TIME (5)*(60)*(1000) //Minutos*segundos*milisegundos
//=======================================================================
//                               Variables
//=======================================================================
uint8_t state = 0;

uint32_t previous_time_INA219 = 0;
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
/*
   Blynk
*/
char auth[] = "UCo5_O_dp3pxvlatchCHlCMmO9u8REof";
char ssid[] = "role";
char pass[] = "role1966";
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
//                               BLYNK Objects
//=======================================================================

//
BlynkTimer blynk_timer;
//=======================================================================
//                               Prototype
//=======================================================================
/*

*/
void task_OLED_id (void);
/*

*/
void task_RTC_id (void);
/*

*/
void task_INA219_id (void);
//=======================================================================
//                               Setup
//=======================================================================

void setup() {
  // put your setup code here, to run once:
  // initialize with the I2C addr 0x3C
  Serial.begin(115200);

  /*
     BLYNK SetUp
  */
  Blynk.begin(auth, ssid, pass);
  /*
     Driver L293D Enable Pin
  */
  pinMode(L293D_DRIVER_ENABLE, OUTPUT);
  digitalWrite(L293D_DRIVER_ENABLE, HIGH);
  /*
     Motor direction SetUp
  */
  pinMode(MOTOR_RED_WIRE, OUTPUT);
  pinMode(MOTOR_WHITE_WIRE, OUTPUT);
  /*
     OLED SetUp
  */
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();// Clear the buffer.
  /*
     INA219
  */
  ina219.begin();
  ina219.setCalibration_16V_400mA();
  /*
     Ticker SetUp
  */
  //Initialize Ticker every 0.5s
  //blinker_one.attach(2.0, task_OLED_id_one); //Use <strong>attach_ms</strong> if you need time in ms
  //blinker_two.attach(3.0, task_OLED_id_two); //Use <strong>attach_ms</strong> if you need time in ms
  blynk_timer.setInterval(BLYNK_TIME, task_BLYNK_id);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint32_t currentTime = millis(); //ms

  /*
     Blynk run
  */
  Blynk.run();
  blynk_timer.run();

  /*

  */
  if (currentTime - previous_time_OLED >= EVENT_TIME_OLED)
  {
    task_OLED_id();

    previous_time_OLED = currentTime;
  }
  /*

  */
  if (currentTime - previous_time_TIME >= EVENT_TIME)
  {
    task_RTC_id();

    previous_time_TIME = currentTime;
  }
  /*

  */
  if (currentTime - previous_time_INA219 >= EVENT_TIME_INA219)
  {
    task_INA219_id();

    previous_time_INA219 = currentTime;
  }
  /*

  */
  if (TRUE == flag_motor)
  {
    task_L293_id();
  }

}
