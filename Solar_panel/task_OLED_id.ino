void task_OLED_id ()
{
  
  display.setTextAlignment(TEXT_ALIGN_LEFT);

  display.display();
  
  display.setCursor(0, 0);     // Start at top-left corner
  display.setTextSize(1);      // Normal 1:1 pixel scale
  
  // Clear the buffer
  display.clearDisplay();



  display.print("V: ");
  display.print(loadvoltage);
  display.setCursor(60, 0);
  display.print("mA: ");
  display.println(current_mA);
  
  display.setCursor(0, 10);
  display.print("mW: ");
  display.print(power_mW);
  
  display.setCursor(0, 20);
  display.print("mWh: ");
  display.print(energy_mWh);

  /*
   * RTC
   */
  display.setCursor(60, 10);
  display.print("TIME:");

  display.setCursor(95, 10);
  display.print(time_s);

  display.setCursor(55, 20);
  display.print("/");

  display.setCursor(68, 20);
  display.print(time_h);
  
  display.setCursor(80, 20);
  display.print(":");
  
  display.setCursor(85, 20);
  display.print(time_m);
  //Serial.print(time_h); Serial.print(":"); Serial.print(time_m); Serial.print(":"); Serial.print(time_s); Serial.println(".");
  
  // write the buffer to the display
  display.display();
}
