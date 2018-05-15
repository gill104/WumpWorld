#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>

#include "Player.h"
class FileInput
{
public:
	struct Coor
	{
		friend std::ostream& operator<< (std::ostream& os, Coor c);
		int x;
		int y;
		Coor();
		Coor(int x, int y);
	};
	struct Box
	{
		int location;
		bool player;
		bool wumpus;
		bool gold;
		bool pit;
		bool breeze;
		bool stench;
		bool shiny;

		bool visited;

		std::vector<int> neighbors;
		Box();
	};
private:
	int bSize;
	Coor pLocation;
	int pRotation;
	std::vector<Coor> pitLocations;
	Coor gLocation;
	Coor wLocation;

	Player player;

	int gridPlayerLocation;
	int gridGoldLocation;
	int gridWumpusLocation;
	std::vector<int> gridPitLocations;

	std::vector<Box> gridBox;

	void addEffect(int, int);
	void addEffect(std::vector<int>);
	int *lowerBounds;
protected:
	void gridAllInfo();



	int getGridOf(int typeOfInput, Coor value);
	std::vector<int> getGridOf(std::vector<Coor> value);
	int fancyMath(int, int, int, int);
	void fillLowerBounds();

	//put on box vector
	void setUpBox();
	bool isWithinBounds(int,int,int);
	void getNeighbors(Box);

public:
	FileInput(std::fstream& file);
	int getBoardSize();

	//control player location
	void movePlayer(char);
	void updatePlayer();

	//displaying 
	std::vector<Box> giveBoxInfo();

};
