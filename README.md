## PingPlong

This is a small (10x20cm 4x8") portable battey-operated synth with a two octave touch keyboard and four voice polyphonic digital sound. 

![Photo of the soldered board](https://raw.github.com/SmallRoomLabs/PlingPlong/master/Doc/PCB-r1-small.jpg)

I'm using two microcontrollers on the board - a Microchip PIC18F44K22 for the user interface and a Atmel ATMEGA328 for the sound generation.

The PIC18 is using the internal CMTU module for capacitivelysensing the 24 touch keys. It is also in charge of scanning the 15 tactile buttons, refreshing the 15 status LEDs and the 7-segment displays, and polling the Rotary Encoder.

Whenever a keypad is touched or the rotary encoder is turned a standard Note On/Off or Control Change MIDI message is sent to the ATMEGA328.

Currently the ATMEGA328 is running a straight copy of the [Midi Vampire-I](http://wiki.openmusiclabs.com/wiki/MidiVamp1) firmware. The ATMEGA328 is also connected to a SD-card connector for future use.

The sound-generating part is contained in a 5x5cm "selfcontained" area to the right on the pcb having pads and via holes for power, midi and SD-card signals. This makes it easy to replace just the synth with something elsethan the MidiVamp. Design a new 5x5 cm pcb and solder it to the pads on the main board.
