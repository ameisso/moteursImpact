#include <DmxReceiver.h>
DmxReceiver DMX = DmxReceiver();

void setup() {
        DMX.begin();
        Serial.begin(115200);
}

void loop() {
  DMX.bufferService();
  delay(2);
  if (DMX.newFrame())
        {
          Serial.println(DMX.getDimmer(1), DEC);
        }
}


