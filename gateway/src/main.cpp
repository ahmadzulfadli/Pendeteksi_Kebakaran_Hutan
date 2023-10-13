#include <config.h>
#include <fungsi.h>

void setup() {
  //set serial monitor to bd 115200
  Serial.begin(115200);

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
  Serial.println("LoRa Reciver Ready!");

  // Networking
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

}

void loop() {

    // penerimaan lora
    String receivedData = "";

    int packetSize = LoRa.parsePacket();
    if (packetSize != 0)
    {
        Serial.print("Received packet '");

        while (LoRa.available())
        {
            receivedData += (char)LoRa.read();
        }

        Serial.println(receivedData);

        char stringData[receivedData.length() + 1];
        strcpy(stringData, receivedData.c_str());

        char *ptr = strtok(stringData, ",");
        int i = 0;
        String data[6];

        while (ptr != NULL)
        {
            data[i] = String(ptr);
            i++;
            ptr = strtok(NULL, ",");
        }

        String temp = data[0];
        String humd = data[1];
        String moist = data[2];
        String co = data[3];
        String jumlahTip = data[4];

        Serial.print("' with RSSI ");
        Serial.println(LoRa.packetRssi());

        Serial.print("Temperature: ");
        Serial.println(temp);
        Serial.print("Humidity: ");
        Serial.println(humd);
        Serial.print("Moisture: ");
        Serial.println(moist);
        Serial.print("CO: ");
        Serial.println(co);
        Serial.print("Jumlah Tip: ");
        Serial.println(jumlahTip);

        // kirim ke server
        // sendDataToServer(temp, humd, moist, co, jumlahTip);
    }

}
