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
#include <iostream>

using Poco::Logger;

using ::testing::Return;
using ::testing::_;

class MockApplication : public IApplication {
public:
	//virtual void log(std::string *msg) = 0;
	MOCK_METHOD1(log, void(std::string *));
};

void do_test() {
	MockApplication mockApp;

	IApplication * pointerToMockApp = &mockApp;

	int times_run = 2;

	//set expectations on mock objects
	EXPECT_CALL(mockApp, log(_)).Times(times_run);

	ElogTask fixture(pointerToMockApp, times_run);

	//execute fixture
	fixture.runTask();
}

TEST(ElogServerTest, TestRunTaskCallsLogger) {
	do_test();
}

