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
	//TODO write an intergration test in bash to make sure this all works
	ServerApplication::defineOptions(options);

	options.addOption(
			Option("help", "h", "display help information on command line arguments, commands: 'info', 'listen', 'start' ")
			.required(false)
			.repeatable(false)
			.callback(OptionCallback<HuskeyServer>(this, &HuskeyServer::handleHelp)));

	options.addOption(
			Option("info", "i", "get information about your ip address and randomly picked port number.\nNow tell your friend about it...")
			.required(false)
			.repeatable(false)
			.callback(OptionCallback<HuskeyServer>(this, &HuskeyServer::handleInfo)));

	options.addOption(
			Option("listen", "l", "Listen for an incomming communication from the internet pipes")
			.required(false)
			.repeatable(false)
			.callback(OptionCallback<HuskeyServer>(this, &HuskeyServer::handleListen)));
}

void HuskeyServer::handleHelp(const std::string& name, const std::string& value)
{
	_helpRequested = true;
	displayHelp();
	stopOptionsProcessing();
}


void HuskeyServer::handleInfo(const std::string& name, const std::string& value)
{
	//TODO write a unit test for this
	HuskeyServer::getLogger().log("Handling an info request...");
	_infoRequested = true;
	stopOptionsProcessing();
}


void HuskeyServer::handleListen(const std::string& name, const std::string& value)
{
	//TODO figure out how to open a raw socket and listen on a particular port
	HuskeyServer::getLogger().log("Handling an listen request...");
	_listenRequested = true;
	stopOptionsProcessing();

}


void HuskeyServer::displayHelp()
{
	HelpFormatter helpFormatter(options());
	helpFormatter.setCommand(commandName());
	helpFormatter.setUsage("OPTIONS");
	helpFormatter.setHeader("Huskey, for those conversations you hope no one knows about...");
	helpFormatter.setFooter("Remember, this is only a piece of software, it be badly designed/written\nOr the man could have a key logger built into your keyboard...\n\n");
	helpFormatter.format(std::cout);
}

int HuskeyServer::main(const std::vector<std::string>& args)
{
	//TODO make sure exe can run on unix/windows/mac without any required libs

	HuskeyServer::getLogger().log("This will just sit here until you 'ctrl c' it or kill it ");

	TaskManagerWrapper taskManagerWrapper;

	if (_infoRequested)
	{
		HuskeyServer::getLogger().log("Handling an info request, some of this code has been written!");
		taskManagerWrapper.startTasks(new InfoTask(new ApplicationWrapper, 5));
	}

	if (_listenRequested)
	{
		HuskeyServer::getLogger().log("Handling an listen request, pity that code hasn't been written yet");
	}

	HuskeyServer::getLogger().log("Waiting to be killed");
	waitForTerminationRequest();
	HuskeyServer::getLogger().log("Clearning up tasks");
	taskManagerWrapper.killAndCleanTasks();

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
