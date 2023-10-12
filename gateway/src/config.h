#ifndef NODE_PENDETEKSI_KEBAKARAN_HUTAN_CONFIG_H
#define NODE_PENDETEKSI_KEBAKARAN_HUTAN_CONFIG_H
#include <config.h>

#include <Arduino.h>
#include <WiFi.h>
#include <LoRa.h>
#include <UrlEncode.h>
// lora
#define SS 5
#define RST 14
#define DIO0 2

const long BAND = 433E6;     // frekuensi operasi LoRa
const int TX_POWER = 17;     // daya output LoRa
const long BAUD_RATE = 9600; // kecepatan data LoRa
const int BW = 125E3;

// wifi
const char *ssid = "Ahmad Zulfadli";
const char *password = "sampoerna12";
const char *host = "192.168.80.240";
const int port = 80;


#endif