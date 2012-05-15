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
	char *start;
	long length;
	const char *tag;
};

class article_reader : public article {
public:
	enum {COMMENT = -1, DOCTYPE = 0, TITLE = 1, CATEGORIES = 2, ABSTRACT = 3, MAIN_TEXT = 4, NOTES = 5, REFERENCES = 6, EXTERNAL_LINKS = 7, ARTICLE_END};

	static const char *PARA_TAG_START;
	static const char *PARA_TAG_END;
	static const char *SECTION_TAG_START;
	static const char *SECTION_TAG_END;

private:
//	std::string content;
//	std::string& out;
	char *current;
	const char *previous;
	article_writer *writer;
	token_string current_token;
	std::string current_tag;

	int progress;

	char *start, *end;
	const char *body_start;
	const char *first_para;  // if
	const char *first_section; // anything before the first section is abstract
	const char *next_section;
	const char *sec_start;
	const char *para_start;
	const char *next_para;

public:
	article_reader(const char *file);
	virtual ~article_reader();

	token_string *get_next_token();
	void copy_to_next_token(article_writer& writer);
	token_string *get_next_token(article_writer& writer);

	virtual void read();

	static char *string_clean(token_string& token, long lower_case_only = 0);

private:
	void init_token();
	void process();

	void read_element_text(const char *tag_name = NULL);

	void read_title();
	void read_categories();
	void read_abstract();
	void read_main_text();
	void read_notes();

	void read_section();
	void read_para();

	void after_reading_abstract();
	void after_reading_a_para();
	void after_reading_a_section();

	void create_comment();
	void reconstruct_comment();

	void skip_doctype();
	void skip_notes();
	void skip_references();
	void skip_external_links();

	void wrap_up_to_body();
	void wrap_up_to_end();

	void copy_to_current();
	void copy_to(const char *start, const char *end);
	void copy_to_section_end();

	void goto_tag_end(char *this_char);
};

#endif /* ARTICLE_READER_H_ */
