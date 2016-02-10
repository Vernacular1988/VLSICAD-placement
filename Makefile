# Copyright (c) 2003, 2004 ACM/SIGDA
#
# Written by Florian Krohm (fkrohm@us.ibm.com)
#
# This Makefile will compile all C (*.c) and C++ (*.C) sources in 
# this directory and link them into an executable specified by variable TARGET.
# In order not to have to model the exact dependencies on header files this
# Makefile assumes that all C/C++ files depend on all header files.
# Bison and flex input files, if any, are handled as expected.
#
# make debug   - compile and link to produce debuggable executable
# make opt     - compile and link to produce optimized executable
# make clean   - remove all generated files
# make test    - run all testcases
# make submit  - copy relevant files to solution directory
#
# You may change the value of SUBMIT_FILES to fit your needs
# You *must not* modify TARGET or SUBMIT_DIR.
#

TARGET = main

#
# Tools used
#
CC    = gcc
CXX   = g++
FLEX  = flex
BISON = bison
COMPARE_RESULT = diff

#
# Bison, Flex input if any 
# (Only one grammar/scanner spec at this point)
#
Y_FILE := $(wildcard *.y)
Y_SRCS := $(subst .y,.tab.c,$(Y_FILE))
Y_HDRS := $(subst .y,.tab.h,$(Y_FILE))
L_FILE := $(wildcard *.l)
L_SRCS := $(subst .l,.yy.c,$(L_FILE))
L_OBJS := $(subst .c,.o,$(L_SRCS))

#
# Assemble sources, objects, and headers
#
C_SRCS  := $(wildcard *.c)
C_SRCS  := $(subst $(L_SRCS),,$(C_SRCS))
C_SRCS  := $(subst $(Y_SRCS),,$(C_SRCS))
C_SRCS  += $(L_SRCS)
C_DOBJS := $(C_SRCS:.c=.o)
C_SRCS  += $(Y_SRCS)
C_OBJS  := $(C_SRCS:.c=.o)

CXX_SRCS  := $(wildcard *.C)
CXX_OBJS  := $(CXX_SRCS:.C=.o)

HDRS   := $(wildcard *.h)
HDRS   := $(subst $(Y_HDRS),,$(HDRS))
HDRS   += $(Y_HDRS)

# Choose suitable commandline flags 
#
ifeq "$(MAKECMDGOALS)" "opt"
CFLAGS   = -O2
CXXFLAGS = -O2
else
CFLAGS   = -g -W -Wall -pedantic -Wno-unused-parameter -DYYDEBUG
CXXFLAGS = -g -W -Wall -pedantic
endif

CFLAGS   +=  -I.
CXXFLAGS +=  -I.

.PHONY:	clean test debug opt submit

.SECONDARY: $(Y_SRCS) $(L_SRCS)

debug opt: $(TARGET)

$(TARGET):  $(C_OBJS) $(CXX_OBJS) 
	$(CXX) -o $(TARGET) $(C_OBJS) $(CXX_OBJS) -L$(HOME)/lib $(LIBS)


%.yy.c:%.l
	$(FLEX) -o$(notdir $*).yy.c $<

%.tab.c %.tab.h:%.y
	$(BISON) -d --output=$*.tab.c $<

%.o:%.c
	$(CC) -c $(CFLAGS) $<

%.o:%.C
	$(CXX) -c $(CXXFLAGS) $<

$(C_DOBJS) $(CXX_OBJS): $(HDRS)

#
# Flex generates code that causes harmless warnings; suppress those
#
$(L_OBJS): $(L_SRCS) $(HDRS)
	$(CC) -c $(CFLAGS) -Wno-unused-function -Wno-unused-label \
                 -Wno-implicit-function-declaration $<

test:	$(TARGET) 
	@for file in ./test*; \
	do \
          f=`basename $$file`; \
	  ./$(TARGET) $$file > /tmp/$$$$; \
	  $(COMPARE_RESULT) /tmp/$$$$ ./result.$$f > /dev/null; \
	  if [ $$? -eq 0 ]; then \
	    echo "$$f passed"; \
          else \
	    echo "$$f FAILED"; \
          fi; \
	  rm -f /tmp/$$$$; \
	done

clean : 
	rm -f *.o $(TARGET) $(Y_HDRS) $(Y_SRCS) $(L_SRCS)

submit:
	submit $(SUBMIT_DIR) $(SUBMIT_FILES)
