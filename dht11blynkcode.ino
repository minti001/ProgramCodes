
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#define DHTPIN 2  //This is Pin D4 in nodemcu

#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
//BlynkTimer timer;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = ""; //Type your authentication code

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

float h;
float t;

void sendSensor()
{
   h = dht.readHumidity();
   t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, t);
  delay(1000);
  Blynk.virtualWrite(V6, h);
  Serial.println(h);
  Serial.println(t);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  //while(!Serial) { };
  // Setup a function to be called every second
  //timer.setInterval(1000L, sendSensor);
 
  //Serial.println("Going into deep sleep for 30 seconds");
  //ESP.deepSleep(30e6); // 30e6 is 30 microseconds

}

void loop()
{
  Blynk.run();
  //timer.run();
  sendSensor();
  
  //Serial.println("Going into deep sleep for 30 seconds");
  
  
  //ESP.deepSleep(360000000); // 36000000 is 36 microseconds
}
