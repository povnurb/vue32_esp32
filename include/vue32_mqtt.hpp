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

bool MqttPinAlarma1();
bool MqttPinAlarma2();
bool MqttPinAlarma3();
bool MqttPinAlarma4();
bool MqttPinAlarma5();
bool MqttPinAlarma6();
bool MqttPinAlarma7();
bool MqttPinAlarma8();

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
    DynamicJsonDocument jsonDoc(3000); //se puede reducir a 2500
    jsonDoc["device_serial"] = deviceID();//ok
    jsonDoc["ALARM_NAME1"] = ALARM_NAME1;
    jsonDoc["ALARM_STATUS1"] = MqttPinAlarma1();
    jsonDoc["ALARM_TIMEON1"] = ALARM_TIMEON1;
    jsonDoc["ALARM_TIMEOFF1"] = ALARM_TIMEOFF1;
    jsonDoc["ALARM_NAME2"] = ALARM_NAME2;
    jsonDoc["ALARM_STATUS2"] = MqttPinAlarma2();
    jsonDoc["ALARM_TIMEON2"] = ALARM_TIMEON2;
    jsonDoc["ALARM_TIMEOFF2"] = ALARM_TIMEOFF2;
    jsonDoc["ALARM_NAME3"] = ALARM_NAME3;
    jsonDoc["ALARM_STATUS3"] = MqttPinAlarma3();
    jsonDoc["ALARM_TIMEON3"] = ALARM_TIMEON3;
    jsonDoc["ALARM_TIMEOFF3"] = ALARM_TIMEOFF3;
    jsonDoc["ALARM_NAME4"] = ALARM_NAME4;
    jsonDoc["ALARM_STATUS4"] = MqttPinAlarma4();
    jsonDoc["ALARM_TIMEON4"] = ALARM_TIMEON4;
    jsonDoc["ALARM_TIMEOFF4"] = ALARM_TIMEOFF4;
    jsonDoc["ALARM_NAME5"] = ALARM_NAME5;
    jsonDoc["ALARM_STATUS5"] = MqttPinAlarma5();
    jsonDoc["ALARM_TIMEON5"] = ALARM_TIMEON5;
    jsonDoc["ALARM_TIMEOFF5"] = ALARM_TIMEOFF5;
    jsonDoc["ALARM_NAME6"] = ALARM_NAME6;
    jsonDoc["ALARM_STATUS6"] = MqttPinAlarma6();
    jsonDoc["ALARM_TIMEON6"] = ALARM_TIMEON6;
    jsonDoc["ALARM_TIMEOFF6"] = ALARM_TIMEOFF6;
    jsonDoc["ALARM_NAME7"] = ALARM_NAME7;
    jsonDoc["ALARM_STATUS7"] = MqttPinAlarma7();
    jsonDoc["ALARM_TIMEON7"] = ALARM_TIMEON7;
    jsonDoc["ALARM_TIMEOFF7"] = ALARM_TIMEOFF7;
    jsonDoc["ALARM_NAME8"] = ALARM_NAME8;
    jsonDoc["ALARM_STATUS8"] = MqttPinAlarma8();
    jsonDoc["ALARM_TIMEON8"] = ALARM_TIMEON8;
    jsonDoc["ALARM_TIMEOFF8"] = ALARM_TIMEOFF8;
    jsonDoc["temp_cpu"] = String(round(TempCPUValue()),1);
    jsonDoc["tempC"] = String(round(Temperatura()),1);
    jsonDoc["humedad"] = String(round(Humedad()),1);
    jsonDoc["tmin"] = String(round(tempMin()),1);
    jsonDoc["tmax"] = String(round(tempMax()),1);
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
// alarmas estados mqtt
bool MqttPinAlarma1(){

    if (!ALARM_LOGICA1){
        alarma1 = {ALARM_PIN1,ALARM_NAME1,ALARM_LOGICA1,INPUT_PULLUP};
        pinMode(alarma1.PIN,alarma1.MODE);
        if (digitalRead(alarma1.PIN)){
            ALARM_STATUS1=true;
        }else
        {
            ALARM_STATUS1=false;
        }
    }else{
        alarma1 = {ALARM_PIN1,ALARM_NAME1,ALARM_LOGICA1,INPUT_PULLDOWN};
        pinMode(alarma1.PIN,alarma1.MODE);
        if (digitalRead(alarma1.PIN)){
            ALARM_STATUS1=false;
        }else
        {
            ALARM_STATUS1=true;
        }
    }
    return ALARM_STATUS1; 
}

