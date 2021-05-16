
#pragma once
#include "LCD.h"

/* Setup 2040 LCD */
LiquidCrystal_I2C lcd(0x27, 20, 4);
char lines[4][21];

/* Setup Rotary Encoder */
#define ENCODER_OPTIMIZE_INTERRUPTS
Encoder rotEnc(ROT_ENC_A, ROT_ENC_B);
int oldPosition, newPosition;
bool initializing = true;
int buttonState;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

/* Setup Menu Stuff */
int menuScreenPosition, cursorPos = 0;
enum displayPage {HOME,MENU,VALUE};
displayPage currentPage = HOME;
enum menuSelect {
                  HOME_SCREEN, 
                  EMPTY_CAN_FEED_CYCLE,
                  FILL_TRIG, 
                  CO2_PURGE_CYCLE, 
                  CO2_RETRAC_CYCLE,
                  CO2_RETRAC_DELAY,
                  FILL_RAM_CYCLE_DELAY,
                  
};
menuSelect currentSelection = HOME_SCREEN;
char menuListText[][21] = {
                  "Home Screen", 
                  "Can Feed Cycle", 
                  "Fill Trigger", 
                  "Co2 Purge Time", 
                  "Co2 Retrac. Time",
                  "Co2 Retrac. Delay", 
                  "Filler Ram Delay"
};
int menuListLength = ((sizeof(menuListText))/(sizeof(menuListText[0])));
int valueBuffer;
bool fromMenu;


void updateLine(int line, char output[]) {
  sprintf(lines[line], "%-20s", output);
}


void updateLCD() {
  for (int i = 0; i < 4; i++) {
    lcd.setCursor(0,i);
    lcd.print(lines[i]);
  }
}



void setupLCD() {
  lcd.init();
  lcd.backlight();
  lcd.print("Initialising...");
  pinMode(ROT_ENC_BUTTON, INPUT);
  initializing = false;
  updateLCD();
}




void showDisplay(char currentStateText[], int filledCans) {
  char lineText[4][21] = {" ", " ", " ", " "};
  

  switch(currentPage) {
    case HOME: 
      sprintf(lineText[0], "%s%s", "", currentStateText);
      sprintf(lineText[3], "%s%i", "Cans Filled: ", filledCans);
     
      break;

    case MENU:
      cursorPos = currentSelection - menuScreenPosition;
      lineText[cursorPos][0] = 62; // >

      sprintf(lineText[0], "%s%s", lineText[0], menuListText[menuScreenPosition]);
      sprintf(lineText[1], "%s%s", lineText[1], menuListText[menuScreenPosition+1]);
      sprintf(lineText[2], "%s%s", lineText[2], menuListText[menuScreenPosition+2]);
      sprintf(lineText[3], "%s%s", lineText[3], menuListText[menuScreenPosition+3]);
      break;

    case VALUE:
      switch (currentSelection) {
        case EMPTY_CAN_FEED_CYCLE:
          sprintf(lineText[0], "%s", "Can Feed Cycle");
          sprintf(lineText[2], "%s%i", "Time in ms: ", valueBuffer);
          break;
        case FILL_TRIG:
          sprintf(lineText[0], "%s", "Fill Trigger");
          sprintf(lineText[2], "%s%i", "Trigger value: ", valueBuffer);
          break;
        case CO2_PURGE_CYCLE:
          sprintf(lineText[0], "%s", "Co2 Purge");
          sprintf(lineText[2], "%s%i", "Time in ms: ", valueBuffer);
          break;
        case CO2_RETRAC_CYCLE:
          sprintf(lineText[0], "%s", "Co2 Retrac. Time");
          sprintf(lineText[2], "%s%i", "Time in ms: ", valueBuffer);
          break;
        case CO2_RETRAC_DELAY:
          sprintf(lineText[0], "%s", "Co2 Retrac. Delay");
          sprintf(lineText[2], "%s%i", "Time in ms: ", valueBuffer);
          break;
        case FILL_RAM_CYCLE_DELAY:
          sprintf(lineText[0], "%s", "Filler Ram Cycle Delay");
          sprintf(lineText[2], "%s%i", "Time in ms: ", valueBuffer);
          break;
      }
      break;
  }

  updateLine(0, lineText[0]);
  updateLine(1, lineText[1]);
  updateLine(2, lineText[2]);
  updateLine(3, lineText[3]);
  updateLCD();
}


