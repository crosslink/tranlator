/*
 * article_writer.h
 *
 *  Created on: Apr 24, 2012
 *      Author: monfee
 */

#ifndef ARTICLE_WRITER_H_
#define ARTICLE_WRITER_H_

#include <string>

#include "corpus.h"
#include "article.h"

class article_writer : public article {
private:
	static corpus out;

public:
	article_writer(const char *file); // the original input file which need to be saved to a new file with a new name
	virtual ~article_writer();

private:
//	std::string content; // a copy of the text that is used for saving the translation version
	void create_output_file(const char *file);
};

#endif /* ARTICLE_WRITER_H_ */
