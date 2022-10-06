CXX_STD = -std=c++17

INCLUDES += -Ictti/include
INCLUDES += -Imap-macro

.PHONY: example1
example1: example1.cpp
	$(CXX) $(CXX_STD) $(INCLUDES) $^ -o $@
