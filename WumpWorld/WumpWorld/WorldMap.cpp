#include "WorldMap.h"
/**
Readies the gridmap vector and fills with [ ] empty
character values for ease of display...may be a bit
more complex in future iterations
*/
WorldMap::WorldMap(FileInput map1)
{
	std::cout << "worldMap called" << std::endl;
}
void WorldMap::displayWorld(FileInput map1)
{
	gridData = map1.giveBoxInfo();
	std::cout << "DataSize: " << gridData.size() << std::endl;
	int count = 0;
	
	for (int x = 0; x < gridData.size(); x++)
	{
		if (count > map1.getBoardSize() - 1)
		{
			std::cout << std::endl;
			count = 0;
		}
		if (gridData[x].player)
		{
			std::cout << "[ p ]";
		}
		else if (gridData[x].gold)
		{
			std::cout << "[ G ]";
		}
		else if (gridData[x].pit)
		{
			std::cout << "[ # ]";
		}
		else if (gridData[x].wumpus)
		{
			std::cout << "[ W ]";
		}
		else
		{
			std::cout << "[ " << gridData[x].location << " ]";
		}
		count++;

	}
}
void WorldMap::giveInfo(FileInput map1)
{
	int userInput;
	std::cout << "Enter Location: ";
	std::cin >> userInput;
	while (userInput >= 0)
	{
		if (userInput < 0)
		{
			break;
		}
		std::cout << "Enter Location: ";
		std::cin >> userInput;

		std::cout << "boxName: " << gridData[userInput].location << std::endl;
		std::cout << "Player: " << gridData[userInput].player << std::endl;
		std::cout << "Gold: " << gridData[userInput].gold << std::endl;
		std::cout << "Wumpus: " << gridData[userInput].wumpus << std::endl;
	}
}