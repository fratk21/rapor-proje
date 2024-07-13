#include <WiFi.h>  // Wi-Fi bağlantısı için gerekli kütüphane
#include <PubSubClient.h>  // MQTT bağlantısı için gerekli kütüphane

const char* ssid = "Wokwi-GUEST";  // Wi-Fi ağ adı
const char* password = "";  // Wi-Fi şifresi
const char* mqtt_server = "test.mosquitto.org";  // MQTT broker adresi

WiFiClient espClient;  // Wi-Fi istemcisi oluşturma
PubSubClient client(espClient);  // MQTT istemcisi oluşturma

const int trigPin = 27;  // Ultrasonik sensörün TRIG pini
const int echoPin = 26;  // Ultrasonik sensörün ECHO pini
const int pirPin = 25;  // PIR sensörünün pini
const int redLed = 12;  // Kırmızı LED'in pini

long duration;  // Ultrasonik sensörün ölçtüğü sürenin saklanacağı değişken
int distance;  // Ölçülen mesafenin saklanacağı değişken
bool ledState = false;  // LED'in açık/kapalı durumunu takip eden değişken
unsigned long lastMsg = 0;  // Son mesaj gönderim zamanını saklayan değişken

// Wi-Fi bağlantısını kuran fonksiyon
void setup_wifi() {
  delay(10);
  Serial.begin(115200);  // Seri haberleşmeyi başlatır
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);  // Wi-Fi bağlantısını başlatır

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  // Bağlantı sağlandığında IP adresini yazdırır
}

// MQTT mesaj geldiğinde çağrılan geri çağırma fonksiyonu
void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];  // Gelen mesajı bir stringe dönüştürür
  }

  if (String(topic) == "20010011075/control") {  // Eğer mesajın konusu "20010011075/control" ise
    if (message == "ON") {
      ledState = true;  // Mesaj "ON" ise LED durumunu açar
    } else if (message == "OFF") {
      ledState = false;  // Mesaj "OFF" ise LED durumunu kapatır
    }
  }
}

// MQTT sunucusuna tekrar bağlanmayı sağlayan fonksiyon
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      client.subscribe("20010011075/control");  // "20010011075/control" konusuna abone olur
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);  // Bağlantı başarısız olursa 5 saniye bekleyip tekrar dene
    }
  }
}

// Başlangıç ayarlarının yapıldığı fonksiyon
void setup() {
  Serial.begin(115200);
  setup_wifi();  // Wi-Fi bağlantısını kurar
  client.setServer(mqtt_server, 1883);  // MQTT sunucusunu ayarlar
  client.setCallback(callback);  // MQTT geri çağırma fonksiyonunu ayarlar

  pinMode(trigPin, OUTPUT);  // Ultrasonik sensör TRIG pinini çıkış olarak ayarlar
  pinMode(echoPin, INPUT);  // Ultrasonik sensör ECHO pinini giriş olarak ayarlar
  pinMode(pirPin, INPUT);  // PIR sensör pinini giriş olarak ayarlar
  pinMode(redLed, OUTPUT);  // Kırmızı LED pinini çıkış olarak ayarlar
}

// Ana döngü fonksiyonu
void loop() {
  if (!client.connected()) {
    reconnect();  // Eğer MQTT istemcisi bağlı değilse tekrar bağlan
  }
  client.loop();  // MQTT istemci döngüsünü çalıştır

  long now = millis();  // Geçerli zamanı al

  // PIR sensörünü kontrol et
  int pirState = digitalRead(pirPin);
  if (pirState == HIGH) {
    // Ultrasonik sensör ile mesafeyi ölç
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);  // ECHO pininde yankı süresini ölç
    distance = duration * 0.034 / 2;  // Ölçülen süreyi mesafeye çevir

    if (distance <= 50) {
      if (now - lastMsg > 2000) {  // 2 saniyede bir mesaj gönder
        lastMsg = now;
        String distanceStr = String(distance);
        client.publish("20010011075/mesafe", distanceStr.c_str());  // Mesafeyi MQTT üzerinden yayınla

        // LED'in yanıp sönme durumunu kontrol et
        if (ledState) {
          digitalWrite(redLed, HIGH);  // LED'i aç
          delay(250);
          digitalWrite(redLed, LOW);  // LED'i kapat
          delay(250);
        }
      }
    }
  }
}
