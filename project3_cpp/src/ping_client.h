#include <iostream>
#include <string>
#include <memory.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h> //seems included in arpa/inet.h? not sure
#include <thread>
#include <mutex>
#include <chrono>
#include <thread>
#include <future>

using namespace std;

long now(){
	return chrono::duration_cast<chrono::milliseconds>(
	chrono::system_clock::now().time_since_epoch()).count();
}

class Client{
public:
	Client(string ip, int port, int timeout)
		: ip(ip), port(port), timeout(timeout/1000){}


	vector<int> run(int count, int period){
		vector<future<int>> future_res(count);
		for(auto iter = future_res.begin(); iter != future_res.end(); iter++){
			//this_thread::sleep_for(1s);
			int pos = iter - future_res.begin();
			future_res[pos] = async(launch::async, &Client::send_msg, this, pos+1);
			if(iter != future_res.end()-1){ //sleep a while except for the last element
				this_thread::sleep_for(chrono::milliseconds(period));
			}
		}

		vector<int> res;
		for_each(future_res.begin(), future_res.end(), 
			[&res](auto &f){
				auto tmp = f.get();
				if(tmp > 0){
					res.push_back(tmp);
				}
			}
		);

		return res;
	}


private:
	string ip;
	int port;
	int timeout;

	mutex m;

	int send_msg(int seq_num){
		//fill in server info
		sockaddr_in serv_addr;
		memset(&serv_addr, 0 ,sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr. sin_port = htons(port);
	    socklen_t addr_size = sizeof(serv_addr);

		//create a socket and set timeout
		int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, addr_size);

		//send msg
		long time_begin = now();
		string text = "PING\t" + to_string(seq_num) + "\t" + to_string(time_begin) + "\r\n";
		int tmp = sendto(sock, text.c_str(), text.size(), 0, (sockaddr*)&serv_addr, addr_size);

		//receive response
		char recv_msg[256];
		int recv_len = recvfrom(sock, recv_msg, 256, 0, (sockaddr*)&serv_addr, &addr_size);

		int elapsed_time;
		if(recv_len > 0){	//if timeout not reaches
			elapsed_time = now()-time_begin;
			//lock
			lock_guard<mutex> lock(m);
			cout<<"PONG\t" + ip + ":\tseq=" + to_string(seq_num)
				+ "\ttime=" + to_string(elapsed_time) + "ms" <<endl;
		}
		else{
			elapsed_time = -1;
		}

		//shutdown(sock, 2);
		return elapsed_time;
	}
};
