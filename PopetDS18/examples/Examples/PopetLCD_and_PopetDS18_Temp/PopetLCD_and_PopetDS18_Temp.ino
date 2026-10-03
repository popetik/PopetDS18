#include <PopetLCD.h>

#include <PopetDS18.h>

void setup() {
  LCD_init(); // инициализируем дисплей
  DS18_reset(); // инициализируем датчик
  DS18_SetResolution(12); // выставляем разрешения
  LCD_setCursor(0, 0);
  LCD_print("DS18B20         2004");
  LCD_setCursor(0, 1);
  LCD_print("--------------------");
}

void loop() {
  DS18getRaw(); // говорим датчику начать измерения
  _delay_ms(800);
  int16_t raw = DS18getTemp(); // читаем температуру
  uint8_t negative = 0;
  if (raw < 0) {
    negative = 1;
    raw = -raw;
  }
  int16_t whole = raw >> 4;
  uint8_t frac_units = raw & 0x0F;
  uint16_t centideg = whole * 100 + frac_units * 25 / 4;
  LCD_setCursor(0, 4);
  if (negative) LCD_data('-'); // если температура отрицательная(negative = 0), то добавляем минус
  LCD_printInt(centideg); // выводим температуру
  LCD_data(0xDF); // знак градус цельсия
  LCD_data('C');
  _delay_ms(200);
}

// Замер веса - Использовал Arduino ide 2.3.10 на ардуино нано, результат:
// Пустой скетч ардуино весит 444 байт учтите это, PopetLCD.h занял 688 байт, PopetDS18.h заняла 308 байт, итого 1440 флеш занимает данный пример PopetLCD_and_PopetDS18_Temp
// результат получен в моих условиях компиляции и может отличаться от версии компилятора, Arduino core и используемого кода.