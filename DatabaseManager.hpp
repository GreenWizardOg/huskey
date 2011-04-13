/*
 * DatabaseManager.hpp
 *
 *  Created on: Apr 7, 2011
 *      Author: barryodriscoll
 */

#ifndef DATABASEMANAGER_HPP_
#define DATABASEMANAGER_HPP_

#include "Poco/Data/Session.h"
#include "Poco/Exception.h"
#include <iostream>
#include "libpq-fe.h"


using Poco::AssertionViolationException;

class DatabaseManager {
public:
	void init(const std::string& username, const std::string& password, const std::string& database) throw (AssertionViolationException);

	void shutdown();

	bool isConnected();

	std::string run(const std::string& sql)  throw (AssertionViolationException);

	std::string getUUID();

private:

	void checkParameter(const std::string& parameter);

	PGconn * _conn;
};


#endif /* DATABASEMANAGER_HPP_ */
