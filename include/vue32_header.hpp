// Variables globales del ESP32

// ---------------------------------------------------
// Definiciones
// ---------------------------------------------------
#define WIFILED 12 // GPIO12 LED WIFI
#define MQTTLED 13 // GPIO13 LED MQTT
#define DHTPIN 2   // pin DHT
// ------------------------------------------------------
// CALCULAR La CAPACIDAD DEL JSON
// Asistente Arduino Json: https://arduinojson.org/v6/assistant/#/step2
// ------------------------------------------------------
const size_t capacitySettings = 2536; // 2536

// ---------------------------------------------------
// Versión de Firmware desde las variables de entorno platformio.ini
// ---------------------------------------------------
#define TEXTIFY(A) #A
#define ESCAPEQUOTE(A) TEXTIFY(A)
String device_fw_version = ESCAPEQUOTE(BUILD_TAG);
// ---------------------------------------------------
// Versión de Hardware y Fabricante
// ---------------------------------------------------
#define device_hw_version "ADMINVUE32 v1 00000000" // Versión de Hardware
#define device_manufacturer "povnurb@hotmail.com"  // Fabricante
//----------------------------------------------------
// Central a la que pertenece y sala
//----------------------------------------------------
char ctral[10]; // Ejemplo: HGO-PTTI2

// ---------------------------------------------------
// Zona configuracion Dispositivo
// ---------------------------------------------------
boolean device_config_file;    // Identificador para archivo de configuración
char device_config_serial[30]; // Numero de serie de cada Archivo de configuración unico
char device_id[30];            // ID del dispositivo
int device_restart;            // Almacena Número de reinicios
char device_old_user[15];      // Usuario para acceso al servidor Web
char device_old_password[15];  // Contraseña del usuario servidor Web
uint8_t ip[4];                 // variable para convertir de string a IP Variable función convertir string a IP
// ---------------------------------------------------
// Zona configuración WIFI modo Cliente
// ---------------------------------------------------
int wifi_mode = WIFI_STA;

boolean wifi_ip_static;      // Uso de IP Estática DHCP
char wifi_ssid[30];          // Nombre de la red WiFi
char wifi_password[30];      // Contraseña de la Red WiFi
char wifi_ipv4[15];          // Dir IPv4 Estático
char wifi_gateway[15];       // Dir IPv4 Gateway
char wifi_subnet[15];        // Dir Ipv4 Subred
char wifi_dns_primary[15];   // Dir IPv4 DNS primario
char wifi_dns_secondary[15]; // Dir IPv4 DNS secundario
// ---------------------------------------------------
// Zona configuración WIFI modo AP
// ---------------------------------------------------
boolean ap_mode;      // Uso de Modo AP
char ap_ssid[31];     // Nombre del SSID AP
char ap_password[63]; // Contraseña del AP
int ap_chanel;        // Canal AP
int ap_visibility;    // Es visible o no el AP (0 -  visible 1 - Oculto)
int ap_connect;       // Número de conexiones en el AP máx 8 conexiones
// ---------------------------------------------------
// Zona configuración MQTT
// ---------------------------------------------------
boolean mqtt_cloud_enable; // Habilitar MQTT Broker
char mqtt_cloud_id[30];    // Cliente ID MQTT Broker
char mqtt_user[30];        // Usuario MQTT broker
char mqtt_password[39];    // Contraseña del MQTT Broker
char mqtt_server[39];      // Servidor del MQTT Broker
int mqtt_port;             // Puerto servidor MQTT Broker
boolean mqtt_retain;       // Habilitar mensajes retenidos
int mqtt_qos;              // Calidad del servicio
boolean mqtt_time_send;    // Habilitar envio de datos
int mqtt_time_interval;    // Tiempo de envio por MQTT en segundos
boolean mqtt_status_send;  // Habilitar envio de estados
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
ESP32Time rtc; // Clase ESP32Time

bool time_ajuste;     // 1- Manual , 0- Automático internet SRV NTP
char time_date[18];   // 2022-09-07T23:47
long time_z_horaria;  // Zona Horaria GMT 0 = 0 -GMT +1 = 3600 - GMT -1 = -3600
char time_server[39]; // Servidor NTP Elemplo: time.mist.gov

