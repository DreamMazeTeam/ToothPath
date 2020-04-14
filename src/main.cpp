#include <Arduino.h>
#include <Wire.h>


#include "Adafruit_INA219.h"


#define __DEBUG__ 0


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

#define LEFT                 0
#define RIGHT                1
#define UP                   1
#define DOWN                 0

#define R_ENGINE_PIN         3
#define L_ENGINE_PIN         5

#define RED_LED_PIN          6
#define YELLOW_LED_PIN       7
#define GREEN_LED_PIN        8
#define SENS_LED_PIN        13

#define Y_FLASK_PIN         12
#define X_FLASK_PIN         10

#define BTN_UPPER_PIN   PIN_A1
#define BTN_LOWWER_PIN  PIN_A0

#define BATTERY_PIN     PIN_A2

#define SENSETIVITY        550
#define ENGINE_TICK_DELAY  100
#define VOLT_TICK_DELAY    100

Adafruit_INA219 ina219(0x40);

enum class Direction{ No, Left, Right, _count };
Direction EngineDirection = Direction::No;

int xFlask   = 0;
int yFlask   = 0;
int btnState = 0;

void setEngineDirection(Direction dir)
{
    LOG("Engines in pos -> ");

    switch (dir)
    {
    case Direction::Left:
        digitalWrite(L_ENGINE_PIN, HIGH);
        digitalWrite(R_ENGINE_PIN, LOW);
        LOGLN("Left");
        break;

    case Direction::Right:
        digitalWrite(L_ENGINE_PIN, LOW);
        digitalWrite(R_ENGINE_PIN, HIGH);
        LOGLN("Right");
        break;

    case Direction::No:
        digitalWrite(L_ENGINE_PIN, LOW);
        digitalWrite(R_ENGINE_PIN, LOW);
        LOGLN("No");
        break;
    }
}

Direction getDirectionFromFlasks()
{
    if (btnState)
    {
        if (xFlask == LEFT && yFlask == DOWN) {
            return Direction::Left;
        }
        else if (xFlask == LEFT && yFlask == UP) {
            return Direction::Right;
        }
        else if (xFlask == RIGHT && yFlask == DOWN) {
            return Direction::Right;
        }
        else if (xFlask == RIGHT && yFlask == UP) {
            return Direction::Left;
        }
    }
    else
    {
        if (xFlask == LEFT && yFlask == DOWN) {
            return Direction::Right;
        }
        else if (xFlask == LEFT && yFlask == UP) {
            return Direction::Left;
        }
        else if (xFlask == RIGHT && yFlask == DOWN) {
            return Direction::Left;
        }
        else if (xFlask == RIGHT && yFlask == UP) {
            return Direction::Right;
        }
    }

    return Direction::No;
}

uint32_t engines_timer = 0;

int xFlaskPrev = xFlask;
int yFlaskPrev = yFlask;

void engines_tick()
{
    int x = digitalRead(X_FLASK_PIN);
    int y = digitalRead(Y_FLASK_PIN);

    float power = ina219.getCurrent_mA();
    if (power >= SENSETIVITY) {
        digitalWrite(SENS_LED_PIN, HIGH);
    }
    else if (power <= -SENSETIVITY) {
        digitalWrite(SENS_LED_PIN, HIGH);
    }
    else {
        digitalWrite(SENS_LED_PIN, LOW);
    }

    if ((millis() - engines_timer) >= ENGINE_TICK_DELAY)
    {
        if (digitalRead(BTN_LOWWER_PIN)){
            btnState = 0;
        }
        else if (digitalRead(BTN_UPPER_PIN)){
            btnState = 1;
        }

        if (xFlaskPrev == x)
            xFlask = x;
        if (yFlaskPrev == y)
            yFlask = y;

        engines_timer = millis();
    }

    xFlaskPrev = x;
    yFlaskPrev = y;
}

uint32_t volt_tick_timer = 0;

void what_the_volt () 
{ 
    if ((millis() - volt_tick_timer) >= VOLT_TICK_DELAY)
    {
        uint16_t vol = analogRead(BATTERY_PIN); 

        LOGLN(vol); 

        if ((vol >= 650) && (vol <= 760))
        {
            digitalWrite(RED_LED_PIN, HIGH);
            LOGLN( "RED" ); 
        }
        else if ((vol >= 760) && (vol <= 860))
        {
            digitalWrite(YELLOW_LED_PIN, HIGH);
            LOGLN( "YELLOW" ); 
        }
        else if(vol>=900)
        {   
            digitalWrite(GREEN_LED_PIN, HIGH);
            LOGLN( "GREEN" ); 
        }
        else
        { 
            LOGLN( " LOL " ); 
        } 

        volt_tick_timer = millis();
    }
}

void setup() 
{
    DBG_INIT(DBG_SPEED);
    ina219.begin();

    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);

    pinMode(R_ENGINE_PIN, OUTPUT);
    pinMode(L_ENGINE_PIN, OUTPUT);

    pinMode(Y_FLASK_PIN-1, OUTPUT);
    pinMode(X_FLASK_PIN-1, OUTPUT);

    digitalWrite(Y_FLASK_PIN-1, HIGH);
    digitalWrite(X_FLASK_PIN-1, HIGH);
}

void loop()
{   
    engines_tick();
    what_the_volt();

    EngineDirection = getDirectionFromFlasks();
    setEngineDirection(EngineDirection); 
}