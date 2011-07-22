/*
 * InfoTask.cpp
 *
 *  Created on: June 20, 2011
 *      Author: barryodriscoll
 */

#include "Poco/Logger.h"
#include "InfoTask.hpp"
#include <iostream>
#include <exception>
#include "LogManager.hpp"
#include "LoggerWrapper.hpp"
#include "HuskeyServer.hpp"

using Poco::Task;

void InfoTask::runTask(){
	//TODO find out how to get ip address and put it in now and write some fucking tests barry
	/* 'ifconfig | grep inet' command to get ip on my mac*/

	std::string commandLineOutput = "inet 127.0.0.1 netmask 0xff000000";
	std::string addy = stripAddress(commandLineOutput);

	HuskeyServer::getLogger().log("Displaying your info: 5");
	HuskeyServer::getLogger().log("[*** Your ip address is: " + addy + " ***]");


	HuskeyServer::getLogger().log("Completed info display task");

}


std::string InfoTask::stripAddress(std::string commandLineOutput)
{
	//TODO This is really shitty, replace with something better, with tests and error handling
	//This only works for 127.1.1.1 but than i have no internet access so fuck it
	//inet 127.0.0.1 netmask 0xff000000
	std::string result = commandLineOutput.substr(5,9);
	return result;
}
