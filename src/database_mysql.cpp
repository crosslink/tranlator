/*
 * databasemysql.cpp
 *
 *  Created on: Apr 20, 2012
 *      Author: monfee
 */

#include "database_mysql.h"
#include "string_utils.h"

#include <stddef.h>

#include <iostream>

using namespace std;

database_mysql::database_mysql() {


	init();
//	connect();
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
		connected = true;
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

void database_mysql::fill(std::vector<long>& container) {
	MYSQL_RES *result;
	MYSQL_ROW row;

	static const string template_query("select id from topics where status = 0 and result = 0");
	string limits = " limit " + number_to_string(number_of_doc);
	string query = template_query + limits;

	mysql_query(connection, query.c_str());
	result = mysql_store_result(connection);

//	int num_fields = mysql_num_fields(result);
	container.clear();

	if (result) {
	  while ((row = mysql_fetch_row(result)))
	  {

//	          printf("%s ", row[i] ? row[i] : "NULL");
		  if (row[0]) {
			  long id = atol(row[0]);
			  if (id > -1)
				  container.push_back(id);
		  }
	  }

	  processing(container);
	}
}



void database_mysql::finish(std::vector<long>& container) {
	update_status(container, 0, 1);
}

void database_mysql::update_status(std::vector<long>& container, int type, int value) {
	if (container.size() <= 0)
		return;

	MYSQL_RES *result;

//	static const char *template_query_update("update topics set %s=%d where id in (%s)");
	string doc_list = collection_to_list(container);
	string column;
	switch (type) {
	case 0:
		column = "result";
		break;
	case 1:
		column = "status";
		break;
	}
	string value_string = number_to_string(value);
	std::stringstream query_buffer;
	query_buffer << "update topics set " << column << "=" << value_string << " where id in (" << doc_list << ")";
	string query = query_buffer.str();
	mysql_query(connection, query.c_str());
	result = mysql_store_result(connection);
}

void database_mysql::processing(std::vector<long>& container) {
	update_status(container, 1, 1);
}

void database_mysql::fail(std::vector<long>& container) {
	update_status(container, 0, 0);
	update_status(container, 1, 0);
}

void database_mysql::update_translation(long id, const char* translation,
		const char* target_lang) {
}

std::string database_mysql::get_google_translate_key() {
	MYSQL_RES *result;
	MYSQL_ROW row;

	static const string template_query_get_key("select key from key");

	mysql_query(connection, template_query_get_key.c_str());
	result = mysql_store_result(connection);


	if (result) {
	  row = mysql_fetch_row(result);
	  {
//	          printf("%s ", row[i] ? row[i] : "NULL");
		  if (row[0]) {
			  string key = row[0];
			  return key;
		  }
	  }
	}
	 return "";
}

void database_mysql::update_google_translate_key(const char* key) {
	MYSQL_RES *result;

	static const string template_query_update_key("update key set key=QUOTE(");
	string query = template_query_update_key + key + ")";
	mysql_query(connection, query.c_str());
	result = mysql_store_result(connection);

	if (result) {
		cerr << "Updated key: " << result << endl;
	}
}

void database_mysql::init() {
	server = "localhost";
	database = "google_translate_info";
	user = "gt";
	password = "gtproject";

	connection = NULL;
	connected = false;
	number_of_doc = DEFAULT_NUMBER_OF_DOC_PER_REQUEST;
}


