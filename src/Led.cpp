/*
 The MIT License (MIT)

 Copyright (c) 2021-2024 Dirk Ohme

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

//---| definitions |----------------------------------------------------------
#undef TEST
//#define TEST

//---| includes |-------------------------------------------------------------
#if defined(ESP8266)
#  include <pgmspace.h>
#else
#  include <avr/pgmspace.h>
#endif
#include <Arduino.h>
#include "Led.h"

//----------------------------------------------------------------------------
// global variable for access
//----------------------------------------------------------------------------
Led LEDs;

//----------------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------------
Led::Led()
{
#ifdef TEST
	Serial.println("[Led] constructor");
#endif

	for (int i = 0; i < MaxLed; i++)
	{
		setLED(i, -1);
	}
	
	m_boFirst = true;
	m_iCounter10 = -1;
	m_coTimer.attach_ms(100, Led::TimerFuncStatic);
}

//----------------------------------------------------------------------------
// timer function (static)
//----------------------------------------------------------------------------
/*static*/ void Led::TimerFuncStatic()
{
	LEDs.TimerFunc();
}

//----------------------------------------------------------------------------
// timer function per LED
//----------------------------------------------------------------------------
void Led::TimerFuncLed(const int iLed)
{
	bool boChange   = m_boFirst;
	bool boNewState = false;
	bool boOldState;
	
	if (isValid(iLed))
	{
		boOldState = m_aboState[iLed];
		
		switch (m_aeMode[iLed])
		{
		case Off:
			boNewState = false;
			break;
			
		case On:
			boNewState = true;
			break;
			
		case Blink:
			boNewState = (m_iCounter10 < 5);
			break;
			
		case BlinkInv:
			boNewState = (m_iCounter10 >= 5);
			break;
			
		case Flash:
			boNewState = ((m_iCounter10 & 1) == 0);
			break;
			
		case FlashInv:
			boNewState = ((m_iCounter10 & 1) != 0);
			break;
			
		case Flash1x:
			boNewState = (m_iCounter10 < 1);
			break;
			
		case Flash1xInv:
			boNewState = (m_iCounter10 > 0);
			break;
			
		case Flash2x:
			boNewState = (m_iCounter10 == 0) ||
			             (m_iCounter10 == 2);
			break;
			
		case Flash2xInv:
			boNewState = (m_iCounter10 != 0) &&
			             (m_iCounter10 != 2);
			break;
			
		case Flash3x:
			boNewState = (m_iCounter10 == 0) ||
			             (m_iCounter10 == 2) ||
			             (m_iCounter10 == 4);
			break;
			
		case Flash3xInv:
			boNewState = (m_iCounter10 != 0) &&
			             (m_iCounter10 != 2) &&
			             (m_iCounter10 != 4);
			break;
			
		case Flash4x:
			boNewState = (m_iCounter10 == 0) ||
			             (m_iCounter10 == 2) ||
			             (m_iCounter10 == 4) ||
			             (m_iCounter10 == 6);
			break;
			
		case Flash4xInv:
			boNewState = (m_iCounter10 != 0) &&
			             (m_iCounter10 != 2) &&
			             (m_iCounter10 != 4) &&
			             (m_iCounter10 != 6);
			break;
			
		default:
			boNewState = false;
			break;
		}
		
#ifdef TEST
		Serial.printf("%c", (boNewState) ? 'X' : '-');
#endif

		if ((boOldState != boNewState) || boChange)
		{
			m_aboState[iLed] = boNewState;
			
			if (m_aiGPIO[iLed] >= 0)
			{
				boNewState ^= m_aboInvers[iLed];
				digitalWrite(m_aiGPIO[iLed], (boNewState) ? HIGH : LOW);
			}
		}
		else
		{
		}
		
	}
}

//----------------------------------------------------------------------------
// timer function (dynamic)
//----------------------------------------------------------------------------
void Led::TimerFunc()
{
#ifdef TEST
	Serial.printf("[Led] count=%2d: ", m_iCounter10);
#endif
	
	for (int i = 0; i < MaxLed; i++)
	{
		TimerFuncLed(i);
	}
	
#ifdef TEST
	Serial.println();
#endif

	if (++m_iCounter10 >= 10)
	{
		m_iCounter10 = 0;
#ifdef TEST
		Serial.println("[Led] ---");
#endif
	}
	
	m_boFirst = false;
}

//----------------------------------------------------------------------------
// get mode
//----------------------------------------------------------------------------
const Led::Mode Led::getMode(const int iLed /*= 0*/)
{
	Mode eMode = Invalid;
	
	if (isValid(iLed))
	{
		eMode = m_aeMode[iLed];
	}
	
	return eMode;
}

//----------------------------------------------------------------------------
// set LED
//----------------------------------------------------------------------------
void Led::setLED(const int  iLed,
                 const int  iGPIO,
		 const bool boInvers /*= false*/)
{
	if (isValid(iLed))
	{
		m_aboState[iLed]  = false;
		m_aboInvers[iLed] = boInvers;
		m_aeMode[iLed]    = Off;
		m_aiGPIO[iLed]    = iGPIO;
#ifdef TEST
		Serial.printf("[Led] set led #%u -> %u (%c)\n",
		              iLed, iGPIO, boInvers ? '-' : '+');
#endif

		if (iGPIO >= 0)
		{
			pinMode(iGPIO, boInvers? OUTPUT_OPEN_DRAIN : OUTPUT);
		}
	}
}

//----------------------------------------------------------------------------
// switch LED off
//----------------------------------------------------------------------------
void Led::switchOff(const int iLed /*= 0*/)
{
	if (isValid(iLed))
	{
		m_aeMode[iLed] = Off;
	}
}

//----------------------------------------------------------------------------
// switch LED on
//----------------------------------------------------------------------------
void Led::switchOn(const int  iLed  /*= 0*/,
                    const Mode eMode /*= On*/)
{
	if (isValid(iLed))
	{
		m_aeMode[iLed] = eMode;
	}
}


//===| eof - end of file |====================================================
