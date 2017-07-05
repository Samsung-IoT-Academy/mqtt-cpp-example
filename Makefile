# Path vars

PRJ_NAME	= mqtt-cpp

BUILDDIR 	?= ../build-$(PRJ_NAME)
OBJDIR 		= $(BUILDDIR)/obj
SRCDIR 		= src
APPDIR 		= app
EXECUTABLE 	= cpp-mqtt

APPSRC 	:= $(shell find $(APPDIR) -name '*.cpp')
SOURCES := $(shell find $(SRCDIR) -name '*.cpp') $(APPSRC)
SRCDIRS := $(shell find . -name '*.cpp' -exec dirname {} \; | uniq)
OBJS 	:= $(patsubst %.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Compiler and linker vars

INC 		+= -Isrc
CXXFLAGS 	+= -Wall -std=c++11
LDLIBS 		+= -lpaho-mqttpp3

ifdef DEBUG
  CPPFLAGS += -DDEBUG
  CXXFLAGS += -g -O0
else
  CPPFLAGS += -D_NDEBUG
  CXXFLAGS += -O2
endif

all: dir $(EXECUTABLE)

dir:
	mkdir -p $(BUILDDIR)
	@for dir in $(patsubst ./%,%,$(SRCDIRS)); do \
		mkdir -p $(OBJDIR)/$$dir; \
	done

$(EXECUTABLE): $(BUILDDIR)/$(EXECUTABLE)

$(BUILDDIR)/$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INC) -c $< -o $@
	
# Cleanup

.PHONY: clean distclean

clean:
	rm -rf $(BUILDDIR)/*

distclean: clean