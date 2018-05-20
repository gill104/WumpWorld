#include "FileInput.h"

/**
Friend class in order to use << operator to output all
information to the screen.
*/

std::ostream& operator<< (std::ostream& os, FileInput::Coor c)
{
	os << c.x;
	os << c.y;

	return os;
}
/**
Default constructor for Coordinates
*/
FileInput::Coor::Coor()
{
	int x = 0;
	int y = 0;
}
/**
Constructor to save x and y values that
will be read in.
*/
FileInput::Coor::Coor(int x, int y)
{
	this->x = x;
	this->y = y;
}
FileInput::Box::Box() {
	std::cout << "Created New Box!" << std::endl;
	location = -1;
	player = false;
	wumpus = false;
	gold = false;
	pit = false;
	breeze = false;
	stench = false;
	shiny = false;

	visited = false;
}
/**
Reads from the file and sets the appropriate values
to each variable. Most are read in as [Coor] which
will later be converted to a [gridLocation] value.
*/
FileInput::FileInput(std::fstream& file)
{
	file >> this->bSize;

	file >> this->pLocation.x;

	file >> this->pLocation.y;

	file >> this->pRotation;

	std::string line;

	std::getline(file, line);

	/*collects gargage*/
	std::getline(file, line);

	std::stringstream ss(line);

	while (!ss.eof())
	{
		int value;
		FileInput::Coor pit;

		ss >> value;
		pit.x = value;

		ss >> value;
		pit.y = value;


		this->pitLocations.push_back(pit);
	}

	file >> this->gLocation.x;
	file >> this->gLocation.y;

	file >> this->wLocation.x;
	file >> this->wLocation.y;

	gridAllInfo();
	setUpBox();
	
	//addEffect(gridPitLocations);
	addEffect(gridGoldLocation, 1);
	addEffect(gridWumpusLocation, 2);
	addEffect(gridPitLocations);
	getNeighbors();
}
int FileInput::getBoardSize()
{
	return this->bSize;
}
void FileInput::gridAllInfo()
{
		
	    gridPlayerLocation = FileInput::getGridOf(0,this->pLocation);
		if (gridPlayerLocation != -1)
		{
			player.setLocation(gridPlayerLocation);
		}
	    gridPitLocations = FileInput::getGridOf(this->pitLocations);
		
	    gridGoldLocation = FileInput::getGridOf(1,this->gLocation);
		
	    gridWumpusLocation = FileInput::getGridOf(2, this->wLocation);
		

		lowerBounds = new int[bSize]; //for limit purposes
		fillLowerBounds();

		
}
/**
Uses the coordinate value of the given [Coor] converts it
with [fancyMath] and return the [gridLocation] of said
item.
*/
int FileInput::getGridOf(int typeOfInput, Coor value)
{
	int total;
	int gridLocation;

	switch (typeOfInput) {
	case 0:
		total = 0;
		gridLocation = fancyMath(value.x, value.y, getBoardSize(), total);
		return gridLocation;
	case 1:
		total = 0;
		gridLocation = fancyMath(value.x, value.y, getBoardSize(), total);
		return gridLocation;
	case 2:
		total = 0;
		gridLocation = fancyMath(value.x, value.y, getBoardSize(), total);;
		return gridLocation;
	default:
		std::cout << "error" << std::endl;
		break;
	}
}

