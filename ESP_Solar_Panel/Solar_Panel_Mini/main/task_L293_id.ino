void task_L293_id()
{
  state++;

  if (state < 8)
  {
    //Serial.println("RIGHT");
    digitalWrite(MOTOR_RED_WIRE, HIGH);
    digitalWrite(MOTOR_WHITE_WIRE, LOW);
    delay(750);
  }
  if (state > 8)
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
