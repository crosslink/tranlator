/*
 * googler_esearch_translator.h
 *
 *  Created on: Apr 17, 2012
 *      Author: monfee
 */

#ifndef GOOGLER_ESEARCH_TRANSLATOR_H_
#define GOOGLER_ESEARCH_TRANSLATOR_H_

#include "google_translator.h"

class google_research_translator: public google_translator {
public:
	static const char *GOOGLE_TRANSLATE_RESEARCH_URL_TEMPLATE;
	static const char *GOOGLE_TRANSLATE_RESEARCH_API_KEY_FILE;

public:
	google_research_translator();
	virtual ~google_research_translator();

//private:
//	static void init();
//	static void load_key();
//	static bool test_key();
};

#endif /* GOOGLER_ESEARCH_TRANSLATOR_H_ */
