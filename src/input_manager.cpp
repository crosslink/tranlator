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

#include <string.h>

#include <string>
#include <iostream>

using namespace std;

#define ENABLE_TRANSLATOR 0

std::string input_manager::out_path;

input_manager::input_manager() {
	init();
}

input_manager::input_manager(std::string lang_pair) : language_pair(lang_pair) {
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

void input_manager::init() {
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
	disk = new sys_files();
	disk->pattern("*.[xX][mM][lL]");
	disk->list(filename);
	if (disk->isdir(filename)) {
		corpus::instance().base(filename);
	}
//	const char *name = NULL;
//
//	for (name = disk->first(); name != NULL ; name = disk->next())
//	{
}

void input_manager::translate() {
#if ENABLE_TRANSLATOR == 1
	static google_research_translator& translator = google_research_translator::get_instance();
	translator.set_lang_pair(language_pair.c_str());
#endif
	const char *file = disk->first();
	try {
		while (file != NULL && strlen(file) > 0) {
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
				cerr << source->tag << ": " << source_string << endl;
#endif
#if ENABLE_TRANSLATOR == 1
//				string trans = string();
				string trans = translator.translate(source_string);
#ifdef DEBUG
				cerr << source->tag << " (Translation): " << trans << endl;
#endif
				writer.fill(trans);
#endif
				delete [] source_string;
				source = reader.get_next_token();
			}
			writer.write();
			file = disk->next();
		}
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
}








