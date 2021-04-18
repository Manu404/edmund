/* https://github.com/buxtronix/arduino/tree/master/libraries/Rotary
 * Rotary encoder library for Arduino.
 */

#ifndef rotary_h
#define rotary_h

#include "Arduino.h"

 // Enable this to emit codes twice per step.
 //#define HALF_STEP

 // Enable weak pullups
#define ENABLE_PULLUPS

// Values returned by 'process'
// No complete step yet.
#define DIR_NONE 0x0
// Clockwise step.
#define DIR_CW 0x10
// Anti-clockwise step.
#define DIR_CCW 0x20

class Rotary
{
public:
  Rotary(char, char);
  // Process pin(s)
  unsigned char process(int a, int b);
private:
  unsigned char state;
  unsigned char pin1;
  unsigned char pin2;
};

#endif