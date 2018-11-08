// Details can be found here:
// https://www.instructables.com/id/Meet-One-Pin-Keypad/

#include <OnePinKeypad.h>

// Define Analog Pin:
int pin = A0;

// Create a keypad object:
OnePinKeypad keypad(pin);

// 5 second time limit to wait for input
int timeout = 5000;

// Insert your calibrated array here:
// ex: int myThresholds[16] = {calibrated values would be here}

// The setup routine runs once when you press reset:
void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // If calibrated values are being used, run keypad.useCalibratedThresholds(your array name) below:
}

// The loop routine runs over and over again forever:
void loop() {
  // Run the readKeypadWithTimeout function to determine which button is pressed within the timeout, in milliseconds
  // Store that value in the variable keyValue
  // If no timeout is desired, pass the NO_TIMEOUT constant as a parameter to readKeypadWithTimeout
  char keyValue = keypad.readKeypadWithTimeout(timeout);

  // Print the key being pressed to Serial Monitor
  Serial.print("You pressed: ");
  Serial.println(keyValue);
  delay(10);
}
