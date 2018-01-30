#include <iostream>

#include "myserver.h"

using namespace std;

int main(int argc, char** argv){
	//create and ***start*** a server
	MyServer server(argv[1]);
   	cout<<"Http server is open now!"<<endl;

	server.run();

	return 0;

}