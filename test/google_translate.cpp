/*
 * google_translate.cpp
 *
 *  Created on: Apr 12, 2012
 *      Author: monfee
 */

#include "../src/google_research_translator.h"
#include "../src/database_mysql.h"
#include "../src/sys_file.h"
#include <iostream>

using namespace std;

void usage(const char *program) {
	cerr << "Usage:" << program << " -f:auth_key.txt | key  " << endl;
	exit(-1);
}

int main(int argc, char **argv) {
//	google_translator::load_key();
	google_research_translator& translator = google_research_translator::get_instance();

//	std::cout << "Hello, world!" << std::endl;
	if (argc > 1) {

		int param;
		const char *p;
		string token;
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
		}

		if (token.length() == 0)
			token = argv[1];

		cerr << "Token:" << endl << token << endl;
		database_mysql::instance().update_google_translate_key(token.c_str());
	}
	return 0;
}

