/*
 * ElogServer.hpp
 *
 *  Created on: Mar 30, 2011
 *      Author: barryodriscoll
 */

#ifndef ELOGSERVER_HPP_
#define ELOGSERVER_HPP_

#include "Poco/Util/ServerApplication.h"
#include "ElogTask.hpp"
#include "Poco/Util/OptionSet.h"
#include <iostream>
#include "ITaskManager.hpp"
#include "LogManager.hpp"
#include "SingletonLogger.hpp"

using Poco::Util::Application;
using Poco::Util::ServerApplication;
using Poco::Util::OptionSet;
using Poco::SingletonHolder;

class ElogServer: public ServerApplication
{
public:

	ElogServer(): _helpRequested(false)
	{
	}

	~ElogServer()
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

	void displayHelp();

	int main(const std::vector<std::string>& args);

private:
	bool _helpRequested;

};

#endif /* ELOGSERVER_HPP_ */
