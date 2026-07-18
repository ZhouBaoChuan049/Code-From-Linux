TARGET_1 = Client
TARGET_2 = Server
ALL : $(TARGET_1) $(TARGET_2)
$(TARGET_1) : Client.cpp
	g++ -o $@ $^
$(TARGET_2) : Server.cpp
	g++ -o $@ $^
