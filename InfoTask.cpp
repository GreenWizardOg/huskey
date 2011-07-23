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
	//TODO find out how to get ip address and write some fucking tests barry
	/* 'ifconfig | grep inet' command to get ip on my mac*/

	std::string commandLineOutput = getIP();
	std::string addy = stripAddress(commandLineOutput);

	HuskeyServer::getLogger().log("Displaying your ip info...");
	HuskeyServer::getLogger().log("[*** Your ip address is: " + addy + " ***]");


	HuskeyServer::getLogger().log("Completed info display task");
	//TODO for some reason this task just hangs afterwards, find out why and fix it

}


std::string InfoTask::stripAddress(std::string commandLineOutput)
{
	//TODO This is really shitty, replace with something better, with tests and error handling
	//This only works for 127.1.1.1 but than i have no internet access so fuck it
	//inet 127.0.0.1 netmask 0xff000000
	std::string result = commandLineOutput.substr(5,9);
	return result;
}

std::string InfoTask::getIP()
{
	std::string result = "";
	result = system("ifconfig | grep \"inet \" > IPAddy");

	HuskeyServer::getLogger().log("checking for ip address");
	/* 'ifconfig | grep inet' command to get ip on my mac*/
	return result;
}

