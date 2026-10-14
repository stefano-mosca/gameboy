CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -Wpedantic -g -O0
CPPFLAGS  := -Iinclude
LDFLAGS   :=

SRC_DIR   := src
INC_DIR   := include
BUILD_DIR := build
TARGET    := $(BUILD_DIR)/emulator

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "✓ Build completata: $(TARGET)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

run: all
	./$(TARGET) $(ARGS)

clean:
	rm -rf $(BUILD_DIR)
	@echo "✓ Cartella $(BUILD_DIR) rimossa"

rebuild: clean all

-include $(DEPS)

.PHONY: all run clean rebuild
