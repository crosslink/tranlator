/*
 * article.h
 *
 *  Created on: Apr 24, 2012
 *      Author: monfee
 */

#ifndef ARTICLE_H_
#define ARTICLE_H_

#include <string>

class article {
protected:
	std::string file_path;
	char *content;
	std::string ext;

public:
	article();
	article(const char *file);
	virtual ~article();

	virtual void read();
	virtual void write();

	static std::string id2dir(unsigned long id);
	static int file2id(const char *file);
};

#endif /* ARTICLE_H_ */
