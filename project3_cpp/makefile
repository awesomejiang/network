all: server client

server: src/PingServer.java
	javac src/PingServer.java -d .

client: src/ping_client.cpp src/ping_client.h
	g++ src/ping_client.cpp -o ping_client -std=c++1z -pthread

clean:
	rm -f ping_client *.class