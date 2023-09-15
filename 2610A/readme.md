# Nanomia Power

A 4HP USB-C Eurorack power adapter

Initial features include:
- USB-passthrough for modules with a rear USB connector
- 250ma on each of the 12V DC outputs
- 500ma on the 5V DC output

This module uses the Recom Power RS6-0512D for 5V to +/-12V conversion.

# Build Journal

_Feel free to ask questions by opening an issue!_

## 2023-09-14

The new PCB revision (1.4) arrived, and is fully assembled. Everything seems to work, as well.

![image](https://github.com/dslik/nanomia/assets/5757591/3346e664-6d81-4506-b09b-72373fa46f95)

While the DC-DC converter I'm uisng here has the ability to support up to 250 mA on the +12V rail and 250 mA on the -12V rail, it is also quite expensive.

I found another DC-DC converter that is much more affordable, but they only support up to 85 mA on each of the +/-12V rails. That's better than the original version, but still isn't nearly enough for many of the more power hungry Eurorack modules. The other downside is that I would need to figure out how to enable 20V USB PD in order to supply them with enough voltage.

I think I'll need to do another power supply design that's designed for multiple modules, and use a seperate 12V and -12V DC-DC converter to give moe more power. But that will be another project.

Next steps on this one will be to create a final board, and get some assembled.

## 2023-08-31

The latest revision of the PCBs have gone off for manufacturing. Once I get them, I can test if the new DC-DC converter is working, and will provide enough current for the more power-hungry modules that I've been designing.

I think I may need to do one more revision, as I'd prefer to add some output capacitors on the +/- 12V rails, convert this over to allow for use of JLCPCB's assembly service, and update the LED board.

I also want to make a current monitor module that shows you the voltage and current on each of the power rails.
