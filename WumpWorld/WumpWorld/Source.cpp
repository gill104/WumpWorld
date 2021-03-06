#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<random>

#include "FileInput.h"
#include "WorldMap.h"
#include "Player.h"
#include "aStarSearch.h"
#include "pQueue.h"

using namespace std;

int main()
{
	//pQueue pQ;
	
	/*Parameters for the world*/

	string string1; // thing here
	bool startGame = true;
	char userInput;
	fstream file("Text.txt");

	if (!file) {
		cout << "no file found" << endl;
		//system("pause");
		return 0;
	}
	FileInput worldInfo(file);

	/*
	-board size
	-player location
	-rotation location
	-pit location
	-gold location
	-wumpus location
	*/
	
	WorldMap map1(worldInfo);
	cout << endl;
	map1.displayWorld(worldInfo);

	AstarSearch astar(worldInfo);
	astar.djikstrasSearch();
	while (startGame)
	{
		
		cout << "Move: ";
		cin >> userInput;
		std::system("cls");
		
		switch (userInput)
		{
		case 'a':
			cout << "move left" << endl;
			worldInfo.movePlayer('a');
			map1.displayWorld(worldInfo);
			break;
		case 's':
			cout << "move left" << endl;
			worldInfo.movePlayer('s');
			map1.displayWorld(worldInfo);
			break;
		case 'd':
			cout << "move left" << endl;
			worldInfo.movePlayer('d');
			map1.displayWorld(worldInfo);
			break;
		case 'w':
			cout << "move left" << endl;
			worldInfo.movePlayer('w');
			map1.displayWorld(worldInfo);
			break;
		case 'o':
			cout << "quit" << endl;
			break;
		case 'i':
		
			map1.displayWorld(worldInfo);
			map1.giveInfo(worldInfo);
			break;
		default:
			cout << "unknown input" << endl;
			break;
		}
	}
	//system("pause");
	return 0;
}
