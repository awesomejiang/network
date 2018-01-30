#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

#include "files.h"

using namespace std;

class Response{
public:
	Response(int, char*);
	void run();

private:
	int clnt_sock;
	char* buf;

	string method;
	string web;
	string protocol;

	static Files f;

	int body = 0;
	string content;


	string build_headline();
	string build_date();
	string build_content_type();
	string build_body();

};

#endif