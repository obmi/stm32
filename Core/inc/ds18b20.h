#include <stm32f4xx.h>

uint8_t ds18b20_reset();
uint8_t ds18b20_readbit();
uint8_t ds18b20_readbyte();

void ds18b20_writebit(uint8_t bit);
void ds18b20_writebyte(uint8_t dt);

uint8_t ds18b20_init();

void ds18b20_measure();
void ds18b20_readscratchpad(uint8_t *data);

void ds18b20_pin_output();
void ds18b20_pin_input();
void ds18b20_write_low();
void ds18b20_write_high();

