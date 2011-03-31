/*
 * ApplicationWrapper.hpp
 *
 *  Created on: Mar 31, 2011
 *      Author: barryodriscoll
 */

#ifndef APPLICATIONWRAPPER_HPP_
#define APPLICATIONWRAPPER_HPP_

#include "Poco/DateTimeFormatter.h"
#include "Poco/Util/Application.h"
#include "Poco/Timespan.h"
#include "Poco/Logger.h"
#include "IApplication.hpp"

using Poco::Util::Application;
using Poco::Timespan;
using Poco::Logger;
using Poco::DateTimeFormatter;


class ApplicationWrapper : public IApplication {
public:
	ApplicationWrapper() {

	}

	void log(std::string *msg) {
		Application::instance().logger().information(*msg + DateTimeFormatter::format(Application::instance().uptime()));
	}
};

#endif /* APPLICATIONWRAPPER_HPP_ */
