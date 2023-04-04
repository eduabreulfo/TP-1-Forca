CC = gcc
CFLAGS = -Wall

SRCDIR = src
OBJDIR = obj
INCDIR = headers

SRCS = main.c $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
HEADERS = $(wildcard $(INCDIR)/*.h)

TARGET = main

RM = rm -f

all: $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c -o $@ $< $(FLAGS)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	$(RM) $(OBJS) $(TARGET)

run: 
	./$(TARGET)