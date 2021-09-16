#include <Arduino.h>
#include <String.h>
#include <WiFi.h>
#include <IRCClient.h>
#include <ESPmDNS.h>
#include <SPIFFS.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ArduinoOTA.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h> 

// definindo WIFI config
WebServer server(80);
const char *SSID = "login";
const char *PASSWORD = "senha";
IPAddress ip (192,168,0,120);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);


//definindo pinos leds
#define RED 25
#define GREEN 26
#define BLUE 27
// definindo parametros do controle de PWM
const int freq = 5000;
const int redChannel = 0;
const int greenChannel = 1;
const int blueChannel = 2;
const int resolution = 8;
//funcoes LEDS
void fadeColor(int ColorChannel){
// aumenta brilho do LED
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // modifica o brilho do LED com PWM
    ledcWrite(ColorChannel, dutyCycle);
    delay(15);
  }

  // diminui brilho do LED
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
     // modifica o brilho do LED com PWM
    ledcWrite(ColorChannel, dutyCycle);   
    delay(15);
  }

  }
void SelectRGB( int R, int G, int B){
  ledcWrite(redChannel,R);
  ledcWrite(greenChannel,G);
  ledcWrite(blueChannel,B);

}

//FUNCOEC WIFI
void handleRoot()
{
  server.send(200, "text/plain", "hello from esp8266!");

}
void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
//CONFIGURAÇÃO ATUALIZAÇÃO VIA REDE
void OTAconfig(){
  //Wi-Fi
#ifdef ESP8266
  // Velocidade para ESP8266
  Serial.begin(74880);
#else
  // Velocidade para ESP32
  Serial.begin(115200);
#endif
  Serial.println("\nIniciando.");
  SPIFFS.begin(true);
  SPIFFS.format();
  if (SPIFFS.exists("/Teste.txt"))
  {
    File f = SPIFFS.open("/Teste.txt", "r");
    if (f)
    {
      Serial.println("Lendo arquivo:");
      Serial.println(f.readString());
      f.close();
    }
  }
  else
  {
    Serial.println("Arquivo não encontrado.");
  }
  WiFi.begin(SSID, PASSWORD);
  Serial.println("\nConectando WiFi " + String(SSID));
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  ArduinoOTA.onStart([]() {
    String s;
    if (ArduinoOTA.getCommand() == U_FLASH)
    {
      // Atualizar sketch
      s = "Sketch";
    }
    else
    { // U_SPIFFS
      // Atualizar SPIFFS
      s = "SPIFFS";
      // SPIFFS deve ser finalizada
      SPIFFS.end();
    }
    Serial.println("Iniciando OTA - " + s);
  });

  // Fim
  ArduinoOTA.onEnd([]() {
    ESP.restart();
    Serial.println("\nOTA Concluído.");
  });

  // Progresso
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.print(progress * 100 / total);
    Serial.print(" ");
  });

  // Falha
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.print("Erro " + String(error) + " ");
    if (error == OTA_AUTH_ERROR)
    {
      Serial.println("Falha de autorização");
    }
    else if (error == OTA_BEGIN_ERROR)
    {
      Serial.println("Falha de inicialização");
    }
    else if (error == OTA_CONNECT_ERROR)
    {
      Serial.println("Falha de conexão");
    }
    else if (error == OTA_RECEIVE_ERROR)
    {
      Serial.println("Falha de recebimento");
    }
    else if (error == OTA_END_ERROR)
    {
      Serial.println("Falha de finalização");
    }
    else
    {
      Serial.println("Falha desconhecida");
    }
  });

  ArduinoOTA.setHostname("Hydrabot");
  // Inicializa OTA
  ArduinoOTA.begin();

  // Pronto
  Serial.println("Atualização via OTA disponível.");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

}

void SERVERcomands(){
  server.on("/", handleRoot);

  server.on("/on", []() {
    server.send(200, "text/plain", "LEDS ON");
    SelectRGB(255,255,255);

  });

    server.on("/off", []() {
    server.send(200, "text/plain", "LEDS ON");
    SelectRGB(0,0,0);

  });

    server.on("/Crimson", []() {
    server.send(200, "text/plain", "LEDS ON");
    SelectRGB(0,0,0);
    SelectRGB(220,20,60);

  });

    server.on("/Turquoise", []() {
    server.send(200, "text/plain", "LEDS ON");
    SelectRGB(0,0,0);
    SelectRGB(0,206,209);

  });


    server.on("/FadeRed", []() {
    server.send(200, "text/plain", "LEDS ON");
    //SelectRGB(0,0,0);
    fadeColor(redChannel);

  });

    server.on("/Lime", []() {
    server.send(200, "text/plain", "LEDS ON");
    SelectRGB(0,0,0);
    SelectRGB(50,205,50);

  });
    server.on("/Orange", []() {
    server.send(200, "text/plain", "LEDS ON");
    SelectRGB(0,0,0);
    SelectRGB(255,69,0);

  });

    server.on("/Roxinha", []() {
    server.send(200, "text/plain", "LEDS ON");
    SelectRGB(0,0,0);
    SelectRGB(75,0,130);

  });

    server.on("/Vermelho", []() {
    server.send(200, "text/plain", "LEDS ON");
    SelectRGB(0,0,0);
    SelectRGB(255,0,0);
  });
    server.on("/Amarelo", []() {
    server.send(200, "text/plain", "LEDS ON");
    SelectRGB(0,0,0);
    SelectRGB(255,255,0);
  });
    server.on("/Ciano", []() {
    server.send(200, "text/plain", "LEDS ON");
    SelectRGB(0,0,0);
    SelectRGB(0,255,255);

  });
    server.on("/caquinha", []() {
    server.send(200, "text/plain", "LEDS ON");
    SelectRGB(0,0,0);
    SelectRGB(224,255,255);

  });
    server.on("/Verde", []() {
    server.send(200, "text/plain", "LEDS ON");
    SelectRGB(0,0,0);
    SelectRGB(0,255,0);

  });


  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");


}

void setup() {
  //pinos leds
  Serial.begin(9600);
  pinMode(RED,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(GREEN,OUTPUT);  
  //inicia leds desligados
  digitalWrite(RED, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
  //inicia canais PWM para os leds
  ledcSetup(redChannel, freq, resolution);
  ledcSetup(greenChannel, freq, resolution);
  ledcSetup(blueChannel, freq, resolution);
  ledcAttachPin(RED, redChannel);
  ledcAttachPin(GREEN, greenChannel);
  ledcAttachPin(BLUE, blueChannel);
  //inicia conexão com wifi
  OTAconfig();
  SERVERcomands();
  WiFi.config(ip,gateway,subnet);
  SelectRGB(255,69,0);

}

void loop() {

  ArduinoOTA.handle();
  server.handleClient();
}
