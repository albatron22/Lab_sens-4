#include <Arduino.h>
#include "LCD_Driver.h"

#define IR_DIST PIN_PA0

void setup()
{
    /* Инициализация LCD-дисплея */
    LCD_Init();
    LCD_Clear();
    LCD_GotoXY(0, 0);
}

void loop()
{
    /* Считывание вых. напряжения с датчика с помощью АЦП */
    int Vo_adc = analogRead(IR_DIST);
    /* Перевод АЦП в напряжени, мВ */
    float Vo = (float)Vo_adc / 1023.0f * 5000.0f;
    /* Вывод напряжения на экран */
    LCD_Clear();
    LCD_GotoXY(0, 0);
    LCD_SendString("Vo [mV]", strlen("Vo [mV]"));
    LCD_GotoXY(0, 1);
    char msg[16] = {'\0'};
    sprintf(msg, "%.1f", Vo);
    LCD_SendString(msg, strlen(msg));
    delay(200);
}