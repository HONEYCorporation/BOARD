#ifndef __HONEYShift3232_H__
#define __HONEYShift3232_H__

#include <Arduino.h>

String boardName = "HONEY-E32IO3232";
#define PIN_RUN 2;
#define PIN_BTN 0;

uint8_t PIN_X[32] = {0};
uint8_t PIN_Y[32] = {0};

#define PIN_OUTDATA 4
#define PIN_OUTCLOCK 26
#define PIN_OUTLATCH 27

#define PIN_INDATA 35
#define PIN_INPLOAD 25
#define PIN_INCLOCK 33
#define PIN_INENABLE 32

void _update()
{
    digitalWrite(PIN_INENABLE, HIGH);
    digitalWrite(PIN_INPLOAD, LOW);
    delayMicroseconds(5);
    digitalWrite(PIN_INPLOAD, HIGH);
    digitalWrite(PIN_INENABLE, LOW);
    byte readInputA = shiftIn(PIN_INDATA, PIN_INCLOCK, MSBFIRST);
    byte readInputB = shiftIn(PIN_INDATA, PIN_INCLOCK, MSBFIRST);
    byte readInputC = shiftIn(PIN_INDATA, PIN_INCLOCK, MSBFIRST);
    byte readInputD = shiftIn(PIN_INDATA, PIN_INCLOCK, MSBFIRST);
    for (int i = 0; i < 8; i++)
    {
        PIN_X[i + 24] = !bitRead(readInputD, i);
        PIN_X[i + 16] = !bitRead(readInputC, i);
        PIN_X[i + 8] = !bitRead(readInputB, i);
        PIN_X[i] = !bitRead(readInputA, i);
    }
    digitalWrite(PIN_INENABLE, HIGH);

    digitalWrite(PIN_OUTLATCH, LOW);
    for (int i = 31; i >= 0; i--)
    {
        digitalWrite(PIN_OUTDATA, PIN_Y[i]);
        digitalWrite(PIN_OUTCLOCK, HIGH);
        digitalWrite(PIN_OUTCLOCK, LOW);
    }
    digitalWrite(PIN_OUTLATCH, HIGH);
}
void _setup()
{
    pinMode(PIN_BTN, INPUT_PULLUP);
    pinMode(PIN_RUN, OUTPUT);
  
    pinMode(PIN_OUTDATA, OUTPUT);  // set output
    pinMode(PIN_OUTLATCH, OUTPUT); // set output
    pinMode(PIN_OUTCLOCK, OUTPUT); // set output

    pinMode(PIN_INDATA, INPUT);    // set input
    pinMode(PIN_INPLOAD, OUTPUT);  // set output
    pinMode(PIN_INCLOCK, OUTPUT);  // set output
    pinMode(PIN_INENABLE, OUTPUT); // set output
    
    xTaskCreate([](void*) {
      while ( true ) {
        _update();
        vTaskDelay(5);
      }
    }, "task_loop", 4096, NULL, 1, NULL);
}
void _digitalWrite(uint8_t _y, bool state)
{
    if (_y < 0 || _y > 32)
        _y = 0;
    PIN_Y[_y] = state;
//     _update();
}
bool _digitalRead(uint8_t _x)
{
//     _update();
    if (_x < 0 || _x > 32)
        _x = 0;
    return PIN_X[_x];
}

#endif
