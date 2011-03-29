/*
 * test_ConfigManager.cpp
 *
 *  Created on: Mar 25, 2011
 *      Author: barryodriscoll
 */

#include "../ConfigManager.h"
#include <gtest/gtest.h>

TEST(ConfigManagerTest, TestAddWorks) {
	ConfigManager* fixture = new ConfigManager;

	EXPECT_EQ(4, fixture->add(2,2));
	ASSERT_EQ(4, fixture->add(2,2));

	delete fixture;
	fixture = NULL;

}
