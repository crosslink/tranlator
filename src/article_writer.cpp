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
	content.append(more);
}

void article_writer::fill(const char* more, size_t length) {
	content.append(more, length);
}

void article_writer::initialize_output_corpus() {
	out = corpus(input_manager::get_out_path());
}


