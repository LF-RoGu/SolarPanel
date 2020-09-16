void task_OLED_id ()
{
  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0,0);
  display.print("V: ");
  display.print(loadvoltage);
  //display.display();
  display.setCursor(60, 0);
  display.print("mA: ");
  display.println(current_mA);
  //display.display();
  display.setCursor(0, 10);
  display.print("mW: ");
  display.print(power_mW);
  //display.display();
  display.setCursor(0, 20);
  display.print("mWh: ");
  display.print(energy_mWh);
  display.display();

  /*
   * RTC
   */
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  display.setCursor(60, 10);
  display.print("TIME:");

  display.setCursor(95, 10);
  display.print(time_s);

  display.setCursor(55, 20);
  display.print("/");

  display.setCursor(75, 20);
  display.print(time_h);
  
  display.setCursor(83, 20);
  display.print(":");
  
  display.setCursor(90, 20);
  display.print(time_m);
  //Serial.print(time_h); Serial.print(":"); Serial.print(time_m); Serial.print(":"); Serial.print(time_s); Serial.println(".");
  
  // write the buffer to the display
  display.display();

}
