/*
 * Author: Luis Fernando
 * Date: 27:05:20
 * Ref:
 * https://microcontrollerslab.com/freertos-counting-semaphore-examples-arduino/
 */

//Rtos
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <event_groups.h>

SemaphoreHandle_t g_semaph;
/*
 * Event
 */
EventGroupHandle_t g_event;

#define DELAY_ADC 100
#define DELAY_OLED 300
#define DELAY_SD 100


const uint8_t task_sensorValue_id =  (1 << 0); // 0x01
const uint8_t task_OLED_id =  (1 << 1); // 0x02
const uint8_t task_SD_id =  (1 << 2); // 0x04
const uint8_t event_task_id = (task_sensorValue_id | task_OLED_id | task_SD_id); // 0x07

uint8_t event_toogle = 0;

uint8_t ev_count = 0;

float voltage = 0;
float current = 0;


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  // set the digital pin as output:
  pinMode(LED_BUILTIN, OUTPUT);
  
  // create semaphore             
  if(g_semaph == NULL)
  {
    g_semaph = xSemaphoreCreateCounting(1,1);

    xSemaphoreGive(g_semaph);
  }
  // create event
  g_event = xEventGroupCreate();
 
   xTaskCreate(Task_sensorValue, // Task function
              "sensorValue", // Task name
              128, // Stack size 
              NULL, 
              0, // Priority
              NULL );
   xTaskCreate(Task_OLED, // Task function
              "LED_G", // Task name
              128, // Stack size 
              NULL, 
              0, // Priority
              NULL );
   xTaskCreate(Task_SD, // Task function
              "LED_B", // Task name
              128, // Stack size 
              NULL, 
              0, // Priority
              NULL );
   xTaskCreate(event_task, // Task function
              "watch_dog", // Task name
              128, // Stack size 
              NULL, 
              5, // Priority
              NULL );

   vTaskStartScheduler();
}

void loop() {}


/*
 * Task to read the panel voltage
 */
void Task_sensorValue(void *pvParameters)
{
  (void) pvParameters;

  const TickType_t xDelay = DELAY_ADC / portTICK_PERIOD_MS;

  uint16_t sensorValue = analogRead(A0);
  
  for (;;) 
    {
      xSemaphoreTake(g_semaph, portMAX_DELAY); 

      

      //Update Values
      voltage = ( sensorValue * (5.0 / 1023.0) ) - 0.48;
      current = voltage/2.5;
      
/*event*/
      //Event to store average values
      ev_count++;
      if(10 == ev_count)
      {
        xEventGroupSetBits(g_event, task_sensorValue_id);
      }
      
      xSemaphoreGive(g_semaph);
      vTaskDelay(xDelay);
    }
  }

void Task_OLED(void *pvParameters)
{
  (void) pvParameters;

  const TickType_t xDelay = DELAY_OLED / portTICK_PERIOD_MS;

  volatile float power = 0;
  volatile float energy = 0;
  
  for (;;) 
    {
      xSemaphoreTake(g_semaph, portMAX_DELAY);

      //Print values on Display

      

/*event*/
      ev_count++;
      if(20 == ev_count)
      {
        xEventGroupSetBits(g_event, task_OLED_id);
      }
      
      xSemaphoreGive(g_semaph);
      vTaskDelay(xDelay);

  }
}

void Task_SD(void *pvParameters)
{
  (void) pvParameters;

  const TickType_t xDelay = DELAY_SD / portTICK_PERIOD_MS;
  
  for (;;) 
    {
      xSemaphoreTake(g_semaph, portMAX_DELAY);
      
/*event*/
      ev_count++;
      if(50 == ev_count)
      {
        xEventGroupSetBits(g_event, task_SD_id);
      }
      
      xSemaphoreGive(g_semaph);
      vTaskDelay(xDelay);

  }
}

void event_task(void *pvParameters)
{
  (void) pvParameters;
  
  for(;;)
  {
    uint8_t event_res = xEventGroupWaitBits(g_event,
                                            event_task_id,
                                            pdTRUE, //clear bits on exit
                                            pdTRUE, //wait for all bits to be set
                                            portMAX_DELAY); // wait time
    ev_count = 0;
    
    if(!event_toogle)
    {
      event_toogle = !event_toogle;
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("EVENT TASK HIGH");
    }
    else if(event_toogle)
    {
      event_toogle = !event_toogle;
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("EVENT TASK LOW");
    }
    
  }
}
