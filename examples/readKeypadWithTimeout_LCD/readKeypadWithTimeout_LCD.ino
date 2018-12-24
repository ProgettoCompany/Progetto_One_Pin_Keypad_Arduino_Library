// readKeypadWithTimeout_LCD example sketch, details can be found here:
// https://www.instructables.com/id/Meet-One-Pin-Keypad/

// Include the libraries:
#include <LiquidCrystal.h>
// Uncomment for I2C LCD (Source: https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads/):
// #include <LiquidCrystal_I2C.h>
#include <OnePinKeypad.h>

// Define Analog Pin:
int pin = A0;

// Variable to store button being pressed:
char keyValue;

// Initialize the LCD library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal LCD(rs, en, d4, d5, d6, d7);
// If using an I2C LCD, use I2C Scanner sketch to find address:
// LiquidCrystal_I2C LCD(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Create a keypad object:
OnePinKeypad keypad(pin);

// 5 second time limit to wait for input
int timeout = 5000;

// Insert your calibrated array here:
// ex: int myThresholds[16] = {calibrated values would be here}

// The setup routine runs once when you press reset:
void setup() {
  // Set up the LCD's number of columns and rows:
  LCD.begin(16, 2);

  // If calibrated values are being used, run keypad.useCalibratedThresholds(your array name) below:
}

// The loop routine runs over and over again forever:
void loop() {
  // Run the readKeypadWithTimeout function to determine which button is pressed within the timeout, in milliseconds
  // Store that value in the variable keyValue
  // If no timeout is desired, pass the NO_TIMEOUT constant as a parameter to readKeypadWithTimeout
  keyValue = keypad.readKeypadWithTimeout(NO_TIMEOUT);

  // Print the key being pressed to the LCD
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("You pressed: ");
  LCD.setCursor(12, 0);
  LCD.print(keyValue);
  delay(10);
}
