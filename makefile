# DIRECTORIES ##########################################################
SRCDIR := src
OBJDIR := obj
BINDIR := bin
LIBDIR := lib
CONFDIR := conf
VPATH = $(SRCDIR):$(LIBDIR):$(BINDIR) # : $(patsubst %.c,%:,$(shell ls src))

# SOURCE ###############################################################
SRC := $(shell ls $(SRCDIR))
OBJ := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
LIB := $(CONFDIR)/libraries.mk
DEP := $(CONFDIR)/dependencies.mk
BIN := ep2

include $(LIB)

# PROGRAMS #############################################################
AR := ar
CC := gcc
RM := rm -f
SED := sed
CAT := cat
FIND := find -type d
MKDIR := mkdir -p

# COMPILER #############################################################
CLIBS  := $(patsubst %,-I%,$(shell find include -type d))
CFLAGS := -ansi -Wall -pedantic -g -pg

# LIBRARIES ############################################################
LIBS    := $(patsubst %.c,lib%.a,$(LIB))
ARFLAGS := -rcv

# LINKER ###############################################################
LDLIBS  := -L$(LIBDIR)
LDFLAGS := -lm $(patsubst lib%.a,-l%,$(LIBS)) -lc -pg

.PHONY: all
all: $(DEP) $(BIN)

.PHONY: clean
clean:
	$(RM) $(OBJDIR)/*.o *~ gmon.out
	rmdir

# DEPENDENCIES #########################################################
$(DEP): $(SRC) | $(LIBDIR)
	$(CC) $(SRCDIR)/* $(CLIBS) -MM $(LDLIBS) > $@
	$(SED) -e 's/\.o/\.c/' -e 's/: .*c /: /' -i $@
include $(DEP)

# GAME #################################################################
$(BIN): $(OBJ) | $(LIBS) $(BINDIR)
	$(CC) $^ -o $(BINDIR)/$@ $(LDLIBS) $(LDFLAGS)

$(OBJ): | $(OBJDIR)

# BUILD ################################################################
lib%.a: $(OBJDIR)/$(notdir %.o)
	$(AR) $(ARFLAGS) $(LIBDIR)/$@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(CLIBS) -c $< -o $@

# GENERATED DIR ########################################################
$(BINDIR):
	@ echo Criando diretório de binários "$@"
	$(MKDIR) $@

$(OBJDIR):
	@ echo Criando diretório de objetos "$@"
	-$(MKDIR) $@

$(LIBDIR):
	@ echo Criando diretório de objetos "$@"
	-$(MKDIR) $@
