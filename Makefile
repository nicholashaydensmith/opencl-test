# Makfile

CSRC = Context.c ContextManager.c Device.c Platform.c hello.c
HSRC = Context.h ContextManager.h Device.h MemoryManager.h  Platform.h Queue.h Util.h
COBJ = $(CSRC:.c=.o)
EXE = hello
JUNK = $(COBJ)
INCLUDE = -I/opt/nvidia/cuda/include
LIB = -lOpenCL
FLAGS = -g -Wall -Wextra --std=c99
GCC = gcc

all: $(EXE)

$(EXE): $(COBJ)
	$(GCC) $(FLAGS) $(INCLUDE) -o $@ $^ $(LIB)

%.o: %.c
	$(GCC) $(FLAGS) $(INCLUDE) -c $^

clean:
	rm $(JUNK)

spotless: clean
	rm $(EXE)
	
