/*
 * reset_artile.cpp
 *
 *  Created on: Oct 9, 2012
 *      Author: monfee
 */


#include <iostream>
#include <fstream>
#include <string>

#include "../src/database_mysql.h"

using namespace std;

void usage(const char *program) {
	cerr << "Usage:" << program << " missing/id/file  lang[zh|ja|ko]" << endl;
	exit(-1);
}

int main(int argc, char **argv) {
	if (argc < 3)
		usage(argv[0]);

	database_mysql::instance().connect();

	string line;
	ifstream myfile (argv[1]);
	if (myfile.is_open())
	  {
	    while ( myfile.good() )
	    {
	      getline (myfile,line);
	      cout << line << endl;


	    }
	    myfile.close();
	  }

	  else cout << "Unable to open file";
	return 0;
}
