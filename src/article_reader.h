/*
 * article_reader.h
 *
 *  Created on: Apr 24, 2012
 *      Author: monfee
 */

#ifndef ARTICLE_READER_H_
#define ARTICLE_READER_H_

#include <string>

#include "article.h"
#include "article_writer.h"

struct token_string {
	const char *start;
	long length;
};

class article_reader : public article {
public:
	enum {INIT = -1, TITLE = 0, CATEGORIES = 1, ABSTRACT = 2, MAIN_TEXT = 3, NOTES = 4, REFERENCES = 5, EXTERNAL_LINKS = 6};

private:
//	std::string content;
//	std::string& out;
	const char *current;
	const char *previous;
	article_writer *writer;
	token_string current_token;
	std::string current_tag;

	int progress;

	const char *start, *end = NULL;
	const char *body_start = NULL;
	const char *first_para = NULL;  // if
	const char *first_section = NULL; // anything before the first section is abstract

public:
	article_reader(const char *file);
	virtual ~article_reader();

	token_string *get_next_token();
	void copy_to_next_token(article_writer& writer);
	token_string *get_next_token(article_writer& writer);

	virtual void read();

	static char *string_clean(char *file, long lower_case_only = 1, long trim = 1);

private:
	void init_token();
	void process();

	void read_element_text(const char *tag_name);
	std::string get_element_text(const char *tag_name);

	void read_title();
	void read_categories();
	void read_abstract();
	void read_main_text();
	void read_notes();

	void read_section();
	void read_para(const char *p_start, const char *p_end);

	void create_comment();
	void reconstruct_comment();

	void skip_notes();
	void skip_references();
	void skip_external_links();

	void wrap_up_to_body();
	void wrap_up_to_end();

	void copy_to_current(const char *start, const char *end);
};

#endif /* ARTICLE_READER_H_ */
