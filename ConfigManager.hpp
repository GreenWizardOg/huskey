/*
 * ConfigManager.hpp
 *
 *  Created on: Apr 1, 2011
 *      Author: barryodriscoll
 */

#ifndef CONFIGMANAGER_HPP_
#define CONFIGMANAGER_HPP_

#include <iostream>
#include "Poco/Exception.h"
#include "IConfig.hpp"

using Poco::AssertionViolationException;

class ConfigManager {
public:
	ConfigManager(IConfig * config) : _config(config) {

	}

	std::string getProperty(std::string * property) throw(AssertionViolationException);

private:
	IConfig * _config;
};

#endif /* CONFIGMANAGER_HPP_ */
