#include <Arduino.h>

bool ioBlink = false;
unsigned long milOld;
int rndTemp = 0;

// -------------------------------------------------------------------
// Off un Led/Relay/Actuador
// -------------------------------------------------------------------
void setOffSingle(int _pin){
    digitalWrite(_pin, LOW); // 0
}
// -------------------------------------------------------------------
// On un Led/Relay/Actuador
// -------------------------------------------------------------------
void setOnSingle(int _pin){
    digitalWrite(_pin, HIGH); // 1
}
// -------------------------------------------------------------------
// On/Off un Led/Relay/Actuador segun Estados
// -------------------------------------------------------------------
void setOnOffSingle(int _pin, bool status){
    if(status){
        digitalWrite(_pin, HIGH); 
    }else{
        digitalWrite(_pin, LOW);
    }          
}
// -------------------------------------------------------------------
// Simple blinking function - Pestañeo para Alarmas tiempo variable
// -------------------------------------------------------------------
void blinkSingle(int speed, int _pin){
    if((milOld + speed) < millis()){
        milOld = millis();
        if(ioBlink == false){
            digitalWrite(_pin, HIGH); //lo prende
            ioBlink = true;           // cambia el estado
        }else{
            digitalWrite(_pin, LOW); //lo apaga
            ioBlink = false;         // cambia de estado
        }
    }
}
// -------------------------------------------------------------------
// Parpadeo Asincrónico Tiempo On y Tiempo Off tiempo variable
// -------------------------------------------------------------------
void blinkSingleAsy(int timeHigh, int timeLow, int _pin){
    if(ioBlink == false){
        if((milOld + timeHigh) < millis()){
            milOld = millis();
            digitalWrite(_pin, LOW);
            ioBlink = true;
        }
    }else{
        if((milOld + timeLow) < millis()){
            milOld = millis();
            digitalWrite(_pin, HIGH);
            ioBlink = false;
        }
    }
}
// -------------------------------------------------------------------
// Blinking with randomised delay como para TX/RX de Datos
// -------------------------------------------------------------------
void blinkRandomSingle(int minTime, int maxTime, int _pin){
    if((milOld + rndTemp) < millis()){
        milOld = millis();
        rndTemp = random(minTime, maxTime);
        if(ioBlink == false){
            digitalWrite(_pin, HIGH);
            ioBlink = true;
        }else{
            digitalWrite(_pin, LOW);
            ioBlink = false;
        }
    }
}