int time_hr; // Hora 0 -23
int time_mn; // Minutos 0 - 59
int time_sc; // Segundos 0-59
int time_dy; // Días 1 - 31
int time_mt; // Meses 1- 12
int time_yr; // Año 2023

// NTP Server
WiFiUDP ntpUDP;
NTPClient ntpClient(ntpUDP);

long lastTime = 0;  // Variable para tiempo de envio por WS
long lastTime2 = 0; // variable para tiempo de envio de Alarmas
long lastTime3 = 0; // contador de alarmas
long last2 = 0;     // Tiempo de activacion de la alarmas ya que podria ser falsa
// ---------------------------------------------------
// Zona de Relays
// ---------------------------------------------------
bool RELAY_STATUS;
int RELAY_LOGICA;
uint8_t RELAY_PIN;
String RELAY_NAME;
String RELAY_DESCRIPTION;
// ---------------------------------------------------
// Zona de alarmas
// ---------------------------------------------------
bool ALARM_STATUS1, ALARM_STATUS2, ALARM_STATUS3, ALARM_STATUS4;
bool ALARM_STATUS5, ALARM_STATUS6, ALARM_STATUS7, ALARM_STATUS8;
// guardar la logica, el pin y el nombre en el vue32_settings en lectura renglon 77
bool ALARM_LOGICA1, ALARM_LOGICA2, ALARM_LOGICA3, ALARM_LOGICA4;
bool ALARM_LOGICA5, ALARM_LOGICA6, ALARM_LOGICA7, ALARM_LOGICA8;
uint8_t ALARM_PIN1, ALARM_PIN2, ALARM_PIN3, ALARM_PIN4;
uint8_t ALARM_PIN5, ALARM_PIN6, ALARM_PIN7, ALARM_PIN8;
String ALARM_NAME1, ALARM_NAME2, ALARM_NAME3, ALARM_NAME4;
String ALARM_NAME5, ALARM_NAME6, ALARM_NAME7, ALARM_NAME8;
String ALARM_TIMEON1, ALARM_TIMEON2, ALARM_TIMEON3, ALARM_TIMEON4;
String ALARM_TIMEON5, ALARM_TIMEON6, ALARM_TIMEON7, ALARM_TIMEON8;
String ALARM_TIMEOFF1, ALARM_TIMEOFF2, ALARM_TIMEOFF3, ALARM_TIMEOFF4;
String ALARM_TIMEOFF5, ALARM_TIMEOFF6, ALARM_TIMEOFF7, ALARM_TIMEOFF8;
int ALARM_CONT1, ALARM_CONT2, ALARM_CONT3, ALARM_CONT4; // registra el valor del contador
int ALARM_CONT5, ALARM_CONT6, ALARM_CONT7, ALARM_CONT8;
int cont[8] = {ALARM_CONT1, ALARM_CONT2, ALARM_CONT3, ALARM_CONT4, ALARM_CONT5, ALARM_CONT6, ALARM_CONT7, ALARM_CONT8}; // lleva la contavilizacion en un for
bool prueba = false;                                                                                                    // envia por mqtt que se hace una prueba de alarmas
bool cambiar[8] = {false, false, false, false, false, false, false, false};                                             // ayuda al contador a idicar si va a cambiar de numero
//-----------------------------------------------------------------
// Zona Otras
//-----------------------------------------------------------------
float TempCPU, humedad, tempC; // Temperatura del CPU en °C
// bool normalizar=true;
bool normalizar; // Normalizar alarmas
//------------------------------------------------------------------------
// OLED
// -----------------------------------------------------------------------
#define SCREEN_WIDTH 128 // Ancho   128 o 128
#define SCREEN_HEIGHT 32 // Alto     32 0 64

Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT);
// -----------------------------------------------------------------------
// Activacion de Alarmas de manera local atravez de la interupcion (boton 34)
// -----------------------------------------------------------------------
#define BOTON2 34 // Botón de interrupción de alarma
volatile boolean togle = true;
#define tiempoDeRebote 250                       // sirve para omitir rebotes
volatile unsigned long tiempoDeInterrupcion = 0; // sirve para omitir rebotes en sonido
void IRAM_ATTR activarAlarmas();

