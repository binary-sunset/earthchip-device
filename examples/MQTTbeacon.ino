#include <Earthchip.h>
#include <ESP8266WiFi.h>

#define wifi_ssid "It's a trap!"
#define wifi_password "costaricandelight1821"

#define mqtt_port 1883
#define mqtt_host "192.168.2.192"

WiFiClient espClient;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  delay(2000);
  Earthchip earthchip (mqtt_host, mqtt_port, espClient);
  Serial.println(earthchip.connect("test"));
}

void loop() {
  // put your main code here, to run repeatedly:
}


void setup_wifi() {
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}