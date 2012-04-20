/*
 * databasemysql.cpp
 *
 *  Created on: Apr 20, 2012
 *      Author: monfee
 */

#include "database_mysql.h"

#include <stddef.h>

database_mysql::database_mysql() {

}

database_mysql::~database_mysql() {

}

int database_mysql::connect() {
	connection = mysql_init(NULL);

//    try {
//		conn.connect("DB NAME", "DB HOST probably localhost", "DB USER", "DB PASS");
//		Query query = conn.query();
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
//
//		} catch (BadQuery er) { // handle any connection or
//			// query errors that may come up
//			cerr << "Error: " << er.what() << endl;
//			return -1;
//		} catch (const BadConversion& er) {
//			// Handle bad conversions
//			cerr << "Conversion error: " << er.what() << endl <<
//					"\tretrieved data size: " << er.retrieved <<
//					", actual size: " << er.actual_size << endl;
//			return -1;
//		} catch (const Exception& er) {
//			// Catch-all for any other MySQL++ exceptions
//			cerr << "Error: " << er.what() << endl;
//			return -1;
//		}

}

void database_mysql::init() {
	server = "localhost";

}


