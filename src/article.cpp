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
	content = NULL;
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
	stm << std::setw(3) << std::setfill('0') << last3 << sys_file::SEPARATOR /*<< id*/;
	return stm.str();
}

void article::write(const char* this_content) {
	sys_file::write(this_content, file_path.c_str());
}

std::string article::file2name(const char* file) {
	string sname(file);
	//string::size_type pos = name ;
//	string part(sname, base_.size());
	string::size_type pos;
	pos = sname.find_last_of(sys_file::SEPARATOR);
	if (pos != string::npos)
		sname.erase(0, pos + 1);
	pos = sname.find('.');
	ext = sname.substr(pos + 1);
	if (pos != string::npos)
		sname.erase(pos);
	return sname;
}

int article::file2id(const char* name) {
	return atoi(name);
}




