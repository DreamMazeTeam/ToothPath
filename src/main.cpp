#include <Arduino.h>
#include <Wire.h>


#include "Adafruit_INA219.h"


#define __DEBUG__ 1


#if __DEBUG__ == 1

    #define DBG_SPEED 9600
    #define LOG(x) Serial.print((x))
    #define LOGLN(x) Serial.println((x))
    #define DBG_INIT(x) Serial.begin((x))

#else

    #define LOG(x) 
    #define LOGLN(x) 
    #define DBG_INIT(x) 

#endif


#define LED_PIN     13
#define SENSETIVITY 700


Adafruit_INA219 ina219(0x40);


void setup() 
{
    DBG_INIT(DBG_SPEED);

    ina219.begin();
}


void tick()
{
    if (ina219.getCurrent_mA() >= SENSETIVITY)
    {
        digitalWrite(LED_PIN, HIGH);
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
    }
    
}


void loop()
{   
    tick();
}