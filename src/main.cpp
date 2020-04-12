#include <Arduino.h>

#define __DEBUG__ 1

#if __DEBUG__ == 1
    #define DBG_SPEED 9600
    #define LOG(x) Serial.print((x))
    #define LOGLN(x) LOG(x)
#endif

void setup() 
{
    #ifdef __DEBUG__ == 1

    Serial.begin(9600)

    #endif
}

void loop()
{

}