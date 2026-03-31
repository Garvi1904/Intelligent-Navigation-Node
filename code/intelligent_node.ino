#include <SoftwareSerial.h>
#include <Wire.h>
#include <MPU6050.h>
const int RXPin = 4;
const int TXPin = 3;
SoftwareSerial ss(RXPin, TXPin);
MPU6050 mpu;
const int hallPin = 7;
String nmeaLine = "";
float latitude = 0.0;
float longitude = 0.0;
bool gpsFix = false;
void setup() {
 Serial.begin(115200);
 ss.begin(9600);
 Wire.begin();
 mpu.initialize();
 pinMode(hallPin, INPUT);
 Serial.println("INTELLIGENT NODE STARTED");
}
void loop() {
 while (ss.available()) {
 char c = ss.read();
 if (c == '\n') {
 if (nmeaLine.startsWith("$GPRMC")) {
 parseGPS(nmeaLine);
 }
 nmeaLine = "";
 } else {
 nmeaLine += c;
 }
 }
 int hallState = digitalRead(hallPin);
 int16_t ax, ay, az;
 int16_t gx, gy, gz;
 mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
 static unsigned long lastPrint = 0;
 if (millis() - lastPrint > 1000) {
 Serial.println("======= INTELLIGENT NODE DATA =======");
 if (gpsFix) {
 Serial.print("Latitude : ");
 Serial.println(latitude, 6);
 Serial.print("Longitude : ");
 Serial.println(longitude, 6);
 } else {
 Serial.println("GPS Status : Waiting for Fix...");
 }
 Serial.print("Hall Sensor: ");
 Serial.println(hallState == LOW ? "Magnet Detected" : "No Magnet");
 Serial.println("--- IMU Data ---");
 Serial.print("Accel X: "); Serial.print(ax);
 Serial.print(" Y: "); Serial.print(ay);
 Serial.print(" Z: "); Serial.println(az);
 Serial.print("Gyro X: "); Serial.print(gx);
 Serial.print(" Y: "); Serial.print(gy);
 Serial.print(" Z: "); Serial.println(gz);
 Serial.println("=====================================");
 Serial.println();
 lastPrint = millis();
 }
}
void parseGPS(String data) {
 int commaIndex[12];
 int index = 0;
 for (int i = 0; i < data.length(); i++) {
 if (data.charAt(i) == ',') {
 commaIndex[index++] = i;
 }
 }
 String status = data.substring(commaIndex[1] + 1, commaIndex[2]);
 if (status == "A") {
 String lat = data.substring(commaIndex[2] + 1, commaIndex[3]);
 String latDir = data.substring(commaIndex[3] + 1, commaIndex[4]);
 String lon = data.substring(commaIndex[4] + 1, commaIndex[5]);
 String lonDir = data.substring(commaIndex[5] + 1, commaIndex[6]);
 latitude = convertToDecimal(lat);
 longitude = convertToDecimal(lon);
 if (latDir == "S") latitude *= -1;
 if (lonDir == "W") longitude *= -1;
 gpsFix = true;
 } else {
 gpsFix = false;
 }
}
float convertToDecimal(String raw) {
 float value = raw.toFloat();
 int degrees = (int)(value / 100);
 float minutes = value - (degrees * 100);
 return degrees + (minutes / 60.0);
