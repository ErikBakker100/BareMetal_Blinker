# Blinker Program with JTAG debug.
## Introduction
It all started with the work of David Welch dwelch@dwelch.com (https://github.com/dwelch67). But I wanted to use the Blinker program for testing the JTAG interface on my Raspberry Pi's: Zero1, Zero2 and 4B.

I have included 2 ways for building. Use either MAKE or CMAKE.
## Prerequitsites
MAKE, https://www.gnu.org/software/make/
CMAKE, https://cmake.org/
ARM toolchain, https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads
a) AArch32 bare-metal target (arm-none-eabi) 
b) AArch64 bare-metal target (aarch64-none-elf) 
Blinker Program using MAKE
This README file is common for all MAKE Blinker sub projects:
For the Raspberri Pi 4B: 32bit and 64bit version
4B\BareMetal32bit_Blinker
4B\BareMetal64bit_Blinker
For the Raspberri Pi Zero2W: 32bit and 64bit version
Zero2W\BareMetal32bit_Blinker
Zero2W\BareMetal64bit_Blinker
For the Raspberri Pi ZeroW1.1: 32bit version
ZeroW1.1\BareMetal32bit_Blinker
It describes the way a Windows system needs to be setup in order to be able to compile and run the Bare metal Blinker program. In each sub project a README file is included with specific details for that project.

The makefile used in each sub project uses the common makefile found in the root directory.
Open powershell and run 'make clean' and 'make' from within each project dir. Then copy all files  from the SD_card directory to the root directory of a SD card.

The confix.txt file in the SD_card directory configures that Raspi for using JTAG pins for debugging.

For the 32 bit version of the Raspberry Pi 4B version, the starting address in src/start.s needs to be at address 0x8000, whereby the 64bit version needs a starting address at 0x80000. The config.txt are different in the way that the 32 bit version has 'arm_64bit=0' included and 'kernel=kernel.img', whereby the 64bit version has 'arm_64bit=1' included and 'kernel=kernel8.img' (if you like you can omit 'kernel=kernel8.img', since this is default).
## JTAG
In the 'openocd' directory you will find the .cfg files for the different FDTI adapters used. In these .cfg files the connections which need to to be made are explained. At least 'TCK', 'TDI', 'TDO', 'TMS' and 'TRST' need to be wired between the FTDI module and the Raspberry Pi. The 'SRST' and 'RTCK' signals are optional (SRST=System Reset, RTCK=Return clock). The 'TRST' resets the JTAG Debug adapter of the Raspberry, whereby the Raspberry itself keeps working. The System Reset, resets the whole Raspberry and by that restarting the CPU and peripherals.
I used 5k6 resistors to pull up or pull down the different signals. 'TCK' needs to be pulled down, the rest pulled up. 

