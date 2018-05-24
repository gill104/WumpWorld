#pragma once
#include "FileInput.h"
class pQueue
{
private:
	class node {
	public:
		FileInput::Box box;
		node *next;
		node *prev;
		node()
		{
			next = nullptr;
			prev = nullptr;
		}
		node(FileInput::Box b, node *n = nullptr, node *p = nullptr)
		{
			box = b;
		}
	};
public:
	node * head;
	node * current;
	pQueue()
	{
		head = nullptr;
		current = nullptr;
	}
	/*	pQueue(FileInput::Box box)
		{
			head = new node(box);
			current = head;
		}*/
	bool empty()
	{
		if (head == nullptr)
		{
			return true;
		}
		return false;
	}
	void enqueue(FileInput::Box box)
	{
		if (head == nullptr)
		{
			head = new node(box);
			current = head;
		}
		else
		{
			node *newNode = new node(box);
			current->next = newNode;
			newNode->prev = current;
			current = newNode;
		}
	}
	std::vector<int> checkForNeighbors()
	{
		std::vector<int> neededNeighbors;
		if (head != nullptr)//something in the link list
		{
			current = head;
			if (current->box.neighbors.size() > 0)//that is the start location
			{
				//if box has neighbors
				//get their true distance
				for (int x = 0; x < current->box.neighbors.size(); x++)
				{
					if (current->box.neighbors[x] > 0)
					{
						std::cout << "neighbors: " << current->box.neighbors[x] << std::endl;
						neededNeighbors.push_back(current->box.neighbors[x]);
					}
				}
			}
			return neededNeighbors;
		}

		
	}
	FileInput::Box dequeue()
	{
		node *helperNode = new node();
		helperNode = head;
		FileInput::Box returningBox;
		int low = getLowestDistance();
		
		while (helperNode->box.currentDistance != low)
		{
			if (helperNode == nullptr)
			{
				std::cout << "Error lowest not found" << std::endl;
			}
			else
				helperNode = helperNode->next;
		}
		if (helperNode->prev != nullptr && helperNode->next != nullptr)
		{

			helperNode->next->prev = helperNode->prev;
			helperNode->prev->next = helperNode->next;
			//return helderNode;
			returningBox = helperNode->box;
			std::cout << helperNode->box.location << " Deleted" << std::endl;
			
			delete helperNode;
			

		}
		else if (helperNode->prev != nullptr)
		{
			helperNode->prev->next = nullptr;
			//return helderNode;
			std::cout << helperNode->box.location << " Deleted" << std::endl;
			returningBox = helperNode->box;
			delete helperNode;

		}
		else
		{
			helperNode->next->prev = nullptr;
			head = helperNode->next;
			returningBox = helperNode->box;

			std::cout << helperNode->box.location << " Deleted" << std::endl;
			delete helperNode;
		}

		return returningBox;
	}

	int getLowestDistance()
	{
		int lowestValue;
		FileInput::Box tempSmall;
		if (head != nullptr)
		{
			current = head;
			lowestValue = current->box.currentDistance;
			do {
				if (lowestValue > current->box.currentDistance)
				{
					lowestValue = current->box.currentDistance;
					tempSmall = current->box;
				}
				current = current->next;
			} while (current != nullptr);
			return lowestValue;
		}
	}
};
