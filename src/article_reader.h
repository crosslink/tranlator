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

class article_reader : public article {
private:
//	std::string content;
//	std::string& out;

public:
	article_reader(const char *file);
	virtual ~article_reader();

	std::string get_next_token();
	void copy_to_next_token(article_writer& writer);
};

#endif /* ARTICLE_READER_H_ */
