/*
 * databasemysql.cpp
 *
 *  Created on: Apr 20, 2012
 *      Author: monfee
 */

#include "database_mysql.h"

#include <stddef.h>

#include <iostream>

using namespace std;

database_mysql::database_mysql() {
	connection = NULL;
}

database_mysql::~database_mysql() {
	if (connection)
		mysql_close(connection);
}

int database_mysql::connect() {
	connection = mysql_init(NULL);

//    try {
		//connection->connect("DB NAME", "DB HOST probably localhost", "DB USER", "DB PASS");
	if (mysql_real_connect(connection, server.c_str(), user.c_str(), password.c_str(), database.c_str(), 0, NULL, 0) == NULL) {
		printf("Error %u: %s\n", mysql_errno(connection), mysql_error(connection));
		 exit(1);
	}
	else {
		cerr << "Database (" << server << ": " << database << ") connected" << endl;
	}

//		Query query = connection->query();
//
//		/* To insert stuff with escaping */
//		query << "INSERT INTO some_table " <<
//					 "VALUES (" <<
//					 "'', " << /* This is left empty because the column is AUTO_INCREMENT */
//					 "\"" << escape << some_var_that_contains_some_value << "\"" <<
//					 ");";
//		query.execute();
//		/* That's it for INSERT */
//
//		/* Now SELECT */
//		query << "SELECT * FROM biz LIMIT 10";
//		StoreQueryResult ares = query.store();
//		for (size_t i = 0; i < ares.num_rows(); i++)
//		   cout << "Name: " << ares[i]["name"] << " - Address: " << ares[i]["address"] << endl;
//
//		/* Let's get a count of something */
//		query << "SELECT COUNT(*) AS row_count FROM biz";
//		StoreQueryResult bres = query.store();
//		cout << "Total rows: " << bres[0]["row_count"];

}



void database_mysql::execute_query(std::string query) {
	MYSQL_RES *result;
	MYSQL_ROW row;

	mysql_query(connection, query.c_str());
	result = mysql_store_result(connection);

	int num_fields = mysql_num_fields(result);

	  while ((row = mysql_fetch_row(result)))
	  {
	      for(int i = 0; i < num_fields; i++)
	      {
	          printf("%s ", row[i] ? row[i] : "NULL");
	      }
	      printf("\n");
	  }
}

void database_mysql::init() {
	server = "localhost";
	database = "google_translate_info";
	user = "gt";
	password = "gtproject";
}


