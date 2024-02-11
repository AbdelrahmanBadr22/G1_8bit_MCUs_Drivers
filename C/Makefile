
DIRS := $(shell find . -maxdepth 5 -type d | grep -E '\./hal/|\./common|\./mcal/|\./utils/')
SRC_PATH :=  $(foreach dir,$(DIRS),$(dir)) 
SOURCES  :=  $(foreach S,$(SRC_PATH),$(wildcard $(S)/*.c))
SRC_NAMES:= $(notdir $(SOURCES))
SOURCES_COUNT:= $(words $(SOURCES))
SOURCES_CTR:=0
INC:=  $(foreach dir,$(DIRS), -I$(dir))

include avr.mk
include pic.mk

# ---- STYLE CHECKING 
STYLE_CHECK_SCRIPT = ../scripts/style-checking/style-check.sh

# ---- DOXYGEN OPTIONS
DOXYGEN_SCRIPT = ../scripts/doxygen/doxygen.sh
TREAT_WARN_AS_ERROR = YES
TREAT_WARN_AS_WARN = NO
DOXYGEN_CONFIG = ./doxygen.cnf

# ---- TESTING 
REGRESSION_TEST_SCRIPT = ../scripts/testing/run-regressions.sh
REGRESSION_ALL_TEST_SCRIPT = ../scripts/testing/run-all-regressions.sh

.PHONY: all clean build 

all:build-avr style-check
	@echo -n "[Doxygen] : "
	@sh $(DOXYGEN_SCRIPT) $(DOXYGEN_CONFIG) $(TREAT_WARN_AS_WARN) 

# ------------------------------------------
# Rule to build avr for debug and test mode 
# make build-avr
# ------------------------------------------
build-avr: $(AVR_OBJS)
	@$(AVR_GCC) $(AVR_GCCFLAGS) $(AVR_OBJS) ./main.c -o $(AVR_ELF_TARGET)
	@$(AVR_OBJ_COPY) $(AVR_OBJ_COPY_OPTS) $(AVR_ELF_TARGET) $(AVR_HEX_TARGET)
	@echo "\n[Makefile][build] : Compiled successfully."

# ------------------------------------------
# Rule to build pic for debug and test mode 
# make build-avr
# ------------------------------------------
build-pic: $(PIC_OBJS)
	@$(PIC_XC8) $(PIC_XC8FLAGS) $(PIC_OBJS) ./main.c -o $(PIC_HEX_TARGET)
	@mv pic.cmf pic.hxl pic.s pic.sdb pic.sym startup.* $(PIC_OBJDIR)
	@rm -rf main.cmf main.d main.hxl main.p1 main.s main.sdb main.sym
	@echo "\n[Makefile][build] : Compiled successfully."

# ------------------------------------------
# Rule to build avr for real applications
# make opt-build-avr
# ------------------------------------------
build-avr-opt:$(AVR_OBJS)
	@$(AVR_GCC) $(AVR_OPT_CCFLAGS) $(AVR_OBJS) ./main.c -o $(AVR_ELF_TARGET)
	@$(AVR_OBJ_COPY) $(AVR_OBJ_COPY_OPTS) $(AVR_ELF_TARGET) $(AVR_HEX_TARGET)
	@echo "\n[Makefile][opt-build] : Compiled successfully."	

# ------------------------------------------
# Rule to build application linked to these 
# files in repo
# make build-app path=path/to/app
# TODO(@Mariamahmed44): #97 Implement this rule
# ------------------------------------------
build-app: $(AVR_OBJS) $(AVR_OBJDIR)
ifndef path 
	$(error "enter your path")
	
endif
ifeq ($(findstring app/, $(path)), app/)
	
		@$(AVR_GCC) $(AVR_GCCFLAGS) $(AVR_OBJS) $(wildcard $(path)/*.c) $(INC) -o $(path)/$(AVR_ELF_TARGET)
		@$(AVR_OBJ_COPY) $(AVR_OBJ_COPY_OPTS) $(path)/$(AVR_ELF_TARGET) $(path)/$(AVR_HEX_TARGET)
		@echo "\n[Makefile][build-app] : Compiled successfully."
else
	$(error "enter a valid path")
endif

# --------------------------------------------------------
# Rule to compile test 
# make compile-test src=path/to/main/file target=test_name
# --------------------------------------------------------
compile-test:$(AVR_OBJS)
	$(AVR_GCC) $(AVR_GCC_TEST_FLAGS) $(AVR_OBJS) $(src) -o $(target).testelf
	@echo "\n[Makefile]: Test compiled successfully."

# ------------------------------------------
# Rule to run regression tests
# There are two modes depending on filter value:
# 1] Run all regressions
# 	 make run-regressions filter=all 
# 2] Run specific regression test
#	 make run-regressions filter=regression-tests/regression-tests/test keep=1
#	 to keep output files
# ------------------------------------------
run-regressions: $(AVR_OBJDIR) $(build-avr)
	@echo -n "[Regression-tests] : Run Regressions\n"
ifeq ($(filter), all)	
	@sh -e $(REGRESSION_ALL_TEST_SCRIPT) 
else
	@sh -e $(REGRESSION_TEST_SCRIPT) -d $(filter) -k $(keep)
endif	
	@echo "\n[Makefile][Regression-Testing] : Tests have been run successfully."

# ----------------------------------------------------
# Rule to run style check rules in sources and headers
# make style-check
# ----------------------------------------------------
style-check:
	@echo -n "[Style-check] : "
	@sh $(STYLE_CHECK_SCRIPT) . ../scripts/style-checking/rules-scripts

# ----------------------------------------------------
# Rule to run doxygen and generate warnings for lines
# that not be documented
# make doxygen
# ----------------------------------------------------
doxygen:
	@echo -n "[Doxygen] : "
	@sh $(DOXYGEN_SCRIPT) $(DOXYGEN_CONFIG) $(TREAT_WARN_AS_ERROR)

# ----------------------------------------------------
# Rule clean all generated files through build process
# make clean
# ----------------------------------------------------
clean:
	@find . -name "*.o" -type f -delete
	@rm -rf .build
	@rm -rf *.o
	@rm -rf *.bin
	@rm -rf *.exe
	@rm -rf *.elf
	@rm -rf *.hex
	@rm -rf avr
	@rm -rf .build
	@find app/* -name "*.hex" -type f -delete
	@find app/* -name "*.elf" -type f -delete

# ----------------------------------------------------
# Rule to display help message
# make help
# TODO(@Mariamahmed44): #96 Fix this help messages
# ----------------------------------------------------
help:
	@echo "make build                		  		  : Build and generate elf and hex files (for debugging and development mode)"
	@echo "make opt-build            		  		  : Build and generate elf and hex files (for release mode)"
	@echo "make style-check          		  		  : Run vera rules and check if code follow our coding style"
	@echo "make doxygen              		  		  : Run doxygen and generate html file"
	@echo "make upload               		  		  : Upload hex file for target"
	@echo "make clean                		  		  : Clean generated files"
	@echo "make run-regression filter=all   		  : Run all regression test"
	@echo "make run-regression filter=elf/path/dir    : Run specific regression test"





