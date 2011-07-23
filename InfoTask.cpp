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

	HuskeyServer::getLogger().log("checking for ip address");

	HuskeyServer::getLogger().log("Displaying your ip info...");
	HuskeyServer::getLogger().log("[*** Your ip address is: XXX.XXX.XXX.XXX ***]");


	HuskeyServer::getLogger().log("Completed info display task");
	//TODO for some reason this task just hangs afterwards, find out why and fix it

}
