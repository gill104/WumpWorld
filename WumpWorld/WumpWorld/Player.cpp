#include "Player.h"

Player::Player()
{
	location = -1;
	rotation = -99;
	prevLocation = -1;
}
void Player::setLocation(int loc)
{
	location = loc;
}

int Player::getPrevLocation()
{
	return prevLocation;
}
int Player::moveWest()
{
	prevLocation = location;
	location -= 1;
	std::cout << "location: " << location << std::endl;
	return location;
}
int Player::moveEast()
{
	prevLocation = location;
	location += 1;
	std::cout << "location: " << location << std::endl;
	return location;
}
int Player::moveSouth(int size)
{
	prevLocation = location;
	location += size;
	std::cout << "location: " << location << std::endl;
	return location;
}
int Player::moveNorth(int size)
{
	prevLocation = location;
	location -= size;
	std::cout << "location: " << location << std::endl;
	return location;
}