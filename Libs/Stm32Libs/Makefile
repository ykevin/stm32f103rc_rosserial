OBJS = $(sort \
 	   $(patsubst %.c,%.o,$(wildcard CMSIS_CM3/*.c)) \
 	   $(patsubst %.c,%.o,$(wildcard STM32F10x_StdPeriph_Driver/src/*.c)) \
 	   $(patsubst %.c,%.o,$(wildcard STM32_USB-FS-Device_Driver/src/*.c)))


stm32lib:$(OBJS)
	$(AR) rcs libstm32f1.a $(OBJS)

include ../../Makefile.include

clean:
	rm -f $(TOP_DIR)/$(STM32LIB_DIR)/*.a
	rm -f $(TOP_DIR)/$(STM32LIB_DIR)/STM32_USB-FS-Device_Driver/src/*.o
	rm -f $(TOP_DIR)/$(STM32LIB_DIR)/STM32_USB-FS-Device_Driver/src/*.o
	rm -f $(TOP_DIR)/$(STM32LIB_DIR)/CMSIS_CM3/*.o



