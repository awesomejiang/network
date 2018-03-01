#include <iostream>
#include <getopt.h>
#include <string>
#include <vector>
#include <algorithm>

#include "ping_client.h"


using namespace std;

void usage(char* program){
	cout<< "Here is the usage function." <<endl;
	cout<< "Usage: python " << program << " [options]" <<endl;
	cout<< "[options]:" <<endl;
	cout<< "-h/--help:                       call usage function" <<endl;
	cout<< "--server_ip=<server ip addr>:    default: hostname" <<endl;
	cout<< "--server_port=<server port>:     default: 8080" <<endl;
	cout<< "--count=<number of pings>:       default: 10" <<endl;
	cout<< "--period=<wait interval>:        default: 1000(ms)" <<endl;
	cout<< "--timeout=<timeout>:             default: 10000(ms)" <<endl;
}


void get_args(int argc, char **argv, string &ip, int &port, int &count, int &period, int &timeout){
    const struct option longopts[] ={
    	{"help",	0,	0,	'h'},	
    	{"server_ip",	2,	0,	1000},
    	{"server_port",	2,	0,	1001},
    	{"count",	2,	0,	1002},
    	{"period",	2,	0,	1003},
    	{"timeout",	2,	0,	1004},
    	{0,	2,	0,	0}
    };

    int iarg = 0, index = 0;
    while(iarg != -1){
    	iarg = getopt_long(argc, argv, "h", longopts, &index);
    	switch(iarg){
    		case 1000:
    			ip = string(optarg);
    			break;
    		case 1001:
    			port = atoi(optarg);
    			break;
    		case 1002:
    			count = atoi(optarg);
    			break;
    		case 1003:
    			period = atoi(optarg);
    			break;
    		case 1004:
    			timeout = atoi(optarg);
    			break;
    		case 'h':
    			usage(argv[0]);
    			exit(1);
    		case '?':
    			usage(argv[0]);
    			exit(1);
    	}
    }
}


void print_stats(string ip, int count, long time_begin, vector<int>& times){
	cout<< "\n--- " + ip + " ping statistics ---" <<endl;
	cout<< count << " transmitted, "
			<< times.size() << " received, "
			<< ((count>0)?to_string((count-times.size())*100/count):string("-"))
			<< "% loss, time " << now()-time_begin << " ms" <<endl;
	cout<< "rtt min/avg/max = ";
	if(times.size()>0){
		cout<< *min_element(times.begin(), times.end()) <<"/"
			<< accumulate(times.begin(), times.end(), 0)/times.size() <<"/"
			<< *max_element(times.begin(), times.end()) <<endl;
	}
	else{
		cout<<"0/0/0"<<endl;
	}
}

int main(int argc, char** argv){
	//set arguments
	string ip = "hostname";
	int port = 8080;
	int count = 10;
	int period = 1000;
	int timeout = 10000;
	get_args(argc, argv, ip, port, count, period, timeout);

	//create client object and run main function
	Client c(ip, port, timeout);

	long time_begin = now();
	cout<< "PING\t" + ip << endl;
	vector<int> res = c.run(count, period);

	//print stats
	print_stats(ip, count, time_begin, res);


	return 0;
}