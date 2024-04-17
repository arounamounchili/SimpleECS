CC = g++
COMPILER_FLAGS = -Wall -Wfatal-errors
LANG_STD = -std=c++17
SRC_FILES = ../src/*.cpp
OBJ_NAME = example

default: build run clean

build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(SRC_FILES) -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)

clean: 
	rm $(OBJ_NAME)