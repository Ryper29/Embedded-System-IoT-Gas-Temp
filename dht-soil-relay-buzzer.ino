Source Code Pertanian Pintar:

#include "DHT.h"

#define SOIL_PIN      34
#define DHT_PIN       4
#define RELAY_PIN     26
#define BUZZER_PIN    25
#define DHTTYPE       DHT11

DHT dht(DHT_PIN, DHTTYPE);

bool RELAY_ACTIVE_LOW = false;

int DRY_VALUE  = 4095;
int WET_VALUE  = 1500;

int   BATAS_TANAH_KERING  = 40;
float BATAS_SUHU_PANAS    = 35.0;
int   LAMA_POMPA_MENYALA  = 3000;

void pompaON() {
  digitalWrite(RELAY_PIN, RELAY_ACTIVE_LOW ? LOW : HIGH);
}

void pompaOFF() {
  digitalWrite(RELAY_PIN, RELAY_ACTIVE_LOW ? HIGH : LOW);
}

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(SOIL_PIN,   INPUT);
  pinMode(RELAY_PIN,  OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  pompaOFF();
  digitalWrite(BUZZER_PIN, LOW);

  dht.begin();

  Serial.println("=================================");
  Serial.println("  SISTEM PERTANIAN PINTAR ESP32  ");
  Serial.println("=================================");
  Serial.print("Mode Relay : ");
  Serial.println(RELAY_ACTIVE_LOW ? "Active LOW (NO)" : "Active HIGH (NC)");
  Serial.println("Sistem siap.");
}

void loop() {
  int soilRaw     = analogRead(SOIL_PIN);
  int soilPercent = map(soilRaw, DRY_VALUE, WET_VALUE, 0, 100);
  soilPercent     = constrain(soilPercent, 0, 100);

  float suhu          = dht.readTemperature();
  float kelembapanUdara = dht.readHumidity();

  if (isnan(suhu) || isnan(kelembapanUdara)) {
    Serial.println("[ERROR] Gagal membaca sensor DHT11! Cek kabel.");
    pompaOFF();
    digitalWrite(BUZZER_PIN, LOW);
    delay(2000);
    return;
  }

  bool tanahKering = (soilPercent < BATAS_TANAH_KERING);
  bool suhuPanas   = (suhu >= BATAS_SUHU_PANAS);

  Serial.println("---------------------------------");
  Serial.print("Soil Raw           : "); Serial.println(soilRaw);
  Serial.print("Kelembapan Tanah   : "); Serial.print(soilPercent); Serial.println("%");
  Serial.print("Suhu Udara         : "); Serial.print(suhu);        Serial.println(" C");
  Serial.print("Kelembapan Udara   : "); Serial.print(kelembapanUdara); Serial.println("%");

  if (tanahKering) {
    Serial.println("Status Tanah       : KERING → Pompa ON");
    Serial.println("Buzzer             : ON");

    digitalWrite(BUZZER_PIN, HIGH);
    pompaON();
    delay(LAMA_POMPA_MENYALA);
    pompaOFF();
    digitalWrite(BUZZER_PIN, LOW);

    Serial.println("Pompa              : OFF (selesai penyiraman)");

  } else {
    Serial.println("Status Tanah       : Lembap → Pompa OFF");
    pompaOFF();

    if (suhuPanas) {
      digitalWrite(BUZZER_PIN, HIGH);
      Serial.println("Buzzer             : ON (suhu panas)");
    } else {
      digitalWrite(BUZZER_PIN, LOW);
      Serial.println("Buzzer             : OFF");
    }
  }

  delay(2000);
}