// -------------------------------------------------------------------
struct Alarma
{
    uint8_t PIN; // 5,14,16,17,18,25,26,27
    String NAME;
    bool LOGICA;
    int MODE;
};
// -------------------------------------------------------------------
// DEFINICION DEL PIN (alarma1)
// PIN: GPIO15 | LOGICA: 0 | MODE: INPUT
// -------------------------------------------------------------------
Alarma alarma1;
Alarma alarma2;
Alarma alarma3;
Alarma alarma4;
Alarma alarma5;
Alarma alarma6;
Alarma alarma7;
Alarma alarma8;
// -------------------------------------------------------------
// SETUP DEL PIN ALARMAS
// -------------------------------------------------------------
void setupPinAlarma1()
{

    if (!ALARM_LOGICA1)
    {
        alarma1 = {ALARM_PIN1, ALARM_NAME1, ALARM_LOGICA1, INPUT_PULLUP};
        pinMode(alarma1.PIN, alarma1.MODE);
        if (digitalRead(alarma1.PIN))
        {
            ALARM_STATUS1 = true;
        }
        else
        {
            ALARM_STATUS1 = false;
        }
    }
    else
    {
        alarma1 = {ALARM_PIN1, ALARM_NAME1, ALARM_LOGICA1, INPUT_PULLDOWN};
        pinMode(alarma1.PIN, alarma1.MODE);
        if (digitalRead(alarma1.PIN))
        {
            ALARM_STATUS1 = false;
        }
        else
        {
            ALARM_STATUS1 = true;
        }
    }
    // log("[ INFO ] ALARMA 1 CONFIGURADA: "+ ALARM_NAME1);
}

void setupPinAlarma2()
{
    if (!ALARM_LOGICA2)
    {
        alarma2 = {ALARM_PIN2, ALARM_NAME2, ALARM_LOGICA2, INPUT_PULLUP};
        pinMode(alarma2.PIN, alarma2.MODE);
        if (digitalRead(alarma2.PIN))
        {
            ALARM_STATUS2 = true;
        }
        else
        {
            ALARM_STATUS2 = false;
        }
    }
    else
    {
        alarma2 = {ALARM_PIN2, ALARM_NAME2, ALARM_LOGICA2, INPUT_PULLDOWN};
        pinMode(alarma2.PIN, alarma2.MODE);
        if (digitalRead(alarma2.PIN))
        {
            ALARM_STATUS2 = false;
        }
        else
        {
            ALARM_STATUS2 = true;
        }
    }
    // log("[ INFO ] ALARMA 2 CONFIGURADA: "+ ALARM_NAME2);
}

void setupPinAlarma3()
{
    if (!ALARM_LOGICA3)
    {
        alarma3 = {ALARM_PIN3, ALARM_NAME3, ALARM_LOGICA3, INPUT_PULLUP};
        pinMode(alarma3.PIN, alarma3.MODE);
        if (digitalRead(alarma3.PIN))
        {
            ALARM_STATUS3 = true;
        }
        else
        {
            ALARM_STATUS3 = false;
        }
    }
    else
    {
        alarma3 = {ALARM_PIN3, ALARM_NAME3, ALARM_LOGICA3, INPUT_PULLDOWN};
        pinMode(alarma3.PIN, alarma3.MODE);
        if (digitalRead(alarma3.PIN))
        {
            ALARM_STATUS3 = false;
        }
        else
        {
            ALARM_STATUS3 = true;
        }
    }
    // log("[ INFO ] ALARMA 3 CONFIGURADA: "+ ALARM_NAME3);
}

void setupPinAlarma4()
{
    if (!ALARM_LOGICA4)
    {
        alarma4 = {ALARM_PIN4, ALARM_NAME4, ALARM_LOGICA4, INPUT_PULLUP};
        pinMode(alarma4.PIN, alarma4.MODE);
        if (digitalRead(alarma4.PIN))
        {
            ALARM_STATUS4 = true;
        }
        else
        {
            ALARM_STATUS4 = false;
        }
    }
    else
    {
        alarma4 = {ALARM_PIN4, ALARM_NAME4, ALARM_LOGICA4, INPUT_PULLDOWN};
        pinMode(alarma4.PIN, alarma4.MODE);
        if (digitalRead(alarma4.PIN))
        {
            ALARM_STATUS4 = false;
        }
        else
        {
            ALARM_STATUS4 = true;
        }
    }
    // log("[ INFO ] ALARMA 4 CONFIGURADA: "+ ALARM_NAME4);
}

