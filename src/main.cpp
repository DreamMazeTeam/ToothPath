#include <Arduino.h>
#include <Wire.h>


#include "Adafruit_INA219.h"


#define __DEBUG__ 1


#if __DEBUG__ == 1

    #define DBG_SPEED                  9600
    #define LOG(x)        Serial.print((x))
    #define LOGLN(x)    Serial.println((x))
    #define DBG_INIT(x)   Serial.begin((x))

#else

    #define LOG(x) 
    #define LOGLN(x) 
    #define DBG_INIT(x) 

#endif

#define R_ENGINE_PIN         3
#define L_ENGINE_PIN         5

#define RED_LED_PIN          6
#define YELLOW_LED_PIN       7
#define GREEN_LED_PIN        8

#define Y_FLASK_PIN         12
#define X_FLASK_PIN         10

#define BTN_UPPER_PIN   PIN_A1
#define BTN_LOWWER_PIN  PIN_A0

#define BATTERY_PIN     PIN_A2

#define SENSETIVITY        700


Adafruit_INA219 ina219(0x40);


void setup() 
{
    DBG_INIT(DBG_SPEED);
    ina219.begin();

    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);

    pinMode(Y_FLASK_PIN-1, OUTPUT);
    pinMode(X_FLASK_PIN-1, OUTPUT);

    digitalWrite(Y_FLASK_PIN-1, HIGH);
    digitalWrite(X_FLASK_PIN-1, HIGH);
}


void loop()
{   
    
}
void salam( ){
    Serial.println("lol");
}