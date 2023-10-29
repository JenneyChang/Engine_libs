#pragma once
#ifndef MANAGER_H
#define MANGER_H

#include "Iterator.h"

//Forward declare
class List;

class Manager
{
public:
	//disabled
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;

protected:
	List* pActive;
	List* pReserve;

	int numGrow;
	int totalNodes;
	int totalReserve;
	int totalActive;

protected:

	//Constructors
	Manager(int numGrow);
	virtual ~Manager();

	//Get Iterators
	Iterator* baseGetActiveIterator();
	Iterator* baseGetReserveIterator();

	//Base methods
	Node* baseAddToFront();
	Node* baseAddToEnd();
	Node* baseFind(Node* pNode);
	void baseRemove(Node* pNode);
	void basePrint();

	//specific time events...
	Node* baseAddByPriority(Node* pNode);
	Node* baseGetReserve();

	//helper method
	void FillReserve(int num);

	//pure virtual/abstract method
	virtual Node* derivedCreateNode() = 0;


};

#endif // !MANAGER_H
