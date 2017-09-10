## Stm32Module 
> This is stm32 robot 2wd moudle driver bsp  
1. motor driver  
2. encoder driver  
3. servo driver  
4. serial driver to ros  
5. sonar driver  
6. led driver

#### stm32 ISP method

ISP upload firmware, please set BOOT0 to 1, set BOOT1 to 0
* 1.use stm32flash
> $sudo apt-get install stm32flash  
sudo stm32flash -w main.bin -v -g 0x0 /dev/ttyUSB0 -b 115200

* 2.use python scprit
> ./ISP/stm32loader.py -w -p /dev/ttyUSB0 -b 115200 main.bin


