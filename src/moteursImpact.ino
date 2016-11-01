#include <Arduino.h>
#include <DmxReceiver.h>
DmxReceiver DMX = DmxReceiver();


#define DMX_FIRST_ADDRESS 1
#define LED_PIN 13
#define SPEED_PIN 3
#define DEBUG

void blinkLed(int times);
void setup()
{
  pinMode(LED_PIN,OUTPUT);
  pinMode(SPEED_PIN,OUTPUT);
  blinkLed(3);
  #ifdef DEBUG
  Serial.begin(9600);
  delay(1000);
  Serial.println("____DMX MOTEURS IMPACT___ ");
  Serial.print("DMX address for speed is :");serial.println("DMX_FIRST_ADDRESS");

  #endif
}

void loop()
{
  DMX.bufferService();
  delay(2);
  if (DMX.newFrame())
  {
    #ifdef DEBUG
    Serial.print("Speed :");  Serial.println(DMX.getDimmer(DMX_FIRST_ADDRESS), DEC);
    analogWrite(SPEED_PIN,DMX.getDimmer(DMX_FIRST_ADDRESS));
    #endif
  }
}

void blinkLed(int times)
{
  for(int i = 0 ; i < times ; i ++)
  {
    digitalWrite(LED_PIN, HIGH);
    delay(400);
    digitalWrite(LED_PIN, LOW);
    delay(400);
  }
}
