# BareMetal_Blinker
Baremetal blinker program for Raspberry pi zeroW1.1 or zeroW2 or 4B
Basic baremetal program to blink a LED on different versions of the Raspberry Pi. These projects were tested in July 2025.

This README file is common for all Blinker sub projects:
For the Raspberri Pi 4B: 32bit and 64bit version
4B\BareMetal32bit_Blinker
4B\BareMetal64bit_Blinker
For the Raspberri Pi Zero2W: 32bit and 64bit version
Zero2W\BareMetal32bit_Blinker
Zero2W\BareMetal64bit_Blinker
For the Raspberri Pi ZeroW1.1: 32bit version
ZeroW1.1\BareMetal32bit_Blinker
It describes the way a Windows system needs to be setup in order to be able to compile and run the Bare metal Blinker program. In each sub project a README file is included with specific details for that project.

The makefile used in each sub poject uses the common makefile found in the root directory.
Open powershell and run 'make clean' and 'make'. Then copy all files in from the SD_card directory to the root directory of a SD card.

The confix.txt file configures JTAG pins to be used for debugging.
