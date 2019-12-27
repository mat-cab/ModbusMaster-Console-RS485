#ifndef MODBUS_H_
#define MODBUS_H_

#include "Arduino.h"

void ModbusSetOptions(uint32_t baudRate, uint8_t slaveAddress, uint16_t timeout);

int32_t ModbusRead(uint16_t address);

void ModbusWrite(uint16_t address, int32_t value);

#endif
