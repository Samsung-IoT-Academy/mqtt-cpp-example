

ifdef DEBUG
  CPPFLAGS += -DDEBUG
  CXXFLAGS += -g -O0
else
  CPPFLAGS += -D_NDEBUG
  CXXFLAGS += -O2
endif

CXXFLAGS += -Wall -std=c++11
LDLIBS += -lpaho-mqttpp3

all: async_publish

async_publish: main.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $< $(LDLIBS) 
	
# Cleanup

.PHONY: clean distclean

clean:
	rm -f $(TGTS)

distclean: clean