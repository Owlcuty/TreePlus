CC = gcc
CSAN = -Wall -Wextra
CO = -o
MAIN = main.c
OFILES = main.o
LINKS = tree.c
LFLAGS =
all:
	$(CC) $(CSAN) $(CO) $(OFILES) $(MAIN) $(LINKS) $(LFLAGS)
