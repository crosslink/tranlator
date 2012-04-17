/*
 * google_research_translator.cpp
 *
 *  Created on: Apr 17, 2012
 *      Author: monfee
 */

#include "google_research_translator.h"
#include "webpage_retriever.h"

#include <stdio.h>
#include <stdlib.h>

#include <string>

using namespace std;

const char *google_research_translator::GOOGLE_TRANSLATE_RESEARCH_URL_TEMPLATE = "http://translate.google.com/researchapi/translate?";
const char *google_research_translator::GOOGLE_TRANSLATE_RESEARCH_API_KEY_FILE = "auth_key.txt";
const char *google_research_translator::GOOGLE_TRANSLATE_RESEARCH_AUTH_HEADER = "Authorization: GoogleLogin auth=";

google_research_translator::google_research_translator() {
	if (key_status <= KEY_UNKNOWN) {
		api_key_file = "GOOGLE_TRANSLATE_RESEARCH_API_KEY_FILE";
		source_lang_var = "sl";
		target_lang_var = "tl";
		set_key();
	}
}

google_research_translator::~google_research_translator() {

}


//void google_research_translator::set_key()
//{
//
//}
//
//
//
bool google_research_translator::set_key()
{
//	int len = api_key.length() + strlen(GOOGLE_TRANSLATE_RESEARCH_AUTH_HEADER);
//	char temp = new char[len + 1];
//	sprintf(temp, (char *)GOOGLE_TRANSLATE_URL_TEMPLATE, api_key.c_str());
//	temp[len] = '\0';
	query_template = GOOGLE_TRANSLATE_RESEARCH_URL_TEMPLATE;
	string header = string(GOOGLE_TRANSLATE_RESEARCH_AUTH_HEADER) + string(api_key);
	webpage_retriever::instance().add_header(header.c_str());
//	delete temp;
}



