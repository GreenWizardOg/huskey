/*
 * test_LogManager.cpp
 *
 *  Created on: Apr 4, 2011
 *      Author: barryodriscoll
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Poco/Exception.h"
#include "../LogManager.hpp"
#include "../ILogger.hpp"
#include "MockLoggerWrapper.hpp"
#include <iostream>
#include <string>

using Poco::AssertionViolationException;
using Poco::NullPointerException;
using ::testing::_;


class LogManagerTest : public testing::Test {
 protected:
	virtual void SetUp() {
		mockLoggerWrapper = new MockLoggerWrapper;
		ILogger * pointerToMockLoggerWrapper = mockLoggerWrapper;
		fixture = new LogManager(pointerToMockLoggerWrapper);
	  }

	virtual void TearDown() {
		delete mockLoggerWrapper;
		delete fixture;
	}

	LogManager * fixture;
	MockLoggerWrapper * mockLoggerWrapper;
};

TEST_F(LogManagerTest, TestThatGoodStringIsLogged) {
	EXPECT_CALL(*mockLoggerWrapper, mockLog(_)).Times(1);
	fixture->log("log this line");
}

TEST_F(LogManagerTest, TestThatBadInputIsHandled) {
	EXPECT_THROW(fixture->log(""), AssertionViolationException);
	EXPECT_THROW(fixture->log("    "), AssertionViolationException);
	EXPECT_THROW(fixture->log("\n"), AssertionViolationException);
}
