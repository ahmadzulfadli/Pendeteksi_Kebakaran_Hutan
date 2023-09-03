#ifndef PENDETEKSI_KEBAKARAN_HUTAN_FUNGSI_H
#define PENDETEKSI_KEBAKARAN_HUTAN_FUNGSI_H
#include <config.h>

void readDhtSensor(float &temp, float &humd)
{
    // DHT22
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // display to serial monitor
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
}

void readMoistureSensor(float &moisture){
    // moisture
    float readValue = analogRead(MOISTUREPIN);

    moisture = map(readValue, 4095, 0, 0, 100);
}

void readRainGuegeSensor(float &intensity){

}

void sendDataLora(float temp, float humd, float moisture, float intensity){
    // LoRa
    String data = String(temp) + "," + String(humd) + "," + String(moisture) + "," + String(intensity);
    LoRa.beginPacket();
    LoRa.print(data);
    LoRa.endPacket();
    Serial.println("====== Paket Send =======");
    Serial.print("Mengirim Data: " + data);
    Serial.println("\n====== End Paket =======");
    
    //menghidupkan led
    digitalWrite(LED2, HIGH);
}

#endif