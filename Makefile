CXX = g++

CXXFLAGS = \
		-std=c++20 \
		-Wall \
		-Wextra \
		-Werror \
		-O3

LDFLAGS = -flto

BRED    = \033[1;31m
BGREEN  = \033[1;32m
BYELLOW = \033[1;33m
GREEN   = \033[1;35m
BCYAN   = \033[1;36m
RESET   = \033[0m

INCLUDE_DIR = include
LIB_DIR = lib
SOURCE_DIR = src
ASM_DIR = asm
BUILD_DIR := build

CPPFLAGS = -I $(abspath $(INCLUDE_DIR))

LIBS = $(notdir $(wildcard $(LIB_DIR)/*.cpp))
SOURCES = $(notdir $(wildcard $(SOURCE_DIR)/*.cpp))


LIB_OBJECTS = $(LIBS:%.cpp=$(BUILD_DIR)/%.o)
SOURCE_OBJECTS = $(SOURCES:%.cpp=$(BUILD_DIR)/%.o)

TEST_OBJ = $(BUILD_DIR)/test.o
CODE_OBJ = $(BUILD_DIR)/code.o
RUN_OBJ = $(BUILD_DIR)/run.o

TEST_EXE = $(BUILD_DIR)/test
CODE_EXE = $(BUILD_DIR)/code
RUN_EXE = $(BUILD_DIR)/run

all: $(LIB_OBJECTS) $(SOURCE_OBJECTS)

$(RUN_EXE): $(RUN_OBJ) $(LIB_OBJECTS)
	@printf "$(BYELLOW)Linking executable $(BCYAN)$@$(RESET)\n"

	@printf "$(BGREEN)>>> $(RESET)"
	$(CXX) $(LDFLAGS) $^ -o $@

$(TEST_EXE): $(TEST_OBJ)
	@printf "$(BYELLOW)Linking executable $(BCYAN)$@$(RESET)\n"
	@printf "$(BGREEN)>>> $(RESET)"

	$(CXX) $(LDFLAGS) $^ -o $@

$(CODE_EXE): $(CODE_OBJ) $(LIB_OBJECTS)
	@printf "$(BYELLOW)Linking executable $(BCYAN)$@$(RESET)\n"
	@printf "$(BGREEN)>>> $(RESET)"

	$(CXX) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(LIB_DIR)/%.cpp Makefile
	@printf "$(BYELLOW)Building object file $(BCYAN)$@$(RESET)\n"

	@mkdir -p $(BUILD_DIR)

	@printf "$(BGREEN)>>> $(RESET)"
	$(CXX) -c $< $(CXXFLAGS) $(CPPFLAGS) $(DEPFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp Makefile
	@printf "$(BYELLOW)Building object file $(BCYAN)$@$(RESET)\n"

	@mkdir -p $(BUILD_DIR)

	@printf "$(BGREEN)>>> $(RESET)"
	$(CXX) -c $< $(CXXFLAGS) $(CPPFLAGS) -o $@


ifeq (code, $(firstword $(MAKECMDGOALS)))
  CODE_ARGS := $(wordlist 2, $(words $(MAKECMDGOALS)), $(MAKECMDGOALS))
  $(eval $(CODE_ARGS):;@:)
else ifeq (run, $(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2, $(words $(MAKECMDGOALS)), $(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
else ifeq (test, $(firstword $(MAKECMDGOALS)))
  CXXFLAGS += -pthread
  CPPFLAGS += -I /opt/homebrew/opt/googletest/include
  LDFLAGS += -L /opt/homebrew/opt/googletest/lib -lgtest -lgtest_main -pthread
endif

test: $(TEST_EXE)
	@printf "$(BGREEN)>>> $(RESET)"
	./$<

code: $(CODE_EXE)
	@printf "$(BGREEN)>>> $(RESET)"
	./$< $(ASM_DIR)/$(CODE_ARGS)

run: $(RUN_EXE)
	@printf "$(BGREEN)>>> $(RESET)"
	./$< $(ASM_DIR)/$(RUN_ARGS)

clean:
	@echo "$(BYELLOW)Cleaning process$(RESET)"

	@printf "$(BGREEN)>>> $(RESET)"
	rm -rf $(BUILD_DIR)
	@printf "$(BGREEN)>>> $(RESET)"
	rm -f $(ASM_DIR)/*.bcode

.PHONY: test code run clean