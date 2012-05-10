/*
 * input_manager.cpp
 *
 *  Created on: Apr 23, 2012
 *      Author: monfee
 */

#include "input_manager.h"
#include "corpus.h"
#include "article_reader.h"
#include "article_writer.h"
#include "database_mysql.h"
//#include "string_utils.h"

#include <string.h>

#include <string>
#include <iostream>

using namespace std;


std::string input_manager::out_path;

inline char *remove_redundant_spaces(const char *from, std::string& to, long limit) {
	const char *ch = from;
	to.clear();
	while (*ch != '\0') {
		while (*ch != '\0' && *ch == ' ')
			++ch;

		if (ch - from > limit)
			return ch;

		while (*ch != '\0' && *ch != ' ')
			to.push_back(*ch++);

		// it is space
		if (*ch != '\0')
			to.push_back(*ch++);
//		if (isspace(*ch))
	}
	return ch;
}

input_manager::input_manager() : translator(google_research_translator::get_instance()) {
	init();
}

input_manager::input_manager(std::string lang_pair) : language_pair(lang_pair), translator(google_research_translator::get_instance())  {
	//google_research_translator& translator = google_research_translator::get_instance();
	init();
}

input_manager::~input_manager() {

}

void input_manager::set_out_path(std::string path) {
	out_path = path;
	article_writer::initialize_output_corpus(out_path.c_str());
}

std::string& input_manager::get_out_path() {
	return out_path;
}

void input_manager::translate_file(const char *file) {
	article_reader reader(file);
	article_writer writer(file);
//		reader.copy_to_next_token(writer);

	reader.read();

	token_string *source = reader.get_next_token(writer);
	while (source->length > 0) {

//			reader.copy_to_next_token(writer);
		char *source_string = new char [source->length + 1];
		memcpy(source_string, source->start, source->length);
		source_string[source->length] = '\0';
//				string source_str(source->start, source->length);
#ifdef DEBUG
		std::string shorted;
		remove_redundant_spaces(source_string, shorted);
		cerr << source->tag << ": " << shorted << endl;
#endif
#if ENABLE_TRANSLATOR == 1
//				string trans = string();
		const char *trans = translator.translate(shorted.c_str());
		if (trans == NULL) {

//					exit(-1);
			break;
		}
		writer.fill(trans);
#ifdef DEBUG
			cerr << source->tag << " (Translation): " << trans << endl;
#endif
#endif
		delete [] source_string;
		source = reader.get_next_token();
	}
	writer.write();
}

void input_manager::load_from_disk() {
	const char *file = disk->first();
	try {
		while (file != NULL && strlen(file) > 0) {
			translate_file(file);
			file = disk->next();
		}
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
}

void input_manager::load_from_database() {
	std::vector<long> container;
	database_mysql::instance().fill(container);

	for (int i = 0; i < container.size(); ++i) {
		long id = container[i];
		string file = in_corpus.id2docpath(id);
		translate_file(file.c_str());
	}
}

void input_manager::set_read_type(int type) {
	read_type = type;
}

void input_manager::init() {
	read_type = READ_FROM_DISK;
	disk = NULL;
	set_out_path(".");
}

void input_manager::cleanup() {
	if (disk != NULL)
		delete disk;
}

void input_manager::set_language_pair(const char *language_pair) {
	this->language_pair = language_pair;
}

void input_manager::load(const char* filename) {
	if (read_type == READ_FROM_DISK) {
		disk = new sys_files();
		disk->pattern("*.[xX][mM][lL]");
		disk->list(filename);
		if (disk->isdir(filename)) {
			in_corpus.base(filename);
		}
	}
	else if (read_type == READ_FROM_DATABASE) {
		database_mysql::instance().connect();
		in_corpus.home(filename);
	}

//	const char *name = NULL;
//
//	for (name = disk->first(); name != NULL ; name = disk->next())
//	{
}

void input_manager::translate() {
#if ENABLE_TRANSLATOR == 1
	translator.set_lang_pair(language_pair.c_str());
#endif
	if (read_type == READ_FROM_DISK)
		load_from_disk();
	else if (read_type == READ_FROM_DATABASE)
		load_from_database();
	else
		cerr << "No input is specified!" << endl;
}








