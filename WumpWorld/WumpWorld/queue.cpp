//#pragma once
//#include "FileInput.h"
//class pQueue
//{
//private:
//	class node {
//	public:
//		FileInput::Box box;
//		node *next;
//		node *prev;
//		node()
//		{
//			next = nullptr;
//			prev = nullptr;
//		}
//		node(FileInput::Box b, node *n = nullptr, node *p = nullptr)
//		{
//			box = b;
//		}
//	};
//public:
//	node * head;
//	node * current;
//	pQueue()
//	{
//		head = nullptr;
//		current = nullptr;
//	}
//	pQueue(FileInput::Box box)
//	{
//		head = new node(box);
//	}
//	bool empty()
//	{
//		if (head == nullptr)
//		{
//			return true;
//		}
//		return false;
//	}
//	void enqueue(FileInput::Box box)
//	{
//		if (head == nullptr)
//		{
//			head = new node(box);
//			current = head;
//		}
//		else
//		{
//			node *newNode = new node(box);
//			current->next = newNode;
//			newNode->prev = current;
//			current = newNode;
//		}
//	}
//	FileInput::Box dequeue()
//	{
//		if (head != nullptr)
//		{
//			node *helperNode = new node();
//			helperNode = getLowestDistance();
//
//			if (helperNode->prev != nullptr && helperNode->next != nullptr)
//			{
//
//				helperNode->next->prev = helperNode->prev;
//				helperNode->prev->next = helperNode->next;
//				return helderNode;
//				delete[] helperNode;
//			}
//			else if (helperNode->prev != nullptr)
//			{
//				helperNode->prev->next = nullptr;
//				return helderNode;
//				delete[] helperNode;
//			}
//			else
//			{
//				helperNode->next->prev = nullptr;
//				head = helperNode->next;
//				current = head;
//				return helderNode;
//				delete[] helperNode;
//			}
//		}
//	}
//
//	FileInput::Box getLowestDistance()
//	{
//		int lowestValue;
//		if (head != nullptr)
//		{
//			current = head;
//			lowestValue = current->value;
//			do {
//				if (lowestValue < current->box.currentDistance)
//				{
//					lowestValue = current->value;
//				}
//				current = current->next;
//			} while (current != nullptr);
//
//		}
//	}
//
//};