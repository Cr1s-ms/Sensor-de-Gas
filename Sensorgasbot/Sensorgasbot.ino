#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>


const char* ssid = "Monda";// Ingresa nombre de la red WIFI
const char* password = "123456788"; // Ingresa la clave WIFI


#define BOTtoken "6178239308:AAFNKSEpNtiIx3FO9_DEcCOgT4iRWIPN4fg" // Enter the bottoken you got from botfather
#define CHAT_ID "5512815981" // Ingresa tu id de telegram 

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int const SensorA0 = A0;
int const buzzer = D3;
int Umbral = 350;//La sensibilidad puede variar

void setup()
{
  Serial.begin(115200);
  configTime(0, 0, "pool.ntp.org");      
  client.setTrustAnchors(&cert);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int a = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    a++;
  }
  
pinMode(SensorA0, INPUT);
pinMode(buzzer, OUTPUT);


  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  bot.sendMessage(CHAT_ID, "-Wifi Conectado-", "");
  bot.sendMessage(CHAT_ID, "-Sistema iniciado-", "");

}
void loop()
{
int lecturaSensor = analogRead(SensorA0);

  Serial.print("La lectura Del Sensor es : ");
  Serial.print(lecturaSensor);
  Serial.println(" m³");

  
  //Verifica si la lectura es mayor al umbral 
  if (lecturaSensor > Umbral){
    digitalWrite(buzzer,HIGH);
    bot.sendMessage(CHAT_ID, "¡¡¡ALERTA GAS DETECTADO!!!", "");
    }
     
  else if (lecturaSensor < Umbral){
    digitalWrite(buzzer, LOW);
    delay(1000);
    }

}
