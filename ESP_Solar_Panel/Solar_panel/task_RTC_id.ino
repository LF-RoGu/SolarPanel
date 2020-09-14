void task_RTC_id ()
{
  
  time_s++;
  if(time_s > 59)
  {
    time_m++;
    time_s = 0;

    if( 0 == (time_m%20) )
    {     
      /*
       * 
       */
      flag_motor = TRUE;
    }
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
  //Serial.print(time_h); Serial.print(":"); Serial.print(time_m); Serial.print(":"); Serial.print(time_s); Serial.println(".");
    
}
