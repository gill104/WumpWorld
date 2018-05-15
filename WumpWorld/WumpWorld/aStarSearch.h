#pragma once
#include "FileInput.h"
#include<queue>
class AstarSearch
{
private:
	std::vector<FileInput::Box> targetList;
	
public:
	AstarSearch(FileInput);

	void breadthFirstSearch();
	int getNeighbors(FileInput::Box);

};