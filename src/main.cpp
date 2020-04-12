#include <Arduino.h>

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

void setup() 
{
    DBG_INIT(DBG_SPEED);
}

void loop()
{

}