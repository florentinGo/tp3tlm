ifndef CROSS_COMPILE
CROSS_COMPILE=microblaze-unknown-linux-gnu-
endif
DIR = /home/refaia/ensimag/3A/cours-tlm/microblaze/bin/
CROSS_COMPILE = $(DIR)microblaze-unknown-linux-gnu-
TARGET_CC = $(CROSS_COMPILE)gcc
TARGET_LD = $(CROSS_COMPILE)ld
TARGET_AS = $(CROSS_COMPILE)as
TARGET_OBJDUMP = $(CROSS_COMPILE)objdump
TARGET_READELF = $(CROSS_COMPILE)readelf
HOST_CC = gcc
HOST_LD = ld
HOST_OBJDUMP = objdump
HOST_READELF = readelf

INCLUDE = -I. -I../..
SRC = ../main.c
DEPENDENCIES = ../../address_map.h ../../hardware/offsets/memory.h \
 ../../hardware/offsets/gpio.h ../../hardware/offsets/timer.h \
  ../../hardware/offsets/vga.h ../../hardware/offsets/uart.h \
   ../../hardware/offsets/intc.h hal.h

OBJS = main.o boot.o it.o
EXEC = a.out
# Disassembly of the generated executable.
dump.txt: $(EXEC)
	$(TARGET_OBJDUMP) -d $< > $@

# Summary of the sections and their size.
sections.txt: $(EXEC)
	$(TARGET_READELF) -S $< > $@


$(EXEC): $(OBJS) ldscript
	$(TARGET_LD) -T  ldscript $^


main.o: $(SRC) $(DEPENDENCIES)
	$(TARGET_CC) -c $(INCLUDE) $(SRC)

# (compile with target C compiler)

%.o: %.s
	$(TARGET_AS) $^ -o $@


.PHONY: clean realclean
clean:
	-$(RM) $(OBJS) $(EXEC) dump.txt

realclean: clean
	-$(RM) *~
