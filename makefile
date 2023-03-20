CC = g++
DEFS ?= RUN
FLAGS ?=

BUILD_DIR ?= build
SRC_DIRS ?= src
LIB_DIRS ?= lib

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
LDFLAGS := $(shell find $(LIB_DIRS) -name *.o)
LDFLAGS += $(shell find $(LIB_DIRS) -name *.a)
LIBS := $(shell find $(LIB_DIRS)/*/$(SRC_DIRS) -name *.cpp)

CPPFLAGS ?= -Wall

TARGET_EXEC ?= stdstreams

all: bin/$(TARGET_EXEC)

bin/$(TARGET_EXEC): $(OBJS)
	@echo "Linking..."
	$(MKDIR_P) $(dir $@)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	@echo "Making Objects..."
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) -c $< -o $@ -D$(DEFS) $(FLAGS)

libs: $(LIBS)
	echo "$(LIBS)"
	echo "$^"
	$(CC) $(CPPFLAGS) -c $^ -o lib/$(notdir ${subst .cpp,.o,$^}) -D${DEFS}

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
