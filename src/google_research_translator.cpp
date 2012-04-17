/*
 * google_research_translator.cpp
 *
 *  Created on: Apr 17, 2012
 *      Author: monfee
 */

#include "google_research_translator.h"

const char *google_research_translator::GOOGLE_TRANSLATE_RESEARCH_URL_TEMPLATE = "http://translate.google.com/researchapi/translate?";
const char *google_research_translator::GOOGLE_TRANSLATE_RESEARCH_API_KEY_FILE = "Auth.txt";

google_research_translator::google_research_translator() {
	if (key_status <= KEY_UNKNOWN) {
		api_key_file = "GOOGLE_TRANSLATE_RESEARCH_API_KEY_FILE";
		source_lang_var = "sl";
		target_lang_var = "tl";
		load_key();
	}
}

google_research_translator::~google_research_translator() {

}

//void google_research_translator::load_key()
//{
//
//}
//
//
//
//bool google_research_translator::test_key()
//{
//}



