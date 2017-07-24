# repo-for-electrical-design
containing sample tasks' C for MCU and Verilog HDL code prepared for the electrical designing competition in the vacation

the tasks are as follow:

(1)PLL(phase lock loop): four independent loops each has its own resolution;(Verilog HDL)

(2)FFT on MCU: display FFT spectrum of input signal on TFT screen;(C for MCU)

(3)DDS DAC: auto gain control loop;(C for MCU)

work folders:

1) agc-gc: (auto gain control - gain control) code for the amplifer task, containing to modes: 1. control the gain of VCA using button; 2. auto VCA gain control by setting different threshold.

2) spi-test: (serial peripheral interface test) code for testing the spi functions, containing code for master divice and slave divice. master send; slave recieve.

3) fre-spec: (frequency - spectrum) code for task on MSP430F6638 to display frequency spectrum of input signal on TFT screen. 
