# Nanomia Matrix

A 10x10 configurable signal router Eurorack module.

Initial features include:
- Open source hardware and software
- Fully buffered inputs AND outputs
- Works with audio, CV and gate signals
- Route any input to up to 10 outputs
- Two fully routable 3-input utility mixers
- Two or more modules can be chained together for larger configurations
- Routing controllable from the Et Seq step sequencer module

# Build Journal

_Feel free to ask questions by opening an issue!_

## 2023-07-02

The control and power board is now fully designed and has been sent off to be manufactured.

![image](https://github.com/dslik/nanomia/assets/5757591/9d4ca0c1-2587-4951-981b-dc842dc7bd8e)

The power section regulates 5V and 3.3V outputs from the 12V input. There is a PTC fuse to prevent excessive power draw from the LEDs from damaging the power regulators (the PTC is rated at 200 mA, and the 5V regulator is rated to 800 mA, so that's plenty of headroom). Since I only run the LEDs at a maximum of 0.08% of rated power, that works out to 102 mA.

The processor section is a general RP2040-based layout that I use across many of my designs, with GPIO lines connected to the J3 through J6.

The board should arrive here for testing in a couple of weeks.

## 2023-06-12

Assembled and tested the new front panel that uses a PCB diffusor for the LEDs instead of 8x8 LED matrix modules. It looks gorgeous. This exceeded my expectations.

![image](https://github.com/dslik/nanomia/assets/5757591/f7011890-7d94-4a81-ab99-1a1572fc205b)

Here are the PCBs so far:

![image](https://github.com/dslik/nanomia/assets/5757591/d103720c-4a3f-4920-beec-061c41706c71)

From left to right:
- Front panel
- LED spacer
- LED board
- Analog board

Not shown:
- Control/Power board (design not yet finished)

I was pleasantly surprised not to be hit with an extra manufacturing charge for the LED spacer, with it's 256 holes.

For reference, here's what the earlier prototype version of this module looked like:

![image](https://github.com/dslik/nanomia/assets/5757591/3147cd45-0683-480f-b5d0-41286db879d8)
