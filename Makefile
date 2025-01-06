SRC_DIR = src
BUILD_DIR = build

all:
	mkdir -pv $(BUILD_DIR)
	avr-gcc -Wall -Os -mmcu=attiny13 -o $(BUILD_DIR)/flash.elf $(SRC_DIR)/*.c
	avr-objcopy -j .text -j .data -O binary $(BUILD_DIR)/flash.elf $(BUILD_DIR)/flash.bin
	avr-objcopy -j .text -j .data -O ihex $(BUILD_DIR)/flash.elf $(BUILD_DIR)/flash.hex

clean:
	rm -rf $(BUILD_DIR)