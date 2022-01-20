//==============================================================================
// LedTest sample program for Led class
// (c) 2021-2022 by Dirk Ohme
//==============================================================================

//---| definitions |------------------------------------------------------------
#undef TEST
//#define TEST

//---| includes |---------------------------------------------------------------
#if defined(ESP8266)
#  include <pgmspace.h>
#else
#  include <avr/pgmspace.h>
#endif
#include <Led.h>

//------------------------------------------------------------------------------
// setup routine
//------------------------------------------------------------------------------
void setup()
{
  // start serial communication
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println("LedTest");

  // initialize LED class
  LEDs.setLED(0, LED_BUILTIN, true);
}

//------------------------------------------------------------------------------
// main loop
//------------------------------------------------------------------------------
void loop()
{
  Serial.println("*** on ***");
  LEDs.switchOn(0, Led::On);
  delay(5000);
  Serial.println("*** blink ***");
  LEDs.switchOn(0, Led::Blink);
  delay(5000);
  Serial.println("*** blink invers ***");
  LEDs.switchOn(0, Led::BlinkInv);
  delay(5000);
  Serial.println("*** flash 1x ***");
  LEDs.switchOn(0, Led::Flash1x);
  delay(5000);
  Serial.println("*** flash 1x invers ***");
  LEDs.switchOn(0, Led::Flash1xInv);
  delay(5000);
  Serial.println("*** flash 2x ***");
  LEDs.switchOn(0, Led::Flash2x);
  delay(5000);
  Serial.println("*** flash 2x invers ***");
  LEDs.switchOn(0, Led::Flash2xInv);
  delay(5000);
  Serial.println("*** flash 3x ***");
  LEDs.switchOn(0, Led::Flash3x);
  delay(5000);
  Serial.println("*** flash 3x invers ***");
  LEDs.switchOn(0, Led::Flash3xInv);
  delay(5000);
  Serial.println("*** flash 4x ***");
  LEDs.switchOn(0, Led::Flash4x);
  delay(5000);
  Serial.println("*** flash 4x invers ***");
  LEDs.switchOn(0, Led::Flash4xInv);
  delay(5000);
  Serial.println("*** flash ***");
  LEDs.switchOn(0, Led::Flash);
  delay(5000);
  Serial.println("*** flash invers ***");
  LEDs.switchOn(0, Led::FlashInv);
  delay(5000);
  Serial.println("*** off ***");
  LEDs.switchOff(0);
  delay(5000);
}

//===| eof - end of file |======================================================
