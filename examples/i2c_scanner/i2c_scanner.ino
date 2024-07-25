#include <Wire.h>
#define SDA_PIN 38
#define SCL_PIN 39

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");

  Wire.begin(SDA_PIN, SCL_PIN);
}

void loop() {
  byte error, address;
  int nDevices = 0;

  for (address = 1; address < 127; address++) {
    // The I2C scanner sends a write request followed by a stop to see if a device responds
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      Serial.println(address, HEX);
      nDevices++;
    } else if (error == 4) {
      // I2C error: errno 4 indicates that the slave did not acknowledge the address
      Serial.print("Unknown error at address 0x");
      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }

  delay(5000); // Wait 5 seconds before scanning again (optional)
}
