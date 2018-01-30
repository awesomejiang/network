#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <locale>
#include <sys/socket.h>
#include <sys/utsname.h>

#include "response.h"
#include "files.h"

using namespace std;

Response::Response(int in_clnt_sock, char* in_buf){
	clnt_sock = in_clnt_sock;
	buf = in_buf;

	//parse request message
	stringstream ss;
	ss << buf;
	ss >> method >> web >> protocol;

}

Files Response::f{};

void Response::run(){
	struct utsname sysinfo;
	uname(&sysinfo);
	content = build_headline()
			+ "Connection: close\r\n"
			+ build_date()
			+ "Server: " + sysinfo.sysname + "/" + sysinfo.release + "\r\n"
			+ build_content_type();

	if(f.redirected(web)){
		content += "Location: " + build_body();
	}

	if(method == "GET" && f.exist(web)){
		content += "\r\n" + build_body();
	}

	send(clnt_sock, content.data(), content.size(), 0);

}


string Response::build_headline(){
	string str = protocol + " ";
	if(method == "GET" || method == "HEAD"){
		if(f.exist(web)){//web exist
			str += "200 OK\r\n";
		}
		else{			
			if(f.redirected(web)){//redirect?
				str += "301 Moved Permanently\r\n";
			}
			else{
				str += "404 Not Found\r\n";
			}
		}
	}
	else{
		if(method == "POST" || method == "PUT" || method == "DELETE"
			|| method == "TRACE" || method == "CONNECT"){//other methods
			str += "405 Method Not Allowed\r\n";
		}
		else{//all other cases
			str += "400 Bad Request\r\n";
		}
	}

	return str;
}

string Response::build_date(){
	time_t t = time(nullptr);
	char s[512];
	if(strftime(s, sizeof(s), "%a, %d %b %Y %T %Z", localtime(&t))){
		return "Date: " + string(s) + "\r\n";
	}
	else{
		cout<<"Error in response_date(): Can not read system time."<<endl;
		exit(0);
		return "";
	}
}

string Response::build_content_type(){
	auto pos = web.find_last_of('.');
	auto str = web.substr(pos+1);
	
	if(str == "html"){
		str = "text/" + str;
	}
	else if(str == "txt"){
		str = "text/plain";
	}
	else if(str == "pdf"){
		str = "application/" + str;
	}
	else if(str == "png" || str == "jpeg"){
		str = "image/" + str;
	}
	else{
		str = "unknown";
	}
	return "Content-Type: " + str + "\r\n";
}

string Response::build_body(){

	return f.mime(web);
}