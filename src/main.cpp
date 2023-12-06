#include <Arduino.h>
#include "LCD_Driver.h"

#define IR_DIST PIN_PA0

#define TRIG_PIN PIN_PD0
#define ECHO_PIN PIN_PD2

/* Параметры характеристики ИК-дальномера, найденные в Лабораторной работе № 3 */
/* ИСПОЛЬЗУЙТЕ СВОИ ЗНАЧЕНИЯ */
const float ir_k = 0.0f; // k
const float ir_b = 0.0f; // b

void setup()
{
    /* Инициализация LCD-дисплея */
    LCD_Init();
    LCD_Clear();
    LCD_GotoXY(0, 0);

    /* Настройка GPIO */
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    digitalWrite(TRIG_PIN, LOW);
    delay(100);
}

float L_IR; // переменная для хранения расстояния с ИК
float L_US; // переменная для хранения расстояния с УЗ

void loop()
{
    /* Вычисление расстояния с ИК-дальномера */
    int Vo_adc = analogRead(IR_DIST);             // Считывание вых. напряжения с датчика с помощью АЦП
    float Vo = (float)Vo_adc / 1023.0f * 5000.0f; // Перевод АЦП в напряжени, мВ
    L_IR = ir_k / (Vo - ir_b) * 10.0f;            // расстояние с ИК-дальномера, мм

    /* Вычисление расстояния с УЗ-дальномера */
    ///////////////////////////////////////////////////////////
    /* СЮДА НЕОБХОДИМО САМОСТОЯТЕЛЬНО НАПИСАТЬ КОД РАБОТЫ С УЗ-ДАЛЬНОМЕРОМ! */
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(5);
    // code...
    // LS_US = ?;
    ///////////////////////////////////////////////////////////

    /* Вывод данных на экран */
    LCD_Clear();
    LCD_GotoXY(0, 0);
    char msg_ir[16] = {'\0'};
    sprintf(msg_ir, "IR:%.1f", L_IR);
    LCD_SendString(msg_ir, strlen(msg_ir));
    LCD_GotoXY(0, 1);
    char msg_us[16] = {'\0'};
    sprintf(msg_us, "US:%.1f", L_US);
    LCD_SendString(msg_us, strlen(msg_us));
    delay(200);
}