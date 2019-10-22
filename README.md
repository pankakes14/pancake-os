# pancake-os #
Simple operating system for rasberry pi. Based on tutorial from https://jsandler18.github.io/


# Installing #
Run make command to build the source into an image file:
    make
This will generate an image 'pancake_os.img' that can be loaded onto an SD card and booted in the raspi. You will first need to actually install a cross comiler to be able to generate a binary for the rasberry pi's ARM core. Install the GNU arm comiler by running:
    sudo apt install gcc-arm-none-eabi

You can also use an arm simulator called 'qemu' to test the code. Use:
    make run
to run the simulator. You'll have to install it first by running the following command in ubuntu:
    sudo apt install qemu-system-arm


Processors:
* Rpi1 - BCM2835
* Rpi2 - 


# Other Info #

broadcom 2835 errata: https://elinux.org/BCM2835_datasheet_errata