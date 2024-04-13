CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
EXEC = $(BINDIR)/program

all: $(EXEC)

$(EXEC): $(OBJS) | $(BINDIR)
    $(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
    $(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
    mkdir -p $(OBJDIR)

$(BINDIR):
    mkdir -p $(BINDIR)

clean:
    rm -rf $(OBJDIR) $(BINDIR)