bool MqttPinAlarma2(){

    if (!ALARM_LOGICA2){
        alarma2 = {ALARM_PIN2,ALARM_NAME2,ALARM_LOGICA2,INPUT_PULLUP};
        pinMode(alarma2.PIN,alarma2.MODE);
        if (digitalRead(alarma2.PIN)){
            ALARM_STATUS2=true;
        }else
        {
            ALARM_STATUS2=false;
        }
    }else{
        alarma2 = {ALARM_PIN2,ALARM_NAME2,ALARM_LOGICA2,INPUT_PULLDOWN};
        pinMode(alarma2.PIN,alarma2.MODE);
        if (digitalRead(alarma2.PIN)){
            ALARM_STATUS2=false;
        }else
        {
            ALARM_STATUS2=true;
        }
    }
    return ALARM_STATUS2; 
}
bool MqttPinAlarma3(){

    if (!ALARM_LOGICA3){
        alarma3 = {ALARM_PIN3,ALARM_NAME3,ALARM_LOGICA3,INPUT_PULLUP};
        pinMode(alarma3.PIN,alarma3.MODE);
        if (digitalRead(alarma3.PIN)){
            ALARM_STATUS3=true;
        }else
        {
            ALARM_STATUS3=false;
        }
    }else{
        alarma3 = {ALARM_PIN3,ALARM_NAME3,ALARM_LOGICA3,INPUT_PULLDOWN};
        pinMode(alarma3.PIN,alarma3.MODE);
        if (digitalRead(alarma3.PIN)){
            ALARM_STATUS3=false;
        }else
        {
            ALARM_STATUS3=true;
        }
    }
    return ALARM_STATUS3; 
}
bool MqttPinAlarma4(){

    if (!ALARM_LOGICA4){
        alarma4 = {ALARM_PIN4,ALARM_NAME4,ALARM_LOGICA4,INPUT_PULLUP};
        pinMode(alarma4.PIN,alarma4.MODE);
        if (digitalRead(alarma4.PIN)){
            ALARM_STATUS4=true;
        }else
        {
            ALARM_STATUS4=false;
        }
    }else{
        alarma4 = {ALARM_PIN4,ALARM_NAME4,ALARM_LOGICA4,INPUT_PULLDOWN};
        pinMode(alarma4.PIN,alarma4.MODE);
        if (digitalRead(alarma4.PIN)){
            ALARM_STATUS4=false;
        }else
        {
            ALARM_STATUS4=true;
        }
    }
    return ALARM_STATUS4; 
}
bool MqttPinAlarma5(){

    if (!ALARM_LOGICA5){
        alarma5 = {ALARM_PIN5,ALARM_NAME5,ALARM_LOGICA5,INPUT_PULLUP};
        pinMode(alarma5.PIN,alarma5.MODE);
        if (digitalRead(alarma5.PIN)){
            ALARM_STATUS5=true;
        }else
        {
            ALARM_STATUS5=false;
        }
    }else{
        alarma5 = {ALARM_PIN5,ALARM_NAME5,ALARM_LOGICA5,INPUT_PULLDOWN};
        pinMode(alarma5.PIN,alarma5.MODE);
        if (digitalRead(alarma5.PIN)){
            ALARM_STATUS5=false;
        }else
        {
            ALARM_STATUS5=true;
        }
    }
    return ALARM_STATUS5; 
}
bool MqttPinAlarma6(){

    if (!ALARM_LOGICA6){
        alarma6 = {ALARM_PIN6,ALARM_NAME6,ALARM_LOGICA6,INPUT_PULLUP};
        pinMode(alarma6.PIN,alarma6.MODE);
        if (digitalRead(alarma6.PIN)){
            ALARM_STATUS6=true;
        }else
        {
            ALARM_STATUS6=false;
        }
    }else{
        alarma6 = {ALARM_PIN6,ALARM_NAME6,ALARM_LOGICA6,INPUT_PULLDOWN};
        pinMode(alarma6.PIN,alarma6.MODE);
        if (digitalRead(alarma6.PIN)){
            ALARM_STATUS6=false;
        }else
        {
            ALARM_STATUS6=true;
        }
    }
    return ALARM_STATUS6; 
}
bool MqttPinAlarma7(){

    if (!ALARM_LOGICA7){
        alarma7 = {ALARM_PIN7,ALARM_NAME7,ALARM_LOGICA7,INPUT_PULLUP};
        pinMode(alarma7.PIN,alarma7.MODE);
        if (digitalRead(alarma7.PIN)){
            ALARM_STATUS7=true;
        }else
        {
            ALARM_STATUS7=false;
        }
    }else{
        alarma7 = {ALARM_PIN7,ALARM_NAME7,ALARM_LOGICA7,INPUT_PULLDOWN};
        pinMode(alarma7.PIN,alarma7.MODE);
        if (digitalRead(alarma7.PIN)){
            ALARM_STATUS7=false;
        }else
        {
            ALARM_STATUS7=true;
        }
    }
    return ALARM_STATUS7; 
}
bool MqttPinAlarma8(){

    if (!ALARM_LOGICA8){
        alarma8 = {ALARM_PIN8,ALARM_NAME8,ALARM_LOGICA8,INPUT_PULLUP};
        pinMode(alarma8.PIN,alarma8.MODE);
        if (digitalRead(alarma8.PIN)){
            ALARM_STATUS8=true;
        }else
        {
            ALARM_STATUS8=false;
        }
    }else{
        alarma8 = {ALARM_PIN8,ALARM_NAME8,ALARM_LOGICA8,INPUT_PULLDOWN};
        pinMode(alarma8.PIN,alarma8.MODE);
        if (digitalRead(alarma8.PIN)){
            ALARM_STATUS8=false;
        }else
        {
            ALARM_STATUS8=true;
        }
    }
    return ALARM_STATUS8; 
}