uint8_t encoderA = 5;
uint8_t encoderB = 4;

const long eventTime_1_LDR = 500; //in ms

unsigned long previousTime_1 = 0;
unsigned long previousTime_2 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // make the encoder's pin an input:
  pinMode(encoderA, INPUT);
  pinMode(encoderB, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  /* Updates frequently */
  unsigned long currentTime = millis();

  /* This is my event_1 */
  if ( currentTime - previousTime_1 >= eventTime_1_LDR) {
    uint8_t encoderA_state = digitalRead(encoderA);
    uint8_t encoderB_state = digitalRead(encoderB);

    if( encoderA_state < encoderB_state )
    {
      /*
       * Alimentar cable blanco
       */
      Serial.println("LEFT");
    }
    else if( encoderA_state > encoderB_state )
    {
      /*
       * Alimentar cable rojo
       */
      Serial.println("RIGHT");
    }
    
    /* Update the timing for the next event*/
    previousTime_1 = currentTime;
  }
  
}
