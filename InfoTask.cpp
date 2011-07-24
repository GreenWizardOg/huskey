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
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "LogManager.hpp"
#include "LoggerWrapper.hpp"
#include "HuskeyServer.hpp"
#include "StringUtils.hpp"

using Poco::Task;

void InfoTask::runTask(){
	//TODO write some fucking tests barry

	HuskeyServer::getLogger().log("checking for ip address");
	HuskeyServer::getLogger().log("Displaying your ip info...");

	FILE *fp;
	char outputLine[1035];


	fp = popen("ifconfig | grep 'inet '", "r");
	if (fp == NULL)
	{
	  HuskeyServer::getLogger().log("Unable to make system all to get ip addresses");
	}
	while (fgets(outputLine, sizeof(outputLine)-1, fp) != NULL) {
	  StringUtils stringUtils;
	  stringUtils.stripIpAddy(outputLine);
		//HuskeyServer::getLogger().log(std::string(outputLine));
	}

	pclose(fp);

	HuskeyServer::getLogger().log("[*** Your ip address is: XXX.XXX.XXX.XXX ***]");
	HuskeyServer::getLogger().log("Completed info display task");
	//TODO for some reason this task just hangs afterwards, find out why and fix it
	//     Starting to think this isn't a bug at all actually but we'll find out in good time
	//I think calling cancel is helping out with the hanging bug
	cancel();

}
