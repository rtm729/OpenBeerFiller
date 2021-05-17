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
#include <Arduino.h>
#include "Settings.h"
int settingsVersion = 1;



void EEPROM16_Write(uint8_t a, uint16_t b) {
  Serial.println("Writing to EEPROM");
  EEPROM.write(a, lowByte(b));
  EEPROM.write(a+1, highByte(b));
}


uint16_t EEPROM16_Read(uint8_t a) {
  return word(EEPROM.read(a+1), EEPROM.read(a));
}


void firstRunSettings() {
  // If EEPROM position 0 has not been set to settingsVersion, assume first run
  if (!(EEPROM16_Read(0) == settingsVersion)) { 

    // Write defaults to EEPROM
    EEPROM16_Write(EEPROM_EMPTY_CAN_FEED_CYCLE, CAN_FEED_CYCLE);
    EEPROM16_Write(EEPROM_FILL_SENSOR_TRIGGER, FILL_SENSOR_TRIGGER);
    EEPROM16_Write(EEPROM_CO2_PURGE_TIME, CO2_PURGE);
    EEPROM16_Write(EEPROM_CO2_RETRACTION_PURGE_PERIOD, CO2_RETRACTION_CYCLE);
    EEPROM16_Write(EEPROM_CO2_RETRACTION_CYCLE_DELAY, CO2_RETRACTION_DELAY);
    EEPROM16_Write(EEPROM_FILL_RAM_CYCLE_DELAY, FILL_RAM_DELAY);

    EEPROM16_Write(0, settingsVersion);
  }
}
