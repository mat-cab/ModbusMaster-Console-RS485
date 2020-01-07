#include "Menu.h"
#include "Constants.h"

void setup() {           
	USB_SERIAL.begin(USB_SERIAL_SPEED);

	while (!USB_SERIAL.available());
}

void loop() {
	showMainMenu();
}
