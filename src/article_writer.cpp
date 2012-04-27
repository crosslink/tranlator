/*
 * article_writer.cpp
 *
 *  Created on: Apr 24, 2012
 *      Author: monfee
 */

#include "article_writer.h"
#include "input_manager.h"

#include <string>

using namespace std;

corpus article_writer::out;

article_writer::article_writer(const char *file) {
	create_output_file(file);
}

void article_writer::create_output_file(const char* file) {
	int id = file2id(file);
//	string id_str = id2dir(id);

	file_path = out.id2docpath(id);
}

article_writer::~article_writer() {

}

void article_writer::fill(std::string more) {
	out_content.append(more);
}

void article_writer::fill(const char* more, size_t length) {
	if (length > -1)
		out_content.append(more, length);
	else
		out_content.append(more);
}

void article_writer::initialize_output_corpus() {
	out.base(input_manager::get_out_path());

}


