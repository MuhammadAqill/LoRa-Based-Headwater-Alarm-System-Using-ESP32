// Transmitter

#include <SPI.h>
#include <LoRa.h>

#define SS 18    // Mengawal bila LoRa aktif dalam komunikasi SPI.
#define RST 14   // Menetapkan semula (reset) modul LoRa bila mula hidup atau bila error.
#define DIO0 26  // Pin interrupt LoRa — memberitahu ESP32 bila sesuatu peristiwa LoRa berlaku.


#define TRIG_PIN 12
#define ECHO_PIN 13

void setup() {
  
  /* ----------------------------------------- Initialize serial communication at 115200 bits per second: ---------------------------------------*/

  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  LoRa.setPins(SS, RST, DIO0);

  while (!Serial);

  Serial.println("Initializing LoRa...");

  if (!LoRa.begin(470E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa init OK!");

}

void loop() {

  // Ultrasonic reading
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2; // cm

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Hantar melalui LoRa
  LoRa.beginPacket();
  LoRa.print("Distance: ");
  LoRa.print(distance);
  LoRa.println(" cm");
  LoRa.endPacket();

}