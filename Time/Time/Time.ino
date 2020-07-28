/* Two "independant" timed events */
const long eventTime_ms = 1000; //in ms

/* When did they start the race? */
uint64_t previousTime_seconds = 0;

uint16_t time_s = 0;
uint16_t time_m = 0;
uint16_t time_h = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {

  /* Updates frequently */
  uint64_t currentTime = millis();

  /* This is my event_1 */
  if ( currentTime - previousTime_seconds >= eventTime_ms) {

    time_s++;
    if(time_s > 59)
    {
      time_m++;
      time_s = 0;
    }
    if(time_m > 59)
    {
      time_h++;
      time_m = 0;
      if(time_h > 23)
      {
        time_s = 0;
        time_m = 0;
        time_h = 0;
      }
    }
    Serial.print(time_h); Serial.print(":"); Serial.print(time_m); Serial.print(":"); Serial.print(time_s); Serial.println(".");
    /* Update the timing for the next event*/
    previousTime_seconds = currentTime;
  }
}
