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

using Poco::Util::Application;
using Poco::Util::ServerApplication;
using Poco::Util::OptionSet;

class ElogServer: public ServerApplication
{
public:
	ElogServer(): _helpRequested(false)
	{
	}

	~ElogServer()
	{
	}

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
