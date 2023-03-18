#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient mqttClient(espClient);

char topic[150]; //topicos son char

String mqtt_data = "";

long lastMqttReconnectAttempt = 0; //envio de mensajes no bloqueates
long lastMsg = 0;
//funcion que recive los mensajes de mqtt y definicion de funciones
void callback(char *topic, byte *payload, unsigned int length);
String Json();
void OnOffRelays(String command);

char    willTopic[150];
bool    willQoS      = 0; //calidad del servicio
bool    willRetain   = false; //retencion de mensajes
String  willMessage  = "{\"connected\": false}"; //ultimo mensaje
bool    cleanSession = true; //borra todos los topicos donde el cliente estaba subscrito

// -------------------------------------------------------------------
// MQTT Connect
// -------------------------------------------------------------------
boolean mqtt_connect(){
    mqttClient.setServer(mqtt_server, mqtt_port);
    mqttClient.setCallback(callback);
    log("[ INFO ] Intentando conexión al Broker MQTT...");
    // https://pubsubclient.knolleary.net/api.html  
    // https://www.amebaiot.com/zh/rtl8722dm-arduino-api-pubsubclient/

    // boolean connect (clientID)  
    // boolean connect (clientID, willTopic, willQoS, willRetain,willMessage)  
    // boolean connect (clientID, username, password)  
    // boolean connect (clientID, username, password, willTopic, willQoS, willRetain, willMessage)  
    // * boolean connect (clientID, username, password, willTopic, willQoS, willRetain, willMessage, cleanSession) 

    /* 
        Parámetros id: ID de cliente, un identificador de cadena único 
        usuario: nombre de usuario para autenticación, valor predeterminado NULL 
        pass: contraseña para autenticación, valor predeterminado NULL 
        willTopic: el tema que utilizará el mensaje 
        willQoS: la calidad del servicio que utilizará el mensaje will 
        willRetain: si el testamento debe publicarse con el indicador de retención 
        willMessage: la carga del mensaje del testamento
        cleanSession: Si cleansession se establece en true , se eliminarán todos los temas suscritos
    */

    // Topico para enviar los estados.
    String topic_publish = pathMqtt()+"/status";//topico
    topic_publish.toCharArray(willTopic, 150);

    // Función para generar la conexión al Broker
    // Intento de reconectar
    if(mqttClient.connect(mqtt_cloud_id, mqtt_user, mqtt_password, willTopic, willQoS, willRetain, willMessage.c_str(), cleanSession)){
        log("[ INFO ] Conectado al Broker MQTT");
        String topic_subscribe = pathMqtt()+"/command"; //para recibir comandos
        topic_subscribe.toCharArray(topic, 150);

        // Nos suscribimos a comandos Topico: v1/device/usuario/dispositivo/comando
        // boolean subscribe (topic)
        // * boolean subscribe (topic, [qos])
        // qos - optional the qos to subscribe at (int: 0 or 1 only)

        // Función para suscribirnos al Topico
        if(mqttClient.subscribe(topic, mqtt_qos)){
            log("[ INFO ] Suscrito: " + String(topic));
        }else{
            log("[ ERROR ] Failed, to suscribe!"); 
        }
        // Si tenemos habilitado en envío de estados enviamos en mensaje de conectado
        if(mqtt_status_send){
            // int publish (topic, payload)
            //  * int publish (topic, payload, retained)
            // int publish (topic, payload, length, retained)
            // topic - the topic to publish to (const char[])
            // payload - the message to publish (const char[])
            // retained - informacion retenida (boolean)
            // length - the length of the message (byte)
            mqttClient.publish(willTopic, "{\"connected\": true}", mqtt_retain);
        }
    }else{
        log("[ ERROR ] failed, rc= " + mqttClient.state());
        return (0);
    }
    return (1);
}
// -------------------------------------------------------------------
// Manejo de los Mensajes Entrantes
// -------------------------------------------------------------------
void callback(char *topic, byte *payload, unsigned int length){
    String mensaje = "";
    String str_topic(topic);
    for(int16_t i = 0; i < length; i++){
        mensaje += (char)payload[i];
        // Parpadeo del Led en cada recepción de caracteres
        mqttRX();
    }
    WsMessage(getSendJson("Inactivo","mqtt"), "","");
    mensaje.trim();
    log("[ INFO ] Topico -->" + str_topic);
    log("[ INFO ] Mensaje -->" + mensaje);
    // mandar el comando a la función
    OnOffRelays(mensaje);
}
// -------------------------------------------------------------------
// Manejo de los Mensajes Salientes
// ------------------------------------------------------------------- 
void mqtt_publish(){
    //log("MQTT Publicando:");
    String topic = pathMqtt()+"/device"; //podria ser "/valores" al final
    mqtt_data = Json();
    mqttClient.publish(topic.c_str(), mqtt_data.c_str(), mqtt_retain);
    mqtt_data = "";
    mqttTX();
    WsMessage(getSendJson("Inactivo","mqtt"), "","");
}
// -------------------------------------------------------------------
// JSON con información del Dispositivo para envio por MQTT v1/devices/L4L0S4N/ESPWROOM325AF6B8701CF1/#
// ------------------------------------------------------------------- 
String Json(){
    String response;
    DynamicJsonDocument jsonDoc(3000);
    jsonDoc["device_serial"] = deviceID();//ok
    jsonDoc["ALARM_NAME1"] = ALARM_NAME1;
    jsonDoc["ALARM_STATUS1"] = ALARM_STATUS1;
    jsonDoc["ALARM_TIMEON1"] = ALARM_TIMEON1;
    jsonDoc["ALARM_TIMEOFF1"] = ALARM_TIMEOFF1;
    jsonDoc["ALARM_NAME2"] = ALARM_NAME2;
    jsonDoc["ALARM_STATUS2"] = ALARM_STATUS2;
    jsonDoc["ALARM_TIMEON2"] = ALARM_TIMEON2;
    jsonDoc["ALARM_TIMEOFF2"] = ALARM_TIMEOFF2;
    jsonDoc["ALARM_NAME3"] = ALARM_NAME3;
    jsonDoc["ALARM_STATUS3"] = ALARM_STATUS3;
    jsonDoc["ALARM_TIMEON3"] = ALARM_TIMEON3;
    jsonDoc["ALARM_TIMEOFF3"] = ALARM_TIMEOFF3;
    jsonDoc["ALARM_NAME4"] = ALARM_NAME4;
    jsonDoc["ALARM_STATUS4"] = ALARM_STATUS4;
    jsonDoc["ALARM_TIMEON4"] = ALARM_TIMEON4;
    jsonDoc["ALARM_TIMEOFF4"] = ALARM_TIMEOFF4;
    jsonDoc["ALARM_NAME5"] = ALARM_NAME5;
    jsonDoc["ALARM_STATUS5"] = ALARM_STATUS5;
    jsonDoc["ALARM_TIMEON5"] = ALARM_TIMEON5;
    jsonDoc["ALARM_TIMEOFF5"] = ALARM_TIMEOFF5;
    jsonDoc["ALARM_NAME6"] = ALARM_NAME6;
    jsonDoc["ALARM_STATUS6"] = ALARM_STATUS6;
    jsonDoc["ALARM_TIMEON6"] = ALARM_TIMEON6;
    jsonDoc["ALARM_TIMEOFF6"] = ALARM_TIMEOFF6;
    jsonDoc["ALARM_NAME7"] = ALARM_NAME7;
    jsonDoc["ALARM_STATUS7"] = ALARM_STATUS7;
    jsonDoc["ALARM_TIMEON7"] = ALARM_TIMEON7;
    jsonDoc["ALARM_TIMEOFF7"] = ALARM_TIMEOFF7;
    jsonDoc["ALARM_NAME8"] = ALARM_NAME8;
    jsonDoc["ALARM_STATUS8"] = ALARM_STATUS8;
    jsonDoc["ALARM_TIMEON8"] = ALARM_TIMEON8;
    jsonDoc["ALARM_TIMEOFF8"] = ALARM_TIMEOFF8;
    jsonDoc["temp_cpu"] = String(round(TempCPUValue()),1);
    //jsonDoc["device_manufacturer"] = String(device_manufacturer);
    //jsonDoc["device_fw_version"] = device_fw_version;
    //jsonDoc["device_hw_version"] = String(device_hw_version);
    //jsonDoc["device_sdk"] = String(ESP.getSdkVersion());
    //jsonDoc["device_time_active"] = String(longTimeStr(millis() / 1000));
    //jsonDoc["device_ram_available"] = String(ESP.getFreeHeap()); 
    //jsonDoc["device_ram_size"] =  String(ESP.getHeapSize());
    //jsonDoc["device_spiffs_total"] = String(SPIFFS.totalBytes());      
    //jsonDoc["device_spiffs_used"] = String(SPIFFS.usedBytes());
    //jsonDoc["device_cpu_clock"] = String(getCpuFrequencyMhz());
    //jsonDoc["device_flash_size"] = String(ESP.getFlashChipSize() / (1024.0 * 1024), 2);
    //jsonDoc["device_restart"] = String(device_restart);
    serializeJson(jsonDoc, response);
    return response;
} 
// -------------------------------------------------------------------
// MQTT Loop Principal
// -------------------------------------------------------------------
void mqttLoop(){
    //log("entro al mqttLoop");
    if(mqtt_cloud_enable){ //si es true osea si esta habilitado
        //log("MQTT habilitado");
        if(!mqttClient.connected()){//si no esta conectado
            //log("mqtt no -conectado");
            long now = millis();
            // Intente conectarse continuamente durante los primeros 60 segundos
            // y luego vuelva a intentarlo una vez cada 120 segundos
            if((now < 60000) || ((now - lastMqttReconnectAttempt) > 120000)){
                lastMqttReconnectAttempt = now;
                // Intento de reconectar
                if(mqtt_connect()){ //si esta conectado
                    lastMqttReconnectAttempt = 0;
                }
                // Poner en ON el Led del MQTT
                setOnSingle(MQTTLED); 
            }
        }else{
            mqttClient.loop();
            // Poner en OFF el Led del MQTT
            //log("mqtt conectado");
            setOffSingle(MQTTLED);
        }
    }
}
