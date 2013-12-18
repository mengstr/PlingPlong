## PingPlong

This is a small (10x20cm 4x8") portable battery-operated synth with a two octave touch keyboard and four voice polyphonic digital sound. A video of the board in action is available at http://youtu.be/FlVGMttL9SU

![Photo of the soldered board](https://raw.github.com/SmallRoomLabs/PlingPlong/master/Doc/PCB-r1-small.jpg)

Two microcontrollers are used on the board - a Microchip PIC18F44K22 for the user interface and a Atmel ATMEGA328 for the sound generation.

The PIC18 is using the internal CMTU module for capacitively sensing the 24 touch keys. It is also in charge of scanning the 15 tactile buttons, refreshing the 15 status LEDs and the 7-segment displays, and polling the Rotary Encoder.

Whenever a padis touched or the rotary encoder is turned a standard Note On/Off or Control Change MIDI message is sent to the ATMEGA328 for playing.

Currently the MEGA328 is running a straight copy of the [Midi Vampire-I](http://wiki.openmusiclabs.com/wiki/MidiVamp1) firmware. The MEGA328 is also connected to a SD-card connector for future use - I want to do firmware updates via the SD card.

The sound-generating part is contained in a 5x5cm "selfcontained" area to the right on the pcb having pads and via holes for power, midi and SD-card signals. This makes it easy to replace just the synth with something else than the MidiVamp. Just design a new 5x5 cm pcb and solder it to the pads on the main board and it's done.

<img src="https://raw.github.com/SmallRoomLabs/PlingPlong/master/Doc/PlingPlong%20Block%20diagram.png" width="75%" height="75%">



