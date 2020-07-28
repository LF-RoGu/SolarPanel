void task_sensorValue_id ()
{
  sensorValue = analogRead(A0);

  voltage = ( sensorValue * (5.0 / 1023.0) ) - 0.48;
  current = voltage/2.5;

  power = current * voltage;
  
  energy = ( power * ((0.1)/(3600)) ) + energy;
}
