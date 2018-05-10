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
		int effect;
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
protected:

public:
	//FileInput();
	/*FileInput(
	int size,
	Coor pLoc,
	int pRot,
	std::vector<Coor> pitLoc,
	Coor gLoc,
	Coor wLoc
	);*/

	FileInput(std::fstream& file);

	void gridAllInfo();
	int getBoardSize();


	int getGridOf(int typeOfInput, Coor value);
	std::vector<int> getGridOf(std::vector<Coor> value);
	int fancyMath(int , int , int , int );

	//control player location
	void movePlayer(char);
	void updatePlayer();

	//put on box vector
	void setUpBox();


	//displaying 
	std::vector<Box> giveBoxInfo();
};
