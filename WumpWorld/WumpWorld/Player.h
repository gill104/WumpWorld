#pragma once
#include<iostream>

class Player
{
private:
	int location;
	int rotation;
	int prevLocation;
	int boardSize;

public:
	Player();

	void setLocation(int);
	
	int getLocation();
	int getPrevLocation();




	void moveNorth();
	void moveNortheast();
	void moveEast();
	void moveSouthEast();
	void moveSouth();
	void moveSouthWest();
	int moveWest();
	void moveNorthWest();


};
