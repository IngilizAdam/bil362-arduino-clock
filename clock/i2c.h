#pragma once

#include <avr/io.h>
#include <stdlib.h>

extern uint8_t i2cBusy;

void startI2C();

void stopI2C();
void sendI2C(uint8_t data);

uint8_t receiveI2C(uint8_t ack);

void sendUSART(short data);
