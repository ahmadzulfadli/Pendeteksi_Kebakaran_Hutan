#include <config.h>
#include <fungsi.h>

void setup() {
  //set serial monitor to bd 115200
  Serial.begin(115200);

  // DHT
  dht.begin();

  // rain gauge
  pinMode(RAINPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RAINPIN), readTip, CHANGE);

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

  // MQ2
  mq2.setRegressionMethod(1); //_PPM =  a*ratio^b
  mq2.setA(36974);
  mq2.setB(-3.109); // Configurate the ecuation values to get LPG concentration
  /*
    Exponential regression:
    Gas    | a      | b
    H2     | 987.99 | -2.162
    LPG    | 574.25 | -2.222
    CO     | 36974  | -3.109
    Alcohol| 3616.1 | -2.675
    Propane| 658.71 | -2.168
  */
  mq2.begin(); 
  Serial.print("Calibrating please wait.");
  float calcR0 = 0;
  for (int i = 1; i <= 10; i++)
  {
    mq2.update(); // Update data, the arduino will be read the voltage on the analog pin
    calcR0 += mq2.calibrate(RatioMQ2CleanAir);
    Serial.print(".");
  }
  mq2.setR0(calcR0 / 10);
  Serial.println("  done!.");

  if (isinf(calcR0))
  {
    Serial.println("Warning: Conection issue founded, R0 is infite (Open circuit detected) please check your "
                    "wiring and supply");
    while (1)
        ;
  }
  if (calcR0 == 0)
  {
    Serial.println("Warning: Conection issue founded, R0 is zero (Analog pin with short circuit to ground) please "
                    "check your wiring and supply");
    while (1)
        ;
  }
  /*****************************  MQ CAlibration ********************************************/

  mq2.serialDebug(true);
}

void loop() {
  //millis
  unsigned long currentMillis = millis();
  static unsigned long previousMillis = 0;
  const long interval = 60000;

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    //pemanggilan fungsi untuk membaca sensor dht
    float temp, humd;
    readDhtSensor(temp, humd);

    //pemanggilan fungsi untuk membaca sensor moisture
    float moisture;
    readMoistureSensor(moisture);

    //pemanggilan fungsi untuk membaca sensor MQ2
    float co;
    readMQ4(co);

    //pemanggilan fungsi untuk mengirim data melalui lora
    sendDataLora(temp, humd, moisture,co, jumlah_tip);

    jumlah_tip = 0;
  }

}
