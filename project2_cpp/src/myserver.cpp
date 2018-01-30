#include <iostream>
#include <memory.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h> //seems included in arpa/inet.h? not sure
#include <thread>

#include "myserver.h"
#include "response.h"

using namespace std;

MyServer::MyServer(char *port){
   	//create server socket
   	serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

   	//bind socket with port
   	sockaddr_in serv_addr;
   	memset(&serv_addr, 0, sizeof(serv_addr));//set all char to 0, not a must in this simple example
   	serv_addr.sin_family = AF_INET;
   	//serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//bind to port but no ip
   	serv_addr.sin_port = htons(stoi(port));
   	bind(serv_sock, (sockaddr*)&serv_addr, sizeof(serv_addr));

   	//set listen, default:20 in queue
   	listen(serv_sock, 20);

}

MyServer::~MyServer(){

	close(serv_sock);
}

void MyServer::run(){
	while(1){
	    //create a client sock for receiving msg
	    sockaddr_in clnt_addr;
	    socklen_t clnt_addr_size = sizeof(clnt_addr);
	    //3rd parameter in accept() is (socklen_t *), so we define it seperately
	    int clnt_sock = accept(serv_sock, (sockaddr*)&clnt_addr, &clnt_addr_size);

	    //open a thread to process request
	    thread t(run_thread, clnt_sock);
	    t.detach();
	}
}


//process a single request from client
void MyServer::run_thread(int clnt_sock){
    //receive
    char buf[512];
    while(recv(clnt_sock, buf, sizeof(buf)-1, 0) == -1){
       ;
    }
    //cout<<"Message received from client:"<<endl
    //    <<buf<<endl<<endl;

    //response to client
    Response r(clnt_sock, buf);
    r.run();
    
    //close client sock
    close(clnt_sock);
}
