#include <DHT.h>
#include <Servo.h>

#define DHTPIN D4
#define DHTTYPE DHT22

#define MQ135_PIN A0

#define SERVO_PIN D5
#define BUZZER_PIN D6

DHT dht(DHTPIN, DHTTYPE);
Servo ventilasi;

// Batas kondisi
float suhuMaks = 30.0;   // °C
int gasMaks = 400;       // Sesuaikan setelah kalibrasi

void setup() {

  Serial.begin(115200);

  dht.begin();

  // Inisialisasi Servo
  ventilasi.attach(SERVO_PIN);
  ventilasi.write(0); // Ventilasi awal tertutup

  pinMode(BUZZER_PIN, OUTPUT);

  Serial.println("================================");
  Serial.println(" SMART KANDANG MONITORING ");
  Serial.println("================================");
}

void loop() {

  // Membaca sensor
  float suhu = dht.readTemperature();
  float kelembapan = dht.readHumidity();
  int nilaiGas = analogRead(MQ135_PIN);

  // Cek pembacaan DHT22
  if (isnan(suhu) || isnan(kelembapan)) {
    Serial.println("Gagal membaca DHT22!");
    delay(2000);
    return;
  }

  // Menampilkan data ke Serial Monitor
  Serial.println("--------------------------------");

  Serial.print("Suhu       : ");
  Serial.print(suhu);
  Serial.println(" °C");

  Serial.print("Kelembapan : ");
  Serial.print(kelembapan);
  Serial.println(" %");

  Serial.print("Gas MQ135  : ");
  Serial.println(nilaiGas);

  // ==================================
  // Kontrol Ventilasi dengan Servo
  // ==================================
  if (suhu > suhuMaks) {

    ventilasi.write(90); // Buka ventilasi

    Serial.println("Status Ventilasi : TERBUKA");

  } else {

    ventilasi.write(0); // Tutup ventilasi

    Serial.println("Status Ventilasi : TERTUTUP");
  }

  // ==================================
  // Kontrol Buzzer
  // ==================================
  if (nilaiGas > gasMaks) {

    Serial.println("PERINGATAN! Kadar gas tinggi");

    tone(BUZZER_PIN, 1000);
    delay(200);

    tone(BUZZER_PIN, 1500);
    delay(200);

    tone(BUZZER_PIN, 2000);
    delay(200);

    noTone(BUZZER_PIN);

  } else {

    noTone(BUZZER_PIN);
  }

  delay(2000);
}
