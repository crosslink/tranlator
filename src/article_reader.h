/*
 * article_reader.h
 *
 *  Created on: Apr 24, 2012
 *      Author: monfee
 */

#ifndef ARTICLE_READER_H_
#define ARTICLE_READER_H_

class article_reader : public article {
private:
	std::string content;
	std::string& out;

public:
	article_reader(const char *file);
	virtual ~article_reader();

	std::string get_next_token();
};

#endif /* ARTICLE_READER_H_ */
