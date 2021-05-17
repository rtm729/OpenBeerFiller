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

// Library includes.
// AVR(UNO) Libraries.'
#include <Arduino.h>
#include <EEPROM.h>
#ifdef __AVR__
#include "TimerOne.h"
#include "LiquidCrystal_I2C.h"
#endif

// Project specific includes.
#include "Config.h"
#include "InputConfig.h"
#include "LCD.h"
#include "Settings.h"

/**
 * ***************************************************************************
 * ******************************* VARIABLES *********************************
 * ***************************************************************************
 */
volatile bool fillSensor1Triggered = false;
volatile bool fillSensor2Triggered = false;
bool idleMessageDisplayed = false;
enum ProgramState {UNDEF, IDLE, START, LOWERING_FILLER, PRE_PURGE, FILLING, POST_PURGE, STOP};
char ProgramStateText[][17] = {"UNDEF", "Start To Proceed", "Feed Empty Cans", "Lowering Filler", "Co2 Purge", "Filling", "Retraction Purge",  "Stop"};
ProgramState currentState = UNDEF;
int cansFilled = 0;

/**
 * ***************************************************************************
 * ******************************** FUNCTIONS ********************************
 * ***************************************************************************
 */
void setupPins() {
  // Filler solenoids.
  pinMode(BEER_INLET_SOL_1, OUTPUT);
  pinMode(BEER_INLET_SOL_2, OUTPUT);


  // CO2 solenoid.
  pinMode(CO2_PURGE_SOL, OUTPUT);

  // Fill cylinder solenoid.
  pinMode(FILL_RAIL_SOL, OUTPUT);

  // Fill cylinder solenoid.
  pinMode(FILL_RAM_PROX, INPUT);

  // Can feed cylinder solenoid.
  pinMode(CAN_FEED_SOL, OUTPUT);

  // Can feed cylinder reed switch.
  pinMode(CAN_FEED_REED_SWITCH, INPUT);

  // Fill sensors.
  pinMode(BEER_FILL_SENSOR_1, INPUT);
  pinMode(BEER_FILL_SENSOR_2, INPUT);


  // Start/Stop button.
  pinMode(START_BUTTON, INPUT);
}

/**
 * Setup a non-blocking interrupt timer for checking the fill sensors.
 */
void setupFillSensorsTimer() {
  Timer1.initialize(FILL_SENSORS_TIMER_FREQUENCY);
  Timer1.attachInterrupt(checkFillSensors);
}

/**
 * Check if the fill sensors have been triggered.
 */
void checkFillSensors() {
  if (EEPROM16_Read(EEPROM_FILL_SENSOR_TRIGGER) < analogRead(BEER_FILL_SENSOR_1)) {
    triggerFullFillSensor1();
  }
  if (EEPROM16_Read(EEPROM_FILL_SENSOR_TRIGGER) < analogRead(BEER_FILL_SENSOR_2)) {
    triggerFullFillSensor2();
  }
}

/**
 * Fired when fill sensor 1 is triggered as full.
 */
void triggerFullFillSensor1() {
  if (!fillSensor1Triggered && hasProgramState(FILLING)) {
    closeBeerFillerTube(BEER_INLET_SOL_1);
    fillSensor1Triggered = true;
    Serial.println("Filler tube 1 closed");
  }
}

/**
 * Fired when fill sensor 2 is triggered as full.
 */
void triggerFullFillSensor2() {
  if (!fillSensor2Triggered && hasProgramState(FILLING)) {
    closeBeerFillerTube(BEER_INLET_SOL_2);
    fillSensor2Triggered = true;
    Serial.println("Filler tube 2 closed");
  }
}




/**
 * Return whether all fill sensors have been triggered or not.
 */
bool allFillSensorsTriggered() {
  return fillSensor1Triggered && fillSensor2Triggered;
}

void resetFillSensorTriggers() {
  fillSensor1Triggered = fillSensor2Triggered = false;
}

/**
 * Open a single beer filler solenoid.
 */
void openBeerFillerTube(int fillerTubePin) {
  digitalWrite(fillerTubePin, HIGH);
}

/**
 * Close a single beer filler solenoid.
 */
void closeBeerFillerTube(int fillerTubePin) {
  digitalWrite(fillerTubePin, LOW);
}

/**
 * Open all beer filler solenoids.
 */
void openAllBeerFillerTubes() {
  Serial.println("Opening all beer filler tubes");
  digitalWrite(BEER_INLET_SOL_1, HIGH);
  digitalWrite(BEER_INLET_SOL_2, HIGH);
  



}

/**
 * Close all beer filler solenoids.
 */
void closeAllBeerFillerTubes() {
  Serial.println("Closing all beer filler tubes");
  digitalWrite(BEER_INLET_SOL_1, LOW);
  digitalWrite(BEER_INLET_SOL_2, LOW);

}

/**
 * Raise the fillter tubes out of the bottles.
 */
void raiseFillerTubes() {
  Serial.println("Raising filler tubes");
  digitalWrite(FILL_RAIL_SOL, HIGH);
  delay(EEPROM16_Read(EEPROM_CO2_RETRACTION_CYCLE_DELAY)); // We use CO2_POST_PURGE_DELAY here as we want to start purging with CO2 as the fill rail raises.
}

/**
 * Lower the filler tubes into the bottles.
 */
