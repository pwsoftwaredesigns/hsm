PROJECT_NAME := example1

ROOT := ../..

CXX_STD = -std=gnu++17

INCLUDES += -I$(ROOT)/include
INCLUDES += -I$(ROOT)/lib/ctti/include
INCLUDES += -I$(ROOT)/lib/lib-pw-macros/include
INCLUDES += -I$(ROOT)/lib/etl/include

SOURCES += $(wildcard *.cpp)
SOURCES += ../cpp_config.cpp

DEFINES += -D'PW_HSM_TRANSITION_TRACE(source_, dest_)=std::cout << "\033[1;33mTRANSITION: " << source_ << " -> " << dest_ << "\033[m" << std::endl'
DEFINES += -D'PW_HSM_HANDLED_TRACE()=std::cout << "\033[1;33mHANDLED\033[m" << std::endl'
DEFINES += -D'PW_HSM_PASS_TRACE()=std::cout << "\033[1;33mPASS\033[m" << std::endl'



.PHONY: all
all: $(PROJECT_NAME)

$(PROJECT_NAME): $(SOURCES)
	$(CXX) $(CXX_STD) $(CXX_FLAGS) $(INCLUDES) $(DEFINES) $^ -o $@
	
.PHONY: clean
clean:
	rm -rf *.exe
	rm -f $(PROJECT_NAME)
	
ifdef WHAT
	
.PHONY: pre
pre: $(WHAT)
	$(CXX) $(CXX_STD) $(CXX_FLAGS) $(INCLUDES) $(DEFINES) -E $^
	
endif