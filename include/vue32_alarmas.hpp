#include <Arduino.h>
// -------------------------------------------------------------------
// Estructura de un Relay
/* 
@PIN            ->  Se define el pin del ESP32 Ejemplo: GPIO15 - 15
@LOGICA         ->  Se define la logica del PIN / 0 - Normal, 1 - Invertida 
    Normal      - On(1) -> cerrar, Off(0) -> abrir
    Invertida   - On(1) -> abrir,  Off(0) -> cerrar
@MODE           ->  Se define el modo de trabajo del PIN si es de Entrada(INPUT) o Salida(OUTPUT)
@NAME           ->  Se define NOMBRE DEL PIN
@CONTADOR       ->  Define las veces que se ha presentado
@TIMEON         -> La fecha que se presentó
@TIMEOFF        -> La fecha que se Clareo
*/
// -------------------------------------------------------------------
struct Alarma{
    uint8_t PIN; //5,14,16,17,18,25,26,27
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
void setupPinAlarma1(){
    alarma1 = {ALARM_PIN1,ALARM_NAME1,ALARM_LOGICA1,INPUT_PULLUP};
    pinMode(alarma1.PIN,alarma1.MODE);
    //digitalWrite(alarma1.PIN,HIGH);  // talvez hay que quitar
    //logica
    if (!alarma1.LOGICA){
        if (digitalRead(alarma1.PIN)){
            ALARM_STATUS1=true;
        }else
        {
            ALARM_STATUS1=false;
        }
    }else{
        if (digitalRead(alarma1.PIN)){
            ALARM_STATUS1=false;
        }else
        {
            ALARM_STATUS1=true;
        }
    }
    log("[ INFO ] ALARMA 1 CONFIGURADA: "+ ALARM_NAME1); 
}

void setupPinAlarma2(){
    alarma2 = {ALARM_PIN2,ALARM_NAME2,ALARM_LOGICA2,INPUT_PULLUP};
    pinMode(alarma2.PIN,alarma2.MODE);
    //digitalWrite(alarma2.PIN,HIGH);  // talvez hay que quitar
    //logica
    if (!alarma2.LOGICA){
        if (digitalRead(alarma2.PIN)){
            ALARM_STATUS2=true;
        }else
        {
            ALARM_STATUS2=false;
        }
    }else{
        if (digitalRead(alarma2.PIN)){
            ALARM_STATUS2=false;
        }else
        {
            ALARM_STATUS2=true;
        }
    }
    log("[ INFO ] ALARMA 2 CONFIGURADA: "+ ALARM_NAME2); 
}

void setupPinAlarma3(){
    alarma3 = {ALARM_PIN3,ALARM_NAME3,ALARM_LOGICA3,INPUT_PULLUP};
    pinMode(alarma3.PIN,alarma3.MODE);
    //digitalWrite(alarma3.PIN,HIGH);  // talvez hay que quitar
    //logica
    if (!alarma3.LOGICA){
        if (digitalRead(alarma3.PIN)){
            ALARM_STATUS3=true;
        }else
        {
            ALARM_STATUS3=false;
        }
    }else{
        if (digitalRead(alarma3.PIN)){
            ALARM_STATUS3=false;
        }else
        {
            ALARM_STATUS3=true;
        }
    }
    log("[ INFO ] ALARMA 3 CONFIGURADA: "+ ALARM_NAME3); 
}

void setupPinAlarma4(){
    alarma4 = {ALARM_PIN4,ALARM_NAME4,ALARM_LOGICA4,INPUT_PULLUP};
    pinMode(alarma4.PIN,alarma4.MODE);
    //digitalWrite(alarma4.PIN,HIGH);  // talvez hay que quitar
    //logica
    if (!alarma4.LOGICA){
        if (digitalRead(alarma4.PIN)){
            ALARM_STATUS4=true;
        }else
        {
            ALARM_STATUS4=false;
        }
    }else{
        if (digitalRead(alarma4.PIN)){
            ALARM_STATUS4=false;
        }else
        {
            ALARM_STATUS4=true;
        }
    }
    log("[ INFO ] ALARMA 4 CONFIGURADA: "+ ALARM_NAME4); 
}

void setupPinAlarma5(){
    alarma5 = {ALARM_PIN5,ALARM_NAME5,ALARM_LOGICA5,INPUT_PULLUP};
    pinMode(alarma5.PIN,alarma5.MODE);
    //digitalWrite(alarma5.PIN,HIGH);  // talvez hay que quitar
    //logica
    if (!alarma5.LOGICA){
        if (digitalRead(alarma5.PIN)){
            ALARM_STATUS5=true;
        }else
        {
            ALARM_STATUS5=false;
        }
    }else{
        if (digitalRead(alarma5.PIN)){
            ALARM_STATUS5=false;
        }else
        {
            ALARM_STATUS5=true;
        }
    }
    log("[ INFO ] ALARMA 5 CONFIGURADA: "+ ALARM_NAME5); 
}

void setupPinAlarma6(){
    alarma6 = {ALARM_PIN6,ALARM_NAME6,ALARM_LOGICA6,INPUT_PULLUP};
    pinMode(alarma6.PIN,alarma6.MODE);
    //digitalWrite(alarma6.PIN,HIGH);  // talvez hay que quitar
    //logica
    if (!alarma6.LOGICA){
        if (digitalRead(alarma6.PIN)){
            ALARM_STATUS6=true;
        }else
        {
            ALARM_STATUS6=false;
        }
    }else{
        if (digitalRead(alarma6.PIN)){
            ALARM_STATUS6=false;
        }else
        {
            ALARM_STATUS6=true;
        }
    }
    log("[ INFO ] ALARMA 6 CONFIGURADA: "+ ALARM_NAME6); 
}

void setupPinAlarma7(){
    alarma7 = {ALARM_PIN7,ALARM_NAME7,ALARM_LOGICA7,INPUT_PULLUP};
    pinMode(alarma7.PIN,alarma7.MODE);
    //digitalWrite(alarma7.PIN,HIGH);  // talvez hay que quitar
    //logica
    if (!alarma7.LOGICA){
        if (digitalRead(alarma7.PIN)){
            ALARM_STATUS7=true;
        }else
        {
            ALARM_STATUS7=false;
        }
    }else{
        if (digitalRead(alarma7.PIN)){
            ALARM_STATUS7=false;
        }else
        {
            ALARM_STATUS7=true;
        }
    }
    log("[ INFO ] ALARMA 7 CONFIGURADA: "+ ALARM_NAME7); 
}

void setupPinAlarma8(){
    alarma8 = {ALARM_PIN8,ALARM_NAME8,ALARM_LOGICA8,INPUT_PULLUP};
    pinMode(alarma8.PIN,alarma8.MODE);
    //digitalWrite(alarma8.PIN,HIGH);  // talvez hay que quitar
    //logica
    if (!alarma8.LOGICA){
        if (digitalRead(alarma8.PIN)){
            ALARM_STATUS8=true;
        }else
        {
            ALARM_STATUS8=false;
        }
    }else{
        if (digitalRead(alarma8.PIN)){
            ALARM_STATUS8=false;
        }else
        {
            ALARM_STATUS8=true;
        }
    }
    log("[ INFO ] ALARMA 8 CONFIGURADA: "+ ALARM_NAME8); 
}

void setupPinAlarmas(){
    setupPinAlarma1();
    setupPinAlarma2();
    setupPinAlarma3();
    setupPinAlarma4();
    setupPinAlarma5();
    setupPinAlarma6();
    setupPinAlarma7();
    setupPinAlarma8();
}
// -------------------------------------------------------------
// control de las ALARMAS desde MQTT o WS
// -------------------------------------------------------------

String OnOffAlarmas(){
    String response = "";
	DynamicJsonDocument jsonDoc(1000);
    jsonDoc["type"] = "alarmas";
    if (!alarma1.LOGICA){
        if (digitalRead(alarma1.PIN)){
            jsonDoc["ALARM_STATUS1"] = true;
            
        }else
        {
           jsonDoc["ALARM_STATUS1"] = false;
           
        }
    }else{
        if (digitalRead(alarma1.PIN)){
            jsonDoc["ALARM_STATUS1"] = false;
            
        }else
        {
           jsonDoc["ALARM_STATUS1"] = true;
           
        }
    }
    serializeJson(jsonDoc, response);
	return response;
}