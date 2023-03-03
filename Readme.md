# MULTITAP2USB
An Arduino sketch that creates a SNES Multitap to 4 HID USB gamepad adapter.  This was developed for use with a Seeeduino Xiao SAMD21 microcontroller, but it should work with any board compatible with [NicoHood's HID-Project Library](https://github.com/NicoHood/HID).  This was tested with a [Hori Multitap](https://m.media-amazon.com/images/I/61Niix1JEYL._SL1500_.jpg), but it should work with all SNES Multitaps, as the communication protocol is standardized and documented by Nintendo.  This sketch doesn't strictly follow the communication specifications, but seems to work regardless.

My testing (with a SAMD21) shows a 1000hz polling rate, so there should be no perceptible input lag.

NOTE: By default, only 3 HID gamepads are created due to USB endpoint limitations.  To enable the 4th gamepad, CDC serial must be disabled for your microcontroller ([see this discussion](https://github.com/arduino/ArduinoCore-avr/pull/383/files)).  Instructions on how to do this are in the sketch.

~~**Work in progress**: Only initialize HID gamepads for connected SNES controllers (i.e. 2 HID gamepads will appear if 2 controllers are connected)~~ <sup>This doesn't seem possible at the moment</sup>

## How does Multitap communication work?
The communication protocol is, unsurprisingly, similar to that of the standard SNES controller.  Connector pins 5 and 6, usually NC for the controller, are used in the Multitap and an additional data line and multiplexer line, respectively.

### Multitap pinout
![Multitap Pinout](https://user-images.githubusercontent.com/52169065/222494081-25e28874-cc6e-4ed6-a9f6-29461d268383.png)

Every full cycle, the controller inputs are latched as normal.  Mux is first driven high, and controllers 2 and 3 are simultaneously read on data0 and data1, respectively.  Mux is then driven low, and controllers 4 and 5 are simultaneously read on data0 and data1, respectively.  Each individual controller's data stream is read using the [normal SNES controller communication protocol](https://www.fpgalover.com/ip-cores/snes-controller-core).

### Multitap communication diagram
![Multitap protocol](https://user-images.githubusercontent.com/52169065/222495704-12407d4d-3fc5-48ef-8f2d-e29607d0f0c0.png)
