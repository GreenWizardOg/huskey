/*
 * DatabaseManager.cpp
 *
 *  Created on: Apr 7, 2011
 *      Author: barryodriscoll
 */

#include "Poco/String.h"
#include "DatabaseManager.hpp"
#include "Poco/Foundation.h"
#include <string>
#include <cstring>
#include <iostream>
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include "LogManager.hpp"
#include "ElogServer.hpp"

using Poco::UUID;
using Poco::UUIDGenerator;
using Poco::AssertionViolationException;
using Poco::trimRightInPlace;

void DatabaseManager::init(const std::string& username, const std::string& password, const std::string& database)  throw (AssertionViolationException) {
	ElogServer::getLogger().log("initialising database connection");

	poco_assert(!_conn);

	checkParameter(username);
	checkParameter(password);
	checkParameter(database);

	std::string connectionInfo = "dbname = " + database + " user = " + username + " password = " + password;

	ElogServer::getLogger().log("with connection string: [" + connectionInfo + "]");

	_conn = PQconnectdb(connectionInfo.c_str());
	if (PQstatus(_conn) != CONNECTION_OK)
	{
		std::string errorMsg(PQerrorMessage(_conn));
		ElogServer::getLogger().log("connection failed with error message: [" + errorMsg + "]");
		poco_assert(false); //TODO BoD/dB - figure out how to throw exceptions properly
	}
	ElogServer::getLogger().log("successfully connected to database");

}

std::string DatabaseManager::run(const std::string& sql)  throw (AssertionViolationException) {
	ElogServer::getLogger().log("attempting to run database command");

	poco_assert(_conn);

	checkParameter(sql);

	ElogServer::getLogger().log("with sql: [" + sql + "]");

	PGresult   *res;
	std::string * resultAsString;

	res = PQexec(_conn, sql.c_str());

	if (PQresultStatus(res) >= PGRES_BAD_RESPONSE){
		ElogServer::getLogger().log("database command failed with error code [" + std::string(PQresStatus(PQresultStatus(res))) + "] and error msg [" + std::string(PQresStatus(PQresultStatus(res))) + "]");
		PQclear(res);
		PQreset(_conn);
		poco_assert(false);//TODO this is really stupid fix later BoD/dB
	}
	if (PQresultStatus(res) == PGRES_TUPLES_OK) {
		ElogServer::getLogger().log("database command succeeded and returned a tuple result");
		resultAsString = new std::string(PQgetvalue(res, 0, 0));
		ElogServer::getLogger().log("tuple result was [" + *resultAsString + "]");
		PQclear(res);
		return *resultAsString;
	} else {
		ElogServer::getLogger().log("database command succeeded");
		PQclear(res);
		return "";
	}

}

void DatabaseManager::checkParameter(const std::string& parameter){
	poco_assert(&parameter);

	char* cs = new char[parameter.length() + 1];

	std::strcpy(cs, parameter.c_str());

	std::string trimed(cs);

	trimRightInPlace(trimed);

	poco_assert(!trimed.size() <= 0);

	delete cs;
}


bool DatabaseManager::isConnected() {
	poco_assert(_conn);
	return (PQstatus(_conn) == CONNECTION_OK);
}

void DatabaseManager::shutdown(){
	ElogServer::getLogger().log("shutting down database connection");
	if (PQstatus(_conn) == CONNECTION_OK){
		PQfinish(_conn);
		ElogServer::getLogger().log("database connection terminated");
	}
}

std::string DatabaseManager::getUUID() {
	ElogServer::getLogger().log("generating uuid");

	UUIDGenerator& generator = UUIDGenerator::defaultGenerator();

	UUID uuid(generator.create());

	ElogServer::getLogger().log("uuid generated [" + uuid.toString() + "]");


	return uuid.toString();
}

