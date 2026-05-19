CXX ?= c++
SRC ?= main.cpp
OUT ?= .build/main
BUNDLE ?= .build/bundled.cpp

.SUFFIXES:

INCLUDE_FLAGS ?= -I.
DEBUG_FLAGS := -std=gnu++2b -fdiagnostics-color=always -Wall -g -fsanitize=address,undefined -ftrapv -DLOCAL
O2_FLAGS := -std=gnu++2b -Wall -O2 -DNDEBUG

SAMPLE_IN ?= sample.in
SAMPLE_OUT ?= sample.out

.PHONY: build buildo2 run runo2 test bundle clean new

build:
	@mkdir -p "$(dir $(OUT))"
	$(CXX) $(DEBUG_FLAGS) $(INCLUDE_FLAGS) "$(SRC)" -o "$(OUT)"

buildo2:
	@mkdir -p "$(dir $(OUT))"
	$(CXX) $(O2_FLAGS) $(INCLUDE_FLAGS) "$(SRC)" -o "$(OUT)"

run: build
	"$(OUT)"

runo2: buildo2
	"$(OUT)"

test: build
	@if [ ! -f "$(SAMPLE_IN)" ]; then echo "missing $(SAMPLE_IN)"; exit 1; fi
	@if [ ! -f "$(SAMPLE_OUT)" ]; then echo "missing $(SAMPLE_OUT)"; exit 1; fi
	@"$(OUT)" < "$(SAMPLE_IN)" > .build/actual.out
	@diff -u "$(SAMPLE_OUT)" .build/actual.out
	@echo "AC"

bundle:
	@command -v uvx >/dev/null 2>&1 || { echo "uvx is required. Install uv first: https://docs.astral.sh/uv/"; exit 1; }
	@mkdir -p "$(dir $(BUNDLE))"
	uvx --from online-judge-verify-helper oj-bundle -I lib "$(SRC)" > "$(BUNDLE)"
	@echo "bundled: $(BUNDLE)"

new:
	@if [ -z "$(NAME)" ]; then echo "usage: make new NAME=icpc2025prelim"; exit 1; fi
	@for problem in A B C D E F G H I J K L M N O P Q R S T U V W X Y Z; do \
		path="problems/$(NAME)/$$problem/$(NAME)_$$problem.cpp"; \
		if [ -e "$$path" ]; then echo "$$path already exists"; exit 1; fi; \
		makefile="problems/$(NAME)/$$problem/Makefile"; \
		if [ -e "$$makefile" ]; then echo "$$makefile already exists"; exit 1; fi; \
		sample_in="problems/$(NAME)/$$problem/sample.in"; \
		if [ -e "$$sample_in" ]; then echo "$$sample_in already exists"; exit 1; fi; \
		sample_out="problems/$(NAME)/$$problem/sample.out"; \
		if [ -e "$$sample_out" ]; then echo "$$sample_out already exists"; exit 1; fi; \
	done
	@for problem in A B C D E F G H I J K L M N O P Q R S T U V W X Y Z; do \
		dir="problems/$(NAME)/$$problem"; \
		path="$$dir/$(NAME)_$$problem.cpp"; \
		mkdir -p "$$dir"; \
		cp template.cpp "$$path"; \
		printf 'include ../../../task.mk\n' > "$$dir/Makefile"; \
		: > "$$dir/sample.in"; \
		: > "$$dir/sample.out"; \
		echo "created $$path"; \
	done

clean:
	rm -rf .build
