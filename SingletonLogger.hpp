/*
 * SingletonHolderWithConstructor.hpp
 *
 *  Created on: Apr 5, 2011
 *      Author: barryodriscoll
 */

#ifndef SINGLETONLOGGER_HPP_
#define SINGLETONLOGGER_HPP_

#include "Poco/Foundation.h"
#include "Poco/Mutex.h"
#include "LoggerWrapper.hpp"
#include "LogManager.hpp"
#include "ILogger.hpp"

using Poco::FastMutex;


class SingletonLogger {
public:
	SingletonLogger(ILogger * logger)
	{
		_pS = new LogManager(logger);
	}

	~SingletonLogger()
	{
		delete _pS;
	}

	LogManager * get(){
		FastMutex::ScopedLock lock(_m);
		poco_assert(_pS);
		return _pS;
	}
	void set(ILogger * logger){
		FastMutex::ScopedLock lock(_m);
		_pS = new LogManager(logger);
	}

private:
	LogManager * _pS;
	FastMutex _m;
};

#endif /* SINGLETONLOGGER_HPP_ */
