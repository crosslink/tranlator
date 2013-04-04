/*
 * google_translate.cpp
 *
 *  Created on: Apr 12, 2012
 *      Author: monfee
 */

#include "../src/google_research_translator.h"
#include "../src/database_mysql.h"
#include "../src/sys_file.h"

#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>

using namespace std;

void usage(const char *program) {
	cerr << "Usage:" << program << " -f:auth_key.txt | key  " << endl
			<< "\t\t" << "-testkey" << endl
			<< "\t\t" << "-langpair input" << endl;
	exit(-1);
}

int main(int argc, char **argv) {

	enum { TEST_KEY, UPDATE_KEY, TRANSLATE};

	if (argc > 1) {

		string token;
		int type = UPDATE_KEY;

		int param;
		const char *p;
		const char *langpair;

		google_research_translator& translator = google_research_translator::get_instance();

		string key;
		for (param = 1; param < argc && *argv[param] == '-'; param++)
		{
			if (strncmp(argv[param], "-f", 2) == 0) {
				p = strchr(argv[param], ':');
				if (p) {
					const char *content = sys_file::read_entire_file(p+1);
					token = content;
					delete [] content;
				}
				else
					usage(argv[0]);
			}
			else if (strncmp(argv[param], "-testkey", 8) == 0) {
				type = TEST_KEY;
			}
			else if (strncmp(argv[param], "-langpair", 9) == 0) {
				langpair = argv[param] + 10;
				type = TRANSLATE;
			}
		}

		switch (type) {
		case UPDATE_KEY:
			if (token.length() == 0)
				token = argv[1];

			cerr << "Token:" << endl << token << endl;
			database_mysql::instance().connect();
			database_mysql::instance().update_google_translate_key(token.c_str());
			break;
		case TEST_KEY:
			database_mysql::instance().connect();
			key = database_mysql::instance().get_google_translate_key();
			translator.set_api_key(key.c_str());
			translator.test_key();
			break;
		case TRANSLATE:
			translator.initialize(google_translator::LOAD_KEY);
			translator.set_lang_pair(langpair);
			cout << translator.translate(argv[argc - 1]);
			break;

		}
	}
	else
		usage(argv[0]);
	return 0;
}

