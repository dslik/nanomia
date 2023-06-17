# Nanomia Mixer

An 8 channel dual output CV-controlled mixer Eurorack module.

Initial features include:
- Open source hardware and software
- Fully buffered inputs AND outputs
- Works with audio, CV and gate signals
- Each input channel mix is CV controlled
- Each output channel mix is CV controlled
- Adjust input levels using dual sliders per input channel
- Adjust output levels with a sldier per output channel
- Built-in VU meters for outputs

# Build Journal

_Feel free to ask questions by opening an issue!_

## 2023-06-16

Received the second revision of the front panel, which replaces a USB connector and a button with two CV inputs to control output mix levels.

Here are the PCBs so far:

![image](https://github.com/dslik/nanomia/assets/5757591/d7142a77-2e26-4af6-98c1-fb45fe8e7baa)

From left to right:
- Front panel
- LED spacer
- LED board

Not shown:
- Mixer board (design not yet finished)

These boards look to be final, but I'll hold off on ordering the "V1" boards until I have finished the main mixer board.

The only thing that is holding back getting the mixer board manufactured is that I need to work out a few design issues in my VCA board first, so that I don't replicate the problems ten times on this board.

This is going to be a really nice module, and I already have some ideas for a "v2" module. But first things first...
