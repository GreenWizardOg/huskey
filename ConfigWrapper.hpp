/*
 * ConfigWrapper.hpp
 *
 *  Created on: Apr 4, 2011
 *      Author: barryodriscoll
 */

#ifndef CONFIGWRAPPER_HPP_
#define CONFIGWRAPPER_HPP_

#include "IConfig.hpp"
#include "Poco/Exception.h"
#include "Poco/Foundation.h"
#include "Poco/Util/Application.h"
#include <iostream>

using Poco::AssertionViolationException;
using Poco::Util::Application;

class ConfigWrapper : public IConfig {
public:
	std::string getProperty(std::string * property) throw(AssertionViolationException) {
		poco_assert(Application::instance().config().has(*property));
		return Application::instance().config().getString(*property);
	}
};

#endif /* CONFIGWRAPPER_HPP_ */
