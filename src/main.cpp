// -------------------------------------------------------------------
// Librerías
// -------------------------------
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <EEPROM.h>
// -------------------------------------------------------------------
// Archivos *.hpp - Fragmentar el Código
// ----------------------------------------
#include "vue32_header.hpp"     //para variables globales
#include "vue32_functions,hpp"  //archivo donde se encontraran las funciones
#include "vue32_settings.hpp"   //opciones generales del proyecto
#include "vue32_wifi.hpp"
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
  log("[ INFO ] Reinicios " + String(device_restart));
  log("[ INFO ] Setup corriendo en el Core "+ String(xPortGetCoreID())); //indica el core donde esta corriendo 
  // iniciar el SPIFFS
  log("[ INFO ] Espera mientras carga la configuración...");
  if(!SPIFFS.begin(true)){
    log("[ ERROR ] Falló la inicializacion del SPIFFS");
    while(true);
  }
  //Leer el Archivo Settings.json
  if(!settingRead()){ //si no lo puede leer el settingSave lo crea y lo guarda
    settingsSave();
  }
  // Configuración de los LEDs
  settingPines();
  //setup WIFI
  wifi_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(wifi_mode == WIFI_STA){
    wifiLoop();
  }else if(wifi_mode == WIFI_AP){
    wifiAPLoop();
  }
}