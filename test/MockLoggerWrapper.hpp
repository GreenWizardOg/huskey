/*
 * MockLoggerWrapper.hpp
 *
 *  Created on: Apr 6, 2011
 *      Author: barryodriscoll
 */

#ifndef MOCKLOGGERWRAPPER_HPP_
#define MOCKLOGGERWRAPPER_HPP_

#include "../ILogger.hpp"
#include "Poco/Exception.h"
#include "gmock/gmock.h"
#include <iostream>

using Poco::AssertionViolationException;

class MockLoggerWrapper : public ILogger {
public:
	//virtual void log(const std::string& msg) throw (AssertionViolationException) = 0;
	MOCK_METHOD1(mockLog, void(const std::string& msg));
	virtual void log(const std::string& msg) throw (AssertionViolationException) {
		mockLog(msg);
	}
};


#endif /* MOCKLOGGERWRAPPER_HPP_ */
