CC := avr-gcc
MCU := atmega32a
CLK := 8000000

CCFLAGS := -g -Wall -DF_CPU=$(CLK) -mmcu=$(MCU) -gdwarf-2 -DMCU_TYPE=1 -O3 -Werror

TARGET := avr

DIRS := $(shell find ../../../ -maxdepth 5 -type d | grep -E '\./hal/|\./common|\./mcal/|\./utils/')
SRC_PATH := $(foreach dir,$(DIRS),$(dir))
SOURCES := $(foreach S,$(SRC_PATH),$(wildcard $(S)/*.c))
SOURCES_COUNT := $(words $(SOURCES))
SOURCES_CTR := 0
SOURCES += ./main.c
INC := $(foreach dir,$(DIRS), -I$(dir))
OBJS := $(SOURCES:.c=.o)
$(foreach dir,$(DIRS),$(eval OBJS += $(wildcard $(dir)/*.o)))

# Exclude main.o from OBJS
OBJS := $(filter-out ./main.o, $(OBJS))

# Add object file of the current directory
OBJS += $(patsubst %.c, %.o, $(wildcard ./*.c))

# Hex file
HEX_TARGET := $(TARGET).hex
ELF_TARGET := $(TARGET).elf

# AVRDUDE options
AVRDUDE := avrdude
AVRDUDE_PROGRAMMER := usbasp
AVRDUDE_MCU := m32
AVRDUDE_PORT := /dev/ACM0
STYLE_CHECK_SCRIPT := ../scripts/style-checking/style-check.sh

.PHONY: all clean build

all: $(OBJS)
	$(MAKE) -C ../../../ -f Makefile build
	@$(CC) $(CCFLAGS) $(OBJS) -o $(ELF_TARGET)
	@avr-objcopy -j .text -j .data -O ihex $(ELF_TARGET) $(HEX_TARGET)
	@echo "\n[Makefile] : Compiled successfully."

%.o: %.c
	@$(CC) $(CCFLAGS) $(INC) -c $< -o $@
	@$(eval SOURCES_CTR=$(shell echo $$(($(SOURCES_CTR)+1))))
	@echo "[Makefile] : [$(SOURCES_CTR)/$(words $(SOURCES))] $<"

upload: $(HEX)
	@$(AVRDUDE) -c $(AVRDUDE_PROGRAMMER) -p $(AVRDUDE_MCU) -P $(AVRDUDE_PORT) -U flash:w:$(TARGET).hex:i

clean:
	$(MAKE) -C ../../../ -f Makefile clean
	@find . -name "*.o" -type f -delete
	@rm -rf *.o
	@rm -rf *.bin
	@rm -rf *.exe
	@rm -rf *.elf
	@rm -rf *.hex
	@rm -rf avr
