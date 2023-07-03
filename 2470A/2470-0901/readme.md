## Overview

Sample program for the 2470A Gateway Eurorack module

## Build Instructions

1. Set up the Pi Pico example programs and build system
2. Check out this project
3. Create a "build" directory
4. Inside the build directory, run "cmake ../"
5. Make and install the built "2470A.elf" executable.

From inside the build directory, use the following command to make and load the program via SWD:

``make;openocd -f interface/raspberrypi-swd.cfg -f target/rp2040.cfg -c "program 2470A.elf verify reset exit"``

## Test Instructions

When programmed successfully, the front panel input LEDs will illuminate, and pressing the buttons will turn them on and off. When a button is turned on, gate inputs from the corresponding input will be forwarded the corresponding output.
