/*
 * IConfig.hpp
 *
 *  Created on: Apr 4, 2011
 *      Author: barryodriscoll
 */

#ifndef ICONFIG_HPP_
#define ICONFIG_HPP_

#include <iostream>
#include "Poco/Exception.h"

using Poco::AssertionViolationException;

class IConfig {
public:
	virtual std::string getProperty(std::string * property) throw(AssertionViolationException) = 0;
};

#endif /* ICONFIG_HPP_ */
