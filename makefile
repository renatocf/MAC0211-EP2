# DIRECTORIES ##########################################################
SRCDIR := src
OBJDIR := obj
BINDIR := bin
LIBDIR := lib
VPATH = $(SRCDIR):$(LIBDIR):$(BINDIR) # : $(patsubst %.c,%:,$(shell ls src))

# SOURCE ###############################################################
SRC := $(shell ls $(SRCDIR))
OBJ := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
LIB := getopt.c
DEP := dependencies.mk
BIN := ep2

# PROGRAMS #############################################################
AR := ar
CC := gcc
RM := rm -f
SED := sed
CAT := cat
MKDIR := mkdir -p

# COMPILER #############################################################
CLIBS  := -Iinclude $(patsubst %,-I%,$(shell find include -type d))
CFLAGS := -ansi -Wall -pedantic -g -pg

# LIBRARIES ############################################################
LIBS    := $(patsubst %.c,lib%.a,$(LIB))
ARFLAGS := -rcv

# LINKER ###############################################################
LDLIBS  := -L$(LIBDIR)
LDFLAGS := -lm $(patsubst lib%.a,-l%,$(LIBS)) -lc -pg

# BUILD ################################################################
$(BIN): $(OBJ) | $(DEP) $(LIBS) $(BINDIR)
	$(CC) $^ -o $(BINDIR)/$@ $(LDLIBS) $(LDFLAGS)

$(OBJ): $(OBJDIR)

lib%.a: %.o 
	$(AR) $(ARFLAGS) $(LIBDIR)/$@ $(OBJDIR)/$<

%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(CLIBS) -c $< -o $(OBJDIR)/$@

$(BINDIR):
	@ echo Criando diretório de binários "$(OBJDIR)"
	$(MKDIR) $@

$(OBJDIR):
	@ echo Criando diretório de objetos "$(OBJDIR)"
	-$(MKDIR) $@

# DEPENDENCIES #########################################################
$(DEP):
	@$(CC) $(SRCDIR)/* $(CLIBS) -MM $(LDLIBS) > $@
	@$(SED) -e 's/\.o/\.c/' -e 's/: .*c /: /' $@ | $(CAT) > $@
-include $(DEP)

# OTHER OPTIONS ########################################################
.PHONY: clean
clean:
	$(RM) $(OBJDIR)/*.o *~ gmon.out
