/*
 * input_manager.cpp
 *
 *  Created on: Apr 23, 2012
 *      Author: monfee
 */

#include "input_manager.h"
#include "corpus.h"
#include "article_reader.h"

#include <string.h>

#include <string>

using namespace std;

google_research_translator& input_manager::translator = google_research_translator::get_instance();

input_manager::input_manager() {
	init();
}

input_manager::input_manager(std::string lang_pair) : language_pair(lang_pair) {
	//google_research_translator& translator = google_research_translator::get_instance();
	init();
}

input_manager::~input_manager() {

}

void input_manager::set_out_path(std::string out_path) {
	this->out_path = out_path;
}

void input_manager::init() {
	disk = NULL;
	out_path = ".";
}

void input_manager::cleanup() {
	if (disk != NULL)
		delete disk;
}

void input_manager::set_language_pair(std::string language_pair) {
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

/*
 * process xml file by each element
 */
std::string input_manager::next_text() {

	return "";
}

void input_manager::translate() {
	const char *file = disk->first();
	while (file != NULL && strlen(file) > 0) {
		article_reader reader(file);
		article_writer writer();
		reader
		string source = reader.get_next_token();
		while (source.length() > 0) {
			source = next_text();
			string trans = translator.translate(source.c_str(), language_pair.c_str());
		}
		file = disk->next();
	}
}








