# Nanomia Phasor

A signal visualization module that displays the phase angle between two different waveforms.

Initial features include:
- Open source hardware and software
- Two inputs, each with dual buffered outputs
- LCD display showing phase angle
- Buttons and encoder input devices

# Build Journal

_Feel free to ask questions by opening an issue!_

## 2023-06-13

Assembled the latest revision of the boards, and ran through the test suite, with everything passing. This means that the hardware is almost final!

![image](https://github.com/dslik/nanomia/assets/5757591/e8f5eae3-adba-4927-a7e2-0924ad0a48ff)

Just a few nore minor outstanding checks and changes:
- Checking if the fit for the 3.5mm jacks is too tight
- Reducing the intensity of the power LEDs
- Thermal profiling and power draw measurement

Here are the PCBs so far:

![image](https://github.com/dslik/nanomia/assets/5757591/5ccb0158-e959-4eea-b99a-f00b4ab528fb)

From left to right:
- Front panel
- LED spacer
- LED board (full panel of five boards)
- Controller board

Not shown:
- Rotary encoder board

The software is coming along more slowly. The LED control routines are complete, and I can now draw to the LCD. Switch debouncing is working, but still needs to be generalized to handle all three switches, and I need to figure out a better interrupt handling approach to minimize any perceivable latency. And the rotary encoder needs some additional work. Since there is no absolute position indication, I unfortunately can't have the LED ring track the position of th eencoder, but it's still useful as an indicator of min/max value selection.

