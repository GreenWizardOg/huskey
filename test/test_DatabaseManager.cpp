/*
 * test_DatabaseManager.cpp
 *
 *  Created on: Apr 7, 2011
 *      Author: barryodriscoll
 */

#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "../DatabaseManager.hpp"
#include "Poco/Exception.h"
#include "../ElogServer.hpp"
#include "../ILogger.hpp"
#include "MockLoggerWrapper.hpp"

using Poco::AssertionViolationException;
using ::testing::_;

class DatabaseManagerTest : public testing::Test {
 protected:
	virtual void SetUp() {
		fixture = new DatabaseManager();

		mockLogger = new MockLoggerWrapper;
		ILogger * pointerToMockLoggerWrapper = mockLogger;
		ElogServer::setupMockLogger(pointerToMockLoggerWrapper);
	  }

	virtual void TearDown() {
		fixture->shutdown();
		delete fixture;
		delete mockLogger;
	}

	DatabaseManager * fixture;
	MockLoggerWrapper * mockLogger;
};


TEST_F(DatabaseManagerTest, TestInsertingAndSelectingSingleData){
	EXPECT_CALL(*mockLogger, mockLog(_)).Times(12);
	fixture->init("postgres", "wulfpack", "elog_test");
	ASSERT_TRUE(fixture->isConnected());

	fixture->run("INSERT INTO DEREK_TABLE values(0, 'Limerick');");

	ASSERT_EQ("Limerick", fixture->run("SELECT name FROM DEREK_TABLE;"));

}
TEST_F(DatabaseManagerTest, TestLoadingConfig){
	EXPECT_CALL(*mockLogger, mockLog(_)).Times(5);
	fixture->init("postgres", "wulfpack", "elog_test");
	ASSERT_TRUE(fixture->isConnected());
}
TEST_F(DatabaseManagerTest, TestLoadingConfigWithBadInput){
	EXPECT_CALL(*mockLogger, mockLog(_)).Times(2);
	ASSERT_THROW(fixture->init("   ", "", "\n"), AssertionViolationException);
}
TEST_F(DatabaseManagerTest, TestLoadingConfigWithBadDetails){
	EXPECT_CALL(*mockLogger, mockLog(_)).Times(4);
	ASSERT_THROW(fixture->init("Munster", "Paul", "Legend"), AssertionViolationException);
}
TEST_F(DatabaseManagerTest, TestingInitTwiceThrowsException){
	EXPECT_CALL(*mockLogger, mockLog(_)).Times(6);
	fixture->init("postgres", "wulfpack", "elog_test");
	ASSERT_TRUE(fixture->isConnected());
	ASSERT_THROW(fixture->init("postgres", "wulfpack", "elog_test"), AssertionViolationException);
}
TEST_F(DatabaseManagerTest, TestSendBadInput){
	EXPECT_CALL(*mockLogger, mockLog(_)).Times(4);
	ASSERT_THROW(fixture->run(""), AssertionViolationException);
	ASSERT_THROW(fixture->run("   "), AssertionViolationException);
	ASSERT_THROW(fixture->run("\n"), AssertionViolationException);
}
TEST_F(DatabaseManagerTest, TestSendBadSql){
	EXPECT_CALL(*mockLogger, mockLog(_)).Times(2);
	ASSERT_THROW(fixture->run("bad sql"), AssertionViolationException);
}
TEST_F(DatabaseManagerTest, TestGetUUID){
	EXPECT_CALL(*mockLogger, mockLog(_)).Times(5);
	std::string uuid_one = fixture->getUUID();
	std::string uuid_two = fixture->getUUID();
	ASSERT_NE(uuid_one, uuid_two);
}

