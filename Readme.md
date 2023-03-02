# MULTITAP2USB
An Arduino sketch that creates a SNES MULTITAP to 4 HID USB gamepad adapter.  This was developed for use with a Seeeduino Xiao SAMD21 microcontroller, but it should work with any board compatible with [NicoHood's HID-Project Library](https://github.com/NicoHood/HID).

My testing (with a SAMD21) shows a 1000hz polling rate, so there should be no perceptible input lag.

NOTE: By default, only 3 HID gamepads are created due to USB endpoint limitations.  To enable the 4th gamepad, CDC serial must be disabled for your microcontroller ([see this discussion](https://github.com/arduino/ArduinoCore-avr/pull/383/files)).  Instructions on how to do this are in the sketch.


In progress: Only initialize HID gamepads for connecte4d SNES controllers (i.e. 2 HID gamepads will appear if 2 controllers are connected)
