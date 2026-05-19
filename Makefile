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
	@if [ -z "$(NAME)" ]; then echo "usage: make new NAME=problems/a.cpp"; exit 1; fi
	@mkdir -p "$$(dirname "$(NAME)")"
	@if [ -e "$(NAME)" ]; then echo "$(NAME) already exists"; exit 1; fi
	@cp template.cpp "$(NAME)"
	@echo "created $(NAME)"

clean:
	rm -rf .build
