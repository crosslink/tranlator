/*
 * test_database.cpp
 *
 *  Created on: Apr 23, 2012
 *      Author: monfee
 */

#include <string>
#include <iostream>

using namespace std;

#include "../src/database_mysql.h"
#include "../src/sys_file.h"

int main(int argc, char **argv) {
	database_mysql database;
	database.connect();


	return 0;
}


