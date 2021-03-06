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
#ifndef TELEMETRY_UAVTALK_UAVTALK_H_
#define TELEMETRY_UAVTALK_UAVTALK_H_

#ifdef TELEMETRY_MAIN_MODULE_ID
#	error Conflicting modules
#endif
#define TELEMETRY_MAIN_MODULE_ID 'U'

#include "lib/common.h"

UT_NAMESPACE_OPEN

const char __name [] PROGMEM = "UAVTalk";

// load settings
void init ();

// parse messages and update the telemetry
bool update ();

// write default settings to EEPROM
void reset ();

UT_NAMESPACE_CLOSE

#endif /* TELEMETRY_UAVTALK_UAVTALK_H_ */
