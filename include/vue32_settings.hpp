// Definicion de funciones
boolean settingRead();  //lectura
void settingsReset();    //reinicia
boolean settingSave();  //salva

boolean settingRead(){
    DynamicJsonDocument jsonSettings(capacitySettings);
    File file = SPIFFS.open("/settings.json", "r");
    if(deserializeJson(jsonSettings, file)){ //si ocurre un error manda un verdadero asi trabaja la libreria
        settingsReset();
        // si da un error osea es verdadero hay que iniciar con valores de fabrica
        DeserializationError error = deserializeJson(jsonSettings, file);
        log("[ ERROR ] Falló la lectura de las configuraciones, tomando valores por defecto");
        if (error){
            log("[ ERROR ] " + String(error.c_str())); //se convierte de un char a un string
        }
        return false;
    }else{
        // ---------------------------------------------
        // si no hubo error:
        // Dispositivo settings.json
        // ---------------------------------------------
        device_config_file = jsonSettings["device_config_file"];
        strlcpy(device_config_serial, jsonSettings["device_config_serial"],sizeof(device_config_serial));
        strlcpy(device_id, jsonSettings["device_id"], sizeof(device_id)); 
        strlcpy(device_old_user, jsonSettings["device_old_user"], sizeof(device_old_user)); 
        strlcpy(device_old_password, jsonSettings["device_old_password"], sizeof(device_old_password)); 
        // ---------------------------------------------
        // WIFI Cliente settings.json
        // ---------------------------------------------
        wifi_ip_static = jsonSettings["wifi_ip_static"];
        strlcpy(wifi_ssid, jsonSettings["wifi_ssid"], sizeof(wifi_ssid)); //copia de un json a una variable tipo char(strlcpy)
        strlcpy(wifi_password, jsonSettings["wifi_password"], sizeof(wifi_password));        
        strlcpy(wifi_ipv4, jsonSettings["wifi_ipv4"], sizeof(wifi_ipv4));
        strlcpy(wifi_subnet, jsonSettings["wifi_subnet"], sizeof(wifi_subnet));
        strlcpy(wifi_gateway, jsonSettings["wifi_gateway"], sizeof(wifi_gateway));
        strlcpy(wifi_dns_primary, jsonSettings["wifi_dns_primary"], sizeof(wifi_dns_primary));
        strlcpy(wifi_dns_secondary, jsonSettings["wifi_dns_secondary"], sizeof(wifi_dns_secondary));
        // ---------------------------------------------
        // WIFI AP settings.json
        // ---------------------------------------------
        ap_mode = jsonSettings["ap_mode"];
        strlcpy(ap_ssid, jsonSettings["ap_ssid"], sizeof(ap_ssid));
        strlcpy(ap_password, jsonSettings["ap_password"], sizeof(ap_password));
        ap_visibility = jsonSettings["ap_visibility"];
        ap_chanel = jsonSettings["ap_chanel"];
        ap_connect = jsonSettings["ap_connect"];
        // ---------------------------------------------
        // Conexion al broker MQTT Cloud settings.json
        // ---------------------------------------------
        mqtt_cloud_enable = jsonSettings["mqtt_cloud_enable"];
        strlcpy(mqtt_user, jsonSettings["mqtt_user"], sizeof(mqtt_user));
        strlcpy(mqtt_password, jsonSettings["mqtt_password"], sizeof(mqtt_password));
        strlcpy(mqtt_server, jsonSettings["mqtt_server"], sizeof(mqtt_server));
        strlcpy(mqtt_cloud_id, jsonSettings["mqtt_cloud_id"], sizeof(mqtt_cloud_id));
        mqtt_port = jsonSettings["mqtt_port"];
        mqtt_retain = jsonSettings["mqtt_retain"];
        mqtt_qos = jsonSettings["mqtt_qos"];
        mqtt_time_send = jsonSettings["mqtt_time_send"];
        mqtt_time_interval = jsonSettings["mqtt_time_interval"];
        mqtt_status_send = jsonSettings["mqtt_status_send"];

        file.close();
        log("[ INFO ] Lectura de las configuraciones correcta");
        return true;
    }
}
// -------------------------------------------------------------------
// Valores de Fábrica al settings.json
// -------------------------------------------------------------------
void settingsReset(){
    // -------------------------------------------------------------------
    // Dispositivo settings.json
    // -------------------------------------------------------------------
    device_config_file = true;
    strlcpy(device_config_serial, deviceID().c_str() ,sizeof(device_config_serial));
    strlcpy(device_id, "adminvue32", sizeof(device_id));
    strlcpy(device_old_user, "admin", sizeof(device_old_user)); 
    strlcpy(device_old_password, "admin", sizeof(device_old_password)); 
    // -------------------------------------------------------------------
    // WIFI Cliente settings.json
    // -------------------------------------------------------------------
    wifi_ip_static = true; // false
    strlcpy(wifi_ssid, "INFINITUM59W1_2.4", sizeof(wifi_ssid));//cambiar a telmex //"INFINITUMD378" //INFINITUM59W1_2.4//INFINITUMF69D_2.4
    strlcpy(wifi_password, "unJvpTX5Vp", sizeof(wifi_password));//cambiar            //"Pm2Kj1Jg6j"    //unJvpTX5Vp      //89r3X2Z7nJ
    strlcpy(wifi_ipv4, "192.168.1.164", sizeof(wifi_ipv4)); // trabajo192.168.1.150 //en casa 192.168.1.75
    strlcpy(wifi_subnet, "255.255.255.0", sizeof(wifi_subnet));
    strlcpy(wifi_gateway, "192.168.1.254", sizeof(wifi_gateway));//192.168.1.254
    strlcpy(wifi_dns_primary, "192.168.1.254", sizeof(wifi_dns_primary)); //8.8.8.8
    strlcpy(wifi_dns_secondary, "8.8.4.4", sizeof(wifi_dns_secondary)); 
    // -------------------------------------------------------------------
    // WIFI AP settings.json
    // -------------------------------------------------------------------
    ap_mode = false; //false
    strlcpy(ap_ssid, deviceID().c_str(), sizeof(ap_ssid));
    strlcpy(ap_password, "adminadmin", sizeof(ap_password));
    ap_visibility = false;        
    ap_chanel = 9;         
    ap_connect = 4;
    // -------------------------------------------------------------------
    // Cloud settings.json
    // -------------------------------------------------------------------
    mqtt_cloud_enable = true;
    strlcpy(mqtt_user, "L4L0S4N", sizeof(mqtt_user));
    strlcpy(mqtt_password, "ED0613620", sizeof(mqtt_password));
    strlcpy(mqtt_server, "broker.hivemq.com", sizeof(mqtt_server));
    strlcpy(mqtt_cloud_id, deviceID().c_str(), sizeof(mqtt_cloud_id));
    mqtt_port = 1883;
    mqtt_retain = false;
    mqtt_qos = 0;
    mqtt_time_send = true;
    mqtt_time_interval = 30000; //3o segundos
    mqtt_status_send = true;
    log("[ INFO ] Se reiniciaron todos los valores por defecto");    
}
// -------------------------------------------------------------------
// Guardar settings.json
// -------------------------------------------------------------------
boolean settingsSave(){
    // StaticJsonDocument<capacitySettings> jsonSettings;
    DynamicJsonDocument jsonSettings(capacitySettings);
    
    File file = SPIFFS.open("/settings.json", "w+"); //escritura

    if (file){ //si se puede abiri
        // -------------------------------------------------------------------
        // Dispositivo settings.json
        // -------------------------------------------------------------------
        jsonSettings["device_config_file"] = device_config_file; //clave:valor
        jsonSettings["device_config_serial"] = device_config_serial;
        jsonSettings["device_id"] = device_id;
        jsonSettings["device_old_user"] = device_old_user; 
        jsonSettings["device_old_password"] = device_old_password;
        // -------------------------------------------------------------------
        // WIFI Cliente settings.json
        // -------------------------------------------------------------------
        jsonSettings["wifi_ip_static"] = wifi_ip_static;
        jsonSettings["wifi_ssid"] = wifi_ssid;
        jsonSettings["wifi_password"] = wifi_password;
        jsonSettings["wifi_ipv4"] = wifi_ipv4;
        jsonSettings["wifi_subnet"] = wifi_subnet;
        jsonSettings["wifi_gateway"] = wifi_gateway;
        jsonSettings["wifi_dns_primary"] = wifi_dns_primary;
        jsonSettings["wifi_dns_secondary"] = wifi_dns_secondary;
        // -------------------------------------------------------------------
        // WIFI AP settings.json
        // -------------------------------------------------------------------
        jsonSettings["ap_mode"] = ap_mode;
        jsonSettings["ap_ssid"] = ap_ssid;
        jsonSettings["ap_password"] = ap_password;
        jsonSettings["ap_visibility"] = ap_visibility;
        jsonSettings["ap_chanel"] = ap_chanel;
        jsonSettings["ap_connect"] = ap_connect;
        // -------------------------------------------------------------------
        // Cloud settings.json
        // -------------------------------------------------------------------
        jsonSettings["mqtt_cloud_enable"] = mqtt_cloud_enable;
        jsonSettings["mqtt_user"] = mqtt_user;
        jsonSettings["mqtt_password"] = mqtt_password;
        jsonSettings["mqtt_server"] = mqtt_server;
        jsonSettings["mqtt_cloud_id"] = mqtt_cloud_id;
        jsonSettings["mqtt_port"] = mqtt_port;
        jsonSettings["mqtt_retain"] = mqtt_retain;
        jsonSettings["mqtt_qos"] = mqtt_qos;
        jsonSettings["mqtt_time_send"] = mqtt_time_send;
        jsonSettings["mqtt_time_interval"] = mqtt_time_interval;
        jsonSettings["mqtt_status_send"] = mqtt_status_send; 

        serializeJsonPretty(jsonSettings, file);
        file.close();
        log("[ INFO ] Configuración Guardada correctamente");
        serializeJsonPretty(jsonSettings, Serial);
        return true;
    }else{
        log("[ ERROR ] Falló el guardado de la configuración");
        return false;
    }
}