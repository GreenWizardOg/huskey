/*
 * TaskManagerWrapper.hpp
 *
 *  Created on: Mar 31, 2011
 *      Author: barryodriscoll
 */

#ifndef TASKMANAGERWRAPPER_HPP_
#define TASKMANAGERWRAPPER_HPP_

#include "ITaskManager.hpp"
#include "Poco/TaskManager.h"

using Poco::TaskManager;

class TaskManagerWrapper : public ITaskManager {
public:
	TaskManagerWrapper(){
		_taskManager = new TaskManager;
	}

	void startTasks(Task * task) {
		_taskManager->start(task);
	}

	void killAndCleanTasks() {
		_taskManager->cancelAll();
		_taskManager->joinAll();
	}
private:
	TaskManager * _taskManager;
};

#endif /* TASKMANAGERWRAPPER_HPP_ */
