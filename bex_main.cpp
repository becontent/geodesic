// Copyright 2017 - Robert J. Erickson
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std; 

int main(int argc, char **argv)
{
	cout << "hello world" << endl; 
	::testing::InitGoogleTest(&argc, argv); 
	int rval = RUN_ALL_TESTS(); 

    return rval;
}

