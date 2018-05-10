#pragma once
#include<vector>
#include<iostream>
#include<string>

#include "FileInput.h"

class WorldMap
{
private:
	std::vector<FileInput::Box> gridData;
public:
	WorldMap(FileInput);
	void displayWorld(FileInput);
	void giveInfo(FileInput);
};

