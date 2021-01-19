name=cssparser
WORKINGDIR=$(shell pwd)
DIRNAME=$(shell basename `pwd`)
HOSTCC=gcc
HOSTCXX=g++
OPTFLAGS=-O2 -fomit-frame-pointer
HOSTCFLAGS=$(OPTFLAGS)
HOSTLD=ld
HOSTLDFLAGS=
CFLAGS=$(HOSTCFLAGS) -funsigned-char
CC=$(HOSTCC)
EXTRA_CFLAGS=
LD=$(HOSTLD)
LDFLAGS=$(HOSTLDFLAGS)
STRIP_ARGS=-s -R .note -R .comment
STRIP=strip $(STRIP_ARGS)
RM=/bin/rm
CP=/bin/cp -PpR 
MV=/bin/mv
LN=/bin/ln

RELEASE_DIR=release

CSSPARSEROBJS= \
	cssparser/CSSUtils.o \
	cssparser/CSSParser.o \
    cssparser/CSSProperties.o \
	cssparser/main.o

.cpp.o:
	$(CXX) -o $(RELEASE_DIR)/$@ -c $(CFLAGS) $<

.PHONY: clean cssparser

all: releasedir $(CSSPARSEROBJS) cssparser

cssparser:
	cd $(RELEASE_DIR); $(CXX) $(LDCFLAGS) -o $(name)/$(name) $(CSSPARSEROBJS)

releasedir:
	mkdir -p $(RELEASE_DIR)/$(name)

clean::
	$(RM) -rf $(RELEASE_DIR)
 
