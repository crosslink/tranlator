/*
 * google_translator.h
 *
 *  Created on: Jan 6, 2010
 *      Author: monfee
 */

#ifndef GOOGLE_TRANSLATOR_H_
#define GOOGLE_TRANSLATOR_H_

#include <string>
#include "pattern_singleton.h"

namespace QLINK {

	class google_translator : public pattern_singleton<google_translator>
	{
	public:
		static const char *GOOGLE_TRANSLATE_URL_TEMPLATE;
		static const char *LANGUAGE_PAIR_EN_CS;
		static const char *LANGUAGE_PAIR_EN_CT;

		static const char *TEST_STRING_EN;
		static const char *TEST_STRING_ZH;

		static const char *GOOGLE_TRANSLATE_API_KEY_FILE;

		static const int KEY_UNKNOWN = 0;
		static const int KEY_INVALID = -1;
		static const int KEY_VALID = 99;
		static const int KEY_LOADED = 1;


	private:
		static std::string api_key;
		static int key_status;

		static std::string query_template;

	public:
		google_translator();
		virtual ~google_translator();

		std::string translate(const char *text, const char *language_pair);

	private:
		static void load_key();
		static bool test_key();
		static bool has_valid_key();

		std::string get_translation(const char *content);

		void append_text(std::string& url, const char *text);
		void append_lp(std::string& url, const char *language_pair);

		void add_lang_options(std::string& url, const char *language_pair);
		void add_text_option(std::string& url, const char *text);
	};

}

#endif /* GOOGLE_TRANSLATOR_H_ */
