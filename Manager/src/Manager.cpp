#include "Manager.h"
#include "List.h"
#include "DLinkMan.h"


//------------------------------------------------------------------------------------
//	CONSTRUCTORS
//------------------------------------------------------------------------------------

Manager::Manager(int numGrow)
{
	assert(numGrow > 0);

	this->numGrow = numGrow;
	this->totalActive = 0;
	this->totalReserve = 0;
	this->totalNodes = 0;

	this->pActive = new DLinkMan();
	this->pReserve = new DLinkMan();
}

Manager::~Manager()
{
	delete this->pActive;
	delete this->pReserve;
}

//------------------------------------------------------------------------------------
//	BASE METHOD
//------------------------------------------------------------------------------------

Iterator* Manager::baseGetActiveIterator()
{
	return this->pActive->GetIterator();
}

Iterator* Manager::baseGetReserveIterator()
{
	return this->pReserve->GetIterator();
}


Node* Manager::baseAddToFront() 
{
	Iterator* it = this->pReserve->GetIterator();

	//if reserve = empty, fill it
	if (it->First() == nullptr)
	{
		this->FillReserve(this->numGrow);
	}

	//pluck from reserve
	Node* pNode = this->pReserve->RemoveFromFront();
	assert(pNode != nullptr);

	//add to active
	this->pActive->AddToFront(pNode);
	
	//update stats
	this->totalActive++;
	this->totalReserve--;

	return pNode;
}

Node* Manager::baseAddToEnd()
{
	Iterator* it = this->pReserve->GetIterator();
	
	//if reserve = empty, fill it
	if (it->First() == nullptr)
	{
		this->FillReserve(this->numGrow);
	}

	//pluck reserve node
	Node* pNode = this->pReserve->RemoveFromFront();
	assert(pNode != nullptr);

	//add to active
	this->pActive->AddToEnd(pNode);

	//update stats
	this->totalReserve--;
	this->totalActive++;

	return pNode;
}

Node* Manager::baseAddByPriority(Node* pNode)
{
	assert(pNode != nullptr);

	//the add
	this->pActive->AddByPriority(pNode);

	//update stats
	this->totalActive++;

	return pNode;
}

Node* Manager::baseGetReserve()
{
	Iterator* it = this->pReserve->GetIterator();
	assert(it != nullptr);

	//fill reserve if empty
	if (it->First() == nullptr)
	{
		this->FillReserve(this->numGrow);
	}

	//pop reserve node
	Node* pNode = this->pReserve->RemoveFromFront();
	assert(pNode != nullptr);

	//update stats
	this->totalReserve--;

	return pNode;
}

Node* Manager::baseFind(Node* pNode)
{
	assert(pNode != nullptr);

	Iterator* it = this->pActive->GetIterator();
	Node* temp = it->First();

	while (!it->IsDone())
	{
		if (temp->Compare(pNode))
		{
			break;
		}
		temp = it->Next();
	}

	return temp;
}

void Manager::baseRemove(Node* pNode)
{
	assert(pNode != nullptr);

	//remove from active
	this->pActive->Remove(pNode);

	//return to reserve
	this->pReserve->AddToFront(pNode);

	//update stats
	this->totalActive--;
	this->totalReserve++;
}

void Manager::basePrint()
{
	Trace::out("      numGrow: %d \n", numGrow);
	Trace::out("  Total Nodes: %d \n", totalNodes);
	Trace::out("Total Reserve: %d \n", totalReserve);
	Trace::out(" Total Active: %d \n", totalActive);
	Trace::out("\n");

	Iterator* pItActive = pActive->GetIterator();
	assert(pItActive != nullptr);
	Node* pNodeActive = pItActive->First();

	Trace::out("   ------ Active List: -----------\n");

	if (pNodeActive == nullptr)
	{
		Trace::out("    Active Head: null\n");
	}
	else
	{
		Trace::out("    Active Head: (%p)\n", pNodeActive);
	}

	int i = 0;
	Node* pData = pItActive->First();
	while (!pItActive->IsDone())
	{
		Trace::out("   %d: -------------\n", i);
		pData->PrintLink();
		i++;
		pData = pItActive->Next();
	}
	Trace::out("\n");

	Iterator* pItReserve = pReserve->GetIterator();
	assert(pItReserve != nullptr);
	Node* pNodeReserve = pItReserve->First();

	Trace::out("   ------ Reserve List: ----------\n");

	if (pNodeReserve == nullptr)
	{
		Trace::out("   Reserve Head: null\n");
	}
	else
	{
		Trace::out("   Reserve Head: (%p)\n", pNodeReserve);
	}
	Trace::out("\n");

	i = 0;
	pData = pItReserve->First();
	while (!pItReserve->IsDone())
	{
		Trace::out("   %d: -------------\n", i);
		pData->PrintLink();
		i++;
		pData = pItReserve->Next();
	}
	Trace::out("\n");
	Trace::out("   ------ End ------- \n");
	Trace::out("\n");
}


//------------------------------------------------------------------------------------
//	PRIVATE METHOD
//------------------------------------------------------------------------------------

void Manager::FillReserve(int num)
{
	//check number
	assert(num > 0);

	//load reserve
	for (int i = 0; i < num; i++)
	{
		Node* pNode = this->derivedCreateNode();
		assert(pNode != nullptr);

		this->pReserve->AddToFront(pNode);
	}

	//update stats
	this->totalNodes += num;
	this->totalReserve += num;
}
