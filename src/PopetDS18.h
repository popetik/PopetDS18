#ifndef POPETDS18_H
#define POPETDS18_H

#include <Arduino.h>

#define OneWire_Pin PD3 
#define OneWire_DDR DDRD
#define OneWire_PORT PORTD
#define OneWire_Input PIND

uint8_t DS18_reset(void); 
void DS18_WriteBit(uint8_t bit); 
void DS18_WriteByte(uint8_t Byte); 
uint8_t DS18_ReadBit(void); 
uint8_t DS18_ReadByte(void);
void DS18getRaw();
void DS18_SetResolution(uint8_t Resolution);
int16_t DS18getTemp(void);

#endif
