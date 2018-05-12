#pragma once
#include<iostream>

class Player
{
private:
	int location;
	int rotation;
	int prevLocation;

public:
	Player();

	void setLocation(int);
	
	int getLocation();
	int getPrevLocation();




	int moveNorth(int);
	void moveNortheast();
	int moveEast();
	void moveSouthEast();
	int moveSouth(int);
	void moveSouthWest();
	int moveWest();
	void moveNorthWest();


};
