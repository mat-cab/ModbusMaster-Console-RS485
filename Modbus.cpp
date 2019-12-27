#include "Arduino.h"

#include "libraries/YAAJ_ModbusMaster/YAAJ_ModbusMaster.h"

#include "Constants.h"

#include "Modbus.h"

YAAJ_ModbusMaster ModbusM;

void ModbusSetOptions(uint32_t baudRate, uint8_t slaveAddress, uint16_t timeout) {
	ModbusM.begin(MODBUS_SERIAL, baudRate, SERIAL_8N1, slaveAddress, MODBUS_PIN_DE, MODBUS_PIN_RE, timeout);
}

int32_t ModbusRead(uint16_t address) {
	uint16_t lowByte, highByte;
	uint8_t returnStatus;

	returnStatus = ModbusM.F4_ReadInputRegisters(address, 2); 

	if ( returnStatus == MODBUS_SUCCESS ) {

		highByte = ModbusM.getRxBuf(0);
		lowByte = ModbusM.getRxBuf(1);

		return (highByte << 16 | lowByte);
	} else {
		USB_SERIAL.println("Error "+String(returnStatus)+" while reading Modbus slave");

		return 0;
	}
}

void ModbusWrite(uint16_t address, int32_t value) {
	uint16_t lowByte, highByte;
	uint8_t returnStatus;

	lowByte = value & 0xFFFF;
	highByte = (value >> 16) & 0xFFFF;

	ModbusM.setTxBuf(0, highByte);
	ModbusM.setTxBuf(1, lowByte);
	
	returnStatus = ModbusM.F16_WriteMultipleHoldingRegisters(address, 2);

	if ( returnStatus != MODBUS_SUCCESS ) {
		USB_SERIAL.println("Error "+String(returnStatus)+" while reading Modbus slave");
	}
}
