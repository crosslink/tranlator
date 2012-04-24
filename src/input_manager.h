/*
 * input_manager.h
 *
 *  Created on: Apr 23, 2012
 *      Author: monfee
 */

#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include "google_research_translator.h"
#include "sys_files.h"

class input_manager {
private:
	std::string input;
	static std::string out_path;

	static google_research_translator& translator;

	std::string language_pair;

	sys_files *disk;


public:
	input_manager();
	input_manager(std::string language_pair);
	virtual ~input_manager();

	void load(const char *file);
	void translate();

	std::string next_text();

	void set_language_pair(std::string language_pair);
	void set_out_path(std::string out_path);

	std::string get_out_path() const {
		return out_path;
	}

private:
	void cleanup();
	void init();
};

#endif /* INPUT_MANAGER_H_ */
