BIN = proc
SRC = Main.cpp
$(BIN) : $(SRC)
	g++ -o $@ $^ -pthread -std=c++17
.PHONY:
clean :
	rm -f $(BIN) ./log/log.txt