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
	virtual ~article();
};

#endif /* ARTICLE_H_ */
