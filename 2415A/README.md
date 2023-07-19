aned up # Nanomia Attenuator

A 2HP mix-attenuate-buffer module.

Initial features include:
- Open source hardware and software
- Two mix inputs
- Attenuation slider
- Two buffered outputs
- Works with audio and CV signals

While these modules can be hand-assembled, they are best ordered pre-assembled from your PCB house. BOM and component placement files are provided for the main board (2415-0201).

Full assembly instructions will be uploaded soon.

# Build Journal

_Feel free to ask questions by opening an issue!_

## 2023-07-19

I re-did the routing for the analog board to eliminate the long traces that were likely adding significant capacitance, and also cleaned up the ground plane on the top side. I did have to move some of the resistors over to 0402, but didn't have to go to four layers.

![image](https://github.com/dslik/nanomia/assets/5757591/f3cd6a0e-f5a1-48e8-abe2-2f76bcb4a509)

I'll get this sent off to be manufactured in the next batch, and hopefully this will fix the power draw problem.

## 2023-07-16

Despite the module working as expected, and not being able to see anything out of the ordinary on the oscilloscope, the NE5532 op-amps are oscillating internally. I broke out the spectrum analyzer and the H-field probe, and sure enough, there is a strong signature present above each op-amp IC:

![image](https://github.com/dslik/nanomia/assets/5757591/cf2173f8-3745-4c87-8fa3-7181097b7ed3)

Just look at those sprus!

I made a couple of improvements to the board layout for the 1.1 revision, namely a better ground plane, and moved the input mix resistors and the output protection resistors closer to the op-amps. Long traces can add capacitance, which may be what is causing the oscillations.

I also incorporated the design changes discussed yesterday to move from a unity follower to a gain of 2, which should also help with stability. Unfortunately, since this board is so cramped, I had to use some 0402 resistors to make everything fit, which does complicate things if I have to do any rework.

Here's the updated schematics for revision 1.1:

![image](https://github.com/dslik/nanomia/assets/5757591/b98f2fee-b108-460f-abd3-1bd5523c7bdb)

I'll have to get a new set of boards made, and re-test everything, but hopefully this will fix the problem.

## 2023-07-15

The two NE5532 op-amps are each drawing around 40 ma, and get hot to the touch.

To check for stability, I applied a square wave to the input (blue trace), and measured the output (purple trace). The response looks well damped, and there aren't any oscillations other than what is present on the input.

![ScreenImg-32](https://github.com/dslik/nanomia/assets/5757591/927c24ca-5711-432b-84b8-3b14c362944d)

I can't see any signs of stability problems on any of the output or input pins, so if there are any oscillations, they are internal to the op-amp.

Still working on figuring out where the excessive current draw is coming from.

The reason why the output trace is 50mV slower than the input trace is because the voltage divider formed by R5 and R10. If I increased the resistance of R5 to 10K, and reconfigured U2A and U2B to have a gain of 2, then the output would exactly match the input.

If I have to do a re-spin to fix the excessive current draw, I think I'll also add that change.

## 2023-07-14

I noticed that while everything is working as expected, the op-amps are drawing way more power than I expected.

So I'd hold of on building any of these until I figure out what is going on.

Here's the schematics:

![image](https://github.com/dslik/nanomia/assets/5757591/e0a7ad7b-ed48-4621-9b81-56d1a5852fcb)

## 2023-07-06

Got the assembled boards from the manufacturer:

![image](https://github.com/dslik/nanomia/assets/5757591/7155883a-6fe2-4039-ad6f-9d4907856ddf)

The front panel is on the left, and the pannelized attenuator boards are on the right.

Once fully assembled, with the power and slider spacer boards added (not shown), the module looks like this:

![image](https://github.com/dslik/nanomia/assets/5757591/419eca58-df9d-428c-8ca8-16dee69cbd5d)

And, after installing it into my Eurorack system, it works exactly as expected!

![image](https://github.com/dslik/nanomia/assets/5757591/c41620b5-1962-4b93-b821-59d7ee9ea361)

So this module is pretty much done!

Next steps are to order final boards, and to write up the assembly instructions.
