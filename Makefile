# Example Makefile for PSPSDK
# Note: PSPSDK may not be preinstalled on GitHub Actions runner.
# You may need to adapt this file to your environment.

TARGET = NarutoRoadToWorldPeace
SRC = src/main.c
OBJS = $(SRC:.c=.o)

CFLAGS = -G0 -Wall -O2 -fno-builtin
LDFLAGS = -lpspuser -lpspdisplay -lpspctrl -lpspdebug

all: EBOOT.PBP

%.o: %.c
	psp-gcc $(CFLAGS) -c $< -o $@

EBOOT.PBP: $(SRC)
	psp-gcc $(CFLAGS) -o kernel.elf $(SRC)
	oc --elf kernel.elf --output EBOOT.PBP || echo "oc tool not found - create EBOOT.PBP using your PSPSDK tools"

clean:
	rm -f *.o *.elf EBOOT.PBP kernel.elf