void FileInput::checkLeftRightBounds(int gridLocation, int wantedgl, int type)
{
	if (type == 0)
	{
		if (!gridBox[wantedgl].pit)
		{
			gridBox[wantedgl].breeze = true;
			//gridBox[gridLocation].weights.push_back(25);
		}
		else
		{
			//gridBox[gridLocation].weights.push_back(200);
		}
	}
	else if (type == 1)
	{
		gridBox[wantedgl].shiny = true;
		//gridBox[gridLocation].weights.push_back(25);
	}
	else if (type == 2)
	{
		gridBox[wantedgl].stench = true;
		//gridBox[gridLocation].weights.push_back(100);
	}
	else
	{
		gridBox[gridLocation].neighbors.push_back(wantedgl);
		addWeights(gridLocation,wantedgl);
	}
}
void FileInput::addWeights(int gridLocation, int wantedgl)
{
	//gridBox[gridLocation].neighbors.push_back(wantedgl);
	if (checkForObsticle(wantedgl))//wumpus, pit
	{
		gridBox[gridLocation].weights.push_back(200);
	}
	else if (gridBox[wantedgl].gold)
	{
		gridBox[gridLocation].weights.push_back(5);
	}
	else if (gridBox[wantedgl].shiny)
	{
		gridBox[gridLocation].weights.push_back(20);
	}
	else if (gridBox[wantedgl].breeze)
	{
		if (gridBox[wantedgl].stench)
		{
			gridBox[gridLocation].weights.push_back(55);
			return;
		}
		gridBox[gridLocation].weights.push_back(40);
	}
	else if (gridBox[wantedgl].stench)
	{
		if (gridBox[wantedgl].breeze)
		{
			gridBox[gridLocation].weights.push_back(55);
			return;
		}
		gridBox[gridLocation].weights.push_back(40);
	}
	else
	{
		gridBox[gridLocation].weights.push_back(25);
	}
}
void FileInput::addEffect(int gridLocation, int type)
{
	/**
		neighbors as listed;
		WEST // EAST // NORTH // NORTHWEST // NORTHEAST // SOUTH // SOUTHWEST // SOUTHEAST

		Weights:
		Breeze - 40;\
					 55
		Stench - 40;/
		Shiny - 20;
		Nothing - 25;
		Pit - 200;
		Wumpus - 200;

	*/
	int tempLocation = gridLocation;
	int fullBoard = bSize * bSize;
	/*switch (type)
	{
	case 1:*/
		std::cout << "gold Location: " << gridGoldLocation << std::endl;
		//up
		//checking base left and right
		if (isWithinBounds(gridLocation, gridLocation - 1, 0))
		{
			checkLeftRightBounds(gridLocation, gridLocation - 1,type);
		}
		else
		{
			gridBox[gridLocation].weights.push_back(1000);
			gridBox[gridLocation].neighbors.push_back(-99);
		}
		if (isWithinBounds(gridLocation, gridLocation + 1, 0))
		{
			checkLeftRightBounds(gridLocation, gridLocation + 1, type);
		}
		else
		{
			gridBox[gridLocation].weights.push_back(1000);
			gridBox[gridLocation].neighbors.push_back(-99);
		}
		//if (isWithinBounds(gridLocation, gridLocation + 1, 0))
		//{
		//	if (type == 0)
		//		if (!gridBox[gridLocation + 1].pit)
		//		{
		//			gridBox[gridLocation + 1].breeze = true;
		//			gridBox[gridLocation].weights.push_back(25);
		//		}
		//		else
		//		{
		//			gridBox[gridLocation].weights.push_back(200);
		//		}
		//	else if (type == 1)
		//	{
		//		gridBox[gridLocation + 1].shiny = true;
		//		gridBox[gridLocation].weights.push_back(25);
		//	}
		//	else if (type == 2)
		//	{
		//		gridBox[gridLocation + 1].stench = true;
		//		gridBox[gridLocation].weights.push_back(100);
		//	}
		//	else
		//	{
		//		gridBox[gridLocation].neighbors.push_back(gridLocation + 1);
		//		if (checkForObsticle(gridLocation + 1))//wumpus, pit
		//		{
		//			gridBox[gridLocation].weights.push_back(200);
		//		}
		//		else//nothing
		//		{
		//			gridBox[gridLocation].weights.push_back(30);
		//		}
		//	}
		//		
		//}
		//if (isWithinBounds(gridLocation, gridLocation - 1, 0))
		//{
		//	if (type == 0)
		//		if (!gridBox[gridLocation - 1].pit)
		//		{
		//			gridBox[gridLocation - 1].breeze = true;
		//			gridBox[gridLocation].weights.push_back(25);
		//		}
		//		else
		//		{
		//			gridBox[gridLocation].weights.push_back(200);
		//		}
		//	if(type == 1)
		//		gridBox[gridLocation - 1].shiny = true;
		//		gridBox[gridLocation].weights.push_back(25);
		//	if(type == 2)
		//		gridBox[gridLocation - 1].stench = true;
		//		gridBox[gridLocation].weights.push_back(200);
		//	if(type == 3)
		//		gridBox[gridLocation].neighbors.push_back(gridLocation - 1);
		//	
		//}

		//checking north portion 
		tempLocation = gridLocation - bSize;
		if (isWithinBounds(gridLocation, tempLocation, 1))
		{
			if (type == 0)
				if (!gridBox[tempLocation].pit)
				{
					gridBox[tempLocation].breeze = true;
				}
			if (type == 1)
				gridBox[tempLocation].shiny = true;
			if (type == 2)
				gridBox[tempLocation].stench = true;
			if (type == 3)
			{
				gridBox[gridLocation].neighbors.push_back(tempLocation);
				addWeights(gridLocation, tempLocation);
			}
				
				
				
			//then check left and right sides
			if (isWithinBounds(tempLocation, tempLocation - 1, 0))
			{
				checkLeftRightBounds(gridLocation, tempLocation - 1, type);
			}
			else
			{
				gridBox[gridLocation].weights.push_back(1000);
				gridBox[gridLocation].neighbors.push_back(-99);
			}
			if (isWithinBounds(tempLocation, tempLocation + 1, 0))
			{
				checkLeftRightBounds(gridLocation, tempLocation + 1, type);
			}
			else
			{
				
					gridBox[gridLocation].weights.push_back(1000);
					gridBox[gridLocation].neighbors.push_back(-99);
				
				
			}
			/*if (isWithinBounds(tempLocation, tempLocation - 1, 0))
			{
				if (type == 0)
					if (!gridBox[tempLocation - 1].pit)
					{
						gridBox[tempLocation - 1].breeze = true;
					}
				if (type == 1)
					gridBox[tempLocation - 1].shiny = true;
				if (type == 2)
					gridBox[tempLocation - 1].stench = true;
				if (type == 3)
					gridBox[gridLocation].neighbors.push_back(tempLocation - 1);
				
			}
			if (isWithinBounds(tempLocation, tempLocation + 1, 0))
			{
				if (type == 0)
					if (!gridBox[tempLocation + 1].pit)
					{
						gridBox[tempLocation + 1].breeze = true;
					}
				if (type == 1)
					gridBox[tempLocation + 1].shiny = true;
				if (type == 2)
					gridBox[tempLocation + 1].stench = true;
				if (type == 3)
					gridBox[gridLocation].neighbors.push_back(tempLocation + 1);
			}*/
		}
		else
		{
			if (type == 3)
			{
				for (int x = 0; x < 3; x++) // cannot go north left right 
				{
					gridBox[gridLocation].weights.push_back(1000);
					gridBox[gridLocation].neighbors.push_back(-99);
				}
			}
			
		}
		// checking south portion 
		tempLocation = gridLocation + bSize;
		if (isWithinBounds(gridLocation, tempLocation, 1))
		{
			if (type == 0)
				if (!gridBox[tempLocation].pit)
				{
					gridBox[tempLocation].breeze = true;
				}
			if (type == 1)
				gridBox[tempLocation].shiny = true;
			if (type == 2)
				gridBox[tempLocation].stench = true;
			if (type == 3)
			{
				gridBox[gridLocation].neighbors.push_back(tempLocation);
				addWeights(gridLocation, tempLocation);
			}
			
			//then check left and right sides
			if (isWithinBounds(tempLocation, tempLocation - 1, 0))
			{
				checkLeftRightBounds(gridLocation, tempLocation - 1, type);
			}
			else
			{
				gridBox[gridLocation].weights.push_back(1000);
				gridBox[gridLocation].neighbors.push_back(-99);
			}
			if (isWithinBounds(tempLocation, tempLocation + 1, 0))
			{
				checkLeftRightBounds(gridLocation, tempLocation + 1, type);
			}
			else
			{
				gridBox[gridLocation].weights.push_back(1000);
				gridBox[gridLocation].neighbors.push_back(-99);
			}
			/*if (isWithinBounds(tempLocation, tempLocation - 1, 0))
			{
				if (type == 0)
					if (!gridBox[tempLocation - 1].pit)
					{
						gridBox[tempLocation - 1].breeze = true;
					}
				if (type == 1)
					gridBox[tempLocation - 1].shiny = true;
				if (type == 2)
					gridBox[tempLocation - 1].stench = true;
				if (type == 3)
					gridBox[gridLocation].neighbors.push_back(tempLocation - 1);
			}
			if (isWithinBounds(tempLocation, tempLocation + 1, 0))
			{
				if (type == 0)
					if (!gridBox[tempLocation + 1].pit)
					{
						gridBox[tempLocation + 1].breeze = true;
					}
				if (type == 1)
					gridBox[tempLocation + 1].shiny = true;
				if (type == 2)
					gridBox[tempLocation + 1].stench = true;
				if (type == 3)
					gridBox[gridLocation].neighbors.push_back(tempLocation + 1);
				
			}*/
		}
		else
		{
			if (type == 3)
			{
				for (int x = 0; x < 3; x++) // cannot go north left right 
				{
					gridBox[gridLocation].weights.push_back(1000);
					gridBox[gridLocation].neighbors.push_back(-99);
				}
			}
			
		}
}
bool FileInput::checkForObsticle(int gridLocation)
{
	if (gridBox[gridLocation].wumpus || gridBox[gridLocation].pit)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void FileInput::addEffect(std::vector<int> pitLoc)
{
	int fullBoard = bSize * bSize;
	for (int x = 0; x < pitLoc.size(); x++)
	{
		addEffect(pitLoc[x], 0);
	}
}
/**
[fancy math] recursive function -- essentially divides X
value summing the total amount of boardlengths needed.
Then adding the remainder, the y value. In order to get
a solid number for [gridLocation].
*/
int FileInput::fancyMath(int x, int y, int s, int total) {

	if (x <= 1) {
		//std::cout << "TOTAL::::::" << total << std::endl;
		return total + y;
	}
	else {
		//std::cout << "TOTAL::::::" << total << std::endl;
		return fancyMath(x - 1, y, s, total + s);
	}
}
/**
For each value in pitLocations get the coordinate x and y
throught the [fancy math] method to return [grid value]
Gets the grid value for the [pit] vector and adds it to
pitlocations for ease of access
*/
std::vector<int> FileInput::getGridOf(std::vector<Coor> value)
{
	int total;
	int gridLocation;
	/**

	*/
	for (FileInput::Coor x : value) {
		total = 0;
		gridLocation = fancyMath(x.x, x.y, getBoardSize(), total);
		gridPitLocations.push_back(gridLocation);
	}
	for (int z = 0; z < gridPitLocations.size(); z++)
	{
		std::cout << "Grid Value: " << gridPitLocations[z] << std::endl;
		//system("pause");
	}

	return gridPitLocations;
}
void FileInput::movePlayer(char direction)
{
	int tempGL;
	switch (direction)
	{
	case 'a':
		
		tempGL = player.moveWest();
		if (isWithinBounds(gridPlayerLocation,tempGL,0))
		{
			std::cout << "accepted" << std::endl;
			gridPlayerLocation = tempGL;
			updatePlayer();
		}
		else
		{
			player.setLocation(gridPlayerLocation);
		}
		break;
	case 's':
		tempGL = player.moveSouth(bSize);
		if (isWithinBounds(gridPlayerLocation,tempGL,1))
		{
			std::cout << "accepted" << std::endl;
			gridPlayerLocation = tempGL;
			updatePlayer();
		}
		else
		{
			player.setLocation(gridPlayerLocation);
		}
		break;
	case 'd':
		tempGL = player.moveEast();
		if (isWithinBounds(gridPlayerLocation,tempGL,0))
		{
			std::cout << "accepted" << std::endl;
			gridPlayerLocation = tempGL;
			updatePlayer();
		}
		else
		{
			player.setLocation(gridPlayerLocation);
		}
		break;
	case 'w':
		tempGL = player.moveNorth(bSize);
		if (isWithinBounds(gridPlayerLocation,tempGL, 1))
		{
			std::cout << "accepted" << std::endl;
			gridPlayerLocation = tempGL;
			updatePlayer();
		}
		else
		{
			player.setLocation(gridPlayerLocation);
		}
		break;
	}
}
void FileInput::updatePlayer()
{
	for (int x = 0; x < (bSize * bSize); x++)
	{
		if (gridPlayerLocation == x)
		{
			gridBox[player.getPrevLocation()].player = false;
			gridBox[x].player = true;

		}
	}
}

void FileInput::setUpBox()
{
	int boxName = 0;
	for (int x = 0; x < (bSize * bSize); x++)
	{
		Box boxData;
		boxData.location = boxName;
		if (gridPlayerLocation == x)
		{
			boxData.player = true;
		}
		if (gridGoldLocation == x)
		{
			boxData.gold = true;
		}
		if (gridWumpusLocation == x)
		{
			boxData.wumpus = true;
		}
		for (int j = 0; j < gridPitLocations.size(); j++)
		{
			if (gridPitLocations[j] == x)
			{
				boxData.pit = true;
			}
		}
		gridBox.push_back(boxData);
		boxName++;
	}
}
std::vector<FileInput::Box> FileInput::giveBoxInfo() {
	return gridBox;
}
void FileInput::fillLowerBounds()
{
	int number;
	for (int x = 0; x < bSize; x++)
	{
		number = bSize * x;
		lowerBounds[x] = number;
		std::cout << "LOWER BOUNDS: " << lowerBounds[x] << std::endl;
	}
}

//type 0 = west/east. 1 = north/south
//subject target location
//tempGL wanted location
bool FileInput::isWithinBounds(int subject, int tempGL, int type)
{
	if (type == 0)//West East lower bounds
	{
		int lowerBoundSection = (subject / bSize);
		//int upperBoundSection = lowerBoundSection + bSize;
		std::cout << "LBS: " << lowerBoundSection << std::endl;
		if (tempGL < lowerBounds[lowerBoundSection])
		{
			return false;
		}
		if(tempGL > (lowerBounds[lowerBoundSection] + bSize-1))
		{
			return false;
		}	
	}
	if (type == 1) //north South lower bounds 
	{
		int lowerBoundSection = 0;
		int upperBoundSection = bSize-1;
		if (tempGL < lowerBounds[lowerBoundSection])
		{
			return false;
		}
		if (tempGL > lowerBounds[upperBoundSection] + bSize-1)
		{
			return false;
		}
	}
	
	return true;
}

void FileInput::getNeighbors()
{
	for (int x = 0; x < gridBox.size(); x++)
	{
		addEffect(gridBox[x].location, 3);
	}
}
