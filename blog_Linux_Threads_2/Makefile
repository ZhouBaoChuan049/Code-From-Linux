BIN = proc
SRC = TestMyThread.cpp
$(BIN) : $(SRC)
	g++ -o $@ $^ -pthread
.PHONY:
clean :
	rm -f $(BIN)