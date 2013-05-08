# SOURCE ###############################################################
SRC := main.c
OBJ := $(patsubst %.c,%.o,$(SRC))
LIB := getopt.c
BIN := ep2

# PROGRAMS #############################################################
AR := ar
CC := gcc
RM := rm -f

# COMPILER #############################################################
CLIBS   := -I. 
CFLAGS  := -ansi -Wall -pedantic -g -pg

# LIBRARIES ############################################################
LIBS    := $(patsubst %.c,lib%.a,$(LIB))
ARFLAGS := -rcv

# LINKER ###############################################################
LDLIBS  := -L.
LDFLAGS := -lm $(patsubst lib%.a,-l%,$(LIBS)) -lc -pg

# BUILD ################################################################
$(BIN): $(OBJ) | $(LIBS)
	$(CC) $^ -o $@ $(LDLIBS) $(LDFLAGS)

lib%.a: %.o 
	$(AR) $(ARFLAGS) $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# OTHER OPTIONS ########################################################
.PHONY: clean
clean:
	$(RM) *.o *~ gmon.out
