# Receiving GPS/INS DATA with Arduino DUE
https://youtu.be/ZbwTwUUQbUk


# Reference
Parsing GPS DATA using Arduino

https://clemencyking.tistory.com/9

NTRIP Client for Arduino

https://github.com/GLAY-AK2/NTRIP-client-for-Arduino


# Equipments

 Arduino DUE
 
 NodeMCU ESP8266 Wi-Fi Module
 
 C099-F9P GPS Module
 
 MPU-9250 IMU Sensor


# How to use

1. Connect Wi-Fi Module TX to GPS Module RX

2. Connect GPS Module TX to Arduino DUE RX2

3. Connect IMU sensor to Arduino DUE (I2C:20,21)

4. Go to https://github.com/GLAY-AK2/NTRIP-client-for-Arduino

5. Edit the code for your application. and upload it on Wi-fi board.

6. Download 'for_arduino.ino' and upload it


# Precautions

Set baudrate (GPS-WiFi, GPS-Arduino)

If you don't want RTK, you don't have to connect the Wi-Fi module.

You must set how many times you want to receive imu data in one second.  **(for_arduino 84th line, while(n<22))** **You must set it to not exceed 1000ms.**
