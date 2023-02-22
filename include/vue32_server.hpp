#include "ESPAsyncWebServer.h"          //servidor asincrono
#include <Update.h>                     //para actualizar el firmware

bool cors = true; //habilita los cruces de origen igual a true

AsyncWebServer server(80);
// -------------------------------------------------------------------
// Zona API REST
// -------------------------------------------------------------------
// URL:                         Método:
// -------------------------------------------------------------------
// /api/index                     GET 
// /api/wifi                      GET 
// /api/wifi                      PUT
// /api/scan                      GET
// /api/cloud                     GET
// /api/cloud/connection          PUT
// /api/cloud/data                PUT
// /api/settings/id               GET
// /api/settings/id               PUT
// /api/settings/user             PUT
// /api/settings/download         GET
// /api/settings/upload           POST
// /api/settings/firmware         POST
// /api/settings/logout           DELETE
// -------------------------------------------------------------------
// -------------------------------------------------------------------
// Método PUT Actualizar configuraciones WiFi
// -------------------------------------------------------------------
void putRequestWiFi(AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total){
    /* if(!request->authenticate(device_old_user, device_old_password))
        return request->requestAuthentication(); */
    const char* dataType = "application/json"; 
    String bodyContent = GetBodyContent(data, len);    
    StaticJsonDocument<768> doc;
    DeserializationError error = deserializeJson(doc, bodyContent);
    if (error) { 
        Serial.println("[ ERROR ] En petición POST");
        request->send(400, dataType, "{ \"status\": \"Error de JSON enviado\" }");
        return;
    };
    Serial.println("[ INFO ] Ok petición POST");
    // -------------------------------------------------------------------
    // WIFI Cliente settings.json
    // -------------------------------------------------------------------  
    String s = "";    
    // SSID Client
    if(doc["wifi_ssid"] != ""){
        s = doc["wifi_ssid"].as<String>();
        s.trim();
        strlcpy(wifi_ssid, s.c_str(), sizeof(wifi_ssid));
        s = "";
    }
    // Password SSID Client
    if(doc["wifi_password"] != ""){
        s = doc["wifi_password"].as<String>();
        s.trim();
        strlcpy(wifi_password, s.c_str() , sizeof(wifi_password)); 
        s = "";
    }
    // DHCP
    wifi_ip_static = doc["wifi_ip_static"].as<bool>();
    // IPV4
    if(doc["wifi_ipv4"] != ""){  
        s = doc["wifi_ipv4"].as<String>();
        s.trim();    
        strlcpy(wifi_ipv4, s.c_str(), sizeof(wifi_ipv4));
        s = "";
    }
    // Subned
    if(doc["wifi_subnet"] != ""){
        s = doc["wifi_subnet"].as<String>();
        s.trim(); 
        strlcpy(wifi_subnet, s.c_str(), sizeof(wifi_subnet));
        s = "";
    }
    // Gateway
    if(doc["wifi_gateway"] != ""){
        s = doc["wifi_gateway"].as<String>();
        s.trim();
        strlcpy(wifi_gateway, s.c_str(), sizeof(wifi_gateway));
        s = "";
    }
    // DNS Primary
    if(doc["wifi_dns_primary"] != ""){
        s = doc["wifi_dns_primary"].as<String>();
        s.trim();
        strlcpy(wifi_dns_primary, s.c_str(), sizeof(wifi_dns_primary));
        s = "";
    }
    // DNS Secondary
    if(doc["wifi_dns_secondary"] != ""){
        s = doc["wifi_dns_secondary"].as<String>();
        s.trim();
        strlcpy(wifi_dns_secondary, s.c_str(), sizeof(wifi_dns_secondary));
        s = "";
    }
    // -------------------------------------------------------------------
    // WIFI AP settings.json
    // -------------------------------------------------------------------
    // AP Enable
    ap_mode = doc["ap_mode"].as<bool>();
    // AP SSID
    if(doc["ap_ssid"] != ""){
        s = doc["ap_ssid"].as<String>();
        s.trim();
        strlcpy(ap_ssid, s.c_str(), sizeof(ap_ssid));
        s = "";
    }
    // AP Password 
    if(doc["ap_password"] != ""){
        s = doc["ap_password"].as<String>();
        s.trim();
        strlcpy(ap_password, s.c_str(), sizeof(ap_password));
        s = "";
    }
    // AP visibility 0 Visible - 1 Oculto
    ap_visibility = !doc["ap_visibility"].as<int>();
    // AP Channel
    if(doc["ap_chanel"] != ""){
        ap_chanel = doc["ap_chanel"].as<int>();
    }
    // AP number of Connections
    if(doc["ap_connect"] != ""){
        ap_connect = doc["ap_connect"].as<int>();
    }
    // Save Settings.json
    if (settingsSave()){
        request->send(200, dataType, "{ \"save\": true }");
        log("[ INFO ] Se Guardo");        
    }else{
        request->send(500, dataType, "{ \"save\": false }");
        log("[ INFO ] No se Guardo");
    } 
}
// -------------------------------------------------------------------
// Método PUT Cloud Conexión.
// -------------------------------------------------------------------
void putRequestCloudConnection(AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total){  
    /* if(!request->authenticate(device_old_user, device_old_password)) 
        return request->requestAuthentication(); */
    const char* dataType = "application/json"; 
    String bodyContent = GetBodyContent(data, len);    
    StaticJsonDocument<768> doc;
    DeserializationError error = deserializeJson(doc, bodyContent);
    if (error) { 
        request->send(400, dataType, "{ \"status\": \"Error de JSON enviado\" }");
        return;
    };
    JsonObject data_connection = doc["data"]["connection"];  // DOC = data.connection
    //serializeJsonPretty(data_connection, Serial);
    // -------------------------------------------------------------------
    // Cloud Conexión settings.json
    // ------------------------------------------------------------------- 
    String s = "";  
    // MQTT Enable 
    mqtt_cloud_enable = data_connection["mqtt_cloud_enable"].as<bool>();
    // MQTT User
    if(data_connection["mqtt_user"] != ""){
        s = data_connection["mqtt_user"].as<String>();
        s.trim();
        strlcpy(mqtt_user, s.c_str(), sizeof(mqtt_user));
        s = "";
    }
    // MQTT Password
    if(data_connection["mqtt_password"] != ""){
        s = data_connection["mqtt_password"].as<String>();
        s.trim(); 
        strlcpy(mqtt_password, s.c_str(), sizeof(mqtt_password)); 
        s = "";
    }
    // MQTT Server
    if(data_connection["mqtt_server"] != ""){  
        s = data_connection["mqtt_server"].as<String>();
        s.trim();    
        strlcpy(mqtt_server, s.c_str(), sizeof(mqtt_server));
        s = "";
    }
    // MQTT ID
    if(data_connection["mqtt_cloud_id"] != ""){
        s = data_connection["mqtt_cloud_id"].as<String>();
        s.trim();
        strlcpy(mqtt_cloud_id, s.c_str() , sizeof(mqtt_cloud_id));
        s = "";
    }
    // MQTT Port
    if(data_connection["mqtt_port"] != ""){
        mqtt_port = data_connection["mqtt_port"].as<int>();
    }
    // MQTT Retain    
    mqtt_retain = data_connection["mqtt_retain"].as<bool>();
    // MQTT QOS      
    mqtt_qos = data_connection["mqtt_qos"].as<int>(); 
    // Save Settings.json
    if (settingsSave()){
        request->send(200, dataType, "{ \"save\": true }");        
    }else{
        request->send(500, dataType, "{ \"save\": false }");
    } 
}
// -------------------------------------------------------------------
// Método PUT Cloud Envio de Datos.
// -------------------------------------------------------------------
void putRequestCloudData(AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total){
    /* if(!request->authenticate(device_old_user, device_old_password)) 
        return request->requestAuthentication(); */    
    const char* dataType = "application/json"; //application/json
    String bodyContent = GetBodyContent(data, len);    
    StaticJsonDocument<768> doc;
    DeserializationError error = deserializeJson(doc, bodyContent);
    if (error) { 
        log("[ INFO ] Error 400");
        request->send(400, dataType, "{ \"status\": \"Error de JSON enviado\" }");
        return;
    };
    JsonObject data_datos = doc["data"]["datos"];    
    //serializeJsonPretty(data_datos, Serial);
    // -------------------------------------------------------------------
    // Cloud Datos settings.json
    // -------------------------------------------------------------------
    // MQTT Send Time Data   
    mqtt_time_send = data_datos["mqtt_time_send"].as<bool>();
    // MQTT Time interval
    if(data_datos["mqtt_time_interval"] != ""){
        mqtt_time_interval = data_datos["mqtt_time_interval"].as<int>()*1000;   // 30 * 1000 = 30000 = 30s
    } 
    // MQTT Send Status       
    mqtt_status_send = data_datos["mqtt_status_send"].as<bool>();  
    // Save Settings.json
    if (settingsSave()){
        request->send(200, dataType, "{ \"save\": true }");        
    }else{
        request->send(500, dataType, "{ \"save\": false }");
    }    
}
// -------------------------------------------------------------------
// Método PUT Dispositivo ID
// -------------------------------------------------------------------
void putRequestDeviceID(AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total){
    /* if(!request->authenticate(device_old_user, device_old_password))
        return request->requestAuthentication(); */    
    const char* dataType = "application/json";
    String bodyContent = GetBodyContent(data, len);    
    StaticJsonDocument<96> doc;
    DeserializationError error = deserializeJson(doc, bodyContent);
    if (error) { 
        request->send(400, dataType, "{ \"status\": \"Error de JSON enviado\" }");
        return;
    };
    // -------------------------------------------------------------------
    // Dispositivo ID settings.json
    // -------------------------------------------------------------------
    if(doc["device_id"] != "" && doc["device_id"] != device_id){
        String s = doc["device_id"].as<String>();
        s.trim();
        strlcpy(device_id, s.c_str(), sizeof(device_id));
        // Save Settings.json
        if(settingsSave()){
            request->send(200, dataType, "{ \"save\": true }");
        }else{
            request->send(500, dataType, "{ \"save\": false }");
        }
    }else{
        request->send(400, dataType, "{ \"save\": false, \"msg\": \"¡Error, No se permite el Device ID vacío ni repetido!\"}");
        return;
    }
}
// -------------------------------------------------------------------
// Método PUT WWW Usuario y Contraseña
// -------------------------------------------------------------------
void putRequestUser(AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total){   
    /* if(!request->authenticate(device_old_user, device_old_password)) 
        return request->requestAuthentication();  */   
    const char* dataType = "application/json";
    String bodyContent = GetBodyContent(data, len);    
    StaticJsonDocument<384> doc;
    DeserializationError error = deserializeJson(doc, bodyContent);
    if (error) { 
        request->send(400, dataType, "{ \"status\": \"Error de JSON enviado\" }");
        return;
    };
    // -------------------------------------------------------------------
    // WWW Usuario y Contraseña settings.json
    // -------------------------------------------------------------------
    String u, p, nu, np, cp; 
    // capturamos las variables enviadas en el JSON
    u  = doc["device_old_user"].as<String>();           // Usuario Actual
    p  = doc["device_old_password"].as<String>();       // Contraseña Actual
    nu = doc["device_new_user"].as<String>();           // Nuevo Usuario
    np = doc["device_new_password"].as<String>();       // Nueva Contraseña
    cp = doc["device_c_new_password"].as<String>();     // Confirmación de nueva Contraseña
    // Limpiamos de espacios vacios
    u.trim();
    p.trim();
    nu.trim();
    np.trim();
    cp.trim();
    // Validar que los datos del usario y contraseña anteriores no esten en blanco
    if(u != "" && p != ""){
        // validar que el usuario y contraseña coincidan con los anteriores
        if(u == device_old_user && p == device_old_password){
            // Guardamos solo el Nuevo Usuario
            if(nu != "" && np == "" && cp == ""){
                // Validar que el usuario nuevo sea diferente al antiguo
                if(nu == device_old_user){        
                    request->send(400, dataType, "{ \"save\": false, \"msg\": \"¡Error, El nuevo usuario no puede ser igual al anterior!\"}");
                    return;
                }
                // Nuevo Usuario en la Variable
                strlcpy(device_old_user, nu.c_str(), sizeof(device_old_user));
                // Guardar settings.json
                if(settingsSave()){
                    request->send(200, dataType, "{ \"save\": true, \"msg\": \"¡Usuario actualizado correctamente!\" }");         
                }else{
                    request->send(500, dataType, "{ \"save\": false }");                    
                }
            }else if(nu == "" && np == "" && cp == ""){
                request->send(400, dataType, "{ \"save\": false, \"msg\": \"¡Error, No se permite nuevo usuario, nueva contraseña y confirmación de nueva contraseña vacíos!\"}");
                return;
            // Guardar solo la nueva contraseña
            }else if(np != "" && cp != "" && np == cp && nu == ""){
                // Validar que la contraseña nueva sea diferente a la antigua
                if(np == device_old_password){
                    request->send(400, dataType, "{ \"save\": false, \"msg\": \"¡Error, La contraseña nueva no puede ser igual a la anterior!\"}");         
                    return;
                }
                // Nueva Contraseña en la Variable
                strlcpy(device_old_password, np.c_str(), sizeof(device_old_password));         
                // Guardar settings.json
                if(settingsSave()){
                    request->send(200, dataType, "{ \"save\": true, \"msg\": \"¡Contraseña actualizada correctamente!\" }");           
                }else{
                    request->send(500, dataType, "{ \"save\": false }");                    
                }
            // Validar la nueva contraseña y confirmación
            }else if(np != cp){
                request->send(400, dataType, "{ \"save\": false, \"msg\": \"¡Error, La nueva contraseña y confirmación de nueva contraseña no coinciden!\"}"); 
                return;
            // Guardo Usuario y Contraseña nuevos
            }else if(nu != "" && np != "" && cp != "" && np == cp){
                // Validar que el usuario nuevo y la contraseña nueva sea diferente a los antiguos
                if(np == device_old_password && nu == device_old_user){
                    request->send(400, dataType, "{ \"save\": false, \"msg\": \"¡Error, La nueva contraseña y el nuevo usuario no puede ser iguales a los anteriores!\"}");  
                    return;
                }
                // Nuevo Usuario en la Variable
                strlcpy(device_old_user, nu.c_str(), sizeof(device_old_user));
                // Nueva Contraseña en la Variable
                strlcpy(device_old_password, np.c_str(), sizeof(device_old_password));
                // Guardar settings.json
                if(settingsSave()){
                    request->send(200, dataType, "{ \"save\": true, \"msg\": \"¡Usuario y Contraseña actualizados correctamente!\" }");     
                }else{
                    request->send(500, dataType, "{ \"save\": false }");                    
                }
            }
        }else{
            AsyncWebServerResponse *response = request->beginResponse(400, dataType, "{ \"save\": false, \"msg\": \"¡Error, No se pudo Guardar, Usuario y Contraseña anterior no coinciden!\"}");         
            request->send(response);
            return; 
        }
    }else{
        request->send(400, dataType, "{ \"save\": false, \"msg\": \"¡Error, No se permite usuario y contraseña anterior vacíos!\"}");  
        return; 
    }
}
// -------------------------------------------------------------------
// Método POST carga del archivo Settings.json OK // Otros
// -------------------------------------------------------------------
// Variables para la carga del Archivo
File file;
bool opened = false;
void handleDoUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
    /* if(!request->authenticate(device_old_user, device_old_password)) 
        return request->requestAuthentication(); */
    const char* dataType = "application/json";
    if (!index) {
        Serial.printf("[ INFO ] Upload Start: %s\n", filename.c_str());
    }
    // Validar el Archivo si esta abierto settings.json
    if (opened == false) {
        opened = true;
        file = SPIFFS.open(String("/") + filename, FILE_WRITE);
        if (!file) {
            log("[ ERROR ] No se pudo abrir el archivo para escribir");
            request->send(500, dataType, "{ \"save\": false, \"msg\": \"¡Error, No se pudo abrir el archivo para escribir!\"}");
            return;
        }
    }
    // Escribir el archivo en la Memoria
    if (file.write(data, len) != len) {
        log("[ ERROR ] No se pudo escribir el Archivo");
        request->send(500, dataType, "{ \"save\": false, \"msg\": \"¡Error, No se pudo escribir el Archivo: " + filename + " !\"}");
        return;
    }
    // Finalizada la carga del Archivo.
    if (final) {
        AsyncWebServerResponse *response = request->beginResponse(201, dataType, "{ \"save\": true, \"msg\": \"¡Carga del Archivo: " + filename + " completada!\"}");
        response->addHeader("Cache-Control","no-cache");
        response->addHeader("Location", "/");
        request->send(response);
        file.close();
        opened = false;
        log("[ INFO ] Carga del Archivo " + filename + " completada");
        // Esperar la Transmisión de los datos seriales
        Serial.flush();
        // Reiniciar el ESP32 
        ESP.restart();
    }
}
// -------------------------------------------------------------------
// Método POST para la carga del nuevo Firmware OK o SPIFFS OK
// -------------------------------------------------------------------
void handleDoFirmware(AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final) {
    /* if(!request->authenticate(device_old_user, device_old_password)) 
        return request->requestAuthentication(); */    
    const char* dataType = "application/json";
    // Si el nombre de archivo incluye ( spiffs ), actualiza la partición de spiffs
    int cmd = (filename.indexOf("spiffs") > -1) ? U_PART : U_FLASH;
    String updateSystem = cmd == U_PART ? "FileSystem" : "Firmware";
    if (!index) {
        content_len = request->contentLength();    
        log("[ INFO ] Actualización del "+ updateSystem +" iniciada");        
        if (!Update.begin(UPDATE_SIZE_UNKNOWN, cmd)) {
            AsyncWebServerResponse *response = request->beginResponse(500, dataType, "{ \"save\": false, \"msg\": \"¡Error, No se pudo actualizar el "+ updateSystem +" Index: " + filename + " !\"}");
            request->send(response);
            Update.printError(Serial);
            log("[ ERROR ] Update del "+ updateSystem +" terminado");
        }
    }
    if (Update.write(data, len) != len) {
        Update.printError(Serial);
    }
    if (final) {        
        if (!Update.end(true)) {
            AsyncWebServerResponse *response = request->beginResponse(500, dataType, "{ \"save\": false, \"msg\": \"¡Error, No se pudo actualizar el "+ updateSystem +" Final: " + filename + " !\"}");
            request->send(response);
            Update.printError(Serial);
        } else {            
            AsyncWebServerResponse *response = request->beginResponse(201, dataType, "{ \"save\": true, \"type\": \""+updateSystem+"\"}");
            response->addHeader("Cache-Control","no-cache");
            response->addHeader("Location", "root@"+ updateSystem +"");
            request->send(response);
            log("[ INFO ] Update del " + updateSystem + " completado");
            // Esperar la Transmisión de los datos seriales
            Serial.flush(); 
            ESP.restart();
        }
    }
}

