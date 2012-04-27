/*
 * article.cpp
 *
 *  Created on: Apr 24, 2012
 *      Author: monfee
 */

#include "article.h"
#include "sys_file.h"

#include <utility>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;


article::article() {
}

article::article(const char *file) : file_path(file) {
	content = NULL;
}

article::~article() {
	if (content != NULL)
		delete [] content;
}

void article::read() {
//	char *bytes = sys_file::read_entire_file(file_path.c_str());
//	content = string(bytes);
	content = sys_file::read_entire_file(file_path.c_str());
//	delete [] bytes;
}

void article::write() {
	sys_file::write(content, file_path.c_str());
}

std::string article::id2dir(unsigned long id) {
	long last3 = id >= 1000 ? (id - (id /1000) * 1000) : id;
	std::ostringstream stm;
	stm << std::setw(3) << std::setfill('0') << last3 << sys_file::SEPARATOR << id;
	return stm.str();
}

int article::file2id(const char* file) {
	string sname(file);
	//string::size_type pos = name ;
//	string part(sname, base_.size());
	string::size_type pos;
	pos = sname.find(sys_file::SEPARATOR);
	if (pos != string::npos)
		sname.erase(0, pos);
	pos = sname.find('.');
	if (pos != string::npos)
		sname.erase(pos);
	return atoi(sname.c_str());
}




