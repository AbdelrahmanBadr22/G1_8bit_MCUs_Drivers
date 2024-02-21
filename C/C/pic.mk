PIC_XC8:= xc8-cc
PIC_MCU:= 18F46K20
PIC_CLK:= 8000000
DEF_PIC:=2

PIC_XC8FLAGS:=     -Og -mdownload-hex -wall -mosccal=$(PIC_CLK) -mcpu=$(PIC_MCU) -DMCU_TYPE=$(DEF_PIC) -O2 -werror
PIC_OPT_XC8FLAGS:= -Og -mdownload-hex -wall -mosccal=$(PIC_CLK) -mcpu=$(PIC_MCU) -DMCU_TYPE=$(DEF_PIC) -O3 -werror

PIC_TARGET:= pic
PIC_OBJDIR := .build/pic/obj
PIC_OBJS:= $(patsubst %.c,$(PIC_OBJDIR)/%.p1,$(SRC_NAMES))

PIC_HEX_TARGET:= $(PIC_TARGET).hex
PIC_ELF_TARGET:= $(PIC_TARGET).elf

$(PIC_OBJDIR)/%.p1 : **/**/%.c
	@mkdir -p $(PIC_OBJDIR)
	@$(PIC_XC8) $(PIC_XC8FLAGS) $(INC) -c $< -o $@
	@$(eval SOURCES_CTR=$(shell echo $$(($(SOURCES_CTR)+1))))
	@echo "[Makefile] : [$(SOURCES_CTR)/$(words $(SOURCES))] $<"