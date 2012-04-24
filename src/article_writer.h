/*
 * article_writer.h
 *
 *  Created on: Apr 24, 2012
 *      Author: monfee
 */

#ifndef ARTICLE_WRITER_H_
#define ARTICLE_WRITER_H_

#include <string>

class article_writer : public article {
private:
	std::string content; // a copy of the text that is used for saving the translation version

public:
	article_writer();
	virtual ~article_writer();
};

#endif /* ARTICLE_WRITER_H_ */
