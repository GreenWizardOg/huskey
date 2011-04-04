/*
 * ElogTask.cpp
 *
 *  Created on: Mar 30, 2011
 *      Author: barryodriscoll
 */

#include "Poco/Logger.h"
#include "ElogTask.hpp"
#include <iostream>
#include <exception>

using Poco::Task;

void ElogTask::runTask(){
	int current_runs = 0;

	while (!sleep(500) && (current_runs < _how_many_times || _how_many_times < 0))
	{
		current_runs++;
	    std::string *msg = new std::string("Elog daemon sitting idle...");
	    _app->log(msg);
	}
}

