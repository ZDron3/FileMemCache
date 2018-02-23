#pragma once
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include "lru.cpp"
#include "multithread.h"
#include <map>
#include <sstream>
using namespace std;

class IMultiThreadReadWrite
{
public:
	virtual void Start() = 0;
};
