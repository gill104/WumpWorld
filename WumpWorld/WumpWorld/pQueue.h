#pragma once
#include "FileInput.h"
class pQueue
{
private:
	class node {
	public:
		FileInput::Box box;
		int value;
		node *next;
		node *prev;
		node()
		{
			value = -99;
			next = nullptr;
			prev = nullptr;
		}
		node(FileInput::Box b,int v, node *n = nullptr, node *p = nullptr)
		{
			box = b;
			value = v;
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
	pQueue(FileInput::Box target)
	{
		head = new node(target,target.location);
	}
	bool empty()
	{
		if (head == nullptr)
		{
			return true;
		}
		return false;
	}
	template <typename T>
	void enqueue(T item)
	{
		if (head == nullptr)
		{
			head = new node(item);
			current = head;
		}
		else
		{
			node *newNode = new node(item);
			current->next = newNode;
			newNode->prev = current;
			current = newNode;
		}
	}
	template <typename T>
	T dequeue()
	{
		if (head != nullptr)
		{
			node *helperNode = new node();
			helperNode = getLowest();

			if (helperNode->prev != nullptr && helperNode->next != nullptr)
			{

				helperNode->next->prev = helperNode->prev;
				helperNode->prev->next = helperNode->next;
				return helderNode;
				delete [] helperNode;
			}
			else if (helperNode->prev != nullptr)
			{
				helperNode->prev->next = nullptr;
				return helderNode;
				delete[] helperNode;
			}
			else
			{
				helperNode->next->prev = nullptr;
				head = helperNode->next;
				current = head;
				return helderNode;
				delete[] helperNode;
			}
		}
	}
	template <typename T>
	T getLowest()
	{
		int lowestValue;
		if (head != nullptr)
		{
			current = head;
			lowestValue = current->value;
			do {
				if (lowestValue < current->value)
				{
					lowestValue = current->value;
				}
				current = current->next;
			} while (current != nullptr);

		}
	}

};