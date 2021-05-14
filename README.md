# Receiving-GPS-INS-DATA
https://youtu.be/ZbwTwUUQbUk


# Reference
Parsing GPS DATA using Arduino

https://clemencyking.tistory.com/9

NTRIP Client for Arduino

https://github.com/GLAY-AK2/NTRIP-client-for-Arduino


# How to use

1. Connect Wi-Fi Module TX to GPS Module RX

2. Connect GPS Module TX to Arduino DUE RX2

3. Connect IMU sensor to Arduino DUE (I2C:20,21)

4. Go to https://github.com/GLAY-AK2/NTRIP-client-for-Arduino

5. Edit the code for your application. and upload it on Wi-fi board.

6. Download 'for_arduino.ino' and upload it


#Precautions

Set baudrate with GPS-WiFi, GPS-Arduino

If you don't want RTK, you don't have to connect the Wi-Fi module.