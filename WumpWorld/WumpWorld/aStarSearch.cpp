#include "aStarSearch.h"
using namespace std;

AstarSearch::AstarSearch(FileInput map1)
{
	targetList = map1.giveBoxInfo();
	qBox.push(targetList[0]); // start of the bfs
	std::cout << "location start: " << targetList[0].location << std::endl;
	breadthFirstSearch();
}
void AstarSearch::breadthFirstSearch()
{
	
	FileInput::Box poppedInfo;
	while (!qBox.empty())
	{
		poppedInfo = qBox.front();
		qBox.pop();

		pathTaken = std::to_string(poppedInfo.location);
		std::cout << "start: " << pathTaken << "-> ";
		targetList[poppedInfo.location].visited = true;
		///poppedInfo.visited = true;
		for (int x = 0; x < poppedInfo.neighbors.size(); x++)
		{
			if (poppedInfo.neighbors[x] > 0)
			{
				if (targetList[poppedInfo.neighbors[x]].visited == false)
				{
					qBox.push(targetList[poppedInfo.neighbors[x]]);
					targetList[poppedInfo.neighbors[x]].visited = true;
					std::cout << poppedInfo.neighbors[x] << ", ";
				}
			}
			
		}
		std::cout << std::endl;
	}

}
void AstarSearch::djikstrasSearch()
{
	pQueue pQ;
	std::vector<int> neededNeighbors;
	targetList[0].currentDistance = 0;

	if (targetList[0].neighbors.size() > 0)
	{
		for (int x = 0; x < targetList[0].neighbors.size(); x++)
		{
			//give them a distance;
			if (targetList[0].neighbors[x] > 0)
			{
				std::cout << "x: " << x << std::endl;
				std::cout << targetList[0].neighbors[x] << "   " << targetList[0].weights[x] << std::endl;
				targetList[targetList[0].neighbors[x]].currentDistance += targetList[0].weights[x];
				pQ.enqueue(targetList[targetList[0].neighbors[x]]);
			}
		}
	}

	while (!pQ.empty())
	{
		//grab shorest Distance from pQ
		FileInput::Box smallest = pQ.dequeue();

		//find neighbors of smallest

	}
//	pQ.enqueue(targetList);
}

