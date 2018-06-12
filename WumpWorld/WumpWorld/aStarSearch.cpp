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
	//enqueue starting
	//dequeue. have priority Q erase
	//input dequeued neighbors(non-visited only)
	//finish upon entering goal
	for (int x = 0; x < targetList.size(); x++)
	{
		targetList[x].visited = false;
	}
	pQueue pQ;
	std::vector<int> neededNeighbors;

	targetList[0].currentDistance = 0;
	pQ.enqueue(targetList[0]);
	std::string vistedList = "";

	while (!pQ.empty())
	{
		std::cout <<"pqSize: " <<  pQ.size() << std::endl;
		//grab shorest Distance from pQ
		int smallest = pQ.dequeue();

		if (targetList[smallest].visited == true)
		{
			smallest = pQ.dequeue();
		}
		vistedList += std::to_string(targetList[smallest].location)  + " ";
		std::cout << vistedList << std::endl;
		std::cout << "Dequeued: " << targetList[smallest].location << std::endl;
	

		targetList[smallest].visited = true;
		std::cout << "marked Visited: " << targetList[smallest].location << std::endl;

		pQ.erase();

		if (targetList[smallest].gold == true)
		{
			std::cout << vistedList << std::endl;
			std::cout << "GOLD FOUND" << std::endl;
			
			std::system("pause");
			break;
		}
		
		//find neighbors of smallest
		std::cout << "adding [ " << targetList[smallest].location << " ] neighbors" << std::endl;

		int neighborLoc;
		for (int x = 0; x < targetList[smallest].neighbors.size(); x++)
		{
			//give them a distance;
			neighborLoc = targetList[smallest].neighbors[x];
			if (neighborLoc > 0)
			{
				if (targetList[neighborLoc].visited == false)
				{
					//has no current distance initialized
					if (targetList[neighborLoc].currentDistance == 100000)
					{
						std::cout << "current: " << targetList[smallest].location << std::endl;
						std::cout << "neighbor: " << targetList[neighborLoc].location << std::endl;

						targetList[neighborLoc].currentDistance = targetList[smallest].weights[x];
						std::cout << "had no distance" << std::endl;
					}
					else //checks new current distance and replaces if smaller distance
					{
						int oldNum = targetList[neighborLoc].currentDistance;
						int newNum = targetList[neighborLoc].currentDistance += targetList[smallest].weights[x];

						if (newNum < oldNum)
						{
							targetList[neighborLoc].currentDistance = newNum;
							std::cout << ">>>>>>Changed Distance" << std::endl;
						}
					}
					//targetList[targetList[smallest].neighbors[x]].currentDistance += targetList[smallest].weights[x];

					pQ.enqueue(targetList[neighborLoc]);
					std::cout << "Inserted: " << targetList[neighborLoc].location << std::endl;


				}
				else
				{
					std::cout << smallest << " is vistited" << std::endl;
				}
			}
			else
			{
				std::cout << neighborLoc << " not valid number;" << std::endl;
			}
			
		}
		//check -- do not add visited neighbors.
		std::system("pause");
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
	}
//	pQ.enqueue(targetList);
}

