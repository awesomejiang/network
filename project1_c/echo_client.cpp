#include <iostream>
#include <string>
#include <memory.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

int main(int argc, char** argv){
	while(1){
		//create socket
		int sock = socket(AF_INET, SOCK_STREAM, 0);

		//init server sock address
		sockaddr_in serv_addr;
		memset(&serv_addr, 0, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
		serv_addr.sin_port = htons(stoi(argv[2]));

		//connect to server
		connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr));

		//send msg to server
		char buf[512];
		strcpy(buf, "test");
		cout<<"Please input the message you want to send:"<<endl;
		cin.getline(buf, sizeof(buf));
		send(sock, buf, sizeof(buf), 0);

		//receive echo from server
		recv(sock, buf, sizeof(buf)-1, 0);
		cout<<"Echo received from server:"<<endl;
		cout<<buf<<endl<<endl;

		//close socket
		close(sock);
	}

	return 0;
}