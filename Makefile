
all:
	gcc -g -Wall -Wextra --std=c99 -I/opt/nvidia/cuda/include hello.c -lOpenCL
