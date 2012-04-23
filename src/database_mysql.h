/*
 * databasemysql.h
 *
 *  Created on: Apr 20, 2012
 *      Author: monfee
 */

#ifndef DATABASEMYSQL_H_
#define DATABASEMYSQL_H_

#include <mysql/mysql.h>

#include <string>

class database_mysql {
private:
    std::string server;
    std::string user;
    std::string password;
    std::string database;

    MYSQL *connection;

public:
	database_mysql();
	virtual ~database_mysql();

	int connect();

	void execute_query(std::string);

private:
	void init();


};

#endif /* DATABASEMYSQL_H_ */
