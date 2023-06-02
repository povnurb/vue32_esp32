// Definicion de funciones
boolean settingRead();  //lectura
void settingsReset();    //reinicia
boolean settingsSave();  //salva

boolean settingRead(){
    DynamicJsonDocument jsonSettings(capacitySettings);
    //DynamicJsonDocument jsonSettings(3000);
    
    File file = SPIFFS.open("/settings.json", "r");
    if(deserializeJson(jsonSettings, file)){ //si ocurre un error manda un verdadero asi trabaja la libreria
        settingsReset();
        // si da un error osea es verdadero hay que iniciar con valores de fabrica
        DeserializationError error = deserializeJson(jsonSettings, file);
        log("[ ERROR:vue32_settings.hpp ] Falló la lectura de las configuraciones, tomando valores por defecto");
        if (error){
            log("[ ERROR:vue32_settings.hpp ] " + String(error.c_str())); //se convierte de un char a un string
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

        // Time settings.json
        time_ajuste = jsonSettings["time_ajuste"];
        strlcpy(time_date, jsonSettings["time_date"], sizeof(time_date));
        time_z_horaria = jsonSettings["time_z_horaria"];
        strlcpy(time_server, jsonSettings["time_server"], sizeof(time_server));

        //----------------------------------------------
        // Relay settings.json
        //----------------------------------------------
        RELAY_STATUS = jsonSettings["RELAY_STATUS"].as<bool>();
        RELAY_PIN = jsonSettings["RELAY_PIN"].as<int>();
        RELAY_LOGICA = jsonSettings["RELAY_LOGICA"].as<int>();
        RELAY_NAME = jsonSettings["RELAY_NAME"].as<String>();
        RELAY_DESCRIPTION = jsonSettings["RELAY_DESCRIPTION"].as<String>();

        // ---------------------------------------------------------
        //  ZONA DE ALARMAS
        // ---------------------------------------------------------
        ALARM_LOGICA1 = jsonSettings["ALARM_LOGICA1"].as<bool>();
        ALARM_NAME1 = jsonSettings["ALARM_NAME1"].as<String>();
        ALARM_PIN1 = jsonSettings["ALARM_PIN1"].as<int>();
        ALARM_LOGICA2 = jsonSettings["ALARM_LOGICA2"].as<bool>();
        ALARM_NAME2 = jsonSettings["ALARM_NAME2"].as<String>();
        ALARM_PIN2 = jsonSettings["ALARM_PIN2"].as<int>();
        ALARM_LOGICA3 = jsonSettings["ALARM_LOGICA3"].as<bool>();
        ALARM_NAME3 = jsonSettings["ALARM_NAME3"].as<String>();
        ALARM_PIN3 = jsonSettings["ALARM_PIN3"].as<int>();
        ALARM_LOGICA4 = jsonSettings["ALARM_LOGICA4"].as<bool>();
        ALARM_NAME4 = jsonSettings["ALARM_NAME4"].as<String>();
        ALARM_PIN4 = jsonSettings["ALARM_PIN4"].as<int>();
        ALARM_LOGICA5 = jsonSettings["ALARM_LOGICA5"].as<bool>();
        ALARM_NAME5 = jsonSettings["ALARM_NAME5"].as<String>();
        ALARM_PIN5 = jsonSettings["ALARM_PIN5"].as<int>();
        ALARM_LOGICA6 = jsonSettings["ALARM_LOGICA6"].as<bool>();
        ALARM_NAME6 = jsonSettings["ALARM_NAME6"].as<String>();
        ALARM_PIN6 = jsonSettings["ALARM_PIN6"].as<int>();
        ALARM_LOGICA7 = jsonSettings["ALARM_LOGICA7"].as<bool>();
        ALARM_NAME7 = jsonSettings["ALARM_NAME7"].as<String>();
        ALARM_PIN7 = jsonSettings["ALARM_PIN7"].as<int>();
        ALARM_LOGICA8 = jsonSettings["ALARM_LOGICA8"].as<bool>();
        ALARM_NAME8 = jsonSettings["ALARM_NAME8"].as<String>();
        ALARM_PIN8 = jsonSettings["ALARM_PIN8"].as<int>();

        file.close();
        log("[ INFO:vue32_settings.hpp ] Lectura de las configuraciones correcta");
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
    strlcpy(device_old_password, "personal", sizeof(device_old_password)); 
    // -------------------------------------------------------------------
    // WIFI Cliente settings.json
    // -------------------------------------------------------------------
    wifi_ip_static = false; // false
    strlcpy(wifi_ssid, "INFINITUM59W1_2.4", sizeof(wifi_ssid));//"INFINITUMD378" //INFINITUM59W1_2.4//INFINITUMF69D_2.4
    strlcpy(wifi_password, "unJvpTX5Vp", sizeof(wifi_password));//"Pm2Kj1Jg6j"    //unJvpTX5Vp      //89r3X2Z7nJ
    strlcpy(wifi_ipv4, "10.4.30.15", sizeof(wifi_ipv4)); // trabajo192.168.1.150 //en casa 192.168.1.75
    strlcpy(wifi_subnet, "255.255.255.0", sizeof(wifi_subnet));
    strlcpy(wifi_gateway, "10.4.30.254", sizeof(wifi_gateway));//192.168.1.254
    strlcpy(wifi_dns_primary, "10.192.10.1", sizeof(wifi_dns_primary)); //8.8.8.8
    strlcpy(wifi_dns_secondary, "10.106.10.2", sizeof(wifi_dns_secondary)); //8.8.4.4
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
    strlcpy(mqtt_user, "lalo", sizeof(mqtt_user)); //lalo79
    strlcpy(mqtt_password, "public", sizeof(mqtt_password)); //public
    strlcpy(mqtt_server, "iotmx.com", sizeof(mqtt_server)); //iotmx.com
    strlcpy(mqtt_cloud_id, deviceID().c_str(), sizeof(mqtt_cloud_id));
    mqtt_port = 1883;
    mqtt_retain = false;
    mqtt_qos = 0;
    mqtt_time_send = true;
    mqtt_time_interval = 10000; //3o segundos
    mqtt_status_send = true;
    log("[ INFO:vue32_settings.hpp ] Se reiniciaron todos los valores por defecto");   

    // -------------------------------------------------------------------
    // Time settings.json
    // -------------------------------------------------------------------
    time_ajuste = true;
    strlcpy(time_date, "2023-03-04T10:09", sizeof(time_date));
    time_z_horaria = -14400;
    strlcpy(time_server, "time.nist.gov", sizeof(time_server));
    // ------------------------------------------------------------
    // Relay settings.json
    // ------------------------------------------------------------
    RELAY_STATUS = false;
    RELAY_PIN = 33;
    RELAY_LOGICA = 0;
    RELAY_NAME = "RELAY D33";
    RELAY_DESCRIPTION = "Control de Iluminación";
    // ------------------------------------------------------------
    // Zona de recuperacion de Alarmas
    // ------------------------------------------------------------
    ALARM_LOGICA1 = false;
    ALARM_NAME1 = "ALARMA 1";
    ALARM_PIN1 = 5;
    ALARM_LOGICA2 = false;
    ALARM_PIN2 = 14;
    ALARM_NAME2 = "ALARMA 2";
    ALARM_LOGICA3 = false;
    ALARM_PIN3 = 16;
    ALARM_NAME3 = "ALARMA 3";
    ALARM_LOGICA4 = false;
    ALARM_PIN4 = 17;
    ALARM_NAME4 = "ALARMA 4";
    ALARM_LOGICA5 = false;
    ALARM_PIN5 = 18;
    ALARM_NAME5 = "ALARMA 5";
    ALARM_LOGICA6 = false;
    ALARM_PIN6 = 25;
    ALARM_NAME6 = "ALARMA 6";
    ALARM_LOGICA7 = false;
    ALARM_PIN7 = 26;
    ALARM_NAME7 = "ALARMA 7";
    ALARM_LOGICA8 = false;
    ALARM_PIN8 = 27;
    ALARM_NAME8 = "ALARMA 8";
    log("[ INFO:vue32_settings.hpp ] Se reiniciaron todos los valores por defecto"); 
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

        // ---------------------------------------------------------------------------------
        // TIME settings.json
        // -------------------------------------------------------------------
        jsonSettings["time_ajuste"] = time_ajuste;
        jsonSettings["time_date"] = time_date;
        jsonSettings["time_z_horaria"] = time_z_horaria;
        jsonSettings["time_server"] = time_server;
        // --------------------------------------------------------------
        // Relay settings.json
        // --------------------------------------------------------------
        jsonSettings["RELAY_STATUS"] = RELAY_STATUS;
        jsonSettings["RELAY_PIN"] = RELAY_PIN;
        jsonSettings["RELAY_LOGICA"] = RELAY_LOGICA;
        jsonSettings["RELAY_NAME"] = RELAY_NAME;
        jsonSettings["RELAY_DESCRIPTION"] =RELAY_DESCRIPTION;
        // --------------------------------------------------------------
        // ALARMAS settings.json
        // --------------------------------------------------------------
        jsonSettings["ALARM_LOGICA1"] = ALARM_LOGICA1;
        jsonSettings["ALARM_NAME1"] = ALARM_NAME1;
        jsonSettings["ALARM_PIN1"] = ALARM_PIN1;
        jsonSettings["ALARM_LOGICA2"] = ALARM_LOGICA2;
        jsonSettings["ALARM_NAME2"] = ALARM_NAME2;
        jsonSettings["ALARM_PIN2"] = ALARM_PIN2;
        jsonSettings["ALARM_LOGICA3"] = ALARM_LOGICA3;
        jsonSettings["ALARM_NAME3"] = ALARM_NAME3;
        jsonSettings["ALARM_PIN3"] = ALARM_PIN3;
        jsonSettings["ALARM_LOGICA4"] = ALARM_LOGICA4;
        jsonSettings["ALARM_NAME4"] = ALARM_NAME4;
        jsonSettings["ALARM_PIN4"] = ALARM_PIN4;
        jsonSettings["ALARM_LOGICA5"] = ALARM_LOGICA5;
        jsonSettings["ALARM_NAME5"] = ALARM_NAME5;
        jsonSettings["ALARM_PIN5"] = ALARM_PIN5;
        jsonSettings["ALARM_LOGICA6"] = ALARM_LOGICA6;
        jsonSettings["ALARM_NAME6"] = ALARM_NAME6;
        jsonSettings["ALARM_PIN6"] = ALARM_PIN6;
        jsonSettings["ALARM_LOGICA7"] = ALARM_LOGICA7;
        jsonSettings["ALARM_NAME7"] = ALARM_NAME7;
        jsonSettings["ALARM_PIN7"] = ALARM_PIN7;
        jsonSettings["ALARM_LOGICA8"] = ALARM_LOGICA8;
        jsonSettings["ALARM_NAME8"] = ALARM_NAME8;
        jsonSettings["ALARM_PIN8"] = ALARM_PIN8;


        serializeJsonPretty(jsonSettings, file);
        file.close();
        log("[ INFO:vue32_settings.hpp ] Configuración Guardada correctamente");
        serializeJsonPretty(jsonSettings, Serial);
        return true;
    }else{
        log("[ ERROR:vue32_settings.hpp ] Falló el guardado de la configuración");
        return false;
    }
}

