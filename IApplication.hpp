/*
 * IApplication.h
 *
 *  Created on: Mar 31, 2011
 *      Author: barryodriscoll
 */

#ifndef IAPPLICATION_H_
#define IAPPLICATION_H_

#include "Poco/Util/Application.h"
#include "Poco/Logger.h"

using Poco::Util::Application;
using Poco::Logger;
using Poco::Timespan;

class IApplication {
public:
	virtual void log(std::string *msg) = 0;
};

#endif /* IAPPLICATION_H_ */
