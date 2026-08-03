BIN = proc
SRC = TestMutex.cpp
$(BIN) : $(SRC)
	g++ -o $@ $^ -pthread
.PHONY:
clean :
	rm -f $(BIN)