## stm32f103rc_rosserial bsp for ros node communication

#### How to build stm32f103rc_rosserial?
* Install Ubuntu16.04 package
> $sudo apt-get install -y git build-essential gcc-arm-none-eabi libstdc++-arm-none-eabi-newlib  libusb-1.0-0-dev  
* Install st-link driver
> $git clone https://github.com/texane/stlink.git  
$cd stlink  
$make  
$cd build/Release  
$sudo make install
* Programmer firmware
> $cd stm32f103rc_rosserial  
$make  
$make flash

#### stm32 ISP method

ISP upload firmware, please set BOOT0 to 1, set BOOT1 to 0
* 1.use stm32flash
> $sudo apt-get install stm32flash  
sudo stm32flash -w main.bin -v -g 0x0 /dev/ttyUSB0 -b 115200

* 2.use python scprit
> ./ISP/stm32loader.py -w -p /dev/ttyUSB0 -b 115200 main.bin

#### Complete User Manual to UserManual Folder

#### QQ Group: 130486387
