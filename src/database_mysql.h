/*
 * databasemysql.h
 *
 *  Created on: Apr 20, 2012
 *      Author: monfee
 */

#ifndef DATABASEMYSQL_H_
#define DATABASEMYSQL_H_

#include "pattern_singleton.h"

#include <mysql/mysql.h>

#include <string>
#include <vector>

class database_mysql : public pattern_singleton<database_mysql> {
public:
	const static int DEFAULT_NUMBER_OF_DOC_PER_REQUEST = 50;

private:
    std::string server;
    std::string user;
    std::string password;
    std::string database;

    MYSQL *connection;

    int number_of_doc;
    bool connected;

public:
	database_mysql();
	virtual ~database_mysql();

	int connect();

	void execute_query(std::string);

	void fill(std::vector<long>& container);
	void finish(std::vector<long>& container);
	void fail(std::vector<long>& container);
	void processing(std::vector<long>& container);

	void update_status(std::vector<long>& container, int type, int value);
	void update_translation(long id, const char *translation, const char *target_lang);

	bool is_connected() { return connected; }

private:
	void init();


};

#endif /* DATABASEMYSQL_H_ */
