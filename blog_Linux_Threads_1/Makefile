BIN = proc
SRC = TestThread.cpp
$(BIN) : $(SRC)
	g++ -o $@ $^ -pthread
.PHONY:
clean :
	rm -f $(BIN)