# Makfile

SRC = hello.c
OBJ = $(SRC:.c=.o)
EXE = hello
JUNK = $(OBJ)
INCLUDE = -I/opt/nvidia/cuda/include
LIB = -lOpenCL
FLAGS = -g -Wall -Wextra --std=c99
GCC = gcc

all: $(EXE)

$(EXE): $(OBJ)
	$(GCC) $(FLAGS) $(INCLUDE) -o $@ $^ $(LIB)

%.o: %.c
	$(GCC) $(FLAGS) $(INCLUDE) -c $^

clean:
	rm $(JUNK)

spotless: clean
	rm $(EXE)
	
