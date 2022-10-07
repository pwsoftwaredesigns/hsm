CXX_STD := -std=c++17
ROOT := ../..

CXX_STD = -std=c++17

INCLUDES += -I$(ROOT)/include
INCLUDES += -I$(ROOT)/lib/ctti/include
INCLUDES += -I$(ROOT)/lib/map-macro
INCLUDES += -I$(ROOT)/lib/etl/include

SOURCES += $(wildcard *.cpp)

DEFINES += -D'PW_HSM_TRANSITION_TRACE(source_, dest_)=std::cout << "\033[1;33mTRANSITION: " << source_ << " -> " << dest_ << "\033[m" << std::endl'
DEFINES += -D'PW_HSM_HANDLED_TRACE()=std::cout << "\033[1;33mHANDLED\033[m" << std::endl'
DEFINES += -D'PW_HSM_PASS_TRACE()=std::cout << "\033[1;33mPASS\033[m" << std::endl'



.PHONY: all
all: example3

example3: $(SOURCES)
	$(CXX) $(CXX_STD) $(CXX_FLAGS) $(INCLUDES) $(DEFINES) $^ -o $@
	
.PHONY: clean
clean:
	rm -rf *.exe
	rm -f example3