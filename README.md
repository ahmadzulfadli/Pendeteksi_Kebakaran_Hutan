# Pendeteksi Kebakaran Hutan - IoT

Alat pendeteksi kebakaran hutan adalah perangkat yang dirancang untuk mengidentifikasi, memonitor, dan memberikan peringatan dini tentang potensi kebakaran hutan. Alat ini menggunakan berbagai sensor untuk mendeteksi perubahan kondisi lingkungan yang dapat mengindikasikan adanya kebakaran hutan. Berikut adalah deskripsi umum tentang alat pendeteksi kebakaran hutan:

- **Sensor Suhu**: Sensor suhu digunakan untuk mengukur suhu udara di sekitar area hutan. Peningkatan suhu yang signifikan bisa menjadi indikasi potensi kebakaran.

- **Sensor Kelembaban**: Sensor kelembaban mengukur tingkat kelembaban udara. Penurunan kelembaban yang drastis dapat menjadi tanda bahaya kebakaran.

- **Sensor Asap**: Sensor asap mendeteksi partikel asap dan gas beracun yang dihasilkan oleh kebakaran hutan. Konsentrasi asap yang tinggi dapat menjadi petunjuk kebakaran.

- **Sensor Kelembaban Tanah**: Sensor ini digunakan untuk mengukur kelembaban tanah di hutan. Kebakaran hutan sering terjadi ketika tanah sangat kering.

- **Sensor Hujan**: Sensor ini digunakan untuk mendeteksi curah hujan. Hujan dapat mengurangi risiko kebakaran dan dapat menjadi tanda bahwa bahaya telah berkurang.

## Komponen yang Dibutuhkan

- **ESP32**: Mikrokontroler untuk mengontrol dan menghubungkan semua komponen.
- **DHT21**: Sensor suhu dan kelembaban.
- **Soil Moisture Sensor**: Sensor kelembaban tanah.
- **Tipping Bucket Rain Gauge Sensor**: Sensor hujan.
- **MQ-2**: Sensor gas.
- **LoRa SX1278**: Modul komunikasi nirkabel LoRa.
- **Modul PLTS 20WP**: Modul pembangkit listrik tenaga surya.
- **Stepdown 5 V**: Konverter daya 5 V.

## Konfigurasi PIN pada Rangkaian

### ESP32

- **DHT21 (Sensor Suhu dan Kelembaban)**:
  - Pin Data DHT21 terhubung ke pin 13.

- **Soil Moisture Sensor**:
  - Pin analog dari Soil Moisture Sensor terhubung ke pin 34.

- **Tipping Bucket Rain Gauge Sensor**:
  - Pin output sensor ini terhubung ke pin 32.

- **MQ-2 (Sensor Gas)**:
  - Pin analog dari sensor MQ-2 terhubung ke pin 35.

- **LoRa SX1278**:
  - Konfigurasi pin LoRa SX1278.
    | Modul LoRa SX1278 | ESP32             |
    |-------------------|-------------------|
    | GND               | GND               |
    | 3.3V              | VCC 3.3V          |
    | D5                | NSS (Chip Select) |
    | D23               | MOSI              |
    | D19               | MISO              |
    | D18               | SCK (Serial Clock)|
    | D14               | RST (Reset)       |
    | D2                | DIO0              |
