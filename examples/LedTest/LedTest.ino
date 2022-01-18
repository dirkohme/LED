//==============================================================================
// LedTest sample program for CLed class
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
  Led.setLED(0, LED_BUILTIN, true);
}

//------------------------------------------------------------------------------
// main loop
//------------------------------------------------------------------------------
void loop()
{
  Serial.println("*** on ***");
  Led.switchOn(0, CLed::On);
  delay(5000);
  Serial.println("*** blink ***");
  Led.switchOn(0, CLed::Blink);
  delay(5000);
  Serial.println("*** blink invers ***");
  Led.switchOn(0, CLed::BlinkInv);
  delay(5000);
  Serial.println("*** flash 1x ***");
  Led.switchOn(0, CLed::Flash1x);
  delay(5000);
  Serial.println("*** flash 1x invers ***");
  Led.switchOn(0, CLed::Flash1xInv);
  delay(5000);
  Serial.println("*** flash 2x ***");
  Led.switchOn(0, CLed::Flash2x);
  delay(5000);
  Serial.println("*** flash 2x invers ***");
  Led.switchOn(0, CLed::Flash2xInv);
  delay(5000);
  Serial.println("*** flash 3x ***");
  Led.switchOn(0, CLed::Flash3x);
  delay(5000);
  Serial.println("*** flash 3x invers ***");
  Led.switchOn(0, CLed::Flash3xInv);
  delay(5000);
  Serial.println("*** flash 4x ***");
  Led.switchOn(0, CLed::Flash4x);
  delay(5000);
  Serial.println("*** flash 4x invers ***");
  Led.switchOn(0, CLed::Flash4xInv);
  delay(5000);
  Serial.println("*** flash ***");
  Led.switchOn(0, CLed::Flash);
  delay(5000);
  Serial.println("*** flash invers ***");
  Led.switchOn(0, CLed::FlashInv);
  delay(5000);
  Serial.println("*** off ***");
  Led.switchOff(0);
  delay(5000);
}

//===| eof - end of file |======================================================
