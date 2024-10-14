#include "DHT.h"
#include <ESP8266WiFi.h>


#define DHTPIN D3
#define DHTTYPE DHT11
DHT dht (DHTPIN, DHTTYPE);

const char* ssid = "Iot";
const char* senha = "Senac123**";


const char *servidor_destino = "api.thingspeak.com";
String apiKey = "ESIP8MABFAPVZJBS";





void setup() {
  // put your setup code here, to run once:

  Serial.begin(74880);
  dht.begin();

  Serial.print("Conectando a rede:");
  Serial.println(ssid);
  WiFi.begin(ssid, senha);


  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi conectado");

  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP()); 

}
   WiFiClient cliente;

void loop() {
  // put your main code here, to run repeatedly:

  delay(3000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.println(h);
  Serial.println(t);

  if(cliente.connect(servidor_destino, 80)){
    String postStr = apiKey;

    postStr += "&field1=";
    postStr += String(t);
    
    postStr += "&field2=";
    postStr += String(h);

    postStr += "\r\n\r\n";

    cliente.print("POST /update HTTP/1.1\n");
    cliente.print("Host:api.thingspeak.com\n");
    cliente.print("Connection:close\n");
    cliente.print("X-THINGSPEAKAPIKEY:"+apiKey+"\n");

    cliente.print("Content-Type: application/x-www-form-urlencoded\n");

    cliente.print("Content-Length:");
    cliente.print(postStr.length());
    cliente.print("\n\n");
    cliente.print(postStr);
}

  
  delay(3000); 

}
