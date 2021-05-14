// 참조절
#include <Wire.h>

// 정의절
#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    GYRO_FULL_SCALE_250_DPS    0x00  
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00  
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18

// I2C통신 함수 정의
void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();

  Wire.requestFrom(Address, Nbytes);
  uint8_t index = 0;
  while (Wire.available())
     Data[index++] = Wire.read();
}
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}

//GPS 데이터 파싱 관련 변수 초기화
char c = ' ';
String str = "";
String targetStr = "GNGGA";
int n;

void setup() 
{
  //I2C, UART 통신 개시
  Wire.begin();
  Serial.begin(9600);
  Serial2.begin(460800);
  I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_16_G);
  I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_2000_DPS);
  I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02);
  I2CwriteByte(MAG_ADDRESS, 0x0A, 0x01);
}

void loop() 
{
  n=0;
  unsigned long millisTime = millis();
  unsigned long previousTime = 0;
  if (Serial2.available())
  {
  c = Serial2.read();
  if(c == '\n')
  {
      if(targetStr.equals(str.substring(1, 6)))
       {
        int first = str.indexOf(",");
        int two = str.indexOf(",", first+1);
        int three = str.indexOf(",", two+1);
        int four = str.indexOf(",", three+1);
        int five = str.indexOf(",", four+1);
        String curtime = str.substring(first+1,two);
        String Lat = str.substring(two+1, three);
        String Long = str.substring(four+1, five);
        String Lat1 = Lat.substring(0, 2);
        String Lat2 = Lat.substring(2);
        String Long1 = Long.substring(0, 3);
        String Long2 = Long.substring(3);
        double LatF = Lat1.toDouble() + Lat2.toDouble()/60;
        float LongF = Long1.toFloat() + Long2.toFloat()/60;
        Serial.print("GPS"); Serial.print("\t"); Serial.print(curtime); Serial.print("\t"); Serial.print(LatF,15); Serial.print("\t"); Serial.println(LongF,15);
        previousTime = millis();
        while(n<22)
        {
        
          // ---  Lectura acelerometro y giroscopio ---
          uint8_t Buf[14];
          I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);
        
          // Convertir registros acelerometro
          int16_t ax = -(Buf[0] << 8 | Buf[1]);
          int16_t ay = -(Buf[2] << 8 | Buf[3]);
          int16_t az = Buf[4] << 8 | Buf[5];
        
          // Convertir registros giroscopio
          int16_t gx = -(Buf[8] << 8 | Buf[9]);
          int16_t gy = -(Buf[10] << 8 | Buf[11]);
          int16_t gz = Buf[12] << 8 | Buf[13];
        
        
        
          // ---  Lectura del magnetometro ---
          uint8_t ST1;
          I2CwriteByte(MAG_ADDRESS,0x0A,0x01);  
          do
          {
             I2Cread(MAG_ADDRESS, 0x02, 1, &ST1);
          } while (!(ST1 & 0x01));
        
          uint8_t Mag[7];
          I2Cread(MAG_ADDRESS, 0x03, 7, Mag);
        
        
          // Convertir registros magnetometro
          int16_t mx = -(Mag[3] << 8 | Mag[2]);
          int16_t my = -(Mag[1] << 8 | Mag[0]);
          int16_t mz = -(Mag[5] << 8 | Mag[4]);
        
        
          // --- Mostrar valores ---
        
          // Acelerometro
          Serial.print("IMU");
          Serial.print("\t");
          Serial.print(ax, DEC);
          Serial.print("\t");
          Serial.print(ay, DEC);
          Serial.print("\t");
          Serial.print(az, DEC);
          Serial.print("\t");
        
          // Giroscopio
          Serial.print(gx, DEC);
          Serial.print("\t");
          Serial.print(gy, DEC);
          Serial.print("\t");
          Serial.print(gz, DEC);
          Serial.print("\t");
        
        
          // Magnetometro
          Serial.print(mx, DEC);
          Serial.print("\t");
          Serial.print(my, DEC);
          Serial.print("\t");
          Serial.print(mz, DEC);
          Serial.print("\t");
         
          // Fin medicion
          millisTime = millis() - previousTime;
          Serial.println(millisTime);
          n=n+1;
        }
       }
       str ="";
  }
   else
   {
    str += c;
  }
  }


}
