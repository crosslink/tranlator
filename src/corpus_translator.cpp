/*
 * translator.cpp
 *
 *  Created on: Apr 10, 2012
 *      Author: monfee
 */

#include <iostream>

#include "input_manager.h"
#include "string.h"

using namespace std;

void usage(char *program) {
	cerr << "Usage: " << program << " [-l:source_lang:target_lang] [-o:/a/path/for/output] /a/path/to/translation/corpus" << std::endl;
	exit(-1);
}

int main(int argc, char **argv) {

	if (argc <= 1) {
		usage(argv[0]);
	}
	int param;
	input_manager manager;
	const char *p;
	bool has_error_param;

	for (param = 1; param < argc && *argv[param] == '-'; param++)
		{
		if (strncmp(argv[param], "-l", 2) == 0) {
			p = strchr(argv[param], ':');
			if (p)
				manager.set_language_pair(p + 1);
			else
				has_error_param = true;
		}
		if (strncmp(argv[param], "-o", 2) == 0)
			manager.set_out_path(string(strchr(argv[param], ':') + 1));
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

	for (int i = 1; i < argc; ++i) {
		manager.load(argv[0]);
		manager.translate();
	}

	return 0;
}