void InitServer(){
    // -------------------------------------------------------------------
    // Zona API REST
    // -------------------------------------------------------------------
    // URL:                         Método:
    // -------------------------------------------------------------------
    // /api/index                     GET 
    // /api/wifi                      GET 
    // /api/wifi                      PUT
    // /api/scan                      GET
    // /api/cloud                     GET
    // /api/cloud/connection          PUT
    // /api/cloud/data                PUT
    // /api/settings/id               GET
    // /api/settings/id               PUT
    // /api/settings/user             PUT
    // /api/settings/download         GET
    // /api/settings/upload           POST
    // /api/settings/firmware         POST
    // /api/settings/logout           DELETE
    // -------------------------------------------------------------------
    
    // -------------------------------------------------------------------
    // Parametros de Configuración Index
    // url: /api/index
    // Método: GET 
    // -------------------------------------------------------------------
    server.on("/api/index", HTTP_GET, [](AsyncWebServerRequest *request){
        /* if(!request->authenticate(device_old_user, device_old_password)) 
            return request->requestAuthentication(); */        
        const char* dataType = "application/json";
        String json = "";
        json = "{";
        json += "\"meta\": { \"serial\": \""+ deviceID() +"\"},";
        json += "\"data\":{";
                json += "\"device_serial\": \""+ deviceID() +"\"";               
                json += ",\"device_fw_version\": \""+String(device_fw_version)+"\"";
                json += ",\"device_sdk\": \""+ String(ESP.getSdkVersion()) +"\"";
                json += ",\"device_hw_version\": \""+ String(device_hw_version) +"\"";
                json += ",\"device_time_active\": \""+ String(longTimeStr(millis() / 1000)) +"\"";
                json += ",\"device_restart\":"+ String(device_restart);   
                json += ",\"device_ram_size\":"+ String(ESP.getHeapSize());
                json += ",\"device_ram_available\":"+ String(ESP.getFreeHeap()); 
                json += ",\"device_spiffs_total\":"+ String(SPIFFS.totalBytes());      
                json += ",\"device_spiffs_used\":"+ String(SPIFFS.usedBytes());
                json += ",\"device_cpu_clock\":"+ String(getCpuFrequencyMhz());
                json += ",\"device_flash_size\":"+ String(ESP.getFlashChipSize() / (1024.0 * 1024), 2);
                json += ",\"device_manufacturer\": \""+String(device_manufacturer)+"\"";
        mqttClient.connected() ? json += ",\"mqtt_online\": true" : json += ",\"mqtt_online\": false"; 
        mqttClient.connected() ? json += ",\"mqtt_server\": \""+ String(mqtt_server) +"\"" : json += ",\"mqtt_server\": \"server not connected\"" ;
                json += ",\"mqtt_user\": \""+ String(mqtt_user) +"\"";
                json += ",\"mqtt_cloud_id\": \""+ String(mqtt_cloud_id) +"\"";
                json += ",\"mqtt_activity\": \"Inactivo\"";
        WiFi.status() == WL_CONNECTED ? json += ",\"wifi_online\": true" : json += ",\"wifi_online\": false"; 
        wifi_mode == WIFI_STA ? json += ",\"wifi_ssid\": \""+ String(wifi_ssid) +"\"" : json += ",\"wifi_ssid\": \""+ String(ap_ssid) +"\""; 
        wifi_mode == WIFI_STA ? json += ",\"wifi_ipv4\": \""+ String(wifi_ipv4) +"\"" : json += ",\"wifi_ipv4\": \""+ String(ap_IPv4) +"\"";
                json += ",\"wifi_mac\": \""+ String(WiFi.macAddress()) +"\"";
        wifi_mode == WIFI_STA ? json += ",\"wifi_mode\": \"Cliente\"" : json += ",\"wifi_mode\": \"AP\"";
        WiFi.status() == WL_CONNECTED ? json += ",\"wifi_rssi\":"+ String(WiFi.RSSI()) : json += ",\"wifi_rssi\": 0";
        WiFi.status() == WL_CONNECTED ? json += ",\"wifi_signal\":"+ String(getRSSIasQuality(WiFi.RSSI())) : json += ",\"wifi_signal\": 0";     
            json += "},"; 
        json += "\"code\": 1 ";
        json += "}";
        request->send(200, dataType, json);
    });
    // -------------------------------------------------------------------
    // Parámetros de Configuración WiFi
    // url: /api/wifi
    // Método: GET 
    // -------------------------------------------------------------------
    server.on("/api/wifi", HTTP_GET, [](AsyncWebServerRequest *request){
        /* if(!request->authenticate(device_old_user, device_old_password)) 
            return request->requestAuthentication(); */
        const char* dataType = "application/json"; 
        String json = "";
        json = "{";
        json += "\"meta\": { \"serial\": \""+ deviceID() +"\"},";
        json += "\"wifi\":";
            json += "{";       
            json += "\"wifi_ssid\": \""+ String(wifi_ssid) +"\"";    
            json += ",\"wifi_password\": \"""\"";               
            wifi_ip_static ? json += ",\"wifi_ip_static\": true" : json += ",\"wifi_ip_static\": false";
            json += ",\"wifi_ipv4\": \""+ String(wifi_ipv4)+"\"";
            json += ",\"wifi_subnet\": \""+ String(wifi_subnet) +"\"";
            json += ",\"wifi_gateway\": \""+ String(wifi_gateway) +"\"";
            json += ",\"wifi_dns_primary\": \""+ String(wifi_dns_primary) +"\"";
            json += ",\"wifi_dns_secondary\": \""+ String(wifi_dns_secondary) +"\"";
            ap_mode ? json += ",\"ap_mode\": true" : json += ",\"ap_mode\": false";
            json += ",\"ap_ssid\": \""+ String(ap_ssid)+"\"";
            json += ",\"ap_password\": \"""\"";
            ap_visibility ? json += ",\"ap_visibility\": false" : json += ",\"ap_visibility\": true";
            json += ",\"ap_chanel\":"+ String(ap_chanel);
            json += ",\"ap_connect\":"+ String(ap_connect);
            json += "},";
        json += "\"code\": 1 ";
        json += "}";
        request->send(200, dataType, json);
    });
    // -------------------------------------------------------------------
    // Actualizar las configuraciones del WiFi
    // url: /api/wifi
    // Método: POST
    // -------------------------------------------------------------------
    server.on("/api/wifi", HTTP_POST, [](AsyncWebServerRequest *request){log("[ INFO ] peticion post");}, NULL, putRequestWiFi);
    // -------------------------------------------------------------------
    // Escanear todas las redes WIFI al alcance de la señal
    // url: /api/scan
    // Método: GET
    // Notas: La primera solicitud devolverá 0 resultados a menos que comience
    // a escanear desde otro lugar (ciclo / configuración).
    // No solicite más de 3-5 segundos. \ ALT + 92 
    // -------------------------------------------------------------------
    server.on("/api/scan", HTTP_GET, [](AsyncWebServerRequest *request){
        /* if(!request->authenticate(device_old_user, device_old_password))
            return request->requestAuthentication(); */        
        const char* dataType = "application/json"; 
        String json = "";
        int n = WiFi.scanComplete();
        if(n == -2){
        json = "{";
        json += "\"meta\": { \"serial\": \""+ deviceID() +"\", \"count\": 0},";
        json += "\"data\": [";
        json += "],";   
        json += "\"code\": 0 ";
        json += "}";
        WiFi.scanNetworks(true, true); 
        } else if(n){
            json = "{";
            json += "\"meta\": { \"serial\": \""+ deviceID() +"\", \"count\":"+String(n)+"},";
            json += "\"data\": [";
            for (int i = 0; i < n; ++i){
                if(i) json += ",";
                json += "{";
                json += "\"n\":"+String(i+1);
                json += ",\"rssi\":"+String(WiFi.RSSI(i));
                json += ",\"ssid\":\""+WiFi.SSID(i)+"\"";
                json += ",\"bssid\":\""+WiFi.BSSIDstr(i)+"\"";
                json += ",\"channel\":"+String(WiFi.channel(i));
                json += ",\"secure\":\""+ EncryptionType(WiFi.encryptionType(i)) +"\"";
                json += "}";
            }
            json += "],";   
            json += "\"code\": 1 ";
            json += "}";
            WiFi.scanDelete();
            if(WiFi.scanComplete() == -2){
                WiFi.scanNetworks(true, true);
            }
        }
        request->send(200, dataType, json);
    });
    // -------------------------------------------------------------------
    // Parámetros de Configuración Cloud
    // url: /api/cloud
    // Método: GET 
    // -------------------------------------------------------------------
    server.on("/api/cloud", HTTP_GET, [](AsyncWebServerRequest *request){
        /* if(!request->authenticate(device_old_user, device_old_password)) 
            return request->requestAuthentication(); */
        const char* dataType = "application/json"; 
        String json = "";
        json = "{";
        json += "\"meta\": { \"serial\": \""+ deviceID() +"\"},";
        json += "\"data\":{";
            json += "\"connection\": {";       
                mqtt_cloud_enable ? json += "\"mqtt_cloud_enable\": true" : json += "\"mqtt_cloud_enable\": false";    
                json += ",\"mqtt_user\": \""+ String(mqtt_user) +"\"";               
                json += ",\"mqtt_password\": \"""\"";
                json += ",\"mqtt_server\": \""+ String(mqtt_server) +"\"";
                json += ",\"mqtt_cloud_id\": \""+ String( mqtt_cloud_id) +"\"";
                json += ",\"mqtt_port\":"+ String(mqtt_port);   
                mqtt_retain ? json += ",\"mqtt_retain\": true" : json += ",\"mqtt_retain\": false";  
                json += ",\"mqtt_qos\":"+ String(mqtt_qos);                  
            json += "},"; 
            json += "\"datos\": {"; 
                mqtt_time_send ? json += "\"mqtt_time_send\": true" : json += "\"mqtt_time_send\": false";
                json += ",\"mqtt_time_interval\":"+ String(mqtt_time_interval/1000); // 30s = 30000
                mqtt_status_send ? json += ",\"mqtt_status_send\": true" : json += ",\"mqtt_status_send\": false";
            json += "}"; 
        json += "},";   
        json += "\"code\": 1 ";
        json += "}";
        request->send(200, dataType, json);
    });
    // -------------------------------------------------------------------
    // Actualizar las configuraciones del Cloud Conexiones
    // url: /api/cloud/connection
    // Método: POST
    // -------------------------------------------------------------------
    server.on("/api/cloud/connection", HTTP_POST, [](AsyncWebServerRequest * request){}, NULL, putRequestCloudConnection);
    // -------------------------------------------------------------------
    // Actualizar las configuraciones del Cloud Datos
    // url: /api/cloud/data
    // Método: POST
    // -------------------------------------------------------------------
    server.on("/api/cloud/data", HTTP_POST, [](AsyncWebServerRequest * request){}, NULL, putRequestCloudData);
    // -------------------------------------------------------------------
    // Parámetros de Configuración del ID del Dispositivo y el Serial
    // url: /api/settings/id
    // Método: GET 
    // -------------------------------------------------------------------
    server.on("/api/settings/id", HTTP_GET, [](AsyncWebServerRequest *request){
        /* if(!request->authenticate(device_old_user, device_old_password))
            return request->requestAuthentication(); */        
        const char* dataType = "application/json"; 
        String json = "";
        json = "{";
        json += "\"meta\": { \"serial\": \"" + deviceID() + "\"},";
        json += "\"data\":";
            json += "{";       
                json += "\"device_serial\": \"" + deviceID() + "\"";    
                json += ",\"device_id\": \""+ String(device_id) + "\""; 
            json += "},";  
        json += "\"code\": 1 ";
        json += "}";    
        request->send(200, dataType, json);
    });
    // -------------------------------------------------------------------
    // Actualizar las configuraciones del ID del Dispositivo
    // url: /api/settings/id
    // Método: POST
    // -------------------------------------------------------------------
    server.on("/api/settings/id", HTTP_POST, [](AsyncWebServerRequest * request){}, NULL, putRequestDeviceID);
    // -------------------------------------------------------------------
    // Actualizar las configuraciones del WWW Usuario y Contraseña
    // url: /api/settings/user
    // Método: POST
    // -------------------------------------------------------------------
    server.on("/api/settings/user", HTTP_POST, [](AsyncWebServerRequest * request){}, NULL, putRequestUser);
    // -------------------------------------------------------------------
    // Manejo de la descarga del Archivo setting.json
    // url: "/api/settings/download"
    // Método: GET
    // -------------------------------------------------------------------
    server.on("/api/settings/download", HTTP_GET, [](AsyncWebServerRequest *request){
        /* if(!request->authenticate(device_old_user, device_old_password)) 
            return request->requestAuthentication(); */
        const char* dataType = "application/json"; 
        log("[ INFO ] Descarga del archivo settings.json");
        AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/settings.json", dataType, true);
        request->send(response);
    });
    // -------------------------------------------------------------------
    // Manejo de la carga del archivo Settings.json
    // url: "/api/settings/upload"
    // Método: POST
    // -------------------------------------------------------------------
    server.on("/api/settings/upload", HTTP_POST, [](AsyncWebServerRequest * request) {
        opened = false;
    },[](AsyncWebServerRequest * request, const String & filename, size_t index, uint8_t *data, size_t len, bool final) {
        handleDoUpload(request, filename, index, data, len, final);
    });
    // -------------------------------------------------------------------
    // Manejo de la Actualización del Firmware a FileSystem
    // url: /api/settings/firmware
    // Método: POST 
    // -------------------------------------------------------------------
    server.on("/api/settings/firmware", HTTP_POST, [](AsyncWebServerRequest * request) {},
    [](AsyncWebServerRequest * request, const String & filename, size_t index, uint8_t *data, size_t len, bool final) {
        handleDoFirmware(request, filename, index, data, len, final);
    });
    // -------------------------------------------------------------------
    // Petición de salir del Servidor
    // url: "/api/settings/logout"
    // Método: DELETE
    // -------------------------------------------------------------------
    server.on("/api/settings/logout", HTTP_DELETE, [](AsyncWebServerRequest *request){
        /* if(!request->authenticate(device_old_user, device_old_password)) 
            return request->requestAuthentication(); */
        request->send(401, "application/json", "{ \"session\": false, \"msg\": \"Sesión cerrada correctamente\"}");
    });
    // -------------------------------------------------------------------
    // Manejo del Error 404 página no encontrada 
    // url: "desconocido"
    // -------------------------------------------------------------------
    server.onNotFound([](AsyncWebServerRequest *request){
        /* if(!request->authenticate(device_old_user, device_old_password)) 
            return request->requestAuthentication(); */
        request->send(404, "application/json", "{ \"status\": 404, \"msg\": \"Error 404, página no encontrada\"}");
        return;
    });
    // -------------------------------------------------------------------
    // Iniciar el Servidor WEB + CORS
    // -------------------------------------------------------------------
    if(cors == true){
        DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
        DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");
        //DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "POST, PUT, GET, DELETE");
    }
    server.begin();
    log("[ INFO ] Servidor HTTP iniciado");

}