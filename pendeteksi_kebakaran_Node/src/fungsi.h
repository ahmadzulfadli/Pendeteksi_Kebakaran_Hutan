#ifndef PENDETEKSI_KEBAKARAN_HUTAN_FUNGSI_H
#define PENDETEKSI_KEBAKARAN_HUTAN_FUNGSI_H
#include <config.h>

void readDhtSensor(float &temp, float &humd)
{
    // DHT22
    temp = dht.readTemperature();
    humd = dht.readHumidity();
    
}

void readMoistureSensor(float &moisture){
    // moisture
    float result = 0;
    float value = 0;

    for (int i = 0; i < 30; i++)
    {
        float readValue = analogRead(MOISTUREPIN)-1690;
        if (readValue < 0){
            readValue = 0;
        }

        Serial.println(readValue);
        value += readValue;
        delay(1000);
    }

    result = value / 30;
    // persentase moisture dengan nilai max 2050
    moisture = (100 - ( (result/2405.00) * 100 ));
}

void readRainGuegeSensor(float &intensity){

}

void readMQ4(float &co){
    float value = 0;

    for (int i = 0; i < 20; i++)
    {
        mq2.update();
        float readValue = mq2.readSensor();

        Serial.println(readValue);
        value += readValue;
        delay(1000);
    }

    co = value / 20;
}

void sendDataLora(float temp, float humd, float moisture, float co, float intensity){

    //display to serial monitor
    Serial.println("====== Data ======");
    Serial.print("Temperature: ");
    Serial.println(temp);
    Serial.print("Humidity: ");
    Serial.println(humd);
    Serial.print("Moisture: ");
    Serial.println(moisture);
    Serial.print("CO: ");
    Serial.println(co);
    Serial.print("Intensity: ");
    Serial.println(intensity);
    Serial.println("====== End Data ======");
    // LoRa
    // String data = String(temp) + "," + String(humd) + "," + String(moisture) + "," + String(intensity);
    // LoRa.beginPacket();
    // LoRa.print(data);
    // LoRa.endPacket();
    // Serial.println("====== Paket Send =======");
    // Serial.print("Mengirim Data: " + data);
    // Serial.println("\n====== End Paket =======");
    
    //menghidupkan led
    digitalWrite(LED2, HIGH);
}

#endif