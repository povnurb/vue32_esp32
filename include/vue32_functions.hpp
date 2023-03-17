#include "vue32_LedBlink.hpp"

void WsMessage(String msg, String icon, String Type);
String getSendJson(String msg, String type);
void setDyMsYr();
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
//------------------------------------------------------------------
// Fecha y Hora del Sistema
//------------------------------------------------------------------
//------------------------------------------------------------------
// Setup de fecha y Hora Auto / Manual
//------------------------------------------------------------------
void timeSetup(){
    
    setDyMsYr();

    if(time_ajuste){
        rtc.setTime(time_sc, time_mn, time_hr, time_dy, time_mt, time_yr); 
        log("[ INFO ] RTC set OK");
    // datos desde el Internet
    }else{
        if ((WiFi.status() == WL_CONNECTED) && (wifi_mode == WIFI_STA)){
            /* WiFi Conectada */
            ntpClient.begin();
            ntpClient.setPoolServerName(time_server); //servidor 
            ntpClient.setTimeOffset(time_z_horaria);    // zona horaria
            ntpClient.update(); 
            log("[ INFO ] NTP set OK");
        }else{
            /* Si no hay conexión a WiFi - No Internet */
            rtc.setTime(time_sc, time_mn, time_hr, time_dy, time_mt, time_yr); 
            log("[ INFO ] RTC set OK");
        }
    }
}

// -------------------------------------------------------------------
// Función para seteo de Día, Mes y Año a las variables
// -------------------------------------------------------------------
void setDyMsYr(){
    // 2022-09-07T23:47
    String str_date = time_date;
    time_sc = 0;
    time_mn = str_date.substring(14, 16).toInt(); //47
    time_hr = str_date.substring(11, 13).toInt(); //23
    time_dy = str_date.substring(8, 10).toInt(); 
    time_mt = str_date.substring(5, 7).toInt();   
    time_yr = str_date.substring(0, 4).toInt();  //2023
}

// -------------------------------------------------------------------
// Fecha y Hora del Sistema
// -------------------------------------------------------------------
String getDateTime(){
    
    char fecha[20];
    int dia = 0;
    int mes = 0;
    int anio = 0;
    int hora = 0;
    int minuto = 0;
    int segundo = 0;

    if(time_ajuste){ // Manual
        /* RTC */
        dia = rtc.getDay();
        mes = rtc.getMonth()+1;
        anio = rtc.getYear();
        hora = rtc.getHour(true);
        minuto = rtc.getMinute();
        segundo = rtc.getSecond();
    }else{ // Automatico
        if((WiFi.status() == WL_CONNECTED) && (wifi_mode == WIFI_STA)){
            /* NTP */
            if(ntpClient.isTimeSet()) {
                String formattedTime = ntpClient.getFormattedTime();
                // FORMAR FECHA DD-MM-YYYY DESDE EPOCH
                time_t epochTime = ntpClient.getEpochTime();
                struct tm *now = gmtime ((time_t *)&epochTime); 
                anio = now->tm_year+1900;
                mes =  now->tm_mon+1;
                dia =  now->tm_mday;
                // 12:00:00
                hora = ntpClient.getHours();
                minuto = ntpClient.getMinutes();
                segundo = ntpClient.getSeconds();
            }  
        }else{
            /* RTC */
            dia = rtc.getDay();
            mes = rtc.getMonth()+1;
            anio = rtc.getYear();
            hora = rtc.getHour(true);
            minuto = rtc.getMinute();
            segundo = rtc.getSecond();
        }                   
    }	
    sprintf( fecha, "%.2d-%.2d-%.4d %.2d:%.2d:%.2d", dia, mes, anio, hora, minuto, segundo);
    //sprintf( fecha, "%.2d-%.2d-%.4d %.2d:%.2d", dia, mes, anio, hora, minuto);
	return String( fecha );
}

// -------------------------------------------------------------------
//contador de alarmas
void contadorAlarmas(){
    int pines[8] = {ALARM_PIN1,ALARM_PIN2,ALARM_PIN3,ALARM_PIN4,ALARM_PIN5,ALARM_PIN6,ALARM_PIN7,ALARM_PIN8};
    bool logicas[8] = {ALARM_LOGICA1,ALARM_LOGICA2,ALARM_LOGICA3,ALARM_LOGICA4,ALARM_LOGICA5,ALARM_LOGICA6,ALARM_LOGICA7,ALARM_LOGICA8};
    String fechaAct[8] = {ALARM_TIMEON1,ALARM_TIMEON2,ALARM_TIMEON3,ALARM_TIMEON4,ALARM_TIMEON5,ALARM_TIMEON6,ALARM_TIMEON7,ALARM_TIMEON8};
    String fechaClear[8] = {ALARM_TIMEOFF1,ALARM_TIMEOFF2,ALARM_TIMEOFF3,ALARM_TIMEOFF4,ALARM_TIMEOFF5,ALARM_TIMEOFF6,ALARM_TIMEOFF7,ALARM_TIMEOFF8};
    //long now2 = millis(); 
    //if (now2 - last2 > 20000 || last2 > now2){// cada 20 segundos si al acabarse el contador last queda en 0 y now en millones   
    //last2 = millis(); 
        for (int i=0; i < 8; i++){
            if(!logicas[i]){ //si la logica es normal
        
                if(!digitalRead(pines[i]) && !cambiar[i]){
                    cont[i]++;
                    fechaAct[i] = getDateTime();
                    fechaClear[i] = "";
                    cambiar[i]=true;
                }else if(digitalRead(pines[i]) && cambiar[i]){
                    cambiar[i]=false;
                    fechaClear[i] = getDateTime();
                }
            }else{  //si la logica es invertida
            
                if(digitalRead(pines[i]) && !cambiar[i]){
                    cont[i]++;
                    fechaAct[i] = getDateTime();
                    fechaClear[i] = "";
                    cambiar[i]=true;
                }else if(!digitalRead(pines[i]) && cambiar[i]){
                    cambiar[i]=false;
                    fechaClear[i] = getDateTime();
                }
            }
        }
    //}
    ALARM_CONT1=cont[0];ALARM_CONT2=cont[1];
    ALARM_CONT3=cont[2];ALARM_CONT4=cont[3];
    ALARM_CONT5=cont[4];ALARM_CONT6=cont[5];
    ALARM_CONT7=cont[6];ALARM_CONT8=cont[7];
    ALARM_TIMEON1=fechaAct[0];ALARM_TIMEON2=fechaAct[1];
    ALARM_TIMEON3=fechaAct[2];ALARM_TIMEON4=fechaAct[3];
    ALARM_TIMEON5=fechaAct[4];ALARM_TIMEON6=fechaAct[5];
    ALARM_TIMEON7=fechaAct[6];ALARM_TIMEON8=fechaAct[7];
    ALARM_TIMEOFF1=fechaClear[0];ALARM_TIMEOFF2=fechaClear[1];
    ALARM_TIMEOFF3=fechaClear[2];ALARM_TIMEOFF4=fechaClear[3];
    ALARM_TIMEOFF5=fechaClear[4];ALARM_TIMEOFF6=fechaClear[5];
    ALARM_TIMEOFF7=fechaClear[6];ALARM_TIMEOFF8=fechaClear[7];
}
