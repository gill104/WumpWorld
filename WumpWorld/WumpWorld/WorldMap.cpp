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

	/**
		+-------------+
		|[ + ][ # ]   |
		|{ G }   [ P ]|   
		|[ ~ ]   [ S ]|
		|    [ W ]    |
		+-------------+
	*/

	//detailed grid
	int counter = 0;
	for (int globalX = 0; globalX < gridData.size(); globalX += map1.getBoardSize())
	{
		for (int rows = 0; rows < 6; rows++)
		{
			counter = globalX;
			for (int columns = 0; columns < map1.getBoardSize(); columns++)
			{
				//EVERY 6 ROWS is a new Box
				//every row  contains specific condition
				//1st row is always default top row
				//2nd row is pit 
				//3rd row is gold / player
				//4th row is breeze
				//5th row is wumpus
				//std::cout << length << std::endl;
				if (rows == 0 && columns > 0)
				{
					if (counter < 10)
					{
						std::cout << "-------" << counter << "------+";
					}
					else
					std::cout << "------" <<  counter <<  "------+";
				}
				else if ((rows == 0 && columns == map1.getBoardSize() - 1) || rows == 0)
				{
					if (counter < 10)
					{
						std::cout << "+-----" << counter << "-------+";
					}
					else
					std::cout << "+----" << counter << "-------+";
				}

				if (rows == 1 && columns > 0)
				{
					if (gridData[counter].shiny && gridData[counter].pit)
					{
						std::cout << "[ + ][ # ]   |";
					}
					else if (gridData[counter].pit)
					{
						std::cout << "    [ # ]     |";
					}
					else if (gridData[counter].shiny)
					{
						std::cout << "[ + ]         |";
					}
					else {
						std::cout << "              |";
					}
				}
				else if ((rows == 1 && columns == map1.getBoardSize() - 1) || rows == 1)
				{
					if (gridData[counter].shiny && gridData[counter].pit)
					{
						std::cout << "|[ + ][ # ]   |";
					}
					else if (gridData[counter].shiny)
					{
						std::cout << "|[ + ]        |";
					}
					else if (gridData[counter].pit)
					{
						std::cout << "|   [ # ]     |";
					}
					else
					{
						std::cout << "|             |";
					}
				}

				if (rows == 2 && columns > 0)
				{
					if (gridData[counter].gold && gridData[counter].player)
					{
						std::cout << "{ G }    [ P ]|";
					}
					else if (gridData[counter].gold)
					{
						std::cout << "{ G }         |";
					}
					else if (gridData[counter].player)
					{
						if (counter < 10)
						{
							std::cout << "     " << counter << "   [ P ]|";
						}
						else
							std::cout << "     " << counter <<  "  [ P ]|";
					}
					else
					{
						std::cout << "              |";
					}
				}
				else if ((rows == 2 && columns == map1.getBoardSize() - 1) || rows == 2)
				{
					if (gridData[counter].gold && gridData[counter].player)
					{
						std::cout << "|{ G }   [ P ]|";
					}
					else if (gridData[counter].gold)
					{
						std::cout << "|{ G }       |";
					}
					else if (gridData[counter].player)
					{
						std::cout << "|        [ P ]|";
					}
					else {
						std::cout << "|             |";
					}
				}

				if (rows == 3 && columns > 0)
				{
					if (gridData[counter].breeze && gridData[counter].stench)
					{
						std::cout << "[ ~ ]    [ S ]|";
					}
					else if (gridData[counter].breeze)
					{
						std::cout << "[ ~ ]         |";
					}
					else if (gridData[counter].stench)
					{
						std::cout << "         [ S ]|";
					}
					else
					{
						std::cout << "              |";
					}
				}
				else if ((rows == 3 && columns == map1.getBoardSize() - 1) || rows == 3)
				{
					if (gridData[counter].breeze && gridData[counter].stench)
					{
						std::cout << "|[ ~ ]  [ S ]|";
					}
					else if (gridData[counter].breeze)
					{
						std::cout << "|[ ~ ]        |";
					}
					else if (gridData[counter].stench)
					{
						std::cout << "|       [ S ]|";
					}
					else {
						std::cout << "|             |";
					}
				}

				if (rows == 4 && columns > 0)
				{
					if (gridData[counter].wumpus)
						std::cout << "    [ W ]     |";
					else {
						std::cout << "              |";
					}
				}
				else if ((rows == 4 && columns == map1.getBoardSize() - 1) || rows == 4)
				{
					if (gridData[counter].wumpus)
					{
						std::cout << "|   [ W ]     |";
					}
					else
					{
						std::cout << "|             |";
					}
				}

				if (rows == 5 && columns > 0)
				{
					std::cout << "              |";
				}
				else if ((rows == 5 && columns == map1.getBoardSize() - 1) || rows == 5)
				{
					std::cout << "|             |";
				}
				counter++;
			}
			

			std::cout << std::endl;

		}
	}
	//minigrid
	/**
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
	*/
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