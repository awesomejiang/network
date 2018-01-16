all: server client

server:
	g++ echo_server.cpp -o echo_server -std=c++11 -pthread

client:
	g++ echo_client.cpp -o echo_client -std=c++11

clean:
	find . -maxdepth 1 -type f -perm /111 -exec rm {} \;