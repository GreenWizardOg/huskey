/*
 * ElogServer.cpp
 *
 * Main class for managing tasks, defining options and displaying help
 *
 *  Created on: Mar 30, 2011
 *      Author: barryodriscoll
 */

#include "ElogServer.hpp"
#include "ElogTask.hpp"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Logger.h"
#include "ApplicationWrapper.hpp"
#include "TaskManagerWrapper.hpp"

using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::Logger;

void ElogServer::initialize(Application& self)
{
	loadConfiguration(); // load default configuration files, if present
	ServerApplication::initialize(self);
	logger().information("starting up");
}

void ElogServer::uninitialize()
{
	logger().information("shutting down");
	ServerApplication::uninitialize();
}

void ElogServer::defineOptions(OptionSet& options)
{
	ServerApplication::defineOptions(options);

	options.addOption(
			Option("help", "h", "display help information on command line arguments")
			.required(false)
			.repeatable(false)
			.callback(OptionCallback<ElogServer>(this, &ElogServer::handleHelp)));
}

void ElogServer::handleHelp(const std::string& name, const std::string& value)
{
	_helpRequested = true;
	displayHelp();
	stopOptionsProcessing();
}

void ElogServer::displayHelp()
{
	HelpFormatter helpFormatter(options());
	helpFormatter.setCommand(commandName());
	helpFormatter.setUsage("OPTIONS");
	helpFormatter.setHeader("The eLog server designed to enable smart metering in any environment");
	helpFormatter.format(std::cout);
}


void ElogServer::performWork(ITaskManager * taskManagerWrapper) {
	if (!_helpRequested){

		taskManagerWrapper->startTasks(new ElogTask(new ApplicationWrapper, -1));

		waitForTerminationRequest();

		taskManagerWrapper->killAndCleanTasks();
	}
}

int ElogServer::main(const std::vector<std::string>& args)
{
	TaskManagerWrapper taskManagerWrapper;

	ITaskManager * pointerToTaskManagerWrapper = &taskManagerWrapper;

	performWork(pointerToTaskManagerWrapper);

	return Application::EXIT_OK;
}

