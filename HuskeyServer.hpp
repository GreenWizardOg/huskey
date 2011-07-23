/*
 * HuskeyServer.hpp
 *
 *  Created on: June 30, 2011
 *      Author: barryodriscoll
 */

#ifndef HUSKEYSERVER_HPP_
#define HUSKEYSERVER_HPP_

#include "Poco/Util/ServerApplication.h"
#include "InfoTask.hpp"
#include "Poco/Util/OptionSet.h"
#include <iostream>
#include "ITaskManager.hpp"
#include "LogManager.hpp"
#include "SingletonLogger.hpp"

using Poco::Util::Application;
using Poco::Util::ServerApplication;
using Poco::Util::OptionSet;
using Poco::SingletonHolder;

class HuskeyServer: public ServerApplication
{
public:

	HuskeyServer(): _helpRequested(false), _infoRequested(false), _listenRequested(false)
	{
	}

	~HuskeyServer()
	{
	}

	void performWork(ITaskManager * taskManagerWrapper);

	//only for tests
	void setHelpRequested(bool helpRequested) {
		_helpRequested = helpRequested;
	}

	static LogManager& getLogger();
	static void setupMockLogger(ILogger * logger);

protected:
	void initialize(Application& self);

	void uninitialize();

	void defineOptions(OptionSet& options);

	void handleHelp(const std::string& name, const std::string& value);

	void handleInfo(const std::string& name, const std::string& value);

	void handleListen(const std::string& name, const std::string& value);

	void displayHelp();

	int main(const std::vector<std::string>& args);

private:
	bool _helpRequested;
	bool _infoRequested;
	bool _listenRequested;

};

#endif /* HUSKEYSERVER_HPP_ */
