ROOT := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
PROBLEM_DIR := $(CURDIR)
PROBLEM := $(notdir $(PROBLEM_DIR))
CONTEST := $(notdir $(patsubst %/,%,$(dir $(PROBLEM_DIR))))
SRC := $(PROBLEM_DIR)/$(CONTEST)_$(PROBLEM).cpp
SAMPLE_IN ?= sample.in
SAMPLE_OUT ?= sample.out
BUNDLE ?= submit.cpp

SAMPLE_IN_PATH := $(if $(filter /%,$(SAMPLE_IN)),$(SAMPLE_IN),$(PROBLEM_DIR)/$(SAMPLE_IN))
SAMPLE_OUT_PATH := $(if $(filter /%,$(SAMPLE_OUT)),$(SAMPLE_OUT),$(PROBLEM_DIR)/$(SAMPLE_OUT))
BUNDLE_PATH := $(if $(filter /%,$(BUNDLE)),$(BUNDLE),$(PROBLEM_DIR)/$(BUNDLE))

.PHONY: build buildo2 run runo2 test bundle clean

build buildo2 run runo2 test bundle clean:
	@$(MAKE) -C "$(ROOT)" SRC="$(SRC)" SAMPLE_IN="$(SAMPLE_IN_PATH)" SAMPLE_OUT="$(SAMPLE_OUT_PATH)" BUNDLE="$(BUNDLE_PATH)" $@
