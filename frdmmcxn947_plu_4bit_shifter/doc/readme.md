Overview
========
The PLU 4 bit shifter project is a simple demonstration program of the PLU module. In this example,
a GPIO from the FRDM-MCXN947 outputs a 1Hz clock signal that should be fed back to the PLU though
on the PLU_CLKIN pad. The logic state from the PLU_IN0 will then propagate though PLU_OUT0 all the
way to PLU_OUT3 for every positive clock edge on the CLKIN pad, which can be seen though an
oscilloscope. This example demonstrates the use of the PLUs Flip Flops in order to build a sequential
logic circuit in the form of a 4 bit Serial-in parallel-out (SIPO) shift register.

SDK version
===========
- Version: 2.14.0

Toolchain supported
===================
- IAR embedded Workbench  9.40.2
- Keil MDK  5.38.1
- GCC ARM Embedded  12.2
- MCUXpresso  11.9.0

Hardware requirements
=====================
- Type-C USB cable
- FRDM-MCXN947 board
- Personal Computer

Board settings
==============
Inputs:
- P3_4(1Hz CLK) to P1_7(PLU_CLKIN).
- P1_10(PLU_IN0) to VDD or GND. *(Note: if using Rev. B, SJ16 need to be changed to position 2-3)*

Outputs:
- P1_8(PLU_OUT0)
- P1_9(PLU_OUT1)
- P1_12(PLU_OUT2)
- P1_13(PLU_OUT3)

Prepare the Demo
================
Note: MCUXpresso IDE project default debug console is semihost
1.  Connect a type-c USB cable between the PC host and the MCU-Link port(J17 on the board).
2.  Download the program to the target board.
3.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Expected Result:

Once programmed, the red LED will blink every second to show the CLK frequency. When seeing PLU_OUT[3:0]
though an oscilloscope or a logic analyzer, the user should be able to see whatever signal was on PLU_IN0,
shifted along on every positive clock cycle of the PLU_CLKIN signal. If the clock signal is removed or stopped
the outputs will retain their values until the clock is applied once again.