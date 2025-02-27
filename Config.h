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

/**
 * General Config Options
 */
#define CO2_PURGE 2000
#define CAN_FEED_CYCLE 50
#define FILL_RAM_DELAY 50
#define CO2_RETRACTION_DELAY 1000 //Delay to start of retraction purge. Adjust this to sync with fill ram to purge near top of can.
#define CO2_RETRACTION_CYCLE 500 //length of Co2 purge to foam the beer as fill ram lifts.
#define FILL_SENSORS_TIMER_FREQUENCY 100000 // 100ms This value needs to be defined in microseconds.
#define FILL_SENSOR_TRIGGER 400 // Ints between 0 and 1023 used to trigger the fill sensor: operating voltage(5v or 3.3v) / 1024

/**
 * Feature flags
 */
//#define CONTINUOUS_FILLING // Uncomment this to have the filling process repeat for new batch after the current batch has completed it filling.
