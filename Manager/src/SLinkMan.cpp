#include "SLinkMan.h"
#include "SLinkIterator.h"

SLinkMan::SLinkMan()
{
	this->pHead = nullptr;
	this->pTail = nullptr;
	this->pIterator = new SLinkIterator();
}

SLinkMan::~SLinkMan()
{
	delete this->pIterator;
	this->pIterator = nullptr;
}

void SLinkMan::AddToFront(Node* pNode) 
{
	assert(pNode != nullptr);
	SLink* pTmp = (SLink*)pNode;

	if (this->pHead == nullptr)
	{
		//add as head
		this->pHead = this->pTail = pTmp;
		this->pHead->pNext = nullptr;
	}
	else
	{
		//add before head
		pTmp->pNext = this->pHead;
		this->pHead = pTmp;
	}
}

void SLinkMan::AddToEnd(Node* pNode) 
{
	assert(pNode != nullptr);
	SLink* pTmp = (SLink*)pNode;

	if (this->pHead == nullptr)
	{
		//add as head
		this->pHead = this->pTail = pTmp;
		this->pHead->pNext = nullptr;
	}
	else
	{
		//add to end
		this->pTail->pNext = pTmp;
		pTmp->pNext = nullptr;

		//update tail ptr
		this->pTail = pTmp;
	}

	//pTmp->ResetLink();
}

void SLinkMan::Remove(Node* pNode) 
{
	assert(pNode != nullptr);
	assert(this->pHead != nullptr);
	SLink* pTmp = (SLink*)pNode;

	if (this->pHead == pTmp)
	{
		//first node
		this->pHead = pTmp->pNext;
	}
	else
	{
		//middle or last node
		SLink* pCurr = this->pHead;
		SLink* pPrev = nullptr;

		//iterate and find
		while (pCurr != pTmp)
		{
			pPrev = pCurr;
			pCurr = pCurr->pNext;
		}

		//found it, now unattach
		if (this->pTail == pCurr)
		{
			//unattach end node
			this->pTail = pPrev;
			pPrev->pNext = nullptr;
		}
		else
		{
			pPrev->pNext = pCurr->pNext;
			pCurr->pNext = nullptr;
		}
	}

	pTmp->ResetLink();
}
	
Node* SLinkMan::RemoveFromFront() 
{
	assert(this->pHead != nullptr);
	SLink* pTmp = this->pHead;
	this->pHead = this->pHead->pNext;

	pTmp->ResetLink();
	return pTmp;
}

Iterator* SLinkMan::GetIterator()
{
	this->pIterator->ResetIterator(this->pHead);
	return this->pIterator;
}