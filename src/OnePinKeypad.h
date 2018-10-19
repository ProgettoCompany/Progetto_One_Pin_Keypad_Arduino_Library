/***************************************************
  This is a library for the One Pin Keypad Board:
  (Insert link here)
  It supports 3x4 and 4x4 membrane keypads and outputs
  the key you pressed as a character, based on an
  analog value.
  Written by: John Wolf, Progetto
  Based on code by: Hari Wiguna: https://www.youtube.com/watch?v=G14tREsVqz0
 ****************************************************/
#ifndef OnePinKeypad_h
#define OnePinKeypad_h

#include "Arduino.h"
#include <inttypes.h>

class OnePinKeypad
{
  public:
    #define NO_TIMEOUT 0
    OnePinKeypad(int pin);
	void useCalibratedThresholds(int calibratedThresholds[16]);
    char readKeypadInstantaneous();
    char readKeypadWithTimeout(unsigned long timeout);
	
  private:
    int _pin;
	
    uint16_t analogValue;
	
	int16_t thresholdCheck = 20;
	
    // Keypad char values (button names):
    const char buttonIDs[16] = {'1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0', '#', 'D'};
    char keyValue = '\0';
	
	// analog values that correspond to each button:
    uint16_t thresholds[16] = {
      10,   // 1
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
	
    unsigned long cutOff;
};

#endif