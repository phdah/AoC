CC=clang++
CXX_FLAGS=-g -std=c++17 -O0

SRC=src
INCLUDE=include

BIN=main

.PHONY: clean test run

$(BIN): clean
	$(CC) $(CXX_FLAGS) $(SRC)/*.cpp -o $(BIN) -I$(INCLUDE)

run: $(BIN)
	./$(BIN) ./input.txt

clean:
	rm $(BIN) || echo "no main file"
	rm -r $(BIN).dSYM || echo "no dSYM"
