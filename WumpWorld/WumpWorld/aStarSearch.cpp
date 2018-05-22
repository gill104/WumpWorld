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
	pQueue pQ(FileInput::Box);
	pQ.enqueue(targetList[0].location);
	while (!pQ.empty())
	{
		//pQ.dequeue();
	}
}

