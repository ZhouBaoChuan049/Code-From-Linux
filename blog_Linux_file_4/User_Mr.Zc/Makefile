BIN = proc
SRC = usercode.cpp
$(BIN) : $(SRC)
	g++ -o $@ $^ -I ./lib/include -L ./lib/mylib -l myc
.PHONY: clean
clean :
	rm -f $(BIN)
