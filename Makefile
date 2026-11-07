# Each problem lives in problems/<number>-<slug>/ with:
#   solution.c  the code submitted to LeetCode
#   test.c      a main() that checks it on the examples
#
#   make            build and test every problem
#   make 0001       build and test one problem (by number prefix)
#   make clean

CC := gcc
CFLAGS := -std=c17 -Wall -Wextra -Werror -g -fsanitize=address,undefined

PROBLEMS := $(wildcard problems/*/)
BIN := build

.PHONY: all clean
# Keep the test binaries (for gdb) instead of deleting them as intermediates.
.SECONDARY:
all: $(patsubst problems/%/,test-%,$(PROBLEMS))

test-%: $(BIN)/%
	@./$< && echo "ok   $*"

$(BIN)/%: problems/%/solution.c problems/%/test.c
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) -o $@ problems/$*/test.c

# `make 0001` runs every problem whose folder starts with 0001.
%:
	@$(MAKE) --no-print-directory $(patsubst problems/%/,test-%,$(wildcard problems/$@*/))

clean:
	rm -rf $(BIN)
