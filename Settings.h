/**
 * Open Beer Filler
 * Copyright (c) 2020 Gerhard Potgieter [https://gerhardpotgieter.com]
 *
 * Based on an idea by Christopher Harrison-Hawkes [https://harrisonsbrewery.com]
 * 
 * Based on Modifications By David Gray (https://github.com/N3MIS15)
 * 
 * Modified by Ryan Moses (https://github.com/rtm729)
 *
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
 *
 */
#pragma once
#include "EEPROM.h"
#include "Arduino.h"
#include "Config.h"
#include "InputConfig.h"

#define EEPROM_EMPTY_CAN_FEED_CYCLE 10
#define EEPROM_FILL_SENSOR_TRIGGER 20
#define EEPROM_CO2_PURGE_TIME 30
#define EEPROM_CO2_RETRACTION_PURGE_PERIOD 40
#define EEPROM_CO2_RETRACTION_CYCLE_DELAY 50
#define EEPROM_FILL_RAM_CYCLE_DELAY 60

void firstRunSettings();
void EEPROM16_Write(uint8_t a, uint16_t b);
uint16_t EEPROM16_Read(uint8_t a);
