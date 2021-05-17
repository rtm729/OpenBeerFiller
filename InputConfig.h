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
 * Pin definitions
 */
#define START_BUTTON 7
#define BEER_INLET_SOL_1 5
#define BEER_INLET_SOL_2 6
#define BEER_FILL_SENSOR_1 A0
#define BEER_FILL_SENSOR_2 A1
// LCD I2C SDA A4
// LCD I2C SCL A5
#define CO2_PURGE_SOL 4
#define FILL_RAIL_SOL 3
#define FILL_RAM_PROX 9
#define CAN_FEED_SOL 2
#define CAN_FEED_REED_SWITCH 8
#define ROT_ENC_A 10
#define ROT_ENC_B 11
#define ROT_ENC_BUTTON 12
