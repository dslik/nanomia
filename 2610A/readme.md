# Nanomia Power

A 4HP USB-C Eurorack power adapter

Initial features include:
- USB-passthrough for modules with a rear USB connector
- 250ma on each of the 12V DC outputs
- 500ma on the 5V DC output

This module uses the Recom Power RS6-0512D for 5V to +/-12V conversion.

# Build Journal

_Feel free to ask questions by opening an issue!_

## 2023-08-31

The latest revision of the PCBs have gone off for manufacturing. Once I get them, I can test if the new DC-DC converter is working, and will provide enough current for the more power-hungry modules that I've been designing.

I think I may need to do one more revision, as I'd prefer to add some output capacitors on the +/- 12V rails, convert this over to allow for use of JLCPCB's assembly service, and update the LED board.

I also want to make a current monitor module that shows you the voltage and current on each of the power rails.
