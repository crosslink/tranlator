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
#include "corpus.h"

#ifndef ENABLE_TRANSLATOR
	#define ENABLE_TRANSLATOR 0
#else
	#define ENABLE_TRANSLATOR 1
#endif

class input_manager {
public:
	enum {READ_FROM_DATABASE, READ_FROM_DISK};

private:
	std::string input;
	static std::string out_path;
	corpus in_corpus;

	google_research_translator& translator;
	int limit;

	std::string language_pair;
	std::string source_lang;
	std::string target_lang;

	sys_files *disk;
	int read_type;
	int write_type;

public:
	input_manager();
	input_manager(std::string language_pair);
	virtual ~input_manager();

	void load(const char *file);
	void translate();
	void load_from_disk();
	void load_from_database();
	void translate_file(const char *file, long id = -1);

	void set_language_pair(const char *);
	void set_read_type(int type);
	void set_write_type(int type);
	void set_limit(int limit) { this->limit = limit; }

	static void set_out_path(std::string out_path);
	static std::string& get_out_path();

	static const char *remove_redundant_spaces(const char *from, std::string& to, long limit = -1);

private:
	void cleanup();
	void init();
};

#endif /* INPUT_MANAGER_H_ */
