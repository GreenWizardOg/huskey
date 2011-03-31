/*
 * ElogTask.hpp
 *
 *  Created on: Mar 31, 2011
 *      Author: barryodriscoll
 */

#ifndef ELOGTASK_HPP_
#define ELOGTASK_HPP_

#include "Poco/Task.h"
#include "IApplication.hpp"

using Poco::Task;

class ElogTask: public Task {
public:
	ElogTask(IApplication * app, int how_many_times) : Task("ElogTask"), _how_many_times(how_many_times) {
		_app = app;
	}

	void runTask();

private:
	int _how_many_times;
	IApplication * _app;
};



#endif /* ELOGTASK_HPP_ */
