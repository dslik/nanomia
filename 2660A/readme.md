# Nanomia Power Meter

A 8HP Eurorack power bus monitor

Initial features include:
- Current and voltage sensors on the 5V and +/- 12V power rails
- Two LCD displays
- Encoder for UI interaction
- Multiple information visualizations (current value, peak value, chart, meters)

This module is also re-usable for providing an extended UI for other processor-based modules.

# Build Journal

_Feel free to ask questions by opening an issue!_

## 2023-10-02

Created the front panel design. Originally, I was going to use seven-segment displays, but this wouldn't have allowed me to show all the voltage and current levels at the same time, and I really want to support multiple ways to show the data, e.g. peak hold, etc. So an LCD made more sense. I did a few quick mock-ups, and having two LCDs was even better, and only added $5 to the BOM. Since I've been working with another module that supports two LCDs, most of the software is already done.

Handling the -12V rail is going to be complicated. Since there is a common return, that makes measuring that much more complicated (you need to subtract the current flows from the +12V and +5V rails, and the errors compound).

Looking at using an INA226 as taught in https://www.ti.com/lit/ug/tidu361a/tidu361a.pdf

The ISO1541DR is a lot more affordable than I expected, at only $1.15 each, quantity 100. I was originally going to put a separate RP2040 there, and use a uni-directional opto-isolator to communicate the measured values to the main RP2040, since the last time I worked with isolator ICs, there were $8 each. But this will allow me to avoid this complexity.
