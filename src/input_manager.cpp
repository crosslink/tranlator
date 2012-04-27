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

//google_research_translator& input_manager::translator = google_research_translator::get_instance();
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
//	this->language_pair = language_pair;
	google_research_translator::set_lang_pair(language_pair);
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
	const char *file = disk->first();
	try {
		while (file != NULL && strlen(file) > 0) {
			article_reader reader(file);
			article_writer writer(file);
	//		reader.copy_to_next_token(writer);
			token_string *source = reader.get_next_token(writer);
			while (source->length > 0) {

	//			reader.copy_to_next_token(writer);
				source = reader.get_next_token();
//				string trans = translator.translate(source->start, language_pair.c_str(), source->length);
				string trans = string(source->start, source->length);
				writer.fill(trans);
			}
			file = disk->next();
		}
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
}








