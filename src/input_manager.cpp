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
#include "translation_write_exception.h"
#include "language.h"
//#include "string_utils.h"

#include <string.h>

#include <string>
#include <iostream>
#include <sstream>

using namespace std;


std::string input_manager::out_path;

const char *input_manager::remove_redundant_spaces(const char *from, std::string& to, long limit) {
	const char *ch = from;
	to.clear();
	while (*ch != '\0') {
		while (*ch != '\0' && *ch == ' ')
			++ch;

		if (limit > 0) {
			if (to.length() > limit)
				return ch;
		}

		while (*ch != '\0' && *ch != ' ') {
			if (language::is_cjk_punctuation(ch)) {
				long size = language::utf8_bytes(ch);
				to.append(ch, size);
				ch += size;
				break;
			}
			to.push_back(*ch++);
		}

		// it is space
		if (*ch != '\0')
			to.push_back(*ch++);
//		if (isspace(*ch))
	}
	return ch;
}

input_manager::input_manager() : translator(google_research_translator::get_instance()) {
	translator.initialize(google_translator::LOAD_KEY);
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

void input_manager::translate_file(const char *file, long id) {
	article_reader reader(file);
	article_writer writer(file);
	writer.set_source_lang(source_lang);
	writer.set_target_lang(target_lang);

//		reader.copy_to_next_token(writer);
	cerr << "processing doc of id (" << id << ")" << endl;

	long doc_id = id;

	if (doc_id == -1)
		doc_id = writer.get_doc_id();

	if (reader.read()) {

		token_string *source = reader.get_next_token(writer);
		bool error = false;
		while (source->length > 0) {
			error = false;
	//			reader.copy_to_next_token(writer);
			char *source_string = new char [source->length + 1];
			memcpy(source_string, source->start, source->length);
			const char *end = source_string;
			source_string[source->length] = '\0';
	//				string source_str(source->start, source->length);
//			while (isspace(*end)) {
//				++end;
//				writer.fill(end, 1);
//			}

			if (*end != '\0') {
				#ifdef DEBUG
					cerr << source->tag << ": " << endl;
				#endif

				std::string shortened;

				#if ENABLE_TRANSLATOR == 1
					std::stringstream fulltran;

					do {
						end = remove_redundant_spaces(end, shortened, limit);
				//				string trans = string();
						cerr << shortened;
						if (shortened.length() > 0) {
							std::string& trans = translator.translate(shortened.c_str());
							if (trans.length() == 0) {

			//							exit(-1);
								error = true;
								break;
							}
							fulltran << trans;
							writer.fill(trans);
						}
					} while (end != NULL && *end != '\0');


					#ifdef DEBUG
					cerr << endl;
					cerr << source->tag << " (Translation): " << fulltran.str() << endl;
					#endif
				#else
					remove_redundant_spaces(source_string, shortened);
					cerr << shortened << endl;
				#endif
			}

			delete [] source_string;
			source = reader.get_next_token();
		}

		if (!error)
			try {
				writer.write(write_type);
		//		if (read_type == READ_FROM_DATABASE)
		//			database_mysql::instance().finish(doc_id);
			}
			catch (translation_write_exception& e) {
				cerr << "Error: " << e.what() << endl;
				if ((write_type & article::WRITE_TO_DISK) &&
						!(write_type & article::WRITE_TO_DATABASE) &&
						read_type == READ_FROM_DATABASE)
					database_mysql::instance().fail(doc_id, source_lang.c_str());
			}
	}
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

	database_mysql::instance().fill(container, source_lang.c_str());
	while (container.size() > 0) {
		for (int i = 0; i < container.size(); ++i) {
			long id = container[i];
			string file = in_corpus.id2docpath(id);
			translate_file(file.c_str(), id);
		}
		database_mysql::instance().fill(container, source_lang.c_str());
	}
}

void input_manager::set_read_type(int type) {
	read_type = type;
}

void input_manager::set_write_type(int type) {
	write_type |= type;
}

void input_manager::init() {
	write_type = article::WRITE_TO_DISK;
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
	const char *pos = strchr(language_pair, ':');
	source_lang = string(language_pair, pos);
	target_lang = string(pos + 1);
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
//		database_mysql::instance().connect();
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








