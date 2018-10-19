#include <OnePinKeypad.h>

// Define Analog Pin:
int pin = A0;

// Create a keypad object:
OnePinKeypad keypad(pin);

// Insert your calibrated array here:
// ex: uint16_t myThresholds[16] = {calibrated values would be here}

// The setup routine runs once when you press reset:
void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // If calibrated values are being used, run useCalibratedThresholds(your array name) below:
}

// The loop routine runs over and over again forever:
void loop() {
  // Run the readKeypadInstantaneous function to determine which button is currently being pressed
  // Store that value in the variable keyValue
  char keyValue = keypad.readKeypadInstantaneous();

  // Print the key being pressed to Serial Monitor
  Serial.print("You pressed: ");
  Serial.println(keyValue);
  // Give it some time to rest
  delay(10);
}
