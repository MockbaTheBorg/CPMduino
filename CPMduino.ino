#include "globals.h"

#include <SPI.h>
#include <SdFat.h>
SdFat SD;
SdFile dir;

#define LED 13
#define DELAY 500
#define SDcs 4  // Pin for the SD chip select signal

#include "abstraction_arduino.h"
#include "cpu.h"
#include "console.h"
#include "ram.h"
#include "disk.h"
#include "cpm.h"

void setup(void)
{
	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);
	pinMode(SDcs, OUTPUT);
	digitalWrite(SDcs, LOW);
	Serial.begin(9600);
	while (!Serial);    // Wait until serial is connected

	_puts("CPMduino v1.3 by Marcelo Dantas\r\n");
	_puts("Arduino pin support by Krzysztof Klis\r\n");
	_puts("------------------------------------\r\n");

	if (SD.begin(SDcs, SPI_HALF_SPEED))
	{
		if (SD.exists(CCPname))
		{
			while (true)
			{
				SD.chdir();
				if (_RamLoad(CCPname, CCPaddr))
				{
					if (_RamVerify(CCPname, CCPaddr))
					{
						if (Status != 2)
							_PatchCPM();
						Z80reset();
						SET_LOW_REGISTER(BC, _RamRead(0x0004));
						PC = CCPaddr;
						Z80run();
						if (Status == 1)
							_RamWrite(0x0004, 0);
					}
					else {
						_puts("Error writing the CCP to RAM. CPU halted.\r\n");
					}
				}
				else {
					_puts("Unable to load the CCP. CPU halted.\r\n");
					break;
				}
			}
		}
		else {
			_puts("Unable to load CP/M CCP. CPU halted.\r\n");
		}
	}
	else {
		_puts("Unable to initialize SD card. CPU halted.\r\n");
	}
}

void loop(void)
{
	digitalWrite(LED, HIGH);
	delay(DELAY);
	digitalWrite(LED, LOW);
	delay(DELAY);
}