void lowerFillerTubes() {
  Serial.println("Lowering fill ram");
  digitalWrite(FILL_RAIL_SOL, LOW);
  Serial.println("Waiting for ram prox");
  while (digitalRead(11) == LOW);
  Serial.println("Ram prox triggered");
  delay(EEPROM16_Read(EEPROM_FILL_RAM_CYCLE_DELAY));
}

/**
 * Move the can feed air cylinder, wait a while and then return it to home position.
 */
void canFeedCycle() {
  Serial.println( "Can Feed Cycle" );
  digitalWrite(CAN_FEED_SOL, HIGH);
  Serial.println("Waiting for can feed prox");
  while (digitalRead(9) == LOW);
  delay(EEPROM16_Read(EEPROM_EMPTY_CAN_FEED_CYCLE));
  digitalWrite(CAN_FEED_SOL, LOW);
}

/**
 * Code to run when we are in the IDLE ProgramState
 */
void idleState() {
  if (!idleMessageDisplayed) {
    Serial.println("Press Start Button to proceed");
    idleMessageDisplayed = true;
  }
  readStartButton();
}

/**
 * Code to run when we are in the START ProgramState.
 */
void startState() {
  canFeedCycle();
  //lowerFillerTubes();
  changeProgramState(LOWERING_FILLER);
}

/**
 * Code to run when we are in the Lowering Filler ProgramState.
 */
void loweringFillerState() {
  lowerFillerTubes();
  changeProgramState(PRE_PURGE);
}

/**
 * Code to run when we are in the PRE_PURGE ProgramState.
 */
void prePurgeState() {
  Serial.println("Co2 Purge");
  digitalWrite(CO2_PURGE_SOL, HIGH);
  delay(EEPROM16_Read(EEPROM_CO2_PURGE_TIME));
  digitalWrite(CO2_PURGE_SOL, LOW);
  openAllBeerFillerTubes();
  changeProgramState(FILLING);
}

/**
 * Code to run when we are in the FILLING ProgramState.
 */
void fillingState() {
  // Check if we are done filling.
  if(allFillSensorsTriggered()){
    cansFilled++;
    cansFilled++;
    raiseFillerTubes();
    changeProgramState(POST_PURGE);
  }
}

/**
 * Code to run when we are in the POST_PURGE ProgramState.
 */
void postPurgeState() {
  if(CO2_RETRACTION_CYCLE) {
    Serial.println("Retraction Co2 Purge");
    digitalWrite(CO2_PURGE_SOL, HIGH);
    delay(EEPROM16_Read(EEPROM_CO2_RETRACTION_PURGE_PERIOD));
    digitalWrite(CO2_PURGE_SOL, LOW);
  }

  resetFillSensorTriggers();

  // If done filling, check if we want to do continuous filling or go back to the UNDEF state.
  #if defined(CONTINUOUS_FILLING)
    changeProgramState(START);
  #else
    changeProgramState(IDLE);
  #endif
}

/**
 * Code to run when we are in the STOP ProgramState.
 */
void stopState() {
  // Reset the sensors and change ProgramState to UNDEF.
  resetUnit();
  changeProgramState(IDLE);
}

/**
 * Read the start button.
 */
void readStartButton() {
  if(
    HIGH==digitalRead(START_BUTTON)
    && hasProgramState(IDLE)
  ) {
    Serial.println("Start Button Pressed");
    changeProgramState(START);
  }
}

/**
 * Read the stop button.
 */
void readStopButton() {
  if(
    HIGH==digitalRead(START_BUTTON)
    && !hasProgramState(IDLE)
    && !hasProgramState(START)
  ) {
    Serial.println("Stop Button Pressed");
    changeProgramState(STOP);
  }
}

/**
 * Reset the unit,
 */
void resetUnit() {
  Serial.println("Reseting unit");
  closeAllBeerFillerTubes();
  digitalWrite(CAN_FEED_SOL, LOW);
  raiseFillerTubes();
  digitalWrite(CO2_PURGE_SOL, LOW);
  Serial.println("Done resetting unit");
  changeProgramState(IDLE);
}

/**
 * Change the ProgramState
 */
void changeProgramState(ProgramState state) {
  // Reset the bool to avoid the IDLE state message to repeat continiously.
  if (IDLE == state){
    idleMessageDisplayed = false;
  }
  currentState = state;
  Serial.print("Program state changed: ");
  Serial.println(ProgramStateText[currentState]);


}

/**
 * Check if the currentState matches the passed state.
 */
bool hasProgramState(ProgramState state) {
  if(state == currentState) {
    return true;
  }
  return false;
}

/**
 * Code in this function must always run, avoid delays in here.
 */
void alwaysRun() {
  readStopButton();
  rotEncRead();
  showDisplay(ProgramStateText[currentState], cansFilled);
}


/**
 * ***************************************************************************
 * ***************************** MAIN FUNCTIONS ******************************
 * ***************************************************************************
 */

/**
 * Main setup routine.
 */
void setup() {
  Serial.begin(115200);//Serial.begin(9600);
  firstRunSettings();
  setupLCD();
  setupPins();
  setupFillSensorsTimer();
  resetUnit();
}

/**
 * The main program loop, where all the magic comes togetger.
 */
void loop() {
  switch(currentState) {
    case IDLE:
      idleState();
      break;
    case START:
      startState();
      break;
    case LOWERING_FILLER:
      loweringFillerState();
      break;
    case PRE_PURGE:
      prePurgeState();
      break;
    case FILLING:
      fillingState();
      break;
    case POST_PURGE:
      postPurgeState();
      break;
    case STOP:
      stopState();
      break;
  }
  alwaysRun();
}
