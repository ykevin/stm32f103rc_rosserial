
NAME = main

STARTUP_OBJ = Libs/Stm32Libs/CMSIS_CM3/startup/gcc/startup_$(STARTUP_FILE).o

#OBJS = $(sort \
 	   $(patsubst %.cpp,%.o,$(wildcard Src/*.cpp)) \
 	   $(patsubst %.cc,%.o,$(wildcard Src/*.cc)) \
 	   $(patsubst %.c,%.o,$(wildcard Src/*.c)) \
 	   $(patsubst %.s,%.o,$(wildcard *.s)) \
 	   $(STARTUP_OBJ))

OBJS  += ./Src/main.o

OBJS  += $(STARTUP_OBJ)
OBJS  += ./Bsp/millisecondtimer.o
OBJS  += ./Bsp/hardwareserial.o
OBJS  += ./Driver/led.o
OBJS  += ./Driver/battery.o

include Makefile.include

clean:
	rm -f $(OBJS)
	rm -f *.a
	rm -f *.bin
	rm -f *.d
	rm -f *.elf
	rm -f *.hex
	rm -f *.list
	rm -f *.log
	rm -f *.srec

