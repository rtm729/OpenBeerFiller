
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
