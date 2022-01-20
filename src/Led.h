/*
 The MIT License (MIT)

 Copyright (c) 2021-2022 Dirk Ohme

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

#pragma once
#include <Ticker.h>

class Led {
public:
	// max. number of LEDs
	static const int MaxLed	= 8;
	
	// mode of operation
	enum Mode {
		Invalid	= -1,
		Off	=  0,
		On,
		Blink,
		BlinkInv,
		Flash,
		FlashInv,
		Flash1x,
		Flash1xInv,
		Flash2x,
		Flash2xInv,
		Flash3x,
		Flash3xInv,
		Flash4x,
		Flash4xInv,
	};

protected:
	bool		m_aboState[MaxLed];
	bool		m_aboInvers[MaxLed];
	Mode		m_aeMode[MaxLed];
	int		m_aiGPIO[MaxLed];
	bool		m_boFirst;
	int		m_iCounter10;
	Ticker		m_coTimer;

	// check validness
	inline const bool isValid(const int iLed) {
		return (iLed >= 0) && (iLed < MaxLed);
	}
	
	// timer routines
	static void TimerFuncStatic();
	void TimerFuncLed(const int iLed);
	void TimerFunc();

public:
	// constructor
	Led();

	// get mode of operation
	// @param iLed number of LED (0 .. MaxLed-1)
	// @return operation mode
	const Mode getMode(const int iLed = 0);

	// set LED
	// @param iLed number of LED (0 .. MaxLed-1)
	// @param iGPIO GPIO port
	// @param boInvers direct or invers mode
	void setLED(const int  iLed,
	            const int  iGPIO,
		    const bool boInvers = false);
	
	// switch LED off
	// @param iLed number of LED (0 .. MaxLed-1)
	void switchOff(const int iLed = 0);
	
	// switch LED on
	// @param iLed number of LED (0 .. MaxLed-1)
	// @param eMode operation mode
	void switchOn(const int  iLed  = 0,
	              const Mode eMode = On);
};

extern Led LEDs;


//===| eof - end of file |====================================================
