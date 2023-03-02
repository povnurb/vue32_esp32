#include "vue32_LedBlink.hpp"

void WsMessage(String msg, String icon, String Type);
String getSendJson(String msg, String type);
// -----------------------------------------------------
// Genera un log en el puerto Serial
// -----------------------------------------------------
void log(String s){
    Serial.println(s);
}
// -----------------------------------------------------
// Definir la plataforma podria ser una ctral para despues
// -----------------------------------------------------
String platform(){
    // Optiene la plataforma del hardware
#ifdef ARDUINO_ESP32_DEV
    return "ESP32";
#else
    return "ESPWROOM32";
#endif
}
// -------------------------------------------------------------------
// De HEX a String
// -------------------------------------------------------------------
String hexStr(const unsigned long &h, const byte &l = 8){
    String s;
    s = String(h, HEX);
    s.toUpperCase();
    s = ("00000000" + s).substring(s.length() + 8 - l);
    return s;
}
// -------------------------------------------------------------------
// Crear un ID unico desde la direccion MAC
// -------------------------------------------------------------------
String idUnique(){
    // Retorna los ultimos 4 Bytes del MAC rotados
    char idunique[15]; 
    uint64_t chipid = ESP.getEfuseMac();           
    uint16_t chip = (uint16_t)(chipid >> 32);
    snprintf(idunique, 15, "%04X", chip);
    return idunique;
}