void setupPinAlarma5()
{
    if (!ALARM_LOGICA5)
    {
        alarma5 = {ALARM_PIN5, ALARM_NAME5, ALARM_LOGICA5, INPUT_PULLUP};
        pinMode(alarma5.PIN, alarma5.MODE);
        if (digitalRead(alarma5.PIN))
        {
            ALARM_STATUS5 = true;
        }
        else
        {
            ALARM_STATUS5 = false;
        }
    }
    else
    {
        alarma5 = {ALARM_PIN5, ALARM_NAME5, ALARM_LOGICA5, INPUT_PULLDOWN};
        pinMode(alarma5.PIN, alarma5.MODE);
        if (digitalRead(alarma5.PIN))
        {
            ALARM_STATUS5 = false;
        }
        else
        {
            ALARM_STATUS5 = true;
        }
    }
    // log("[ INFO ] ALARMA 5 CONFIGURADA: "+ ALARM_NAME5);
}

void setupPinAlarma6()
{
    if (!ALARM_LOGICA6)
    {
        alarma6 = {ALARM_PIN6, ALARM_NAME6, ALARM_LOGICA6, INPUT_PULLUP};
        pinMode(alarma6.PIN, alarma6.MODE);
        if (digitalRead(alarma6.PIN))
        {
            ALARM_STATUS6 = true;
        }
        else
        {
            ALARM_STATUS6 = false;
        }
    }
    else
    {
        alarma6 = {ALARM_PIN6, ALARM_NAME6, ALARM_LOGICA6, INPUT_PULLDOWN};
        pinMode(alarma6.PIN, alarma6.MODE);
        if (digitalRead(alarma6.PIN))
        {
            ALARM_STATUS6 = false;
        }
        else
        {
            ALARM_STATUS6 = true;
        }
    }
    // log("[ INFO ] ALARMA 6 CONFIGURADA: "+ ALARM_NAME6);
}

void setupPinAlarma7()
{
    if (!ALARM_LOGICA7)
    {
        alarma7 = {ALARM_PIN7, ALARM_NAME7, ALARM_LOGICA7, INPUT_PULLUP};
        pinMode(alarma7.PIN, alarma7.MODE);
        if (digitalRead(alarma7.PIN))
        {
            ALARM_STATUS7 = true;
        }
        else
        {
            ALARM_STATUS7 = false;
        }
    }
    else
    {
        alarma7 = {ALARM_PIN7, ALARM_NAME7, ALARM_LOGICA7, INPUT_PULLDOWN};
        pinMode(alarma7.PIN, alarma7.MODE);
        if (digitalRead(alarma7.PIN))
        {
            ALARM_STATUS7 = false;
        }
        else
        {
            ALARM_STATUS7 = true;
        }
    }
    // log("[ INFO ] ALARMA 7 CONFIGURADA: "+ ALARM_NAME7);
}

void setupPinAlarma8()
{
    if (!ALARM_LOGICA8)
    {
        alarma8 = {ALARM_PIN8, ALARM_NAME8, ALARM_LOGICA8, INPUT_PULLUP};
        pinMode(alarma8.PIN, alarma8.MODE);
        if (digitalRead(alarma8.PIN))
        {
            ALARM_STATUS8 = true;
        }
        else
        {
            ALARM_STATUS8 = false;
        }
    }
    else
    {
        alarma8 = {ALARM_PIN8, ALARM_NAME8, ALARM_LOGICA8, INPUT_PULLDOWN};
        pinMode(alarma8.PIN, alarma8.MODE);
        if (digitalRead(alarma8.PIN))
        {
            ALARM_STATUS8 = false;
        }
        else
        {
            ALARM_STATUS8 = true;
        }
    }
    // log("[ INFO ] ALARMA 8 CONFIGURADA: "+ ALARM_NAME8);
}
