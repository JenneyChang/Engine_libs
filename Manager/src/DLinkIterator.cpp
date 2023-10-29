#include "DLinkIterator.h"
#include "DLink.h"

DLinkIterator::DLinkIterator() : Iterator()
{
	this->prClear();
}

Node* DLinkIterator::Next()
{
	DLink* temp = (DLink*)this->pCurr;

	if (temp != nullptr)
	{
		temp = temp->pNext;
	}

	this->pCurr = temp;

	if (this->pCurr == nullptr)
	{
		this->done = true;
	}
	else
	{
		this->done = false;
	}

	return this->pCurr;
}

Node* DLinkIterator::First()
{
	if (this->pHead != nullptr)
	{
		this->done = false;
		this->pCurr = this->pHead;
	}
	else
	{
		this->prClear();
	}

	return this->pCurr;
}

Node* DLinkIterator::Curr()
{
	return this->pCurr;
}

bool DLinkIterator::IsDone()
{
	return this->done;
}

void DLinkIterator::ResetIterator(Node* head)
{
	if (head != nullptr)
	{
		done = false;
		pCurr = head;
		pHead = head;
	}
	else
	{
		this->prClear();
	}
}


void DLinkIterator::prClear()
{
	this->pHead = nullptr;
	this->pCurr = nullptr;
	this->done = true;
}