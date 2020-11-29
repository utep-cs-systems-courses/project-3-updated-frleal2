# makfile configuration
COMMON_OBJECTS =
CPU            = msp430g2553
CFLAGS         = -mmcu=${CPU} -Os -I../h
LDFLAGS        = -L/lib -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC             = msp430-elf-gcc
AS             = msp430-elf-gcc - mmcu=${CPU} -c

install:
	(cd ./timerLib; make install)

led.o: led.h led.c

switches.o: switches.h switches.c

stateMachines.o: stateMachines.h stateMachines.c

p2_interrupt_handler.o: p2_interrupt_handler.c

wdInterruptHandler.o: wdInterruptHandler.c

buzzer.o: buzzer.h buzzer.c

project.elf: wdInterruptHandler.o p2_interrupt_handler.o buzzer.o main.o led.o stateMachines.o switches.o ./lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

all: project.elf

load: project.elf
	mspdebug rf2500 "prog $^"

clean:
	(cd timerLib; make clean)
	rm -rf lib h lib h
	rm -rf doxygen_docs/*
	rm -rf doxygen_docs/*rm -f *.o *.elf



