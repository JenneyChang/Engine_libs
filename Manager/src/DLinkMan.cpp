#include "DLinkMan.h"
#include "List.h"
#include "DLinkIterator.h"

DLinkMan::DLinkMan() 
{ 
	this->pIterator = new DLinkIterator();
	this->pHead = nullptr;
	this->pTail = nullptr;
}

DLinkMan::~DLinkMan()
{
	delete this->pIterator;
	this->pIterator = nullptr;

}

void DLinkMan::AddToFront(Node* pNode)
{
	//check incoming
	assert(pNode != nullptr);
	DLink* pTmp = (DLink*)pNode;

	//if list is empty, add as head
	if (this->pHead == nullptr)
	{
		this->pHead = this->pTail = pTmp;
		pTmp->pPrev = nullptr;
		pTmp->pNext = nullptr;
	}
	//else, push to front
	else
	{
		//attach new node
		pTmp->pNext = this->pHead;
		pTmp->pPrev = nullptr;

		//update head
		this->pHead->pPrev = pTmp;
		this->pHead = pTmp;
	}
}

void DLinkMan::AddToEnd(Node* pNode)
{
	assert(pNode != nullptr);
	DLink* pTmp = (DLink*)pNode;

	//if empty list, add as head
	if (this->pHead == nullptr)
	{
		this->pHead = this->pTail = pTmp;
		pTmp->pNext = nullptr;
		pTmp->pPrev = nullptr;
	}
	//else, add to end
	else
	{
		//add to to end
		this->pTail->pNext = pTmp;
		pTmp->pPrev = this->pTail;
		pTmp->pNext = nullptr;

		//update tail ptr
		this->pTail = pTmp;
	}
}

void DLinkMan::Remove(Node* pNode)
{
	//check incoming & list exists
	assert(this->pHead != nullptr);
	assert(pNode != nullptr);
	DLink* pTmp = (DLink*)pNode;

	//only node on list
	if (pTmp->pPrev == nullptr && pTmp->pNext == nullptr)
	{
		this->pHead = this->pTail = nullptr;
	}
	//head node
	else if (pTmp->pPrev == nullptr && pTmp->pNext != nullptr)
	{
		this->pHead = pTmp->pNext;
		pTmp->pNext->pPrev = pTmp->pPrev;
	}
	//last node
	else if (pTmp->pPrev != nullptr && pTmp->pNext == nullptr)
	{
		this->pTail = pTail->pPrev;
		pTmp->pPrev->pNext = nullptr;
	}
	//middle node
	else
	{
		pTmp->pNext->pPrev = pTmp->pPrev;
		pTmp->pPrev->pNext = pTmp->pNext;
	}

	//clear link
	pTmp->ResetLink();
}

Node* DLinkMan::RemoveFromFront()
{
	//assert(this->pHead != nullptr);

	Node* temp = this->pHead;

	//only node on list
	if (this->pHead->pNext == nullptr)
	{
		this->pHead = this->pTail = nullptr;
	}
	//remove head
	else
	{
		this->pHead = this->pHead->pNext;
		this->pHead->pPrev = nullptr;
	}

	//clear links
	temp->ResetLink();

	return temp;
}

Iterator* DLinkMan::GetIterator()
{
	this->pIterator->ResetIterator(this->pHead);
	return this->pIterator;
}

void DLinkMan::AddByPriority(Node* pNode)
{
	assert(pNode != nullptr);
	DLink* pTmp = (DLink*)pNode;

	if (this->pHead == nullptr) 
	{
		//empty list, simple add
		this->pHead = this->pTail = pTmp;
		pTmp->pNext = nullptr;
		pTmp->pPrev = nullptr;
	}
	else 
	{
		DLink* pCurr = this->pHead;
		DLink* pPrev = nullptr;

		//iterate list
		while (pCurr != nullptr)
		{
			if (pCurr->ComparePriority(pTmp))
			{
				//curr priority is >= InNode priortiy, exit 
				break;
			}

			pPrev = pCurr;			//save ref
			pCurr = pCurr->pNext;	//get next 
		}

		if (pCurr == nullptr)
		{
			//reached end list, add at end
			pPrev->pNext = pTmp;
			pTmp->pPrev = pPrev;
			pTmp->pNext = nullptr;

			//update tail pointer
			this->pTail = pTmp;
		}
		else if (pCurr == this->pHead)
		{
			//add as head
			pTmp->pNext = this->pHead;
			this->pHead->pPrev = pTmp;

			this->pHead = pTmp;
		}
		else
		{
			//add before
			pPrev->pNext = pTmp;
			pCurr->pPrev = pTmp;

			pTmp->pPrev = pPrev;
			pTmp->pNext = pCurr;
		}
	}
}