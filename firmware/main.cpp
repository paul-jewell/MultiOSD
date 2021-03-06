/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "config.h"
#include "settings.h"

#include "lib/timer/timer.h"
#include "lib/uart/uart.h"
#include "lib/spi/spi.h"
#include "lib/max7456/max7456.h"
#include "telemetry/telemetry.h"
#include "lib/console/console.h"
#include "commands.h"
#include "boot.h"
#include "osd/osd.h"

inline void init ()
{
	// let's check EEPROM state
	settings::init ();
	// setup timer
	timer::init ();
	// wait 1 sec
	_delay_ms (1000);
	// setup UART
	CONSOLE_UART::init (UART_BAUD_SELECT (UART_BAUD_RATE));
	// setup SPI...
	spi::init ();
	// ...and MAX7456
	max7456::init ();
	// Show boot screen
	if (boot::show ())
	{
		// magic word has been entered so let's run console
		max7456::clear ();
		max7456::puts_p (max7456::hcenter - 4, max7456::vcenter, PSTR ("\xfc CONFIG"));
		fprintf_P (&CONSOLE_UART::stream, PSTR ("MultiOSD v.%04u\r\n"), VERSION);
		console::run (console::process);
	}
	// boot to OSD
	CONSOLE_UART::send_string_p (PSTR ("BOOT\r\n"));
	// load telemetry settings
	telemetry::init ();
	// load OSD settings
	osd::init ();
}

int main ()
{
	init ();

	// main loop
	osd::main ();

	return 0;
}

