/*
 * article.cpp
 *
 *  Created on: Apr 24, 2012
 *      Author: monfee
 */

#include "article.h"
#include "sys_file.h"

using namespace std;

article::article(const char *file) : file_path(file) {
//	content = NULL;
}

article::~article() {
//	if (content != NULL)
}

void article::read() {
	char *bytes = sys_file::read_entire_file(file_path.c_str());
	content = string(bytes);
	delete [] bytes;
}

void article::write() {
	sys_file::write(content.c_str(), file_path.c_str());
}


