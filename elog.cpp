//============================================================================
// Name        : elog.cpp
// Author      : Barry O'Driscoll
// Version     :
// Copyright   :
// Description : elog main file
//============================================================================

#include <iostream>
#include <string>

#include "ConfigManager.h"


using namespace std;


int main()
{
	cout << "HelloWorld" << endl;

	ConfigManager* configManager = new ConfigManager;

	cout << "Adding 2 + 2" << endl;
	cout << "Result: " << configManager->add(2,2) << endl;
}
