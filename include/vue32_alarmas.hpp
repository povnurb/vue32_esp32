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
    log("[ INFO ] ALARMA 1 CONFIGURADA: "+ ALARM_NAME1); 
}

void setupPinAlarma2(){
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
    log("[ INFO ] ALARMA 2 CONFIGURADA: "+ ALARM_NAME2); 
}

void setupPinAlarma3(){
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
    log("[ INFO ] ALARMA 3 CONFIGURADA: "+ ALARM_NAME3); 
}

void setupPinAlarma4(){
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
    log("[ INFO ] ALARMA 4 CONFIGURADA: "+ ALARM_NAME4); 
}

void setupPinAlarma5(){
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
    log("[ INFO ] ALARMA 5 CONFIGURADA: "+ ALARM_NAME5); 
}

void setupPinAlarma6(){  
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
    log("[ INFO ] ALARMA 6 CONFIGURADA: "+ ALARM_NAME6); 
}

void setupPinAlarma7(){
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
    log("[ INFO ] ALARMA 7 CONFIGURADA: "+ ALARM_NAME7); 
}

void setupPinAlarma8(){
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
    log("[ INFO ] ALARMA 8 CONFIGURADA: "+ ALARM_NAME8); 
}
*/
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
	DynamicJsonDocument jsonDoc(2500); //2500
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
    if (!alarma2.LOGICA){
        if (digitalRead(alarma2.PIN)){
            jsonDoc["ALARM_STATUS2"] = true;
            
        }else
        {
           jsonDoc["ALARM_STATUS2"] = false;
           
        }
    }else{
        if (digitalRead(alarma2.PIN)){
            jsonDoc["ALARM_STATUS2"] = false;
            
        }else
        {
           jsonDoc["ALARM_STATUS2"] = true;
           
        }
    }
    if (!alarma3.LOGICA){
        if (digitalRead(alarma3.PIN)){
            jsonDoc["ALARM_STATUS3"] = true;
            
        }else
        {
           jsonDoc["ALARM_STATUS3"] = false;
           
        }
    }else{
        if (digitalRead(alarma3.PIN)){
            jsonDoc["ALARM_STATUS3"] = false;
            
        }else
        {
           jsonDoc["ALARM_STATUS3"] = true;
           
        }
    }
    if (!alarma4.LOGICA){
        if (digitalRead(alarma4.PIN)){
            jsonDoc["ALARM_STATUS4"] = true;
            
        }else
        {
           jsonDoc["ALARM_STATUS4"] = false;
           
        }
    }else{
        if (digitalRead(alarma4.PIN)){
            jsonDoc["ALARM_STATUS4"] = false;
            
        }else
        {
           jsonDoc["ALARM_STATUS4"] = true;
           
        }
    }
    if (!alarma5.LOGICA){
        if (digitalRead(alarma5.PIN)){
            jsonDoc["ALARM_STATUS5"] = true;
            
        }else
        {
           jsonDoc["ALARM_STATUS5"] = false;
           
        }
    }else{
        if (digitalRead(alarma5.PIN)){
            jsonDoc["ALARM_STATUS5"] = false;
            
        }else
        {
           jsonDoc["ALARM_STATUS5"] = true;
           
        }
    }
    if (!alarma6.LOGICA){
        if (digitalRead(alarma6.PIN)){
            jsonDoc["ALARM_STATUS6"] = true;
            
        }else
        {
           jsonDoc["ALARM_STATUS6"] = false;
           
        }
    }else{
        if (digitalRead(alarma6.PIN)){
            jsonDoc["ALARM_STATUS6"] = false;
            
        }else
        {
           jsonDoc["ALARM_STATUS6"] = true;
           
        }
    }
    if (!alarma7.LOGICA){
        if (digitalRead(alarma7.PIN)){
            jsonDoc["ALARM_STATUS7"] = true;
            
        }else
        {
           jsonDoc["ALARM_STATUS7"] = false;
           
        }
    }else{
        if (digitalRead(alarma7.PIN)){
            jsonDoc["ALARM_STATUS7"] = false;
            
        }else
        {
           jsonDoc["ALARM_STATUS7"] = true;
           
        }
    }
    if (!alarma8.LOGICA){
        if (digitalRead(alarma8.PIN)){
            jsonDoc["ALARM_STATUS8"] = true;
            
        }else
        {
           jsonDoc["ALARM_STATUS8"] = false;
           
        }
    }else{
        if (digitalRead(alarma8.PIN)){
            jsonDoc["ALARM_STATUS8"] = false;
            
        }else
        {
           jsonDoc["ALARM_STATUS8"] = true;
           
        }
    }
    
    jsonDoc["ALARM_CONT1"]=ALARM_CONT1;jsonDoc["ALARM_CONT5"]=ALARM_CONT5;
    jsonDoc["ALARM_CONT2"]=ALARM_CONT2;jsonDoc["ALARM_CONT6"]=ALARM_CONT6;
    jsonDoc["ALARM_CONT3"]=ALARM_CONT3;jsonDoc["ALARM_CONT7"]=ALARM_CONT7;
    jsonDoc["ALARM_CONT4"]=ALARM_CONT4;jsonDoc["ALARM_CONT8"]=ALARM_CONT8;
    jsonDoc["ALARM_TIMEON1"]=ALARM_TIMEON1;jsonDoc["ALARM_TIMEON2"]=ALARM_TIMEON2;
    jsonDoc["ALARM_TIMEON3"]=ALARM_TIMEON3;jsonDoc["ALARM_TIMEON4"]=ALARM_TIMEON4;
    jsonDoc["ALARM_TIMEON5"]=ALARM_TIMEON5;jsonDoc["ALARM_TIMEON6"]=ALARM_TIMEON6;
    jsonDoc["ALARM_TIMEON7"]=ALARM_TIMEON7;jsonDoc["ALARM_TIMEON8"]=ALARM_TIMEON8;
    jsonDoc["ALARM_TIMEOFF1"]=ALARM_TIMEOFF1;jsonDoc["ALARM_TIMEOFF2"]=ALARM_TIMEOFF2;
    jsonDoc["ALARM_TIMEOFF3"]=ALARM_TIMEOFF3;jsonDoc["ALARM_TIMEOFF4"]=ALARM_TIMEOFF4;
    jsonDoc["ALARM_TIMEOFF5"]=ALARM_TIMEOFF5;jsonDoc["ALARM_TIMEOFF6"]=ALARM_TIMEOFF6;
    jsonDoc["ALARM_TIMEOFF7"]=ALARM_TIMEOFF7;jsonDoc["ALARM_TIMEOFF8"]=ALARM_TIMEOFF8;
    jsonDoc["t_cpu"] = String(round(TempCPUValue()),0);
    jsonDoc["tC"] = String(round(Temperatura()),0);
    jsonDoc["hum"] = String(round(Humedad()),0); //tempMin() //tempMax()
    jsonDoc["tmin"] = String(round(tempMin()),0);
    jsonDoc["tmax"] = String(round(tempMax()),0);
    serializeJson(jsonDoc, response);
	return response;
}
// ----------------------------------------------------------------------------------
// Activar Alarmas
// ----------------------------------------------------------------------------------
void activarAlarma(){ //para provar despues en casa

int pines[8] = {ALARM_PIN1,ALARM_PIN2,ALARM_PIN3,ALARM_PIN4,ALARM_PIN5,ALARM_PIN6,ALARM_PIN7,ALARM_PIN8};
bool logicas[8] = {ALARM_LOGICA1,ALARM_LOGICA2,ALARM_LOGICA3,ALARM_LOGICA4,ALARM_LOGICA5,ALARM_LOGICA6,ALARM_LOGICA7,ALARM_LOGICA8};
    if(digitalRead(15)&&normalizar){
        //digitalWrite(32,HIGH);
        normalizar=false;
        for (int i=0; i < 8; i++){
            if(!logicas[i]){
                pinMode(pines[i],OUTPUT); //activa las alarmas de manera remota
                digitalWrite(pines[i],LOW);
                
            }else{
                pinMode(pines[i],INPUT_PULLUP);
                digitalWrite(pines[i],HIGH);//tenia 1
                
            }
            
        }
    }else if(!digitalRead(15)&&!normalizar){
        normalizar=true;
        setupPinAlarmas();
        //digitalWrite(32,LOW);
    }
}
//------------------------------------------------------------------------------------------------------------
// Setup pin Alarmas por interrupcion boton en sitio
// ----------------------------------------------------------------------------------------------------------
void setupPinActivarAlarmas(){
    pinMode(BOTON2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BOTON2), activarAlarmas, FALLING);  // Flanco de bajada
}
void IRAM_ATTR activarAlarmas(){
    if(millis() - tiempoDeInterrupcion > tiempoDeRebote){
    Serial.println("Interrupción34");
    if(togle){
        Serial.println("Activando Alarmas");
        digitalWrite(15, HIGH); //cuando se activa el pin15 se activan las alarmas
    }else{
        Serial.println("Desactivando Alarmas");
        digitalWrite(15, LOW);
        }
    tiempoDeInterrupcion = millis();
    togle ^= true;
} 
}