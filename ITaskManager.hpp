/*
 * ITaskManager.hpp
 *
 *  Created on: Mar 31, 2011
 *      Author: barryodriscoll
 */

#ifndef ITASKMANAGER_HPP_
#define ITASKMANAGER_HPP_

#include "Poco/Task.h"

using Poco::Task;

class ITaskManager {
public:
	virtual void startTasks(Task * task) = 0;
	virtual void killAndCleanTasks() = 0;
};

#endif /* ITASKMANAGER_HPP_ */
