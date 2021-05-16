
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
