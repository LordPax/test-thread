CC=gcc
LIBS=-lpthread
FLAGS=-W -Wall -ansi -std=c11
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
EXEC=test

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $^ -o $@ $(LIBS)

%.o : %.c
	$(CC) -c $< -o $@ $(FLAGS)

clean :
	rm -rf src/*.o

mrproper : clean
	rm -rf $(EXEC)

# $@ ref cible
# $< ref premiere dependance
# $^ ref listes dependances

# main.o : main.cpp
# 	$(CC) -c main.cpp
