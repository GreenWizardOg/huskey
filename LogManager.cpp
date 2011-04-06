/*
 * LogManager.cpp
 *
 *  Created on: Apr 4, 2011
 *      Author: barryodriscoll
 */

#include "Poco/String.h"
#include "Poco/Foundation.h"
#include "Poco/Exception.h"
#include "LogManager.hpp"
#include <string>
#include <cstring>

using Poco::trimRightInPlace;
using Poco::AssertionViolationException;
using Poco::NullPointerException;

void LogManager::log(const std::string& msg) throw (AssertionViolationException) {
	poco_assert(&msg);

	poco_assert(_logger);

	char* cs = new char[msg.length() + 1];

	std::strcpy(cs, msg.c_str());

	std::string trimed(cs);

	trimRightInPlace(trimed);

	poco_assert(!trimed.size() <= 0);

	_logger->log(msg);

	delete cs;
}
