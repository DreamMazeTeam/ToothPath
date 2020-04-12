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

Adafruit_INA219 ina219(0x40);

void setup() 
{
    DBG_INIT(DBG_SPEED);

    ina219.begin();
}

void loop()
{
    LOG("U = ");
    LOG(ina219.getBusVoltage_V() + ina219.getShuntVoltage_mV() / 1000);
    LOGLN(" V");

    LOG(ina219.getCurrent_mA() / 1000);
    LOGLN(" A");

    LOG(ina219.getPower_mW() / 1000);
    LOGLN(" W");

    delay(200);
}