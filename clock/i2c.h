#pragma once

#include <avr/io.h>
#include <stdlib.h>

void startI2C();

void stopI2C();
void sendI2C(uint8_t data);

uint8_t receiveI2C(uint8_t ack);

void sendUSART(short data);
