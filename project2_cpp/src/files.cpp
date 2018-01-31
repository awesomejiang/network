#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <experimental/filesystem>

#include "files.h"

using namespace std;
namespace fs = std::experimental::filesystem;

Files::Files(){
	//load redirect.defs
	fstream file("www/redirect.defs");

	string line, origin, redirect;
	while(getline(file, line)){
		stringstream ss;
		ss << line;
		ss >> origin >> redirect;

		redirect_map[origin] = redirect;
	}

	file.close();

}


int Files::exist(string str){
	fs::path p = "www"+str;
	//process redirect.defs as special case
	if(fs::exists(p) && !fs::is_directory(p) && str != "redirect.defs"){
		return 1;
	}
	else{
		return 0;
	}
}

int Files::redirected(string str){

	return redirect_map.find(str) != redirect_map.end();
}

string Files::mime(string str){
	if(redirected(str)){
		return redirect_map[str] + "\r\n";
	}
	else{
		fstream file("www"+str);
		stringstream ss;
		ss << file.rdbuf();

		file.close();
		return ss.str() + "\r\n";
	}
}