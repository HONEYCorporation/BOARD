#include <Arduino.h>

String boardName = "HONEY-E32IO0808";
uint8_t PIN_RUN = 2;
uint8_t PIN_BTN = 0;
uint8_t X[] = {26, 25, 33, 32, 35, 34, 39, 36};
uint8_t Y[] = {23, 19, 18, 5, 4, 13, 14, 27};

void _setup()
{
    pinMode(PIN_BTN,INPUT_PULLUP);
    pinMode(PIN_RUN, OUTPUT);
    for (int i = 0; i < 8; i++)
    {
        pinMode(X[i], INPUT);
    }
    for (int i = 0; i < 8; i++)
    {
        pinMode(Y[i], OUTPUT);
        digitalWrite(Y[i], LOW);
    }
}
