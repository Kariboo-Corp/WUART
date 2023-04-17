#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <WiFi.h>

const char* SSID = "DRONE_1";
const char* PSWD = "DRONE_1";

// debug log, set to 1 to enable
#define ENABLE_DEBUG_LOG 1
  
// ethernet config
const IPAddress local_IP(192, 168, 4, 1);
const IPAddress subnet(255, 255, 255, 0);
  
// rs-server config
const int serverPort = 3001;
  
// rs port config
const int baudrate = 115200;
const int rs_config = SERIAL_8N1;
  
// reading buffor config
#define BUFFER_SIZE 1024
  
// global objects
WiFiServer server;
byte buff[BUFFER_SIZE];

void start_ota();
  
void debug_log(char* str) {
#if ENABLE_DEBUG_LOG == 1
   Serial.println(str);
#endif
}


#endif