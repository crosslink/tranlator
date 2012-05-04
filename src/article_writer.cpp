/*
 * article_writer.cpp
 *
 *  Created on: Apr 24, 2012
 *      Author: monfee
 */

#include "article_writer.h"
#include "input_manager.h"

#include <string>
#include <ctype.h>

#include "string_utils.h"

using namespace std;

corpus article_writer::out;

article_writer::article_writer(const char *file) : article() {
	create_output_file(file);
}

void article_writer::write() {
	article::write(out_content.c_str());
}

void article_writer::create_output_file(const char* file) {
	name = file2name(file);
	if (name.length() > 0 && isdigit(name[0])) {

		int id = atoi(name.c_str());
	//	string id_str = id2dir(id);
		string parent_path = out.docpath() + id2dir(id);
		if (!sys_file::exist(parent_path.c_str()))
			sys_file::mkdir_p(parent_path.c_str());

		file_path = parent_path + number_to_string(id) + "." + ext;
	}
	else {
		file_path = out.home() + name + "." + ext;
	}
}

article_writer::~article_writer() {

}

void article_writer::fill(std::string more) {
	out_content.append(more);
}

void article_writer::fill(const char* more, size_t length) {
	if ((long)length > -1)
		out_content.append(more, length);
	else
		out_content.append(more);
}

void article_writer::initialize_output_corpus() {
	out.home(input_manager::get_out_path() + sys_file::SEPARATOR);

}

void article_writer::initialize_output_corpus(const char* out_path) {
	out.home(out_path + string(sys_file::SEPARATOR));
}



