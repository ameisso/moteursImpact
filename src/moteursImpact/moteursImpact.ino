#include <Arduino.h>
#include <DMXSerial.h>

#define DMX_FIRST_ADDRESS 1
#define LED_PIN 13
#define SPEED_PIN 3
#define MIN_SPEED 81
//#define DEBUG

void blinkLed(int times);
void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(SPEED_PIN, OUTPUT);
  blinkLed(3);
#ifdef DEBUG
  Serial.begin(57600);
  delay(1000);
  Serial.println("____DMX MOTEURS IMPACT___ ");
  Serial.print("DMX address for speed is :"); Serial.println(DMX_FIRST_ADDRESS);
#endif
  DMXSerial.init(DMXController);
}

void loop()
{
  unsigned long lastPacket = DMXSerial.noDataSince();
  if (lastPacket < 1000 )
  {
    int dmxValue = DMXSerial.read(DMX_FIRST_ADDRESS);
    dmxValue = map(dmxValue, 0, 255, MIN_SPEED, 255);
    analogWrite(SPEED_PIN, dmxValue);
  }
#ifdef DEBUG
  if (Serial.available() > 0)
  {
    int incomingByte = 0;
    incomingByte = Serial.read();
    incomingByte  = map(incomingByte, 97, 122, 0, 255);
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
    analogWrite(SPEED_PIN, incomingByte);
  }
#endif
}

void blinkLed(int times)
{
  for (int i = 0 ; i < times ; i ++)
  {
    digitalWrite(LED_PIN, HIGH);
    delay(400);
    digitalWrite(LED_PIN, LOW);
    delay(400);
  }
}
