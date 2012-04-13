/*
 * google_translator.cpp
 *
 *  Created on: Jan 6, 2010
 *      Author: monfee
 */

#include "google_translator.h"
#include "webpage_retriever.h"
#include "string_utils.h"
#include "sys_file.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <stpl/stpl_parser.h>
#include <stpl/stpl_property.h>

using namespace std;

namespace QLINK {
//	const char *google_translator::GOOGLE_TRANSLATE_URL_TEMPLATE = "http://translate.google.com/?oe=utf8"; //&langpair=en|zh&text=dahuangshan
	const char *google_translator::GOOGLE_TRANSLATE_URL_TEMPLATE = "https://www.googleapis.com/language/translate/v2?key=%s";
	const char *google_translator::LANGUAGE_PAIR_EN_CT = "en|zh-TW";
	const char *google_translator::LANGUAGE_PAIR_EN_CS = "en|zh-CN";

	const char *google_translator::TEST_STRING_EN = "I";
	const char *google_translator::TEST_STRING_EN = "\346\210\221"; // chinese character for "I"


	const char *google_translator::GOOGLE_TRANSLATE_API_KEY_FILE = "key.txt";

	int google_translator::key_status =  google_translator::KEY_UNKNOWN;

	google_translator::google_translator()
	{

	}

	google_translator::~google_translator()
	{

	}



	void google_translator::load_key() {
		if (key_status == KEY_UNKNOWN) {
			const char *key_text = sys_file::read_entire_file(GOOGLE_TRANSLATE_API_KEY_FILE);
			if (key_text == NULL) {
				api_key = key_text;
				if (test_key())
					key_status = KEY_VALID;
				else
					key_status = KEY_INVALID;
			}
			else
				key_status = KEY_INVALID;
		}

		if (key_status != KEY_VALID) {
			std::cerr << "Invalid Google Translate API key: " << api_key << std::endl;
			exit(-1);
		}
	}

	bool google_translator::test_key() {
		query_template = sprintf((char *)GOOGLE_TRANSLATE_URL_TEMPLATE, api_key.c_str());
		string result =
		return false;
	}

	bool google_translator::has_valid_key() {
		return key_status == KEY_VALID;
	}

	std::string google_translator::translate(const char *text, const char *language_pair)
	{
		string url(query_template);
//		append_lp(url, language_pair);
//		append_text(url, text);
		add_text_option(url, text);
		add_lang_options(url, language_pair);
		const char *content = webpage_retriever::instance().retrieve(url.c_str());

		string result;

		result = get_translation(content);

		return result;
	}

	std::string google_translator::get_translation(const char *content)
	{
		const char *start, *end;
		static const char *TEXTAREA_TAG = "translatedText";
		string gtrans;

		start = strstr(content, TEXTAREA_TAG);
		if (start != NULL) {
			start += strlen(TEXTAREA_TAG);
			start = strchr(start, ':');

			start = strchr(start, '"');
			++start;
			end =  strchr(start, '"');
			gtrans = string(start, end);
		}
		return gtrans;
	}

//	std::string google_translator::get_translation(const char *content)
//	{
//		const char *start = content, *end;
//		static const char *TEXTAREA_TAG = "<textarea";
//		string gtrans;
//
//		while ((start = strstr(start, TEXTAREA_TAG)) != NULL) {
//			start += strlen(TEXTAREA_TAG);
//			if (!(end = strchr(start, '>')))
//				break;
//
//			stpl::GeneralParser<stpl::Property<string, const char *> > property_parser(start, end);
//			property_parser.parse();
//			stpl::Property<string, const char *> *property;
//			while ((property = property_parser.get_next_entity()) != NULL)
//				if (property->name() == "name") {
//					string value = property->value();
//					if (value == "utrans") {
//						const char *trans_start, *trans_end;
//						++end;
//						trans_start = end;
//						trans_end = strchr(trans_start, '<');
//						return string(trans_start, trans_end);
//					}
//				}
//		}
//		return "";
//	}

	void google_translator::append_text(std::string& url, const char *text)
	{
		url.append("&text=");
		while (*text != '\0') {
			if (*text == ' ')
				url.append("%20");
			else if (*text == ',')
				url.append("%2C");
			else if (*text == '\'')
				url.append("%27");
			else if (isalnum(*text))
				url.push_back(*text);
			else
				url.append("%" + byte_to_string(*text, 16));

			++text;
		}
		//url.append(text);
	}

	void google_translator::append_lp(std::string& url, const char *language_pair)
	{
		url.append("&langpair=");
		url.append(language_pair);
	}

	void google_translator::add_lang_options(std::string& url,const char *language_pair)
	{
		const char *pos = strchr(language_pair, '|');
		string source_lang(language_pair, pos);
		string target_lang(pos + 1);
		url.append("&source=");
		url.append(source_lang);
		url.append("&target=");
		url.append(target_lang);
	}

	void google_translator::add_text_option(std::string& url, const char *text)
	{
		url.append("&q=");
		url.append(text);
	}
}
