#include <iostream>
#include <string>
#include <memory.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h> //seems included in arpa/inet.h? not sure
#include <thread>

using namespace std;

//process a single message from client
void process_thread(int clnt_sock){
    //receive
    char buf[512];
    while(recv(clnt_sock, buf, sizeof(buf)-1, 0) == -1){
       ;
    }
    cout<<"Message received from client:"<<endl;
    cout<<buf<<endl<<endl;

    //echo back
    send(clnt_sock, buf, sizeof(buf), 0);

    //close client sock
    close(clnt_sock);
}

int main(int argc, char** argv){
   	//create server socket
   	int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

   	//bind socket with port
   	sockaddr_in serv_addr;
   	memset(&serv_addr, 0, sizeof(serv_addr));//set all char to 0, not a must in this simple example
   	serv_addr.sin_family = AF_INET;
   	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//localhost
   	serv_addr.sin_port = htons(stoi(argv[1]));
   	bind(serv_sock, (sockaddr*)&serv_addr, sizeof(serv_addr));

   	//set listen, default:20 in queue
   	listen(serv_sock, 20);

   	//main loop
   	while(1){
        //create a client sock for receiving msg
        sockaddr_in clnt_addr;
        socklen_t clnt_addr_size = sizeof(clnt_addr);
        //3rd parameter in accept() is (socklen_t *), so we define it seperately
        int clnt_sock = accept(serv_sock, (sockaddr*)&clnt_addr, &clnt_addr_size);

        thread t(process_thread, clnt_sock);
        t.detach();
   	}

   	//close server
   	close(serv_sock);

   	return 0;
}