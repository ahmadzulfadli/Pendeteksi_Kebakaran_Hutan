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

    
    // pengiriman nilai sensor ke web server
    String apiUrl = "apiEndpoint";
    apiUrl += "mode=save";
    apiUrl += "&temperature=" + temp;
    apiUrl += "&humidity=" + humd;
    apiUrl += "&moisture=" + moist;
    apiUrl += "&co=" + co;
    apiUrl += "&count_tip=" + jumlahTip;

    // Make the HTTP GET request
    HTTPClient http;
    http.begin(apiUrl);

    // Send the GET request
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0)
    {
        Serial.printf("HTTP Response code: %d\n", httpResponseCode);
        String response = http.getString();
        Serial.println(response);
    }
    else
    {
        Serial.printf("HTTP GET request failed, error: %s\n", http.errorToString(httpResponseCode).c_str());
    }

    http.end();
}

#endif