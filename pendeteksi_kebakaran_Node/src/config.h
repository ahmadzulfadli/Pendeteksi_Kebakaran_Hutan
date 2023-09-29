#ifndef PENDETEKSI_KEBAKARAN_HUTAN_CONFIG_H
#define PENDETEKSI_KEBAKARAN_HUTAN_CONFIG_H
#include <config.h>

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "MQ-Sensor-SOLDERED.h"
#include <SPI.h>
#include <LoRa.h>

// konfigurasi dht
#define DHTPIN 13
#define DHTTYPE DHT21
DHT dht(DHTPIN, DHTTYPE);

// konfigurasi moisture sensor
#define MOISTUREPIN 34

// konfigurasi rain gauge

// lora
#define SS 5
#define RST 14
#define DIO0 2

const long BAND = 433E6;     // frekuensi operasi LoRa
const int TX_POWER = 17;     // daya output LoRa
const long BAUD_RATE = 9600; // kecepatan data LoRa
const int BW = 125E3;

// MQ4
#define RatioMQ2CleanAir (9.83) // RS / R0 = 9.83 ppm
#define SENSOR_ANALOG_PIN 35   // D35
MQ2 mq2(SENSOR_ANALOG_PIN);

// konfigurasi dua led
#define LED1 12
#define LED2 27

#endif