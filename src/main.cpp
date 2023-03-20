// -------------------------------------------------------------------
// Librerías      v1/devices/L4L0S4N/ESPWROOM325AF6B8701CF1/# subcribirse
// -------------------------------
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <EEPROM.h>
#include <TimeLib.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <ESPmDNS.h> 
// Libreria para el RTC del ESP32
#include <ESP32Time.h>
// Libreria para NTP
#include <NTPClient.h>

/*Librerias agregadas para nuevas funcionalidades (LALO)*/
#include <Adafruit_Sensor.h>    //by Adafruit
#include <DHT.h>                //by Adafruit
#include <Adafruit_I2CDevice.h> //by Adafruit
#include <Adafruit_SSD1306.h>   //by Adafruit

// -------------------------------------------------------------------
// Archivos *.hpp - Fragmentar el Código
// ----------------------------------------
#include "vue32_header.hpp"     //para variables globales
#include "vue32_functions.hpp"  //archivo donde se encontraran las funciones
#include "vue32_settings.hpp"   //opciones generales del proyecto
#include "vue32_wifi.hpp"
#include "vue32_mqtt.hpp"
#include "vue32_server.hpp"
#include "vue32_websockets.hpp"
#include "vue32_relays.hpp"
#include "vue32_alarmas.hpp"
#include "vue32_reset.hpp"



// -------------------------------------------------------------------
// Setup
// -------------------------------
void setup() {
  Serial.begin(115200);
  setCpuFrequencyMhz(240);
  // Memoria EEPROMM init
  EEPROM.begin(256);
  EEPROM.get(Restart_Address, device_restart);
  device_restart++;
  //Guardar el valor en la memoria
  EEPROM.put(Restart_Address, device_restart);
  EEPROM.commit();
  EEPROM.end();
  log("\n[ INFO ] Iniciando Setup");
  if(!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)){ // Dirección 0x3C
    Serial.println("OLED no encontrado");
    while(true);
  }
  OLED.clearDisplay();
  dht.begin(); //su funcionalidad se encuentra en vue32_functions.hpp
  log("[ INFO ] Reinicios " + String(device_restart));
  log("[ INFO ] Setup corriendo en el Core "+ String(xPortGetCoreID())); //indica el core donde esta corriendo 
  // iniciar el SPIFFS
  log("[ INFO ] Espera mientras carga la configuración...");
  if(!SPIFFS.begin(true)){
    log("[ ERROR ] Falló la inicializacion del SPIFFS");
    while(true);
  }
  //SPIFFS.remove("/settings.json"); //para pruebas ya que se guarda la configuracion y con esto reseteamos el SPIFFS
  //Leer el Archivo Settings.json
  if(!settingRead()){ //si no lo puede leer el settingSave lo crea y lo guarda
    settingsSave();
  }
  // Configuración de los LEDs
  settingPines();
  //setup WIFI
  wifi_setup();
  // setup del Time
  timeSetup();
  // Inicio de configuracion del relay
  setupPinRelay();
  // inicia los pines de las alarmas
  setupPinAlarmas(); //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Inicializar el Servidor WEB
  InitServer();
  // Inicializamos el Websocket
  InitWebSockets();
  // Init pin restore
  setupPintRestore();
  //fin del setup
  log("[ INFO ] Setup completado");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(wifi_mode == WIFI_STA){
    wifiLoop();
  }else if(wifi_mode == WIFI_AP){
    wifiAPLoop();
  }
  // -----------------------------------------------------------------
  // MQTT
  // -----------------------------------------------------------------
  if((WiFi.status() == WL_CONNECTED) && (wifi_mode == WIFI_STA)){ //estoy conectado al WIFI y en mono estación
    if(mqtt_server != 0){
      // Función para el Loop principla de MQTT
      //log("server diferente de 0");
      mqttLoop();
      if(mqttClient.connected() && mqtt_time_send){
        //log("va a publicar");
        // Funcion para enviar JSON por MQTT cada determinado tiempo
        if(millis() - lastMsg > mqtt_time_interval){
          lastMsg = millis();
          //log("ya paso el tiempo para publicar");
          mqtt_publish();
        }
      }
    }
  }
  // ---------------------------------------------------------------
  // Enviar Json por ws cada un segundo incluiran las alarmas se encuentra
  // en vue32_websockets.hpp
  // ---------------------------------------------------------------
  if (millis() - lastWsSend > 1000){
    lastWsSend = millis();
    WsMessage(getJsonIndex(),"",""); // seguir esta
  }
  //-----------------------------------------------------------------
  // RTC & NTP
  //---------------------------------------------------------------------
  if((WiFi.status() == WL_CONNECTED) && (wifi_mode == WIFI_STA)){  //ntpClient.isTimeSet() se podria agregar
    ntpClient.update();    
  }
  
  if (millis() - lastTime > 1000){
    lastTime = millis();
    WsMessage(getSendJson(getDateTime(), "time"), "", "");
  }
  if (millis() - lastTime2 > 1000){
    lastTime2 = millis();
    WsMessage(OnOffAlarmas(),"",""); //se captura en cli useApp.js linea 140
  }
  if (millis() - lastTime3 > 1000){
    lastTime3 = millis();
    contadorAlarmas(); 
    activarAlarma();//para activar las alarmas
    mostrar();
  }

  // -------------------------------------------------------------
  // Monitoreo del Pin 35
  // -------------------------------------------------------------
  resetIntLoop();
  // -------------------------------------------------------------
  // Monitoreo del Pin 34 para hacer la activacion de las alarmas
  // -------------------------------------------------------------
}