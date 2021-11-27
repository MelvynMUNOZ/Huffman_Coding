# Directories set up
INCLDIR =include
BINDIR  =bin
OBJDIR  =obj
SRCDIR  =src

# Executable name
TARGET	=$(BINDIR)/huffman

# Project set up, compiler flags and linker flags
CC      =gcc -fsanitize=address
CFLAGS  =-Wall -std=c17 -g -O3
LDFLAGS =-lm

# Files set up
SRC     =$(wildcard $(SRCDIR)/*.c)
INCL    =$(wildcard $(INCLDIR)/*.h)
OBJ     =$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Compile binary and object files and build target
all: $(TARGET)
	
$(TARGET): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CC) $(LFLAGS) $(OBJ) -o $@
	@echo "Linking completed !"

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled successfully !"


# Clean entire project directory
.PHONY: clean

clean:
	@rm -rf $(BINDIR) $(OBJDIR)
	@echo "Cleanup completed !"
