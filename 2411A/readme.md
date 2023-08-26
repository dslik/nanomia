# Nanomia Adjustible CV Output

A simple 2HP CV level output module.

Initial features include:
- Adjustable ranges:
   - 0V - 5V
   - 0V - 12V
   - -12V - 5V
   - -12V - 12V
- Fine and coarse sliders 

# Build Journal

_Feel free to ask questions by opening an issue!_

## 2023-08-26

The PCBs came in, and everything is ready to test:

![image](https://github.com/dslik/nanomia/assets/5757591/2f369cf3-e923-49e1-9c69-2512ec98e53e)

Here's what it looks like fully assembled:

![image](https://github.com/dslik/nanomia/assets/5757591/10e03563-5e07-461c-a9cc-3035f6d61ba2)

And, when I test it, everything works as expected.

The fine slider lets you adjust the CV by 0.5V, and the coarse slider lets you adjust the CV by 5V.

You can easily adjust it to a given voltage with 10mv accuracy.

I am going to double the resistance of R7 to make the fine slider adjust the CV by 0.25V, since will give me better control, with less overlap between the sliders.

Next steps are to order the final PCBs, and do a limited production run. I'll also create a 4HP front panel to allow two modules to be connected together.

## 2023-07-24

Position test for the components that mount to the front panel is looking good. This means I can have a small manufacturing run with ENIG done for these boards.

![image](https://github.com/dslik/nanomia/assets/5757591/468ffc6f-8263-4340-b1de-228c66327851)

## 2023-07-19

Created schematics for this module. PCB designs are ready for manufacturing, and will be sent off in the next batch.

![image](https://github.com/dslik/nanomia/assets/5757591/ba6bf140-deba-4671-b7e3-88d814f3e0d4)