int valueLowHigh(int rotEncncPosition, int lowVal, int highVal) {
  if (rotEncncPosition < (lowVal+1))    { rotEncncPosition = lowVal;  rotEnc.write(lowVal); }
  if (rotEncncPosition > (highVal-1))   { rotEncncPosition = highVal; rotEnc.write(highVal); }
  return rotEncncPosition;
}


void readRotEncRotation() {
  newPosition = rotEnc.read() / 4;
  switch(currentPage) {
    case HOME:
      break;

    case MENU:
      if (newPosition < 1) { newPosition = 0; rotEnc.write(0);}
      if (newPosition > (menuListLength-2)) { newPosition = menuListLength-1; rotEnc.write(newPosition * 4);}

      // Check if we need to scroll the screen
      // Cursor Moved Down
      if (newPosition > currentSelection) {
        if ((newPosition-3) > menuScreenPosition) {
          menuScreenPosition++;
        }
      }
      
      // Cursor Moved Up
      if (newPosition < menuScreenPosition) {
        menuScreenPosition--;
      }

      // Stop the cursor going too far
      if (newPosition > (menuScreenPosition + 3)) {newPosition = menuScreenPosition + 3;}
      currentSelection = newPosition;
      break;

     case VALUE:
      int x;
      if (fromMenu) {
        newPosition = valueBuffer;
        fromMenu = false;
      }
      
       switch(currentSelection) {
        case EMPTY_CAN_FEED_CYCLE:
          x = valueLowHigh(newPosition, 0, 32767);
          break;
        case FILL_TRIG:
          x = valueLowHigh(newPosition, 0, 1023);
          break;
        case CO2_PURGE_CYCLE:
          x = valueLowHigh(newPosition, 0, 32767);
          break;
        case CO2_RETRACTION_CYCLE:
          x = valueLowHigh(newPosition, 0, 32767);
          break;
        case CO2_RETRACTION_DELAY:
          x = valueLowHigh(newPosition, 0, 32767);
          break;
        case FILL_RAM_CYCLE_DELAY:
          x = valueLowHigh(newPosition, 0, 32767);
          break;
      }
      valueBuffer = x;
      break;
  }
}


void readRotEncButton() {
  int reading = digitalRead(ROT_ENC_BUTTON);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle if the button state is LOW
      if (buttonState == LOW) {

        switch(currentPage) {
          case HOME:
            currentPage = MENU;
            currentSelection = HOME_SCREEN;
            rotEnc.write(0);
            break;

          case MENU:
            fromMenu = true;
            valueBuffer = EEPROM16_Read(currentSelection*10);
            rotEnc.write(valueBuffer*4);

            switch(currentSelection) {
              case HOME_SCREEN:
                currentPage = HOME;
                break;
              case EMPTY_CAN_FEED_CYCLE:
                currentPage = VALUE;
                break;
              case FILL_TRIG:
                currentPage = VALUE;
                break;
              case CO2_PURGE_CYCLE:
                currentPage = VALUE;
                break;
              case CO2_RETRACTION_CYCLE:
                currentPage = VALUE;
                break;
              case CO2_RETRACTION_DELAY:
                currentPage = VALUE;
                break;
              case FILL_RAM_CYCLE_DELAY:
                currentPage = VALUE;
                break;
            }
            break;

          case VALUE:
            if (EEPROM16_Read(currentSelection*10) != valueBuffer) {
              // Only write to EEPROM if we have to
              EEPROM16_Write(currentSelection*10, valueBuffer);
            }
            newPosition = currentSelection;
            rotEnc.write(currentSelection*4);
            currentPage = MENU;
            break;
        }
      }
    }
  }

  lastButtonState = reading;
}


void rotEncRead() {
  readRotEncButton();
  readRotEncRotation();
}
