#include <config.h>
#include <fungsi.h>

void setup() {
  //set serial monitor to bd 115200
  Serial.begin(115200);

  // DHT
  dht.begin();

  // LORA
  while (!Serial)
    ;
  Serial.println("LoRa Sender");
  LoRa.setPins(SS, RST, DIO0);
  while (!LoRa.begin(BAND))
  {
    Serial.println(".");
    delay(500);
  }
  LoRa.setTxPower(TX_POWER);
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(BW);
  LoRa.setCodingRate4(5);
  LoRa.enableCrc();
  Serial.println("LoRa Transmitter Ready!");

  // LED
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  //millis
  unsigned long currentMillis = millis();
  static unsigned long previousMillis = 0;
  const long interval = 10000;

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    //pemanggilan fungsi untuk membaca sensor dht
    float temp, humd;
    readDhtSensor(temp, humd);

    //pemanggilan fungsi untuk membaca sensor moisture
    float moisture;
    readMoistureSensor(moisture);

    //pemanggilan fungsi untuk membaca sensor rain gauge
    float intensity;
    readRainGuegeSensor(intensity);

    //pemanggilan fungsi untuk mengirim data melalui lora
    sendDataLora(temp, humd, moisture, intensity);

  }

  //menghidupkan led
  digitalWrite(LED1, HIGH);
  delay(500);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
}
