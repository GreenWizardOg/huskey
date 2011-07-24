/*
 * StringUtils.cpp
 *
 *  Created on: Jul 24, 2011
 *      Author: barryodriscoll
 */

#include "StringUtils.hpp"
#include "HuskeyServer.hpp"
#include <iostream>

std::string StringUtils::stripIpAddy(char* input)
{
	 //HuskeyServer::getLogger().log(std::string(input));
	 for (int nChar = 0; nChar < sizeof(input); nChar++)
	 {
		 std::string* output = new std::string(input);

		 HuskeyServer::getLogger().log("FUCK YOU");
		 delete output;
		 return "FUCK YOU C++";
	 }
}
