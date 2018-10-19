#include "OnePinKeypad.h"

OnePinKeypad::OnePinKeypad(int pin) {
  _pin = pin;
}

void OnePinKeypad::useCalibratedThresholds(int calibratedThresholds[16]) {
  // replace thresholds with calibratedThresholds
    for (uint8_t i = 0; i < 16; i++) {
      thresholds[i] = calibratedThresholds[i];
    }
}

/* Returns the input from the keypad at the moment this function
   is executed. Note that the function does not wait for input
   from the keypad, and returns null if no key is being pressed
   during the keypad value check.
   @return char representing pressed key, or null if no input is detected.
*/
char OnePinKeypad::readKeypadInstantaneous() {
  // Read the input on analog pin 0
  analogValue = analogRead(_pin);
 
  // If no button is being pressed, return null
  if (analogValue > 1000) {
      // no-op 
	  keyValue = '\0';
  }
  else {  
	  // Compare the input value to each threshold value
	  for (int i = 0; i < 16; i++)
	  {
		// Check value against keypad thresholds
		thresholdCheck = analogValue - thresholds[i];
		if (abs(thresholdCheck) <= 7) {
		  // return the name of the key closest to the input value
		  thresholdCheck = 0;
		  keyValue = buttonIDs[i];
		}
	  }
  }
  return keyValue;
}

/*
   Waits until keypad input is received, or the timeout expires,
   should it be set, in which case a null is returned
   @return a char representing the keypad input or a null, if no
   input is detected before the timeout expires
   @timeout value specified in milliseconds, set to 0 if are to
   wait indefinitely
*/
char OnePinKeypad::readKeypadWithTimeout(unsigned long timeout) {
  char keyValue = '\0';
  
  if (timeout == 0) {
    while (true) {
      keyValue = readKeypadInstantaneous();
      if (keyValue != '\0') {
        // Wait until the button is released
        while (analogRead(_pin) < 1000) {
          delay(100);
        }
        break;
      }
	  delay(10);
    }
  }
  else {
    cutOff = millis() + timeout;
    while (millis() < cutOff) {
      keyValue = readKeypadInstantaneous();
      if (keyValue != '\0') {
        // Wait until the button is released
        while (analogRead(_pin) < 1000) {
          delay(100);
        }
        break;
      }
	  delay(10);
    }
  }
  
  // FOR DEBUG:
  // Serial.print("analogValue: ");
  // Serial.println(analogValue);
  
  return keyValue;
}