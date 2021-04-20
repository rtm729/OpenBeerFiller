/**
 * Open Beer Filler
 * Copyright (c) 2020 Gerhard Potgieter [https://gerhardpotgieter.com]
 *
 * Based on an idea by Christopher Harrison-Hawkes [https://harrisonsbrewery.com]
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
#pragma once;

/**
 * General Config Options
 */
#define CO2_PURGE_PERIOD 2000 // How long in milliseconds to purge with CO2 before filling with beer
#define MOVE_BEER_BELT_PERIOD 5000 // How long in milliseconds to run the beer belt solenoid for, ie how long should the beer belt move.
#define FILLER_TUBE_MOVEMENT_DELAY 2000 // How long in milliseconds to wait after raising/lowering filler tube before starting the next action like opening the filling lines.
#define CO2_PURGE_RETRACTION_DELAY 1000 // How long in milliseconds to wait before starting CO2 purge after starting to retract filler tubes.
#define CO2_PURGE_RETRACTION_PERIOD 500 // How long in milliseconds to purge with CO2 after filling with beer, this happes mid lifting the filler tubes
#define FILL_SENSORS_TIMER_FREQUENCY 100000 // 100ms This value needs to be defined in microseconds.
#define FILL_SENSORS_TRIGGER 400 // Int between 0 and 1023 used to trigger the fill sensor: operating voltage(5v or 3.3v) / 1024
#define VARIABLE_FILL_SENSOR_TRIGGER false // Use a potentiometer to adjust trigger value

/**
 * Feature flags
 */
//#define CONINUOUS_FILLING // Uncomment this to have the filling process repeat for new batch after the current batch has completed it filling.
