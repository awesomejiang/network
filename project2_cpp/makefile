all: out files response myserver main

out:
	mkdir out

files: src/files.h | out
	g++ src/files.cpp -c -o out/files.o -std=c++17

response: src/response.h out/files.o | out
	g++ src/response.cpp -c -o out/response.o -std=c++17

myserver: src/myserver.h out/response.o | out
	g++ src/myserver.cpp -c -o out/myserver.o -std=c++17

main: out/myserver.o src/main.cpp | out
	g++ out/files.o out/response.o out/myserver.o src/main.cpp -o http_server -std=c++17 -pthread -lstdc++fs

clean:
	rm -f -r out/ http_server