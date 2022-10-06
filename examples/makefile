ROOT := ..

CXX_STD = -std=c++17

INCLUDES += -I$(ROOT)/include
INCLUDES += -I$(ROOT)/lib/ctti/include
INCLUDES += -I$(ROOT)/lib/map-macro

.PHONY: all
all: example1

example1: example1.cpp
	$(CXX) $(CXX_STD) $(INCLUDES) $^ -o $@

.PHONY: preprocessor
preprocessor: example1.cpp
	$(CXX) -E $(CXX_STD) $(INCLUDES) $^