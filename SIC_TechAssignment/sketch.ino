#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define DHTPIN 4 
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Wifi";
const char* password = "pass123";

// Server
const char* serverName = "http://127.0.0.1:5000/temperature";

void setup() {
  Serial.begin(115200);
  delay(10);

  // Mulai sensor DHT
  dht.begin();

  // Connect ke wifi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(2000);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Data dengan format JSON
  String postData = "{";
  postData += "\"temperature\":" + String(temperature) + ",";
  postData += "\"humidity\":" + String(humidity);
  postData += "}";

  // Kirim data ke local server dengan POST
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("POST Error: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Wifi Error");
  }
}