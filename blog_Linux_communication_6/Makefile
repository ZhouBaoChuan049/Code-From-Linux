OBJECT_1 = Server
OBJECT_2 = Client
SOURCE_1 = Server.cc
SOURCE_2 = Client.cc

ALL : $(OBJECT_1) $(OBJECT_2)
OBJECT_1 : $(SOURCE_1)
	g++ -o $@ $^
OBJECT_2 : $(SOURCE_2)
	g++ -o $@ $^
.PHONY: clean
clean : 
	rm -f $(OBJECT_1) $(OBJECT_2) fifo
