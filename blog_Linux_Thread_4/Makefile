BIN = proc
SRC = TestMyMutex.cpp
$(BIN) : $(SRC)
	g++ -o $@ $^ -pthread
.PHONY:
clean :
	rm -f $(BIN)