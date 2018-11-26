// calibrateThresholds example sketch, details can be found here:
// https://www.instructables.com/id/Meet-One-Pin-Keypad/

#include <OnePinKeypad.h>

// Define Analog Pin:
int pin = A0;

// Variable to store button being pressed:
char keyValue;

// Keypad button names:
const char buttonIDs[16] = {'1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0', '#', 'D'};

// default analog values that correspond to each button:
int thresholds[16] = {
  30,   // 1
  110,  // 2
  155,  // 3
  210,  // A
  250,  // 4
  310,  // 5
  340,  // 6
  370,  // B
  400,  // 7
  440,  // 8
  460,  // 9
  480,  // C
  500,  // *
  525,  // 0
  540,  // #
  560   // D
};

int newThresholds[16];

int tolerance = 40;

// Create a keypad object:
OnePinKeypad keypad(pin);

void calibrateButton(char button, int arrayIndex) {
  Serial.print("Press ");
  Serial.print(button);
  Serial.println(":");
  delay(10);
  
  while (true) {
    if (analogRead(A0) > 1000); // no-op
    else {
      int buttonVal = analogRead(A0);
      int calibrationCheck = buttonVal - thresholds[arrayIndex];
      if (abs(calibrationCheck) <= tolerance) {
        Serial.print("Passed button analog value: ");
        Serial.println(buttonVal);
        tolerance--;
        newThresholds[arrayIndex] = buttonVal;
        Serial.println("Release the button");
        return;
      }
    }
    delay(10);
  }
}

// The setup routine runs once when you press reset:
void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  delay(10);

  Serial.println("\nKeypad Calibration for Progetto One Pin Keypad Boards:");
  Serial.println("Please note: for your convenience a tolerance is used ");
  Serial.println("to avoid bad values from pressing the wrong button. ");
  Serial.println("Unfortunately, the analog values get closer and closer");
  Serial.println("together as they increase so if you press 0 instead of #");
  Serial.println("the analog value will still be accepted.");
  Serial.println("\nTL;DR: Press the correct button when prompted!!!\n");

  delay(500);
  
  // less than is used because array indexing starts at 0
  for (int buttonIndex = 0; buttonIndex < 16; buttonIndex++) {
    calibrateButton(buttonIDs[buttonIndex], buttonIndex);
    delay(1000);
  }
  Serial.println("\nInsert the following line of code before void setup():");
  Serial.print("int myThresholds[16] = {");
  for (int thresholdsIndex = 0; thresholdsIndex < 15; thresholdsIndex++) {
    Serial.print(newThresholds[thresholdsIndex]);
    Serial.print(", ");
  }
  Serial.print(newThresholds[15]);
  Serial.println("};");

  Serial.println("\nNext, insert the following line of code inside void setup()");
  Serial.println("of your project to use the new calibrated analog thresholds:");
  Serial.println("keypad.useCalibratedThresholds(myThresholds);");
  
  keypad.useCalibratedThresholds(newThresholds);
  
  Serial.println("\nCalibrated value demo beginning in 5 seconds...");
  Serial.println("Feel free to test out your calibrated values by pressing ");
  Serial.println("any button at random, it should be printed to the Serial "); 
  Serial.println("Monitor. If a button fails, hit the reset button to recalibrate.");
  delay(5000);
  Serial.println("\nBegin.");
}

// The loop routine runs over and over again forever:
void loop() {
  // Run the readKeypadWithTimeout function to determine which button is pressed within the timeout, in milliseconds
  // Store that value in the variable keyValue
  // If no timeout is desired, pass the NO_TIMEOUT constant as a parameter to readKeypadWithTimeout
  keyValue = keypad.readKeypadWithTimeout(NO_TIMEOUT);

  // Print the key being pressed to Serial Monitor
  Serial.print("You pressed: ");
  Serial.println(keyValue);
  delay(10);
}
