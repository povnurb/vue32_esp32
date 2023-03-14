#include <Arduino.h>

// -------------------------------------------------------------------
// Estructura de un Relay
/* 
@PIN            ->  Se define el pin del ESP32 Ejemplo: GPIO2 - 2
@LOGICA         ->  Se define la logica del PIN / 0 - Normal, 1 - Invertida 
    Normal      - On(1) -> cerrar, Off(0) -> abrir
    Invertida   - On(1) -> abrir,  Off(0) -> cerrar
@MODE           ->  Se define el modo de trabajo del PIN si es de Entrada(INPUT) o Salida(OUTPUT)
@NAME           ->  Se define NOMBRE DEL PIN
@DESCRIPTION    ->  Se define LA DESCRIPCIÓN / USO DEL PIN
*/
// -------------------------------------------------------------------
struct Relay {
    uint8_t PIN;
    String NAME;
    String DESCRIPTION;
    int LOGICA;
    int MODE;
};

// -------------------------------------------------------------------
// DEFINICION DEL PIN
// PIN: GPIO2 | LOGICA: 0 | MODE: OUTPUT
// -------------------------------------------------------------------

Relay relay_pin;

// -------------------------------------------------------------------
// SETUP DEL PIN RELAY
// -------------------------------------------------------------------

void setupPinRelay(){

    // RELAY_PIN
    // RELAY_LOGICA
    // RELAY_NAME
    // RELAY_DESCRIPTION

    // Defino la estructura del relay
    relay_pin = {RELAY_PIN, RELAY_NAME, RELAY_DESCRIPTION, RELAY_LOGICA, OUTPUT};

    pinMode(relay_pin.PIN, relay_pin.MODE); 

    if(relay_pin.LOGICA == 0){
        if(RELAY_STATUS){
            setOnSingle(relay_pin.PIN); 
        }else{
            setOffSingle(relay_pin.PIN);
        }
    }else{
        if(RELAY_STATUS){
            setOffSingle(relay_pin.PIN); 
        }else{
            setOnSingle(relay_pin.PIN);
        }
    }

    log("[ INFO ] Salida a Relay inicializada");

}

// -------------------------------------------------------------------
// Control de los Relay desde MQTT & WS
// -------------------------------------------------------------------
void OnOffRelays(String command){

    DynamicJsonDocument JsonDoc(1024);

    deserializeJson(JsonDoc, command);

    if(JsonDoc["protocol"] == "WS"){
        log("[ INFO ] Commando por WS => " + command);
    }else{
        log("[ INFO ] Commando por MQTT => " + command);
    }
    //todo esto meterlo en el ultimo else+++++++++++++++++++++++++++++
    if(JsonDoc["output"]=="ALARM_LOGICA1"){
        log("cambia logica1");
        
    }else if(JsonDoc["output"]=="ALARM_LOGICA2"){
        log("cambia logica2");
        
    }else if(JsonDoc["output"]=="ALARM_LOGICA3"){
        log("cambia logica3");
    }else if(JsonDoc["output"]=="ALARM_LOGICA4"){
        log("cambia logica4");
        
    }else if(JsonDoc["output"]=="ALARM_LOGICA5"){
        log("cambia logica5");
        
    }else if(JsonDoc["output"]=="ALARM_LOGICA6"){
        log("cambia logica6");
        
    }else if(JsonDoc["output"]=="ALARM_LOGICA7"){
        log("cambia logica7");
        
    }else if(JsonDoc["output"]=="ALARM_LOGICA8"){
        log("cambia logica8");
        
    }else{
    if(JsonDoc["value"]){
        if (relay_pin.LOGICA == 0){
            setOnSingle(relay_pin.PIN);                    
            RELAY_STATUS = true;
        }else{           
            setOffSingle(relay_pin.PIN);   
            RELAY_STATUS = false;          
        }
    }else{
        if (relay_pin.LOGICA == 0){
            setOffSingle(relay_pin.PIN);                    
            RELAY_STATUS = false;
        }else{           
            setOnSingle(relay_pin.PIN);   
            RELAY_STATUS = true;          
        }
    }
    settingsSave();  
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // guardar status en memoria spiffs
    
}
