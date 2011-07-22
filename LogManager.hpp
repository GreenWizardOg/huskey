/*
 * LogManager.hpp
 *
 *  Created on: Apr 4, 2011
 *      Author: barryodriscoll
 */

#ifndef LOGMANAGER_HPP_
#define LOGMANAGER_HPP_

#include "Poco/Exception.h"
#include <iostream>
#include "ILogger.hpp"
#include "LoggerWrapper.hpp"

using Poco::AssertionViolationException;

class LogManager {
public:
	LogManager(ILogger * logger) : _logger(logger) {

	}

	void init(ILogger * logger);

	void log(const std::string& msg) throw (AssertionViolationException);

private:
	ILogger * _logger;
};

#endif /* LOGMANAGER_HPP_ */
