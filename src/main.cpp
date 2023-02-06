#include <Arduino.h>
#include <WiFi.h>

#include "main.h"
  
void setup() {
// init rs port
  Serial.begin(baudrate, rs_config);
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
}
  
void loop() {
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
              Serial.write(buff, size);
              Serial.flush();
    }
  
    // read data from serial and send to wifi client
    while ((size = Serial.available())) {
              size = (size >= BUFFER_SIZE ? BUFFER_SIZE : size);
              Serial.readBytes(buff, size);
              client.write(buff, size);
              client.flush();
    }
  }
  
  debug_log("client disconnected");
  client.stop();
}