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

//namespace QLINK {

	class google_translator : public pattern_singleton<google_translator>
	{
	public:
		static const char *GOOGLE_TRANSLATE_URL_TEMPLATE;
		static const char *LANGUAGE_PAIR_EN_CS;
		static const char *LANGUAGE_PAIR_EN_CT;

		static const char *TEST_STRING_EN;
		static const char *TEST_STRING_ZH;

		static const char *GOOGLE_TRANSLATE_API_KEY_FILE;

		static const int KEY_UNKNOWN = -1;
		static const int KEY_INVALID = 99;
		static const int KEY_VALID = 1;
		static const int KEY_LOADED = 0;


	protected:
		static std::string api_key;
		static int key_status;
		static std::string api_key_file;

		static std::string query_template;
		static std::string query_lang_pair_template;

		static std::string source_lang_var;
		static std::string target_lang_var;

		static std::string source_lang;
		static std::string target_lang;

	public:
		google_translator();
		virtual ~google_translator();

		std::string translate(const char *text, long length = -1);
		static bool has_valid_key();

		virtual std::string get_translation(const char *content);

		google_translator& get_instance();

		static void set_lang_pair(const char *langpair);

	protected:

		void append_text(std::string& url, const char *text, long length = 0);
		void append_lp(std::string& url, const char *language_pair);

		static void add_lang_options(std::string& url);

		void add_text_option(std::string& url, const char *text, long length = 0);

//	private:
		void init();
		void init_once();
		virtual void set_key();
		bool test_key();
	};

//}

#endif /* GOOGLE_TRANSLATOR_H_ */
