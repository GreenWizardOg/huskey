/*
 * test_ElogTask.cpp
 *
 *  Created on: Mar 30, 2011
 *      Author: barryodriscoll
 */

#include "../ElogTask.hpp"
#include "../IApplication.hpp"
#include "Poco/Timespan.h"
#include "Poco/Logger.h"
#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "MockLoggerWrapper.hpp"
#include "../ILogger.hpp"
#include "../ElogServer.hpp"
#include <iostream>

using Poco::Logger;

using ::testing::Return;
using ::testing::_;

class MockApplication : public IApplication {
public:
	//virtual void log(std::string *msg) = 0;
	MOCK_METHOD1(log, void(std::string *));
};

TEST(ElogTaskTest, TestRunTaskCallsLogger) {
	MockApplication mockApp;

	IApplication * pointerToMockApp = &mockApp;

	int times_run = 2;

	ElogTask fixture(pointerToMockApp, times_run);

	MockLoggerWrapper mockLoggerWrapper;
	ILogger * pointerToMockLoggerWrapper = &mockLoggerWrapper;

	EXPECT_CALL(mockLoggerWrapper, mockLog(_)).Times(times_run);

	ElogServer::setupMockLogger(pointerToMockLoggerWrapper);

	//execute fixture
	fixture.runTask();
}

