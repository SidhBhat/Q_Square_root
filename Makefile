#!/usr/bin/make -f
# Set environment variables

# this makefile follows the below conventions for variables denoting files and directories
# all directory names must end with a terminal '/' character
# file names never end in terminal '/' character


#===================================================

SHELL = /bin/bash

# set this variable if using shared library, to any value (cleaning existing build files may be necessary).
SHARED =

#===================================================
# Compile commands
#===================================================
CXX         = g++
CXXLIBS     =
CXXINCLUDES =
CXXFLAGS    = -g -O -Wall -std=c++20
ifdef SHARED
CXXFLAGS += -fpie
endif
ifdef SHARED
CXXRPATH =
endif
#===================================================
# Build Directories
#===================================================
override srcdir     = src/
override buildir    = build/
#===================================================
# Install directories
#===================================================
DESTDIR     =
prefix      = /usr/local/
override exec_prefix = $(prefix)
override bindir      = $(exec_prefix)/bin/
override datarootdir = $(prefix)/share/
override datadir     = $(datarootdir)
override libdir      = $(prefix)/lib/
#===================================================
prog_name    = quaketest
#===================================================
override INSTALL          = install -D -p
override INSTALL_PROGRAM  = $(INSTALL) -m 755
override INSTALL_DATA     = $(INSTALL) -m 644
#===================================================
# Source and target objects
#===================================================
SRCS1  = $(wildcard $(srcdir)*.cpp)
SRCS2  = $(wildcard $(srcdir)*.cxx)
SRCS3  = $(wildcard $(srcdir)*.cc)
SRCS   = $(SRCS1) $(SRCS2) $(SRCS3)
OBJS   = $(patsubst $(srcdir)%.cpp,$(buildir)cpp%.o,$(SRCS1)) $(patsubst $(srcdir)%.cxx,$(buildir)cxx%.o,$(SRCS2)) $(patsubst $(srcdir)%.cc,$(buildir)cc%.o,$(SRCS3))
MKS    = $(patsubst $(srcdir)%.cpp,$(buildir)pp%.mk,$(SRCS1)) $(patsubst $(srcdir)%.cxx,$(buildir)xx%.mk,$(SRCS2)) $(patsubst $(srcdir)%.cc,$(buildir)cc%.mk,$(SRCS3))
#=====================================================

build: $(buildir)$(prog_name)
.PHONY: build


install: FILE = $(DESTDIR)$(bindir)$(prog_name)
install:
	@[ -f "$(FILE)" ] && { echo -e "\e[31mError\e[32m $$file exists Defualt behavior is not to overwrite...\e[0m Terminating..."; exit 24; } || true
	$(INSTALL_PROGRAM) $(buildir)$(prog_name) -t $(DESTDIR)$(bindir)
.PHONY:install

debug:
	@echo -e "\e[35mC++ Source Files \e[0m: $(SRCS)"
	@echo -e "\e[35mC++ Make Files   \e[0m: $(MKS)"
	@echo -e "\e[35mC++ Object Files \e[0m: $(OBJS)"
	@echo    "#-------------------------------------------#"
	@echo -e "\e[35mmakeflages;makegoals\e[0m:$(MAKEFLAGS) ; $(MAKECMDGOALS)"
.PHONY:debug

help:
	@echo "The follwing targets may be given..."
	@echo -e "\t...install"
	@echo -e "\t...build*"
	@echo -e "\t...uninstall"
	@echo -e "\t...clean"
	@echo "Other options"
	@echo -e "\t...debug"
	@echo -e "\t...help"
.PHONY:help

#=====================================================

$(buildir)$(prog_name): $(OBJS)
ifndef SHARED
	$(CXX) $(CXXFLAGS) -o $@ $(CXXINCLUDES) $(OBJS) $(CXXLIBS)
else
	$(CXX) $(filter-out -pic -fpic -Fpic,$(CXXFLAGS)) -o $@ $(CXXINCLUDES) -Wl,-rpath="$(RPATH)" $(OBJS) $(CXXLIBS)
endif

$(buildir)pp%.mk : $(srcdir)%.cpp
	@mkdir -p $(@D)
ifndef SHARED
	@$(CC) -M $< -MQ $(buildir)cpp$*.o | awk '{ print $$0 } END { printf("\t$$(CXX) $$(CXXFLAGS) -c -o $(buildir)cpp$*.o $<")}' > $@
else
	@$(CC) -M $< -MQ $(buildir)cpp$*.o | awk '{ print $$0 } END { printf("\t$$(CXX) $$(filter-out -pie -fpie -Fpie -pic -fpic -Fpic,$$(CXXFLAGS)) -c -o $(buildir)cpp$*.o $<")}' > $@
endif
	@echo -e "\e[32mCreating Makefile \"$@\"\e[0m..."

$(buildir)xx%.mk : $(srcdir)%.cxx
	@mkdir -p $(@D)
ifndef SHARED
	@$(CC) -M $< -MQ $(buildir)cxx$*.o | awk '{ print $$0 } END { printf("\t$$(CXX) $$(CXXFLAGS) -c -o $(buildir)cxx$*.o $<")}' > $@
else
	@$(CC) -M $< -MQ $(buildir)cxx$*.o | awk '{ print $$0 } END { printf("\t$$(CXX) $$(filter-out -pie -fpie -Fpie -pic -fpic -Fpic,$$(CXXFLAGS)) -c -o $(buildir)cxx$*.o $<")}' > $@
endif
	@echo -e "\e[32mCreating Makefile \"$@\"\e[0m..."


$(buildir)cc%.mk : $(srcdir)%.cc
	@mkdir -p $(@D)
ifndef SHARED
	@$(CC) -M $< -MQ $(buildir)cc$*.o | awk '{ print $$0 } END { printf("\t$$(CXX) $$(CXXFLAGS) -c -o $(buildir)cc$*.o $<")}' > $@
else
	@$(CC) -M $< -MQ $(buildir)cc$*.o | awk '{ print $$0 } END { printf("\t$$(CXX) $$(filter-out -pie -fpie -Fpie -pic -fpic -Fpic,$$(CXXFLAGS)) -c -o $(buildir)cc$*.o $<")}' > $@
endif
	@echo -e "\e[32mCreating Makefile \"$@\"\e[0m..."

override build_targets = install build $(buildir)$(prog_name) $(OBJS)
ifneq ($(strip $(filter $(build_targets),$(MAKECMDGOALS))),)
include $(MKS)
else ifeq ($(MAKECMDGOALS),)
include $(MKS)
endif

#=====================================================

clean:
	rm -rf $(buildir)
.PHONY:clean

uninstall: FILE = $(DESTDIR)$(bindir)$(prog_name)
uninstall:
	rm -f $(FILE)
.PHONY:uninstall
