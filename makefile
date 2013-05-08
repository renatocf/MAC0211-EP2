# SOURCE ###############################################################
SRC := statistical.c
OBJ := $(patsubst %.c,%.o,$(SRC))
LIB :=
BIN := ep2

# PROGRAMS #############################################################
CC := gcc
RM := rm -f
AR := ar

# COMPILER #############################################################
CLIBS   := -I. 
CFLAGS  := -ansi -Wall -pedantic -g -pg

# LIBRARIES ############################################################
LIBS    := $(patsubst %.c,lib%.a,$(LIB))
ARFLAGS := -rcv

# LINKER ###############################################################
LDLIBS  := $(patsubst lib%.a,-l%,$(LIBS))
LDFLAGS := -lm -lc -pg

# BUILD ################################################################
$(BIN): $(OBJ) | $(LIBS)
	$(CC) $^ -o $@ $(LDLIBS) $(LDFLAGS)

%.a: %.o 
	$(AR) $(ARFLAGS) $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# OTHER OPTIONS ########################################################
.PHONY: clean
clean:
	$(RM) *.o *~ gmon.out
