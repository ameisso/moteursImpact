#define DMX_FIRST_ADDRESS 1
#define LED_PIN 13
#define SPEED_PIN 3
#define MIN_SPEED 81
#define DEBUG

#include <Arduino.h>

#ifndef DEBUG
#include <DMXSerial.h>
#endif



void blinkLed(int times);
void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(SPEED_PIN, OUTPUT);
  analogWrite(SPEED_PIN, 0);
  blinkLed(3);
#ifdef DEBUG
  Serial.begin(57600);
  delay(1000);
  Serial.println("____DMX MOTEURS IMPACT___ ");
  Serial.print("DMX address for speed is :"); Serial.println(DMX_FIRST_ADDRESS);
#else
  DMXSerial.init(DMXController);
#endif
}

void loop()
{
#ifdef DEBUG
  if (Serial.available() > 0)
  {
    int incomingByte = 0;
    incomingByte = Serial.read();
    if (incomingByte != 97)
    {
      incomingByte  = map(incomingByte, 97, 122, MIN_SPEED, 255);
    }
    else
    {
      incomingByte = 0;
    }
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
    analogWrite(SPEED_PIN, incomingByte);
  }
#else
  unsigned long lastPacket = DMXSerial.noDataSince();
  if (lastPacket < 1000 )
  {
    int dmxValue = DMXSerial.read(DMX_FIRST_ADDRESS);
    if (dmxValue > 0)
    {
      dmxValue = map(dmxValue, 0, 255, MIN_SPEED, 255);
    }
    analogWrite(SPEED_PIN, dmxValue);
  }
  else
  {
    analogWrite(SPEED_PIN, 0);
    blink(1);
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
