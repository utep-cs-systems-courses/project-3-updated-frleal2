# makfile configuration
COMMON_OBJECTS =
CPU            = msp430g2553
CFLAGS         = -mmcu=${CPU} -Os -I../h
LDFLAGS        = -L/lib -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC             = msp430-elf-gcc
AS             = msp430-elf-gcc -mmcu=${CPU} -c

all:toy.elf

#additional rules

toy.elf: ${COMMON_OBJECTS} wdt_handler.o stateMachines.o switches.o led.o buzzer.o main.o  
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd -lp2sw

load: toy.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
