/*
 * test_parse_translation.cpp
 *
 *  Created on: Apr 17, 2012
 *      Author: monfee
 */

#include <string>
#include <iostream>

using namespace std;

#include "../src/google_research_translator.h"
#include "../src/sys_file.h"

int main(int argc, char **argv) {
	if (argc <= 1) {
		cerr << "Usage: " << argv[0] << " /a/path/to/translation/result/file" << std::endl;
		exit(-1);
	}
	const char *content = sys_file::read_entire_file(argv[1]);
	string trans = google_research_translator().get_translation(content);
	cout << "Translation: " << trans << endl;
	return 0;
}

