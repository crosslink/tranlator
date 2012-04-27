/*
 * google_translate.cpp
 *
 *  Created on: Apr 12, 2012
 *      Author: monfee
 */

#include "../src/google_research_translator.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
//	google_translator::load_key();
	google_research_translator& translator = google_research_translator::get_instance();

//	std::cout << "Hello, world!" << std::endl;
	return 0;
}

