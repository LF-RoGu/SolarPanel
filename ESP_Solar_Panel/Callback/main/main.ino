#include <ESP8266WiFi.h>
#include <Ticker.h>

bool s = true;
void getSample()
{
  s = !s;
}
Ticker tickerObject(getSample, 100, 0, MICROS_MICROS);

const char *ssid =  "___";  // Change it
const char *pass =  "___";  // Change it

void setup()
{
  Serial.begin(115200);
  Serial.println(0);      //start
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  tickerObject.start();

}


void loop()
{
    if(s == true)
    {
      Serial.println("True");
    }
    else
    {
      Serial.println("False");
    }
}
