ROOT := ..

CXX_STD = -std=c++17

SOURCES += cpp_config.cpp

INCLUDES += -I$(ROOT)/include
INCLUDES += -I$(ROOT)/lib/ctti/include
INCLUDES += -I$(ROOT)/lib/map-macro
INCLUDES += -I$(ROOT)/lib/etl/include

ifdef ARM

	OBJDUMP := arm-none-eabi-objdump -marm -Mforce-thumb

	CXX := arm-none-eabi-g++
	SOURCES += syscalls.cpp
	override CXX_FLAGS += "-mcpu=cortex-m33"
	override CXX_FLAGS += -fno-exceptions
	override CXX_FLAGS += -fno-rtti
	override CXX_FLAGS += -fdata-sections
	override CXX_FLAGS += -ffunction-sections

else

	OBJDUMP := objdump

	DEFINES += -D'PW_HSM_TRANSITION_TRACE(source_, dest_)=std::cout << "\033[1;33mTRANSITION: " << source_ << " -> " << dest_ << "\033[m" << std::endl'
	DEFINES += -D'PW_HSM_HANDLED_TRACE()=std::cout << "\033[1;33mHANDLED\033[m" << std::endl'
	DEFINES += -D'PW_HSM_PASS_TRACE()=std::cout << "\033[1;33mPASS\033[m" << std::endl'

endif

.PHONY: all
all: example1 example2

example1: example1.cpp $(SOURCES) $(wildcard $(ROOT)/include/pw/hsm/*.hpp)
	$(CXX) $(CXX_STD) $(CXX_FLAGS) $(INCLUDES) $(DEFINES) $(SOURCES) $< -o $@

example2: example2.cpp $(SOURCES) $(wildcard $(ROOT)/include/pw/hsm/*.hpp)
	$(CXX) $(CXX_STD) $(CXX_FLAGS) $(INCLUDES) $(DEFINES) $(SOURCES) $< -o $@

.PHONY: clean
clean:
	rm -rf *.exe
	rm -f example1
	rm -f example2
	rm -rf *.s
	
.PHONY: dump
dump: $(WHAT)
	$(OBJDUMP) -D -C $< > $<.s