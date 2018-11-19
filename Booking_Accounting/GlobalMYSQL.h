#pragma once
#include "mysql.h"

extern MYSQL *connection, mysql;
extern int query_state;
extern MYSQL_RES *result;
extern MYSQL_ROW row;