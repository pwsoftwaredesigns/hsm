ROOT := ..

CXX_STD = -std=c++17

INCLUDES += -I$(ROOT)/include
INCLUDES += -I$(ROOT)/lib/ctti/include
INCLUDES += -I$(ROOT)/lib/map-macro
INCLUDES += -I$(ROOT)/lib/etl/include

DEFINES += -D'PW_HSM_TRANSITION_TRACE(source_, dest_)=std::cout << "\033[1;33mTRANSITION: " << source_ << " -> " << dest_ << "\033[m" << std::endl'
DEFINES += -D'PW_HSM_HANDLED_TRACE()=std::cout << "\033[1;33mHANDLED\033[m" << std::endl'
DEFINES += -D'PW_HSM_PASS_TRACE()=std::cout << "\033[1;33mPASS\033[m" << std::endl'

.PHONY: all
all: example1 example2

example1: example1.cpp cpp_config.cpp $(wildcard $(ROOT)/include/pw/hsm/*.hpp)
	$(CXX) $(CXX_STD) $(INCLUDES) $(DEFINES) cpp_config.cpp $< -o $@

example2: example2.cpp cpp_config.cpp $(wildcard $(ROOT)/include/pw/hsm/*.hpp)
	$(CXX) $(CXX_STD) $(INCLUDES) $(DEFINES) cpp_config.cpp $< -o $@
	
.PHONY: clean
clean:
	rm -r *.exe