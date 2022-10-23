CC = gcc

BINDIR = bin
INCLUDE = include
SRCDIR = src
OBJDIR = obj

CFLAGS = -Wall -I$(INCLUDE) 

# SRCDIR内のファイルをリストアップ
SRC = $(wildcard $(SRCDIR)/*.c)  
# SRCにあるsrc/*.c を obj/*.oに置き換える
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

TARGET = $(BINDIR)/paintapp

$(TARGET): $(OBJ) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BINDIR):
	mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

.PHONY: tmpclean clean

tmpclean:
	rm -f $(SRCDIR)/*~ $(INCLUDE)/*~

clean: tmpclean
	@$(RM) -rv $(BINDIR) $(OBJDIR)