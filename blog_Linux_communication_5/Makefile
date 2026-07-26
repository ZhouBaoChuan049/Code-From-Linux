ALL : Mr_List Mr_Zhang
Mr_List : Mr_List.cpp
	g++ -o $@ $^
Mr_Zhang : Mr_Zhang.cpp
	g++ -o $@ $^
.PHONY : clean 
clean : 
	rm -f Mr_List Mr_Zhang fifo