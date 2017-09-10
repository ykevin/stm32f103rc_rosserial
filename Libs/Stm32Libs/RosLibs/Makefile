ROSOBJS = $(sort \
		  $(patsubst %.cpp, %.o, $(wildcard *.cpp)))


roslib:$(ROSOBJS)
	$(AR) rcs libros.a $(ROSOBJS)


include ../../Makefile.include

clean:
	rm -f $(TOP_DIR)/$(ROSLIB_DIR)/*.o
	rm -f $(TOP_DIR)/$(ROSLIB_DIR)/*.a
