# Led-Library

Library for auto Light Emitting Diode (LED) control based on the timer
function of the ESP8266. The purpose is to have LED running "for their
own" without the need to to such things like blinking on your own.

## Led

Led is the name of the class which implements methods for virtual LEDs
that are connected to real ports. There is a standard object called "Led"
to gain access. See the example code for usage.

### Parameters
- num = virtual LED number (0..7)
- gpio = output port selection
- inv = inverted mode
- mode = mode of operation
  - Led::Off = switch off
  - Led::On = switch on
  - Led::Blink = blink with ratio 50% on, 50% off
  - Led::BlinkInv = blink with ratio 50% off, 50% on
  - Led::Flash = flash 1 time each period
  - Led::FlashInv = on with 1 time each period short off
  - Led::Flash1x = flash 1 time each period
  - Led::Flash1xInv = on with 1 time each period short off
  - Led::Flash2x = flash 2 time each period
  - Led::Flash2xInv = on with 2 time each period short off
  - Led::Flash3x = flash 3 time each period
  - Led::Flash3xInv = on with 3 time each period short off
  - Led::Flash4x = flash 4 time each period
  - Led::Flash4xInv = on with 4 time each period short off

### Constants
- LEDs.MaxLed = number of virtual LEDs (8)

### Methods
- LEDs.getMode(num) = returns the current mode of operation for a LED
- LEDs.setLED(num, gpio, inv) = associates a virtual LED to a physical port
- LEDs.switchOff(num) = turn LED off
- LEDs.switchOn(num, mode) = turn LED on with selected mode (if mode is omitted, use "on")

## Releases

- 1.0.0 Initial release.

## How to install

[Installing Additional Arduino Libraries](https://www.arduino.cc/en/Guide/Libraries)
