#ifndef MYSERVER_H
#define MYSERVER_H

class MyServer{
public:
	MyServer(char *);
	~MyServer();

	void run();


private:
	int serv_sock;
	static void run_thread(int);

};

#endif