// Variables globales del ESP32

// ---------------------------------------------------
// Definiciones
// ---------------------------------------------------
#define WIFILED 12                                      //GPIO12 LED WIFI
#define MQTTLED 13                                      //GPIO13 LED MQTT
// ------------------------------------------------------
// CALCULAR La CAPACIDAD DEL JSON
// Asistente Arduino Json: https://arduinojson.org/v6/assistant/#/step2
// ------------------------------------------------------
const size_t capacitySettings = 2536;

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
int wifi_mode = WIFI_STA;

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
//----------------------------------------------------
//   Zona time
//----------------------------------------------------
ESP32Time rtc;              //Clase ESP32Time

bool time_ajuste;           // 1- Manual , 0- Automático internet SRV NTP
char time_date[18];         // 2022-09-07T23:47
long time_z_horaria;        // Zona Horaria GMT 0 = 0 -GMT +1 = 3600 - GMT -1 = -3600
char time_server[39];       // Servidor NTP Elemplo: time.mist.gov

int time_hr;                // Hora 0 -23
int time_mn;                // Minutos 0 - 59
int time_sc;                // Segundos 0-59
int time_dy;                // Días 1 - 31
int time_mt;                // Meses 1- 12
int time_yr;                // Año 2023

// NTP Server
WiFiUDP ntpUDP;
NTPClient ntpClient(ntpUDP);

long lastTime = 0;          // Variable para tiempo de envio por WS
long lastTime2 = 0;         // variable para tiempo de envio de Alarmas
// ---------------------------------------------------
// Zona de Relays
// ---------------------------------------------------
bool        RELAY_STATUS;
int         RELAY_LOGICA;
uint8_t     RELAY_PIN;
String      RELAY_NAME;
String      RELAY_DESCRIPTION;
// ---------------------------------------------------
// Zona de alarmas
// ---------------------------------------------------
bool    ALARM_STATUS1, ALARM_STATUS2, ALARM_STATUS3, ALARM_STATUS4;
bool    ALARM_STATUS5, ALARM_STATUS6, ALARM_STATUS7, ALARM_STATUS8;
// guardar la logica, el pin y el nombre en el vue32_settings en lectura renglon 77
bool    ALARM_LOGICA1, ALARM_LOGICA2, ALARM_LOGICA3, ALARM_LOGICA4;
bool    ALARM_LOGICA5, ALARM_LOGICA6, ALARM_LOGICA7, ALARM_LOGICA8;
uint8_t ALARM_PIN1, ALARM_PIN2, ALARM_PIN3, ALARM_PIN4;
uint8_t ALARM_PIN5, ALARM_PIN6, ALARM_PIN7, ALARM_PIN8;
String  ALARM_NAME1, ALARM_NAME2, ALARM_NAME3, ALARM_NAME4;
String  ALARM_NAME5, ALARM_NAME6, ALARM_NAME7, ALARM_NAME8;
String  ALARM_TIMEON1, ALARM_TIMEON2, ALARM_TIMEON3, ALARM_TIMEON4;
String  ALARM_TIMEON5, ALARM_TIMEON6, ALARM_TIMEON7, ALARM_TIMEON8;
String  ALARM_TIMEOFF1, ALARM_TIMEOFF2, ALARM_TIMEOFF3, ALARM_TIMEOFF4;
String  ALARM_TIMEOFF5, ALARM_TIMEOFF6, ALARM_TIMEOFF7, ALARM_TIMEOFF8;
int     ALARM_CONT1, ALARM_CONT2, ALARM_CONT3, ALARM_CONT4;
int     ALARM_CONT5, ALARM_CONT6, ALARM_CONT7, ALARM_CONT8;