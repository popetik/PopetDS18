#include "PopetDS18.h"
#include <util/delay.h>

uint8_t DS18_reset(void) {
  uint8_t Bit;
  OneWire_DDR |= (1 << OneWire_Pin);
  OneWire_PORT &= ~(1 << OneWire_Pin);
  _delay_us(500);
  OneWire_DDR &= ~(1 << OneWire_Pin);
  _delay_us(100);
  Bit = !(OneWire_Input & (1 << OneWire_Pin));
  _delay_us(450);
  return Bit;
}

void DS18_WriteBit(uint8_t bit) {
  OneWire_DDR |= (1 << OneWire_Pin);
  OneWire_PORT &= ~(1 << OneWire_Pin);
  if (bit) {
    _delay_us(2);
    OneWire_DDR &= ~(1 << OneWire_Pin);
    _delay_us(58);
  } else {
    _delay_us(60);
    OneWire_DDR &= ~(1 << OneWire_Pin);
    _delay_us(2);
  }
}

void DS18_WriteByte(uint8_t Byte) {
  for (uint8_t i = 0; i < 8; i++) {
    DS18_WriteBit(Byte & 0x01);
    Byte >>= 1;
  }
}

uint8_t DS18_ReadBit(void) {
  uint8_t bit;
  OneWire_DDR |= (1 << OneWire_Pin);
  OneWire_PORT &= ~(1 << OneWire_Pin);
  _delay_us(2);
  OneWire_DDR &= ~(1 << OneWire_Pin);
  _delay_us(10);
  bit = (OneWire_Input & (1 << OneWire_Pin)) ? 1 : 0;
  _delay_us(50);
  return bit;
}

uint8_t DS18_ReadByte(void) {
  uint8_t byte = 0;
  for (uint8_t i = 0; i < 8; i++) {
    byte >>= 1;
    if (DS18_ReadBit()) {
      byte |= 0x80;
    }
  }
  return byte;
}

void DS18getRaw() {
  DS18_reset();
  DS18_WriteByte(0xCC);
  DS18_WriteByte(0x44);
}

int16_t DS18getTemp(void) {
  DS18_reset();
  DS18_WriteByte(0xCC);
  DS18_WriteByte(0xBE);
  uint8_t lsb = DS18_ReadByte();
  uint8_t msb = DS18_ReadByte();
  int16_t raw = (msb << 8) | lsb;
  return raw;
}

void DS18_SetResolution(uint8_t Resolution) {
  if (Resolution == 9) {
    DS18_reset();
    DS18_WriteByte(0xCC);
    DS18_WriteByte(0x4E);
    DS18_WriteByte(0x7F);
    DS18_WriteByte(0x80);
    DS18_WriteByte(0x1F);
  }
  else if (Resolution == 10) {
    DS18_reset();
    DS18_WriteByte(0xCC);
    DS18_WriteByte(0x4E);
    DS18_WriteByte(0x7F);
    DS18_WriteByte(0x80);
    DS18_WriteByte(0x3F);
  }
  else if (Resolution == 11) {
    DS18_reset();
    DS18_WriteByte(0xCC);
    DS18_WriteByte(0x4E);
    DS18_WriteByte(0x7F);
    DS18_WriteByte(0x80);
    DS18_WriteByte(0x5F);
  }
  else if (Resolution == 12) {
    DS18_reset();
    DS18_WriteByte(0xCC);
    DS18_WriteByte(0x4E);
    DS18_WriteByte(0x7F);
    DS18_WriteByte(0x80);
    DS18_WriteByte(0x7F);
  }
}