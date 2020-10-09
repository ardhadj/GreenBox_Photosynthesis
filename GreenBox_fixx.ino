#include <Wire.h> 
#include <DS3231.h>
#include "CO2Sensor.h"
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT22

// Set the LCD address to 0x27 for a 16 chars and 2 line display
CO2Sensor co2Sensor(A0, 0.99, 100);
DS3231  rtc(SDA, SCL);
int ledPin = 3;  // LED di PIN 3
File myFile;
Time T;
Time T1;
DHT dht(DHTPIN, DHTTYPE);
const int AirValue = 778;
const int WaterValue = 365;
int CO2MAX = 1500;
int CO2MIN = 350;
int val = 0;
int soilMoistureValue = 0;
int soilMoisturePercent = 0;
//set Data Logger
int pinCS = 10;

void setup()
{
  Serial.begin(9600);
  dht.begin();
  rtc.begin();
  co2Sensor.calibrate();
  pinMode(pinCS, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.println(FreeRam());
    if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
  myFile = SD.open("G6.txt", FILE_WRITE);
   while (millis() < 5000){
   val = co2Sensor.read();
     if (val > CO2MAX) {
      CO2MAX = val;
    }
    if (val < CO2MIN) {
      CO2MIN = val;
    }
  }
}

void loop()
{         T = rtc.getTime();
     soilMoistureValue = analogRead(A1);  //put Sensor insert into soil
  soilMoisturePercent = map (soilMoistureValue, AirValue, WaterValue, 0, 100); //ubah jadi percent val, low, high, low, high
  int HU = dht.readHumidity();
  val = co2Sensor.read();
  val = map(val, CO2MIN, CO2MAX, 350, 1500);
  val = constrain(val, 350, 1500);
  int Tempt = dht.readTemperature();
  if (isnan(HU) ||  isnan(Tempt) ) {
    Serial.println("Failed DHT sensor!");
    return;
  }
    if (T.min == 0 && (T.sec >= 1 && T.sec <= 2)){
    Serial.println(FreeRam());
    myFile = SD.open("G7.txt", FILE_WRITE);
    myFile.print(T.date);
    myFile.print('/');
    myFile.print(rtc.getMonthStr());
    myFile.print('/');
    myFile.print(T.year);
    myFile.print(" ");
    myFile.print(T.hour);
    myFile.print(":");
    myFile.print(T.min);
    myFile.print(" ");
    myFile.print(HU);
    myFile.print("%");
    myFile.print(" ");
    myFile.print(soilMoisturePercent);
    myFile.print("%");
    myFile.print(" ");
    myFile.print(Tempt);
    myFile.print(" ");
    myFile.println(val);
    myFile.close();
  }
    if (T.min == 15 && (T.sec >= 1 && T.sec <= 2)){
    Serial.println(FreeRam());
    myFile = SD.open("G7.txt", FILE_WRITE);
    myFile.print(T.date);
    myFile.print('/');
    myFile.print(rtc.getMonthStr());
    myFile.print('/');
    myFile.print(T.year);
    myFile.print(" ");
    myFile.print(T.hour);
    myFile.print(":");
    myFile.print(T.min);
    myFile.print(" ");
    myFile.print(HU);
    myFile.print("%");
    myFile.print(" ");
    myFile.print(soilMoisturePercent);
    myFile.print("%");
    myFile.print(" ");
    myFile.print(Tempt);
    myFile.print(" ");
    myFile.println(val);
    myFile.close();
  }if (T.min == 30 && (T.sec >= 1 && T.sec <= 2)){
    Serial.println(FreeRam());
    myFile = SD.open("G7.txt", FILE_WRITE);
    myFile.print(T.date);
    myFile.print('/');
    myFile.print(rtc.getMonthStr());
    myFile.print('/');
    myFile.print(T.year);
    myFile.print(" ");
    myFile.print(T.hour);
    myFile.print(":");
    myFile.print(T.min);
    myFile.print(" ");
    myFile.print(HU);
    myFile.print("%");
    myFile.print(" ");
    myFile.print(soilMoisturePercent);
    myFile.print("%");
    myFile.print(" ");
    myFile.print(Tempt);
    myFile.print(" ");
    myFile.println(val);
    myFile.close();
  }if (T.min == 45 && (T.sec >= 1 && T.sec <= 2)){
    Serial.println(FreeRam());
    myFile = SD.open("G7.txt", FILE_WRITE);
    myFile.print(T.date);
    myFile.print('/');
    myFile.print(rtc.getMonthStr());
    myFile.print('/');
    myFile.print(T.year);
    myFile.print(" ");
    myFile.print(T.hour);
    myFile.print(":");
    myFile.print(T.min);
    myFile.print(" ");
    myFile.print(HU);
    myFile.print("%");
    myFile.print(" ");
    myFile.print(soilMoisturePercent);
    myFile.print("%");
    myFile.print(" ");
    myFile.print(Tempt);
    myFile.print(" ");
    myFile.println(val);
    myFile.close();
  }
  GETLED();
}

void GETLED(){
  T = rtc.getTime();
    if ((T.hour >= 5) && (T.hour <= 17)){
    digitalWrite(ledPin, LOW);
   }else{
    digitalWrite(ledPin, HIGH); 
   }
}
