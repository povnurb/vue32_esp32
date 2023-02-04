// ---------------------------------------------------
// Definiciones
// ---------------------------------------------------
#define WIFILED 12                                      //GPIO12 LED WIFI
#define MQTTLED 13                                      //GPIO13 LED MQTT
// ------------------------------------------------------
// CALCULAR La CAPACIDAD DEL JSON
// Asistente Arduino Json: https://arduinojson.org/v6/assistant/#/step2
// ------------------------------------------------------
const size_t capacitySettings = 1536;

// ---------------------------------------------------
// Versión de Firmware desde las variables de entorno platformio.ini
// ---------------------------------------------------
#define TEXTIFY(A) #A
#define ESCAPEQUOTE(A) TEXTIFY(A)
String device_fw_version = ESCAPEQUOTE(BUILD_TAG);
// ---------------------------------------------------
// Versión de Hardware y Fabricante
// ---------------------------------------------------
#define device_hw_version "ADMINVUE32 v1 00000000"      // Versión de Hardware
#define device_manufacturer "EDUARDO"                   // Fabricante
// ---------------------------------------------------
// Zona configuracion Dispositivo
// ---------------------------------------------------
boolean device_config_file;         //Identificador para archivo de configuración
char    device_config_serial[30];   //Numero de serie de cada Archivo de configuración unico
char    device_id[30];              //ID del dispositivo
int     device_restart;             //Almacena Número de reinicios
char    device_old_user[15];        //Usuario para acceso al servidor Web
char    device_old_password[15];    //Contraseña del usuario servidor Web
uint8_t ip[4];                      //convierte de string a IP Variable función convertir string a IP
// ---------------------------------------------------
// Zona configuración WIFI modo Cliente
// ---------------------------------------------------
boolean wifi_ip_static;             //Uso de IP Estática DHCP
char    wifi_ssid[30];              //Nombre de la red WiFi
char    wifi_password[30];          //Contraseña de la Red WiFi
char    wifi_ipv4[15];              //Dir IPv4 Estático
char    wifi_gateway[15];           //Dir IPv4 Gateway
char    wifi_subnet[15];            //Dir Ipv4 Subred
char    wifi_dns_primary[15];       //Dir IPv4 DNS primario
char    wifi_dns_secondary[15];     //Dir IPv4 DNS secundario
// ---------------------------------------------------
// Zona configuración WIFI modo AP
// ---------------------------------------------------
boolean ap_mode;                    //Uso de Modo AP
char    ap_ssid[31];                //Nombre del SSID AP
char    ap_password[63];            //Contraseña del AP
int     ap_chanel;                  //Canal AP
int     ap_visibility;              //Es visible o no el AP (0 -  visible 1 - Oculto)
int     ap_connect;                 //Número de conexiones en el AP máx 8 conexiones
// ---------------------------------------------------
// Zona configuración MQTT
// ---------------------------------------------------
boolean mqtt_cloud_enable;          //Habilitar MQTT Broker
char    mqtt_cloud_id[30];          //Cliente ID MQTT Broker
char    mqtt_user[30];              //Usuario MQTT broker
char    mqtt_password[39];          //Contraseña del MQTT Broker
char    mqtt_server[39];            //Servidor del MQTT Broker
int     mqtt_port;                  //Puerto servidor MQTT Broker
boolean mqtt_retain;                //Habilitar mensajes retenidos
int     mqtt_qos;                   //Calidad del servicio
boolean mqtt_time_send;             //Habilitar envio de datos
int     mqtt_time_interval;         //Tiempo de envio por MQTT en segundos
boolean mqtt_status_send;           //Habilitar envio de estados
// ---------------------------------------------------
// Zona Firmware Update 
// ---------------------------------------------------
size_t content_len;
#define U_PART U_SPIFFS
// ---------------------------------------------------
// Zona EEPROM para contador de reinicios
// -----------------------------------------
#define Start_Address 0
#define Restart_Address Start_Address + sizeof(int)
// ---------------------------------------------------
// Zona de alarmas
// ---------------------------------------------------
