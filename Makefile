TARGET_EXEC := bin/pathtracer

BUILD_DIR := build
SRC_DIRS := src

# Source auto-discovery

SRCS := $(shell find $(SRC_DIRS) -name '*.cc')
OBJS := $(SRCS:%.cc=$(BUILD_DIR)/%.o)

DEPS := $(OBJS:.o=.d)
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Compiler and linker settings

CXX := clang++

CPPFLAGS := $(INC_FLAGS) -MMD -MP
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -Wshadow -Werror

LDLIBS :=

# Target rules
$(TARGET_EXEC):	$(OBJS)
	mkdir -p $(dir $@)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: %.cc
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: run
run: $(TARGET_EXEC)
	@./${TARGET_EXEC}

.PHONY: print-sources
print-sources: $(SRCS)
	@echo $^ | xargs -n1 echo

.PHONY: print-objects
print-objects: $(OBJS)
	@echo $^ | xargs -n1 echo

.PHONY: print-includes
print-includes: $(INC_DIRS)
	@echo $(INC_DIRS) | xargs -n1 echo

.PHONY: clean
clean:
	rm -rf $(TARGET_EXEC) $(BUILD_DIR)

-include $(DEPS)
