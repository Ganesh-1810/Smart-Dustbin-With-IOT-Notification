#include <LiquidCrystal.h>
LiquidCrystallcd(13,12,11,10,9,8);
inttrigPin = 7; // Trigger
intechoPin = 6; // Echo
int m1 = 2; //m1
int m2 = 3; //m2
int s1=0;
constintsensorPin=0;
constint threshold= 100;
intultra_cm;
voidiot_init();
void send_iot1();
void send_iot2();
void send_iot3();
intultra_sonic();
void motor(unsigned int s);
void setup()
{
pinMode(trigPin, OUTPUT);
pinMode(m1, OUTPUT);
pinMode(m2, OUTPUT);
pinMode(echoPin, INPUT);
lcd.begin(16, 2);
lcd.print("DustBin:1 status");
lcd.setCursor(0,2);
lcd.print("initialize...");
Serial.begin(9600);
iot_init();
lcd.setCursor(0,2);
lcd.print(" "); 
}
void loop()
{
intval= analogRead(sensorPin);
if (val>= threshold)
{
digitalWrite(m1, HIGH);
digitalWrite(m2, LOW);
delay(2000);
digitalWrite(m2, LOW);
digitalWrite(m1, LOW);
delay(4000);
digitalWrite(m1, LOW);
digitalWrite(m2, HIGH);
delay(2000);
}
else
{
digitalWrite(m1, LOW);
digitalWrite(m2, LOW);
}
ultra_cm=ultra_sonic();
 if(ultra_cm<10)
 {
lcd.setCursor(0,2);
lcd.print("Full ");
 send_iot1();
// delay(500);
 }
 else if(ultra_cm>10&&ultra_cm<20)
 {
lcd.setCursor(0,2);
lcd.print("Half ");
 send_iot2();
// delay(500);
 }
 else if(ultra_cm>20&&ultra_cm<30)
 {
lcd.setCursor(0,2);
lcd.print("Empty");
 send_iot3(); 
 //delay(500);
 }
}
voidiot_init()
{
Serial.write("AT");
Serial.write(0x0D);Serial.write(0x0A);
delay(2000);
Serial.write("AT+CWMODE?");
Serial.write(0x0D);Serial.write(0x0A);
delay(2000);
Serial.write("AT+CWJAP=");
Serial.write('"');delay(10);
Serial.write("prdsnla");delay(10); //UID
Serial.write('"');delay(10);
Serial.write(',');delay(10);
Serial.write('"');delay(10);
Serial.write("12345678");delay(10); //PWD
Serial.write('"');delay(10);
Serial.write(0x0D);Serial.write(0x0A);
delay(10000);
Serial.write("AT+CIPMUX=1");
Serial.write(0x0D);Serial.write(0x0A);
delay(2000);
}
void send_iot1()gbgg
{
Serial.write("AT+CIPSERVER=1,80");
Serial.write(0x0D);Serial.write(0x0A);
delay(4000);
lcd.setCursor(9,2);
lcd.print("iotUD");
delay(4000);
lcd.setCursor(9,2);
lcd.print(" ");
Serial.write("AT+CIPSEND=0,14");delay(10);
Serial.write(0x0D);Serial.write(0x0A);
delay(500);
Serial.write("DustBin-1:Full"); //data to be transmit
delay(500);
Serial.write("AT+CIPCLOSE=0");
Serial.write(0x0D);Serial.write(0x0A);
 //delay(5000);
}
void send_iot2()
{
Serial.write("AT+CIPSERVER=1,80");
Serial.write(0x0D);Serial.write(0x0A);
delay(4000);
lcd.setCursor(9,2);
lcd.print("iotUD");
delay(4000);
lcd.setCursor(9,2);
lcd.print(" ");
Serial.write("AT+CIPSEND=0,14");delay(10);
Serial.write(0x0D);Serial.write(0x0A);
delay(500);
Serial.write("DustBin-1:Half"); //data to be transmit
delay(500);
Serial.write("AT+CIPCLOSE=0");
Serial.write(0x0D);Serial.write(0x0A);
// delay(5000);
}
void send_iot3()
{
Serial.write("AT+CIPSERVER=1,80");
Serial.write(0x0D);Serial.write(0x0A);
delay(4000);
lcd.setCursor(9,2);
lcd.print("iotUD");
delay(4000);
lcd.setCursor(9,2);
lcd.print(" ");
Serial.write("AT+CIPSEND=0,15");delay(10);
Serial.write(0x0D);Serial.write(0x0A);
delay(500);
Serial.write("DustBin-1:Empty"); //data to be transmit
delay(500);
Serial.write("AT+CIPCLOSE=0");
Serial.write(0x0D);Serial.write(0x0A);
 //delay(5000);
}
intultra_sonic()
{
longduration,cm;
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
 cm = (duration/2) / 29.1;
 return cm;
}