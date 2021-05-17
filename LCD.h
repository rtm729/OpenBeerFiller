
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
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // LiquidCrystal_I2C.h: https://github.com/johnrickman/LiquidCrystal_I2C
#include <Encoder.h> // http://www.pjrc.com/teensy/td_libs_Encoder.html

#include "InputConfig.h"
#include "Settings.h"

void updateLine(int line, char output[]);
void setupLCD();
void rotEncRead();
void showDisplay(char currentStateText[], int filledCans);
