/*
 * test_ConfigManager.cpp
 *
 *  Created on: Mar 25, 2011
 *      Author: barryodriscoll
 */

#include "../ConfigManager.hpp"
#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "Poco/Exception.h"
#include "../IConfig.hpp"
#include "../ElogServer.hpp"
#include "../ILogger.hpp"
#include "MockLoggerWrapper.hpp"
#include <string>

using ::testing::_;
using ::testing::Throw;
using ::testing::Return;
using Poco::AssertionViolationException;

class MockConfigWrapper : public IConfig {
public:
	MOCK_METHOD1(getPropertyMock, std::string(std::string * property));

	virtual std::string getProperty(std::string * property) throw(AssertionViolationException)
	{
	    return getPropertyMock(property);
	}
};

class ConfigManagerTest : public testing::Test {
 protected:
	virtual void SetUp() {
		mockLogger = new MockLoggerWrapper;
		ILogger * pointerToMockLoggerWrapper = mockLogger;

		ElogServer::setupMockLogger(pointerToMockLoggerWrapper);

		mockConfig = new MockConfigWrapper;
		IConfig * pointerToMockConfig = mockConfig;
		fixture = new ConfigManager(pointerToMockConfig);
	  }

	virtual void TearDown() {
		delete mockConfig;
		delete fixture;
		delete mockLogger;
	}

	ConfigManager * fixture;
	MockConfigWrapper * mockConfig;
	MockLoggerWrapper * mockLogger;

};

TEST_F(ConfigManagerTest, TestGetPropertyThatExists) {
	EXPECT_CALL(*mockLogger, mockLog(_)).Times(1);
	EXPECT_CALL(*mockConfig, getPropertyMock(_)).Times(1).WillRepeatedly(Return(std::string("I was in the config file!")));

	EXPECT_EQ(std::string("I was in the config file!"), fixture->getProperty(new std::string("good_property")));
}

TEST_F(ConfigManagerTest, TestGetPropertyThatDoesNotExist) {
	AssertionViolationException exception;
	EXPECT_CALL(*mockConfig, getPropertyMock(_)).Times(1).WillOnce(Throw(exception));

	EXPECT_THROW(fixture->getProperty(new std::string("missing_property")), AssertionViolationException);
}

TEST_F(ConfigManagerTest, TestGetPropertyWithBadInput) {
	EXPECT_THROW(fixture->getProperty(new std::string("")), AssertionViolationException);
	EXPECT_THROW(fixture->getProperty(new std::string("    ")), AssertionViolationException);
	EXPECT_THROW(fixture->getProperty(new std::string("\n")), AssertionViolationException);
	EXPECT_THROW(fixture->getProperty(NULL), AssertionViolationException);
}

