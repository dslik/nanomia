# Nanomia Ultra Sequencer

A step sequencer built around a massive 10 x 100 pixel RGB display.

Features:

* 8 gate and CV inputs for recording and learning
* 8 gate and CV outputs for playback
* 8 gate inputs for external transport control
* LCD and buttons for easy manual control

# Build Journal

_Feel free to ask questions by opening an issue!_

## 2023-08-25

The six PCBs came in:

![image](https://github.com/dslik/nanomia/assets/5757591/66b2edd1-eaae-4c81-9c97-90daf005465a)

From top to bottom:
- Front panel PCB
- LED spacer PCB
- LED PCBs (left and right)
- Stiffener PCB
- Main PCB

Here's what the PCBs that attach to the front panel look like:

![image](https://github.com/dslik/nanomia/assets/5757591/ed6ba2c6-13c9-4b84-b1f9-dced9b38a7a9)

The mechanical clearances all work, except that the LCD needs a bit more room, so I'll have to update the stiffener PCB to make more room.

The two processors on the main board came up without any problems, and basic tests of the LED display and indicators all worked:

![image](https://github.com/dslik/nanomia/assets/5757591/cff9bccf-b7ec-4ae4-bf3c-354cf384d969)

Looking pretty good!

Next steps involve testing the gate I/O, buttons, and inter-processor communication.

## 2023-08-15

This started out a few days ago as a joke:

> "Hey, what if you used that giant display (https://github.com/dslik/rack-display/tree/main/1910A) in a sequencer"

And well, here we are, with all five board designs uploaded, and the first order for PCBs placed.

The main board isn't 100% finished, as the ADC and DAC sections still need to be designed and finalized, respectively, but I wanted to get an order in sooner rather than later, since there are plenty of mechanical tolerances to verify, and I can test all the rest of the control circuitry.

My goal is to be able to capture CV values with a 1 mA accuracy, and output CV values with a 1 mA accuracy, so the design of the analog subsystems and their calibration processes will require a little more thought than usual. I have a design based on the MCP4728 that I am validating for another purpose, but one channel alone will likely let me get to 10 mA at a 20V span. I might be able to get closer by combining two channels and mixing them.

I am tempted to build some unholy multi-channel PWM-based contraption (PWM into a R2R ladder, yay!), but the higher frequencies leads to EMI certification madness, so I should just swallow the higher BOM cost of dedicated ICs. It's not like that's going to hurt much when you need $100 of RGB LEDs for the display alone!

Next steps will involve receiving the boards and checking out what's been designed so far. In the mean time, I can work on the ADC and DAC subsystems, and see how close to 1 mA I can push things.
