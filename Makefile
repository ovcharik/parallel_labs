CC=g++
FL=-std=c++0x -fopenmp

SRC_DIR=src
BIN_DIR=bin

SRC=$(wildcard $(SRC_DIR)/*.cc)
BIN=$(SRC:$(SRC_DIR)%.cc=$(BIN_DIR)%)

all: compile

compile: $(BIN)

run: $(BIN)
	./run.sh


$(BIN): $(BIN_DIR)/%: $(SRC_DIR)/%.cc
	$(CC) $(FL) $< -o $@