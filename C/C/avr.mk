
AVR_GCC:= avr-gcc
AVR_MCU:= atmega32a
AVR_CLK:= 8000000
AVR_OBJ_COPY:= avr-objcopy
DEF_AVR:=1
AVR_GCCFLAGS:=    -g -Wall -DF_CPU=$(AVR_CLK) -mmcu=$(AVR_MCU) -gdwarf-2 -DMCU_TYPE=$(DEF_AVR) -O2 -Werror
AVR_OPT_CCFLAGS:= -g -Wall -DF_CPU=$(AVR_CLK) -mmcu=$(AVR_MCU) -gdwarf-2 -DMCU_TYPE=$(DEF_AVR) -O3 -Werror
AVR_GCC_TEST_FLAGS:= -g -Wall -DF_CPU=$(AVR_CLK) -mmcu=$(AVR_MCU) -gdwarf-2 -DMCU_TYPE=$(DEF_AVR) -O2
AVR_OBJ_COPY_OPTS:= -j .text -j .data -O ihex 

AVR_TARGET:= avr
AVR_OBJDIR := .build/avr/obj
AVR_OBJS:= $(patsubst %.c,$(AVR_OBJDIR)/%.o,$(SRC_NAMES))


AVR_HEX_TARGET:= $(AVR_TARGET).hex
AVR_ELF_TARGET:=$(AVR_TARGET).elf

# AVRDUDE options
AVRDUDE = avrdude
AVRDUDE_PROGRAMMER = usbasp
AVRDUDE_MCU = m32
AVRDUDE_PORT = /dev/ACM0

upload-avr: $(HEX)
	@$(AVRDUDE) -c $(AVRDUDE_PROGRAMMER) -p $(AVRDUDE_MCU) -P $(AVRDUDE_PORT) -U flash:w:$(AVR_TARGET).hex:i

$(AVR_OBJDIR)/%.o : **/**/%.c
	@mkdir -p $(AVR_OBJDIR)
	@$(AVR_GCC) $(AVR_GCCFLAGS) $(INC) -c $< -o $@
	@$(eval SOURCES_CTR=$(shell echo $$(($(SOURCES_CTR)+1))))
	@echo "[Makefile] : [$(SOURCES_CTR)/$(words $(SOURCES))] $<"
