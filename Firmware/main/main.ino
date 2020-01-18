
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
//#include <BlynkSimpleEsp8266.h>
#include <BlynkSimpleStream.h>
#include <ShiftRegister74HC595.h>
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>        
#include <DNSServer.h>        
#include <WiFiManager.h>  


ShiftRegister74HC595 sr (1, 16, 13, 12);

ESP8266WebServer server(80);

WiFiClient wifiClient;

bool connectBlynk()
{
  wifiClient.stop();
  return wifiClient.connect(BLYNK_DEFAULT_DOMAIN, BLYNK_DEFAULT_PORT);
}

void handleRoot();

char blynk_token[34] = "YxOrXKNUTgQjNXg6nFkI8lY84buC0DlK"; // Copy Your Token From Blink App


void setup()
{
  Serial.begin(9600);

  WiFiManagerParameter custom_blynk_token("blynk", "blynk token", blynk_token, 32);
  
  WiFiManager wifiManager;
  wifiManager.addParameter(&custom_blynk_token);
  wifiManager.autoConnect();
  wifiManager.setConfigPortalTimeout(180);
  wifiManager.addParameter(&custom_blynk_token);

  Serial.print(custom_blynk_token.getValue());
  
  connectBlynk();
  Blynk.begin(wifiClient, blynk_token);
  server.begin();
  
}


void loop()
{
  Blynk.run();
}


BLYNK_CONNECTED() {
  Blynk.syncAll();
}

BLYNK_WRITE_DEFAULT(){
  int pin = request.pin;
  int value = param.asInt();
  sr.set(pin, value);
}
