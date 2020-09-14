/*
 * 
 */
void task_OLED_id (void)
{
  display.setCursor(0, 0);     // Start at top-left corner
  display.setTextSize(1);      // Normal 1:1 pixel scale
  
  display.display();

  // Clear the buffer
  display.clearDisplay();


  display.print("V: ");
  //display.print(loadvoltage);
  display.display();
  display.setCursor(60, 0);
  display.print("mA: ");
  //display.println(current_mA);
  display.display();
  
  
  display.setCursor(0, 10);
  display.print("mW: ");
  //display.print(power_mW);
  display.display();
  
  display.setCursor(0, 20);
  display.print("mWh: ");
  //display.print(energy_mWh);
  display.display();
}
