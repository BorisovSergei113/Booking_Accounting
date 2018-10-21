
#include "stdafx.h"
#include <mysql.h>
#include <iostream>


int main()
{
	MYSQL *connection; //pointer on connection
	MYSQL  mysql;
	MYSQL_RES *result;//result table
	MYSQL_ROW row; //rows
	int request_state;

	mysql_init(&mysql);
	connection = mysql_real_connect(&mysql, "localhost", "root", "1234", "mydb", 3306, 0, 0);// (&MYSQL,"host","login","pasword","name_database","port","unix_socket","clientflag")
	if (connection == NULL) {
		std::cout << mysql_error(&mysql)<< '\n';
		return 1;
	}
	request_state = mysql_query(connection, "select user_count()");
	if (request_state != 0){
		std::cout << mysql_error(connection)<< '\n';
		return 1;
	}
	result = mysql_store_result(connection);
	while ((row = mysql_fetch_row(result)) != NULL){
		std::cout << "Number users" << row[0] << '\n';
	}
	mysql_free_result(result);
	mysql_close(connection);
    return 0;
}

