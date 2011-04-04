/*
 * ConfigManager.cpp
 *
 *  Created on: Apr 1, 2011
 *      Author: barryodriscoll
 */

#include "ConfigManager.hpp"
#include "ConfigWrapper.hpp"
#include "Poco/String.h"
#include "Poco/Foundation.h"
#include <string>

using Poco::trimRightInPlace;
using Poco::AssertionViolationException;
using Poco::Util::Application;

std::string ConfigManager::getProperty(std::string * property) throw (AssertionViolationException) {
	//check if property is valid throw exception if bad

	poco_assert(property);

	std::string trimed(trimRightInPlace(*property));

	poco_assert(!trimed.size() <= 0);

	return _config->getProperty(property);
}
