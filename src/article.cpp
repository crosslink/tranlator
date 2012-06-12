/*
 * article.cpp
 *
 *  Created on: Apr 24, 2012
 *      Author: monfee
 */

#include "article.h"
#include "sys_file.h"
#include "database_mysql.h"
#include "translation_write_exception.h"

#include <utility>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;


article::article() {
	init();
}

article::article(const char *file) : file_path(file) {
	init();
}

article::~article() {
	if (content != NULL)
		delete [] content;
}

void article::write(const char* this_content, int write_type) {
	cerr << this_content << endl;
	write(this_content, file_path.c_str(), write_type);
}

void article::init() {
	content = NULL;
	doc_id = -1;
}

bool article::read() {
//	char *bytes = sys_file::read_entire_file(file_path.c_str());
//	content = string(bytes);
	bool result = false;
	if (sys_file::exist(file_path.c_str())) {
		content = sys_file::read_entire_file(file_path.c_str());

		if (content == NULL)
			cerr << "Error: reading file " << file_path << endl;
		else
			result = true;
	}
//	delete [] bytes;
	return result;
}

void article::write() {
	write(content, file_path.c_str(), WRITE_TO_DISK);
}

std::string article::id2dir(unsigned long id) {
	long last3 = id >= 1000 ? (id - (id /1000) * 1000) : id;
	std::ostringstream stm;
	stm << std::setw(3) << std::setfill('0') << last3 << sys_file::SEPARATOR /*<< id*/;
	return stm.str();
}

void article::write(const char* this_content) {
//	cerr << this_content << endl;
	write(this_content, file_path.c_str(), WRITE_TO_DISK);
}

void article::write(const char* this_content, const char *path, int write_type) {
	if (database_mysql::instance().is_connected()) {
		database_mysql::instance().finish(doc_id, source_lang.c_str());

		if (write_type & WRITE_TO_DATABASE) {
	//		try {
				database_mysql::instance().update_translation(doc_id, this_content, target_lang.c_str(), source_lang.c_str());

	//		}
	//		catch (translation_write_exception& e) {
	//
	//		}
		}
	}

	if (write_type & WRITE_TO_DISK) {
		try {
			sys_file::write(this_content, file_path.c_str());
		}
		catch (exception& e) {
			cerr << e.what() << endl;
			translation_write_exception ex(translation_write_exception::WRITE_FILE_ERROR);
			throw ex;
		}
	}

}

void article::write(int write_type) {
	write(content, file_path.c_str(), write_type);
}

long article::get_doc_id()
{
    return doc_id;
}

void article::set_doc_id(long  id)
{
    doc_id = id;
}

std::string article::get_source_lang() const {
	return source_lang;
}

void article::set_source_lang(std::string source_lang) {
	this->source_lang = source_lang;
}

std::string article::get_target_lang() const {
	return target_lang;
}

void article::set_target_lang(std::string target_lang) {
	this->target_lang = target_lang;
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






