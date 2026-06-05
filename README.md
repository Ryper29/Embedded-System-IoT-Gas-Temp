# 🌡️ ESP8266 IoT Gas & Temperature Monitor

Proyek **Embedded System IoT** berbasis **ESP8266** yang memantau kualitas udara (gas/asap), suhu, dan kelembapan secara real-time menggunakan sensor **MQ2** dan **DHT22**, dengan notifikasi melalui **buzzer** dan **LED**, serta visualisasi data melalui aplikasi **Blynk**.

---

## 📦 Komponen yang Digunakan

| Komponen | Keterangan |
|----------|------------|
| **ESP8266** (NodeMCU/Wemos D1) | Mikrokontroler utama dengan koneksi WiFi |
| **Sensor MQ2** | Mendeteksi gas LPG, asap, CO, dan uap mudah terbakar |
| **Sensor DHT22** | Mengukur suhu dan kelembapan udara |
| **Buzzer** | Alarm aktif saat gas berbahaya terdeteksi |
| **LED** | Indikator visual saat suhu atau kelembapan di luar batas normal |
| **Blynk (IoT Platform)** | Dashboard monitoring & kontrol via smartphone |

---

## 🔌 Pin yang Digunakan

| Komponen | Pin ESP8266 |
|----------|-------------|
| Sensor MQ2 (Analog Out) | `A0` |
| Sensor DHT22 (Data) | `D7` |
| Buzzer | `D5` |
| LED | `D1` |

---

## 📊 Virtual Pin Blynk

| Virtual Pin | Fungsi |
|-------------|--------|
| **V0** | Nilai Suhu (°C) |
| **V1** | Nilai Kelembapan (%) |
| **V2** | Nilai Sensor MQ2 (raw ADC) |
| **V3** | Status Gas (`Aman` / `Bahaya! Gas/Asap Terdeteksi`) |
| **V4** | Status Suhu (`Suhu Normal` / `Suhu Tinggi` / `Sensor Suhu Error`) |
| **V5** | Status Kelembapan (`Kelembapan Normal` / `Kelembapan Tidak Normal` / `Sensor Kelembapan Error`) |

---

## ⚙️ Logika Threshold

| Parameter | Nilai Default |
|-----------|--------------|
| Batas Gas MQ2 | `> 1000` → Bahaya |
| Batas Suhu | `> 30.0°C` → Suhu Tinggi |
| Batas Kelembapan Min | `< 30%` → Tidak Normal |
| Batas Kelembapan Max | `> 80%` → Tidak Normal |

---

## 🚀 Cara Penggunaan

### 1. Clone Repository
```bash
git clone https://github.com/Ryper29/Embedded-System-IoT-Gas-Temp.git
cd Embedded-System-IoT-Gas-Temp
```

### 2. Ganti Placeholder Blynk & WiFi

Buka file `esp8266_blynk_mq2_dht22.ino`, lalu ganti bagian berikut dengan data asli Anda:

```cpp
#define BLYNK_TEMPLATE_ID "ISI_TEMPLATE_ID"       // ← Ganti dengan Template ID Blynk Anda
#define BLYNK_TEMPLATE_NAME "ISI_TEMPLATE_NAME"   // ← Ganti dengan Template Name Blynk Anda
#define BLYNK_AUTH_TOKEN "ISI_AUTH_TOKEN"         // ← Ganti dengan Auth Token Blynk Anda

char ssid[] = "NAMA_WIFI";       // ← Ganti dengan nama WiFi Anda
char pass[] = "PASSWORD_WIFI";   // ← Ganti dengan password WiFi Anda
```

> ⚠️ **PENTING:** Jangan pernah commit file dengan token atau password asli ke repository publik!

### 3. Install Library Arduino

Pastikan library berikut sudah terinstall di Arduino IDE:
- `ESP8266WiFi` (bawaan ESP8266 Board Package)
- `BlynkSimpleEsp8266` (via Library Manager: `Blynk`)
- `DHT sensor library` (by Adafruit)

### 4. Upload ke Board

- Pilih board: **NodeMCU 1.0 (ESP-12E Module)** atau sesuai board ESP8266 Anda
- Pilih port COM yang sesuai
- Upload sketch

### 5. Setup Blynk Dashboard

Di aplikasi Blynk, buat datastream untuk setiap virtual pin (V0–V5) sesuai tabel di atas, lalu tambahkan widget seperti **Gauge**, **Label**, atau **SuperChart** untuk memantau data secara real-time.

---

## 📁 Struktur File

```
Embedded-System-IoT-Gas-Temp/
├── esp8266_blynk_mq2_dht22.ino   # Sketch utama Arduino
└── README.md                      # Dokumentasi proyek
```

---

## 📜 Lisensi

Proyek ini dibuat untuk keperluan akademik mata kuliah **Embedded System / IoT**.
