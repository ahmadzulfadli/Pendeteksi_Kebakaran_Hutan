// Curah hujan 1 mm adl jml air hujan yang jatuh di permukaan per satuan luas (m2) dengan volume sbnyk 1 liter tanpa ada yang menguap, meresap/mengalir.

// Tinggi curah hujan (cm) = volume yang dikumpulkan (mL) / area pengumpulan (cm2)
// Luas kolektor phi x r kuadrat 3.14 x (3.55x3.55) = 39,57 cm2
// Koleksi per ujung tip kami dapat dengan cara menuangkan 100ml air ke kolektor kemudian menghitung berapa kali air terbuang dari tip,
// Dlm perhitungan yang kami lakukan air terbuang sebanyak 70 kali. 100ml / 70= 1.42mL per tip.
// Jadi 1 tip bernilai 1.42 / 39,57 = 0,03cm atau 0.30 mm curah hujan.

// - Per tip 0,30 mm.
// - Tegangan 5v/3.3v.
// - Menggunakan pin interrupt.

#ifndef NODE_PENDETEKSI_KEBAKARAN_HUTAN_FUNGSI_H
#define NODE_PENDETEKSI_KEBAKARAN_HUTAN_FUNGSI_H
#include <config.h>

// KIRIM DATA KE SERVER
void sendDataToServer(String temp, String humd, String moist, String co, String jumlahTip){
    WiFiClient client;
    if (!client.connect(host, port))
    {
        Serial.println(">>> Connection failed !");
        return;
    }

    // pengiriman nilai sensor ke web server
    String apiUrl = "http://intai.com/crud/kirim_data.php?";
    apiUrl += "mode=save";
    apiUrl += "&temp=" + temp;
    apiUrl += "&humd=" + humd;
    apiUrl += "&moist=" + moist;
    apiUrl += "&co=" + co;
    apiUrl += "&jumlah_tip=" + jumlahTip;

    // Set header Request
    client.print(String("GET ") + apiUrl + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");

    // Pastikan tidak berlarut-larut
    unsigned long timeout = millis();
    while (client.available() == 0)
    {
        if (millis() - timeout > 3000)
        {
            Serial.println(">>> Client Timeout !");
            Serial.println(">>> Operation failed !");
            client.stop();
            return;
        }
    }

    // Baca hasil balasan dari PHP
    while (client.available())
    {
        String line = client.readStringUntil('\r');
        Serial.println(line);
    }
}

#endif