# WUART - Wireless UART

This firmware is used to create a WiFi AP to connect to a serial enabled device. It was intend to use with an ESP32 and a flight controller (PX4 FMUvX). Both are connected through their serial port (TELEM 1 for the FCU) and Serial2 (IO16 @ IO17 on the ESP32). 

## Build instructions

This code is made with & for platformIO wich is a VS Code extension. The `platformio.ini` file provide two configuration :
 - [env:esp32dev]
 Is used to compile and upload code through the hardware serial port of the ESP32.
 - [env:espota]
 Is used to compile and upload code trough the wifi access point create by the ESP32.

&copy; aiRCS Lab SAS - 2023