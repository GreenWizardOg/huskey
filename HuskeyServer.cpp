/*
 * HuskeyServer.cpp
 *
 * Main class for managing tasks, defining options and displaying help
 *
 *  Created on: June 30, 2011
 *      Author: barryodriscoll
 */

#include "HuskeyServer.hpp"
#include "InfoTask.hpp"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Logger.h"
#include "ApplicationWrapper.hpp"
#include "TaskManagerWrapper.hpp"
#include "LogManager.hpp"
#include "LoggerWrapper.hpp"

using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::Logger;

void HuskeyServer::initialize(Application& self)
{
	loadConfiguration(); // load default configuration files, if present
	ServerApplication::initialize(self);
	LogManager logger = getLogger();
	logger.log("starting up");
}

void HuskeyServer::uninitialize()
{
	getLogger().log("shutting down");
	ServerApplication::uninitialize();
}

void HuskeyServer::defineOptions(OptionSet& options)
{
	ServerApplication::defineOptions(options);

	options.addOption(
			Option("help", "h", "display help information on command line arguments, commands: 'info', 'listen', 'start' ")
			.required(false)
			.repeatable(false)
			.callback(OptionCallback<HuskeyServer>(this, &HuskeyServer::handleHelp)));
}

void HuskeyServer::handleHelp(const std::string& name, const std::string& value)
{
	_helpRequested = true;
	displayHelp();
	stopOptionsProcessing();
}

void HuskeyServer::displayHelp()
{
	HelpFormatter helpFormatter(options());
	helpFormatter.setCommand(commandName());
	helpFormatter.setUsage("OPTIONS");
	helpFormatter.setHeader("Huskey, for those conversations you hope no one knows about...");
	helpFormatter.setFooter("Remember, this is only a piece of software, it can be cracked\n or they could have a key logger built into your keyboard...");
	helpFormatter.format(std::cout);
}


void HuskeyServer::performWork(ITaskManager * taskManagerWrapper) {
	if (!_helpRequested){

		taskManagerWrapper->startTasks(new InfoTask(new ApplicationWrapper, 5));

		waitForTerminationRequest();

		taskManagerWrapper->killAndCleanTasks();
	}
}

int HuskeyServer::main(const std::vector<std::string>& args)
{
	TaskManagerWrapper taskManagerWrapper;

	ITaskManager * pointerToTaskManagerWrapper = &taskManagerWrapper;

	performWork(pointerToTaskManagerWrapper);

	return Application::EXIT_OK;
}


namespace
{
	static SingletonLogger singletonLogger(new LoggerWrapper);
}

LogManager& HuskeyServer::getLogger()
{
	return *singletonLogger.get();
}

//only for tests
void HuskeyServer::setupMockLogger(ILogger * logger){
	singletonLogger.set(logger);
}
