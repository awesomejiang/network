#ifndef FILES_H
#define FILES_H

#include <string>
#include <map>
#include <vector>
#include <experimental/filesystem>

using namespace std;


class Files{
public:
	Files();
	
	int exist(string);
	int redirected(string);
	string mime(string);

private:
	map<string, string> redirect_map;

};

#endif