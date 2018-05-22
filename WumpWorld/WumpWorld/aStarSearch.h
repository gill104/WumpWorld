#pragma once
#include "FileInput.h"
#include "pQueue.h"
#include<queue>
class AstarSearch
{
private:
	std::vector<FileInput::Box> targetList;
	std::queue<FileInput::Box> qBox;
	std::string pathTaken;

public:
	AstarSearch(FileInput);

	void breadthFirstSearch();
	int getNeighbors(FileInput::Box);
	void djikstrasSearch();
};