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

	int progress;

public:
	article_reader(const char *file);
	virtual ~article_reader();

	token_string *get_next_token();
	void copy_to_next_token(article_writer& writer);
	token_string *get_next_token(article_writer& writer);

	virtual void read();

private:
	void init_token();
	void process();

	void read_title();
	void read_categories();
	void read_main_text();
	void read_notes();

	void create_comment();
	void reconstruct_comment();

	void skip_notes();
	void skip_references();
	void skip_external_links();

	void copy_to_current(const char *start, const char *end);
};

#endif /* ARTICLE_READER_H_ */