// -----------------------------------------------------
// Numero de serie del Dispositivo
// -----------------------------------------------------
String deviceID(){
    return String(platform()) + hexStr(ESP.getEfuseMac()) + String(idUnique());
}
// -------------------------------------------------------------------
// Configurar los Pines de Salida WIFI - MQTT
// -------------------------------------------------------------------
void settingPines(){
    pinMode(WIFILED, OUTPUT);
    pinMode(MQTTLED, OUTPUT);
    setOffSingle(WIFILED);
    setOffSingle(MQTTLED);
}
// -------------------------------------------------------------------
// Convierte un char a IP
// -------------------------------------------------------------------
//uint8_t ip[4];    // Variable función convertir string a IP 
IPAddress CharToIP(const char *str){ //convierte de char a IP
    sscanf(str, "%hhu.%hhu.%hhu.%hhu", &ip[0], &ip[1], &ip[2], &ip[3]);
    return IPAddress(ip[0], ip[1], ip[2], ip[3]);
}
// -------------------------------------------------------------------
// Retorna IPAddress en formato "n.n.n.n" osea de IP a String
// -------------------------------------------------------------------
String ipStr(const IPAddress &ip){    
    String sFn = "";
    for (byte bFn = 0; bFn < 3; bFn++){
        sFn += String((ip >> (8 * bFn)) & 0xFF) + ".";
    }
    sFn += String(((ip >> 8 * 3)) & 0xFF);
    return sFn;
}
// -------------------------------------------------------------------
// Crear un path para los Topicos en MQTT
// v1/devices/vue32_admin/ESP329B1C52100C3D
// -------------------------------------------------------------------
String pathMqtt(){
    return String("v1/devices/"+String(mqtt_user)+"/"+String(mqtt_cloud_id));
}
// -------------------------------------------------------------------
// Parpadeo LED MQTT Recepción
// -------------------------------------------------------------------
void mqttRX(){
    for(int16_t i = 0; i < 1; i++){
        WsMessage(getSendJson("Recepción","mqtt"), "","");
        blinkRandomSingle(5,50, MQTTLED);
        vTaskDelay(10);
        setOffSingle(MQTTLED);
    }
}
// -------------------------------------------------------------------
// Parpadeo LED MQTT Transmisión
// -------------------------------------------------------------------
void mqttTX(){
    for(int16_t i = 0; i < 6; i++){
        WsMessage(getSendJson("Transmisión","mqtt"), "","");
        setOnSingle(MQTTLED);
        vTaskDelay(50);
        setOffSingle(MQTTLED);
        vTaskDelay(10);
    }
}
// -------------------------------------------------------------------
// Retorna segundos como "d:hh:mm:ss"
// -------------------------------------------------------------------
String longTimeStr(const time_t &t){        
    String s = String(t / SECS_PER_DAY) + ':';
    if (hour(t) < 10)
    {
        s += '0';
    }
    s += String(hour(t)) + ':';
    if (minute(t) < 10)
    {
        s += '0';
    }
    s += String(minute(t)) + ':';
    if (second(t) < 10)
    {
        s += '0';
    }
    s += String(second(t));
    return s;
}
// -------------------------------------------------------------------
// Retorna la calidad de señal WIFI en %
// -------------------------------------------------------------------
int getRSSIasQuality(int RSSI){
    int quality = 0;
    if(RSSI <= -100){
        quality = 0;
    }else if (RSSI >= -50){
        quality = 100;
    }else{
       quality = 2 * (RSSI + 100);
    }
    return quality;
}
// -------------------------------------------------------------------
// Retorna el contenido del Body Enviado como JSON metodo POST/PUT
// -------------------------------------------------------------------
String GetBodyContent(uint8_t *data, size_t len){
  String content = "";
  for (size_t i = 0; i < len; i++) {
    content .concat((char)data[i]);
  }
  return content;
}
// -------------------------------------------------------------------
// Retorna el Tipo de Encriptacion segun el codigo (0-1-2-3-4-5)
// -------------------------------------------------------------------
String EncryptionType(int encryptionType) {
    switch (encryptionType) {
        case (0):
            return "Open";
        case (1):
            return "WEP";
        case (2):
            return "WPA_PSK";
        case (3):
            return "WPA2_PSK";
        case (4):
            return "WPA_WPA2_PSK";
        case (5):
            return "WPA2_ENTERPRISE";
        default:
            return "UNKOWN";
    }
}
// -------------------------------------------------------------------
// Empaquetar el JSON para enviar por WS ( progress en % y Actividad MQTT )
// -------------------------------------------------------------------
String getSendJson(String msg, String type){
    String response = "";
    StaticJsonDocument<300> doc;
    doc["type"] = type;
    doc["msg"] = msg;
    serializeJson(doc, response);
    return response;
}
// ------------------------------------------------------------
// Print Progress Firware or SPIFFS Update
// ------------------------------------------------------------
int c = 0;
void printProgress(size_t prog, size_t sz){
    int progress = (prog * 100) / content_len;
     switch (progress){
        case 10:
            c ++;
            if(c>=2) c=1;
            if(c==1){
                WsMessage(getSendJson(String(progress), "update"), "", "");
            }
            break;
        case 20:
            c ++;
            if(c>=2) c=1;
            if(c==1){
                WsMessage(getSendJson(String(progress), "update"), "", "");
            }
            break;
        case 30:
            c ++;
            if(c>=2) c=1;
            if(c==1){
                WsMessage(getSendJson(String(progress), "update"), "", "");
            }
            break;
        case 40:
            c ++;
            if(c>=2) c=1;
            if(c==1){
                WsMessage(getSendJson(String(progress), "update"), "", "");
            }
            break;
        case 50:
            c ++;
            if(c>=2) c=1;
            if(c==1){
                WsMessage(getSendJson(String(progress), "update"), "", "");
            }
            break;
        case 60:
            c ++;
            if(c>=2) c=1;
            if(c==1){
                WsMessage(getSendJson(String(progress), "update"), "", "");
            }
            break;
        case 70:
            c ++;
            if(c>=2) c=1;
            if(c==1){
                WsMessage(getSendJson(String(progress), "update"), "", "");
            }
            break;
        case 80:
            c ++;
            if(c>=2) c=1;
            if(c==1){
                WsMessage(getSendJson(String(progress), "update"), "", "");
            }
            break;
        case 90:
            c ++;
            if(c>=2) c=1;
            if(c==1){
                WsMessage(getSendJson(String(progress), "update"), "", "");
            }
            break;
        case 98:
            c ++;
            if(c>=2) c=1;
            if(c==1){
                WsMessage(getSendJson(String(100), "update"), "", "");
            }
            break;
    }
    Serial.printf("[ INFO ] Progreso de la Actualizacion al : %d%%\n", progress);

}