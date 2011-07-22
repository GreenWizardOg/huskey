/*
 * InfoTask.hpp
 *
 *  Created on: June 20, 2011
 *      Author: barryodriscoll
 */

#ifndef INFOTASK_HPP_
#define INFOTASK_HPP_

#include "Poco/Task.h"
#include "IApplication.hpp"
#include <string>

using Poco::Task;

class InfoTask: public Task
{
public:
	InfoTask(IApplication * app, int how_many_times) : Task("InfoTask")
	{
		_app = app;
	}

	void runTask();

private:
	std::string stripAddress(std::string commandLineOutput);
	IApplication * _app;
};



#endif /* INFOTASK_HPP_ */
