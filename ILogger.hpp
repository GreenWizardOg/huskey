/*
 * ILogger.hpp
 *
 *  Created on: Apr 4, 2011
 *      Author: barryodriscoll
 */

#ifndef ILOGGER_HPP_
#define ILOGGER_HPP_

#include "Poco/Exception.h"
#include <string>

using Poco::AssertionViolationException;

class ILogger {
public:
	virtual void log(const std::string& msg) throw (AssertionViolationException) = 0;
};

#endif /* ILOGGER_HPP_ */
