#include "thingsProperties.h" // Arduino Cloud ile ilişkili değişkenleri içeren başlık dosyasını dahil ettik
#include "DHT.h" // DHT sensör kütüphanesini dahil ettik
#include <LiquidCrystal_I2C.h> // I2C LCD kütüphanesini dahil ettik

// DHT sensörünü tanımladık, GPIO 0 pinine bağlı (DHT22 sensör)
DHT dht(0, DHT22);

// LCD ekranını tanımladık, 0x27 adresi ve 16x2 boyutu
LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);

void setup() {
  Serial.begin(9600); // Seri bağlantıyı başlattık
  delay(1000);

  // Pin modunu ayarladık
  pinMode(12, OUTPUT);

  // LCD'yi başlattık
  LCD.init();
  LCD.backlight();
  LCD.setCursor(0, 0);

  // Arduino Cloud ile ilişkili değişkenleri başlattık
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2); // Hata ayıklama seviyesini ayarladık
  ArduinoCloud.printDebugInfo(); // Hata ayıklama bilgilerini yazdırdık
}



void loop() {
  ArduinoCloud.update(); // Arduino Cloud güncellemelerini aldık
  dhtVeriOkuma(); // DHT sensöründen veri okuduk

  delay(2000); // 2 saniye bekledik
}

// DHT sensöründen veri okuma fonksiyonu
void dhtVeriOkuma() {
  delay(2000); // 2 saniye bekle
  onSicaklikChange(); // Sıcaklık değişikliğini işledik
  delay(2000); // 2 saniye bekle
  onNemChange(); // Nem değişikliğini işledik
  delay(2000); // 2 saniye bekle
  onMesajChange(); // Mesaj değişikliğini işledik
}

// Mesaj değişikliğini işleme fonksiyonu
void onMesajChange() {
  LCD.clear(); // LCD ekranını temizle
  LCD.setCursor(0, 0); // İmleci ilk satırın başlangıcına taşı
  LCD.print(mesaj); // Mesajı yazdır
}

// Led değişikliğini işleme fonksiyonu
void onLedChange() {
  if (led == 1) {
    digitalWrite(12, HIGH); // Led'i aç
  } else {
    digitalWrite(12, LOW); // Led'i kapat
  }
}

// Sıcaklık değerini işleme fonksiyonu
void onSicaklikChange() {
  float yeniSicaklik = dht.readTemperature(); // DHT22 sensöründen sıcaklık oku
  String kategori = degersicak(yeniSicaklik); // Sıcaklık değerini kategorize et
  sicaklik = yeniSicaklik; // Arduino Cloud üzerindeki sıcaklık değerini güncelle
  LCD.clear(); // LCD ekranını temizle
  LCD.setCursor(0, 0); // İmleci ilk satırın başlangıcına taşı
  LCD.print(" TEMPERATURE "); // Başlık yazdır
  LCD.setCursor(0, 1); // İmleci ikinci satırın başlangıcına taşı
  LCD.print(yeniSicaklik); // Sıcaklık değerini yazdır
  LCD.print(" - "); // Ayracı yazdır
  LCD.println(kategori); // Kategoriyi yazdır
}

// Nem değerini işleme fonksiyonu
void onNemChange() {
  float yeniNem = dht.readHumidity(); // DHT22 sensöründen nem oku
  String kategori = degernem(yeniNem); // Nem değerini kategorize et
  nem = yeniNem; // Arduino Cloud üzerindeki nem değerini güncelle
  LCD.clear(); // LCD ekranını temizle
  LCD.setCursor(0, 0); // İmleci ilk satırın başlangıcına taşı
  LCD.print(" HUMIDITY "); // Başlık yazdır
  LCD.setCursor(0, 1); // İmleci ikinci satırın başlangıcına taşı
  LCD.print(yeniNem); // Nem değerini yazdır
  LCD.print(" - "); // Ayracı yazdır
  LCD.println(kategori); // Kategoriyi yazdır
}

// Sıcaklık değerini kategorilere ayırma fonksiyonu
String degersicak(float deger) {
  if (deger < 0) {
    return "Çok Düşük";
  } else if (deger >= 0 && deger <= 25) {
    return "Normal";
  } else {
    digitalWrite(12, HIGH); // Led'i aç
    return "Yüksek";
  }
}

// Nem değerini kategorilere ayırma fonksiyonu
String degernem(float deger) {
  if (deger <= 50) {
    return "Çok Düşük";
  } else {
    return "Yüksek";
  }
}
