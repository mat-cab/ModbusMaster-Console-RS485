#include "Arduino.h"

#include "Constants.h"
#include "Modbus.h"
#include "Menu.h"

void showMainMenu() {
	USB_SERIAL.println(MENU_SEPARATOR);
	USB_SERIAL.println("1. Change ModbusMaster Settings");
	USB_SERIAL.println("2. Read register from Modbus Slave");
	USB_SERIAL.println("3. Write register to Modbus Slave");
	USB_SERIAL.println(MENU_SEPARATOR);
	
	int i;
	boolean bControl = true;
	do {
		i = ask("Select Option:");

		switch (i) {
			case 1:
				bControl = false;
				showSettingsMenu();
				break;
			case 2:
				bControl = false;
				showReadMenu();
				break;
			case 3:
				bControl = false;
				showWriteMenu();
				break;
			default:
				USB_SERIAL.println("Unknown option");
				bControl = true;
				break;
		}
	} while ( bControl );
}

void showSettingsMenu() {
	uint32_t baudRate;
	uint8_t slaveAddress;
	uint16_t timeout;

	int confirm;

	USB_SERIAL.println(MENU_SEPARATOR);

	baudRate = ask("Set Modbus baud rate:");

	slaveAddress = ask("Set Modbus slave address:");

	timeout = ask("Set Modbus timeout (in ms):");
	
	USB_SERIAL.println(MENU_SEPARATOR);

	USB_SERIAL.println("Modbus baud rate: "+String(baudRate));
	USB_SERIAL.println("Modbus slave address: "+String(slaveAddress));
	USB_SERIAL.println("Modbus timeout: "+String(timeout));

	confirm = ask("Do you confirm these options (1 for Yes):");
	if (confirm == 1) {
		ModbusSetOptions(baudRate, slaveAddress, timeout);
	}
}

void showReadMenu() {
	uint16_t address;
	uint32_t readValue;

	USB_SERIAL.println(MENU_SEPARATOR);
	address = ask("Select slave register address:");

	if (address == 0) {
		USB_SERIAL.println("Aborted read register");
		return;
	}
	
	readValue = ModbusRead(address);
	USB_SERIAL.println("Value read at slave register address "+String(address)+" is "+String(readValue));
}

void showWriteMenu() {
	uint16_t address;
	int32_t value;
	int confirm;

	USB_SERIAL.println(MENU_SEPARATOR);
	address = ask("Select slave register address:");

	if (address == 0) {
		USB_SERIAL.println("Aborted write register");
		return;
	}

	value = ask("Value to write:");

	USB_SERIAL.println(MENU_SEPARATOR);
	USB_SERIAL.println("Modbus slave register address: "+String(address));
	USB_SERIAL.println("Value to write:"+String(value));
	
	confirm = ask("Do you confirm these options (1 for Yes):");
	if (confirm == 1) {
		ModbusWrite(address, value);
	}
}

int ask(String question) {
	int result;

	USB_SERIAL.print(question);

	while (!USB_SERIAL.available());

	result = USB_SERIAL.parseInt();

	USB_SERIAL.println(result);

	return result;
}
