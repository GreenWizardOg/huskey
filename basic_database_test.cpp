/*
 * basic_database_test.cpp
 *
 *  Created on: Apr 13, 2011
 *      Author: barryodriscoll
 */

#include <string>
#include <iostream>
#include "libpq-fe.h"

int main(int argc, char** argv) {
	PGconn * _conn;
	PGresult * res;

	_conn = PQconnectdb("dbname = elog_test user = postgres password = wulfpack");

	if (PQstatus(_conn) != CONNECTION_OK)
	{
		std::cout << "Failed to connect to database" << std::endl;
		return -1;
	}

	res = PQexec(_conn, "DROP TABLE DEREK_TABLE;");
	PQclear(res);
	res = PQexec(_conn, "CREATE TABLE DEREK_TABLE (id integer PRIMARY KEY, name varchar(255));");
	PQclear(res);
	res = PQexec(_conn, "INSERT INTO DEREK_TABLE values(0, 'Limerick');");
	PQclear(res);
	res = PQexec(_conn, "SELECT name FROM DEREK_TABLE;");
	if(PQresultStatus(res) == PGRES_TUPLES_OK){
		std::cout << PQgetvalue(res, 0, 0) << std::endl;
	}
	PQclear(res);

}
