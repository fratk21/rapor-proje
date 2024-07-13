#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
const char DEVICE_LOGIN_NAME[] = "6fb046ff-bb03-412e-8986-2226351ea5f1";//Sample
const char SSID[] = "Wokwi-GUEST"; // Network SSID (name)
const char PASS[] = ""; // Network password (use for WPA, or useas key for WEP)
const char DEVICE_KEY[] = "upTX8LdaRSUksaO7slh8zTFQt"; // Secret device//Sample password
void onMesajChange();
void onLedChange();
String mesaj;
CloudTemperatureSensor sicaklik;
CloudTemperatureSensor denem;
CloudRelativeHumidity nem;
bool led;
void initProperties(){
ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
ArduinoCloud.addProperty(mesaj, READWRITE, ON_CHANGE, onMesajChange);
ArduinoCloud.addProperty(sicaklik, READ, ON_CHANGE, NULL);
ArduinoCloud.addProperty(nem, READ, ON_CHANGE, NULL);
ArduinoCloud.addProperty(led, READWRITE, ON_CHANGE, onLedChange);
}
WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);