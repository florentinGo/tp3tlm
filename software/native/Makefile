CC=gcc
INCLUDE=-I. -I../../
CFLAGS=$(INCLUDE)

SRC = ../main.c
DEPENDENCIES = ../../address_map.h ../../hardware/offsets/memory.h \
 ../../hardware/offsets/gpio.h ../../hardware/offsets/timer.h \
  ../../hardware/offsets/vga.h ../../hardware/offsets/uart.h \
   ../../hardware/offsets/intc.h hal.h

main.o: $(SRC) $(DEPENDENCIES)
	$(CC) -c $(INCLUDE) $(SRC)

.PHONY: clean realclean
clean:
	$(RM) main.o

realclean: clean
	-$(RM) *~
