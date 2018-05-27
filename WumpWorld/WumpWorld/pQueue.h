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
	void erase()
	{
		while (current != head)
		{
			node * helperNode = new node();
			helperNode = current;

			current = current->prev;
			delete helperNode;
		}
		head = nullptr;
		current = head;
	}
	int size()
	{
		node *helperNode = new node();
		helperNode = head;
		int count = 0;
		while (helperNode != nullptr)
		{
			count++;
			helperNode = helperNode->next;
		}
		return count;
	}
	int dequeue()
	{
		node *helperNode = new node();
		helperNode = head;
	//	FileInput::Box returningBox;
		int low = getLowestDistance();
		
		if (helperNode != nullptr)
		{
			while (helperNode->box.currentDistance != low)
			{
				if (helperNode == nullptr)
				{
					return -20;
				}
				helperNode = helperNode->next;
				
			}


			//helperNode->box.visited = true;
			if (helperNode->prev != nullptr && helperNode->next != nullptr)
			{
				low = helperNode->box.location;
				helperNode->next->prev = helperNode->prev;
				helperNode->prev->next = helperNode->next;
				//return helderNode;
			//	returningBox = helperNode->box;
				
				std::cout << helperNode->box.location << " Deleted" << std::endl;

				delete helperNode;


			}
			else if (helperNode->prev == nullptr && helperNode->next == nullptr)
			{
				low = helperNode->box.location;
				head = nullptr;
				current = head;
				
				delete helperNode;
			}
			else if (helperNode->prev != nullptr)
			{
				low = helperNode->box.location;
				helperNode->prev->next = nullptr;
				//return helderNode;
				current = helperNode->prev;
				
				std::cout << helperNode->box.location << " Deleted" << std::endl;
				//returningBox = helperNode->box;
				delete helperNode;

			}
			else
			{
				low = helperNode->box.location;
				helperNode->next->prev = nullptr;
				head = helperNode->next;
				
				//returningBox = helperNode->box;

				std::cout << helperNode->box.location << " Deleted" << std::endl;
				delete helperNode;
			}
		}
	
		return low;
	}

	int getLowestDistance()
	{
		int lowestValue;
		FileInput::Box tempSmall;
		node *helperNode = current;
		if (head != nullptr)
		{
			helperNode = head;
			lowestValue = helperNode->box.currentDistance;
			do {
				if (lowestValue > helperNode->box.currentDistance)
				{
					lowestValue = helperNode->box.currentDistance;
					tempSmall = helperNode->box;
				}
				helperNode = helperNode->next;
			} while (helperNode != nullptr);
			delete helperNode;
			return lowestValue;
		}
	}
};
