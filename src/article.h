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
	std::string content;

public:
	article();
	article(const char *file);
	virtual ~article();

	void read();
	void write();

	static
};

#endif /* ARTICLE_H_ */
