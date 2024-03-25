CC=clang
CC_OPT=-emit-llvm -c -g -O0 -Xclang -disable-O0-optnone 
LINKER=llvm-link
LIBRARY_FOLDER=libs/fixed
BUG_LIBRARY_FOLDER=libs/bugged
UTILS_FOLDER=klee/utils
NORMAL_TESTS=klee/normal
BUG_TESTS=klee/bugs
KLEE_INCLUDE=../klee_src/include

BUILD_FOLDER=klee_build


lib = $(wildcard $(LIBRARY_FOLDER)/*.c)
libbc = $(addprefix $(BUILD_FOLDER)/,$(lib:.c=.bc))

libbug = $(wildcard $(BUG_LIBRARY_FOLDER)/*.c)
libbugbc = $(addprefix $(BUILD_FOLDER)/,$(libbug:.c=.bc))

tests =  $(wildcard $(NORMAL_TESTS)/**/*.c)
testsbc = $(addprefix $(BUILD_FOLDER)/,$(tests:.c=.bc))

testbugs = $(wildcard $(BUG_TESTS)/*.c)
testbugsbc = $(addprefix $(BUILD_FOLDER)/,$(testbugs:.c=.bc))

.PHONY: clean

.SECONDARY: $(libbc) $(libbugbc)

default: all

all: normal bug

bug: $(testbugsbc)

normal: $(testsbc)

$(BUILD_FOLDER)/klee/bugs/%.bc: klee/bugs/%.c $(libbugbc) $(BUILD_FOLDER)/utils/utils.bc 
	@mkdir -p $(dir $@)
	@echo "Building $@"
	@$(CC) $(CC_OPT) -I $(KLEE_INCLUDE) -I $(UTILS_FOLDER) -I $(BUG_LIBRARY_FOLDER)/include -o $@__i $< > /dev/null 2>&1
	@$(LINKER) $@__i $(libbugbc) $(BUILD_FOLDER)/utils/utils.bc -o $@ > /dev/null 2>&1

$(BUILD_FOLDER)/$(BUG_LIBRARY_FOLDER)/%.bc: $(BUG_LIBRARY_FOLDER)/%.c
	@mkdir -p $(dir $@)
	@echo "Building $@"
	@$(CC) $(CC_OPT) -I $(BUG_LIBRARY_FOLDER)/include -o $@ $^ > /dev/null 2>&1

$(BUILD_FOLDER)/klee/normal/%.bc: klee/normal/%.c $(libbc) $(BUILD_FOLDER)/utils/utils.bc 
	@mkdir -p $(dir $@)
	@echo "Building $@"
	@$(CC) $(CC_OPT) -I $(KLEE_INCLUDE) -I $(UTILS_FOLDER) -I $(LIBRARY_FOLDER)/include -o $@__i $< > /dev/null 2>&1
	@$(LINKER) $@__i $(libbc) $(BUILD_FOLDER)/utils/utils.bc -o $@ > /dev/null 2>&1

$(BUILD_FOLDER)/utils/utils.bc: $(UTILS_FOLDER)/utils.c
	@mkdir -p $(dir $@)
	@echo "Building $@"
	@$(CC) $(CC_OPT) -I $(KLEE_INCLUDE) -I $(UTILS_FOLDER) -o $@ $^ > /dev/null 2>&1

$(BUILD_FOLDER)/lib/%.bc: lib/%.c
	@mkdir -p $(dir $@)
	@echo "Building $@"
	@$(CC) $(CC_OPT) -I $(LIBRARY_FOLDER)/include -o $@ $^ > /dev/null 2>&1

clean:
	@./clean.sh
