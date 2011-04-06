/*
 * LoggerWrapper.hpp
 *
 *  Created on: Apr 4, 2011
 *      Author: barryodriscoll
 */

#ifndef LOGGERWRAPPER_HPP_
#define LOGGERWRAPPER_HPP_

#include "ILogger.hpp"
#include "Poco/LocalDateTime.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Util/Application.h"
#include <string>

using Poco::LocalDateTime;
using Poco::DateTime;
using Poco::DateTimeFormat;
using Poco::DateTimeFormatter;
using Poco::Util::Application;

class LoggerWrapper: public ILogger {
public:
	void log(const std::string& msg) throw (AssertionViolationException){
		LocalDateTime now;
		Application::instance().logger().information("[" + DateTimeFormatter::format(now, DateTimeFormat::HTTP_FORMAT) + "] : " + msg);;
	}

};

#endif /* LOGGERWRAPPER_HPP_ */
