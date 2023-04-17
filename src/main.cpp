#include <Arduino.h>
#include <ArduinoOTA.h>
#include <WiFi.h>

#include "main.h"
  
void setup() {
// init rs port
  Serial.begin(baudrate, rs_config);
  Serial2.begin(baudrate, rs_config);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(SSID, PSWD);

  // init wifi connection
  if (!WiFi.softAPConfig(local_IP, local_IP, subnet)) {
        debug_log("Failed to configure network settings");
  }
  
  #if ENABLE_DEBUG_LOG == 1
    Serial.println("connected to WiFi");
    Serial.println("IP adddr: ");
    Serial.println(WiFi.localIP());
  #endif

   delay(1000);
  
  //start server
   server = WiFiServer(serverPort);
   server.begin();
   delay(1000);
   debug_log("server started");

   start_ota();
}
  
void loop() {

  ArduinoOTA.handle();

  // wait for client
  WiFiClient client = server.available();
  
  if (!client)
    return;
  
  debug_log("client found");
  while (client.connected()) {
  int size = 0;
    
    // read data from wifi client and send to serial
    while ((size = client.available())) {
              size = (size >= BUFFER_SIZE ? BUFFER_SIZE : size);
              client.read(buff, size);
              Serial2.write(buff, size);
              Serial2.flush();
    }
  
    // read data from serial and send to wifi client
    while ((size = Serial2.available())) {
              size = (size >= BUFFER_SIZE ? BUFFER_SIZE : size);
              Serial2.readBytes(buff, size);
              client.write(buff, size);
              client.flush();
    }
  }
  
  debug_log("client disconnected");
  client.stop();
}

void start_ota() {
    ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();
}