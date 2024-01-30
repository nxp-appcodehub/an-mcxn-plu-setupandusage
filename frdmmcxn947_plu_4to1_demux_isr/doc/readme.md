Overview
========
The PLU 4 to 1 demultiplexer project is a simple demonstration program of the PLU module. In this example,
three PLU_IN pads are set up as a Data and two Selector lines, which will demultiplex an input signal
between four PLU_OUT pads. These lines can be connected to an oscilloscope in order to see the demultiplexing
occur. This example demonstrates the use of the PLUs LUT elements in order to build a simple combinational
logic circuit in the form of a 1 bit 4 to 1 demultiplexer, and how to set it up in order to cause a wakeup event.

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
PLU input pins connection:
- P1_7 (PLU_CLKIN) to external clock signal for PLU latched interruption.
- P1_10(PLU_IN0) to VDD or GND. This pad functions as the Selector0 line. *(Note: if using Rev. B, SJ16 need to be changed to position 2-3)*
- P1_11(PLU_IN1) to VDD or GND. This pad functions as the Selector1 line. *(Note: if using Rev. B, SJ26 need to be changed to position 2-3)*
- P1_14(PLU_IN2) to VDD or GND. This pad functions as the Data signal.

PLU output pins connection:
- P1_8(PLU_OUT0).
- P1_9(PLU_OUT1).
- P1_12(PLU_OUT2).
- P1_13(PLU_OUT3).

Prepare the Demo
================
Note: MCUXpresso IDE project default debug console is semihost
1.  Connect a type-c USB cable between the PC host and the MCU-Link port(J17 on the board).
2.  Download the program to the target board.
3.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Expected Result:

Once programmed, the PLU_OUTx signals' output should follow the behaviour of this 4 to 1 truth table:
 PLU_IN2 | PLU_IN1 | PLU_IN0 | PLU_OUT3 | PLU_OUT2 | PLU_OUT1 | PLU_OUT0 
  (Data) |(Select1)|(Select0)|          |          |          |          
---------|---------|---------|----------|----------|----------|----------
 0       | 0       | 0       | off      | off      | off      |off       
 0       | 0       | 1       | off      | off      | off      |off       
 0       | 1       | 0       | off      | off      | off      |off       
 0       | 1       | 1       | off      | off      | off      |off       
 1       | 0       | 0       | off      | off      | off      |on        
 1       | 0       | 1       | off      | off      | on       |off       
 1       | 1       | 0       | off      | on       | off      |off       
 1       | 1       | 1       | on       | off      | off      |off       

Additionally, after pressing SW3 on the breakout board, the MCU will enter Deep Sleep and turn off the blue LED.
A "ON" signal on PLU_OUT0 or PLU_OUT3 will cause the MCU to go back to Active mode, turning the blue LED back on.
As mentioned on the previous table, the "ON" signal from PLU_OUT0 and PLU_OUT3 that will cause the MCU to wake up
can be achieved by the following combinations of inputs:

PLU_IN2 (Data)      = 1
PLU_IN1 (Select1)   = 0
PLU_IN0 (Select0)   = 0

or

PLU_IN2 (Data)      = 1
PLU_IN1 (Select1)   = 1
PLU_IN0 (Select0)   = 1
