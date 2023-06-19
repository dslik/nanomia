# Nanomia Gateway

A four input/four output gate processor

Initial features include:
- Clock generation
- Clock processing (divide, multiply, etc)
- Gate logic (AND/OR/XOR/etc)
- Gate enable/disable
- MIDI gate control (over USB)

# Build Journal

_Feel free to ask questions by opening an issue!_

## 2023-06-19

Finally figured out the cause of the I2C issue, and I can easily bodge in a fix. In the process of working out the I2C issues, I made a bunch of improvements to the software stack, including adding in UART debugging output and a polling framework for the front panel buttons.

The first example program for this module will be a clock generator:

- Gate in 1 - Start clock
- Gate in 3 - Stop clock
- Gate in 5 - Speed up clock
- Gate in 7 - Slow down clock
- Gate out 2 - Clock
- Gate out 4 - Clock / 2
- Gate out 6 - Clock / 4
- Gate out 8 - Clock / 16

The buttons will perform the same functions as the corresponding gate input.

Once the software is all tested with the bodged PCBs, I will be able to order the final PCBs, and this module (at least the hardware), will be ready to post!

## 2023-06-15

Assembled and tested the latest reivsion of this module. The front panel is working, and all the components fit as expected.

In the previous revision, among a few other issues, the opening for the USB connector was a little too tight (always test with multiple different cables from different vendors!), so I enlarged it, and now things are looking good.

![image](https://github.com/dslik/nanomia/assets/5757591/90e9ad13-e92a-4a55-b583-0203346e3280)

I still have some issues with I2C communication (I suspect it is a software problem, since the previous version worked), and I need to test the input protection / level shifting circuits to make sure they handles over-voltage correctly.

This module will become increasingly important over time as I finish up the inter-module networking over gate singal technique that I'm working on. Then this module will become the main hub to connect all of my modules together, allow them to work together, and allow them to be configured through a web interface / JSON API.
