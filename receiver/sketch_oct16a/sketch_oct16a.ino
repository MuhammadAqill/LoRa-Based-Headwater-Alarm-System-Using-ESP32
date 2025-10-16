// Receiver

#include <SPI.h>
#include <LoRa.h>

#define SS 18    // Mengawal bila LoRa aktif dalam komunikasi SPI.
#define RST 14   // Menetapkan semula (reset) modul LoRa bila mula hidup atau bila error.
#define DIO0 26  // Pin interrupt LoRa — memberitahu ESP32 bila sesuatu peristiwa LoRa berlaku.

void setup() {

  Serial.begin(115200);

  while (!Serial);

  Serial.println("Initializing LoRa...");

  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(470E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa init OK!");
  Serial.println("Waiting messege....");

}

void loop() {

  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    String incoming = "";
    while (LoRa.available()) {
      incoming += (char)LoRa.read();
    }
    
    Serial.println(incoming);

  }

}
