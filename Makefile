# Path vars

PRJ_NAME = mqtt-cpp

BUILDPATH ?= ..
BUILDPREFIX ?= build-

SRCDIR = src
APPDIR = app

BUILDDIR = $(BUILDPATH)/$(BUILDPREFIX)$(PRJ_NAME)
OBJDIR = $(BUILDDIR)/obj
SRCDIRS = 	app \
			src \
			src/mqtt \
			src/mqtt/action_listeners
EXECUTABLE = mqtt-cpp

LIB_HEADERS = ./lib
SRC_HEADERS = ./src

SRC += 	$(wildcard $(APPDIR)/*.cpp) \
		$(wildcard $(SRCDIR)/*.cpp) \
		$(wildcard $(SRCDIR)/*/*.cpp) \
		$(wildcard $(SRCDIR)/*/*/*.cpp)
OBJ := 	$(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC))

# -----------------------------------------------------------------------------
# Compiler and linker vars
INC += $(INCLUDE_DIRS) -I$(SRC_HEADERS) -I$(LIB_HEADERS)
CXXFLAGS += -Wall -std=c++11
LDLIBS += -lpaho-mqttpp3 -lpaho-mqtt3as -ljsoncpp

debug: CXXFLAGS += -g -O0
debug: CPPFLAGS += -DDEBUG
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------

.PHONY: clean distclean all debug

all: dir $(EXECUTABLE)

dir:
	@mkdir -p $(BUILDDIR)
	@for dir in $(patsubst ./%,%,$(SRCDIRS)); do \
		mkdir -p $(OBJDIR)/$$dir; \
	done

$(EXECUTABLE): $(BUILDDIR)/$(EXECUTABLE)

$(BUILDDIR)/$(EXECUTABLE): $(OBJ)
	@echo $(OBJ)
	$(CXX) $(CXXFLAGS) $(INC) $^ -o $@ $(LDLIBS)

$(OBJDIR)/src/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $(INC) $< -o $@

$(OBJDIR)/app/%.o: $(APPDIR)/%.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $(INC) $< -o $@


debug: dir $(EXECUTABLE)


# -----------------------------------------------------------------------------
# Cleanup
clean:
	rm -rf $(BUILDDIR)/*

distclean: clean
# -----------------------------------------------------------------------------
