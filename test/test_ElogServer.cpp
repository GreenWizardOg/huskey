/*
 * test_ElogServer.cpp
 *
 *  Created on: Mar 30, 2011
 *      Author: barryodriscoll
 */

#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "../ElogServer.hpp"
#include "../ITaskManager.hpp"
#include "Poco/Thread.h"
#include "Poco/RunnableAdapter.h"
#include <iostream>

using Poco::Thread;
using ::testing::_;

class Killer
{
public:
	Killer(ElogServer * server) : _server(server) {

	}

	void kill()
	{
		Thread::sleep(2000);
		_server->terminate();
	}
private:
	ElogServer * _server;
};

class MockTaskManager : public ITaskManager {
public:
	//virtual void startTasks(Task * task) = 0;
	MOCK_METHOD1(startTasks, void(Task * task));

	//virtual void killAndCleanTasks() = 0;
	MOCK_METHOD0(killAndCleanTasks, void());
};

class ElogServerTest : public testing::Test {
 protected:
	virtual void SetUp() {
		fixture = new ElogServer();
	  }

	virtual void TearDown() {
		fixture->terminate();
		delete fixture;
	}

	ElogServer * fixture;

};


TEST_F(ElogServerTest, TestServerPerformWork) {
	MockTaskManager mockTaskManager;
	ITaskManager * pointerToMockTaskManager = &mockTaskManager;

	// Expected Calls on Mocks;

	EXPECT_CALL(mockTaskManager, startTasks(_)).Times(1);
	EXPECT_CALL(mockTaskManager, killAndCleanTasks()).Times(1);

	Killer killer(fixture);
	Poco::RunnableAdapter<Killer> runnable(killer, &Killer::kill);

	Poco::Thread thread;
	thread.start(runnable);


	// Run Fixture;
	fixture->performWork(pointerToMockTaskManager);
}

TEST_F(ElogServerTest, TestServerNotPerformWorkWithHelpRequested) {
	fixture->setHelpRequested(true);

	MockTaskManager mockTaskManager;
	ITaskManager * pointerToMockTaskManager = &mockTaskManager;

	// Run Fixture;
	fixture->performWork(pointerToMockTaskManager);
}

