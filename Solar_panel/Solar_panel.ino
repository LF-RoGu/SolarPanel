#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_INA219.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)

#define EVENT_TIME_ADC 100
#define EVENT_TIME_OLED 120
#define EVENT_TIME 1000

#define MOTOR_RED_WIRE 9
#define MOTOR_WHITE_WIRE 11
#define L293D_DRIVER_ENABLE  13

#define TRUE 1
#define FALSE 0


// Initialize the OLED display using Wire library
SSD1306Wire  display(0x3c, D2, D1);  //D2=SDK  D1=SCK  As per labeling on NodeMCU

Adafruit_INA219 ina219;

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

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);


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

  /*
  * OLED SetUp
  */
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  /*
   * INA219
   */
  ina219.begin();
  ina219.setCalibration_16V_400mA();
}
/********************************************/
/********************************************/
/********************************************/
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

/********************************************/
/********************************************/
/********************************************/

/*
 * Main Loop
 */
void loop() {
  uint32_t currentTime = millis(); //ms

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
  /*
   * 
   */
  if( TRUE == flag_motor )
  {  
    state++;
    if(state < 8)
    {
      //Serial.println("RIGHT");
      digitalWrite(MOTOR_RED_WIRE, HIGH);
      digitalWrite(MOTOR_WHITE_WIRE, LOW);
      delay(750);
    }

    if(state > 8)
    {
      //Serial.println("LEFT");
      digitalWrite(MOTOR_WHITE_WIRE, HIGH);
      digitalWrite(MOTOR_RED_WIRE, LOW);
      delay(3500);
      
      state = 0;
    }

    flag_motor = FALSE;
    digitalWrite(MOTOR_RED_WIRE, LOW);
    digitalWrite(MOTOR_WHITE_WIRE, LOW);
  }
}
