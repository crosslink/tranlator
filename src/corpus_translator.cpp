/*
 * translator.cpp
 *
 *  Created on: Apr 10, 2012
 *      Author: monfee
 */

#include <iostream>

#include "input_manager.h"
#include "string.h"
#include "article.h"
#include "database_mysql.h"

using namespace std;

void usage(char *program) {
	cerr << "Usage: " << program << " [-lp:source_lang:target_lang] [-limit:500] [-o:/a/path/for/output] /a/path/to/translation/corpus" << std::endl;
	exit(-1);
}

int main(int argc, char **argv) {

	if (argc <= 1) {
		usage(argv[0]);
	}

	input_manager manager;

	bool has_error_param;
	long limit = 450;

	int param;
	const char *p;
	bool required_database = false;

	for (param = 1; param < argc && *argv[param] == '-'; param++)
		{
		if (strncmp(argv[param], "-lp", 3) == 0) {
			p = strchr(argv[param], ':');
			if (p)
				manager.set_language_pair(p + 1);
			else
				has_error_param = true;
		}
		else if (strncmp(argv[param], "-limit", 6) == 0) {
			limit = atol(strchr(argv[param], ':') + 1);
			if (limit < 0) {
				cerr << "Unknown limit option: " << argv[param] << endl;
				has_error_param = true;
			}
		}
		else if (strncmp(argv[param], "-o", 2) == 0)
			manager.set_out_path(string(strchr(argv[param], ':') + 1));
		else if (strncmp(argv[param], "-database", 9) == 0) {
			required_database = true;
			manager.set_read_type(input_manager::READ_FROM_DATABASE);
		}
//		else if (strncmp(argv[param], "-write2db", 9) == 0) {
//			required_database = true;
//			manager.set_write_type(article::WRITE_TO_DATABASE);
//		}
//			lowercase_only = TRUE;
//		else if (strcmp(argv[param], "-noyears") == 0)
//			print_mode |= MODE_NO_4_DIGIT_NUMBERS;
//		else if (strncmp(argv[param], "-runname:", 9) == 0)
//			runname = strchr(argv[param], ':') + 1;
//		else if (strncmp(argv[param], "-propernounboost:", 17) == 0)
//			proper_noun_boost = atof(strchr(argv[param], ':') + 1);
//		else if (strncmp(argv[param], "-targets:", 8) == 0)
//			{
//			targets_per_link = atoi(strchr(argv[param], ':') + 1);
//			if (targets_per_link <= 0)
//				usage(argv[0]);
//			}
//		else if (strncmp(argv[param], "-anchors:", 8) == 0)
//			{
//			anchors_per_run = atoi(strchr(argv[param], ':') + 1);
//			if (anchors_per_run <= 0)
//				usage(argv[0]);
//			}
//		else
//					// and exit

		}

	if (has_error_param || param >= argc)
		usage(argv[0]);

//	if (required_database)
	manager.set_write_type(article::WRITE_TO_DATABASE);
		database_mysql::instance().connect();

	manager.set_limit(limit);

	for (int i = param; i < argc; ++i) {
		manager.load(argv[i]);
		manager.translate();
	}

	return 0;
}

