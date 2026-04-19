TARGET  = firmware
CC      = arm-none-eabi-gcc
CFLAGS  = -mcpu=cortex-m3 -mthumb -nostdlib -nostartfiles -O0 -g
LDFLAGS = -T linker.ld -nostdlib

all: $(TARGET).elf

$(TARGET).elf: startup.s main.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f *.elf

run: $(TARGET).elf
	qemu-system-arm -machine lm3s811evb \
	    -kernel $(TARGET).elf \
	    -nographic \
	    -semihosting

debug: $(TARGET).elf
	qemu-system-arm -machine lm3s811evb \
	    -kernel $(TARGET).elf \
	    -serial stdio \
	    -nographic \
	    -S -gdb tcp::3333