I started not using these pull up/down resistors, but after checking with an oscilloscope and/or Pulseview (https://github.com/sigrokproject/pulseview) I noticed that sometimes the voltage levels did not meet the minimum required levels, therefore I soldered these resistors fixed to the FTDI adapters. The SRST can not be found on the P1 connector of the Raspberry but needs to be connected via a 10k resistor to the RUN connection on the Raspberry Pi board (sometimes requires soldering). The SRST connection is not shown in the figure. The RTCK is shown here, but I was not able to get it to work (but is not needed anyway).
## FTDI Adapters
I have used 3 different types of  adapters 1-channel (FT232H), 2-channel (FT2232H) and 4-channel (FT4232H). If using the FT232H and you want to use the Serial port of a Raspberry at the same time you need to attach a scond adapter. Using the FT2232H makes it possible to connect the JTAG to the first channel and the Serial interface to the second channel. The 4 channel has two ports which can be used as JTAG interface (port o and port 1) whereby the other two (port 2 and 3) can be used as serial interface. The configuration used per type can be found in the 'openocd' directory.
## Drivers
The JTAG interface when used in combination with Openocd requires WinUSB driver. WinUSB driver can be installed using Zadig (https://zadig.akeo.ie/). When reconnecting the adapter (or started my computer again) I needed to reinstall the WinUSB driver again. Also starting OpenOCD  with debug option (openocd -d3) and if the debug output gives “Error: 157 1234 mpsse.c:180 open_matching_device(): libusb_open() failed with LIBUSB_ERROR_NOT_SUPPORTED” you know the driver is wrong. 
For the Serial port used as a COM port the FTDI driver (https://ftdichip.com/drivers/vcp-drivers/) is needed.
## OpenOCD
I have chosen to compile the source code (https://github.com/openocd-org/openocd) to be sure I had all the options I needed available. See openocd/building_openocd_32bit.txt and  openocd/building_openocd_64bit.txt for the 32bit or 64bit version for the way I did it. Since I'm using the Cortex-Debug expansion in Visual Studio Code I had to make some changes to the settings in 'openocd.cfg' (can be found in each project dir). Cortex-Debug uses other ports as standard than OpenOCD does (gdb_port 50000, tcl_port 50001 and telnet_port 50002).
## SD_Card
Each Raspberry needs different files and setup. Use the ones supplied in each SD_card subdirectory of the specific project file. The new .img file will be automatically copied to the SD_card directory after (re)compiling. Copy the files in the SD_card directory to the root of a SD_card and put the card in the raspberry. Power on (or reset) to start the program.
## config.txt
Each configuration requires a slightly different config.txt in the root of the SD_card.
### Raspberry pi 4B, 32 bit version
arm_64bit=0
kernel=kernel.img
gpio=22-27=a4
dtoverlay=disable-bt
[pi4]
arm_boost=1
enable_jtag_gpio=1
### Raspberry pi 4B, 64 bit version
arm_64bit=1
kernel=kernel8.img
gpio=22-27=a4
dtoverlay=disable-bt
[pi4]
arm_boost=1
enable_jtag_gpio=1
### Raspberry pi Zero2, 32 bit version
arm_64bit=0
gpio=22-27=a4
dtoverlay=disable-bt
kernel=kernel.img
### Raspberry pi Zero2, 64 bit version
arm_64bit=1
gpio=22-27=a4
dtoverlay=disable-bt
kernel=kernel8.img
### Raspberry pi Zero1, 32 bit version
arm_64bit=0
gpio=22-27=a4
dtoverlay=disable-bt
kernel=kernel.img

## files
Each configuration requires different files to be placed on the root of the SD_card.

### Raspberry pi 4B, 32 bit version
bcm2711-rpi-4-b.dtb, config.txt, fixup4.dat, kernel.img, start4.elf.
### Raspberry pi 4B, 64 bit version
bcm2711-rpi-4-b.dtb, config.txt, fixup4.dat, kernel8.img, start4.elf.
### Raspberry pi Zero2, 32 bit version
bcm2710-rpi-zero-2.dtb, bootcode.bin, config.txt, fixup4.dat, kernel.img, start.elf.
### Raspberry pi Zero2, 64 bit version
bcm2710-rpi-zero-2.dtb, bootcode.bin, config.txt, fixup4.dat, kernel8.img, start.elf.
### Raspberry pi Zero1, 32 bit version
bootcode.bin, config.txt, fixup.dat, kernel.img, start.elf.
## Blinker Program using CMAKE
To generate the build files via Cmake follow the following commands.
Run the following command from the root directory to configure the specific system:
`cmake -B <NAME> -G "Unix Makefiles" -DARCH=<VERSION> -DRPI_MODEL=<MODEL>`
Whereby:
\<NAME\> can be anything you want. F.e. “build_Z1_32bit”. This wil be used as the output directory where all of your build files will be located. The actual output (kernel.img or kernel8.img) can be found in the \<NAME\>/bin.
\<VERSION\> must be 'arm32' or 'arm64' depending if you want to use 32bit or 64bit version of the program.
\<MODEL\> must be 'Z1', 'Z2' or '4B' depending on the version raspberry pi you are using.

For example if you want to build for a raspberry pi Zero1, first use:
`cmake -B build_Z1_arm32 -G "Unix Makefiles" -DARCH=arm32 -DRPI_MODEL=Z1`
This will configure the build system, and generates the MAKE files in the <NAME> directory.
Now we can compile, do:
`cmake --build <NAME>`.
As an alternative you could also enter the \<NAME\> directory via `cd <NAME>` and run `make`.

If you want to see what is going on under the hood add `-- VERBOSE=1` to the command.

When the source file(s) have changed you need to run `cmake --build <NAME> again.
If a configuration has changed (f.e. New version compiler has been installed), you need to rerun the `cmake -B ….' command. But then first do 'rm -r <NAME>/*`
Updating Arm toolchain
The information for Cmake to be able to use the right Arm toolchain two seperate files can be found in the CmakeFiles directory:
toolchain-aarch64.cmake
toolchain-arm-eabi.cmake
In these files you will find the following: 
The line 'set(TOOLCHAIN_PREFIX "C:/Program Files (x86)/Arm GNU Toolchain aarch64-none-elf/14.3 rel1/bin")' needs to changed to be able to use the new version toolchain installed.

If you want debugging information add `-DCMAKE_BUILD_TYPE=Debug` to the `cmake -B …` command.

## notes
The ACT_LED present on may pi's, is not present on a rpi4b and therefore can not be controlled via the program on a rpi4b, in this case GPIO 21 is being used. A LED should be connected (via a 330ohm resistor to ground) to GPIO21 to see the blinking.
